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
/** \file CustomerInterface.c
 **
 ** Add description here...
 **
 ** History:
 **   - 2013-12-22  0.1.0  Micheal.Yang  First version 
 *****************************************************************************/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "CustomerInterface.h"
#include "InitMcu.h"
#include "base_types.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/******************************************************************************
 * switch paramerters - PFC and compressor
 ******************************************************************************/
uint8_t Comp_u8FreqCtrlEnable           = 1;    // 1: enable

CUSTOMER_PARA  st_CustomerPara;

void InitMotorPara(void)
{
    st_CustomerPara.Comp_u32PolePairs			= 4;//3
    st_CustomerPara.Comp_f32L					= 242;//146;  //mH

    st_CustomerPara.Comp_f32Res					= 33;
    st_CustomerPara.Comp_f32Ke					= 95;      // inductive voltage constant between two phases
    st_CustomerPara.Comp_f32Flux				= 0.36f;	// wb


    /******************************************************************************
     * Motor running parameters - compressor
     ******************************************************************************/

    //
    // Deadtime, carrier frequency, direction and speed
    //
    st_CustomerPara.Comp_f32DeadTimeMicroSec      = 1.5f; // Dead timer us
    st_CustomerPara.Comp_u16CarrierFreq           = 16000; // motor carry frequency (hz)
                                                     
    st_CustomerPara.Comp_u8RunningDirection       = CW;   // motor running direction

    st_CustomerPara.EndFreqMin                    = 4;     //Hz
    st_CustomerPara.EndFreqMax                    = 30;    //Hz

    st_CustomerPara.Comp_u16SpdMax             = 1500;    // motor run maximum speed rpm 9000
    st_CustomerPara.Comp_u16SpdMin             = 300;    // motor run minimum speed rpm 1

    st_CustomerPara.Comp_i32Q8CurrentMax       = Q8(3); // motor phase current peak A
    st_CustomerPara.Comp_i32Q8CurrentLock     = Q8(1.5*1.414); //堵转过流判断点
    st_CustomerPara.Comp_i32Q8CurrentLimit    = Q8(0.8*1.414);   //降低转速电流点

    
    st_CustomerPara.Comp_f32ISampleResistor   = 0.2;
    st_CustomerPara.Comp_f32ISampleRef        = 2.435;    
    st_CustomerPara.Comp_u16VAmplifierFactor  = 133;

    st_CustomerPara.Comp_f32Ikp               = 1.0f;
    st_CustomerPara.Comp_f32Iki               = 0.0005f;

    st_CustomerPara.Comp_f32Skp               = 1.0f;
    st_CustomerPara.Comp_f32Ski               = 0.001; //0.004f;

    st_CustomerPara.Comp_f32Powerkp               = 1.2f;
    st_CustomerPara.Comp_f32Powerki               = 0.25f;
    st_CustomerPara.Comp_f32SpdAccelerationHz     = 2.0f; // acceleration speed
    st_CustomerPara.Comp_f32SpdDecelerationHz     = 2.0f; // deceleration speed
    st_CustomerPara.Comp_i32Q8VbusMax          = Q8(380);
    st_CustomerPara.Comp_i32Q8VbusMin          = Q8(210);
    st_CustomerPara.Comp_i32Q8VbusLimit          = Q8(240);
    st_CustomerPara.Comp_i32Q8VbusLimitRec      = Q8(255);
    st_CustomerPara.Comp_u16StartFreq        = 2;

    st_CustomerPara.Comp_PowerMax            = 120;
    st_CustomerPara.Comp_PowerMin            = 2;
    st_CustomerPara.u32IuvOffsetCheckTimes = 64;
    
    st_CustomerPara.i32CompIuvOffsetMin = 1980;
    st_CustomerPara.i32CompIuvOffsetMax = 2020;
    st_CustomerPara.BoardTempWarn    = 128;   //88℃
}





