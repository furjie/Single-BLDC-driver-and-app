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

#include "InitMcu.h"
#include "base_types.h"
#include "system_s6e1a1.h"
#include "s6e1a1.h"
#include "Isr.h"
#include "Led.h"
#include "uart.h"
#include "Eeprom.h"

#define MIN_ADC_SUM_VALUE    12360
#define MAX_ADC_SUM_VALUE    127742


#define TEMP_NUMBER          166

#define TORQUE_CONST          9550

#define SIXTY_SEC          60

#define OFFSET_SPEED       5


typedef struct 
{
    INT16U  HighLevelMax;
    INT16U  MedLevelMax;
    INT16U  LowLevelMax;    
    INT16U  HighLevelMin;
    INT16U  MedLevelMin;
    INT16U  LowLevelMin;    

    INT16U  HighDryPower;
    INT16U  MedDryPower;
    INT16U  LowDryPower;   
    INT16U  HighWetPower;
    INT16U  MedWetPower;
    INT16U  LowWetPower; 
    
    INT16U  HighDrySpeed;
    INT16U  MedDrySpeed;
    INT16U  LowDrySpeed;    
    INT16U  HighWetSpeed;
    INT16U  MedWetSpeed;
    INT16U  LowWetSpeed;

    INT32S HighLinearParaA;
    INT32S HighLinearParaB;
    INT32S MedLinearParaA;
    INT32S MedLinearParaB;
    INT32S LowLinearParaA;
    INT32S LowLinearParaB;

    INT32S HighSpeedLinearParaA;
    INT32S HighSpeedLinearParaB;
    INT32S MedSpeedLinearParaA;
    INT32S MedSpeedLinearParaB;
    INT32S LowSpeedLinearParaA;
    INT32S LowSpeedLinearParaB;

    INT32S Q16_CurryTorque;
    INT32S Q8_SmallTorque;
    INT32S Q8_LargeTorque;
    INT32S LastSpeedRpm;
    INT16U PowerLimitOut;
}stc_three_level_para;

stc_three_level_para      st_ThreeLevelPara;

INT32S	g_TempSpeed = 0;
INT32S	g_LastTempSpeed = 0;
const INT32U TemperatureTab[TEMP_NUMBER] =
{
    127742 ,127577 ,127394 ,127192 ,126965 ,126711 ,126503 ,126275 ,126022 ,125742,   //-40℃~31℃
    125428 ,125171 ,124890 ,124580 ,124238 ,123858 ,123544 ,123201 ,122826 ,122413 ,  //-30℃~21℃
    121957 ,121579 ,121169 ,120722 ,120232 ,119694 ,119245 ,118760 ,118233 ,117658 ,  //-20℃~11℃
    117030 ,116503 ,115935 ,115320 ,114654 ,113928 ,113321 ,112668 ,111966 ,111209 ,  //-10℃~-1℃
    110389 ,109701 ,108966 ,108179 ,107334 ,106424 ,105657 ,104840 ,103969 ,103038 ,  //0℃~9℃
    102041 ,101197 ,100303 ,99353 ,98343 ,97267 ,96356 ,95395 ,94380 ,93305 ,  //10℃~19℃
    92165 ,91199 ,90184 ,89116 ,87990 ,86803 ,85792 ,84734 ,83626 ,82463 ,  //20℃~29℃
    81242 ,80205 ,79125 ,77997 ,76819 ,75588 ,74543 ,73457 ,72329 ,71156 ,  //30℃~39℃
    69935 ,68892 ,67813 ,66696 ,65539 ,64339 ,63316 ,62261 ,61174 ,60051 ,  //40℃~49℃
    58891 ,57902 ,56885 ,55840 ,54765 ,53658 ,52713 ,51744 ,50751 ,49732 ,  //50℃~59℃
    48688 ,47809 ,46912 ,45995 ,45058 ,44100 ,43282 ,42449 ,41599 ,40734 ,  //60℃~69℃
    39851 ,39090 ,38317 ,37530 ,36730 ,35917 ,35218 ,34509 ,33789 ,33059 ,  //70℃~79℃
    32318 ,31681 ,31035 ,30381 ,29718 ,29047 ,28471 ,27888 ,27299 ,26702 ,  //80℃~89℃
    26099 ,25576 ,25047 ,24513 ,23973 ,23428 ,22955 ,22477 ,21995 ,21509 ,  //90℃~99℃
    21018 ,20596 ,20171 ,19742 ,19311 ,18875 ,18498 ,18117 ,17734 ,17348 ,   //100℃~109℃
    16960 ,16624 ,16286 ,15946 ,15604 ,15260 ,14954 ,14647 ,14338 ,14027 ,  //110℃~119℃
    13715 ,13446 ,13177 ,12906 ,12633 ,12360                     //120℃~125℃
};  
INT32U ReTempSum = 0;

/**************************************************************************
*    函数原型:uchar GetTemperature(uchar ADChannel,uint ADValue)
*    功    能:判断温度值
**************************************************************************/
INT32U GetTemperature(INT32U ADValue)
{
    INT32U Offset = 0;
    INT32U Top = 0 ;
    INT32U Bottom = 0;
    INT32U ReTemp;

	Top = TEMP_NUMBER - 1;
	Bottom = 0;
	ReTempSum = ADValue;
	for(Offset = 82;(Top - Bottom) != 1;)
	{
        Hwwdg_Feed(0x55,0xAA);
        Swwdg_Feed();
	    if(ADValue > TemperatureTab[Offset])
	    {
	        Top = Offset;
	        Offset = (Top + Bottom)/2;
	    }
	    else if(ADValue < TemperatureTab[Offset])
	    {
	        Bottom = Offset;
	        Offset = (Top + Bottom)/2;
	    }
	    else
	    {
	        ReTemp = Offset;
	        return ReTemp;
	    }
	    
	}
	
	ReTemp = Offset;
	return ReTemp;
}
/**************************************************************************
*    函数原型:void ReadTemperature()
*    功    能:读取温度
**************************************************************************/
void ReadTemperature(void)
{
    if(st_BoardTemperature.ADSampleCnt == TEMP_AD_NUMBER)
    {
        if((st_BoardTemperature.BoardADValueSum > MAX_ADC_SUM_VALUE)||
        (st_BoardTemperature.BoardADValueSum < MIN_ADC_SUM_VALUE))
        {
            st_CompRunPar.u32ErroType = BOARD_SENSOR_ERROR;
        }
        else
        {
            st_CompRunPar.u32ErroType &= 0xffffffef;
            st_BoardTemperature.BoardTemperature = GetTemperature(st_BoardTemperature.BoardADValueSum);  
        }
        st_BoardTemperature.ADSampleCnt = 0;
        st_BoardTemperature.BoardADValueSum = 0;

        if(st_CompRunPar.u8Status == MOTOR_RUNNING)
        {
            if(st_BoardTemperature.BoardTemperature > st_CustomerPara.BoardTempWarn)
            {
                st_MotorWarnPara.u8TempReduceSpeedFlag = 1;  
                st_MotorWarnPara.u32ReduceTimeCnt = 0;
                st_MotorWarnPara.u8ReduceCancelFlag = 1;
            }
        }
    }       
 
}
/**************************************************************************
*    函数原型:void CompRestart(void)
*    功    能:风机重启函数
**************************************************************************/
void CompRestart(void)
{
    if((st_MotorWarnPara.u8UnderVoltageCnt >= 3)||(st_MotorWarnPara.u8OverVoltageCnt >= 3)\
    ||(st_MotorWarnPara.u8SpeedErrorCnt >= 3)||(st_MotorWarnPara.u8MotorLockCnt >= 4))
    {
        st_MotorWarnPara.u8RestartFlag = 0;
    }
    
    if(st_MotorWarnPara.u8RestartFlag == 1)
    {
        st_MotorWarnPara.u32RestartTimeCnt++;
        if(st_MotorWarnPara.u32RestartTimeCnt > RESTART_TIME)
        {
            st_MotorWarnPara.u8RestartFlag = 0;
    		st_CompRunPar.u32ErroType = 0;
            SetCompressorOn();
        }
    }
    else
    {
        st_MotorWarnPara.u32RestartTimeCnt = 0;
    }
}  
/**************************************************************************
*    函数原型:void CompAutoReduceSpeed(void)
*    功    能:风机重启函数
**************************************************************************/
void CompAutoReduceSpeed(void)
{
    if(st_CompRunPar.u8Status == MOTOR_RUNNING)
    {
        if(st_MotorWarnPara.u8ReduceSpeedFlag == 1)
        {
            if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
            {
                if (st_CompPower.u32TargetPower > st_CustomerPara.Comp_PowerMin)
            	{
            		st_CompPower.u32TargetPower--;
            	}
            	
            }
            else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
            {
                if(st_CompRunPar.i32TargetSpeedRpm > st_CustomerPara.Comp_u16SpdMin)
            	{
            		st_CompRunPar.i32TargetSpeedRpm -= 10;
            	}
            	
            }
            st_MotorWarnPara.u8ReduceSpeedFlag = 0;
        } 

        if(st_MotorWarnPara.u8TempReduceSpeedFlag == 1)
        {
            st_MotorWarnPara.u32TempReduceTimeCnt++;
            if(st_MotorWarnPara.u32TempReduceTimeCnt > SIXTY_SEC)
            {
                if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
                {
                    if (st_CompPower.u32TargetPower > st_CustomerPara.Comp_PowerMin)
                	{
                		st_CompPower.u32TargetPower--;
                	}
                	
                }
                else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
                {
                    if(st_CompRunPar.i32TargetSpeedRpm > st_CustomerPara.Comp_u16SpdMin)
                	{
                		st_CompRunPar.i32TargetSpeedRpm -= 10;
                	}
                	
                }
                st_MotorWarnPara.u32TempReduceTimeCnt = 0;
            }
            st_MotorWarnPara.u8TempReduceSpeedFlag = 0;
        }
        
    }
}
/**************************************************************************
*    函数原型:void TorqueLinearParaA()
*    功    能:
**************************************************************************/
INT32S TorqueLinearParaA(INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{
    INT32S LinearParaA = 0;    
    INT32S TorqueWet = 0;
    INT32S TorqueDry = 0;

    TorqueWet = (TORQUE_CONST * WetPower)/(1000* WetSpeed);
    TorqueDry = (TORQUE_CONST * DryPower)/(1000* DrySpeed);

    if(TorqueWet != TorqueDry)
    {
        LinearParaA = (WetPower - DryPower)/(TorqueWet - TorqueDry);
    }
    else
    {
        LinearParaA = 0;
    }
    
    return (LinearParaA);
}
/**************************************************************************
*    函数原型:void TorqueLinearParaB()
*    功    能:
**************************************************************************/
INT32S TorqueLinearParaB(INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{    
    INT32S LinearParaB = 0;
    INT32S TorqueWet = 0;
    INT32S TorqueDry = 0;

    TorqueWet = (TORQUE_CONST * WetPower)/(1000* WetSpeed);
    TorqueDry = (TORQUE_CONST * DryPower)/(1000* DrySpeed);

    if(TorqueWet != TorqueDry)
    {
        LinearParaB = (TorqueWet * DryPower - TorqueDry * WetPower)/(TorqueWet - TorqueDry); 
    }
    else
    {
        LinearParaB = 0;
    }
    return (LinearParaB);
}
/**************************************************************************
*    函数原型:void SpeedLinearParaA()
*    功    能:
**************************************************************************/
INT32S SpeedLinearParaA(INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{
    INT32S LinearParaA = 0;
    INT32S Q16_TorqueWet = 0;
    INT32S Q16_TorqueDry = 0;

    Q16_TorqueWet = (((TORQUE_CONST * WetPower)/1000)<<8)/ WetSpeed;
    Q16_TorqueDry = (((TORQUE_CONST * DryPower)/1000)<<8)/ DrySpeed;

    if(Q16_TorqueWet != Q16_TorqueDry)
    {
        LinearParaA = ((WetSpeed - DrySpeed)<<16)/(Q16_TorqueWet - Q16_TorqueDry);
    }
    else
    {
        LinearParaA = 0;
    }
    
    return (LinearParaA);
}
/**************************************************************************
*    函数原型:void SpeedLinearParaB()
*    功    能:
**************************************************************************/
INT32S SpeedLinearParaB(INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{    
    INT32S LinearParaB = 0;  
    INT32S Q16_TorqueWet = 0;
    INT32S Q16_TorqueDry = 0;

    Q16_TorqueWet = (((TORQUE_CONST * WetPower)/1000)<<8)/ WetSpeed;
    Q16_TorqueDry = (((TORQUE_CONST * DryPower)/1000)<<8)/ DrySpeed;

    if(Q16_TorqueWet != Q16_TorqueDry)
    {
        LinearParaB = (DrySpeed * Q16_TorqueWet - WetSpeed * Q16_TorqueDry)/(Q16_TorqueWet - Q16_TorqueDry);
    }
    else
    {
        LinearParaB = 0;
    }
    return (LinearParaB);
}

/**************************************************************************
*    函数原型:void TorqueLinear()
*    功    能:
**************************************************************************/
INT16U PowerLinearCaculate(INT32S ParaA,INT32S ParaB)
{
    INT16U Q8_PowerOut = 0;
    //INT32S Q16_CurryTorque = 0;
    
    st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
    Q8_PowerOut = ((ParaA * st_ThreeLevelPara.Q16_CurryTorque)>>8) + ParaB ;

    return (Q8_PowerOut);
}
/**************************************************************************
*    函数原型:void TorqueLinear()
*    功    能:
**************************************************************************/
INT16U TorqueSpeedLinearCaculate(INT32S ParaA,INT32S ParaB)
{
    INT16U SpeedOut = 0;
    
    SpeedOut = ((ParaA * st_ThreeLevelPara.Q16_CurryTorque)>>16) + ParaB ;

    return (SpeedOut);
}

/**************************************************************************
*    函数原型:INT16U PowerControlDryWet(void)
*    功    能:
**************************************************************************/
INT16U SpeedControlDryWet(INT8U Level,INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{
    INT16U SpeedOutput = 0;
    INT16U SmallSpeed = 0;
    INT16U LargeSpeed = 0;
    INT32S ParaA;
    INT32S ParaB;
    INT32S Q16_TorqueWet = 0;
    INT32S Q16_TorqueDry = 0;
    INT16U CurrentPower = 0;

    CurrentPower = st_CompPower.u32Q16_CompPowerFilter>>8;
    Q16_TorqueWet = (((TORQUE_CONST * WetPower)/1000)<<8)/ WetSpeed;
    Q16_TorqueDry = (((TORQUE_CONST * DryPower)/1000)<<8)/ DrySpeed;
    st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
    if(Level == HIGH_LEVEL)
    {
        ParaA = st_ThreeLevelPara.HighSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.HighSpeedLinearParaB;
    }
    else if(Level == MED_LEVEL)
    {
        ParaA = st_ThreeLevelPara.MedSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.MedSpeedLinearParaB;
    }
    else
    {
        ParaA = st_ThreeLevelPara.LowSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.LowSpeedLinearParaB;
    }

    
    if(DrySpeed == WetSpeed)
    {
        SpeedOutput = DrySpeed;
    }
    else if(WetSpeed > DrySpeed)
    {
        if(WetPower > DryPower)
        {
            if(CurrentPower > WetPower)
            { 
                SpeedOutput = DrySpeed; 
            }
            else if(CurrentPower < DryPower)
            {
                SpeedOutput = WetSpeed;
            }
            else
            {
                if(st_CompRunPar.i32CurrentSpeedRpm >= ((WetSpeed + DrySpeed)/2))
                {
                   SpeedOutput = WetSpeed; 
                }
                else
                {
                    SpeedOutput = DrySpeed;
                }
            }
            
        }
        else if(WetPower < DryPower)
        {
            if(CurrentPower >= DryPower)
            {
                SpeedOutput = DrySpeed;
            }
            else if(CurrentPower <= WetPower)
            {
                SpeedOutput = WetSpeed;
            }
            else
            {
                SpeedOutput = TorqueSpeedLinearCaculate(ParaA,ParaB);
                if(SpeedOutput < DrySpeed)
                {
                    SpeedOutput = DrySpeed;
                }
                else if(SpeedOutput > WetSpeed)
                {
                    SpeedOutput = WetSpeed;
                }                
            }
        }
        else
        {
            if(st_ThreeLevelPara.Q16_CurryTorque >= Q16_TorqueDry)
            {
                SpeedOutput = DrySpeed;
            }
            else if(st_ThreeLevelPara.Q16_CurryTorque <= Q16_TorqueWet)
            {
                SpeedOutput = WetSpeed;
            }
            else
            {
                SpeedOutput = (TORQUE_CONST * WetPower)/((st_ThreeLevelPara.Q16_CurryTorque * 1000)>>8);
                if(SpeedOutput < DrySpeed)
                {
                    SpeedOutput = DrySpeed;
                }
                else if(SpeedOutput > WetSpeed)
                {
                    SpeedOutput = WetSpeed;
                } 
            }
        }
    }
    else
    {
        ;
    }
    #if 0
    Q16_TorqueWet = (((TORQUE_CONST * WetPower)/1000)<<8)/ WetSpeed;
    Q16_TorqueDry = (((TORQUE_CONST * DryPower)/1000)<<8)/ DrySpeed;

    if(DrySpeed > WetSpeed)
    {
        SmallSpeed = WetSpeed;
        LargeSpeed = DrySpeed;
    }
    else
    {
        LargeSpeed = WetSpeed;
        SmallSpeed = DrySpeed;        
    }
    
    if(WetSpeed == DrySpeed)
    {
        SpeedOutput = DrySpeed;    
    }    
    else if(Q16_TorqueWet == Q16_TorqueDry)
    {
        st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
        if(st_ThreeLevelPara.Q16_CurryTorque > Q16_TorqueWet)
        {
            SpeedOutput = (DrySpeed + WetSpeed)/2;
        }
        else
        {
            SpeedOutput = SmallSpeed;
        }
    }
    else
    {
        if(Level == HIGH_LEVEL)
        {
            ParaA = st_ThreeLevelPara.HighSpeedLinearParaA;
            ParaB = st_ThreeLevelPara.HighSpeedLinearParaB;
        }
        else if(Level == MED_LEVEL)
        {
            ParaA = st_ThreeLevelPara.MedSpeedLinearParaA;
            ParaB = st_ThreeLevelPara.MedSpeedLinearParaB;
        }
        else
        {
            ParaA = st_ThreeLevelPara.LowSpeedLinearParaA;
            ParaB = st_ThreeLevelPara.LowSpeedLinearParaB;
        }
        if(st_CompRunPar.i32CurrentSpeedRpm < st_CustomerPara.Comp_u16SpdMin)
        {
             SpeedOutput = SmallSpeed;
        }
        else
        {
             st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
             SpeedOutput = TorqueSpeedLinearCaculate(ParaA,ParaB);
        }          
        
        if(SpeedOutput < st_CustomerPara.Comp_u16SpdMin)
        {
            SpeedOutput = st_CustomerPara.Comp_u16SpdMin;
        }
        else if(SpeedOutput > st_CustomerPara.Comp_u16SpdMax)
        {
            SpeedOutput = st_CustomerPara.Comp_u16SpdMax;
        }  
        
    }
    #endif
    return (SpeedOutput);
}

INT32S g_CurryTorque = 0;
INT32S g_WetTorque = 0;
INT32S g_DryTorque = 0;
INT32S g_i32LastSpeedRpm = 0;
/**************************************************************************
*    函数原型:INT16U PowerControlDryWet(void)
*    功    能:
**************************************************************************/
INT16U PowerControlDryWet(INT8U Level,INT16U WetPower,INT16U WetSpeed, INT16U DryPower, INT16U DrySpeed)
{
    INT16U PowerOutput = 0;
    INT32S ParaA;
    INT32S ParaB;
    INT32S CurryTorque = 0;
    INT32S WetTorque = 0;
    INT32S DryTorque = 0;
    INT16U CurryPower = 0;
    INT16U CaculatePower = 0;
    INT16U CurrySpeed = 0;
	INT16U MidSpeed = 0;
	INT16U SpeedDiff = 0;
	INT16U SpeedAdd = 0;
	INT32S Q16_TorqueWet = 0;
    INT32S Q16_TorqueDry = 0;
    INT16U SpeedOutput = 0;
    INT16U SmallPower = 0;
    INT16U LargePower = 0;

    if(DryPower > WetPower)
    {
      SmallPower = WetPower;
      LargePower = DryPower;
    }
    else
    {
      LargePower = WetPower;
      SmallPower = DryPower;        
    }

    Q16_TorqueWet = (((TORQUE_CONST * WetPower)/1000)<<8)/ WetSpeed;
    Q16_TorqueDry = (((TORQUE_CONST * DryPower)/1000)<<8)/ DrySpeed;
    st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);

    if(Level == HIGH_LEVEL)
    {
        ParaA = st_ThreeLevelPara.HighSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.HighSpeedLinearParaB;
    }
    else if(Level == MED_LEVEL)
    {
        ParaA = st_ThreeLevelPara.MedSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.MedSpeedLinearParaB;
    }
    else
    {
        ParaA = st_ThreeLevelPara.LowSpeedLinearParaA;
        ParaB = st_ThreeLevelPara.LowSpeedLinearParaB;
    }
    
    if(WetPower == DryPower)
    {
        PowerOutput = WetPower;    
    }
    else if(Q16_TorqueWet == Q16_TorqueDry)
    {      
        if(WetSpeed > DrySpeed)
        {
            if(st_CompRunPar.i32CurrentSpeedRpm >= WetSpeed)
            {
                PowerOutput = WetPower;
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= DrySpeed)
            {
                PowerOutput = DryPower;
            }
            else
            {
                SpeedOutput = st_ThreeLevelPara.Q16_CurryTorque * DrySpeed/Q16_TorqueDry;
                PowerOutput = (((st_ThreeLevelPara.Q16_CurryTorque * SpeedOutput)>>8)*1000)/TORQUE_CONST;       
            }
        }
        else
        {
            if(st_CompRunPar.i32CurrentSpeedRpm >= DrySpeed)
            {
                PowerOutput = DryPower;
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= WetSpeed)
            {
                PowerOutput = WetPower;
            }
            else
            {
                SpeedOutput = st_ThreeLevelPara.Q16_CurryTorque * WetSpeed/Q16_TorqueDry;
                PowerOutput = (((st_ThreeLevelPara.Q16_CurryTorque * SpeedOutput)>>8)*1000)/TORQUE_CONST;
          
            }    
        }
    }
    else
    {
        if(WetSpeed > DrySpeed)
        {
            if(st_CompRunPar.i32CurrentSpeedRpm >= WetSpeed)
            {
                PowerOutput = WetPower;
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= DrySpeed)
            {
                PowerOutput = DryPower;
            }
            else
            {
                SpeedOutput = TorqueSpeedLinearCaculate(ParaA,ParaB);
                PowerOutput = (((st_ThreeLevelPara.Q16_CurryTorque * SpeedOutput)>>8)*1000)/TORQUE_CONST;
    
            }          
        }
        else
        {
    	    if(st_CompRunPar.i32CurrentSpeedRpm >= DrySpeed)
            {
                PowerOutput = DryPower;
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= WetSpeed)
            {
                PowerOutput = WetPower;
            }
            else
            {
                SpeedOutput = TorqueSpeedLinearCaculate(ParaA,ParaB);
                PowerOutput = (((st_ThreeLevelPara.Q16_CurryTorque * SpeedOutput)>>8)*1000)/TORQUE_CONST;             
            }
        }
    }

    if(PowerOutput < SmallPower)
    {
        PowerOutput = SmallPower;
    }
    else if(PowerOutput > LargePower)
    {
        PowerOutput = LargePower;
    }  

    #if 0
    if(WetPower == DryPower)
    {
        PowerOutput = WetPower;    
    }
    else if(WetPower < DryPower)
    {
        if(Level == HIGH_LEVEL)
        {
            ParaA = st_ThreeLevelPara.HighLinearParaA;
            ParaB = st_ThreeLevelPara.HighLinearParaB;
        }
        else if(Level == MED_LEVEL)
        {
            ParaA = st_ThreeLevelPara.MedLinearParaA;
            ParaB = st_ThreeLevelPara.MedLinearParaB;
        }
        else
        {
            ParaA = st_ThreeLevelPara.LowLinearParaA;
            ParaB = st_ThreeLevelPara.LowLinearParaB;
        }
        if(WetSpeed > DrySpeed)
        {
            if(st_CompRunPar.i32CurrentSpeedRpm >= WetSpeed)
            {
                PowerOutput = WetPower;
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= DrySpeed)
            {
                PowerOutput = DryPower;
            }
            else
            {
                PowerOutput = PowerLinearCaculate(ParaA,ParaB);
                if(PowerOutput < WetPower)
                {
                	PowerOutput = WetPower;
                }
                else if(PowerOutput > DryPower)
                {
                	PowerOutput = DryPower;
                }
            }
        }
        else
        {
        	st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
            CurryTorque = st_ThreeLevelPara.Q16_CurryTorque>>8;                   
            WetTorque = (TORQUE_CONST * WetPower)/(1000* DrySpeed);//这里必须使用干工况的设定转速
            DryTorque = (TORQUE_CONST * DryPower)/(1000* DrySpeed);    
            if(CurryTorque >= DryTorque)
            {
                PowerOutput = DryPower;
            }
            else if(CurryTorque <= WetTorque)
            {
                PowerOutput = WetPower;
            }
            else
            {
                PowerOutput = (1000 * CurryTorque * DrySpeed)/TORQUE_CONST;
                if(PowerOutput < WetPower)
                {
                	PowerOutput = WetPower;
                }
                else if(PowerOutput > DryPower)
                {
                	PowerOutput = DryPower;
                }
            }            
        }
    }
    else
    {
        if(WetSpeed > DrySpeed)
        {
            WetTorque = (TORQUE_CONST * WetPower)/(1000* WetSpeed);
            DryTorque = (TORQUE_CONST * DryPower)/(1000* DrySpeed); 
            CurryPower = st_CompPower.u32Q16_CompPowerFilter>>8;
            CurrySpeed = st_CompRunPar.i32CurrentSpeedRpm;
            if(WetTorque > DryTorque)
            {
                st_ThreeLevelPara.Q8_SmallTorque = DryTorque;
                st_ThreeLevelPara.Q8_LargeTorque = WetTorque;
                
            }
            else
            {
                st_ThreeLevelPara.Q8_SmallTorque = WetTorque;
                st_ThreeLevelPara.Q8_LargeTorque = DryTorque;
            }
            MidSpeed = (WetSpeed + DrySpeed)/2;
            if(st_CompRunPar.i32CurrentSpeedRpm >= WetSpeed)
            {
                //CaculatePower = (1000 * st_ThreeLevelPara.Q8_SmallTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
				CaculatePower = (1000 * st_ThreeLevelPara.Q8_LargeTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
                if(st_ThreeLevelPara.PowerLimitOut < DryPower)
                {
                    st_ThreeLevelPara.PowerLimitOut = DryPower;
                }
                else if((st_ThreeLevelPara.PowerLimitOut < WetPower)&&(CurrySpeed < st_CustomerPara.Comp_u16SpdMax))
                {
                    st_ThreeLevelPara.PowerLimitOut += 126;
                }

                PowerOutput = CaculatePower;
                if(PowerOutput < DryPower)
                {
                	PowerOutput = DryPower;
                }
                else if(PowerOutput > WetPower)
                {
                	PowerOutput = WetPower;
                }    
                
            }
            else if(st_CompRunPar.i32CurrentSpeedRpm <= DrySpeed )
            {
                PowerOutput = DryPower;                
            }
            else
            {             
                SpeedDiff = WetSpeed - DrySpeed;
                if(SpeedDiff < 50)
                {
                	SpeedAdd = 10;
                }
                else
                {
                	SpeedAdd = 15;
                }
                if(g_i32LastSpeedRpm < MidSpeed)
                {                	
	                if(st_CompRunPar.i32CurrentSpeedRpm >= (DrySpeed + 15))
	                {
	                	CaculatePower = (1000 * st_ThreeLevelPara.Q8_LargeTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
	                }
	                else
	                {
	                	CaculatePower = (1000 * st_ThreeLevelPara.Q8_SmallTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
	                }
	            }
	            else
	            {
	            	if(st_CompRunPar.i32CurrentSpeedRpm >= (WetSpeed - 10))
	                {
	                	CaculatePower = (1000 * st_ThreeLevelPara.Q8_LargeTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
	                }
	                else
	                {
	                	CaculatePower = (1000 * st_ThreeLevelPara.Q8_SmallTorque * st_CompRunPar.i32CurrentSpeedRpm)/TORQUE_CONST;
	                }
	            }
                PowerOutput = CaculatePower;
                
                if(PowerOutput < DryPower)
                {
                	PowerOutput = DryPower;
                }
                else if(PowerOutput > WetPower)
                {
                	PowerOutput = WetPower;
                } 
                st_ThreeLevelPara.PowerLimitOut = PowerOutput;
            }            
      
        }
        else
        {
        	#if 0
             if(st_CompRunPar.i32CurrentSpeedRpm < DrySpeed)    
             {
                PowerOutput = DryPower;
             }
             else
             {
                PowerOutput = WetPower;
             }
             #endif
            st_ThreeLevelPara.Q16_CurryTorque = (TORQUE_CONST * (st_CompPower.u32Q16_CompPowerFilter/1000))/(st_CompRunPar.i32CurrentSpeedRpm);
            CurryTorque = st_ThreeLevelPara.Q16_CurryTorque>>8;                   
            WetTorque = (TORQUE_CONST * WetPower)/(1000* DrySpeed);//这里必须使用干工况的设定转速
            DryTorque = (TORQUE_CONST * DryPower)/(1000* DrySpeed);    
            if(CurryTorque >= WetTorque)
            {
                PowerOutput = WetPower;
            }
            else if(CurryTorque <= DryTorque)
            {
                PowerOutput = DryPower;
            }
            else
            {
                PowerOutput = (1000 * CurryTorque * DrySpeed)/TORQUE_CONST;
                if(PowerOutput < DryPower)
                {
                	PowerOutput = DryPower;
                }
                else if(PowerOutput > WetPower)
                {
                	PowerOutput = WetPower;
                }
            } 
        }
    }
    g_i32LastSpeedRpm = st_CompRunPar.i32CurrentSpeedRpm;
    #endif
    return (PowerOutput);
}
    

INT16U g_PowerOutput = 0;
INT32U g_SpdValuecnt = 0;
/**************************************************************************
*    函数原型:void UpdatePwmInFreq(void)
*    功    能:根据PWM输入的电频率，更新运行频率
**************************************************************************/
void UpdateCompSpeed(void)
{    
    INT16U SpdValue = 0;
    INT16U Q8_PowerOutput = 0;
    INT16U SpeedOutput = 0;
    
    if(st_CompRunPar.u16MotorInputMode == THREE_LEVEL_MODE)
    {    
        SpdValue = st_CompRunPar.ThreeLevelValue;
        if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
        {            
            if((SpdValue < st_ThreeLevelPara.HighLevelMax)&&(SpdValue >= st_ThreeLevelPara.HighLevelMin))
            {
                Q8_PowerOutput = PowerControlDryWet(HIGH_LEVEL,st_ThreeLevelPara.HighWetPower,\
                st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);
                g_PowerOutput = Q8_PowerOutput;
                st_CompPower.u32TargetPower = Q8_PowerOutput>>8;
                st_CompPower.u32TargetPowerDecimal = Q8_PowerOutput&0x00ff;
                //st_CompPower.u32TargetPower = st_ThreeLevelPara.HighDryPower>>8;
                //st_CompPower.u32TargetPowerDecimal = st_ThreeLevelPara.HighDryPower&0x00ff;
            }   
            else if((SpdValue < st_ThreeLevelPara.MedLevelMax)&&(SpdValue >= st_ThreeLevelPara.MedLevelMin))
            {
                Q8_PowerOutput = PowerControlDryWet(MED_LEVEL,st_ThreeLevelPara.MedWetPower,\
                st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);
                st_CompPower.u32TargetPower = Q8_PowerOutput>>8;
                st_CompPower.u32TargetPowerDecimal = Q8_PowerOutput&0x00ff;
            }   
            else if((SpdValue < st_ThreeLevelPara.LowLevelMax)&&(SpdValue >= st_ThreeLevelPara.LowLevelMin))
            {
                Q8_PowerOutput = PowerControlDryWet(LOW_LEVEL,st_ThreeLevelPara.LowWetPower,\
                st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);
                st_CompPower.u32TargetPower = Q8_PowerOutput>>8;
                st_CompPower.u32TargetPowerDecimal = Q8_PowerOutput&0x00ff;
            }
            else
            {	            
                st_CompPower.u32TargetPower = 0;
                st_CompPower.u32TargetPowerDecimal = 0;
            }            
        }
        else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
        {
            if((SpdValue < st_ThreeLevelPara.HighLevelMax)&&(SpdValue >= st_ThreeLevelPara.HighLevelMin))
            {
                SpeedOutput = SpeedControlDryWet(HIGH_LEVEL,st_ThreeLevelPara.HighWetPower,\
                st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);

                st_CompRunPar.i32TargetSpeedRpm = SpeedOutput;
                //st_CompRunPar.i32TargetSpeedRpm = st_CompRunPar.HighSpeed;
            }   
            else if((SpdValue < st_ThreeLevelPara.MedLevelMax)&&(SpdValue >= st_ThreeLevelPara.MedLevelMin))
            {
                SpeedOutput = SpeedControlDryWet(MED_LEVEL,st_ThreeLevelPara.MedWetPower,\
                st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);

                st_CompRunPar.i32TargetSpeedRpm = SpeedOutput;
                //st_CompRunPar.i32TargetSpeedRpm = st_CompRunPar.MedSpeed;
            }   
            else if((SpdValue < st_ThreeLevelPara.LowLevelMax)&&(SpdValue >= st_ThreeLevelPara.LowLevelMin))
            {
                SpeedOutput = SpeedControlDryWet(LOW_LEVEL,st_ThreeLevelPara.LowWetPower,\
                st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);

                st_CompRunPar.i32TargetSpeedRpm = SpeedOutput;
                //st_CompRunPar.i32TargetSpeedRpm = st_CompRunPar.LowSpeed;
            }
            else
            {
                st_CompRunPar.i32TargetSpeedRpm = 0;
            }
        }
    }
    else if(st_CompRunPar.u16MotorInputMode == VSP_INPUT_MODE)
    {
        if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
        {            
        	if((st_CompRunPar.i32TargetVoltageToPower < (st_CustomerPara.Comp_PowerMin - 2))||(st_CompRunPar.i32TargetVoltageToPower > (st_CustomerPara.Comp_PowerMax + 2)))
        	{
        		st_CompPower.u32TargetPower = 0;
        	}
        	else if(st_CompRunPar.i32TargetVoltageToPower > st_CustomerPara.Comp_PowerMax)
        	{   
        	    st_CompPower.u32TargetPower = st_CustomerPara.Comp_PowerMax;
        	}
        	else if(st_CompRunPar.i32TargetVoltageToPower < st_CustomerPara.Comp_PowerMin)
        	{
        	    st_CompPower.u32TargetPower = st_CustomerPara.Comp_PowerMin ;
        	}
        	else
        	{
        		st_CompPower.u32TargetPower = st_CompRunPar.i32TargetVoltageToPower;
        	}  
        }
        else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
        {   
        	if((st_CompRunPar.i32TargetVoltageToSpeed < (st_CustomerPara.Comp_u16SpdMin - 100))||(st_CompRunPar.i32TargetVoltageToSpeed > (st_CustomerPara.Comp_u16SpdMax + 300)))
        	{
        		st_CompRunPar.i32TargetSpeedRpm = 0;
        	}
        	else if(st_CompRunPar.i32TargetVoltageToSpeed > st_CustomerPara.Comp_u16SpdMax)
        	{   
        	    st_CompRunPar.i32TargetSpeedRpm = st_CustomerPara.Comp_u16SpdMax;
        	}
        	else if(st_CompRunPar.i32TargetVoltageToSpeed < st_CustomerPara.Comp_u16SpdMin)
        	{
        	    st_CompRunPar.i32TargetSpeedRpm = st_CustomerPara.Comp_u16SpdMin ;
        	}
        	else
        	{
        		st_CompRunPar.i32TargetSpeedRpm = st_CompRunPar.i32TargetVoltageToSpeed;
        	}        
        }
    }   
}

/**************************************************************************
*    函数原型:void Time250msPrc(void)
*    功    能:
**************************************************************************/
void Time250mSPrc(void)
{
      //--ten time counting
    if (++st_LedPara.DispTenTime >= st_LedPara.DispPeriodSecond)
    {
        st_LedPara.DispTenTime = 0;
    }

    //--unit time counting
    if (++st_LedPara.DispUnitTime >= st_LedPara.DispPeriodSecond)
    {
        st_LedPara.DispUnitTime = 0;
    }     
             
}
/**************************************************************************
*    函数原型:void Time100mSPrc(void)
*    功    能:
**************************************************************************/
void Time100mSPrc(void)
{   
    if (st_LedPara.F_NormalFlashOn == 1)
    {
        st_LedPara.F_NormalFlashOn = 0;
    }
    else
    {
        st_LedPara.F_NormalFlashOn = 1;
    }
}
/**************************************************************************
*    函数原型:void TimePrc(void)
*    功    能:
**************************************************************************/
void TimePrc(void)
{
    if (st_TimerPara.F_248Ms)
    {
        st_TimerPara.F_248Ms = 0;
        Time250mSPrc();         //100ms
        GetRunParameter();
    }

    if (st_TimerPara.F_100Ms)
    {
        st_TimerPara.F_100Ms = 0;
        Time100mSPrc();         //100ms
    }

    if(st_TimerPara.F_1S == 1)
    {
        st_TimerPara.F_1S = 0;
        CompRestart();

        
        st_MotorWarnPara.u32ReduceTimeCnt++; 
        if(st_MotorWarnPara.u32ReduceTimeCnt > 60)
        {
            st_MotorWarnPara.u32ReduceTimeCnt = 0;
            st_MotorWarnPara.u8ReduceCancelFlag = 0;
        }
        
    }
    
    if (st_TimerPara.F_3S == 1)
    {
        st_TimerPara.F_3S = 0;
        if(st_MotorWarnPara.u8ReduceCancelFlag == 1)
        {
            CompAutoReduceSpeed();
        }
        else
        {
            UpdateCompSpeed();
        }
    }
     
}
/****************************************************
 Function name:    InitMotorRunPara
 description:
 input:
 output:            none
 ****************************************************/
void InitMotorRunPara(void)
{
    st_CompRunPar.u16MotorInputMode = EepromParameter.Data.MotorInputMode;
    st_CompRunPar.u16MotorRunningMode = EepromParameter.Data.MotorRunningMode;    


    st_ThreeLevelPara.HighDryPower = EepromParameter.Data.HighDryPowerRom;
    st_ThreeLevelPara.MedDryPower = EepromParameter.Data.MedDryPowerRom;   
    st_ThreeLevelPara.LowDryPower = EepromParameter.Data.LowDryPowerRom;
    st_ThreeLevelPara.HighWetPower = EepromParameter.Data.HighWetPowerRom;    
    st_ThreeLevelPara.MedWetPower = EepromParameter.Data.MedWetPowerRom;    
    st_ThreeLevelPara.LowWetPower = EepromParameter.Data.LowWetPowerRom;
    
    st_ThreeLevelPara.HighDrySpeed = EepromParameter.Data.HighDrySpeedRom;    
    st_ThreeLevelPara.MedDrySpeed = EepromParameter.Data.MedDrySpeedRom;   
    st_ThreeLevelPara.LowDrySpeed = EepromParameter.Data.LowDrySpeedRom;
    st_ThreeLevelPara.HighWetSpeed = EepromParameter.Data.HighWetSpeedRom;    
    st_ThreeLevelPara.MedWetSpeed = EepromParameter.Data.MedWetSpeedRom;    
    st_ThreeLevelPara.LowWetSpeed = EepromParameter.Data.LowWetSpeedRom;

    if(st_ThreeLevelPara.HighDrySpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.HighDrySpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    if(st_ThreeLevelPara.MedDrySpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.MedDrySpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    if(st_ThreeLevelPara.LowDrySpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.LowDrySpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    if(st_ThreeLevelPara.HighWetSpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.HighWetSpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    if(st_ThreeLevelPara.MedWetSpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.MedWetSpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    if(st_ThreeLevelPara.LowWetSpeed < st_CustomerPara.Comp_u16SpdMin)
    {
        st_ThreeLevelPara.LowWetSpeed = st_CustomerPara.Comp_u16SpdMin;
    }
    /*****************各档位转矩、功率线性参数计算*****************/
    st_ThreeLevelPara.HighLinearParaA = TorqueLinearParaA(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);
    st_ThreeLevelPara.HighLinearParaB = TorqueLinearParaB(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);

    st_ThreeLevelPara.MedLinearParaA = TorqueLinearParaA(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);
    st_ThreeLevelPara.MedLinearParaB = TorqueLinearParaB(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);

    st_ThreeLevelPara.LowLinearParaA = TorqueLinearParaA(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);
    st_ThreeLevelPara.LowLinearParaB = TorqueLinearParaB(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);

    #if 0
    /*****************各档位转速、功率线性参数计算*****************/
    st_ThreeLevelPara.HighSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);
    st_ThreeLevelPara.HighSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);

    st_ThreeLevelPara.MedSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);
    st_ThreeLevelPara.MedSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);

    st_ThreeLevelPara.LowSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);
    st_ThreeLevelPara.LowSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);
    #endif
    
    /*****************各档位转速、转矩线性参数计算*****************/
    st_ThreeLevelPara.HighSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);
    st_ThreeLevelPara.HighSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.HighWetPower,\
    st_ThreeLevelPara.HighWetSpeed,st_ThreeLevelPara.HighDryPower,st_ThreeLevelPara.HighDrySpeed);

    st_ThreeLevelPara.MedSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);
    st_ThreeLevelPara.MedSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.MedWetPower,\
    st_ThreeLevelPara.MedWetSpeed,st_ThreeLevelPara.MedDryPower,st_ThreeLevelPara.MedDrySpeed);

    st_ThreeLevelPara.LowSpeedLinearParaA = SpeedLinearParaA(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);
    st_ThreeLevelPara.LowSpeedLinearParaB = SpeedLinearParaB(st_ThreeLevelPara.LowWetPower,\
    st_ThreeLevelPara.LowWetSpeed,st_ThreeLevelPara.LowDryPower,st_ThreeLevelPara.LowDrySpeed);


    st_CompRunPar.HighSpeed = EepromParameter.Data.HighSpeed;
    st_CompRunPar.MedSpeed = EepromParameter.Data.MedSpeed;
    st_CompRunPar.LowSpeed = EepromParameter.Data.LowSpeed;

    /*高档电压值范围:1750mv~4500mv; 中档电压值范围:650mv~1750mv; 低档电压值范围:200mv~650mv;*/
    st_ThreeLevelPara.HighLevelMax = 4500 * 4096/5000;
    st_ThreeLevelPara.HighLevelMin = 1750 * 4096/5000; 
    st_ThreeLevelPara.MedLevelMax = 1750 * 4096/5000;
    st_ThreeLevelPara.MedLevelMin = 650 * 4096/5000;
    st_ThreeLevelPara.LowLevelMax = 650 * 4096/5000;
    st_ThreeLevelPara.LowLevelMin = 200 * 4096/5000;

}

/********************************************************************************
 ** \brief  Main function of project for S6E1A1 series.
 **
 ** \param  none
 ** \return uint32_t return value, if needed
 ******************************************************************************/
void main(void)
{
    InitMcu_Clock();
    InitMcu_Nvic();
    InitMcu_Gpio();
    InitIICPort();
    InitMotorPara();
    InitMcu_Adc(st_CustomerPara.Comp_u16CarrierFreq);
    CompCtrl_Init(st_CustomerPara.Comp_u16CarrierFreq);
    InitLedPort();

    InitMcu_Basetimer();
    InitMcu_CompTimerRun();
    InitUart3();

    InitMcu_Wdg();

    ReadEepromData(); 
    InitMotorRunPara();
    while(1)
    {
        Hwwdg_Feed(0x55,0xAA);
        Swwdg_Feed();      

        if(st_CompRunPar.u16MotorRunningMode == POWER_MODE)
        {
            if((st_CompRunPar.u32ErroType == 0)&&(st_CompRunPar.u8Status != MOTOR_RUNNING)&&(st_CompPower.u32TargetPower > 0))
            {
                st_CompRunPar.i32TargetSpeedRpm = 300;
                CompCtrl_Start(st_CustomerPara.Comp_u16CarrierFreq);                
            }        
            if(st_CompRunPar.u8Status == MOTOR_RUNNING)
            {                  
                if((st_CompRunPar.u32ErroType != 0)||(st_CompPower.u32TargetPower  == 0))           
                {
                    CompCtrl_Stop();
                }
            } 
        }
        else if(st_CompRunPar.u16MotorRunningMode == SPEED_MODE)
        {
            if((st_CompRunPar.u32ErroType == 0)&&(st_CompRunPar.u8Status != MOTOR_RUNNING)&&(st_CompRunPar.i32TargetSpeedRpm > 0))
            { 
                CompCtrl_Start(st_CustomerPara.Comp_u16CarrierFreq);                
            }        
            if(st_CompRunPar.u8Status == MOTOR_RUNNING)
            {   
                if((st_CompRunPar.u32ErroType != 0)||(st_CompRunPar.i32TargetSpeedRpm == 0))                
                {
                    CompCtrl_Stop();
                }
            } 
        }
        DecodeUartRx();
    	ReadTemperature();
        TimePrc();
        LedDisp(); 
    }    
}
