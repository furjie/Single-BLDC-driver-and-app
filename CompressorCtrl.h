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
/** \file CompressorCtrl.h
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

#ifndef __COMP_CTRL_H__
#define __COMP_CTRL_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "CustomerInterface.h"
#include "base_types.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/


#define CW                     0 // motor run direction - clockwise
#define CCW                    1 // motor run direction - counter-clockwise


#define MOTOR_STOP             0
#define MOTOR_RUNNING          1

#define SPEEDPI_STOP           0
#define SPEEDPI_RUNNING        1

#define BRAKE                  0
#define PREHOT                 0
#define ORIENTE                1
#define FORCE_STARTUP          2
#define ENTER_CLOSEDLOOP       3
#define CHANGE_SPEED           4

#define NORMAL_RUNNING       0x00
#define OVER_VOLTAGE         0x01
#define UNDER_VOLTAGE        0x02
#define SW_OVER_CURRENT      0x04
#define MOTOR_OVER_CURRENT   0x08
#define BOARD_SENSOR_ERROR     0x10
#define NO_CONECT_COMPRESSOR 0x20
#define AD_MIDDLE_ERROR      0x40
#define SF_WTD_RESET         0x80
#define MOTOR_LOCK           0x100
#define UNDEFINED_INT        0x200
#define HW_WTD_RESET         0x400
#define SPEED_ERROR          0x800


#define SENSOR_STOP          0
#define SENSOR_RUNNING       1

#define RESTART_TIME          60

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
typedef struct 
{
    INT16S    i16DutyMax;
    INT16S    i16Cycle;
    INT16S    i16DeadTime;
    
    INT16S    i16Duty;
    INT16S    i16DutyCount;
    INT16S    i16AonUp;
    INT16S    i16AonDown;
    INT16S    i16BonUp;
    INT16S    i16BonDown;    
}stc_pwm_gen_t;

extern stc_pwm_gen_t      st_CompCtrlPwm;

typedef struct
{
    INT32S i32ISampleRef;
    INT32S i32IuSampleRef;
    INT32S i32IvSampleRef;
    INT32S i32IuSampleRefSum;
    INT32S i32IvSampleRefSum;
    
    INT32S i32Q14_Vbusk;
    INT32S i32Q14_CompCurrentFactor;
    INT32S i32Q14_VSPDFactor;
    INT32S i32Q14_VSPDPowerFactor;
    INT32U u32CompOffsetCheckDelay;
    INT32U u32SampleNum;
    INT32U u32VspdSum;
    INT32U u32ThreeLevelSum;
    volatile INT8U u8CompCompleteFlag;
    INT8U u8VolSampleNum;
    
} stc_sensor_t;

extern stc_sensor_t        st_AdcSample;


typedef struct
{
    INT16U          u16MotorInputMode;
    INT16U          u16MotorRunningMode;
    volatile INT32S i32TargetSpeedRpm;
    INT32S          i32CurrentSpeedRpm;
    INT32S          i32Q8_CurrentSpeedWmHz;    
    INT32S          i32Q8_TargetSpeedWmHz;   
    INT32S          i32Q22_TargetSpeedWmHz;
    INT32S          i32Q8_Vbus;
    INT32S          i32Q8_ISensed;     
    
    INT32S          i32Q8_ISensedPre;
    INT32U          u32ErroType;
    INT32S          i32Q22_TargetWmIncTs;
    INT32S          i32Q22_TargetWmDecTs;
    INT32S          i32TargetVoltageToSpeed;
    INT32S          i32TargetVoltageToPower;
    INT16U          ThreeLevelValue;
    INT16U          HighPower;
    INT16U          MedPower;
    INT16U          LowPower;   
    INT16U          HighPowerDec;
    INT16U          MedPowerDec;
    INT16U          LowPowerDec;
    INT16U          HighSpeed;
    INT16U          MedSpeed;
    INT16U          LowSpeed;
    
    INT8U           u8LimitIFlag;
    INT8U           u8MotorStallFlag;     //电机堵转标志位
    INT8U           u8HallPolarity;
    INT8U           u8Status;
    INT8U           u8Runninglevel;
    volatile INT8U  u8SensorAdcStatus;
} stc_comp_run_t;

extern stc_comp_run_t  st_CompRunPar;

typedef struct
{   
    INT32U u32_Coff;
    INT32U u32_CycleUpperLimt;
    
    INT32S i32Q5_Freq;
    INT32S i32_SpdCoff;
    INT32U u32_CntSum;
    INT8U  CntTimes;
    INT8U OvCnt;
    INT8U OvCntMax;
}stc_hall_detect_t;

extern stc_hall_detect_t   st_HallDetect;

typedef struct
{   
    INT32U u32AngleCount;
    INT32U u32CycleCount;
    
    INT32U u32Q12_CompAngle;
    INT32S i32Q12_CompSinValue;    

}stc_angle_para;

extern stc_angle_para   st_CompRunAngle;

typedef struct
{  
    INT32U u32Q16_PowerSum;
    INT32U u32Q16_AntiPowerSum;
    INT32U u32Q16_CurryPower;
    INT32U u32Q16_CompPower;
    INT32U u32Q16_AntiCompPower;
    INT32U u32Q16_CompPowerFilter;
    INT32U u32Q16_AntiCompPowerFilter;
    INT32U u32CompPower;
    INT32U u32AntiCompPower;
    INT32U u32CompCnt;
    INT32U u32AntiCompCnt;

    INT32U u32TargetPower;
    INT32U u32TargetPowerDecimal;
    INT32S i32Q8_PidTargetPower;
    INT32S i32Q8_PowerPidReg;
    INT8U  u8PowerOpenLoopFlag;    
}stc_Power_para;

extern stc_Power_para   st_CompPower;

typedef struct 
{
    INT32U u32RestartTimeCnt;
    INT32U u32SpeedTimeCnt;
    INT32U u32ReduceTimeCnt;
    INT32U u32TempReduceTimeCnt;
    INT8U u8RestartFlag;
    INT8U u8OverVoltageCnt;
    INT8U u8UnderVoltageCnt;
    INT8U u8LimitVoltageFlag;
    INT8U u8SpeedErrorCnt;
    INT8U u8MotorLockCnt;
    INT8U u8ReduceSpeedFlag;
    INT8U u8TempReduceSpeedFlag;
    INT8U u8ReduceCancelFlag;

} stc_motor_warn_para;

extern stc_motor_warn_para st_MotorWarnPara;

typedef enum
{
    START_LEVEL = 0,
    OPEN_LOOP   = 1,
    CLOSE_LOOP  = 2,
}MOTROR_RUN_LEVEL;

typedef enum
{
    POWER_MODE = 0,
    SPEED_MODE = 1,    
}MOTROR_RUN_MODE;

typedef enum
{
    THREE_LEVEL_MODE = 0,
    COMM_INPUT_MODE = 1,
    VSP_INPUT_MODE   = 2,
}MOTROR_INPUT_MODE;

typedef enum
{
    HIGH_LEVEL = 0,
    MED_LEVEL = 1,
    LOW_LEVEL   = 2,
}THREE_LEVEL;

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
// sample

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/

/****************************************************
Function name:  AverSpd_Init
description:
input:          none
output:         none
****************************************************/
extern void CompCtrl_ConfigPwm(void);

/****************************************************
 Function name: CompCtrl_Init
 description:
 input:         none
 output:            none
 ****************************************************/
extern void CompCtrl_Init(uint16_t u16SampleFreq);

/****************************************************
 Function name: CompCtrl_Process
 description:
 input:         none
 output:            none
 ****************************************************/
extern void CompCtrl_Process(void);

/****************************************************
 Function name: CompCtrl_Start
 description:
 input:         none
 output:            none
 ****************************************************/
extern void CompCtrl_Start(uint16_t u16SampleFreq);
/****************************************************
 Function name: CompCtrl_Stop
 description:
 input:         none
 output:        none
 ****************************************************/
extern void CompCtrl_Stop(void);

/**************************************************************************
*    函数原型: void SetCompressorOn()
*    功    能: 开机
**************************************************************************/
extern void SetCompressorOn(void);

/**************************************************************************
*    函数原型: void SetCompressorOff()
*    功    能: 关机
**************************************************************************/
extern void SetCompressorOff(void);

/**************************************************************************
*    函数原型: void SetNewTargrt(INT16U TargetValue)
*    功    能: 目标频率设定
**************************************************************************/
extern void SetNewTargrt(INT16U TargetValue);

/**************************************************************************
*    函数原型:void GetRunParameter(void) 
*    功    能:
**************************************************************************/
extern void GetRunParameter(void);

#endif /* __COMP_CTRL_H__ */


