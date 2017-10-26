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
/** \file Isr.c
 **
 ** Add description here...
 **
 ** History:
 **   - 2014-09-16  0.1.0  Michael.Yang  First version 
 *****************************************************************************/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "Isr.h"
#include "s6e1a1.h"
#include "base_types.h"
#include "CompressorCtrl.h"
#include "Uart.h"
#include "InitMcu.h"
#include "Eeprom.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
#define ADC_CH_AMOUNT 8
#define SYSTEM_TIME_LIMIT_4MS  1 //base timer:X*4ms
#define SYSTEM_TIME_LIMIT      SYSTEM_TIME_LIMIT_4MS //Select System Tick Interval

volatile INT16U Adc_u16RsltOfAdc[ADC_CH_AMOUNT];

Timer_Para st_TimerPara;
Board_Temp_para st_BoardTemperature;

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


INT8U  g_on = 0;
INT8U  g_Laston = 2;


void SystemTimeProcess(void)
{
	if(++st_TimerPara.R8ms>=2)               //ms->8ms
	{
		st_TimerPara.R8ms=0;
		st_TimerPara.F_8Ms=1;		
		
	}  
	if(++st_TimerPara.R20ms>=5)
    {
		st_TimerPara.R20ms=0;
		st_TimerPara.F_20Ms=1;                
    }

	if(++st_TimerPara.R100ms>=25)
	{
		st_TimerPara.R100ms=0;
		st_TimerPara.F_100Ms=1;
	}
    
    if(++st_TimerPara.R248ms >= 62)
    {
        st_TimerPara.R248ms = 0;
        st_TimerPara.F_248Ms = 1;
    }

    g_WaitTime++;

    if(st_CompRunPar.u8Runninglevel == OPEN_LOOP)
    //if(st_CompRunPar.u8Runninglevel == CLOSE_LOOP)
    {
    	if(++st_TimerPara.ROpenLoop >= 250)
    	{
    		st_TimerPara.ROpenLoop = 0;
    		st_TimerPara.F_OpenLoop = 1;		
    	} 
    }
    
	if(++st_TimerPara.R1s >= 250)
	{
		st_TimerPara.R1s = 0;
		st_TimerPara.F_1S = 1;		
	} 

	if(++st_TimerPara.R3s >= 250)
	{
		st_TimerPara.R3s = 0;
		st_TimerPara.F_3S = 1;		
	}   

	if(++st_TimerPara.R10s >= 1000)
	{
		st_TimerPara.R10s = 0;
		st_TimerPara.F_10S = 1;		
	}   
	if(++st_TimerPara.R100s >= 25000)
	{
		st_TimerPara.R100s = 0;
		st_TimerPara.F_100S ++;		
	}   
	
    if (st_UartTx.DelayTxFlag == 1)
    {
        if (++st_UartTx.TxDelayTime >= TX_DELAY_TIME)
        {
            st_UartTx.DelayTxFlag = 0;
            st_UartTx.TxDelayTime = 0;
            
            ReadyUartTx();
        }
    }
}
 
/****************************************************
 Function name:  	ISR_Base_Timer
 description:    	
 input:          		none
 output:         	none
 ****************************************************/
void SysTimeISR(void)
{  
    st_TimerPara.SystemTimeCnt++; 
	st_TimerPara.timeTick4ms++;
    if(st_TimerPara.SystemTimeCnt >= SYSTEM_TIME_LIMIT)
    {
        st_TimerPara.SystemTimeCnt=0;
    	st_TimerPara.F_4Ms=1;     
    	
    	SystemTimeProcess(); 
        
    }        
    
    FM0P_BT1_RT->STC &= 0xF8;        //Enable underflow interrupt,Clear interupt cause
    FM0P_BT1_RT->PCSR = 78;          // 4MS    
    FM0P_BT1_RT->TMR = 78;
    FM0P_BT1_RT->TMCR|= 0x03;      //software trigger and count start 

}

void FreqDet_FreqCalc(INT32U u32_Val,stc_hall_detect_t *pstcVal)
{
    if(u32_Val > pstcVal->u32_CycleUpperLimt)
    {
        u32_Val = pstcVal->u32_CycleUpperLimt;
    }
    pstcVal->i32Q5_Freq = (pstcVal->u32_Coff << 5)/(u32_Val);
    pstcVal->i32Q5_Freq = pstcVal->i32Q5_Freq + Q5(0.5);
    pstcVal->i32Q5_Freq &= 0xFFFFFFE0;
    pstcVal->i32Q5_Freq = pstcVal->i32Q5_Freq >> 1;
}


__root void HWD_Handler(void)
{
    if(1 == bFM0P_INTREQ_EXC02MON_HWINT)
    {
        while (1)
        {
            st_CompRunPar.u32ErroType |= HW_WTD_RESET;
            CompCtrl_Stop();          
        }
    }
    else
    {
        while (1)
        {
            st_CompRunPar.u32ErroType |= UNDEFINED_INT;
            CompCtrl_Stop();
        }
    }

}

__root void SWDT_IRQHandler(void)
{ 
    while (TRUE)

    {
        st_CompRunPar.u32ErroType |= SF_WTD_RESET;
        CompCtrl_Stop();      
    }

}

  INT32U g_u32FeedBackCycle = 0;
  INT32U g_u32FeedBackCycleCnt = 0;
  
__root void BT0_3_IRQHandler(void)
{
    INT32U u32_Temp1;
    INT32U u32EndFreqMin = 0;
    INT32U u32EndFreqMax = 0;
    INT32U u32FeedBackCycle = 0;
    
    if(FM0P_BT0_PWC->STC_f.OVIR == 1)
    {
        FM0P_BT0_PWC->STC_f.OVIR = 0;
        st_HallDetect.OvCnt ++;
        if(st_CompRunPar.u8MotorStallFlag == 0)
        {
            if(st_HallDetect.OvCnt > st_HallDetect.OvCntMax)
            {   
                if(st_CompRunPar.u8LimitIFlag == 1)
                {
                    st_CompRunPar.u8MotorStallFlag = 1;     
                }
                else
                {
                    st_HallDetect.i32Q5_Freq = Q5(0);
                    FM0P_BT2_PWM->TMCR &= 0xfffC;      //Disable software trigger and count stop 
                }
            }
        }
        else
        {
            if(st_HallDetect.OvCnt >= 40)       //hall超过2s没有信号，则认为堵转故障
            {
                st_CompRunPar.u32ErroType = MOTOR_LOCK;
                st_MotorWarnPara.u8MotorLockCnt++;
                CompCtrl_Stop();
            }
        }
        #if 0
        if((st_HallDetect.OvCnt  > 40)&&(st_CompRunPar.u8Status == MOTOR_RUNNING))
        {
             st_HallDetect.i32Q5_Freq = 0;
             st_CompRunPar.i32Q8_CurrentSpeedWmHz = 0;
             
             st_CompRunPar.i32CurrentSpeedRpm = 0;
             st_HallDetect.OvCnt = 0;
             st_CompRunPar.u32ErroType = MOTOR_LOCK;
        }
        #endif
    }
    else if(FM0P_BT0_PWC->STC_f.EDIR == 1)
    { 
        st_CompRunPar.u8MotorStallFlag = 0;
        
        u32_Temp1 = FM0P_BT0_PWC->DTBF;
        u32_Temp1 = (u32_Temp1 + 65535 * st_HallDetect.OvCnt);
        st_HallDetect.OvCnt = 0;
        st_HallDetect.u32_CntSum += u32_Temp1;
        st_HallDetect.CntTimes++;
        if(st_HallDetect.CntTimes > 3)
        {
            u32_Temp1 = st_HallDetect.u32_CntSum /st_HallDetect.CntTimes;
            st_HallDetect.u32_CntSum = 0;
            st_HallDetect.CntTimes = 0;
            FreqDet_FreqCalc(u32_Temp1,&st_HallDetect);
        }
               
        
        u32EndFreqMax = st_CustomerPara.EndFreqMax * st_CustomerPara.Comp_u32PolePairs;
        if(st_HallDetect.i32Q5_Freq > Q5(u32EndFreqMax))
        {
            st_HallDetect.i32Q5_Freq = Q5(u32EndFreqMax);

        }
        
        st_CompRunPar.i32CurrentSpeedRpm = ((st_HallDetect.i32Q5_Freq *60) >> 5)/st_CustomerPara.Comp_u32PolePairs;
        st_CompRunPar.i32Q8_CurrentSpeedWmHz = (st_CompRunPar.i32CurrentSpeedRpm << 8)/60;
        

        if(st_CompRunPar.u8Status != MOTOR_RUNNING)
        {
            st_CompRunPar.i32CurrentSpeedRpm = 0;
            st_CompRunPar.i32Q8_CurrentSpeedWmHz = 0;
            
        }

        /*电机运行角度计算计数清零*/
        st_CompRunAngle.u32AngleCount = 0;

        /*转速反馈，电机转一圈输出占空比50的6个周期PWM波*/
        if(st_HallDetect.i32Q5_Freq  > 0)
        {
            u32FeedBackCycle = ((10000000 *st_CustomerPara.Comp_u32PolePairs )<< 5) /((INT32U)st_HallDetect.i32Q5_Freq * 512 * 6);
           //u32FeedBackCycle = (2 * u32_Temp1  * st_CustomerPara.Comp_u32PolePairs)/6;
    		g_u32FeedBackCycleCnt ++;
    		g_u32FeedBackCycle += u32FeedBackCycle;
		    if(g_u32FeedBackCycleCnt >= 200)
    		{
    			g_u32FeedBackCycle = g_u32FeedBackCycle/g_u32FeedBackCycleCnt;
    			FM0P_BT2_PWM->PCSR = g_u32FeedBackCycle; 
	            FM0P_BT2_PWM->PDUT = g_u32FeedBackCycle/2;
	            FM0P_BT2_PWM->TMCR|= 0x03;      //software trigger and count start 
	            g_u32FeedBackCycle = 0;
    			g_u32FeedBackCycleCnt = 0;
    		}
         } 
    }
    
   
    if((FM0P_BT1_RT->STC & 0x01) == 0x01)
    {         
        SysTimeISR();                  
    } 

    if((FM0P_BT3_RT->STC & 0x01) == 0x01)
    {
        UartFrameRec();
    }
}


__root void MFT_FRT_IRQHandler(void)
{
    if(FM0P_MFT0_FRT->TCSA0_f.IRQZF == 1) // 0-detect interrupt triggered by FRT0 in MFT0
    {   	
        CompCtrl_Process(); 
        
        FM0P_MFT0_FRT->TCSA0_f.IRQZF = 0;
    }
    else
    { 
        st_CompRunPar.u32ErroType |= UNDEFINED_INT;
        CompCtrl_Stop();                        
    }
      
}

/****************************************************
 Function name:     Motor0_Sensor_Offeset_Detect
 description:
 input:                 none
 output:            none
 ****************************************************/
void Adc_CompSensorOffesetDetect(void)
{
    if(st_AdcSample.u32CompOffsetCheckDelay < 1)
    {   
        st_AdcSample.i32IuSampleRefSum += Adc_u16RsltOfAdc[COMP_ADC_CH_IU];
        st_AdcSample.i32IvSampleRefSum += Adc_u16RsltOfAdc[COMP_ADC_CH_IV];
        st_AdcSample.u32SampleNum++;
        if(st_AdcSample.u32SampleNum >= st_CustomerPara.u32IuvOffsetCheckTimes)
        {
            st_AdcSample.i32IuSampleRef = st_AdcSample.i32IuSampleRefSum/st_CustomerPara.u32IuvOffsetCheckTimes;
            st_AdcSample.i32IvSampleRef = st_AdcSample.i32IvSampleRefSum/st_CustomerPara.u32IuvOffsetCheckTimes;
            st_AdcSample.i32IuSampleRefSum = 0;
            st_AdcSample.i32IvSampleRefSum = 0;
            st_AdcSample.u32SampleNum = 0;
            if((st_AdcSample.i32IuSampleRef  < st_CustomerPara.i32CompIuvOffsetMin) ||
            (st_AdcSample.i32IuSampleRef  > st_CustomerPara.i32CompIuvOffsetMax)||
            (st_AdcSample.i32IvSampleRef  < st_CustomerPara.i32CompIuvOffsetMin)||
            (st_AdcSample.i32IvSampleRef  > st_CustomerPara.i32CompIuvOffsetMax))            
            {
                st_CompRunPar.u32ErroType |= AD_MIDDLE_ERROR;
            }
            else
            {
                st_CompRunPar.u8SensorAdcStatus = SENSOR_RUNNING;
            }
        }
    }
    else
    {
        st_AdcSample.u32CompOffsetCheckDelay--;
    }
}
/**************************************************************************
*    函数原型:void ReadTempADValue()
*    功    能:读取温度
**************************************************************************/
void ReadTempADValue(void)
{    
    if(st_BoardTemperature.ADSampleCnt < TEMP_AD_NUMBER)
    {
        st_BoardTemperature.ADSampleCnt++;
        st_BoardTemperature.BoardADValueSum += Adc_u16RsltOfAdc[BOARD_TEMP];
    }
}

/****************************************************
 Function name:     ADC0_IRQHandler
 description:
 input:                 none
 output:            none
 ****************************************************/

volatile INT16U g_FRTCount = 0;
INT32U VbusSum = 0;
INT32U VbusCnt = 0;

__root void ADC0_IRQHandler(void)
{
    unsigned long scfd;
    unsigned short data;
    unsigned short ch;   
    INT32U CompVspd = 0;
	INT32U CompSpd = 0;
 
    g_FRTCount = FM0P_MFT0_FRT->TCDT0;

    if(FM0P_ADC0->ADCR_f.SCIF == 1)
    {             
        
        FM0P_ADC0->ADCR_f.SCIF = 0;
        Hwwdg_Feed(0x55,0xAA); 
        while(FM0P_ADC0->SCCR_f.SEMP == 0)  //wait untill fifo empty
        {          
            scfd = FM0P_ADC0->SCFD;			
            ch = scfd & 0x1F;
            data = scfd >> 20;
            Adc_u16RsltOfAdc[ch] = data;
        }
        FM0P_ADC0->SCCR_f.SFCLR = 1; //clear fifo 

        if(++VbusCnt < 32)
        {
        	VbusSum += Adc_u16RsltOfAdc[PFC_ADC_CH_VDC];
        }
        else
        {
        	st_CompRunPar.i32Q8_Vbus = ((VbusSum* st_AdcSample.i32Q14_Vbusk)/VbusCnt) >>6;
        	VbusCnt = 0;
        	VbusSum = 0;
        }
        //st_CompRunPar.i32Q8_Vbus = (Adc_u16RsltOfAdc[PFC_ADC_CH_VDC]* st_AdcSample.i32Q14_Vbusk)>>6;   
	st_AdcSample.u8VolSampleNum++;
	st_AdcSample.u32VspdSum += Adc_u16RsltOfAdc[COMP_VSPD];
	st_AdcSample.u32ThreeLevelSum += Adc_u16RsltOfAdc[COMP_SPD];
	if(st_AdcSample.u8VolSampleNum >= 32)
	{
		CompVspd = st_AdcSample.u32VspdSum/st_AdcSample.u8VolSampleNum;
		CompSpd = st_AdcSample.u32ThreeLevelSum/st_AdcSample.u8VolSampleNum;
	        st_CompRunPar.i32TargetVoltageToSpeed = (CompVspd * st_AdcSample.i32Q14_VSPDFactor)>>14;
	        st_CompRunPar.i32TargetVoltageToPower = (CompVspd * st_AdcSample.i32Q14_VSPDPowerFactor)>>14;
	        st_CompRunPar.ThreeLevelValue = CompSpd;
		st_AdcSample.u32VspdSum = 0;
		st_AdcSample.u32ThreeLevelSum = 0;
		st_AdcSample.u8VolSampleNum = 0;
	}

        ReadTempADValue();
        if(st_CompRunPar.u8SensorAdcStatus == SENSOR_RUNNING)
        {
            st_AdcSample.u8CompCompleteFlag = 1;
         }
         else if(st_CompRunPar.u8SensorAdcStatus == SENSOR_STOP)
        {              
        	Adc_CompSensorOffesetDetect();               
        }
         
    }     
    
}
__root void MFT_WFG_DTIF_IRQHandler(void)
{
    if(1 == FM0P_MFT0_WFG->WFIR_f.DTIFA)
    { 
        st_CompRunPar.u32ErroType = MOTOR_OVER_CURRENT;
        CompCtrl_Stop();
        
        FM0P_MFT0_WFG->WFIR_f.DTICA = 1;         
    }
}

__root void MFS0_RX_IRQHandler(void)
{
    ISR_UART0_Receive();
}
__root void MFS0_TX_IRQHandler(void)
{
    ISR_UART0_Transmit();
}

__root void CSV_IRQHandler(void)
{
    asm("nop");
}
__root void LVD_IRQHandler(void)
{
    asm("nop");
}


__root void EXINT0_7_IRQHandler(void)
{
    asm("nop");
}
__root void DummyIRQHandler(void)
{
    asm("nop");
}
__root void DT_QDU_IRQHandler(void)
{
    asm("nop");
}

__root void MFS1_RX_IRQHandler(void)
{
    asm("nop");
}
__root void MFS1_TX_IRQHandler(void)
{
    asm("nop");
}
__root void MFS3_RX_IRQHandler(void)
{
    asm("nop");
}
__root void MFS3_TX_IRQHandler(void)
{
    asm("nop");
}
__root void DMAC0_IRQHandler(void)
{
    asm("nop");
}
__root void DMAC1_IRQHandler(void)
{
    asm("nop");
}

__root void PPG_IRQHandler(void)
{
    asm("nop");
}
__root void TIM_IRQHandler(void)
{
    asm("nop");
}
__root void MFT_IPC_IRQHandler(void)
{
    asm("nop");
}
__root void MFT_OPC_IRQHandler(void)
{
    asm("nop");
}

