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
/** \file base_types.h
 **
 ** Additional base type definitions to stddef.h and stdint.h
 **
 ** History:
 **   - 2013-03-21  1.0  MWi  First version.
 **   - 2013-12-17  1.1  YU   Changed header comment.
 **
 *****************************************************************************/

#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stddef.h>
#include "stdint.h"
  
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#ifndef TRUE
  /** Value is true (boolean_t type) */
  #define TRUE        ((boolean_t) 1)
#endif

#ifndef FALSE
  /** Value is false (boolean_t type) */
  #define FALSE       ((boolean_t) 0)
#endif  

/** Returns the minimum value out of two values */
#define MIN( X, Y )  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define MAX( X, Y )  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define DIM( X )  (sizeof(X) / sizeof(X[0]))

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;
  
/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCCI character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void         (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void         (*func_ptr_arg1_t)(uint8_t);

/** generic error codes */
typedef enum en_result
{
    Ok                          = 0,  ///< No error
    Error                       = 1,  ///< Non-specific error code
    ErrorAddressAlignment       = 2,  ///< Address alignment does not match
    ErrorAccessRights           = 3,  ///< Wrong mode (e.g. user/system) mode is set
    ErrorInvalidParameter       = 4,  ///< Provided parameter is not valid
    ErrorOperationInProgress    = 5,  ///< A conflicting or requested operation is still in progress
    ErrorInvalidMode            = 6,  ///< Operation not allowed in current mode
    ErrorUninitialized          = 7,  ///< Module (or part of it) was not initialized properly
    ErrorBufferFull             = 8,  ///< Circular buffer can not be written because the buffer is full
    ErrorTimeout                = 9,  ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ErrorNotReady               = 10, ///< A requested final state is not reached
    OperationInProgress         = 11  ///< Indicator for operation in progress (e.g. ADC conversion not finished, DMA channel used, etc.)
} en_result_t;
    


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
typedef signed   char       BOOL;   // Boolean
typedef unsigned char       INT8U;  // Unsigned  8 bit quantity
typedef signed   char       INT8S;  // Signed    8 bit quantity
typedef unsigned short      INT16U; // Unsigned 16 bit quantity
typedef signed   short      INT16S; // Signed   16 bit quantity
typedef unsigned int        INT32U; // Unsigned 32 bit quantity
typedef signed   int        INT32S; // Signed   32 bit quantity
typedef unsigned long       LONG32U;// Unsigned 32 bit quantity
typedef signed   long       LONG32S;// Signed   32 bit quantity
typedef unsigned long long  INT64U; // Unsigned 64 bit quantity
typedef signed   long long  INT64S; // signed   64 bit quantity
typedef float               FP32;   // single precision floating point
typedef double              FP64;   // double precision floating point


// Qn format storage type
typedef INT8S  Qn_VAL8;
typedef INT16S Qn_VAL16;
typedef INT32S Qn_VAL32;
typedef INT64S Qn_VAL64;

typedef struct
{
    INT8U bit00 : 1;
    INT8U bit01 : 1;
    INT8U bit02 : 1;
    INT8U bit03 : 1;
    INT8U bit04 : 1;
    INT8U bit05 : 1;
    INT8U bit06 : 1;
    INT8U bit07 : 1;
}_stReg8;

typedef union
{
    INT8U all;
    _stReg8 bit;
}_uniReg8;

typedef struct
{
    INT16U bit00 : 1;
    INT16U bit01 : 1;
    INT16U bit02 : 1;
    INT16U bit03 : 1;
    INT16U bit04 : 1;
    INT16U bit05 : 1;
    INT16U bit06 : 1;
    INT16U bit07 : 1;
    INT16U bit08 : 1;
    INT16U bit09 : 1;
    INT16U bit10 : 1;
    INT16U bit11 : 1;
    INT16U bit12 : 1;
    INT16U bit13 : 1;
    INT16U bit14 : 1;
    INT16U bit15 : 1;
}_stReg16;

typedef union
{
    INT16U all;
    _stReg16 bit;
}_uniReg16;

typedef struct
{
    INT32U bit00 : 1;
    INT32U bit01 : 1;
    INT32U bit02 : 1;
    INT32U bit03 : 1;
    INT32U bit04 : 1;
    INT32U bit05 : 1;
    INT32U bit06 : 1;
    INT32U bit07 : 1;
    INT32U bit08 : 1;
    INT32U bit09 : 1;
    INT32U bit10 : 1;
    INT32U bit11 : 1;
    INT32U bit12 : 1;
    INT32U bit13 : 1;
    INT32U bit14 : 1;
    INT32U bit15 : 1;
    INT32U bit16 : 1;
    INT32U bit17 : 1;
    INT32U bit18 : 1;
    INT32U bit19 : 1;
    INT32U bit20 : 1;
    INT32U bit21 : 1;
    INT32U bit22 : 1;
    INT32U bit23 : 1;
    INT32U bit24 : 1;
    INT32U bit25 : 1;
    INT32U bit26 : 1;
    INT32U bit27 : 1;
    INT32U bit28 : 1;
    INT32U bit29 : 1;
    INT32U bit30 : 1;
    INT32U bit31 : 1;
}_stReg32;

typedef union
{
    INT32U all;
    _stReg32 bit;
}_uniReg32;

//*****************************************************************************
//
// Define global variables
//
//*****************************************************************************

/*
 * Define global variables. Global variables can ONLY be defined for one
 * time in a source file, so we always want to define them in the main.c
 * Defining a macro named DEFINE_GLOBAL_VARS in the main.c to realize only
 * define global variables in main.c.
 */
#ifdef DEFINE_GLOBAL_VARS // Define global variables here

#else // Declare global variables here

#endif

//*****************************************************************************
//
// Define macro functions
//
//*****************************************************************************

#define  Q0(value)  (Qn_VAL32)((value) * 0x00000001)
#define  Q1(value)  (Qn_VAL32)((value) * 0x00000002)
#define  Q2(value)  (Qn_VAL32)((value) * 0x00000004)
#define  Q3(value)  (Qn_VAL32)((value) * 0x00000008)
#define  Q4(value)  (Qn_VAL32)((value) * 0x00000010)
#define  Q5(value)  (Qn_VAL32)((value) * 0x00000020)
#define  Q6(value)  (Qn_VAL32)((value) * 0x00000040)
#define  Q7(value)  (Qn_VAL32)((value) * 0x00000080)
#define  Q8(value)  (Qn_VAL32)((value) * 0x00000100)
#define  Q9(value)  (Qn_VAL32)((value) * 0x00000200)
#define Q10(value)  (Qn_VAL32)((value) * 0x00000400)
#define Q11(value)  (Qn_VAL32)((value) * 0x00000800)
#define Q12(value)  (Qn_VAL32)((value) * 0x00001000)
#define Q13(value)  (Qn_VAL32)((value) * 0x00002000)
#define Q14(value)  (Qn_VAL32)((value) * 0x00004000)
#define Q15(value)  (Qn_VAL32)((value) * 0x00008000)
#define Q16(value)  (Qn_VAL32)((value) * 0x00010000)
#define Q17(value)  (Qn_VAL32)((value) * 0x00020000)
#define Q18(value)  (Qn_VAL32)((value) * 0x00040000)
#define Q19(value)  (Qn_VAL32)((value) * 0x00080000)
#define Q20(value)  (Qn_VAL32)((value) * 0x00100000)
#define Q21(value)  (Qn_VAL32)((value) * 0x00200000)
#define Q22(value)  (Qn_VAL32)((value) * 0x00400000)
#define Q23(value)  (Qn_VAL32)((value) * 0x00800000)
#define Q24(value)  (Qn_VAL32)((value) * 0x01000000)
#define Q25(value)  (Qn_VAL32)((value) * 0x02000000)
#define Q26(value)  (Qn_VAL32)((value) * 0x04000000)
#define Q27(value)  (Qn_VAL32)((value) * 0x08000000)
#define Q28(value)  (Qn_VAL32)((value) * 0x10000000)
#define Q29(value)  (Qn_VAL32)((value) * 0x20000000)
#define Q30(value)  (Qn_VAL32)((value) * 0x40000000)

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/

#endif /* __BASE_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
