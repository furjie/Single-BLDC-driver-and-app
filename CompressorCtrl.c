/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved. 
*
* This software is owned and published by: 
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion 
* components. This software is licensed by Spansion to be adapted only 
* for use in systems utilizing Spansion components. Spansion shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein.  Spansion is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.  
*/
/******************************************************************************/
/** \file CompressorCtrl.c
 **
 ** Add description here...
 **
 ** History:
 **   - 2011-11-10  0.1.0  Stom    First version
 **   - 2012-12-12  0.2.0  Devin   Modify varible name, optizime startup
 **   - 2013-09-11  0.2.1  Tyler   Update Fixed-Point math and Filter module
 **   - 2013-09-15  0.2.2  Micheal Update coordinate transformation and PID module
 **   - 2013-09-22  0.2.3  Stom    Add over-modulation function, update SVPWM and
 **                                Single shunt module
 **   - 2013-10-05  0.2.3  Jason   Update ADC, fieldweaken, PFC, torque compeansation
 **                                module
 **   - 2013-10-10  0.2.4  Kartik  Update startup module
 **   - 2013-12-16  0.3.0  Stom    Modify varible name acorrding code standard
*****************************************************************************/


/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stdlib.h>
#include "InitMcu.h"
#include "CompressorCtrl.h"
#include "system_s6e1a1.h"
#include "s6e1a1.h"
#include "base_types.h"
#include "Isr.h"
#include "uart.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
typedef struct 
{
    INT32S i32Q12_LPFK;
    INT32S i32Q20_LowBits;
}stc_one_order_lpf;

typedef struct
{
    INT32S i32Q8_ISensedFilter;
    INT32S i32Q8_IRef_pre;
    INT32S i32Q8_IRef;
    INT32S i32Q8_IPidReg; 
    INT32S i32Q8_SpeedPidReg; 
    INT32S i32Q8_SpeedIBase; 
    INT32S i32Q16_VoutTemp;
    INT32S i32Q16_UTemp;   
    INT32S i32Q16_ETemp;
    INT8U  u8Flag;
} stc_comp_i_t;

typedef struct
{
    INT32S i32Q8_VBase_pre;
    INT32S i32Q8_VBase;
    INT32S i32Q8_VOutPeak;   
    INT32S i32Q8_VOut;  
    INT32S i32Q16_UTemp ;
    INT32S i32Q16_UTemp1 ;
    INT32S i32Q16_ETemp;
} stc_comp_v_t;


typedef struct
{
    volatile INT32U u32Timer0;
    volatile INT32U u32Timer1;
    volatile INT32U u32Timer2;
    volatile INT32U u32Timer3;
} stc_soft_timers_t;


typedef struct
{
	INT32S i32Q8_Kp;          
	INT32S i32Q8_Ki; 
	INT32S i32Q16_Ki;
	INT32S i32Q8_Kd;         
	INT32S i32Q8_OutMax;       
	INT32S i32Q8_OutMin;
	INT32S i32Q8_ErroPre;         
	INT32S i32Q8_ErroNow;          
	INT32S i32Q8_Pout;  
	INT32S i32Q8_Iout;
	INT32S i32Q16_Iout; 
	INT32S i32Q8_Out;  
	INT32S i32Q8_Out_pre;	
}stc_pid_t;

typedef struct 
{
    INT32S i32Q8_Res;
    INT32S i32Q8_Ls;
    INT32S i32Q8_Ke;
} stc_compctl_customer_t;

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
stc_pwm_gen_t       st_CompCtrlPwm;

stc_comp_run_t      st_CompRunPar;
stc_sensor_t        st_AdcSample;
stc_hall_detect_t   st_HallDetect;

stc_soft_timers_t   st_SoftTimers;
stc_one_order_lpf   st_Powerdlpf = {Q12(0.05),Q20(0.0)};   //滤波系数
stc_one_order_lpf   st_ISensedlpf = {Q12(0.8),Q20(0.0)};   //滤波系数
stc_pid_t           st_CompCtrlIPidReg;
stc_pid_t           st_CompCtrlSpeedPidReg;
stc_pid_t           st_CompCtrlPowerPidReg;

stc_comp_i_t        st_CompIPara;
stc_comp_v_t        st_CompVPara;

stc_compctl_customer_t  st_CompCustomerPara;

stc_angle_para   st_CompRunAngle;

stc_Power_para   st_CompPower;

stc_motor_warn_para st_MotorWarnPara;

const unsigned short Q12MotorSinTbl[] = {0x0000,							   //0
0x0019, 0x0032, 0x004B, 0x0064, 0x007D, 0x0096, 0x00AF, 0x00C8, 0x00E2, 0x00FB,//10
0x0114, 0x012D, 0x0146, 0x015F, 0x0178, 0x0191, 0x01AA, 0x01C3, 0x01DC, 0x01F5,//20
0x020E, 0x0227, 0x0240, 0x0258, 0x0271, 0x028A, 0x02A3, 0x02BC, 0x02D4, 0x02ED,//30
0x0306, 0x031F, 0x0337, 0x0350, 0x0368, 0x0381, 0x0399, 0x03B2, 0x03CA, 0x03E3,//40
0x03FB, 0x0413, 0x042C, 0x0444, 0x045C, 0x0474, 0x048C, 0x04A4, 0x04BC, 0x04D4,//50
0x04EC, 0x0504, 0x051C, 0x0534, 0x054C, 0x0563, 0x057B, 0x0593, 0x05AA, 0x05C2,//60
0x05D9, 0x05F0, 0x0608, 0x061F, 0x0636, 0x064D, 0x0664, 0x067B, 0x0692, 0x06A9,//70
0x06C0, 0x06D7, 0x06ED, 0x0704, 0x071B, 0x0731, 0x0747, 0x075E, 0x0774, 0x078A,//80
0x07A0, 0x07B6, 0x07CC, 0x07E2, 0x07F8, 0x080E, 0x0824, 0x0839, 0x084F, 0x0864,//90
0x087A, 0x088F, 0x08A4, 0x08B9, 0x08CE, 0x08E3, 0x08F8, 0x090D, 0x0921, 0x0936,//100
0x094A, 0x095F, 0x0973, 0x0987, 0x099C, 0x09B0, 0x09C4, 0x09D7, 0x09EB, 0x09FF,//110
0x0A12, 0x0A26, 0x0A39, 0x0A4D, 0x0A60, 0x0A73, 0x0A86, 0x0A99, 0x0AAB, 0x0ABE,//120
0x0AD1, 0x0AE3, 0x0AF6, 0x0B08, 0x0B1A, 0x0B2C, 0x0B3E, 0x0B50, 0x0B61, 0x0B73,//130
0x0B85, 0x0B96, 0x0BA7, 0x0BB8, 0x0BC9, 0x0BDA, 0x0BEB, 0x0BFC, 0x0C0C, 0x0C1D,//140
0x0C2D, 0x0C3E, 0x0C4E, 0x0C5E, 0x0C6E, 0x0C7D, 0x0C8D, 0x0C9C, 0x0CAC, 0x0CBB,//150
0x0CCA, 0x0CD9, 0x0CE8, 0x0CF7, 0x0D06, 0x0D14, 0x0D23, 0x0D31, 0x0D3F, 0x0D4D,//160
0x0D5B, 0x0D69, 0x0D76, 0x0D84, 0x0D91, 0x0D9F, 0x0DAC, 0x0DB9, 0x0DC6, 0x0DD2,//170
0x0DDF, 0x0DEB, 0x0DF8, 0x0E04, 0x0E10, 0x0E1C, 0x0E28, 0x0E33, 0x0E3F, 0x0E4A,//180
0x0E55, 0x0E60, 0x0E6B, 0x0E76, 0x0E81, 0x0E8B, 0x0E96, 0x0EA0, 0x0EAA, 0x0EB4,//190
0x0EBE, 0x0EC8, 0x0ED1, 0x0EDB, 0x0EE4, 0x0EED, 0x0EF6, 0x0EFF, 0x0F07, 0x0F10,//200
0x0F18, 0x0F21, 0x0F29, 0x0F31, 0x0F39, 0x0F40, 0x0F48, 0x0F4F, 0x0F56, 0x0F5D,//210
0x0F64, 0x0F6B, 0x0F72, 0x0F78, 0x0F7F, 0x0F85, 0x0F8B, 0x0F91, 0x0F96, 0x0F9C,//220
0x0FA1, 0x0FA7, 0x0FAC, 0x0FB1, 0x0FB6, 0x0FBA, 0x0FBF, 0x0FC3, 0x0FC7, 0x0FCB,//230
0x0FCF, 0x0FD3, 0x0FD7, 0x0FDA, 0x0FDE, 0x0FE1, 0x0FE4, 0x0FE7, 0x0FE9, 0x0FEC,//240
0x0FEE, 0x0FF0, 0x0FF2, 0x0FF4, 0x0FF6, 0x0FF8, 0x0FF9, 0x0FFB, 0x0FFC, 0x0FFD,//250
0x0FFE, 0x0FFE, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF};							   //256

INT16S i16DutMax = 0;
INT16S i16Duty = 0;
INT32S i32Q12_CompSinValue = 0; 
/**************************************************************************
*    函数原型: void SetCompressorOn()
*    功    能: 开机
**************************************************************************/
void SetCompressorOn(void)
{
    if (st_CompRunPar.u8Status != MOTOR_RUNNING)    //关机状态下才能开机
    {
	    if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
	    {
		    st_CompPower.u32TargetPower = 20;
		}
		else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
		{
		    st_CompRunPar.i32TargetSpeedRpm = 500;
		}        
    }        
}
/**************************************************************************
*    函数原型: void SetCompressorOff()
*    功    能: 关机
**************************************************************************/
void SetCompressorOff(void)
{
	if (st_CompRunPar.u8Status == MOTOR_RUNNING)
	{
	    if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
	    {
		    st_CompPower.u32TargetPower = 0; 
		    st_CompPower.u32TargetPowerDecimal = 0;
		}
		else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
		{
		    st_CompRunPar.i32TargetSpeedRpm = 0;
		}
	}     
}

/**************************************************************************
*    函数原型: void SetNewTargrt(INT16U TargetValue)
*    功    能: 目标频率设定
**************************************************************************/
void SetNewTargrt(INT16U TargetValue)
{
    if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
    {
        if (TargetValue > st_CustomerPara.Comp_PowerMax)			//设定的最大最小值
    	{
    		TargetValue = st_CustomerPara.Comp_PowerMax;
    	}
    	else if (TargetValue < st_CustomerPara.Comp_PowerMin)
    	{
    		TargetValue = st_CustomerPara.Comp_PowerMin;
    	}
    	st_CompPower.u32TargetPower = TargetValue;
    }
    else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
    {
        if (TargetValue > st_CustomerPara.Comp_u16SpdMax)			//设定的最大最小值
    	{
    		TargetValue = st_CustomerPara.Comp_u16SpdMax;
    	}
    	else if (TargetValue < st_CustomerPara.Comp_u16SpdMin)
    	{
    		TargetValue = st_CustomerPara.Comp_u16SpdMin;
    	}
    	st_CompRunPar.i32TargetSpeedRpm = TargetValue;
    }
}

/**************************************************************************
*    函数原型:void GetRunParameter(void) 
*    功    能:
**************************************************************************/
void GetRunParameter(void)
{
    RunParameter.Data.CompressorStatus = st_CompRunPar.u8Status;
    RunParameter.Data.AlarmCode = st_CompRunPar.u32ErroType;
    RunParameter.Data.CompressorSpeed = st_CompRunPar.i32CurrentSpeedRpm;
    RunParameter.Data.CompPower = st_CompPower.u32CompPower;
    RunParameter.Data.BoardTemp = (INT16S)st_BoardTemperature.BoardTemperature - 40;
    RunParameter.Data.CurrentConsumption = st_CompRunPar.i32Q8_ISensed;
    RunParameter.Data.SoftwareVersion = 0x01;

}
/****************************************************
Function name:	Q12_Sin
description:    calculate sin(theta)
input:
output:
****************************************************/
INT32S Q12_Sin(INT32U Angle)
{
	INT32U AngleTemp;
	INT32S SineValue;
	
	AngleTemp =  Angle;
	//AngleTemp &= 0x03FF;            //0~1024
	
	if (AngleTemp <= 256)
	{
		SineValue = Q12MotorSinTbl[AngleTemp];
	}	
	else if (AngleTemp <= 512)
	{
		AngleTemp = 512 - AngleTemp;
		SineValue = Q12MotorSinTbl[AngleTemp];
	}
	#if 0
	else if (AngleTemp <= 768)
	{
		AngleTemp -= 512;
		SineValue = -Q12MotorSinTbl[AngleTemp];
	}
	else if (AngleTemp <= 1024)
	{
		AngleTemp = 1024 - AngleTemp;
		SineValue = -Q12MotorSinTbl[AngleTemp];
	}
	#endif
	else
	{
	    SineValue = 0;
	}

	return (SineValue);
}
/****************************************************
 Function name: Q8_to_Q12_SpeedPI
 description:
 input:         none
 output:            none
 ****************************************************/
INT32S Q8_to_Q8_SpeedPI(INT32S Reference, INT32S Input, stc_pid_t *PIParameter)
{
	INT32S sltemp0;
	INT32S Output;

	PIParameter->i32Q8_Out_pre = PIParameter->i32Q8_Out;
	//PIParameter->i32Q8_ErroPre = PIParameter->i32Q8_ErroNow;
	PIParameter->i32Q8_ErroNow = Reference - Input;	  
	PIParameter->i32Q8_Pout = (PIParameter->i32Q8_ErroNow * PIParameter->i32Q8_Kp)>>8;
    PIParameter->i32Q16_Iout += PIParameter->i32Q8_ErroNow * PIParameter->i32Q8_Ki;
    sltemp0 = PIParameter->i32Q16_Iout>>8;
   	PIParameter->i32Q8_Iout = sltemp0;
    sltemp0 <<= 8;
    PIParameter->i32Q16_Iout -= sltemp0;
	  
	if(PIParameter->i32Q8_Iout > PIParameter->i32Q8_OutMax)
	{
		PIParameter->i32Q8_Iout = PIParameter->i32Q8_OutMax;
	}
	else if(PIParameter->i32Q8_Iout < PIParameter->i32Q8_OutMin)
	{
		PIParameter->i32Q8_Iout = PIParameter->i32Q8_OutMin;
	}
	
	PIParameter->i32Q8_Out = PIParameter->i32Q8_Pout + PIParameter->i32Q8_Iout ;


	if(PIParameter->i32Q8_Out > PIParameter->i32Q8_OutMax)
	{
		Output = PIParameter->i32Q8_OutMax;
	}
	else if(PIParameter->i32Q8_Out < PIParameter->i32Q8_OutMin)
	{
		Output = PIParameter->i32Q8_OutMin;
	}
	else
	{
		Output = PIParameter->i32Q8_Out;
	}
    
    return(Output);

}

/****************************************************
 Function name: Q8_to_Q8_PID
 description:
 input:         none
 output:            none
 ****************************************************/
INT32S Q8_to_Q8_PID(INT32S Reference, INT32S Input,  stc_pid_t *PIParameter)
{
	INT32S sltemp0;
	INT32S Output;

	PIParameter->i32Q8_Out_pre = PIParameter->i32Q8_Out;
	PIParameter->i32Q8_ErroPre = PIParameter->i32Q8_ErroNow;
	PIParameter->i32Q8_ErroNow = Reference - Input;	  
	PIParameter->i32Q8_Pout = ((PIParameter->i32Q8_ErroNow - PIParameter->i32Q8_ErroPre) * PIParameter->i32Q8_Kp)>>8;
    PIParameter->i32Q16_Iout += (PIParameter->i32Q8_ErroNow * PIParameter->i32Q16_Ki)>>8;
    sltemp0 = PIParameter->i32Q16_Iout>>8;
   	PIParameter->i32Q8_Iout = sltemp0;
    sltemp0 <<= 8;
    PIParameter->i32Q16_Iout -= sltemp0;
	  
	if(PIParameter->i32Q8_Iout > PIParameter->i32Q8_OutMax)
	{
		PIParameter->i32Q8_Iout = PIParameter->i32Q8_OutMax;
	}
	else if(PIParameter->i32Q8_Iout < PIParameter->i32Q8_OutMin)
	{
		PIParameter->i32Q8_Iout = PIParameter->i32Q8_OutMin;
	}
	
	PIParameter->i32Q8_Out = PIParameter->i32Q8_Pout + PIParameter->i32Q8_Iout + PIParameter->i32Q8_Out_pre;


	if(PIParameter->i32Q8_Out > PIParameter->i32Q8_OutMax)
	{
		PIParameter->i32Q8_Out = PIParameter->i32Q8_OutMax;
	}
	else if(PIParameter->i32Q8_Out < 0)
	{
		PIParameter->i32Q8_Out = 0;
	}
	else
	{
		PIParameter->i32Q8_Out = PIParameter->i32Q8_Out;
	}

    Output = PIParameter->i32Q8_Out;
    return(Output);
}

/****************************************************
 Function name: F_OneOderLPF
 description:
 input:         none
 output:            none
 ****************************************************/
void Filter_OneOderLPF(INT32S Input, INT32S *Output, stc_one_order_lpf *LPFPar)
{
	INT32S  sltmp0;
	INT32S  sltmp1;
	
	sltmp0 				 = *Output;
	sltmp1 				 = Input - sltmp0;
	sltmp1 				 = sltmp1 * LPFPar->i32Q12_LPFK;
	LPFPar->i32Q20_LowBits = sltmp1;
	sltmp1				 = sltmp1>>12;
    //sltmp1               = Qm_RightShift(LPFPar->Q20_LowBits,12);	
	*Output				 = sltmp0 + sltmp1;
}

/****************************************************
 Function name: CompCtrl_InitPar
 description:
 input:         none
 output:            none
 ****************************************************/
static void CompCtrl_InitPar(INT16U u16SampleFreq)
{ 
    st_CompRunPar.i32Q22_TargetWmIncTs = Q22(st_CustomerPara.Comp_f32SpdAccelerationHz * 4.0/u16SampleFreq);
    st_CompRunPar.i32Q22_TargetWmDecTs = Q22(st_CustomerPara.Comp_f32SpdDecelerationHz * 4.0/u16SampleFreq);

#if 0
	st_CompCtrlIPidReg.i32Q8_Kp = Q8(st_CustomerPara.Comp_f32Ikp);
	//st_CompCtrlIPidReg.i32Q8_Ki = Q8(st_CustomerPara.Comp_f32Iki);
	st_CompCtrlIPidReg.i32Q16_Ki = Q16(st_CustomerPara.Comp_f32Iki);
	st_CompCtrlIPidReg.i32Q8_Kd = Q8(0);
    st_CompCtrlIPidReg.i32Q8_OutMax = Q8(200);
	st_CompCtrlIPidReg.i32Q8_OutMin = Q8(-200);	
	st_CompCtrlIPidReg.i32Q8_ErroPre = Q8(0);
	st_CompCtrlIPidReg.i32Q8_ErroNow = Q8(0);
	st_CompCtrlIPidReg.i32Q8_Pout = Q8(0);
	st_CompCtrlIPidReg.i32Q8_Iout = Q8(0);
	st_CompCtrlIPidReg.i32Q8_Out  = Q8(0);
	st_CompCtrlIPidReg.i32Q8_Out_pre = Q8(0);
#endif	
    st_CompCtrlSpeedPidReg.i32Q8_Kp = Q8(st_CustomerPara.Comp_f32Skp);
	//st_CompCtrlSpeedPidReg.i32Q8_Ki = Q8(st_CustomerPara.Comp_f32Ski);
	st_CompCtrlSpeedPidReg.i32Q16_Ki = Q16(st_CustomerPara.Comp_f32Ski);
	st_CompCtrlSpeedPidReg.i32Q8_Kd = Q8(0);
    st_CompCtrlSpeedPidReg.i32Q8_OutMax = Q8(380);
	st_CompCtrlSpeedPidReg.i32Q8_OutMin = Q8(-380);
	st_CompCtrlSpeedPidReg.i32Q8_ErroPre = Q8(0);
	st_CompCtrlSpeedPidReg.i32Q8_ErroNow = Q8(0);
	st_CompCtrlSpeedPidReg.i32Q8_Pout = Q8(0);
	st_CompCtrlSpeedPidReg.i32Q8_Iout = Q8(0);
	st_CompCtrlSpeedPidReg.i32Q8_Out  = Q8(0);
	st_CompCtrlSpeedPidReg.i32Q8_Out_pre = Q8(0);
	
   
    st_CompCtrlPowerPidReg.i32Q8_Kp = Q8(st_CustomerPara.Comp_f32Powerkp);
	//st_CompCtrlSpeedPidReg.i32Q8_Ki = Q8(st_CustomerPara.Comp_f32Ski);
	st_CompCtrlPowerPidReg.i32Q16_Ki = Q16(st_CustomerPara.Comp_f32Powerki);
	st_CompCtrlPowerPidReg.i32Q8_Kd = Q8(0);
    st_CompCtrlPowerPidReg.i32Q8_OutMax = Q8(st_CustomerPara.Comp_u16SpdMax);
	st_CompCtrlPowerPidReg.i32Q8_OutMin = Q8(-st_CustomerPara.Comp_u16SpdMin);
	st_CompCtrlPowerPidReg.i32Q8_ErroPre = Q8(0);
	st_CompCtrlPowerPidReg.i32Q8_ErroNow = Q8(0);
	st_CompCtrlPowerPidReg.i32Q8_Pout = Q8(0);
	st_CompCtrlPowerPidReg.i32Q8_Iout = Q8(0);
	st_CompCtrlPowerPidReg.i32Q8_Out  = Q8(st_CustomerPara.Comp_u16SpdMin);
	st_CompCtrlPowerPidReg.i32Q8_Out_pre = Q8(0);


    st_SoftTimers.u32Timer2 = 0;
    st_CompPower.u8PowerOpenLoopFlag = 0;
    st_CompPower.u32Q16_CurryPower = 0;
    st_CompPower.u32Q16_PowerSum = 0;
    st_CompPower.u32CompCnt = 0;
    st_CompPower.u32CompPower = 0;
}
/****************************************************
 Function name: CompCtrl_InitCustomerPar
 description:
 input:         none
 output:            none
 ****************************************************/
static void CompCtrl_InitCustomerPar(INT16U u16SampleFreq)
{
    st_CompCustomerPara.i32Q8_Res     = Q8(st_CustomerPara.Comp_f32Res);
    st_CompCustomerPara.i32Q8_Ls      = Q8(st_CustomerPara.Comp_f32L);

    st_CompCustomerPara.i32Q8_Ke      = Q8(st_CustomerPara.Comp_f32Ke);

}

/****************************************************
 Function name: CompCtrl_Start
 description:
 input:         none
 output:            none
 ****************************************************/
void CompCtrl_Start(INT16U u16SampleFreq)
{    
    if(st_CompRunPar.u8SensorAdcStatus == SENSOR_RUNNING)
    {
        CompCtrl_InitPar(u16SampleFreq);
        CompCtrl_InitCustomerPar(u16SampleFreq);

        InitMcu_CompPwmEn();
        
        st_CompRunPar.u8Status = MOTOR_RUNNING;    
        st_CompRunPar.u8Runninglevel = START_LEVEL;
        st_CompIPara.u8Flag = 0;
    }
}
/****************************************************
 Function name: CompCtrl_Stop
 description:
 input:         none
 output:            none
 ****************************************************/
void CompCtrl_Stop(void)
{
    InitMcu_CompPwmDis();
    st_CompRunPar.u8Status = MOTOR_STOP;
    st_CompRunPar.i32TargetSpeedRpm = 0; 
    st_CompPower.u32TargetPower = 0;
    st_CompPower.u32TargetPowerDecimal = 0;
    st_CompRunPar.u8Runninglevel = 0;

    st_CompVPara.i32Q8_VOut = 0;
    st_CompIPara.i32Q8_SpeedIBase = 0;
    st_CompRunPar.i32Q22_TargetSpeedWmHz = 0;
    st_CompRunPar.i32Q8_TargetSpeedWmHz = 0;
    st_SoftTimers.u32Timer0 = 0;
    st_SoftTimers.u32Timer1 = 0;
    st_CompRunPar.u8MotorStallFlag = 0;
    st_CompRunPar.u8LimitIFlag = 0; 
	st_MotorWarnPara.u8ReduceCancelFlag = 0;
	st_MotorWarnPara.u8ReduceSpeedFlag = 0;
	st_MotorWarnPara.u32SpeedTimeCnt = 0;
}

void CompCtrl_ConfigPwm(void)
{
	INT16U u16Tmp1;

    if (st_CustomerPara.Comp_f32DeadTimeMicroSec < 1.5)   /*Motor0 dead time min limit unit: us*/
    {
        st_CustomerPara.Comp_f32DeadTimeMicroSec = 1.5;
    }
	u16Tmp1 = (INT16U)(gstClkPara.FreqOfAPB1Clk_Hz/ st_CustomerPara.Comp_u16CarrierFreq);
	st_CompCtrlPwm.i16Cycle = (u16Tmp1)>>1;	
    
    st_CompCtrlPwm.i16DutyMax = Q0(st_CompCtrlPwm.i16Cycle - 1);
    
    st_CompCtrlPwm.i16DeadTime = Q0(st_CustomerPara.Comp_f32DeadTimeMicroSec* (gstClkPara.FreqOfAPB1Clk_Hz / 1000000));
    
    FM0P_MFT0_FRT->TCCP0 = st_CompCtrlPwm.i16Cycle;
    FM0P_MFT0_WFG->WFTA10 = st_CompCtrlPwm.i16DeadTime;
    FM0P_MFT0_WFG->WFTB10 = st_CompCtrlPwm.i16DeadTime;
    FM0P_MFT0_WFG->WFTA32 = st_CompCtrlPwm.i16DeadTime;
    FM0P_MFT0_WFG->WFTB32 = st_CompCtrlPwm.i16DeadTime;

    //scan trigger point
    FM0P_MFT0_ADCMP->ACMP2 = 0;    

}
/****************************************************
 Function name:     Sensor_Parameter_Init
 description:
 input:                 none
 output:            none
 ****************************************************/
void Adc_InitSensorPar(uint16_t u16SampleFreq)
{
    st_AdcSample.i32Q14_Vbusk = Q14(st_CustomerPara.Comp_u16VAmplifierFactor * ADC_VOLT_REF / ADC_VALUE_MAX);
    st_AdcSample.i32ISampleRef = Q0(st_CustomerPara.Comp_f32ISampleRef * ADC_VALUE_MAX/ADC_VOLT_REF);
    st_AdcSample.i32Q14_CompCurrentFactor
            = Q24(ADC_VOLT_REF * ADC_R1/ (st_CustomerPara.Comp_f32ISampleResistor * ADC_R2 * ADC_VALUE_MAX));
    st_AdcSample.i32Q14_VSPDFactor = Q14(VOLTAGE_TO_SPEED * ADC_VOLT_REF / ADC_VALUE_MAX);
    st_AdcSample.i32Q14_VSPDPowerFactor = Q14(VOLTAGE_TO_POWER * ADC_VOLT_REF / ADC_VALUE_MAX);

    st_AdcSample.u32CompOffsetCheckDelay = (INT32U) (u16SampleFreq );
    st_AdcSample.u32SampleNum = 0;
}
/****************************************************
 Function name:     InitHallDet
 description:
 input:                 none
 output:            none
 ****************************************************/
void InitHallDet(stc_hall_detect_t *pstcVal)
{
    pstcVal->OvCnt = 0;
    pstcVal->u32_CycleUpperLimt = (INT32U)((gstClkPara.FreqOfAPB1Clk_Hz >> 4)/1); // 40Mhz/16 /1Hz
    pstcVal->u32_Coff = (INT32U)(gstClkPara.FreqOfAPB1Clk_Hz/16);   //40Mhz/16
    pstcVal->OvCntMax = (((gstClkPara.FreqOfAPB1Clk_Hz/16)/(2*st_CustomerPara.EndFreqMin*st_CustomerPara.Comp_u32PolePairs)) >> 16) + 1;
    //pstcVal->i32_SpdCoff = Q12(st_CustomerPara.Comp_u16SpdMax - st_CustomerPara.Comp_u16SpdMin)/Q5(EffectiveFreqUpper - EffectiveFreqLower);
}

/****************************************************
 Function name: CompCtrl_Init
 description:
 input:         none
 output:            none
 ****************************************************/
void CompCtrl_Init(uint16_t u16SampleFreq)
{    
    //
    // init PWM register
    //
    CompCtrl_ConfigPwm();
    InitMcu_CompPwm();
    Adc_InitSensorPar(u16SampleFreq);

   // CompCtrl_InitProtector(u16SampleFreq);

    InitHallDet(&st_HallDetect);
}


/****************************************************
 Function name:     CompCurrentSense
 description:
 input:                 none
 output:            none
 ****************************************************/
void Adc_CompCurrentSense(void)
{
    INT32S i32AdcUValue = 0;
    INT32S i32AdcVValue = 0;
   
    st_CompRunPar.i32Q8_ISensedPre = st_CompRunPar.i32Q8_ISensed;
    i32AdcUValue = Adc_u16RsltOfAdc[COMP_ADC_CH_IU];
    i32AdcVValue = Adc_u16RsltOfAdc[COMP_ADC_CH_IV];

 
    if(st_CompRunPar.u8HallPolarity == 1)
    {   
		st_CompRunPar.i32Q8_ISensed = ((st_AdcSample.i32IuSampleRef - i32AdcUValue  ) * st_AdcSample.i32Q14_CompCurrentFactor)>>16;
    }
    else
    { 
		st_CompRunPar.i32Q8_ISensed = (( st_AdcSample.i32IvSampleRef -i32AdcVValue ) * st_AdcSample.i32Q14_CompCurrentFactor)>>16; 
    }
    //Filter_OneOderLPF(st_CompRunPar.i32Q8_ISensed,&st_CompIPara.i32Q8_ISensedFilter,&st_ISensedlpf);
	st_CompIPara.i32Q8_ISensedFilter = st_CompRunPar.i32Q8_ISensed;

}
#if 1
/****************************************************
 Function name: CompCtrl_CloseLoop
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_VoltageCalculate(void)
{
    INT32S i32Q16_UTemp = 0;
    INT32S i32Q16_UTemp1 = 0;
    INT32S i32Q16_ETemp = 0;

    st_CompVPara.i32Q8_VBase_pre = st_CompVPara.i32Q8_VBase; 

    st_CompVPara.i32Q16_UTemp = st_CompIPara.i32Q8_IRef * st_CompCustomerPara.i32Q8_Res;
    
    st_CompVPara.i32Q16_UTemp1 = (st_CompCustomerPara.i32Q8_Ls * st_CustomerPara.Comp_u16CarrierFreq * (st_CompRunPar.i32Q8_ISensed - st_CompRunPar.i32Q8_ISensedPre))/1000;
    
    st_CompVPara.i32Q16_ETemp = ((st_CompCustomerPara.i32Q8_Ke * (INT32U)st_CompRunPar.i32CurrentSpeedRpm)/1000)<<8;

    //st_CompVPara.i32Q8_VBase = (st_CompVPara.i32Q16_UTemp + st_CompVPara.i32Q16_UTemp1 + st_CompVPara.i32Q16_ETemp)>>8;
    st_CompVPara.i32Q8_VBase = (st_CompVPara.i32Q16_UTemp  + abs(st_CompVPara.i32Q16_UTemp1) + st_CompVPara.i32Q16_ETemp)>>8;
    //st_CompVPara.i32Q8_VOutPeak = st_CompVPara.i32Q8_VBase + st_CompIPara.i32Q8_IPidReg;
    //st_CompVPara.i32Q8_VOutPeak = st_CompVPara.i32Q8_VBase ;

    //if(st_CompVPara.i32Q8_VOutPeak > st_CompRunPar.i32Q8_Vbus)
    {
      //  st_CompVPara.i32Q8_VOutPeak = st_CompRunPar.i32Q8_Vbus;
    }
}
#endif
INT32U g_PowerSum = 0;
INT32U g_AntiPowerSum = 0;
INT32U g_u32CompCntSum = 0;
INT8U g_Cnt = 0;
INT32U g_Power = 0;
INT32U g_Q16Power = 0;
INT32U g_Q16PowerFilter = 0;
/****************************************************
 Function name: CompCtrl_PowerCalculate
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_PowerCalculate(void)
{
	INT32U u32CompCntSum = 0;
	INT32U u32AntiPowerPara = 0;
	
    if(st_CompRunAngle.u32AngleCount == 0)
    {
        u32CompCntSum = st_CompPower.u32CompCnt + st_CompPower.u32AntiCompCnt;

        if(u32CompCntSum != 0)
        {
            #if 0
        	if(st_CompPower.u32CompPower > 32)
        	{
        		u32AntiPowerPara = 256;
        	}
        	else if(st_CompPower.u32CompPower > 19)
        	{
        		u32AntiPowerPara = 1024;
        	}
        	else if(st_CompPower.u32CompPower > 13)
        	{
        		u32AntiPowerPara = 512;
        	}
        	else
        	{
        		u32AntiPowerPara = 332;
        	}
        	#endif
        	st_CompPower.u32Q16_CompPower = ((st_CompPower.u32Q16_PowerSum - ((st_CompPower.u32Q16_AntiPowerSum*u32AntiPowerPara)/256))/u32CompCntSum);        	
        	Filter_OneOderLPF(st_CompPower.u32Q16_CompPower,&st_CompPower.u32Q16_CompPowerFilter,&st_Powerdlpf);
        	if(st_CompPower.u32Q16_CompPowerFilter > Q16(st_CustomerPara.Comp_PowerMax))
        	{
        		st_CompPower.u32Q16_CompPowerFilter = Q16(st_CustomerPara.Comp_PowerMax);
        	}
        	st_CompPower.u32CompPower = st_CompPower.u32Q16_CompPowerFilter>>16;

        	
        }       
        st_CompPower.u32Q16_AntiCompPower = st_CompPower.u32Q16_AntiPowerSum/u32CompCntSum;
		st_CompPower.u32AntiCompPower = st_CompPower.u32Q16_AntiCompPower>>16;
		#if 0
        g_Cnt++;
        g_PowerSum += st_CompPower.u32Q16_PowerSum;
        g_AntiPowerSum += st_CompPower.u32Q16_AntiPowerSum;
        g_u32CompCntSum += u32CompCntSum;
        if(g_Cnt >= 4)
        {
        	g_Q16Power = (g_PowerSum - g_AntiPowerSum)/g_u32CompCntSum;
        	Filter_OneOderLPF(g_Q16Power,&g_Q16PowerFilter,&st_Powerdlpf);
        	g_Power = g_Q16PowerFilter>>16;
        	g_Cnt = 0;
        	g_PowerSum = 0;
        	g_AntiPowerSum = 0;
        	g_u32CompCntSum = 0;
        }
        #endif
        st_CompPower.u32Q16_CurryPower = 0;
        st_CompPower.u32Q16_PowerSum = 0;
        st_CompPower.u32CompCnt = 0;

        st_CompPower.u32Q16_AntiPowerSum = 0;
        st_CompPower.u32AntiCompCnt = 0;
        if(st_CompPower.u32Q16_CompPowerFilter > 0)
        {
            st_SoftTimers.u32Timer2++;
        }
        //st_SoftTimers.u32Timer2 %= 4;        
      
    }
    else
    {	
        st_CompPower.u32Q16_CurryPower = (INT32U)(st_CompVPara.i32Q8_VOut * abs(st_CompIPara.i32Q8_ISensedFilter));
		
        if(st_CompIPara.i32Q8_ISensedFilter >= 0)
        {
            st_CompPower.u32Q16_PowerSum += st_CompPower.u32Q16_CurryPower;
            st_CompPower.u32CompCnt++;
        }
        else 
        {
            st_CompPower.u32Q16_AntiPowerSum += st_CompPower.u32Q16_CurryPower;
            st_CompPower.u32AntiCompCnt++;
        }        
    }
}

/****************************************************
 Function name: CompCtrl_PowerReg
 description:
 input:         none
 output:            none
 ****************************************************/
static void CompCtrl_PowerReg(void)
{    
    INT32S i32Q8_CompPower = 0;
    
    if(st_CompPower.u32TargetPower > st_CustomerPara.Comp_PowerMax)
    {
        st_CompPower.u32TargetPower = st_CustomerPara.Comp_PowerMax;
    }
    else if((st_CompPower.u32TargetPower != 0) && (st_CompPower.u32TargetPower
            < st_CustomerPara.Comp_PowerMin))
    {
        st_CompPower.u32TargetPower = st_CustomerPara.Comp_PowerMin;
    }

    st_CompPower.i32Q8_PidTargetPower = (st_CompPower.u32TargetPower<<8) + st_CompPower.u32TargetPowerDecimal;
    //st_CompPower.i32Q8_PidTargetPower = (st_CompPower.u32TargetPower<<8);
    i32Q8_CompPower  = st_CompPower.u32Q16_CompPowerFilter>>8; 	
	//i32Q8_CompPower = g_Q16PowerFilter>>8;
    st_CompPower.i32Q8_PowerPidReg = Q8_to_Q8_PID(st_CompPower.i32Q8_PidTargetPower,i32Q8_CompPower,&st_CompCtrlPowerPidReg);

    if(st_CompPower.i32Q8_PowerPidReg < 0)
    {	
    	st_CompPower.i32Q8_PowerPidReg = 0;
        st_CompRunPar.i32TargetSpeedRpm = st_CustomerPara.Comp_u16SpdMin;        
    }
    else
    {
        st_CompRunPar.i32TargetSpeedRpm = st_CompPower.i32Q8_PowerPidReg>>8;
    }
}

/****************************************************
 Function name: CompCtrl_SpdReg
 description:
 input:         none
 output:            none
 ****************************************************/
static void CompCtrl_SpdReg(void)
{
    INT32S Q8_TargetSpeed_Hz_temp;

    if (st_CompRunPar.i32TargetSpeedRpm > st_CustomerPara.Comp_u16SpdMax)
    {
        st_CompRunPar.i32TargetSpeedRpm = st_CustomerPara.Comp_u16SpdMax;
    }
    else if ((st_CompRunPar.i32TargetSpeedRpm != 0) && st_CompRunPar.i32TargetSpeedRpm
            < st_CustomerPara.Comp_u16SpdMin)
    {
        st_CompRunPar.i32TargetSpeedRpm = st_CustomerPara.Comp_u16SpdMin;
    }
    Q8_TargetSpeed_Hz_temp = (st_CompRunPar.i32TargetSpeedRpm<<8)/60;

    if ((Q8_TargetSpeed_Hz_temp - st_CompRunPar.i32Q8_TargetSpeedWmHz) > (st_CompRunPar.i32Q22_TargetWmIncTs >> 15))
    {
        st_CompRunPar.i32Q22_TargetSpeedWmHz += st_CompRunPar.i32Q22_TargetWmIncTs;

        st_CompRunPar.i32Q8_TargetSpeedWmHz = st_CompRunPar.i32Q22_TargetSpeedWmHz >> 14;
    }
    else if ((Q8_TargetSpeed_Hz_temp - st_CompRunPar.i32Q8_TargetSpeedWmHz) < -(st_CompRunPar.i32Q22_TargetWmDecTs
            >> 15))
    {
        st_CompRunPar.i32Q22_TargetSpeedWmHz -= st_CompRunPar.i32Q22_TargetWmDecTs;
        st_CompRunPar.i32Q8_TargetSpeedWmHz = st_CompRunPar.i32Q22_TargetSpeedWmHz >> 14;
    }


    if(st_CompIPara.u8Flag == 0)     
    {
        st_CompIPara.i32Q8_SpeedIBase = st_CompVPara.i32Q8_VOut;

        st_CompCtrlSpeedPidReg.i32Q8_Out = st_CompIPara.i32Q8_SpeedIBase ;
        
        st_CompIPara.u8Flag = 1;        
    }

    
    st_CompIPara.i32Q8_SpeedPidReg = Q8_to_Q8_PID(st_CompRunPar.i32Q8_TargetSpeedWmHz,st_CompRunPar.i32Q8_CurrentSpeedWmHz,&st_CompCtrlSpeedPidReg);
   
}

/****************************************************
 Function name: CompCtrl_StartStage
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_PwmSet(void)
{
    st_CompCtrlPwm.i16Duty = (st_CompVPara.i32Q8_VOut * 100) /st_CompRunPar.i32Q8_Vbus;
    i16Duty = (st_CompIPara.i32Q8_SpeedPidReg * 100) /st_CompRunPar.i32Q8_Vbus;
    if(st_CompRunAngle.i32Q12_CompSinValue > i32Q12_CompSinValue)
    {
    	i32Q12_CompSinValue = st_CompRunAngle.i32Q12_CompSinValue ;
    }
    if(st_CompCtrlPwm.i16Duty > i16DutMax)
    {	
    	i16DutMax = st_CompCtrlPwm.i16Duty;
    }
    st_CompCtrlPwm.i16DutyCount = (st_CompCtrlPwm.i16Cycle * st_CompCtrlPwm.i16Duty)/100;
  
    
    if(st_CompRunPar.u8HallPolarity == 0)   
    {
    	 #if 1
        st_CompCtrlPwm.i16AonUp = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount - st_CompCtrlPwm.i16DeadTime)/2;
        st_CompCtrlPwm.i16AonDown = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount - st_CompCtrlPwm.i16DeadTime)/2;
        st_CompCtrlPwm.i16BonUp = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount + st_CompCtrlPwm.i16DeadTime)/2  ;
        st_CompCtrlPwm.i16BonDown = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount + st_CompCtrlPwm.i16DeadTime)/2  ;
        #endif   
        #if 0
        st_CompCtrlPwm.i16AonUp = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount)/2;
        st_CompCtrlPwm.i16AonDown = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount)/2;
        st_CompCtrlPwm.i16BonUp = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount)/2 ;
        st_CompCtrlPwm.i16BonDown = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount)/2 ;
#endif
        //FM0P_MFT0_ADCMP->ACMP2 = st_CompCtrlPwm.i16AonUp + 5;
    }
    else
    {    
	    #if 1
        st_CompCtrlPwm.i16AonUp = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount + st_CompCtrlPwm.i16DeadTime)/2 ;
        st_CompCtrlPwm.i16AonDown = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount + st_CompCtrlPwm.i16DeadTime)/2;
        st_CompCtrlPwm.i16BonUp = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount - st_CompCtrlPwm.i16DeadTime)/2;
        st_CompCtrlPwm.i16BonDown = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount - st_CompCtrlPwm.i16DeadTime)/2;
       #endif
        #if 0
        st_CompCtrlPwm.i16AonUp = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount)/2 ;
        st_CompCtrlPwm.i16AonDown = (st_CompCtrlPwm.i16Cycle + st_CompCtrlPwm.i16DutyCount)/2;
        st_CompCtrlPwm.i16BonUp = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount)/2;
        st_CompCtrlPwm.i16BonDown = (st_CompCtrlPwm.i16Cycle - st_CompCtrlPwm.i16DutyCount)/2;
#endif
        //FM0P_MFT0_ADCMP->ACMP2 = st_CompCtrlPwm.i16BonUp + 5;
    }
	//st_CompCtrlPwm.i16AonUp = 0;
	
	if(st_CompCtrlPwm.i16AonUp > st_CompCtrlPwm.i16DutyMax)
	{
		st_CompCtrlPwm.i16AonUp = st_CompCtrlPwm.i16DutyMax;
	}
	else if(st_CompCtrlPwm.i16AonUp <= st_CompCtrlPwm.i16DeadTime)
	{
		st_CompCtrlPwm.i16AonUp = st_CompCtrlPwm.i16DeadTime;
	}
	
	if(st_CompCtrlPwm.i16AonDown > st_CompCtrlPwm.i16DutyMax)
	{
		st_CompCtrlPwm.i16AonDown = st_CompCtrlPwm.i16DutyMax;
	}
	else if(st_CompCtrlPwm.i16AonDown <= st_CompCtrlPwm.i16DeadTime)
	{
		st_CompCtrlPwm.i16AonDown = st_CompCtrlPwm.i16DeadTime;
	}
	if(st_CompCtrlPwm.i16BonUp > st_CompCtrlPwm.i16DutyMax)
	{
		st_CompCtrlPwm.i16BonUp = st_CompCtrlPwm.i16DutyMax;
	}
	else if(st_CompCtrlPwm.i16BonUp <= st_CompCtrlPwm.i16DeadTime)
	{
		st_CompCtrlPwm.i16BonUp = st_CompCtrlPwm.i16DeadTime;
	}
	if(st_CompCtrlPwm.i16BonDown > st_CompCtrlPwm.i16DutyMax)
	{
		st_CompCtrlPwm.i16BonDown = st_CompCtrlPwm.i16DutyMax;
	}
	else if(st_CompCtrlPwm.i16BonDown <= st_CompCtrlPwm.i16DeadTime)
	{
		st_CompCtrlPwm.i16BonDown = st_CompCtrlPwm.i16DeadTime;
	}
    FM0P_MFT0_OCU->OCCP0 = st_CompCtrlPwm.i16AonUp;//up
    FM0P_MFT0_OCU->OCCP1 = st_CompCtrlPwm.i16AonDown;//down
    FM0P_MFT0_OCU->OCCP2 = st_CompCtrlPwm.i16BonUp;
    FM0P_MFT0_OCU->OCCP3 = st_CompCtrlPwm.i16BonDown;

    
}

INT32U OverCnt = 0;
INT32U LimitCnt = 0;
INT32U OverVolCnt = 0;
INT32U UnderVolCnt = 0;
INT32U UnderLimitVolCnt = 0;

/****************************************************
Function name:	Motor0_Protect
description:    
input:			none
output:			none
****************************************************/
void CompCtrl_Protect(void)
{ 
    INT32S OverSpeed = 0;
    INT32S UnderSpeed = 0;
    
    if(st_CompRunPar.u8Status == MOTOR_RUNNING)
    {
        /*过流故障*/
        if(abs(st_CompRunPar.i32Q8_ISensed) > abs(st_CustomerPara.Comp_i32Q8CurrentMax))    
        {
    		OverCnt++;
    		if(OverCnt > 10)
    		{
    			OverCnt = 0;
		        st_CompRunPar.u32ErroType = SW_OVER_CURRENT;        
    		}
        }
        if(abs(st_CompRunPar.i32Q8_ISensed) > abs(st_CustomerPara.Comp_i32Q8CurrentLock))    
        {
            st_CompRunPar.u8LimitIFlag = 1;        
        }
        
        if(abs(st_CompRunPar.i32Q8_ISensed) > abs(st_CustomerPara.Comp_i32Q8CurrentLimit))    
        {
    		LimitCnt++;
    		if(LimitCnt > 10)
    		{
    		    LimitCnt = 0;
                st_MotorWarnPara.u8ReduceSpeedFlag = 1;
                st_MotorWarnPara.u32ReduceTimeCnt = 0;
                st_MotorWarnPara.u8ReduceCancelFlag = 1;
            }
        }

        
        /*过压，欠压故障*/
        if(st_CompRunPar.i32Q8_Vbus < st_CustomerPara.Comp_i32Q8VbusMin)
        {
    		UnderVolCnt++;
    		if(UnderVolCnt > 20)
    		{
    			UnderVolCnt = 0;
	            st_CompRunPar.u32ErroType = UNDER_VOLTAGE;
	            st_MotorWarnPara.u8UnderVoltageCnt++;
			}
        }

        if(st_CompRunPar.i32Q8_Vbus > st_CustomerPara.Comp_i32Q8VbusMax)
        {
    		OverVolCnt++;
    		if(OverVolCnt > 20)
    		{
    			OverVolCnt = 0;
                st_CompRunPar.u32ErroType = OVER_VOLTAGE;
	            st_MotorWarnPara.u8OverVoltageCnt++;
			}

        }

        /*欠压降频保护*/
        if(st_CompRunPar.i32Q8_Vbus < st_CustomerPara.Comp_i32Q8VbusLimit)
        {
            UnderLimitVolCnt++;
            if(UnderLimitVolCnt > 20)
            {
                UnderLimitVolCnt = 0;                
                st_MotorWarnPara.u8LimitVoltageFlag = 1;
                st_MotorWarnPara.u8ReduceSpeedFlag = 1;
                st_MotorWarnPara.u32ReduceTimeCnt = 0;
                st_MotorWarnPara.u8ReduceCancelFlag = 1;
            }
        }

        
        if(st_MotorWarnPara.u8LimitVoltageFlag == 1)
        {
            if(st_CompRunPar.i32Q8_Vbus < st_CustomerPara.Comp_i32Q8VbusLimitRec)
            {
                st_MotorWarnPara.u8ReduceSpeedFlag = 1;
                st_MotorWarnPara.u32ReduceTimeCnt = 0;
                st_MotorWarnPara.u8ReduceCancelFlag = 1;
            }
            else
            {
                /*欠压降频保护取消*/
                st_MotorWarnPara.u8LimitVoltageFlag = 0;
            }
        }
        
        /*低速，超速故障*/
		#if 1
    	if(st_CompRunPar.u8Runninglevel == CLOSE_LOOP)
    	{
    	        OverSpeed = st_CustomerPara.Comp_u16SpdMax + st_CustomerPara.Comp_u16SpdMax/10;
    	        UnderSpeed = st_CustomerPara.Comp_u16SpdMin - st_CustomerPara.Comp_u16SpdMin/10;

    	        if((st_CompRunPar.i32CurrentSpeedRpm > OverSpeed)||(st_CompRunPar.i32CurrentSpeedRpm < UnderSpeed))
    	        {
    	            st_MotorWarnPara.u32SpeedTimeCnt++;
    	        }
    	        else
    	        {
    	            st_MotorWarnPara.u32SpeedTimeCnt = 0;
    	        }
    	        if(st_MotorWarnPara.u32SpeedTimeCnt > 96000) //持续2s都有超速或低速则为故障
    	        {
    	        	st_MotorWarnPara.u32SpeedTimeCnt = 0;
    	            st_CompRunPar.u32ErroType = SPEED_ERROR;
    	            st_MotorWarnPara.u8SpeedErrorCnt++;
    	        }
    	}
		#endif
        
        if(st_CompRunPar.u32ErroType != 0)
        {
            CompCtrl_Stop();
        }
     }
     else
     {
        /*过，欠压出现3次或超速出现3次或堵转出现4次则不再重启*/
        if((st_MotorWarnPara.u8UnderVoltageCnt >= 3)||(st_MotorWarnPara.u8OverVoltageCnt >= 3)\
        ||(st_MotorWarnPara.u8SpeedErrorCnt >= 3)||(st_MotorWarnPara.u8MotorLockCnt >= 4))
        {
            st_MotorWarnPara.u8RestartFlag = 0;
            return;
        }
        
        /*过压，欠压保护，过10s后重启*/
        if((st_CompRunPar.u32ErroType == UNDER_VOLTAGE)||(st_CompRunPar.u32ErroType == OVER_VOLTAGE))
        {
            if((st_CompRunPar.i32Q8_Vbus <= (st_CustomerPara.Comp_i32Q8VbusMax - Q8(10)))&&(st_CompRunPar.i32Q8_Vbus >= (st_CustomerPara.Comp_i32Q8VbusMin + Q8(10))))
            {      
                //st_CompRunPar.u32ErroType = 0;	
                if(st_MotorWarnPara.u8RestartFlag == 0)
            	{
	                st_MotorWarnPara.u32RestartTimeCnt = RESTART_TIME - 10; //过压，欠压保护10s后重启    
            	}
                st_MotorWarnPara.u8RestartFlag = 1;		
                OverVolCnt = 0;
                UnderVolCnt = 0;
            }
        }

        
        /*超速保护，过60s后重启*/
        if(st_CompRunPar.u32ErroType == SPEED_ERROR)
        {            

           //st_CompRunPar.u32ErroType = 0;	
              if(st_MotorWarnPara.u8RestartFlag == 0)
        	{
                st_MotorWarnPara.u32RestartTimeCnt = 0; //过压，欠压保护10s后重启    
        	}
            st_MotorWarnPara.u8RestartFlag = 1;            
        }

        /*堵转保护*/
        if(st_CompRunPar.u32ErroType == MOTOR_LOCK)
        {

           //st_CompRunPar.u32ErroType = 0;	
            if(st_MotorWarnPara.u8RestartFlag == 0)
            {
                st_MotorWarnPara.u32RestartTimeCnt = RESTART_TIME - 20; //过压，欠压保护10s后重启    
            }
            st_MotorWarnPara.u8RestartFlag = 1;           
        }
     }
}

/****************************************************
 Function name: CompCtrl_StartStage
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_StartStage(void)
{
    INT32U StartFirstTime = 0;

    StartFirstTime = 190*st_CustomerPara.Comp_u16CarrierFreq/1000;   //190ms

    st_SoftTimers.u32Timer0++;
    if(st_SoftTimers.u32Timer0 < StartFirstTime)     //  Q2,Q4导通，其他关闭
    {
        st_CompCtrlPwm.i16AonUp = st_CompCtrlPwm.i16Cycle;
        st_CompCtrlPwm.i16AonDown = st_CompCtrlPwm.i16Cycle;
        st_CompCtrlPwm.i16BonUp = st_CompCtrlPwm.i16Cycle;
        st_CompCtrlPwm.i16BonDown = st_CompCtrlPwm.i16Cycle;
    }
    else if(st_SoftTimers.u32Timer0 < (StartFirstTime + 200)) 
    {
        InitMcu_CompPwmDis();
    } 
    else
    {
        InitMcu_CompPwmEn();
        st_CompRunPar.u8HallPolarity = HALL_POLARITY;
        st_CompRunPar.u8Runninglevel = OPEN_LOOP;
    }    
    
    FM0P_MFT0_OCU->OCCP0 = st_CompCtrlPwm.i16AonUp;//up
    FM0P_MFT0_OCU->OCCP1 = st_CompCtrlPwm.i16AonDown;//down
    FM0P_MFT0_OCU->OCCP2 = st_CompCtrlPwm.i16BonUp;
    FM0P_MFT0_OCU->OCCP3 = st_CompCtrlPwm.i16BonDown;
}

/****************************************************
 Function name: CompCtrl_OpenLoop
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_OpenLoop(void)
{    
    
    if(((st_CompRunPar.i32CurrentSpeedRpm > (st_CustomerPara.Comp_u16StartFreq * 60))&&(st_CompVPara.i32Q8_VOut > Q8(40)))||
    (st_CompVPara.i32Q8_VOut > Q8(30)))
    {        
        st_CompPower.u8PowerOpenLoopFlag = 1;
        
        st_CompRunPar.i32Q22_TargetSpeedWmHz = Q22(st_CompRunPar.i32CurrentSpeedRpm)/60;
        st_CompRunPar.i32Q8_TargetSpeedWmHz = st_CompRunPar.i32Q22_TargetSpeedWmHz >> 14;

        st_CompRunAngle.u32Q12_CompAngle = ((1024 * ((INT32U)st_HallDetect.i32Q5_Freq) *st_CompRunAngle.u32AngleCount)/st_CustomerPara.Comp_u16CarrierFreq)<<7;
        st_CompRunAngle.u32Q12_CompAngle = st_CompRunAngle.u32Q12_CompAngle>>12;
        st_CompRunAngle.i32Q12_CompSinValue = Q12_Sin(st_CompRunAngle.u32Q12_CompAngle);
        if(st_HallDetect.i32Q5_Freq != 0)
        {
            st_CompRunAngle.u32CycleCount = (st_CustomerPara.Comp_u16CarrierFreq<<5)/((INT32U)st_HallDetect.i32Q5_Freq); 
        }
        
        if(st_CompRunAngle.u32AngleCount < st_CompRunAngle.u32CycleCount)
        {
            st_CompRunAngle.u32AngleCount++;
        }
        else
        {
            st_CompRunAngle.u32AngleCount = 0;
        }
        
        if(st_TimerPara.F_OpenLoop == 1)
        {
            st_TimerPara.F_OpenLoop = 0;
            st_CompRunPar.u8Runninglevel = CLOSE_LOOP;
        }
        
    }
    else
    {
        st_CompVPara.i32Q8_VOut += 5;
        st_SoftTimers.u32Timer2 = 0;
        //st_CompVPara.i32Q8_VOut = Q8(50);
    }
    
    CompCtrl_PwmSet();
}


INT32U u32VOut;

/****************************************************
 Function name: CompCtrl_CloseLoop
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_CloseLoop(void)
{  
    if (st_CompRunPar.u8Status == MOTOR_RUNNING)
    {         
        while (st_AdcSample.u8CompCompleteFlag != 1);
        st_AdcSample.u8CompCompleteFlag = 0;
       
        CompCtrl_SpdReg();  
   
        st_CompRunAngle.u32Q12_CompAngle = ((1024 * ((INT32U)st_HallDetect.i32Q5_Freq) *st_CompRunAngle.u32AngleCount)/st_CustomerPara.Comp_u16CarrierFreq)<<7;
        st_CompRunAngle.u32Q12_CompAngle = st_CompRunAngle.u32Q12_CompAngle>>12;
        st_CompRunAngle.i32Q12_CompSinValue = Q12_Sin(st_CompRunAngle.u32Q12_CompAngle);
        if(st_HallDetect.i32Q5_Freq != 0)
        {
            st_CompRunAngle.u32CycleCount = (st_CustomerPara.Comp_u16CarrierFreq<<5)/((INT32U)st_HallDetect.i32Q5_Freq); 
        }        
       
        
        if(st_CompRunAngle.u32AngleCount < st_CompRunAngle.u32CycleCount)
        {
            st_CompRunAngle.u32AngleCount++;
        }
        else
        {
            st_CompRunAngle.u32AngleCount = 0;
        }

        //u32VOut = (st_CompVPara.i32Q8_VOutPeak * st_CompRunAngle.i32Q12_CompSinValue)>>12;
        if(st_CompIPara.i32Q8_SpeedPidReg > st_CompRunPar.i32Q8_Vbus)
        {
            st_CompIPara.i32Q8_SpeedPidReg = st_CompRunPar.i32Q8_Vbus;
        }
        else if(st_CompIPara.i32Q8_SpeedPidReg < 0)
        {
            st_CompIPara.i32Q8_SpeedPidReg = 0;
        }
		//st_CompIPara.i32Q8_SpeedPidReg = Q8(150);
        u32VOut = ((INT32U)st_CompIPara.i32Q8_SpeedPidReg * (INT32U)st_CompRunAngle.i32Q12_CompSinValue)>>12;
        st_CompVPara.i32Q8_VOut = u32VOut;
        

        CompCtrl_PwmSet();
    }

}
/****************************************************
 Function name: CompCtrl_Process
 description:
 input:         none
 output:        none
 ****************************************************/ 
void CompCtrl_Process(void)
{    
    if(st_CompRunPar.u8Status == MOTOR_RUNNING)
    {
        Adc_CompCurrentSense();
         
    }
    CompCtrl_Protect();

    if(st_CompRunPar.u8Status != MOTOR_RUNNING)
    {
        return;
    }

    if(st_CompRunPar.u8MotorStallFlag == 1)
    {
	 //   st_CompRunPar.i32TargetSpeedRpm = 600;
    	 st_HallDetect.i32Q5_Freq = Q5(30);
	 
        if(st_SoftTimers.u32Timer1 == 1)
        {
            st_CompRunAngle.u32AngleCount = 0;
            if(st_CompRunPar.u8HallPolarity == 1)
            {
                st_CompRunPar.u8HallPolarity = 0;
            }
            else
            {
                st_CompRunPar.u8HallPolarity = 1;
            }
        }
        else if(st_SoftTimers.u32Timer1 >= 200) //堵转后按600rpm速度来变换hall
        {
            st_SoftTimers.u32Timer1 = 0;
        }

	st_SoftTimers.u32Timer1++;
	
    
    }
    else
    {
        if(HALL_POLARITY == 1)
        {
            st_CompRunPar.u8HallPolarity = 1;
            
        }
        else
        {
            st_CompRunPar.u8HallPolarity = 0;
            
        }
		CompCtrl_PowerCalculate();
    }
    
    if(st_CompRunPar.u8Runninglevel == START_LEVEL)
    {
        CompCtrl_StartStage();
    }
    
    if(st_CompRunPar.u8Runninglevel == OPEN_LOOP)
    {
        CompCtrl_OpenLoop();
    }

    if(st_CompRunPar.u8Runninglevel == CLOSE_LOOP)
    {
        CompCtrl_CloseLoop();
    }


    if((st_SoftTimers.u32Timer2 == 0x02)&&(st_CompPower.u8PowerOpenLoopFlag == 1)&&(st_CompRunPar.u8MotorStallFlag == 0))
    {
        st_SoftTimers.u32Timer2 = 0;
        
        if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
        {
            CompCtrl_PowerReg();
        }        
        
    }

}


