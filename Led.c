
/******************************************************************************/
/** \file led.c
 **
 ** Add description here...
 **
 ** History:
 **   
 *****************************************************************************/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "InitMcu.h"
#include "system_s6e1a1.h"
#include "s6e1a1.h"
#include "base_types.h"
#include "Led.h"

Led_Para st_LedPara;

/**************************************************************************
*    函数原型:void InitLedPort(void)
*    功    能:
**************************************************************************/
void InitLedPort(void)
{
    //--LED1    
    FM0P_GPIO->PFR6_f.P61 = 0;
    FM0P_GPIO->DDR6_f.P61 = 1;                // output pin
    FM0P_GPIO->PDOR6_f.P61 = 1;	
}
/**************************************************************************
*    函数原型:void DispCode(INT8U Code)
*    功    能: 
**************************************************************************/
void DispCode(INT8U Code)
{
    //--首先设定周期
    INT8U i = 0;
    INT8U j = 0;

    i = (Code >> 4) << 1;           //
    j = (Code & 0x0f) << 1;         //高低数值编程以0.5S为单位 如12 = 2S和4S

    st_LedPara.DispPeriodSecond = j + 8;       //闪烁周期= 闪烁时间+2S空闲时间
    // DispPeriodSecond = 28;       //闪烁周期= 7S

    #if 0
    //--十位
    if (st_LedPara.DispTenTime >= i)
    {
        SwitchOffLed1();
    }
    else
    {
        if ((st_LedPara.DispTenTime & 0x01) == 0)
        {
            SwitchOnLed1();
        }
        else
        {
            SwitchOffLed1();
        }
    }
#endif
    //--个位
    if (st_LedPara.DispUnitTime >= j)
    {
        SwitchOffLed1();
    }
    else
    {
        if ((st_LedPara.DispUnitTime & 0x01) == 0)
        {
            SwitchOnLed1();
        }
        else
        {
            SwitchOffLed1();
        }
    }
}

/**************************************************************************
*    函数原型:void DispAlarm(void)
*    功    能:报警码显示
**************************************************************************/
void DispAlarm(void)
{

    if (st_CompRunPar.u32ErroType == UNDER_VOLTAGE)        //under voltage
    {
        DispCode(0x03);
    }
    else if (st_CompRunPar.u32ErroType == OVER_VOLTAGE)        //over voltage
    {
        DispCode(0x02);
    }
    else if (st_CompRunPar.u32ErroType == MOTOR_LOCK)        //motor 堵转
    {
        DispCode(0x06);
    }
    else if (st_CompRunPar.u32ErroType == SW_OVER_CURRENT)        //hardware over current
    {
        DispCode(0x04);
    }  
    else if (st_CompRunPar.u32ErroType == AD_MIDDLE_ERROR)        
    {
        DispCode(0x01);
    }   
    else if (st_CompRunPar.u32ErroType == BOARD_SENSOR_ERROR)        
    {
        DispCode(0x05);
    }   
    else if (st_CompRunPar.u32ErroType == SPEED_ERROR)        
    {
        DispCode(0x07);
    }  
    else if (st_CompRunPar.u32ErroType == MOTOR_OVER_CURRENT)        
    {
        DispCode(0x08);
    }  
	
}
/**************************************************************************
*    函数原型:void DispNormalRunning(void)
*    功    能:指示灯闪烁
**************************************************************************/
void DispNormalRunning(void)
{
    if (st_LedPara.F_NormalFlashOn)
    {
        SwitchOnLed1();
       
    }
    else
    {
        SwitchOffLed1();
        
    }
}

/**************************************************************************
*    函数原型:void LedDisp(void)
*    功    能:指示灯闪烁
**************************************************************************/
void LedDisp(void)
{     
    if (st_CompRunPar.u32ErroType == 0)               //目前用到的故障标志
    {
        DispNormalRunning();
    }
    else
    {        
        DispAlarm();                
    }    
      
}


