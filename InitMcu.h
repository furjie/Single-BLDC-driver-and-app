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
/** \file InitMcu.h
 **
 ** Add description here...
 **
 ** History:
 **   - 2013-09-20  0.1.0  Mecheal.Yang  First version 
 *****************************************************************************/

#ifndef __INIT_MCU_H__
#define __INIT_MCU_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "CompressorCtrl.h"
#include "CustomerInterface.h"
#include "base_types.h"

//*****************************************************************************
//
// Define data types
//
//*****************************************************************************

typedef struct
{
    INT32U FreqOfPLL_Hz;
    INT32U FreqOfBaseClk_Hz;
    INT32U FreqOfAPB0Clk_Hz;
    INT32U FreqOfAPB1Clk_Hz;
    INT32U FreqOfAPB2Clk_Hz;
}_stClkPara;

#define PFC_ADC_CH_VDC         2//0//ADC_CH_2    // ADC channel - Vdc
#define COMP_ADC_CH_IU         1// ADC channel - Iu
#define COMP_ADC_CH_IV         0//7    // ADC channel - Iv
#define COMP_SPD               5    // 三档输入
#define COMP_VSPD              6    // 电压控制转速，采集电压值
#define BOARD_TEMP             4    // 温度采集

#define HALL_POLARITY       FM0P_GPIO->PDIR4_f.P49
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
// ADC FIFO trigger deepth for scan conversion
#define ADC_SCAN_CONV_STAGE1 1
#define ADC_SCAN_CONV_STAGE2 2
#define ADC_SCAN_CONV_STAGE3 3
#define ADC_SCAN_CONV_STAGE4 4
#define ADC_SCAN_CONV_STAGE5 5
#define ADC_SCAN_CONV_STAGE6 6
#define ADC_SCAN_CONV_STAGE7 7
#define ADC_SCAN_CONV_STAGE8 8
#define ADC_SCAN_CONV_STAGE9 9
#define ADC_SCAN_CONV_STAGE10 10
#define ADC_SCAN_CONV_STAGE11 11
#define ADC_SCAN_CONV_STAGE12 12
#define ADC_SCAN_CONV_STAGE13 13
#define ADC_SCAN_CONV_STAGE14 14
#define ADC_SCAN_CONV_STAGE15 15
#define ADC_SCAN_CONV_STAGE16 16
// Frequency multiplication value 1 for Sampling time
#define ADC_ST_VALUE0 0
#define ADC_ST_VALUE1 1
#define ADC_ST_VALUE2 2
#define ADC_ST_VALUE3 3
#define ADC_ST_VALUE4 4
#define ADC_ST_VALUE5 5
#define ADC_ST_VALUE6 6
#define ADC_ST_VALUE7 7
#define ADC_ST_VALUE8 8
#define ADC_ST_VALUE9 9
#define ADC_ST_VALUE10 10
#define ADC_ST_VALUE11 11
#define ADC_ST_VALUE12 12
#define ADC_ST_VALUE13 13
#define ADC_ST_VALUE14 14
#define ADC_ST_VALUE15 15
#define ADC_ST_VALUE16 16
#define ADC_ST_VALUE17 17
#define ADC_ST_VALUE18 18
#define ADC_ST_VALUE19 19
#define ADC_ST_VALUE20 20
#define ADC_ST_VALUE21 21
#define ADC_ST_VALUE22 22
#define ADC_ST_VALUE23 23
#define ADC_ST_VALUE24 24
#define ADC_ST_VALUE25 25
#define ADC_ST_VALUE26 26
#define ADC_ST_VALUE27 27
#define ADC_ST_VALUE28 28
#define ADC_ST_VALUE29 29
#define ADC_ST_VALUE30 30
#define ADC_ST_VALUE31 31
// Frequency multiplication value 2 for Sampling time
#define ADC_STX_VALUE0 0
#define ADC_STX_VALUE1 1
#define ADC_STX_VALUE2 2
#define ADC_STX_VALUE3 3
#define ADC_STX_VALUE4 4
#define ADC_STX_VALUE5 5
#define ADC_STX_VALUE6 6
#define ADC_STX_VALUE7 7

// Sampling time set register
#define ADC_ST0 0
#define ADC_ST1 1
//
// clock frequency
//
#define Main_Frequency_4M   0
#define Main_Frequency_8M   1
#define Main_Frequency_12M  2
#define Main_Frequency_16M  3
#define Main_Frequency_20M  4
#define Main_Frequency_24M  5
#define Main_Frequency_28M  6
#define Main_Frequency_32M  7
#define Main_Frequency_36M  8
#define Main_Frequency_40M  9
#define Main_Frequency_44M  10
#define Main_Frequency_48M  11
#define Main_Frequency_52M  12
#define Main_Frequency_56M  13
#define Main_Frequency_60M  14
#define Main_Frequency_64M  15
#define Main_Frequency_68M  16
#define Main_Frequency_72M  17
#define Main_Frequency_76M  18
#define Main_Frequency_80M  19
#define Main_Frequency_84M  20
#define Main_Frequency_88M  21
#define Main_Frequency_92M  22
#define Main_Frequency_96M  23
#define Main_Frequency_100M  24
#define Main_Frequency_104M  25
#define Main_Frequency_108M  26
#define Main_Frequency_112M  27
#define Main_Frequency_116M  28
#define Main_Frequency_120M  29
#define Main_Frequency_124M  30
#define Main_Frequency_128M  31
#define Main_Frequency_132M  32
#define Main_Frequency_136M  33
#define Main_Frequency_140M  34
#define Main_Frequency_144M  35
    


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
extern _stClkPara gstClkPara;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
extern void InitMcu_Nvic(void);
extern void InitMcu_Clock(void);
extern void InitMcu_Wdg(void);
extern void InitMcu_Gpio(void);
extern void InitMcu_CompTimerRun(void);
extern void InitMcu_CompPwm(void);
extern void InitMcu_CompPwmEn(void);
extern void InitMcu_CompPwmDis(void);
extern void InitMcu_Adc(uint16_t u16SampleFreq);
extern void InitLedPort(void);
extern void Swwdg_Feed(void);
extern void Hwwdg_Feed(uint8_t u8ClearPattern1, uint8_t u8ClearPattern2);

// ----------------
// configure UART
// ----------------

//void ConfUart0(stc_uart0_cfg_t *pUserPara);
//boolean_t SetUart0(stc_uart0_cfg_t *pUserPara);
//boolean_t InitMcu_Uart0(void);
void InitMcu_Basetimer(void);


#endif /* __INIT_MCU_H__ */

