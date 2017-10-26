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
/** \file Isr.h
 **
 ** Add description here...
 **
 ** History:
 **   - 2013-09-10  0.1.0  Micheal.Yang   First version 
 *****************************************************************************/

#ifndef __ISR_H__
#define __ISR_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "base_types.h"


#define TEMP_AD_NUMBER      32
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
typedef struct
{   
    INT8U SystemTimeCnt;     
    INT32U timeTick4ms;

    INT8U  R8ms;
    INT8U  R20ms;
    INT8U  R248ms;
    INT8U  R100ms;
    INT16U R1s;
    INT16U R3s;
    INT16U R10s;
    INT16U R100s;
    INT16U ROpenLoop;
    
    INT8U  F_4Ms;
    INT8U  F_8Ms;
    INT8U  F_20Ms;
    INT8U  F_248Ms;
    INT8U  F_100Ms;
    INT8U  F_1S;
    INT8U  F_3S;
    INT8U  F_10S;
    INT8U  F_100S;
    INT8U  F_OpenLoop;
}Timer_Para;
extern Timer_Para st_TimerPara;

typedef struct 
{
    INT32U BoardTemperature;     
    INT32U BoardADValueSum;       
    INT32U ADSampleCnt;
}Board_Temp_para;

extern Board_Temp_para st_BoardTemperature;

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
extern volatile INT16U Adc_u16RsltOfAdc[];

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/


#endif /* __ISR_H__ */


