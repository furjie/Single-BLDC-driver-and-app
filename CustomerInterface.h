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
/** \file CustomerInterface.h
 **
 ** Add description here...
 **
 ** History:
 **   - 2013-12-22  0.1.0  Micheal.Yang  First version 
 *****************************************************************************/
#ifndef __CUSTOMER_INTERFACE_H__
#define __CUSTOMER_INTERFACE_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "base_types.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#define ADC_VOLT_REF                  5.0f     // Reference voltage for ADC
#define ADC_VALUE_MAX              4096.0f     // 12-bits ADC     
#define ADC_R1                      5100     // 5.1Kµç×è
#define ADC_R2                      12000     // 12Kµç×è   
#define VOLTAGE_TO_SPEED        450
#define VOLTAGE_TO_POWER        30


/******************************************************************************
 * switch paramerters - PFC and compressor
 ******************************************************************************/
typedef struct
{
    INT32U    Comp_u32PolePairs	; //the pole pairs of rotor
    float32_t Comp_f32L	    ; // the d axis reductance
    
    float32_t Comp_f32Res		; // the resistance between two phases
    float32_t Comp_f32Ke		; // inductive voltage constant between two phases
    float32_t Comp_f32Flux	    ; //

    float32_t Comp_f32DeadTimeMicroSec ;
    float32_t Comp_f32ISampleRef;
    float32_t Comp_f32ISampleResistor ;    
    float32_t Comp_u16VAmplifierFactor; 
    
    float32_t Comp_f32Iki            ;    //d axis current PI regulator integral constant
    float32_t Comp_f32Ikp            ;   //d axis current PI regulator proportion constant
    float32_t Comp_f32Skp             ;    //speed PI regulator proportion constant
    float32_t Comp_f32Ski             ; //speed PI regulator integral constant
    
    float32_t Comp_f32Powerkp             ;    //power PI regulator proportion constant
    float32_t Comp_f32Powerki             ; //power PI regulator integral constant
    
    float32_t Comp_f32SpdAccelerationHz  ; // acceleration speed
    float32_t Comp_f32SpdDecelerationHz  ; // deceleration speed
    INT16U    Comp_u16CarrierFreq;      
    INT16U    Comp_u16StartFreq  ;     //Hz

    INT32S    Comp_i32Q8VbusMax            ;     // the maximum value of DC
                                                    // voltage is 400V
    INT32S    Comp_i32Q8VbusMin            ;     // the minimum value of DC
    INT32S    Comp_i32Q8VbusLimit           ;     
    INT32S    Comp_i32Q8VbusLimitRec           ;   
    
    INT32U  u32IuvOffsetCheckTimes;
    
    INT32S  i32CompIuvOffsetMin;
    INT32S  i32CompIuvOffsetMax;
    
    INT32U  Comp_PowerMax;
    INT32U  Comp_PowerMin;
    INT16U  EndFreqMin;
    INT16U  EndFreqMax; 
    INT32S  Comp_i32Q8CurrentMax   ;
    INT32S  Comp_i32Q8CurrentLock  ;
    INT32S  Comp_i32Q8CurrentLimit   ;
    INT16U  Comp_u16SpdMax          ;    
    INT16U  Comp_u16SpdMin          ;
    INT8U   Comp_u8RunningDirection ;
    INT8U   BoardTempWarn ;
}CUSTOMER_PARA;

extern CUSTOMER_PARA  st_CustomerPara;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
extern void InitMotorPara(void);

#endif /* __CUSTOMER_INTERFACE_H__ */



