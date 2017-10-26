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

/************************************************************************/
/*                                                                      */
/*  Header File for Device S6E1A1                                       */
/*  Version V1.9                                                        */
/*  Date    2014-05-08                                                  */
/*                                                                      */
/************************************************************************/

/******************************************************************************
 * History
 * Date       Ver Description
 * 2013-12-17 1.0 Initial
 * 2013-12-26 1.1 Revise RDR, TDR register's structure definition of 
 *                MFS (UART, CSIO, LIN, I2C)
 * 2014-01-03 1.2 Revise Flash I/F CRTRMM_TRMM; 
 *                Delete bit-banding definition of Fast IO;
 *                Delete redundant prefix for MFT macro;
 *                Revise GPIO: Py --> Pxy format;
 * 2014-01-07 1.3 Add PRTSL and SCTSL register in ADC12 module;
 * 2014-01-08 1.4 Add IRQCMODE register definition;
 *                Refine naming of IRQ Handler;
 *                Modify MFT_PPG: TRG ==> TRG0, RG6O ==> TRG6O;
 *                Register definition of TTCR0
 * 2014-01-13 1.5 Typo: WCMPRCR ==> WCMPCR in ADC12 module;
 *                Add QPRC0_NF part;
 *                Revise offset address of MFT module from 0x20000 to 0x20100;
 *                Accroding to PM's update, the following content is updated;
 *                CSIO->SSR->AWC is deleted;
 *                CSIO->ESCR->CSFE is added;
 *                CSIO->SCSCR is updated;
 *                CSIO->TBytex is updated;
 *                LIN->SMR->WUCR is deleted;
 * 2014-01-14 1.6 Revise reserved byte in 'MFT_ADCMP_MODULE'
 * 2014-01-26 1.7 Delete bit band definition of FPOER;
 *                Add the bit alias address of Fast GPIO registers;
 * 2014-03-24 1.8 Correct 'stc_mfs_lin_smr_field_t'
 * 2014-05-08 1.9 Correct bit address of Fast GPIO
 *
 ******************************************************************************/

#ifndef _S6E1A1_H_
#define _S6E1A1_H_

#ifdef __cplusplus
extern "C" {
#endif 

#define FM0P_DEVICE_TYPE 1

/******************************************************************************
 * Configuration of the Cortex-M0P Processor and Core Peripherals
 ******************************************************************************/
#define __MPU_PRESENT           0 /* FM0P provide an MPU                           */
#define __NVIC_PRIO_BITS        2 /* FM0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */


/******************************************************************************
 * Interrupt Number Definition
 ******************************************************************************/
typedef enum IRQn
{
    NMI_IRQn          = -14, /*  2 Non Maskable      */
    HardFault_IRQn    = -13, /*  3 Hard Fault        */
    SVC_IRQn          = -5,  /* 11 SV Call           */
    PendSV_IRQn       = -2,  /* 14 Pend SV           */
    SysTick_IRQn      = -1,  /* 15 System Tick       */

    CSV_IRQn          =  0, /* Clock Super Visor                             */
    SWDT_IRQn         =  1, /* Software Watchdog Timer                       */
    LVD_IRQn          =  2, /* Low Voltage Detector                          */
    WFG_DTIF_IRQn     =  3, /* Wave Form Generator / DTIF                    */
    EXINT0_7_IRQn     =  4, /* External Interrupt Request ch.0 to ch.7       */
    /* Reserved       =  5                                                   */
    DTIM_QDU_IRQn     =  6, /* Dual Timer / Quad Decoder                     */
    MFS0RX_IRQn       =  7, /* MultiFunction Serial Reception ch.0           */
    MFS0TX_IRQn       =  8, /* MultiFunction Serial Transmission ch.0        */
    MFS1RX_IRQn       =  9, /* MultiFunction Serial Reception ch.1           */
    MFS1TX_IRQn       = 10, /* MultiFunction Serial Transmission ch.1        */
    /* Reserved       = 11                                                   */
    /* Reserved       = 12                                                   */
    MFS3RX_IRQn       = 13, /* MultiFunction Serial Reception ch.3           */
    MFS3TX_IRQn       = 14, /* MultiFunction Serial Transmission ch.3        */
    /* Reserved       = 15                                                   */
    /* Reserved       = 16                                                   */
    /* Reserved       = 17                                                   */
    /* Reserved       = 18                                                   */
    DMAC0_IRQn        = 19, /* DMAC ch.0                                     */
    DMAC1_IRQn        = 20, /* DMAC ch.1                                     */
    /* Reserved       = 21                                                   */
    /* Reserved       = 22                                                   */
    PPG_IRQn          = 23, /* PPG                                           */
    OSC_PLL_WC_RTC_IRQn = 24, /* OSC / PLL / Watch Counter / RTC             */
    ADC0_IRQn         = 25, /* ADC0                                          */
    /* Reserved       = 26                                                   */
    /* Reserved       = 27                                                   */
    FRTIM_IRQn        = 28, /* Free-run Timer                                */
    INCAP_IRQn        = 29, /* Input Capture                                 */
    OUTCOMP_IRQn      = 30, /* Output Compare                                */
    BTIM0_3_FLASH_IRQn = 31, /* Base Timer ch.0 to ch.3 / Flash              */
} IRQn_Type;


#include <core_cm0plus.h>
#include "system_s6e1a1.h"
#include <stdint.h>

#define SUCCESS  0
#define ERROR    -1

#ifndef NULL
#define NULL 0
#endif


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/******************************************************************************
 * Peripheral register bit fields
 ******************************************************************************/

/******************************************************************************
 * Flash_IF_MODULE
 ******************************************************************************/
/* Flash_IF_MODULE register bit fields */
typedef struct stc_flashif_frwtr_field
{
  __IO  uint8_t RWT        : 2;
} stc_flashif_frwtr_field_t;

typedef struct stc_flashif_fstr_field
{
  __IO  uint8_t RDY        : 1;
  __IO  uint8_t HNG        : 1;
  __IO  uint8_t CERS       : 1;
  __IO  uint8_t ESPS       : 1;
  __IO  uint8_t SERS       : 1;
  __IO  uint8_t PGMS       : 1;
} stc_flashif_fstr_field_t;

typedef struct stc_flashif_fsyndn_field
{
  __IO  uint8_t SD         : 4;
} stc_flashif_fsyndn_field_t;

typedef struct stc_flashif_ficr_field
{
  __IO  uint8_t RDYIE      : 1;
  __IO  uint8_t HANGIE     : 1;
} stc_flashif_ficr_field_t;

typedef struct stc_flashif_fisr_field
{
  __IO  uint8_t RDYIF      : 1;
  __IO  uint8_t HANGIF     : 1;
} stc_flashif_fisr_field_t;

typedef struct stc_flashif_ficlr_field
{
  __IO  uint8_t RDYC       : 1;
  __IO  uint8_t HANGC      : 1;
} stc_flashif_ficlr_field_t;

typedef struct stc_flashif_crtrmm_field
{
  __IO uint32_t TRMM       :10;
       uint32_t RESERVED10 : 6;
  __IO uint32_t TTRMM      : 5;
} stc_flashif_crtrmm_field_t;

/******************************************************************************
* UNIQUE_ID_MODULE
******************************************************************************/
/* Unique ID register bit fields */
typedef struct stc_uid_uidr0_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t UID0       :28;
} stc_uid_uidr0_field_t;

typedef struct stc_unique_id_uidr1_field
{
  __IO uint32_t UID1       :13;
} stc_uid_uidr1_field_t;

/******************************************************************************
 * Clock_Reset_MODULE
 ******************************************************************************/
/* Clock_Reset_MODULE register bit fields */
typedef struct stc_crg_scm_ctl_field
{
  __IO  uint8_t HCRE       : 1;
  __IO  uint8_t MOSCE      : 1;
        uint8_t RESERVED2  : 1;
  __IO  uint8_t SOSCE      : 1;
  __IO  uint8_t PLLE       : 1;
  __IO  uint8_t RCS        : 3;
} stc_crg_scm_ctl_field_t;

typedef struct stc_crg_scm_str_field
{
  __IO  uint8_t HCRDY      : 1;
  __IO  uint8_t MORDY      : 1;
        uint8_t RESERVED2  : 1;
  __IO  uint8_t SORDY      : 1;
  __IO  uint8_t PLRDY      : 1;
  __IO  uint8_t RCM        : 3;
} stc_crg_scm_str_field_t;

typedef struct stc_crg_stb_ctl_field
{
  __IO uint32_t STM        : 2;
  __IO uint32_t DSTM       : 1;
       uint32_t RESERVED3  : 1;
  __IO uint32_t SPL        : 1;
       uint32_t RESERVED5  :11;
  __IO uint32_t KEY        :16;
} stc_crg_stb_ctl_field_t;

typedef struct stc_crg_rst_str_field
{
  __IO uint16_t PONR       : 1;
  __IO uint16_t INITX      : 1;
       uint16_t RESERVED2  : 2;
  __IO uint16_t SWDT       : 1;
  __IO uint16_t HWDT       : 1;
  __IO uint16_t CSVR       : 1;
  __IO uint16_t FCSR       : 1;
  __IO uint16_t SRST       : 1;
} stc_crg_rst_str_field_t;

typedef struct stc_crg_bsc_psr_field
{
  __IO  uint8_t BSR        : 3;
} stc_crg_bsc_psr_field_t;

typedef struct stc_crg_apbc0_psr_field
{
  __IO  uint8_t APBC0      : 2;
} stc_crg_apbc0_psr_field_t;

typedef struct stc_crg_apbc1_psr_field
{
  __IO  uint8_t APBC1      : 2;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t APBC1RST   : 1;
        uint8_t RESERVED5  : 2;
  __IO  uint8_t APBC1EN    : 1;
} stc_crg_apbc1_psr_field_t;

typedef struct stc_crg_swc_psr_field
{
  __IO  uint8_t SWDS       : 2;
        uint8_t RESERVED2  : 5;
  __IO  uint8_t TESTB      : 1;
} stc_crg_swc_psr_field_t;

typedef struct stc_crg_csw_tmr_field
{
  __IO  uint8_t MOWT       : 4;
  __IO  uint8_t SOWT       : 4;
} stc_crg_csw_tmr_field_t;

typedef struct stc_crg_psw_tmr_field
{
  __IO  uint8_t POWT       : 3;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t PINC       : 1;
} stc_crg_psw_tmr_field_t;

typedef struct stc_crg_pll_ctl1_field
{
  __IO  uint8_t PLLM       : 4;
  __IO  uint8_t PLLK       : 4;
} stc_crg_pll_ctl1_field_t;

typedef struct stc_crg_pll_ctl2_field
{
  __IO  uint8_t PLLN       : 6;
} stc_crg_pll_ctl2_field_t;

typedef struct stc_crg_csv_ctl_field
{
  __IO uint16_t MCSVE      : 1;
  __IO uint16_t SCSVE      : 1;
       uint16_t RESERVED2  : 6;
  __IO uint16_t FCSDE      : 1;
  __IO uint16_t FCSRE      : 1;
       uint16_t RESERVED10 : 2;
  __IO uint16_t FCD        : 3;
} stc_crg_csv_ctl_field_t;

typedef struct stc_crg_csv_str_field
{
  __IO  uint8_t MCMF       : 1;
  __IO  uint8_t SCMF       : 1;
} stc_crg_csv_str_field_t;

typedef struct stc_crg_dbwdt_ctl_field
{
        uint8_t RESERVED0  : 5;
  __IO  uint8_t DPSWBE     : 1;
        uint8_t RESERVED6  : 1;
  __IO  uint8_t DPHWBE     : 1;
} stc_crg_dbwdt_ctl_field_t;

typedef struct stc_crg_int_enr_field
{
  __IO  uint8_t MCSE       : 1;
  __IO  uint8_t SCSE       : 1;
  __IO  uint8_t PCSE       : 1;
        uint8_t RESERVED3  : 2;
  __IO  uint8_t FCSE       : 1;
} stc_crg_int_enr_field_t;

typedef struct stc_crg_int_str_field
{
  __IO  uint8_t MCSI       : 1;
  __IO  uint8_t SCSI       : 1;
  __IO  uint8_t PCSI       : 1;
        uint8_t RESERVED3  : 2;
  __IO  uint8_t FCSI       : 1;
} stc_crg_int_str_field_t;

typedef struct stc_crg_int_clr_field
{
  __IO  uint8_t MCSC       : 1;
  __IO  uint8_t SCSC       : 1;
  __IO  uint8_t PCSC       : 1;
        uint8_t RESERVED3  : 2;
  __IO  uint8_t FCSC       : 1;
} stc_crg_int_clr_field_t;

/******************************************************************************
 * HWWDT_MODULE
 ******************************************************************************/
/* HWWDT_MODULE register bit fields */
typedef struct stc_hwwdt_wdg_ctl_field
{
  __IO  uint8_t INTEN      : 1;
  __IO  uint8_t RESEN      : 1;
} stc_hwwdt_wdg_ctl_field_t;

typedef struct stc_hwwdt_wdg_ris_field
{
  __IO  uint8_t RIS        : 1;
} stc_hwwdt_wdg_ris_field_t;

/******************************************************************************
 * SWWDT_MODULE
 ******************************************************************************/
/* SWWDT_MODULE register bit fields */
typedef struct stc_swwdt_wdogcontrol_field
{
  __IO  uint8_t INTEN      : 1;
  __IO  uint8_t RESEN      : 1;
  __IO  uint8_t TWD        : 2;
  __IO  uint8_t SPM        : 1;
} stc_swwdt_wdogcontrol_field_t;

typedef struct stc_swwdt_wdogris_field
{
  __IO  uint8_t RIS        : 1;
} stc_swwdt_wdogris_field_t;

typedef struct stc_swwdt_wdogspmc_field
{
  __IO  uint8_t TGR        : 1;
} stc_swwdt_wdogspmc_field_t;

/******************************************************************************
 * DTIM_MODULE
 ******************************************************************************/
/* DTIM_MODULE register bit fields */
typedef struct stc_dtim_timer1control_field
{
  __IO uint32_t ONESHOT    : 1;
  __IO uint32_t TIMERSIZE  : 1;
  __IO uint32_t TIMERPRE   : 2;
       uint32_t RESERVED4  : 1;
  __IO uint32_t INTENABLE  : 1;
  __IO uint32_t TIMERMODE  : 1;
  __IO uint32_t TIMEREN    : 1;
} stc_dtim_timer1control_field_t;

typedef struct stc_dtim_timer1ris_field
{
  __IO uint32_t TIMER1RIS  : 1;
} stc_dtim_timer1ris_field_t;

typedef struct stc_dtim_timer1mis_field
{
  __IO uint32_t TIMER1MIS  : 1;
} stc_dtim_timer1mis_field_t;

typedef struct stc_dtim_timer2control_field
{
  __IO uint32_t ONESHOT    : 1;
  __IO uint32_t TIMERSIZE  : 1;
  __IO uint32_t TIMERPRE   : 2;
       uint32_t RESERVED4  : 1;
  __IO uint32_t INTENABLE  : 1;
  __IO uint32_t TIMERMODE  : 1;
  __IO uint32_t TIMEREN    : 1;
} stc_dtim_timer2control_field_t;

typedef struct stc_dtim_timer2ris_field
{
  __IO uint32_t TIMER1RIS  : 1;
} stc_dtim_timer2ris_field_t;

typedef struct stc_dtim_timer2mis_field
{
  __IO uint32_t TIMER1MIS  : 1;
} stc_dtim_timer2mis_field_t;

/******************************************************************************
 * MFT_FRT_MODULE
 ******************************************************************************/
/* MFT_FRT_MODULE register bit fields */
typedef struct stc_mft_frt_tcsa0_field
{
  __IO uint16_t CLK        : 4;
  __IO uint16_t SCLR       : 1;
  __IO uint16_t MODE       : 1;
  __IO uint16_t STOP       : 1;
  __IO uint16_t BFE        : 1;
  __IO uint16_t ICRE       : 1;
  __IO uint16_t ICLR       : 1;
       uint16_t RESERVED10 : 3;
  __IO uint16_t IRQZE      : 1;
  __IO uint16_t IRQZF      : 1;
  __IO uint16_t ECKE       : 1;
} stc_mft_frt_tcsa0_field_t;

typedef struct stc_mft_frt_tcsc0_field
{
  __IO uint16_t MSZI       : 4;
  __IO uint16_t MSPI       : 4;
  __IO uint16_t MSZC       : 4;
  __IO uint16_t MSPC       : 4;
} stc_mft_frt_tcsc0_field_t;

typedef struct stc_mft_frt_tccp0_field
{
  __IO uint16_t TCCP       : 16;
} stc_mft_frt_tccp0_field_t;

typedef struct stc_mft_frt_tcsa1_field
{
  __IO uint16_t CLK        : 4;
  __IO uint16_t SCLR       : 1;
  __IO uint16_t MODE       : 1;
  __IO uint16_t STOP       : 1;
  __IO uint16_t BFE        : 1;
  __IO uint16_t ICRE       : 1;
  __IO uint16_t ICLR       : 1;
       uint16_t RESERVED10 : 3;
  __IO uint16_t IRQZE      : 1;
  __IO uint16_t IRQZF      : 1;
  __IO uint16_t ECKE       : 1;
} stc_mft_frt_tcsa1_field_t;

typedef struct stc_mft_frt_tcsc1_field
{
  __IO uint16_t MSZI       : 4;
  __IO uint16_t MSPI       : 4;
  __IO uint16_t MSZC       : 4;
  __IO uint16_t MSPC       : 4;
} stc_mft_frt_tcsc1_field_t;

typedef struct stc_mft_frt_tccp1_field
{
  __IO uint16_t TCCP       : 16;
} stc_mft_frt_tccp1_field_t;

typedef struct stc_mft_frt_tcsa2_field
{
  __IO uint16_t CLK        : 4;
  __IO uint16_t SCLR       : 1;
  __IO uint16_t MODE       : 1;
  __IO uint16_t STOP       : 1;
  __IO uint16_t BFE        : 1;
  __IO uint16_t ICRE       : 1;
  __IO uint16_t ICLR       : 1;
       uint16_t RESERVED10 : 3;
  __IO uint16_t IRQZE      : 1;
  __IO uint16_t IRQZF      : 1;
  __IO uint16_t ECKE       : 1;
} stc_mft_frt_tcsa2_field_t;

typedef struct stc_mft_frt_tcsc2_field
{
  __IO uint16_t MSZI       : 4;
  __IO uint16_t MSPI       : 4;
  __IO uint16_t MSZC4      : 4;
  __IO uint16_t MSPC       : 4;
} stc_mft_frt_tcsc2_field_t;

typedef struct stc_mft_frt_tccp2_field
{
  __IO uint16_t TCCP       : 16;
} stc_mft_frt_tccp2_field_t;

typedef struct stc_mft_frt_tcal_field
{
  __IO uint32_t STOP00     : 1;
  __IO uint32_t STOP01     : 1;
  __IO uint32_t STOP02     : 1;
  __IO uint32_t STOP10     : 1;
  __IO uint32_t STOP11     : 1;
  __IO uint32_t STOP12     : 1;
  __IO uint32_t STOP20     : 1;
  __IO uint32_t STOP21     : 1;
  __IO uint32_t STOP22     : 1;
       uint32_t RESERVED9  : 7;
  __IO uint32_t SCLR00     : 1;
  __IO uint32_t SCLR01     : 1;
  __IO uint32_t SCLR02     : 1;
  __IO uint32_t SCLR10     : 1;
  __IO uint32_t SCLR11     : 1;
  __IO uint32_t SCLR12     : 1;
  __IO uint32_t SCLR20     : 1;
  __IO uint32_t SCLR21     : 1;
  __IO uint32_t SCLR22     : 1;
} stc_mft_frt_tcal_field_t;

/******************************************************************************
 * MFT_OCU_MODULE
 ******************************************************************************/
/* MFT_OCU_MODULE register bit fields */
typedef struct stc_mft_ocu_ocsa10_field
{
  __IO  uint8_t CST0       : 1;
  __IO  uint8_t CST1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t IOE0       : 1;
  __IO  uint8_t IOE1       : 1;
  __IO  uint8_t IOP0       : 1;
  __IO  uint8_t IOP1       : 1;
} stc_mft_ocu_ocsa10_field_t;

typedef struct stc_mft_ocu_ocsb10_field
{
  __IO  uint8_t OTD0       : 1;
  __IO  uint8_t OTD1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t CMOD       : 1;
        uint8_t RESERVED5  : 2;
  __IO  uint8_t FM4        : 1;
} stc_mft_ocu_ocsb10_field_t;

typedef struct stc_mft_ocu_ocsd10_field
{
  __IO  uint8_t OCCP0BUFE  : 2;
  __IO  uint8_t OCCP1BUFE  : 2;
  __IO  uint8_t OCSE0BUFE  : 2;
  __IO  uint8_t OCSE1BUFE  : 2;
} stc_mft_ocu_ocsd10_field_t;

typedef struct stc_mft_ocu_ocsa32_field
{
  __IO  uint8_t CST0       : 1;
  __IO  uint8_t CST1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t IOE0       : 1;
  __IO  uint8_t IOE1       : 1;
  __IO  uint8_t IOP0       : 1;
  __IO  uint8_t IOP1       : 1;
} stc_mft_ocu_ocsa32_field_t;

typedef struct stc_mft_ocu_ocsb32_field
{
  __IO  uint8_t OTD0       : 1;
  __IO  uint8_t OTD1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t CMOD       : 1;
        uint8_t RESERVED5  : 2;
  __IO  uint8_t FM4        : 1;
} stc_mft_ocu_ocsb32_field_t;

typedef struct stc_mft_ocu_ocsd32_field
{
  __IO  uint8_t OCCP0BUFE  : 2;
  __IO  uint8_t OCCP1BUFE  : 2;
  __IO  uint8_t OCSE0BUFE  : 2;
  __IO  uint8_t OCSE1BUFE  : 2;
} stc_mft_ocu_ocsd32_field_t;

typedef struct stc_mft_ocu_ocsa54_field
{
  __IO  uint8_t CST0       : 1;
  __IO  uint8_t CST1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t IOE0       : 1;
  __IO  uint8_t IOE1       : 1;
  __IO  uint8_t IOP0       : 1;
  __IO  uint8_t IOP1       : 1;
} stc_mft_ocu_ocsa54_field_t;

typedef struct stc_mft_ocu_ocsb54_field
{
  __IO  uint8_t OTD0       : 1;
  __IO  uint8_t OTD1       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t CMOD       : 1;
        uint8_t RESERVED5  : 2;
  __IO  uint8_t FM4        : 1;
} stc_mft_ocu_ocsb54_field_t;

typedef struct stc_mft_ocu_ocsd54_field
{
  __IO  uint8_t OCCP0BUFE  : 2;
  __IO  uint8_t OCCP1BUFE  : 2;
  __IO  uint8_t OCSE0BUFE  : 2;
  __IO  uint8_t OCSE1BUFE  : 2;
} stc_mft_ocu_ocsd54_field_t;

typedef struct stc_mft_ocu_ocsc_field
{
  __IO  uint8_t MOD0       : 1;
  __IO  uint8_t MOD1       : 1;
  __IO  uint8_t MOD2       : 1;
  __IO  uint8_t MOD3       : 1;
  __IO  uint8_t MOD4       : 1;
  __IO  uint8_t MOD5       : 1;
} stc_mft_ocu_ocsc_field_t;

typedef struct stc_mft_ocu_ocse0_field
{
  __IO uint16_t OCSE0      : 1;
  __IO uint16_t OCSE1      : 1;
  __IO uint16_t OCSE2      : 1;
  __IO uint16_t OCSE3      : 1;
  __IO uint16_t OCSE4      : 1;
  __IO uint16_t OCSE5      : 1;
  __IO uint16_t OCSE6      : 1;
  __IO uint16_t OCSE7      : 1;
  __IO uint16_t OCSE8      : 1;
  __IO uint16_t OCSE9      : 1;
  __IO uint16_t OCSE10     : 1;
  __IO uint16_t OCSE11     : 1;
  __IO uint16_t OCSE12     : 1;
  __IO uint16_t OCSE13     : 1;
  __IO uint16_t OCSE14     : 1;
  __IO uint16_t OCSE15     : 1;
} stc_mft_ocu_ocse0_field_t;

typedef struct stc_mft_ocu_ocse1_field
{
  __IO uint32_t OCSE0      : 1;
  __IO uint32_t OCSE1      : 1;
  __IO uint32_t OCSE2      : 1;
  __IO uint32_t OCSE3      : 1;
  __IO uint32_t OCSE4      : 1;
  __IO uint32_t OCSE5      : 1;
  __IO uint32_t OCSE6      : 1;
  __IO uint32_t OCSE7      : 1;
  __IO uint32_t OCSE8      : 1;
  __IO uint32_t OCSE9      : 1;
  __IO uint32_t OCSE10     : 1;
  __IO uint32_t OCSE11     : 1;
  __IO uint32_t OCSE12     : 1;
  __IO uint32_t OCSE13     : 1;
  __IO uint32_t OCSE14     : 1;
  __IO uint32_t OCSE15     : 1;
  __IO uint32_t OCSE16     : 1;
  __IO uint32_t OCSE17     : 1;
  __IO uint32_t OCSE18     : 1;
  __IO uint32_t OCSE19     : 1;
  __IO uint32_t OCSE20     : 1;
  __IO uint32_t OCSE21     : 1;
  __IO uint32_t OCSE22     : 1;
  __IO uint32_t OCSE23     : 1;
  __IO uint32_t OCSE24     : 1;
  __IO uint32_t OCSE25     : 1;
  __IO uint32_t OCSE26     : 1;
  __IO uint32_t OCSE27     : 1;
  __IO uint32_t OCSE28     : 1;
  __IO uint32_t OCSE29     : 1;
  __IO uint32_t OCSE30     : 1;
  __IO uint32_t OCSE31     : 1;
} stc_mft_ocu_ocse1_field_t;

typedef struct stc_mft_ocu_ocse2_field
{
  __IO uint16_t OCSE0      : 1;
  __IO uint16_t OCSE1      : 1;
  __IO uint16_t OCSE2      : 1;
  __IO uint16_t OCSE3      : 1;
  __IO uint16_t OCSE4      : 1;
  __IO uint16_t OCSE5      : 1;
  __IO uint16_t OCSE6      : 1;
  __IO uint16_t OCSE7      : 1;
  __IO uint16_t OCSE8      : 1;
  __IO uint16_t OCSE9      : 1;
  __IO uint16_t OCSE10     : 1;
  __IO uint16_t OCSE11     : 1;
  __IO uint16_t OCSE12     : 1;
  __IO uint16_t OCSE13     : 1;
  __IO uint16_t OCSE14     : 1;
  __IO uint16_t OCSE15     : 1;
} stc_mft_ocu_ocse2_field_t;

typedef struct stc_mft_ocu_ocse3_field
{
  __IO uint32_t OCSE0      : 1;
  __IO uint32_t OCSE1      : 1;
  __IO uint32_t OCSE2      : 1;
  __IO uint32_t OCSE3      : 1;
  __IO uint32_t OCSE4      : 1;
  __IO uint32_t OCSE5      : 1;
  __IO uint32_t OCSE6      : 1;
  __IO uint32_t OCSE7      : 1;
  __IO uint32_t OCSE8      : 1;
  __IO uint32_t OCSE9      : 1;
  __IO uint32_t OCSE10     : 1;
  __IO uint32_t OCSE11     : 1;
  __IO uint32_t OCSE12     : 1;
  __IO uint32_t OCSE13     : 1;
  __IO uint32_t OCSE14     : 1;
  __IO uint32_t OCSE15     : 1;
  __IO uint32_t OCSE16     : 1;
  __IO uint32_t OCSE17     : 1;
  __IO uint32_t OCSE18     : 1;
  __IO uint32_t OCSE19     : 1;
  __IO uint32_t OCSE20     : 1;
  __IO uint32_t OCSE21     : 1;
  __IO uint32_t OCSE22     : 1;
  __IO uint32_t OCSE23     : 1;
  __IO uint32_t OCSE24     : 1;
  __IO uint32_t OCSE25     : 1;
  __IO uint32_t OCSE26     : 1;
  __IO uint32_t OCSE27     : 1;
  __IO uint32_t OCSE28     : 1;
  __IO uint32_t OCSE29     : 1;
  __IO uint32_t OCSE30     : 1;
  __IO uint32_t OCSE31     : 1;
} stc_mft_ocu_ocse3_field_t;

typedef struct stc_mft_ocu_ocse4_field
{
  __IO uint16_t OCSE0      : 1;
  __IO uint16_t OCSE1      : 1;
  __IO uint16_t OCSE2      : 1;
  __IO uint16_t OCSE3      : 1;
  __IO uint16_t OCSE4      : 1;
  __IO uint16_t OCSE5      : 1;
  __IO uint16_t OCSE6      : 1;
  __IO uint16_t OCSE7      : 1;
  __IO uint16_t OCSE8      : 1;
  __IO uint16_t OCSE9      : 1;
  __IO uint16_t OCSE10     : 1;
  __IO uint16_t OCSE11     : 1;
  __IO uint16_t OCSE12     : 1;
  __IO uint16_t OCSE13     : 1;
  __IO uint16_t OCSE14     : 1;
  __IO uint16_t OCSE15     : 1;
} stc_mft_ocu_ocse4_field_t;

typedef struct stc_mft_ocu_ocse5_field
{
  __IO uint32_t OCSE0      : 1;
  __IO uint32_t OCSE1      : 1;
  __IO uint32_t OCSE2      : 1;
  __IO uint32_t OCSE3      : 1;
  __IO uint32_t OCSE4      : 1;
  __IO uint32_t OCSE5      : 1;
  __IO uint32_t OCSE6      : 1;
  __IO uint32_t OCSE7      : 1;
  __IO uint32_t OCSE8      : 1;
  __IO uint32_t OCSE9      : 1;
  __IO uint32_t OCSE10     : 1;
  __IO uint32_t OCSE11     : 1;
  __IO uint32_t OCSE12     : 1;
  __IO uint32_t OCSE13     : 1;
  __IO uint32_t OCSE14     : 1;
  __IO uint32_t OCSE15     : 1;
  __IO uint32_t OCSE16     : 1;
  __IO uint32_t OCSE17     : 1;
  __IO uint32_t OCSE18     : 1;
  __IO uint32_t OCSE19     : 1;
  __IO uint32_t OCSE20     : 1;
  __IO uint32_t OCSE21     : 1;
  __IO uint32_t OCSE22     : 1;
  __IO uint32_t OCSE23     : 1;
  __IO uint32_t OCSE24     : 1;
  __IO uint32_t OCSE25     : 1;
  __IO uint32_t OCSE26     : 1;
  __IO uint32_t OCSE27     : 1;
  __IO uint32_t OCSE28     : 1;
  __IO uint32_t OCSE29     : 1;
  __IO uint32_t OCSE30     : 1;
  __IO uint32_t OCSE31     : 1;
} stc_mft_ocu_ocse5_field_t;


typedef struct stc_mft_ocu_ocfs10_field
{
  __IO  uint8_t FSO0       : 4;
  __IO  uint8_t FSO1       : 4;
} stc_mft_ocu_ocfs10_field_t;

typedef struct stc_mft_ocu_ocfs32_field
{
  __IO  uint8_t FSO0       : 4;
  __IO  uint8_t FSO1       : 4;
} stc_mft_ocu_ocfs32_field_t;

typedef struct stc_mft_ocu_ocfs54_field
{
  __IO  uint8_t FSO0       : 4;
  __IO  uint8_t FSO1       : 4;
} stc_mft_ocu_ocfs54_field_t;

/******************************************************************************
 * MFT_WFG_MODULE
 ******************************************************************************/
/* MFT_WFG_MODULE register bit fields */
typedef struct stc_mft_wfg_wfsa10_field
{
  __IO uint16_t DCK        : 3;
  __IO uint16_t TMD        : 3;
  __IO uint16_t GTEN       : 2;
  __IO uint16_t PSEL       : 2;
  __IO uint16_t PGEN       : 2;
  __IO uint16_t DMOD       : 2;
} stc_mft_wfg_wfsa10_field_t;

typedef struct stc_mft_wfg_wfsa32_field
{
  __IO uint16_t DCK        : 3;
  __IO uint16_t TMD        : 3;
  __IO uint16_t GTEN       : 2;
  __IO uint16_t PSEL       : 2;
  __IO uint16_t PGEN       : 2;
  __IO uint16_t DMOD       : 2;
} stc_mft_wfg_wfsa32_field_t;

typedef struct stc_mft_wfg_wfsa54_field
{
  __IO uint16_t DCK        : 3;
  __IO uint16_t TMD        : 3;
  __IO uint16_t GTEN       : 2;
  __IO uint16_t PSEL       : 2;
  __IO uint16_t PGEN       : 2;
  __IO uint16_t DMOD       : 2;
} stc_mft_wfg_wfsa54_field_t;

typedef struct stc_mft_wfg_wfir_field
{
  __IO uint16_t DTIFA      : 1;
  __IO uint16_t DTICA      : 1;
  __IO uint16_t DTIFB      : 1;
  __IO uint16_t DTICB      : 1;
  __IO uint16_t TMIF10     : 1;
  __IO uint16_t TMIC10     : 1;
  __IO uint16_t TMIE10     : 1;
  __IO uint16_t TMIS10     : 1;
  __IO uint16_t TMIF32     : 1;
  __IO uint16_t TMIC32     : 1;
  __IO uint16_t TMIE32     : 1;
  __IO uint16_t TMIS32     : 1;
  __IO uint16_t TMIF54     : 1;
  __IO uint16_t TMIC54     : 1;
  __IO uint16_t TMIE54     : 1;
  __IO uint16_t TMIS54     : 1;
} stc_mft_wfg_wfir_field_t;

typedef struct stc_mft_wfg_nzcl_field
{
  __IO uint16_t DTIEA      : 1;
  __IO uint16_t NWS        : 3;
  __IO uint16_t SDTI       : 1;
  __IO uint16_t DTIEB      : 1;
       uint16_t RESERVED6  : 2;
  __IO uint16_t DIMA       : 1;
  __IO uint16_t DIMB       : 1;
       uint16_t RESERVED10 : 2;
  __IO uint16_t WIM10      : 1;
  __IO uint16_t WIM32      : 1;
  __IO uint16_t WIM54      : 1;
} stc_mft_wfg_nzcl_field_t;

/******************************************************************************
 * MFT_ICU_MODULE
 ******************************************************************************/
/* MFT_ICU_MODULE register bit fields */
typedef struct stc_mft_icu_icfs10_field
{
  __IO  uint8_t FSI0       : 4;
  __IO  uint8_t FSI1       : 4;
} stc_mft_icu_icfs10_field_t;

typedef struct stc_mft_icu_icfs32_field
{
  __IO  uint8_t FSI0       : 4;
  __IO  uint8_t FSI1       : 4;
} stc_mft_icu_icfs32_field_t;

typedef struct stc_mft_icu_icsa10_field
{
  __IO  uint8_t EG0        : 2;
  __IO  uint8_t EG1        : 2;
  __IO  uint8_t ICE0       : 1;
  __IO  uint8_t ICE1       : 1;
  __IO  uint8_t ICP0       : 1;
  __IO  uint8_t ICP1       : 1;
} stc_mft_icu_icsa10_field_t;

typedef struct stc_mft_icu_icsb10_field
{
  __IO  uint8_t IEI0       : 1;
  __IO  uint8_t IEI1       : 1;
} stc_mft_icu_icsb10_field_t;

typedef struct stc_mft_icu_icsa32_field
{
  __IO  uint8_t EG0        : 2;
  __IO  uint8_t EG1        : 2;
  __IO  uint8_t ICE0       : 1;
  __IO  uint8_t ICE1       : 1;
  __IO  uint8_t ICP0       : 1;
  __IO  uint8_t ICP1       : 1;
} stc_mft_icu_icsa32_field_t;

typedef struct stc_mft_icu_icsb32_field
{
  __IO  uint8_t IEI0       : 1;
  __IO  uint8_t IEI1       : 1;
} stc_mft_icu_icsb32_field_t;

/******************************************************************************
 * MFT_ADCMP_MODULE
 ******************************************************************************/
/* MFT_ADCMP_MODULE register bit fields */
typedef struct stc_mft_adcmp_acfs10_field
{
  __IO  uint8_t FSA0       : 4;
  __IO  uint8_t FSA1       : 4;
} stc_mft_adcmp_acfs10_field_t;

typedef struct stc_mft_adcmp_acfs32_field
{
  __IO  uint8_t FSA0       : 4;
  __IO  uint8_t FSA1       : 4;
} stc_mft_adcmp_acfs32_field_t;

typedef struct stc_mft_adcmp_acfs54_field
{
  __IO  uint8_t FSA0       : 4;
  __IO  uint8_t FSA1       : 4;
} stc_mft_adcmp_acfs54_field_t;

typedef struct stc_mft_adcmp_acmp0_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp0_field_t;

typedef struct stc_mft_adcmp_acmp1_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp1_field_t;

typedef struct stc_mft_adcmp_acmp2_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp2_field_t;

typedef struct stc_mft_adcmp_acmp3_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp3_field_t;

typedef struct stc_mft_adcmp_acmp4_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp4_field_t;

typedef struct stc_mft_adcmp_acmp5_field
{
  __IO uint16_t ACMP       :16;
} stc_mft_adcmp_acmp5_field_t;

typedef struct stc_mft_adcmp_acsa_field
{
  __IO uint16_t CE10      : 2;
  __IO uint16_t CE32      : 2;
  __IO uint16_t CE54      : 2;
       uint16_t RESERVED6  : 2;
  __IO uint16_t SEL10     : 2;
  __IO uint16_t SEL32     : 2;
  __IO uint16_t SEL54     : 2;
} stc_mft_adcmp_acsa_field_t;

typedef struct stc_mft_adcmp_acsc0_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc0_field_t;

typedef struct stc_mft_adcmp_acsd0_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd0_field_t;

typedef struct stc_mft_adcmp_acsc1_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc1_field_t;

typedef struct stc_mft_adcmp_acsd1_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd1_field_t;

typedef struct stc_mft_adcmp_acsc2_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc2_field_t;

typedef struct stc_mft_adcmp_acsd2_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd2_field_t;

typedef struct stc_mft_adcmp_acsc3_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc3_field_t;

typedef struct stc_mft_adcmp_acsd3_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd3_field_t;

typedef struct stc_mft_adcmp_acsc4_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc4_field_t;

typedef struct stc_mft_adcmp_acsd4_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd4_field_t;

typedef struct stc_mft_adcmp_acsc5_field
{
  __IO  uint8_t BUFE       : 2;
  __IO  uint8_t ADSEL      : 3;
} stc_mft_adcmp_acsc5_field_t;

typedef struct stc_mft_adcmp_acsd5_field
{
  __IO  uint8_t AMOD       : 1;
  __IO  uint8_t OCUS       : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t DE         : 1;
  __IO  uint8_t PE         : 1;
  __IO  uint8_t UE         : 1;
  __IO  uint8_t ZE         : 1;
} stc_mft_adcmp_acsd5_field_t;

/******************************************************************************
 * MFT_PPG_MODULE
 ******************************************************************************/
/* MFT_PPG_MODULE register bit fields */
typedef struct stc_mft_ppg_ttcr0_field
{
  __IO uint8_t STR0       : 1;
  __IO uint8_t MONI0      : 1;
  __IO uint8_t CS00       : 1;
  __IO uint8_t CS01       : 1;
  __IO uint8_t TRG0O      : 1;
  __IO uint8_t TRG2O      : 1;
  __IO uint8_t TRG4O      : 1;
  __IO uint8_t RG6O       : 1;
} stc_mft_ppg_ttcr0_field_t;

typedef struct stc_mft_ppg_ttcr1_field
{
  __IO uint8_t STR1       : 1;
  __IO uint8_t MONI1      : 1;
  __IO uint8_t CS10       : 1;
  __IO uint8_t CS11       : 1;
  __IO uint8_t TRG1O      : 1;
  __IO uint8_t TRG3O      : 1;
  __IO uint8_t TRG5O      : 1;
  __IO uint8_t TRG7O      : 1;
} stc_mft_ppg_ttcr1_field_t;

typedef struct stc_mft_ppg_ttcr2_field
{
  __IO uint8_t STR2       : 1;
  __IO uint8_t MONI2      : 1;
  __IO uint8_t CS20       : 1;
  __IO uint8_t CS21       : 1;
  __IO uint8_t TRG16O     : 1;
  __IO uint8_t TRG18O     : 1;
  __IO uint8_t TRG20O     : 1;
  __IO uint8_t TRG22O     : 1;
} stc_mft_ppg_ttcr2_field_t;

typedef struct stc_mft_ppg_trg0_field
{
  __IO uint16_t PEN00      : 1;
  __IO uint16_t PEN01      : 1;
  __IO uint16_t PEN02      : 1;
  __IO uint16_t PEN03      : 1;
  __IO uint16_t PEN04      : 1;
  __IO uint16_t PEN05      : 1;
  __IO uint16_t PEN06      : 1;
  __IO uint16_t PEN07      : 1;
  __IO uint16_t PEN08      : 1;
  __IO uint16_t PEN09      : 1;
  __IO uint16_t PEN10      : 1;
  __IO uint16_t PEN11      : 1;
  __IO uint16_t PEN12      : 1;
  __IO uint16_t PEN13      : 1;
  __IO uint16_t PEN14      : 1;
  __IO uint16_t PEN15      : 1;
} stc_mft_ppg_trg0_field_t;

typedef struct stc_mft_ppg_revc0_field
{
  __IO uint16_t REV00      : 1;
  __IO uint16_t REV01      : 1;
  __IO uint16_t REV02      : 1;
  __IO uint16_t REV03      : 1;
  __IO uint16_t REV04      : 1;
  __IO uint16_t REV05      : 1;
  __IO uint16_t REV06      : 1;
  __IO uint16_t REV07      : 1;
  __IO uint16_t REV08      : 1;
  __IO uint16_t REV09      : 1;
  __IO uint16_t REV10      : 1;
  __IO uint16_t REV11      : 1;
  __IO uint16_t REV12      : 1;
  __IO uint16_t REV13      : 1;
  __IO uint16_t REV14      : 1;
  __IO uint16_t REV15      : 1;
} stc_mft_ppg_revc0_field_t;

typedef struct stc_mft_ppg_trg1_field
{
  __IO uint16_t PEN16      : 1;
  __IO uint16_t PEN17      : 1;
  __IO uint16_t PEN18      : 1;
  __IO uint16_t PEN19      : 1;
  __IO uint16_t PEN20      : 1;
  __IO uint16_t PEN21      : 1;
  __IO uint16_t PEN22      : 1;
  __IO uint16_t PEN23      : 1;
} stc_mft_ppg_trg1_field_t;

typedef struct stc_mft_ppg_revc1_field
{
  __IO uint16_t REV16      : 1;
  __IO uint16_t REV17      : 1;
  __IO uint16_t REV18      : 1;
  __IO uint16_t REV19      : 1;
  __IO uint16_t REV20      : 1;
  __IO uint16_t REV21      : 1;
  __IO uint16_t REV22      : 1;
  __IO uint16_t REV23      : 1;
} stc_mft_ppg_revc1_field_t;

typedef struct stc_mft_ppg_ppgc1_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc1_field_t;

typedef struct stc_mft_ppg_ppgc0_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc0_field_t;

typedef struct stc_mft_ppg_ppgc3_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc3_field_t;

typedef struct stc_mft_ppg_ppgc2_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc2_field_t;

typedef struct stc_mft_ppg_prll0_field
{
  __IO  uint8_t PRLL0      : 1;
  __IO  uint8_t PRLL1      : 1;
  __IO  uint8_t PRLL2      : 1;
  __IO  uint8_t PRLL3      : 1;
  __IO  uint8_t PRLL4      : 1;
  __IO  uint8_t PRLL5      : 1;
  __IO  uint8_t PRLL6      : 1;
  __IO  uint8_t PRLL7      : 1;
} stc_mft_ppg_prll0_field_t;

typedef struct stc_mft_ppg_prlh0_field
{
  __IO  uint8_t PRLH0      : 1;
  __IO  uint8_t PRLH1      : 1;
  __IO  uint8_t PRLH2      : 1;
  __IO  uint8_t PRLH3      : 1;
  __IO  uint8_t PRLH4      : 1;
  __IO  uint8_t PRLH5      : 1;
  __IO  uint8_t PRLH6      : 1;
  __IO  uint8_t PRLH7      : 1;
} stc_mft_ppg_prlh0_field_t;

typedef struct stc_mft_ppg_prll1_field
{
  __IO  uint8_t PRLL0      : 1;
  __IO  uint8_t PRLL1      : 1;
  __IO  uint8_t PRLL2      : 1;
  __IO  uint8_t PRLL3      : 1;
  __IO  uint8_t PRLL4      : 1;
  __IO  uint8_t PRLL5      : 1;
  __IO  uint8_t PRLL6      : 1;
  __IO  uint8_t PRLL7      : 1;
} stc_mft_ppg_prll1_field_t;

typedef struct stc_mft_ppg_prlh1_field
{
  __IO  uint8_t PRLH0      : 1;
  __IO  uint8_t PRLH1      : 1;
  __IO  uint8_t PRLH2      : 1;
  __IO  uint8_t PRLH3      : 1;
  __IO  uint8_t PRLH4      : 1;
  __IO  uint8_t PRLH5      : 1;
  __IO  uint8_t PRLH6      : 1;
  __IO  uint8_t PRLH7      : 1;
} stc_mft_ppg_prlh1_field_t;

typedef struct stc_mft_ppg_prll2_field
{
  __IO  uint8_t PRLL0      : 1;
  __IO  uint8_t PRLL1      : 1;
  __IO  uint8_t PRLL2      : 1;
  __IO  uint8_t PRLL3      : 1;
  __IO  uint8_t PRLL4      : 1;
  __IO  uint8_t PRLL5      : 1;
  __IO  uint8_t PRLL6      : 1;
  __IO  uint8_t PRLL7      : 1;
} stc_mft_ppg_prll2_field_t;

typedef struct stc_mft_ppg_prlh2_field
{
  __IO  uint8_t PRLH0      : 1;
  __IO  uint8_t PRLH1      : 1;
  __IO  uint8_t PRLH2      : 1;
  __IO  uint8_t PRLH3      : 1;
  __IO  uint8_t PRLH4      : 1;
  __IO  uint8_t PRLH5      : 1;
  __IO  uint8_t PRLH6      : 1;
  __IO  uint8_t PRLH7      : 1;
} stc_mft_ppg_prlh2_field_t;

typedef struct stc_mft_ppg_prll3_field
{
  __IO  uint8_t PRLL0      : 1;
  __IO  uint8_t PRLL1      : 1;
  __IO  uint8_t PRLL2      : 1;
  __IO  uint8_t PRLL3      : 1;
  __IO  uint8_t PRLL4      : 1;
  __IO  uint8_t PRLL5      : 1;
  __IO  uint8_t PRLL6      : 1;
  __IO  uint8_t PRLL7      : 1;
} stc_mft_ppg_prll3_field_t;

typedef struct stc_mft_ppg_prlh3_field
{
  __IO  uint8_t PRLH0      : 1;
  __IO  uint8_t PRLH1      : 1;
  __IO  uint8_t PRLH2      : 1;
  __IO  uint8_t PRLH3      : 1;
  __IO  uint8_t PRLH4      : 1;
  __IO  uint8_t PRLH5      : 1;
  __IO  uint8_t PRLH6      : 1;
  __IO  uint8_t PRLH7      : 1;
} stc_mft_ppg_prlh3_field_t;

typedef struct stc_mft_ppg_gatec0_field
{
  __IO  uint8_t EDGE0      : 1;
  __IO  uint8_t STRG0      : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE2      : 1;
  __IO  uint8_t STRG2      : 1;
} stc_mft_ppg_gatec0_field_t;

typedef struct stc_mft_ppg_ppgc5_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc5_field_t;

typedef struct stc_mft_ppg_ppgc4_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc4_field_t;

typedef struct stc_mft_ppg_ppgc7_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc7_field_t;

typedef struct stc_mft_ppg_ppgc6_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc6_field_t;

typedef struct stc_mft_ppg_prll4_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll4_field_t;

typedef struct stc_mft_ppg_prlh4_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh4_field_t;

typedef struct stc_mft_ppg_prll5_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll5_field_t;

typedef struct stc_mft_ppg_prlh5_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh5_field_t;

typedef struct stc_mft_ppg_prll6_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll6_field_t;

typedef struct stc_mft_ppg_prlh6_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh6_field_t;

typedef struct stc_mft_ppg_prll7_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll7_field_t;

typedef struct stc_mft_ppg_prlh7_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh7_field_t;

typedef struct stc_mft_ppg_gatec4_field
{
  __IO  uint8_t EDGE4      : 1;
  __IO  uint8_t STRG4      : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE6      : 1;
  __IO  uint8_t STRG6      : 1;
} stc_mft_ppg_gatec4_field_t;

typedef struct stc_mft_ppg_ppgc9_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc9_field_t;

typedef struct stc_mft_ppg_ppgc8_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc8_field_t;

typedef struct stc_mft_ppg_ppgc11_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc11_field_t;

typedef struct stc_mft_ppg_ppgc10_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc10_field_t;

typedef struct stc_mft_ppg_prll8_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll8_field_t;

typedef struct stc_mft_ppg_prlh8_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh8_field_t;

typedef struct stc_mft_ppg_prll9_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll9_field_t;

typedef struct stc_mft_ppg_prlh9_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh9_field_t;

typedef struct stc_mft_ppg_prll10_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll10_field_t;

typedef struct stc_mft_ppg_prlh10_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh10_field_t;

typedef struct stc_mft_ppg_prll11_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll11_field_t;

typedef struct stc_mft_ppg_prlh11_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh11_field_t;

typedef struct stc_mft_ppg_gatec8_field
{
  __IO  uint8_t EDGE8      : 1;
  __IO  uint8_t STRG8      : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE10     : 1;
  __IO  uint8_t STRG10     : 1;
} stc_mft_ppg_gatec8_field_t;

typedef struct stc_mft_ppg_ppgc13_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc13_field_t;

typedef struct stc_mft_ppg_ppgc12_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc12_field_t;

typedef struct stc_mft_ppg_ppgc15_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc15_field_t;

typedef struct stc_mft_ppg_ppgc14_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc14_field_t;

typedef struct stc_mft_ppg_prll12_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll12_field_t;

typedef struct stc_mft_ppg_prlh12_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh12_field_t;

typedef struct stc_mft_ppg_prll13_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll13_field_t;

typedef struct stc_mft_ppg_prlh13_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh13_field_t;

typedef struct stc_mft_ppg_prll14_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll14_field_t;

typedef struct stc_mft_ppg_prlh14_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh14_field_t;

typedef struct stc_mft_ppg_prll15_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll15_field_t;

typedef struct stc_mft_ppg_prlh15_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh15_field_t;

typedef struct stc_mft_ppg_gatec12_field
{
  __IO  uint8_t EDGE12     : 1;
  __IO  uint8_t STRG12     : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE14     : 1;
  __IO  uint8_t STRG14     : 1;
} stc_mft_ppg_gatec12_field_t;

typedef struct stc_mft_ppg_ppgc17_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc17_field_t;

typedef struct stc_mft_ppg_ppgc16_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc16_field_t;

typedef struct stc_mft_ppg_ppgc19_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc19_field_t;

typedef struct stc_mft_ppg_ppgc18_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc18_field_t;

typedef struct stc_mft_ppg_prll16_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll16_field_t;

typedef struct stc_mft_ppg_prlh16_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh16_field_t;

typedef struct stc_mft_ppg_prll17_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll17_field_t;

typedef struct stc_mft_ppg_prlh17_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh17_field_t;

typedef struct stc_mft_ppg_prll18_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll18_field_t;

typedef struct stc_mft_ppg_prlh18_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh18_field_t;

typedef struct stc_mft_ppg_prll19_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll19_field_t;

typedef struct stc_mft_ppg_prlh19_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh19_field_t;

typedef struct stc_mft_ppg_gatec16_field
{
  __IO  uint8_t EDGE16     : 1;
  __IO  uint8_t STRG16     : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE18     : 1;
  __IO  uint8_t STRG18     : 1;
} stc_mft_ppg_gatec16_field_t;

typedef struct stc_mft_ppg_ppgc21_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc21_field_t;

typedef struct stc_mft_ppg_ppgc20_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc20_field_t;

typedef struct stc_mft_ppg_ppgc23_field
{
        uint8_t RESERVED0  : 3;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc23_field_t;

typedef struct stc_mft_ppg_ppgc22_field
{
  __IO  uint8_t TTRG       : 1;
  __IO  uint8_t MD         : 2;
  __IO  uint8_t PCS        : 2;
  __IO  uint8_t INTM       : 1;
  __IO  uint8_t PUF        : 1;
  __IO  uint8_t PIE        : 1;
} stc_mft_ppg_ppgc22_field_t;

typedef struct stc_mft_ppg_prll20_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll20_field_t;

typedef struct stc_mft_ppg_prlh20_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh20_field_t;

typedef struct stc_mft_ppg_prll21_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll21_field_t;

typedef struct stc_mft_ppg_prlh21_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh21_field_t;

typedef struct stc_mft_ppg_prll22_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll22_field_t;

typedef struct stc_mft_ppg_prlh22_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh22_field_t;

typedef struct stc_mft_ppg_prll23_field
{
  __IO  uint8_t PRLL       : 8;
} stc_mft_ppg_prll23_field_t;

typedef struct stc_mft_ppg_prlh23_field
{
  __IO  uint8_t PRLH       : 8;
} stc_mft_ppg_prlh23_field_t;

typedef struct stc_mft_ppg_gatec20_field
{
  __IO  uint8_t EDGE20     : 1;
  __IO  uint8_t STRG20     : 1;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t EDGE22     : 1;
  __IO  uint8_t STRG22     : 1;
} stc_mft_ppg_gatec20_field_t;

typedef struct stc_mft_ppg_igbtc_field
{
  __IO  uint8_t IGBTMD     : 1;
  __IO  uint8_t IGTRGLV    : 1;
  __IO  uint8_t IGOSEL     : 2;
  __IO  uint8_t IGNFW      : 3;
  __IO  uint8_t IGATIH     : 1;
} stc_mft_ppg_igbtc_field_t;
/******************************************************************************
 * BT_PPG_MODULE
 ******************************************************************************/
/* BT_PPG_MODULE register bit fields */
typedef struct stc_bt_ppg_tmcr_field
{
  __IO uint16_t STRG       : 1;
  __IO uint16_t CTEN       : 1;
  __IO uint16_t MDSE       : 1;
  __IO uint16_t OSEL       : 1;
  __IO uint16_t FMD        : 3;
       uint16_t RESERVED1  : 1;
  __IO uint16_t EGS        : 2;
  __IO uint16_t PMSK       : 1;
  __IO uint16_t RTGEN      : 1;
  __IO uint16_t CKS        : 3;
} stc_bt_ppg_tmcr_field_t;

typedef struct stc_bt_ppg_stc_field
{
  __IO  uint8_t UDIR       : 1;
        uint8_t RESERVED1  : 1;
  __IO  uint8_t TGIR       : 1;
        uint8_t RESERVED2  : 1;
  __IO  uint8_t UDIE       : 1;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t TGIE       : 1;
} stc_bt_ppg_stc_field_t;

typedef struct stc_bt_ppg_tmcr2_field
{
  __IO  uint8_t CKS3       : 1;
} stc_bt_ppg_tmcr2_field_t;

/******************************************************************************
 * BT_PWM_MODULE
 ******************************************************************************/
/* BT_PWM_MODULE register bit fields */
typedef struct stc_bt_pwm_tmcr_field
{
  __IO uint16_t STRG       : 1;
  __IO uint16_t CTEN       : 1;
  __IO uint16_t MDSE       : 1;
  __IO uint16_t OSEL       : 1;
  __IO uint16_t FMD        : 3;
       uint16_t RESERVED1  : 1;
  __IO uint16_t EGS        : 2;
  __IO uint16_t PMSK       : 1;
  __IO uint16_t RTGEN      : 1;
  __IO uint16_t CKS        : 3;
} stc_bt_pwm_tmcr_field_t;

typedef struct stc_bt_pwm_stc_field
{
  __IO  uint8_t UDIR       : 1;
  __IO  uint8_t DTIR       : 1;
  __IO  uint8_t TGIR       : 1;
        uint8_t RESERVED1  : 1;
  __IO  uint8_t UDIE       : 1;
  __IO  uint8_t DTIE       : 1;
  __IO  uint8_t TGIE       : 1;
} stc_bt_pwm_stc_field_t;

typedef struct stc_bt_pwm_tmcr2_field
{
  __IO  uint8_t CKS3       : 1;
} stc_bt_pwm_tmcr2_field_t;

/******************************************************************************
 * BT_RT_MODULE
 ******************************************************************************/
/* BT_RT_MODULE register bit fields */
typedef struct stc_bt_rt_tmcr_field
{
  __IO uint16_t STRG       : 1;
  __IO uint16_t CTEN       : 1;
  __IO uint16_t MDSE       : 1;
  __IO uint16_t OSEL       : 1;
  __IO uint16_t FMD        : 3;
  __IO uint16_t T32        : 1;
  __IO uint16_t EGS        : 2;
       uint16_t RESERVED1  : 2;
  __IO uint16_t CKS        : 3;
} stc_bt_rt_tmcr_field_t;

typedef struct stc_bt_rt_stc_field
{
  __IO  uint8_t UDIR       : 1;
        uint8_t RESERVED1  : 1;
  __IO  uint8_t TGIR       : 1;
        uint8_t RESERVED2  : 1;
  __IO  uint8_t UDIE       : 1;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t TGIE       : 1;
} stc_bt_rt_stc_field_t;

typedef struct stc_bt_rt_tmcr2_field
{
  __IO  uint8_t CKS3       : 1;
        uint8_t RESERVED1  : 6;
  __IO  uint8_t GATE       : 1;
} stc_bt_rt_tmcr2_field_t;

/******************************************************************************
 * BT_PWC_MODULE
 ******************************************************************************/
/* BT_PWC_MODULE register bit fields */
typedef struct stc_bt_pwc_tmcr_field
{
       uint16_t RESERVED1  : 1;
  __IO uint16_t CTEN       : 1;
  __IO uint16_t MDSE       : 1;
       uint16_t RESERVED2  : 1;
  __IO uint16_t FMD        : 3;
  __IO uint16_t T32        : 1;
  __IO uint16_t EGS        : 3;
       uint16_t RESERVED3  : 1;
  __IO uint16_t CKS        : 3;
} stc_bt_pwc_tmcr_field_t;

typedef struct stc_bt_pwc_stc_field
{
  __IO  uint8_t OVIR       : 1;
        uint8_t RESERVED1  : 1;
  __IO  uint8_t EDIR       : 1;
        uint8_t RESERVED2  : 1;
  __IO  uint8_t OVIE       : 1;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t EDIE       : 1;
  __IO  uint8_t ERR        : 1;
} stc_bt_pwc_stc_field_t;

typedef struct stc_bt_pwc_tmcr2_field
{
  __IO  uint8_t CKS3       : 1;
} stc_bt_pwc_tmcr2_field_t;

/******************************************************************************
 * BTIOSEL03_MODULE
 ******************************************************************************/
/* BTIOSEL03_MODULE register bit fields */
typedef struct stc_btiosel03_btsel0123_field
{
       uint16_t RESERVED0  : 8;
  __IO uint16_t SEL01      : 4;
  __IO uint16_t SEL23      : 4;
} stc_btiosel03_btsel0123_field_t;

/******************************************************************************
 * SBSSR_MODULE
 ******************************************************************************/
/* SBSSR_MODULE register bit fields */
typedef struct stc_sbssr_btsssr_field
{
  __IO uint16_t SSSR0      : 1;
  __IO uint16_t SSSR1      : 1;
  __IO uint16_t SSSR2      : 1;
  __IO uint16_t SSSR3      : 1;
} stc_sbssr_btsssr_field_t;

/******************************************************************************
 * QPRC_MODULE
 ******************************************************************************/
/* QPRC_MODULE register bit fields */
typedef struct stc_qprc0_qicrl_field
{
  __IO  uint8_t QPCMIE     : 1;
  __IO  uint8_t QPCMF      : 1;
  __IO  uint8_t QPRCMIE    : 1;
  __IO  uint8_t QPRCMF     : 1;
  __IO  uint8_t OUZIE      : 1;
  __IO  uint8_t UFDF       : 1;
  __IO  uint8_t OFDF       : 1;
  __IO  uint8_t ZIIF       : 1;
} stc_qprc0_qicrl_field_t;

typedef struct stc_qprc0_qicrh_field
{
  __IO  uint8_t CDCIE      : 1;
  __IO  uint8_t CDCF       : 1;
  __IO  uint8_t DIRPC      : 1;
  __IO  uint8_t DIROU      : 1;
  __IO  uint8_t QPCNRCMIE  : 1;
  __IO  uint8_t QPCNRCMF   : 1;
} stc_qprc0_qicrh_field_t;

typedef struct stc_qprc0_qcrl_field
{
  __IO  uint8_t PCM        : 2;
  __IO  uint8_t RCM        : 2;
  __IO  uint8_t PSTP       : 1;
  __IO  uint8_t CGSC       : 1;
  __IO  uint8_t RSEL       : 1;
  __IO  uint8_t SWAP       : 1;
} stc_qprc0_qcrl_field_t;

typedef struct stc_qprc0_qcrh_field
{
  __IO  uint8_t PCRM       : 2;
  __IO  uint8_t AES        : 2;
  __IO  uint8_t BES        : 2;
  __IO  uint8_t CGE        : 2;
} stc_qprc0_qcrh_field_t;

typedef struct stc_qprc0_qecr_field
{
  __IO uint16_t ORNGMD     : 1;
  __IO uint16_t ORNGF      : 1;
  __IO uint16_t ORNGIE     : 1;
} stc_qprc0_qecr_field_t;

/******************************************************************************
 * QPRC_NF_MODULE
 ******************************************************************************/
/* QPRC_NF_MODULE register bit fields */
typedef struct stc_qprc0_nf_nfctla_field
{
  __IO  uint8_t AINNWS     : 3;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t AINLV      : 1;
  __IO  uint8_t AINMD      : 1;
} stc_qprc0_nf_nfctla_field_t;

typedef struct stc_qprc0_nf_nfctlb_field
{
  __IO  uint8_t BINNWS     : 3;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t BINLV      : 1;
  __IO  uint8_t BINMD      : 1;
} stc_qprc0_nf_nfctlb_field_t;

typedef struct stc_qprc0_nf_nfctlz_field
{
  __IO  uint8_t ZINNWS     : 3;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t ZINLV      : 1;
  __IO  uint8_t ZINMD      : 1;
} stc_qprc0_nf_nfctlz_field_t;

/******************************************************************************
 * ADC12_MODULE
 ******************************************************************************/
/* ADC12_MODULE register bit fields */
typedef struct stc_adc0_adsr_field
{
  __IO  uint8_t SCS        : 1;
  __IO  uint8_t PCS        : 1;
  __IO  uint8_t PCNS       : 1;
        uint8_t RESERVED3  : 3;
  __IO  uint8_t FDAS       : 1;
  __IO  uint8_t ADSTP      : 1;
} stc_adc0_adsr_field_t;

typedef struct stc_adc0_adcr_field
{
  __IO  uint8_t OVRIE      : 1;
  __IO  uint8_t CMPIE      : 1;
  __IO  uint8_t PCIE       : 1;
  __IO  uint8_t SCIE       : 1;
        uint8_t RESERVED4  : 1;
  __IO  uint8_t CMPIF      : 1;
  __IO  uint8_t PCIF       : 1;
  __IO  uint8_t SCIF       : 1;
} stc_adc0_adcr_field_t;

typedef struct stc_adc0_sfns_field
{
  __IO  uint8_t SFS        : 4;
} stc_adc0_sfns_field_t;

typedef struct stc_adc0_sccr_field
{
  __IO  uint8_t SSTR       : 1;
  __IO  uint8_t SHEN       : 1;
  __IO  uint8_t RPT        : 1;
        uint8_t RESERVED3  : 1;
  __IO  uint8_t SFCLR      : 1;
  __IO  uint8_t SOVR       : 1;
  __IO  uint8_t SFUL       : 1;
  __IO  uint8_t SEMP       : 1;
} stc_adc0_sccr_field_t;

typedef struct stc_adc0_scfd_field
{
  __IO uint32_t SC         : 5;
       uint32_t RESERVED5  : 3;
  __IO uint32_t RS         : 2;
       uint32_t RESERVED10 : 2;
  __IO uint32_t INVL       : 1;
       uint32_t RESERVED13 : 7;
  __IO uint32_t SD         :12;
} stc_adc0_scfd_field_t;

typedef struct stc_adc0_scis2_field
{
  __IO  uint8_t AN16       : 1;
  __IO  uint8_t AN17       : 1;
  __IO  uint8_t AN18       : 1;
  __IO  uint8_t AN19       : 1;
  __IO  uint8_t AN20       : 1;
  __IO  uint8_t AN21       : 1;
  __IO  uint8_t AN22       : 1;
  __IO  uint8_t AN23       : 1;
} stc_adc0_scis2_field_t;

typedef struct stc_adc0_scis3_field
{
  __IO  uint8_t AN24       : 1;
  __IO  uint8_t AN25       : 1;
  __IO  uint8_t AN26       : 1;
  __IO  uint8_t AN27       : 1;
  __IO  uint8_t AN28       : 1;
  __IO  uint8_t AN29       : 1;
  __IO  uint8_t AN30       : 1;
  __IO  uint8_t AN31       : 1;
} stc_adc0_scis3_field_t;

typedef struct stc_adc0_scis0_field
{
  __IO  uint8_t AN0        : 1;
  __IO  uint8_t AN1        : 1;
  __IO  uint8_t AN2        : 1;
  __IO  uint8_t AN3        : 1;
  __IO  uint8_t AN4        : 1;
  __IO  uint8_t AN5        : 1;
  __IO  uint8_t AN6        : 1;
  __IO  uint8_t AN7        : 1;
} stc_adc0_scis0_field_t;

typedef struct stc_adc0_scis1_field
{
  __IO  uint8_t AN8        : 1;
  __IO  uint8_t AN9        : 1;
  __IO  uint8_t AN10       : 1;
  __IO  uint8_t AN11       : 1;
  __IO  uint8_t AN12       : 1;
  __IO  uint8_t AN13       : 1;
  __IO  uint8_t AN14       : 1;
  __IO  uint8_t AN15       : 1;
} stc_adc0_scis1_field_t;

typedef struct stc_adc0_pfns_field
{
  __IO  uint8_t PFS        : 2;
        uint8_t RESERVED2  : 2;
  __IO  uint8_t TEST       : 2;
} stc_adc0_pfns_field_t;

typedef struct stc_adc0_pccr_field
{
  __IO  uint8_t PSTR       : 1;
  __IO  uint8_t PHEN       : 1;
  __IO  uint8_t PEEN       : 1;
  __IO  uint8_t ESCE       : 1;
  __IO  uint8_t PFCLR      : 1;
  __IO  uint8_t POVR       : 1;
  __IO  uint8_t PFUL       : 1;
  __IO  uint8_t PEMP       : 1;
} stc_adc0_pccr_field_t;

typedef struct stc_adc0_pcfd_field
{
  __IO uint32_t PC         : 5;
       uint32_t RESERVED5  : 3;
  __IO uint32_t RS         : 3;
       uint32_t RESERVED11 : 1;
  __IO uint32_t INVL       : 1;
       uint32_t RESERVED13 : 7;
  __IO uint32_t PD         :12;
} stc_adc0_pcfd_field_t;

typedef struct stc_adc0_pcis_field
{
  __IO  uint8_t P1A        : 3;
  __IO  uint8_t P2A        : 5;
} stc_adc0_pcis_field_t;

typedef struct stc_adc0_cmpcr_field
{
  __IO  uint8_t CCH        : 5;
  __IO  uint8_t CMD0       : 1;
  __IO  uint8_t CMD1       : 1;
  __IO  uint8_t CMPEN      : 1;
} stc_adc0_cmpcr_field_t;

typedef struct stc_adc0_cmpd_field
{
       uint16_t RESERVED0  : 6;
  __IO uint16_t CMAD       :10;
} stc_adc0_cmpd_field_t;

typedef struct stc_adc0_adss2_field
{
  __IO  uint8_t TS16       : 1;
  __IO  uint8_t TS17       : 1;
  __IO  uint8_t TS18       : 1;
  __IO  uint8_t TS19       : 1;
  __IO  uint8_t TS20       : 1;
  __IO  uint8_t TS21       : 1;
  __IO  uint8_t TS22       : 1;
  __IO  uint8_t TS23       : 1;
} stc_adc0_adss2_field_t;

typedef struct stc_adc0_adss3_field
{
  __IO  uint8_t TS24       : 1;
  __IO  uint8_t TS25       : 1;
  __IO  uint8_t TS26       : 1;
  __IO  uint8_t TS27       : 1;
  __IO  uint8_t TS28       : 1;
  __IO  uint8_t TS29       : 1;
  __IO  uint8_t TS30       : 1;
  __IO  uint8_t TS31       : 1;
} stc_adc0_adss3_field_t;

typedef struct stc_adc0_adss0_field
{
  __IO  uint8_t TS0        : 1;
  __IO  uint8_t TS1        : 1;
  __IO  uint8_t TS2        : 1;
  __IO  uint8_t TS3        : 1;
  __IO  uint8_t TS4        : 1;
  __IO  uint8_t TS5        : 1;
  __IO  uint8_t TS6        : 1;
  __IO  uint8_t TS7        : 1;
} stc_adc0_adss0_field_t;

typedef struct stc_adc0_adss1_field
{
  __IO  uint8_t TS8        : 1;
  __IO  uint8_t TS9        : 1;
  __IO  uint8_t TS10       : 1;
  __IO  uint8_t TS11       : 1;
  __IO  uint8_t TS12       : 1;
  __IO  uint8_t TS13       : 1;
  __IO  uint8_t TS14       : 1;
  __IO  uint8_t TS15       : 1;
} stc_adc0_adss1_field_t;

typedef struct stc_adc0_adst1_field
{
  __IO  uint8_t ST1        : 5;
  __IO  uint8_t STX1       : 3;
} stc_adc0_adst1_field_t;

typedef struct stc_adc0_adst0_field
{
  __IO  uint8_t ST0        : 5;
  __IO  uint8_t STX0       : 3;
} stc_adc0_adst0_field_t;

typedef struct stc_adc0_adct_field
{
  __IO  uint8_t CT         : 8;
} stc_adc0_adct_field_t;

typedef struct stc_adc0_prtsl_field
{
  __IO  uint8_t PRTSL      : 4;
} stc_adc0_prtsl_field_t;

typedef struct stc_adc0_sctsl_field
{
  __IO  uint8_t SCTSL      : 4;
} stc_adc0_sctsl_field_t;

typedef struct stc_adc0_adcen_field
{
  __IO uint16_t ENBL       : 1;
  __IO uint16_t READY      : 1;
       uint16_t RESERVED2  : 6;
  __IO uint16_t ENBLTIME   : 8;
} stc_adc0_adcen_field_t;

typedef struct stc_adc0_wcmrcif_field
{
  __IO uint32_t RCINT      : 1;
} stc_adc0_wcmrcif_field_t;

typedef struct stc_adc0_wcmrcot_field
{
  __IO uint32_t RCOOF      : 1;
} stc_adc0_wcmrcot_field_t;

typedef struct stc_adc0_wcmpcr_field
{
        uint8_t RESERVED0  : 2;
  __IO  uint8_t RCOE       : 1;
  __IO  uint8_t RCOIE      : 1;
  __IO  uint8_t RCOIRS     : 1;
  __IO  uint8_t RCODC0     : 1;
  __IO  uint8_t RCODC1     : 1;
  __IO  uint8_t RCODC2     : 1;
} stc_adc0_wcmpcr_field_t;

typedef struct stc_adc0_wcmpsr_field
{
  __IO  uint8_t WCCH       : 5;
  __IO  uint8_t WCMD       : 1;
} stc_adc0_wcmpsr_field_t;

typedef struct stc_adc0_wcmpdl_field
{
       uint16_t RESERVED0  : 6;
  __IO uint16_t CMLD       :10;
} stc_adc0_wcmpdl_field_t;

typedef struct stc_adc0_wcmpdh_field
{
       uint16_t RESERVED0  : 6;
  __IO uint16_t CMHD       :10;
} stc_adc0_wcmpdh_field_t;

/******************************************************************************
 * CRTRIM_MODULE
 ******************************************************************************/
/* CRTRIM_MODULE register bit fields */
typedef struct stc_crtrim_mcr_psr_field
{
  __IO  uint8_t CSR        : 3;
} stc_crtrim_mcr_psr_field_t;

typedef struct stc_crtrim_mcr_ftrm_field
{
  __IO uint16_t TRD        :10;
} stc_crtrim_mcr_ftrm_field_t;

typedef struct stc_crtrim_mcr_ttrm_field
{
  __IO  uint8_t TRT        : 5;
} stc_crtrim_mcr_ttrm_field_t;

typedef struct stc_crtrim_mcr_rlr_field
{
  __IO uint32_t TRMLCK     :32;
} stc_crtrim_mcr_rlr_field_t;

/******************************************************************************
 * EXTI_MODULE
 ******************************************************************************/
/* EXTI_MODULE register bit fields */
typedef struct stc_exti_enir_field
{
  __IO uint32_t EN0        : 1;
  __IO uint32_t EN1        : 1;
  __IO uint32_t EN2        : 1;
  __IO uint32_t EN3        : 1;
  __IO uint32_t EN4        : 1;
  __IO uint32_t EN5        : 1;
  __IO uint32_t EN6        : 1;
       uint32_t RESERVED0  : 8;
  __IO uint32_t EN15       : 1;
} stc_exti_enir_field_t;

typedef struct stc_exti_eirr_field
{
  __IO uint32_t ER0        : 1;
  __IO uint32_t ER1        : 1;
  __IO uint32_t ER2        : 1;
  __IO uint32_t ER3        : 1;
  __IO uint32_t ER4        : 1;
  __IO uint32_t ER5        : 1;
  __IO uint32_t ER6        : 1;
       uint32_t RESERVED0  : 8;
  __IO uint32_t ER15       : 1;
} stc_exti_eirr_field_t;

typedef struct stc_exti_eicl_field
{
  __IO uint32_t ECL0       : 1;
  __IO uint32_t ECL1       : 1;
  __IO uint32_t ECL2       : 1;
  __IO uint32_t ECL3       : 1;
  __IO uint32_t ECL4       : 1;
  __IO uint32_t ECL5       : 1;
  __IO uint32_t ECL6       : 1;
       uint32_t RESERVED0  : 8;
  __IO uint32_t ECL15      : 1;
} stc_exti_eicl_field_t;

typedef struct stc_exti_elvr_field
{
  __IO uint32_t LA0        : 1;
  __IO uint32_t LB0        : 1;
  __IO uint32_t LA1        : 1;
  __IO uint32_t LB1        : 1;
  __IO uint32_t LA2        : 1;
  __IO uint32_t LB2        : 1;
  __IO uint32_t LA3        : 1;
  __IO uint32_t LB3        : 1;
  __IO uint32_t LA4        : 1;
  __IO uint32_t LB4        : 1;
  __IO uint32_t LA5        : 1;
  __IO uint32_t LB5        : 1;
  __IO uint32_t LA6        : 1;
  __IO uint32_t LB6        : 1;
       uint32_t RESERVED0  : 16;
  __IO uint32_t LA15       : 1;
  __IO uint32_t LB15       : 1;
} stc_exti_elvr_field_t;

typedef struct stc_exti_nmirr_field
{
  __IO uint16_t NR         : 1;
} stc_exti_nmirr_field_t;

typedef struct stc_exti_nmicl_field
{
  __IO uint16_t NCL        : 1;
} stc_exti_nmicl_field_t;

/******************************************************************************
 * INTREQ_MODULE
 ******************************************************************************/
/* INTREQ_MODULE register bit fields */
typedef struct stc_intreq_drqsel_field
{
       uint32_t RESERVED0  : 5;
  __IO uint32_t ADCSCAN0   : 1;
  __IO uint32_t ADCSCAN1   : 1;
  __IO uint32_t ADCSCAN2   : 1;
  __IO uint32_t IRQ0BT0    : 1;
  __IO uint32_t IRQ0BT2    : 1;
  __IO uint32_t IRQ0BT4    : 1;
  __IO uint32_t IRQ0BT6    : 1;
  __IO uint32_t MFS0RX     : 1;
  __IO uint32_t MFS0TX     : 1;
  __IO uint32_t MFS1RX     : 1;
  __IO uint32_t MFS1TX     : 1;
  __IO uint32_t MFS2RX     : 1;
  __IO uint32_t MFS2TX     : 1;
  __IO uint32_t MFS3RX     : 1;
  __IO uint32_t MFS3TX     : 1;
  __IO uint32_t MFS4RX     : 1;
  __IO uint32_t MFS4TX     : 1;
  __IO uint32_t MFS5RX     : 1;
  __IO uint32_t MFS5TX     : 1;
  __IO uint32_t MFS6RX     : 1;
  __IO uint32_t MFS6TX     : 1;
  __IO uint32_t MFS7RX     : 1;
  __IO uint32_t MFS7TX     : 1;
  __IO uint32_t EXINT0     : 1;
  __IO uint32_t EXINT1     : 1;
  __IO uint32_t EXINT2     : 1;
  __IO uint32_t EXINT3     : 1;
} stc_intreq_drqsel_field_t;

typedef struct stc_intreq_irqcmode_field
{
	__IO uint32_t IRQCMODE   : 1;
} stc_intreq_irqcmode_field_t;

typedef struct stc_intreq_exc02mon_field
{
  __IO uint32_t NMI        : 1;
  __IO uint32_t HWINT      : 1;
} stc_intreq_exc02mon_field_t;

typedef struct stc_intreq_irq00mon_field
{
  __IO uint32_t FCSINT     : 1;
} stc_intreq_irq00mon_field_t;

typedef struct stc_intreq_irq01mon_field
{
  __IO uint32_t SWWDTINT   : 1;
} stc_intreq_irq01mon_field_t;

typedef struct stc_intreq_irq02mon_field
{
  __IO uint32_t LVDINT     : 1;
} stc_intreq_irq02mon_field_t;

typedef struct stc_intreq_irq03mon_field
{
  __IO uint32_t WAVE0INT0  : 1;
  __IO uint32_t WAVE0INT1  : 1;
  __IO uint32_t WAVE0INT2  : 1;
  __IO uint32_t WAVE0INT3  : 1;
  __IO uint32_t WAVE1INT0  : 1;
  __IO uint32_t WAVE1INT1  : 1;
  __IO uint32_t WAVE1INT2  : 1;
  __IO uint32_t WAVE1INT3  : 1;
  __IO uint32_t WAVE2INT0  : 1;
  __IO uint32_t WAVE2INT1  : 1;
  __IO uint32_t WAVE2INT2  : 1;
  __IO uint32_t WAVE2INT3  : 1;
} stc_intreq_irq03mon_field_t;

typedef struct stc_intreq_irq04mon_field
{
  __IO uint32_t EXTINT0    : 1;
  __IO uint32_t EXTINT1    : 1;
  __IO uint32_t EXTINT2    : 1;
  __IO uint32_t EXTINT3    : 1;
  __IO uint32_t EXTINT4    : 1;
  __IO uint32_t EXTINT5    : 1;
  __IO uint32_t EXTINT6    : 1;
  __IO uint32_t EXTINT7    : 1;
} stc_intreq_irq04mon_field_t;

typedef struct stc_intreq_irq05mon_field
{
  __IO uint32_t EXTINT8    : 1;
  __IO uint32_t EXTINT9    : 1;
  __IO uint32_t EXTINT10   : 1;
  __IO uint32_t EXTINT11   : 1;
  __IO uint32_t EXTINT12   : 1;
  __IO uint32_t EXTINT13   : 1;
  __IO uint32_t EXTINT14   : 1;
  __IO uint32_t EXTINT15   : 1;
  __IO uint32_t EXTINT16   : 1;
  __IO uint32_t EXTINT17   : 1;
  __IO uint32_t EXTINT18   : 1;
  __IO uint32_t EXTINT19   : 1;
  __IO uint32_t EXTINT20   : 1;
  __IO uint32_t EXTINT21   : 1;
  __IO uint32_t EXTINT22   : 1;
  __IO uint32_t EXTINT23   : 1;
  __IO uint32_t EXTINT24   : 1;
  __IO uint32_t EXTINT25   : 1;
  __IO uint32_t EXTINT26   : 1;
  __IO uint32_t EXTINT27   : 1;
  __IO uint32_t EXTINT28   : 1;
  __IO uint32_t EXTINT29   : 1;
  __IO uint32_t EXTINT30   : 1;
  __IO uint32_t EXTINT31   : 1;
} stc_intreq_irq05mon_field_t;

typedef struct stc_intreq_irq06mon_field
{
  __IO uint32_t TIMINT0    : 1;
  __IO uint32_t TIMINT1    : 1;
  __IO uint32_t QUD0INT0   : 1;
  __IO uint32_t QUD0INT1   : 1;
  __IO uint32_t QUD0INT2   : 1;
  __IO uint32_t QUD0INT3   : 1;
  __IO uint32_t QUD0INT4   : 1;
  __IO uint32_t QUD0INT5   : 1;
  __IO uint32_t QUD1INT0   : 1;
  __IO uint32_t QUD1INT1   : 1;
  __IO uint32_t QUD1INT2   : 1;
  __IO uint32_t QUD1INT3   : 1;
  __IO uint32_t QUD1INT4   : 1;
  __IO uint32_t QUD1INT5   : 1;
  __IO uint32_t QUD2INT0   : 1;
  __IO uint32_t QUD2INT1   : 1;
  __IO uint32_t QUD2INT2   : 1;
  __IO uint32_t QUD2INT3   : 1;
  __IO uint32_t QUD2INT4   : 1;
  __IO uint32_t QUD2INT5   : 1;
} stc_intreq_irq06mon_field_t;

typedef struct stc_intreq_irq07mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq07mon_field_t;

typedef struct stc_intreq_irq08mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq08mon_field_t;

typedef struct stc_intreq_irq09mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq09mon_field_t;

typedef struct stc_intreq_irq10mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq10mon_field_t;

typedef struct stc_intreq_irq11mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq11mon_field_t;

typedef struct stc_intreq_irq12mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq12mon_field_t;

typedef struct stc_intreq_irq13mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq13mon_field_t;

typedef struct stc_intreq_irq14mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq14mon_field_t;

typedef struct stc_intreq_irq15mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq15mon_field_t;

typedef struct stc_intreq_irq16mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq16mon_field_t;

typedef struct stc_intreq_irq17mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
} stc_intreq_irq17mon_field_t;

typedef struct stc_intreq_irq18mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
} stc_intreq_irq18mon_field_t;

typedef struct stc_intreq_irq19mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
       uint32_t RESERVED2  : 2;
  __IO uint32_t DMAINT0    : 1;
} stc_intreq_irq19mon_field_t;

typedef struct stc_intreq_irq20mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
  __IO uint32_t DMAINT1    : 1;
} stc_intreq_irq20mon_field_t;

typedef struct stc_intreq_irq21mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
       uint32_t RESERVED2  : 2;
  __IO uint32_t DMAINT2    : 1;
} stc_intreq_irq21mon_field_t;

typedef struct stc_intreq_irq22mon_field
{
  __IO uint32_t MFSINT0    : 1;
  __IO uint32_t MFSINT1    : 1;
  __IO uint32_t MFSINT2    : 1;
  __IO uint32_t MFSINT3    : 1;
  __IO uint32_t DMAINT3    : 1;
} stc_intreq_irq22mon_field_t;

typedef struct stc_intreq_irq23mon_field
{
  __IO uint32_t PPGINT0    : 1;
  __IO uint32_t PPGINT1    : 1;
  __IO uint32_t PPGINT2    : 1;
  __IO uint32_t PPGINT3    : 1;
  __IO uint32_t PPGINT4    : 1;
  __IO uint32_t PPGINT5    : 1;
  __IO uint32_t PPGINT6    : 1;
  __IO uint32_t PPGINT7    : 1;
  __IO uint32_t PPGINT8    : 1;
} stc_intreq_irq23mon_field_t;

typedef struct stc_intreq_irq24mon_field
{
  __IO uint32_t MOSCINT    : 1;
  __IO uint32_t SOSCINT    : 1;
  __IO uint32_t MPLLINT    : 1;
       uint32_t RESERVED3  : 1;
  __IO uint32_t WCINT      : 1;
  __IO uint32_t RTCINT     : 1;
} stc_intreq_irq24mon_field_t;

typedef struct stc_intreq_irq25mon_field
{
  __IO uint32_t ADCINT0    : 1;
  __IO uint32_t ADCINT1    : 1;
  __IO uint32_t ADCINT2    : 1;
  __IO uint32_t ADCINT3    : 1;
  __IO uint32_t ADCINT4    : 1;
} stc_intreq_irq25mon_field_t;

typedef struct stc_intreq_irq26mon_field
{
  __IO uint32_t ADCINT0    : 1;
  __IO uint32_t ADCINT1    : 1;
  __IO uint32_t ADCINT2    : 1;
  __IO uint32_t ADCINT3    : 1;
  __IO uint32_t ADCINT4    : 1;
} stc_intreq_irq26mon_field_t;

typedef struct stc_intreq_irq27mon_field
{
  __IO uint32_t ADCINT0    : 1;
  __IO uint32_t ADCINT1    : 1;
  __IO uint32_t ADCINT2    : 1;
  __IO uint32_t ADCINT3    : 1;
  __IO uint32_t ADCINT4    : 1;
  __IO uint32_t LCDCINT    : 1;
} stc_intreq_irq27mon_field_t;

typedef struct stc_intreq_irq28mon_field
{
  __IO uint32_t FRT0INT0   : 1;
  __IO uint32_t FRT0INT1   : 1;
  __IO uint32_t FRT0INT2   : 1;
  __IO uint32_t FRT0INT3   : 1;
  __IO uint32_t FRT0INT4   : 1;
  __IO uint32_t FRT0INT5   : 1;
  __IO uint32_t FRT1INT0   : 1;
  __IO uint32_t FRT1INT1   : 1;
  __IO uint32_t FRT1INT2   : 1;
  __IO uint32_t FRT1INT3   : 1;
  __IO uint32_t FRT1INT4   : 1;
  __IO uint32_t FRT1INT5   : 1;
  __IO uint32_t FRT2INT0   : 1;
  __IO uint32_t FRT2INT1   : 1;
  __IO uint32_t FRT2INT2   : 1;
  __IO uint32_t FRT2INT3   : 1;
  __IO uint32_t FRT2INT4   : 1;
  __IO uint32_t FRT2INT5   : 1;
} stc_intreq_irq28mon_field_t;

typedef struct stc_intreq_irq29mon_field
{
  __IO uint32_t ICU0INT0   : 1;
  __IO uint32_t ICU0INT1   : 1;
  __IO uint32_t ICU0INT2   : 1;
  __IO uint32_t ICU0INT3   : 1;
  __IO uint32_t ICU1INT0   : 1;
  __IO uint32_t ICU1INT1   : 1;
  __IO uint32_t ICU1INT2   : 1;
  __IO uint32_t ICU1INT3   : 1;
  __IO uint32_t ICU2INT0   : 1;
  __IO uint32_t ICU2INT1   : 1;
  __IO uint32_t ICU2INT2   : 1;
  __IO uint32_t ICU2INT3   : 1;
} stc_intreq_irq29mon_field_t;

typedef struct stc_intreq_irq30mon_field
{
  __IO uint32_t OCU0INT0   : 1;
  __IO uint32_t OCU0INT1   : 1;
  __IO uint32_t OCU0INT2   : 1;
  __IO uint32_t OCU0INT3   : 1;
  __IO uint32_t OCU0INT4   : 1;
  __IO uint32_t OCU0INT5   : 1;
  __IO uint32_t OCU1INT0   : 1;
  __IO uint32_t OCU1INT1   : 1;
  __IO uint32_t OCU1INT2   : 1;
  __IO uint32_t OCU1INT3   : 1;
  __IO uint32_t OCU1INT4   : 1;
  __IO uint32_t OCU1INT5   : 1;
  __IO uint32_t OCU2INT0   : 1;
  __IO uint32_t OCU2INT1   : 1;
  __IO uint32_t OCU2INT2   : 1;
  __IO uint32_t OCU2INT3   : 1;
  __IO uint32_t OCU2INT4   : 1;
  __IO uint32_t OCU2INT5   : 1;
} stc_intreq_irq30mon_field_t;

typedef struct stc_intreq_irq31mon_field
{
  __IO uint32_t BTINT0     : 1;
  __IO uint32_t BTINT1     : 1;
  __IO uint32_t BTINT2     : 1;
  __IO uint32_t BTINT3     : 1;
  __IO uint32_t BTINT4     : 1;
  __IO uint32_t BTINT5     : 1;
  __IO uint32_t BTINT6     : 1;
  __IO uint32_t BTINT7     : 1;
  __IO uint32_t BTINT8     : 1;
  __IO uint32_t BTINT9     : 1;
  __IO uint32_t BTINT10    : 1;
  __IO uint32_t BTINT11    : 1;
  __IO uint32_t BTINT12    : 1;
  __IO uint32_t BTINT13    : 1;
  __IO uint32_t BTINT14    : 1;
  __IO uint32_t BTINT15    : 1;
       uint32_t RESERVED16 :11;
  __IO uint32_t FLASHINT   : 1;
} stc_intreq_irq31mon_field_t;

/******************************************************************************
 * GPIO_MODULE
 ******************************************************************************/
/* GPIO_MODULE register bit fields */
typedef struct stc_gpio_pfr0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_pfr0_field_t;

typedef struct stc_gpio_pfr1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_pfr1_field_t;

typedef struct stc_gpio_pfr2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_pfr2_field_t;

typedef struct stc_gpio_pfr3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_pfr3_field_t;

typedef struct stc_gpio_pfr4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_pfr4_field_t;

typedef struct stc_gpio_pfr5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_pfr5_field_t;

typedef struct stc_gpio_pfr6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_pfr6_field_t;

typedef struct stc_gpio_pfr8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_pfr8_field_t;

typedef struct stc_gpio_pfre_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_pfre_field_t;

typedef struct stc_gpio_pcr0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_pcr0_field_t;

typedef struct stc_gpio_pcr1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_pcr1_field_t;

typedef struct stc_gpio_pcr2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_pcr2_field_t;

typedef struct stc_gpio_pcr3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_pcr3_field_t;

typedef struct stc_gpio_pcr4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_pcr4_field_t;

typedef struct stc_gpio_pcr5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_pcr5_field_t;

typedef struct stc_gpio_pcr6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_pcr6_field_t;

typedef struct stc_gpio_pcr8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_pcr8_field_t;

typedef struct stc_gpio_pcre_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_pcre_field_t;

typedef struct stc_gpio_ddr0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_ddr0_field_t;

typedef struct stc_gpio_ddr1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_ddr1_field_t;

typedef struct stc_gpio_ddr2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_ddr2_field_t;

typedef struct stc_gpio_ddr3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_ddr3_field_t;

typedef struct stc_gpio_ddr4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_ddr4_field_t;

typedef struct stc_gpio_ddr5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_ddr5_field_t;

typedef struct stc_gpio_ddr6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_ddr6_field_t;

typedef struct stc_gpio_ddr8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_ddr8_field_t;

typedef struct stc_gpio_ddre_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_ddre_field_t;

typedef struct stc_gpio_pdir0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_pdir0_field_t;

typedef struct stc_gpio_pdir1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_pdir1_field_t;

typedef struct stc_gpio_pdir2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_pdir2_field_t;

typedef struct stc_gpio_pdir3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_pdir3_field_t;

typedef struct stc_gpio_pdir4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_pdir4_field_t;

typedef struct stc_gpio_pdir5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_pdir5_field_t;

typedef struct stc_gpio_pdir6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_pdir6_field_t;

typedef struct stc_gpio_pdir8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_pdir8_field_t;

typedef struct stc_gpio_pdire_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_pdire_field_t;

typedef struct stc_gpio_pdor0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_pdor0_field_t;

typedef struct stc_gpio_pdor1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_pdor1_field_t;

typedef struct stc_gpio_pdor2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_pdor2_field_t;

typedef struct stc_gpio_pdor3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_pdor3_field_t;

typedef struct stc_gpio_pdor4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_pdor4_field_t;

typedef struct stc_gpio_pdor5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_pdor5_field_t;

typedef struct stc_gpio_pdor6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_pdor6_field_t;

typedef struct stc_gpio_pdor8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_pdor8_field_t;

typedef struct stc_gpio_pdore_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_pdore_field_t;

typedef struct stc_gpio_ade_field
{
  __IO uint32_t AN00       : 1;
  __IO uint32_t AN01       : 1;
  __IO uint32_t AN02       : 1;
  __IO uint32_t AN03       : 1;
  __IO uint32_t AN04       : 1;
  __IO uint32_t AN05       : 1;
  __IO uint32_t AN06       : 1;
  __IO uint32_t AN07       : 1;
} stc_gpio_ade_field_t;

typedef struct stc_gpio_spsr_field
{
  __IO uint32_t SUBXC0     : 1;
  __IO uint32_t SUBXC1     : 1;
  __IO uint32_t MAINXC0    : 1;
  __IO uint32_t MAINXC1    : 1;
} stc_gpio_spsr_field_t;

typedef struct stc_gpio_epfr00_field
{
  __IO uint32_t NMIS       : 1;
  __IO uint32_t CROUTE     : 2;
       uint32_t RESERVED3  : 1;
  __IO uint32_t RTCCOE     : 2;
  __IO uint32_t SUBOUTE    : 2;
       uint32_t RESERVED8  : 8;
  __IO uint32_t SWDEN      : 1;
} stc_gpio_epfr00_field_t;

typedef struct stc_gpio_epfr01_field
{
  __IO uint32_t RTO00E     : 2;
  __IO uint32_t RTO01E     : 2;
  __IO uint32_t RTO02E     : 2;
  __IO uint32_t RTO03E     : 2;
  __IO uint32_t RTO04E     : 2;
  __IO uint32_t RTO05E     : 2;
  __IO uint32_t DTTI0C     : 1;
  __IO uint32_t IGTRG0     : 1;
       uint32_t RESERVED14 : 2;
  __IO uint32_t DTTI0S     : 2;
  __IO uint32_t FRCK0S     : 2;
  __IO uint32_t IC00S      : 3;
  __IO uint32_t IC01S      : 3;
  __IO uint32_t IC02S      : 3;
  __IO uint32_t IC03S      : 3;
} stc_gpio_epfr01_field_t;

typedef struct stc_gpio_epfr02_field
{
  __IO uint32_t RTO10E     : 2;
  __IO uint32_t RTO11E     : 2;
  __IO uint32_t RTO12E     : 2;
  __IO uint32_t RTO13E     : 2;
  __IO uint32_t RTO14E     : 2;
  __IO uint32_t RTO15E     : 2;
  __IO uint32_t DTTI1C     : 1;
       uint32_t RESERVED13 : 3;
  __IO uint32_t DTTI1S     : 2;
  __IO uint32_t FRCK1S     : 2;
  __IO uint32_t IC10S      : 3;
  __IO uint32_t IC11S      : 3;
  __IO uint32_t IC12S      : 3;
  __IO uint32_t IC13S      : 3;
} stc_gpio_epfr02_field_t;

typedef struct stc_gpio_epfr03_field
{
  __IO uint32_t RTO20E     : 2;
  __IO uint32_t RTO21E     : 2;
  __IO uint32_t RTO22E     : 2;
  __IO uint32_t RTO23E     : 2;
  __IO uint32_t RTO24E     : 2;
  __IO uint32_t RTO25E     : 2;
  __IO uint32_t DTTI2C     : 1;
       uint32_t RESERVED13 : 3;
  __IO uint32_t DTTI2S     : 2;
  __IO uint32_t FRCK2S     : 2;
  __IO uint32_t IC20S      : 3;
  __IO uint32_t IC21S      : 3;
  __IO uint32_t IC22S      : 3;
  __IO uint32_t IC23S      : 3;
} stc_gpio_epfr03_field_t;

typedef struct stc_gpio_epfr04_field
{
       uint32_t RESERVED0  : 2;
  __IO uint32_t TIOA0E     : 2;
  __IO uint32_t TIOB0S     : 3;
       uint32_t RESERVED7  : 1;
  __IO uint32_t TIOA1S     : 2;
  __IO uint32_t TIOA1E     : 2;
  __IO uint32_t TIOB1S     : 2;
       uint32_t RESERVED14 : 4;
  __IO uint32_t TIOA2E     : 2;
  __IO uint32_t TIOB2S     : 2;
       uint32_t RESERVED22 : 2;
  __IO uint32_t TIOA3S     : 2;
  __IO uint32_t TIOA3E     : 2;
  __IO uint32_t TIOB3S     : 2;
} stc_gpio_epfr04_field_t;

typedef struct stc_gpio_epfr05_field
{
       uint32_t RESERVED0  : 2;
  __IO uint32_t TIOA4E     : 2;
  __IO uint32_t TIOB4S     : 2;
       uint32_t RESERVED6  : 2;
  __IO uint32_t TIOA5S     : 2;
  __IO uint32_t TIOA5E     : 2;
  __IO uint32_t TIOB5S     : 2;
       uint32_t RESERVED14 : 4;
  __IO uint32_t TIOA6E     : 2;
  __IO uint32_t TIOB6S     : 2;
       uint32_t RESERVED22 : 2;
  __IO uint32_t TIOA7S     : 2;
  __IO uint32_t TIOA7E     : 2;
  __IO uint32_t TIOB7S     : 2;
} stc_gpio_epfr05_field_t;

typedef struct stc_gpio_epfr06_field
{
  __IO uint32_t EINT00S    : 2;
  __IO uint32_t EINT01S    : 2;
  __IO uint32_t EINT02S    : 2;
  __IO uint32_t EINT03S    : 2;
  __IO uint32_t EINT04S    : 2;
  __IO uint32_t EINT05S    : 2;
  __IO uint32_t EINT06S    : 2;
  __IO uint32_t EINT07S    : 2;
  __IO uint32_t EINT08S    : 2;
  __IO uint32_t EINT09S    : 2;
  __IO uint32_t EINT10S    : 2;
  __IO uint32_t EINT11S    : 2;
  __IO uint32_t EINT12S    : 2;
  __IO uint32_t EINT13S    : 2;
  __IO uint32_t EINT14S    : 2;
  __IO uint32_t EINT15S    : 2;
} stc_gpio_epfr06_field_t;

typedef struct stc_gpio_epfr07_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t SIN0S      : 2;
  __IO uint32_t SOT0B      : 2;
  __IO uint32_t SCK0B      : 2;
  __IO uint32_t SIN1S      : 2;
  __IO uint32_t SOT1B      : 2;
  __IO uint32_t SCK1B      : 2;
  __IO uint32_t SIN2S      : 2;
  __IO uint32_t SOT2B      : 2;
  __IO uint32_t SCK2B      : 2;
  __IO uint32_t SIN3S      : 2;
  __IO uint32_t SOT3B      : 2;
  __IO uint32_t SCK3B      : 2;
} stc_gpio_epfr07_field_t;

typedef struct stc_gpio_epfr08_field
{
  __IO uint32_t RTS4E      : 2;
  __IO uint32_t CTS4S      : 2;
  __IO uint32_t SIN4S      : 2;
  __IO uint32_t SOT4B      : 2;
  __IO uint32_t SCK4B      : 2;
  __IO uint32_t SIN5S      : 2;
  __IO uint32_t SOT5B      : 2;
  __IO uint32_t SCK5B      : 2;
  __IO uint32_t SIN6S      : 2;
  __IO uint32_t SOT6B      : 2;
  __IO uint32_t SCK6B      : 2;
  __IO uint32_t SIN7S      : 2;
  __IO uint32_t SOT7B      : 2;
  __IO uint32_t SCK7B      : 2;
} stc_gpio_epfr08_field_t;

typedef struct stc_gpio_epfr09_field
{
  __IO uint32_t QAIN0S     : 2;
  __IO uint32_t QBIN0S     : 2;
  __IO uint32_t QZIN0S     : 2;
  __IO uint32_t QAIN1S     : 2;
  __IO uint32_t QBIN1S     : 2;
  __IO uint32_t QZIN1S     : 2;
  __IO uint32_t ADTRG0S    : 4;
  __IO uint32_t ADTRG1S    : 4;
  __IO uint32_t ADTRG2S    : 4;
  __IO uint32_t CRX0S      : 2;
  __IO uint32_t CTX0E      : 2;
  __IO uint32_t CRX1S      : 2;
  __IO uint32_t CTX1E      : 2;
} stc_gpio_epfr09_field_t;

typedef struct stc_gpio_epfr12_field
{
       uint32_t RESERVED0  : 2;
  __IO uint32_t TIOA8E     : 2;
  __IO uint32_t TIOB8S     : 2;
       uint32_t RESERVED6  : 2;
  __IO uint32_t TIOA9S     : 2;
  __IO uint32_t TIOA9E     : 2;
  __IO uint32_t TIOB9S     : 2;
       uint32_t RESERVED14 : 4;
  __IO uint32_t TIOA10E    : 2;
  __IO uint32_t TIOB10S    : 2;
       uint32_t RESERVED22 : 2;
  __IO uint32_t TIOA11S    : 2;
  __IO uint32_t TIOA11E    : 2;
  __IO uint32_t TIOB11S    : 2;
} stc_gpio_epfr12_field_t;

typedef struct stc_gpio_epfr13_field
{
       uint32_t RESERVED0  : 2;
  __IO uint32_t TIOA12E    : 2;
  __IO uint32_t TIOB12S    : 2;
       uint32_t RESERVED6  : 2;
  __IO uint32_t TIOA13S    : 2;
  __IO uint32_t TIOA13E    : 2;
  __IO uint32_t TIOB13S    : 2;
       uint32_t RESERVED14 : 4;
  __IO uint32_t TIOA14E    : 2;
  __IO uint32_t TIOB14S    : 2;
       uint32_t RESERVED22 : 2;
  __IO uint32_t TIOA15S    : 2;
  __IO uint32_t TIOA15E    : 2;
  __IO uint32_t TIOB15S    : 2;
} stc_gpio_epfr13_field_t;

typedef struct stc_gpio_epfr14_field
{
  __IO uint32_t QAIN2S     : 2;
  __IO uint32_t QBIN2S     : 2;
  __IO uint32_t QZIN2S     : 2;
} stc_gpio_epfr14_field_t;

typedef struct stc_gpio_epfr15_field
{
  __IO uint32_t EINT16S    : 2;
  __IO uint32_t EINT17S    : 2;
  __IO uint32_t EINT18S    : 2;
  __IO uint32_t EINT19S    : 2;
  __IO uint32_t EINT20S    : 2;
  __IO uint32_t EINT21S    : 2;
  __IO uint32_t EINT22S    : 2;
  __IO uint32_t EINT23S    : 2;
  __IO uint32_t EINT24S    : 2;
  __IO uint32_t EINT25S    : 2;
  __IO uint32_t EINT26S    : 2;
  __IO uint32_t EINT27S    : 2;
  __IO uint32_t EINT28S    : 2;
  __IO uint32_t EINT29S    : 2;
  __IO uint32_t EINT30S    : 2;
  __IO uint32_t EINT31S    : 2;
} stc_gpio_epfr15_field_t;

typedef struct stc_gpio_epfr16_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t SIN8S      : 2;
  __IO uint32_t SOT8B      : 2;
  __IO uint32_t SCK8B      : 2;
  __IO uint32_t SIN9S      : 2;
  __IO uint32_t SOT9B      : 2;
  __IO uint32_t SCK9B      : 2;
  __IO uint32_t SIN10S     : 2;
  __IO uint32_t SOT10B     : 2;
  __IO uint32_t SCK10B     : 2;
  __IO uint32_t SIN11S     : 2;
  __IO uint32_t SOT11B     : 2;
  __IO uint32_t SCK11B     : 2;
} stc_gpio_epfr16_field_t;

typedef struct stc_gpio_epfr17_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t SIN12S     : 2;
  __IO uint32_t SOT12B     : 2;
  __IO uint32_t SCK12B     : 2;
  __IO uint32_t SIN13S     : 2;
  __IO uint32_t SOT13B     : 2;
  __IO uint32_t SCK13B     : 2;
  __IO uint32_t SIN14S     : 2;
  __IO uint32_t SOT14B     : 2;
  __IO uint32_t SCK14B     : 2;
  __IO uint32_t SIN15S     : 2;
  __IO uint32_t SOT15B     : 2;
  __IO uint32_t SCK15B     : 2;
} stc_gpio_epfr17_field_t;

typedef struct stc_gpio_epfr18_field
{
  __IO uint32_t CECR0B     : 2;
  __IO uint32_t CECR1B     : 2;
} stc_gpio_epfr18_field_t;

typedef struct stc_gpio_epfr21_field
{
  __IO uint32_t QAIN0S     : 1;
  __IO uint32_t QBIN0S     : 1;
  __IO uint32_t QZIN0S     : 1;
} stc_gpio_epfr21_field_t;

typedef struct stc_gpio_epfr22_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t SCS10B     : 2;
  __IO uint32_t SCS11E     : 2;
       uint32_t RESERVED8  : 4;
  __IO uint32_t SCS30B     : 2;
  __IO uint32_t SCS31E     : 2;
} stc_gpio_epfr22_field_t;

typedef struct stc_gpio_pzr0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_pzr0_field_t;

typedef struct stc_gpio_pzr1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_pzr1_field_t;

typedef struct stc_gpio_pzr2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_pzr2_field_t;

typedef struct stc_gpio_pzr3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_pzr3_field_t;

typedef struct stc_gpio_pzr4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_pzr4_field_t;

typedef struct stc_gpio_pzr5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_pzr5_field_t;

typedef struct stc_gpio_pzr6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_pzr6_field_t;

typedef struct stc_gpio_pzr8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_pzr8_field_t;

typedef struct stc_gpio_pzre_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_pzre_field_t;

typedef struct stc_gpio_fpoer0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_gpio_fpoer0_field_t;

typedef struct stc_gpio_fpoer1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_gpio_fpoer1_field_t;

typedef struct stc_gpio_fpoer2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_gpio_fpoer2_field_t;

typedef struct stc_gpio_fpoer3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_gpio_fpoer3_field_t;

typedef struct stc_gpio_fpoer4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_gpio_fpoer4_field_t;

typedef struct stc_gpio_fpoer5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_gpio_fpoer5_field_t;

typedef struct stc_gpio_fpoer6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_gpio_fpoer6_field_t;

typedef struct stc_gpio_fpoer8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_gpio_fpoer8_field_t;

typedef struct stc_gpio_fpoere_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_gpio_fpoere_field_t;

/******************************************************************************
 * FASTIO_MODULE
 ******************************************************************************/
/* FASTIO_MODULE register bit fields */
typedef struct stc_fastio_fpdir0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_fastio_fpdir0_field_t;

typedef struct stc_fastio_fpdir1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_fastio_fpdir1_field_t;

typedef struct stc_fastio_fpdir2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_fastio_fpdir2_field_t;

typedef struct stc_fastio_fpdir3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_fastio_fpdir3_field_t;

typedef struct stc_fastio_fpdir4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_fastio_fpdir4_field_t;

typedef struct stc_fastio_fpdir5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_fastio_fpdir5_field_t;

typedef struct stc_fastio_fpdir6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_fastio_fpdir6_field_t;

typedef struct stc_fastio_fpdir8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_fastio_fpdir8_field_t;

typedef struct stc_fastio_fpdire_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_fastio_fpdire_field_t;

typedef struct stc_fastio_fpdor0_field
{
  __IO uint32_t P00        : 1;
  __IO uint32_t P01        : 1;
  __IO uint32_t P02        : 1;
  __IO uint32_t P03        : 1;
  __IO uint32_t P04        : 1;
       uint32_t RESERVED5  :10;
  __IO uint32_t P0F        : 1;
} stc_fastio_fpdor0_field_t;

typedef struct stc_fastio_fpdor1_field
{
  __IO uint32_t P10        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P15        : 1;
} stc_fastio_fpdor1_field_t;

typedef struct stc_fastio_fpdor2_field
{
       uint32_t RESERVED0  : 1;
  __IO uint32_t P21        : 1;
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
} stc_fastio_fpdor2_field_t;

typedef struct stc_fastio_fpdor3_field
{
       uint32_t RESERVED0  : 9;
  __IO uint32_t P39        : 1;
  __IO uint32_t P3A        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3F        : 1;
} stc_fastio_fpdor3_field_t;

typedef struct stc_fastio_fpdor4_field
{
       uint32_t RESERVED0  : 6;
  __IO uint32_t P46        : 1;
  __IO uint32_t P47        : 1;
       uint32_t RESERVED8  : 1;
  __IO uint32_t P49        : 1;
  __IO uint32_t P4A        : 1;
} stc_fastio_fpdor4_field_t;

typedef struct stc_fastio_fpdor5_field
{
  __IO uint32_t P50        : 1;
  __IO uint32_t P51        : 1;
  __IO uint32_t P52        : 1;
} stc_fastio_fpdor5_field_t;

typedef struct stc_fastio_fpdor6_field
{
  __IO uint32_t P60        : 1;
  __IO uint32_t P61        : 1;
} stc_fastio_fpdor6_field_t;

typedef struct stc_fastio_fpdor8_field
{
  __IO uint32_t P80        : 1;
  __IO uint32_t P81        : 1;
  __IO uint32_t P82        : 1;
} stc_fastio_fpdor8_field_t;

typedef struct stc_fastio_fpdore_field
{
  __IO uint32_t PE0        : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t PE2        : 1;
  __IO uint32_t PE3        : 1;
} stc_fastio_fpdore_field_t;

typedef struct stc_fastio_m_fpdir0_field
{
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
  __IO uint32_t P15        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P10        : 1;
} stc_fastio_m_fpdir0_field_t;

typedef struct stc_fastio_m_fpdir1_field
{
  __IO uint32_t P47        : 1;
  __IO uint32_t P46        : 1;
  __IO uint32_t P3F        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3A        : 1;
} stc_fastio_m_fpdir1_field_t;

typedef struct stc_fastio_m_fpdor0_field
{
  __IO uint32_t P22        : 1;
  __IO uint32_t P23        : 1;
  __IO uint32_t P15        : 1;
  __IO uint32_t P14        : 1;
  __IO uint32_t P13        : 1;
  __IO uint32_t P12        : 1;
  __IO uint32_t P11        : 1;
  __IO uint32_t P10        : 1;
} stc_fastio_m_fpdor0_field_t;

typedef struct stc_fastio_m_fpdor1_field
{
  __IO uint32_t P47        : 1;
  __IO uint32_t P46        : 1;
  __IO uint32_t P3F        : 1;
  __IO uint32_t P3E        : 1;
  __IO uint32_t P3D        : 1;
  __IO uint32_t P3C        : 1;
  __IO uint32_t P3B        : 1;
  __IO uint32_t P3A        : 1;
} stc_fastio_m_fpdor1_field_t;

/******************************************************************************
 * LVD_MODULE
 ******************************************************************************/
/* LVD_MODULE register bit fields */
typedef struct stc_lvd_lvd_ctl_field
{
       uint16_t RESERVED0  : 2;
  __IO uint16_t SVHI       : 5;
  __IO uint16_t LVDIE      : 1;
       uint16_t RESERVED8  : 2;
  __IO uint16_t SVHR       : 5;
  __IO uint16_t LVDRE      : 1;
} stc_lvd_lvd_ctl_field_t;

typedef struct stc_lvd_lvd_str_field
{
        uint8_t RESERVED0  : 7;
  __IO  uint8_t LVDIR      : 1;
} stc_lvd_lvd_str_field_t;

typedef struct stc_lvd_lvd_clr_field
{
        uint8_t RESERVED0  : 7;
  __IO  uint8_t LVDCL      : 1;
} stc_lvd_lvd_clr_field_t;

typedef struct stc_lvd_lvd_rlr_field
{
  __IO uint32_t LVDLCK     : 32;
} stc_lvd_lvd_rlr_field_t;

typedef struct stc_lvd_lvd_str2_field
{
        uint8_t RESERVED0  : 6;
  __IO  uint8_t LVDRRDY    : 1;
  __IO  uint8_t LVDIRDY    : 1;
} stc_lvd_lvd_str2_field_t;

/******************************************************************************
 * DS_MODULE
 ******************************************************************************/
/* Deep standby mode control registers bit fields */
typedef struct stc_ds_reg_ctl_field
{
        uint8_t RESERVED0  : 1;
  __IO  uint8_t ISUBSEL    : 2;
} stc_ds_reg_ctl_field_t;

typedef struct stc_ds_rck_ctl_field
{
  __IO  uint8_t RTCCKE     : 1;
  __IO  uint8_t CECCKE     : 1;
} stc_ds_rck_ctl_field_t;

typedef struct stc_ds_pmd_ctl_field
{
  __IO  uint8_t RTCE       : 1;
} stc_ds_pmd_ctl_field_t;

typedef struct stc_ds_wrfsr_field
{
  __IO  uint8_t WINITX     : 1;
  __IO  uint8_t WLVDH      : 1;
} stc_ds_wrfsr_field_t;

typedef struct stc_ds_wifsr_field
{
  __IO uint16_t WRTCI      : 1;
  __IO uint16_t WLVDI      : 1;
  __IO uint16_t WUI0       : 1;
  __IO uint16_t WUI1       : 1;
  __IO uint16_t WUI2       : 1;
  __IO uint16_t WUI3       : 1;
  __IO uint16_t WUI4       : 1;
  __IO uint16_t WUI5       : 1;
  __IO uint16_t WCEC0I     : 1;
  __IO uint16_t WCEC1I     : 1;
} stc_ds_wifsr_field_t;

typedef struct stc_ds_wier_field
{
  __IO uint16_t WRTCE      : 1;
  __IO uint16_t WLVDE      : 1;
       uint16_t RESERVED2  : 1;
  __IO uint16_t WUE1       : 1;
  __IO uint16_t WUE2       : 1;
  __IO uint16_t WUE3       : 1;
  __IO uint16_t WUE4       : 1;
  __IO uint16_t WUE5       : 1;
  __IO uint16_t WCEC0E     : 1;
  __IO uint16_t WCEC1E     : 1;
} stc_ds_wier_field_t;

typedef struct stc_ds_wilvr_field
{
  __IO  uint8_t WUI1LV     : 1;
  __IO  uint8_t WUI2LV     : 1;
  __IO  uint8_t WUI3LV     : 1;
  __IO  uint8_t WUI4LV     : 1;
  __IO  uint8_t WUI5LV     : 1;
} stc_ds_wilvr_field_t;

typedef struct stc_ds_dsramr_field
{
  __IO  uint8_t SRAMR      : 2;
} stc_ds_dsramr_field_t;

/******************************************************************************
 * MFS_UART_MODULE
 ******************************************************************************/
/* MFS_UART_MODULE register bit fields */
typedef struct stc_mfs_uart_smr_field
{
  __IO  uint8_t SOE        : 1;
        uint8_t RESERVED1  : 1;
  __IO  uint8_t BDS        : 1;
  __IO  uint8_t SBL        : 1;
        uint8_t RESERVED4  : 1;
  __IO  uint8_t MD         : 3;
} stc_mfs_uart_smr_field_t;

typedef struct stc_mfs_uart_scr_field
{
  __IO  uint8_t TXE        : 1;
  __IO  uint8_t RXE        : 1;
  __IO  uint8_t TBIE       : 1;
  __IO  uint8_t TIE        : 1;
  __IO  uint8_t RIE        : 1;
        uint8_t RESERVED5  : 2;
  __IO  uint8_t UPCL       : 1;
} stc_mfs_uart_scr_field_t;

typedef struct stc_mfs_uart_escr_field
{
  __IO  uint8_t L          : 3;
  __IO  uint8_t P          : 1;
  __IO  uint8_t PEN        : 1;
  __IO  uint8_t INV        : 1;
  __IO  uint8_t ESBL       : 1;
  __IO  uint8_t FLWEN      : 1;
} stc_mfs_uart_escr_field_t;

typedef struct stc_mfs_uart_ssr_field
{
  __IO  uint8_t TBI        : 1;
  __IO  uint8_t TDRE       : 1;
  __IO  uint8_t RDRF       : 1;
  __IO  uint8_t ORE        : 1;
  __IO  uint8_t FRE        : 1;
  __IO  uint8_t PE         : 1;
        uint8_t RESERVED6  : 1;
  __IO  uint8_t REC        : 1;
} stc_mfs_uart_ssr_field_t;

typedef struct stc_mfs_uart_bgr_field
{
  __IO uint16_t BGR        :15;
  __IO uint16_t EXT        : 1;
} stc_mfs_uart_bgr_field_t;

typedef struct stc_mfs_uart_fcr0_field
{
  __IO  uint8_t FE1        : 1;
  __IO  uint8_t FE2        : 1;
  __IO  uint8_t FCL1       : 1;
  __IO  uint8_t FCL2       : 1;
  __IO  uint8_t FSET       : 1;
  __IO  uint8_t FLD        : 1;
  __IO  uint8_t FLST       : 1;
} stc_mfs_uart_fcr0_field_t;

typedef struct stc_mfs_uart_fcr1_field
{
  __IO  uint8_t FSEL       : 1;
  __IO  uint8_t FTIE       : 1;
  __IO  uint8_t FDRQ       : 1;
  __IO  uint8_t FRIIE      : 1;
  __IO  uint8_t FLSTE      : 1;
} stc_mfs_uart_fcr1_field_t;

/******************************************************************************
 * MFS_CSIO_MODULE
 ******************************************************************************/
/* MFS_CSIO_MODULE register bit fields */
typedef struct stc_mfs_csio_smr_field
{
  __IO  uint8_t SOE        : 1;
  __IO  uint8_t SCKE       : 1;
  __IO  uint8_t BDS        : 1;
  __IO  uint8_t SCINV      : 1;
        uint8_t RESERVED4  : 1;
  __IO  uint8_t MD         : 3;
} stc_mfs_csio_smr_field_t;

typedef struct stc_mfs_csio_scr_field
{
  __IO  uint8_t TXE        : 1;
  __IO  uint8_t RXE        : 1;
  __IO  uint8_t TBIE       : 1;
  __IO  uint8_t TIE        : 1;
  __IO  uint8_t RIE        : 1;
  __IO  uint8_t SPI        : 1;
  __IO  uint8_t MS         : 1;
  __IO  uint8_t UPCL       : 1;
} stc_mfs_csio_scr_field_t;

typedef struct stc_mfs_csio_escr_field
{
  __IO  uint8_t L          : 3;
  __IO  uint8_t WT         : 2;
  __IO  uint8_t CSFE       : 1;
  __IO  uint8_t L3         : 1;
  __IO  uint8_t SOP        : 1;
} stc_mfs_csio_escr_field_t;

typedef struct stc_mfs_csio_ssr_field
{
  __IO  uint8_t TBI        : 1;
  __IO  uint8_t TDRE       : 1;
  __IO  uint8_t RDRF       : 1;
  __IO  uint8_t ORE        : 1;
        uint8_t RESERVED4  : 3;
  __IO  uint8_t REC        : 1;
} stc_mfs_csio_ssr_field_t;

typedef struct stc_mfs_csio_bgr_field
{
  __IO uint16_t BGR        :16;
} stc_mfs_csio_bgr_field_t;

typedef struct stc_mfs_csio_fcr0_field
{
  __IO  uint8_t FE1        : 1;
  __IO  uint8_t FE2        : 1;
  __IO  uint8_t FCL1       : 1;
  __IO  uint8_t FCL2       : 1;
  __IO  uint8_t FSET       : 1;
  __IO  uint8_t FLD        : 1;
  __IO  uint8_t FLST       : 1;
} stc_mfs_csio_fcr0_field_t;

typedef struct stc_mfs_csio_fcr1_field
{
  __IO  uint8_t FSEL       : 1;
  __IO  uint8_t FTIE       : 1;
  __IO  uint8_t FDRQ       : 1;
  __IO  uint8_t FRIIE      : 1;
  __IO  uint8_t FLSTE      : 1;
} stc_mfs_csio_fcr1_field_t;

typedef struct stc_mfs_csio_scstr0_field
{
  __IO  uint8_t CSHD       : 8;
} stc_mfs_csio_scstr0_field_t;

typedef struct stc_mfs_csio_scstr1_field
{
  __IO  uint8_t CSSU       : 8;
} stc_mfs_csio_scstr1_field_t;

typedef struct stc_mfs_csio_scstr32_field
{
  __IO uint16_t CSDS       :16;
} stc_mfs_csio_scstr32_field_t;

typedef struct stc_mfs_csio_sacsr_field
{
  __IO uint16_t TMRE       : 1;
  __IO uint16_t TDIV       : 4;
       uint16_t RESERVED5  : 1;
  __IO uint16_t TSYNE      : 1;
  __IO uint16_t TINTE      : 1;
  __IO uint16_t TINT       : 1;
       uint16_t RESERVED9  : 2;
  __IO uint16_t CSE        : 1;
  __IO uint16_t CSEIE      : 1;
  __IO uint16_t TBEEN      : 1;
} stc_mfs_csio_sacsr_field_t;

typedef struct stc_mfs_csio_stmr_field
{
  __IO uint16_t TM         :16;
} stc_mfs_csio_stmr_field_t;

typedef struct stc_mfs_csio_stmcr_field
{
  __IO uint16_t TC         :16;
} stc_mfs_csio_stmcr_field_t;

typedef struct stc_mfs_csio_scscr_field
{
  __IO uint16_t CSOE       : 1;
  __IO uint16_t CSEN0      : 1;
  __IO uint16_t CSEN1      : 1;
  __IO uint16_t CSEN2      : 1;
  __IO uint16_t CSEN3      : 1;
  __IO uint16_t CSLVL      : 1;
  __IO uint16_t CDIV       : 3;
  __IO uint16_t SCAM       : 1;
  __IO uint16_t SCD        : 2;
  __IO uint16_t SED        : 2;
  __IO uint16_t SST        : 2;
} stc_mfs_csio_scscr_field_t;

typedef struct stc_mfs_csio_scsfr0_field
{
  __IO uint8_t CS1         :8;
} stc_mfs_csio_scsfr0_field_t;

typedef struct stc_mfs_csio_scsfr1_field
{
  __IO uint8_t CS2         :8;
} stc_mfs_csio_scsfr1_field_t;

typedef struct stc_mfs_csio_scsfr2_field
{
  __IO uint8_t CS3         :8;
} stc_mfs_csio_scsfr2_field_t;

/******************************************************************************
 * MFS_LIN_MODULE
 ******************************************************************************/
/* MFS_LIN_MODULE register bit fields */
typedef struct stc_mfs_lin_smr_field
{
  __IO  uint8_t SOE        : 1;
        uint8_t RESERVED1  : 2;
  __IO  uint8_t SBL        : 1;
        uint8_t RESERVED4  : 1;
  __IO  uint8_t MD         : 3;
} stc_mfs_lin_smr_field_t;

typedef struct stc_mfs_lin_scr_field
{
  __IO  uint8_t TXE        : 1;
  __IO  uint8_t RXE        : 1;
  __IO  uint8_t TBIE       : 1;
  __IO  uint8_t TIE        : 1;
  __IO  uint8_t RIE        : 1;
  __IO  uint8_t LBR        : 1;
  __IO  uint8_t MS         : 1;
  __IO  uint8_t UPCL       : 1;
} stc_mfs_lin_scr_field_t;

typedef struct stc_mfs_lin_escr_field
{
  __IO  uint8_t DEL        : 2;
  __IO  uint8_t LBL        : 2;
  __IO  uint8_t LBIE       : 1;
        uint8_t RESERVED5  : 1;
  __IO  uint8_t ESBL       : 1;
} stc_mfs_lin_escr_field_t;

typedef struct stc_mfs_lin_ssr_field
{
  __IO  uint8_t TBI        : 1;
  __IO  uint8_t TDRE       : 1;
  __IO  uint8_t RDRF       : 1;
  __IO  uint8_t ORE        : 1;
  __IO  uint8_t FRE        : 1;
  __IO  uint8_t LBD        : 1;
        uint8_t RESERVED6  : 1;
  __IO  uint8_t REC        : 1;
} stc_mfs_lin_ssr_field_t;

typedef struct stc_mfs_lin_bgr_field
{
  __IO uint16_t BGR        :15;
  __IO uint16_t EXT        : 1;
} stc_mfs_lin_bgr_field_t;

typedef struct stc_mfs_lin_fcr0_field
{
  __IO  uint8_t FE1        : 1;
  __IO  uint8_t FE2        : 1;
  __IO  uint8_t FCL1       : 1;
  __IO  uint8_t FCL2       : 1;
  __IO  uint8_t FSET       : 1;
  __IO  uint8_t FLD        : 1;
  __IO  uint8_t FLST       : 1;
} stc_mfs_lin_fcr0_field_t;

typedef struct stc_mfs_lin_fcr1_field
{
  __IO  uint8_t FSEL       : 1;
  __IO  uint8_t FTIE       : 1;
  __IO  uint8_t FDRQ       : 1;
  __IO  uint8_t FRIIE      : 1;
  __IO  uint8_t FLSTE      : 1;
} stc_mfs_lin_fcr1_field_t;

/******************************************************************************
 * MFS_I2C_MODULE
 ******************************************************************************/
/* MFS_I2C_MODULE register bit fields */
typedef struct stc_mfs_i2c_smr_field
{
        uint8_t RESERVED0  : 2;
  __IO  uint8_t TIE        : 1;
  __IO  uint8_t RIE        : 1;
        uint8_t RESERVED4  : 1;
  __IO  uint8_t MD         : 3;
} stc_mfs_i2c_smr_field_t;

typedef struct stc_mfs_i2c_ibcr_field
{
  __IO  uint8_t INT        : 1;
  __IO  uint8_t BER        : 1;
  __IO  uint8_t INTE       : 1;
  __IO  uint8_t CNDE       : 1;
  __IO  uint8_t WSEL       : 1;
  __IO  uint8_t ACKE       : 1;
  __IO  uint8_t ACT_SCC    : 1;
  __IO  uint8_t MSS        : 1;
} stc_mfs_i2c_ibcr_field_t;

typedef struct stc_mfs_i2c_ibsr_field
{
  __IO  uint8_t BB         : 1;
  __IO  uint8_t SPC        : 1;
  __IO  uint8_t RSC        : 1;
  __IO  uint8_t AL         : 1;
  __IO  uint8_t TRX        : 1;
  __IO  uint8_t RSA        : 1;
  __IO  uint8_t RACK       : 1;
  __IO  uint8_t FBT        : 1;
} stc_mfs_i2c_ibsr_field_t;

typedef struct stc_mfs_i2c_ssr_field
{
  __IO  uint8_t TBI        : 1;
  __IO  uint8_t TDRE       : 1;
  __IO  uint8_t RDRF       : 1;
  __IO  uint8_t ORE        : 1;
  __IO  uint8_t TBIE       : 1;
  __IO  uint8_t DMA        : 1;
  __IO  uint8_t TSET       : 1;
  __IO  uint8_t REC        : 1;
} stc_mfs_i2c_ssr_field_t;

typedef struct stc_mfs_i2c_bgr_field
{
  __IO uint16_t BGR        :16;
} stc_mfs_i2c_bgr_field_t;

typedef struct stc_mfs_i2c_isba_field
{
  __IO  uint8_t SA         : 7;
  __IO  uint8_t SAEN       : 1;
} stc_mfs_i2c_isba_field_t;

typedef struct stc_mfs_i2c_ismk_field
{
  __IO  uint8_t SM         : 7;
  __IO  uint8_t EN         : 1;
} stc_mfs_i2c_ismk_field_t;

typedef struct stc_mfs_i2c_fcr0_field
{
  __IO  uint8_t FE1        : 1;
  __IO  uint8_t FE2        : 1;
  __IO  uint8_t FCL1       : 1;
  __IO  uint8_t FCL2       : 1;
  __IO  uint8_t FSET       : 1;
  __IO  uint8_t FLD        : 1;
  __IO  uint8_t FLST       : 1;
} stc_mfs_i2c_fcr0_field_t;

typedef struct stc_mfs_i2c_fcr1_field
{
  __IO  uint8_t FSEL       : 1;
  __IO  uint8_t FTIE       : 1;
  __IO  uint8_t FDRQ       : 1;
  __IO  uint8_t FRIIE      : 1;
  __IO  uint8_t FLSTE      : 1;
} stc_mfs_i2c_fcr1_field_t;

typedef struct stc_mfs_i2c_eibcr_field
{
  __IO  uint8_t BEC        : 1;
  __IO  uint8_t SOCE       : 1;
  __IO  uint8_t SCLC       : 1;
  __IO  uint8_t SDAC       : 1;
  __IO  uint8_t SCLS       : 1;
  __IO  uint8_t SDAS       : 1;
} stc_mfs_i2c_eibcr_field_t;

/******************************************************************************
 * CRC_MODULE
 ******************************************************************************/
/* CRC_MODULE register bit fields */
typedef struct stc_crc_crccr_field
{
  __IO  uint8_t INIT       : 1;
  __IO  uint8_t CRC32      : 1;
  __IO  uint8_t LTLEND     : 1;
  __IO  uint8_t LSBFST     : 1;
  __IO  uint8_t CRCLTE     : 1;
  __IO  uint8_t CRCLSF     : 1;
  __IO  uint8_t FXOR       : 1;
} stc_crc_crccr_field_t;

typedef struct stc_crc_crcinit_field
{
  __IO uint32_t D          :32;
} stc_crc_crcinit_field_t;

typedef struct stc_crc_crcin_field
{
  __IO uint32_t D          :32;
} stc_crc_crcin_field_t;

typedef struct stc_crc_crcr_field
{
  __IO uint32_t D          :32;
} stc_crc_crcr_field_t;

/******************************************************************************
 * WC_MODULE
 ******************************************************************************/
/* WC_MODULE register bit fields */
typedef struct stc_wc_wcrd_field
{
  __IO  uint8_t CTR        : 6;
} stc_wc_wcrd_field_t;

typedef struct stc_wc_wcrl_field
{
  __IO  uint8_t RLC        : 6;
} stc_wc_wcrl_field_t;

typedef struct stc_wc_wccr_field
{
  __IO  uint8_t WCIF       : 1;
  __IO  uint8_t WCIE       : 1;
  __IO  uint8_t CS         : 2;
        uint8_t RESERVED4  : 2;
  __IO  uint8_t WCOP       : 1;
  __IO  uint8_t WCEN       : 1;
} stc_wc_wccr_field_t;

typedef struct stc_wc_clk_sel_field
{
  __IO uint16_t SEL_IN     : 2;
       uint16_t RESERVED2  : 6;
  __IO uint16_t SEL_OUT    : 3;
} stc_wc_clk_sel_field_t;

typedef struct stc_wc_clk_en_field
{
  __IO  uint8_t CLK_EN     : 1;
  __IO  uint8_t CLK_EN_R   : 1;
} stc_wc_clk_en_field_t;

/******************************************************************************
 * RTC_MODULE
 ******************************************************************************/
/* Realtime clock registers bit fields */
typedef struct stc_rtc_wtcr1_field
{
  __IO uint32_t ST         : 1;
       uint32_t RESERVED1  : 1;
  __IO uint32_t RUN        : 1;
  __IO uint32_t SRST       : 1;
  __IO uint32_t SCST       : 1;
  __IO uint32_t SCRST      : 1;
  __IO uint32_t BUSY       : 1;
       uint32_t RESERVED7  : 1;
  __IO uint32_t MIEN       : 1;
  __IO uint32_t HEN        : 1;
  __IO uint32_t DEN        : 1;
  __IO uint32_t MOEN       : 1;
  __IO uint32_t YEN        : 1;
       uint32_t RESERVED13 : 3;
  __IO uint32_t INTSSI     : 1;
  __IO uint32_t INTSI      : 1;
  __IO uint32_t INTMI      : 1;
  __IO uint32_t INTHI      : 1;
  __IO uint32_t INTTMI     : 1;
  __IO uint32_t INTALI     : 1;
  __IO uint32_t INTERI     : 1;
  __IO uint32_t INTCRI     : 1;
  __IO uint32_t INTSSIE    : 1;
  __IO uint32_t INTSIE     : 1;
  __IO uint32_t INTMIE     : 1;
  __IO uint32_t INTHIE     : 1;
  __IO uint32_t INTTMIE    : 1;
  __IO uint32_t INTALIE    : 1;
  __IO uint32_t INTERIE    : 1;
  __IO uint32_t INTCRIE    : 1;
} stc_rtc_wtcr1_field_t;

typedef struct stc_rtc_wtcr2_field
{
  __IO uint32_t CREAD      : 1;
       uint32_t RESERVED1  : 7;
  __IO uint32_t TMST       : 1;
  __IO uint32_t TMEN       : 1;
  __IO uint32_t TMRUN      : 1;
} stc_rtc_wtcr2_field_t;

typedef struct stc_rtc_wtbr_field
{
  __IO uint32_t BR         :24;
} stc_rtc_wtbr_field_t;

typedef struct stc_rtc_wtsr_field
{
  __IO  uint8_t S          : 4;
  __IO  uint8_t TS         : 3;
} stc_rtc_wtsr_field_t;

typedef struct stc_rtc_wtmir_field
{
  __IO  uint8_t MI         : 4;
  __IO  uint8_t TMI        : 3;
} stc_rtc_wtmir_field_t;

typedef struct stc_rtc_wthr_field
{
  __IO  uint8_t H          : 4;
  __IO  uint8_t TH         : 2;
} stc_rtc_wthr_field_t;

typedef struct stc_rtc_wtdr_field
{
  __IO  uint8_t D          : 4;
  __IO  uint8_t TD         : 2;
} stc_rtc_wtdr_field_t;

typedef struct stc_rtc_wtdw_field
{
  __IO  uint8_t DW         : 3;
} stc_rtc_wtdw_field_t;

typedef struct stc_rtc_wtmor_field
{
  __IO  uint8_t MO         : 4;
  __IO  uint8_t TMO        : 1;
} stc_rtc_wtmor_field_t;

typedef struct stc_rtc_wtyr_field
{
  __IO  uint8_t Y          : 4;
  __IO  uint8_t TY         : 4;
} stc_rtc_wtyr_field_t;

typedef struct stc_rtc_almir_field
{
  __IO  uint8_t AMI        : 4;
  __IO  uint8_t TAMI       : 3;
} stc_rtc_almir_field_t;

typedef struct stc_rtc_alhr_field
{
  __IO  uint8_t AH         : 4;
  __IO  uint8_t TAH        : 2;
} stc_rtc_alhr_field_t;

typedef struct stc_rtc_aldr_field
{
  __IO  uint8_t AD         : 4;
  __IO  uint8_t TAD        : 2;
} stc_rtc_aldr_field_t;

typedef struct stc_rtc_almor_field
{
  __IO  uint8_t AMO        : 4;
  __IO  uint8_t TAMO       : 1;
} stc_rtc_almor_field_t;

typedef struct stc_rtc_alyr_field
{
  __IO  uint8_t AY         : 4;
  __IO  uint8_t TAY        : 4;
} stc_rtc_alyr_field_t;

typedef struct stc_rtc_wttr_field
{
  __IO uint32_t TM         :18;
} stc_rtc_wttr_field_t;

typedef struct stc_rtc_wtclks_field
{
  __IO  uint8_t WTCLKS     : 1;
} stc_rtc_wtclks_field_t;

typedef struct stc_rtc_wtclkm_field
{
  __IO  uint8_t WTCLKM     : 2;
} stc_rtc_wtclkm_field_t;

typedef struct stc_rtc_wtcal_field
{
  __IO  uint16_t WTCAL     :10;
} stc_rtc_wtcal_field_t;

typedef struct stc_rtc_wtcalen_field
{
  __IO  uint8_t WTCALEN    : 1;
} stc_rtc_wtcalen_field_t;

typedef struct stc_rtc_wtdiv_field
{
  __IO  uint8_t WTDIV      : 4;
} stc_rtc_wtdiv_field_t;

typedef struct stc_rtc_wtdiven_field
{
  __IO  uint8_t WTDIVEN    : 1;
  __IO  uint8_t WTDIVRDY   : 1;
} stc_rtc_wtdiven_field_t;

typedef struct stc_rtc_wtcalprd_field
{
  __IO  uint8_t WTCALPRD   : 6;
} stc_rtc_wtcalprd_field_t;

typedef struct stc_rtc_wtcosel_field
{
  __IO  uint8_t WTCOSEL    : 1;
} stc_rtc_wtcosel_field_t;

/******************************************************************************
 * LSCRP_MODULE
 ******************************************************************************/
/* LSCRP_MODULE register bit fields */
typedef struct stc_lscrp_lcr_prsld_field
{
  __IO  uint8_t LCR_PRSLD  : 6;
} stc_lscrp_lcr_prsld_field_t;

/******************************************************************************
 * PCG_MODULE
 ******************************************************************************/
/* PCG_MODULE register bit fields */
typedef struct stc_pcg_cken0_field
{
  __IO uint32_t MFSCK0     : 1;
  __IO uint32_t MFSCK1     : 1;
  __IO uint32_t MFSCK2     : 1;
  __IO uint32_t MFSCK3     : 1;
  __IO uint32_t MFSCK4     : 1;
  __IO uint32_t MFSCK5     : 1;
  __IO uint32_t MFSCK6     : 1;
  __IO uint32_t MFSCK7     : 1;
  __IO uint32_t MFSCK8     : 1;
  __IO uint32_t MFSCK9     : 1;
  __IO uint32_t MFSCK10    : 1;
  __IO uint32_t MFSCK11    : 1;
  __IO uint32_t MFSCK12    : 1;
  __IO uint32_t MFSCK13    : 1;
  __IO uint32_t MFSCK14    : 1;
  __IO uint32_t MFSCK15    : 1;
  __IO uint32_t ADCCK0     : 1;
  __IO uint32_t ADCCK1     : 1;
  __IO uint32_t ADCCK2     : 1;
  __IO uint32_t ADCCK3     : 1;
       uint32_t RESERVED20 : 4;
  __IO uint32_t DMACK      : 1;
       uint32_t RESERVED25 : 3;
  __IO uint32_t GIOCK      : 1;
} stc_pcg_cken0_field_t;

typedef struct stc_pcg_mrst0_field
{
  __IO uint32_t MFSRST0    : 1;
  __IO uint32_t MFSRST1    : 1;
  __IO uint32_t MFSRST2    : 1;
  __IO uint32_t MFSRST3    : 1;
  __IO uint32_t MFSRST4    : 1;
  __IO uint32_t MFSRST5    : 1;
  __IO uint32_t MFSRST6    : 1;
  __IO uint32_t MFSRST7    : 1;
  __IO uint32_t MFSRST8    : 1;
  __IO uint32_t MFSRST9    : 1;
  __IO uint32_t MFSRST10   : 1;
  __IO uint32_t MFSRST11   : 1;
  __IO uint32_t MFSRST12   : 1;
  __IO uint32_t MFSRST13   : 1;
  __IO uint32_t MFSRST14   : 1;
  __IO uint32_t MFSRST15   : 1;
  __IO uint32_t ADCRST0    : 1;
  __IO uint32_t ADCRST1    : 1;
  __IO uint32_t ADCRST2    : 1;
  __IO uint32_t ADCRST3    : 1;
       uint32_t RESERVED20 : 4;
  __IO uint32_t DMARST     : 1;
} stc_pcg_mrst0_field_t;

typedef struct stc_pcg_cken1_field
{
  __IO uint32_t BTMCK0     : 1;
  __IO uint32_t BTMCK1     : 1;
  __IO uint32_t BTMCK2     : 1;
  __IO uint32_t BTMCK3     : 1;
       uint32_t RESERVED4  : 4;
  __IO uint32_t MFTCK0     : 1;
  __IO uint32_t MFTCK1     : 1;
  __IO uint32_t MFTCK2     : 1;
  __IO uint32_t MFTCK3     : 1;
       uint32_t RESERVED12 : 4;
  __IO uint32_t QDUCK0     : 1;
  __IO uint32_t QDUCK1     : 1;
  __IO uint32_t QDUCK2     : 1;
  __IO uint32_t QDUCK3     : 1;
} stc_pcg_cken1_field_t;

typedef struct stc_pcg_mrst1_field
{
  __IO uint32_t BTMRST0    : 1;
  __IO uint32_t BTMRST1    : 1;
  __IO uint32_t BTMRST2    : 1;
  __IO uint32_t BTMRST3    : 1;
       uint32_t RESERVED4  : 4;
  __IO uint32_t MFTRST0    : 1;
  __IO uint32_t MFTRST1    : 1;
  __IO uint32_t MFTRST2    : 1;
  __IO uint32_t MFTRST3    : 1;
       uint32_t RESERVED12 : 4;
  __IO uint32_t QDURST0    : 1;
  __IO uint32_t QDURST1    : 1;
  __IO uint32_t QDURST2    : 1;
  __IO uint32_t QDURST3    : 1;
} stc_pcg_mrst1_field_t;

typedef struct stc_pcg_cken2_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t CANCK0     : 1;
  __IO uint32_t CANCK1     : 1;
} stc_pcg_cken2_field_t;

typedef struct stc_pcg_mrst2_field
{
       uint32_t RESERVED0  : 4;
  __IO uint32_t CANRST0    : 1;
  __IO uint32_t CANRST1    : 1;
} stc_pcg_mrst2_field_t;

/******************************************************************************
 * DMAC_MODULE
 ******************************************************************************/
/* DMAC_MODULE register bit fields */
typedef struct stc_dmac_dmacr_field
{
       uint32_t RESERVED0  :24;
  __IO uint32_t DH         : 4;
  __IO uint32_t PR         : 1;
       uint32_t RESERVED29 : 1;
  __IO uint32_t DS         : 1;
  __IO uint32_t DE         : 1;
} stc_dmac_dmacr_field_t;

typedef struct stc_dmac_dmaca0_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca0_field_t;

typedef struct stc_dmac_dmacb0_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb0_field_t;

typedef struct stc_dmac_dmaca1_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca1_field_t;

typedef struct stc_dmac_dmacb1_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb1_field_t;

typedef struct stc_dmac_dmaca2_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca2_field_t;

typedef struct stc_dmac_dmacb2_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb2_field_t;

typedef struct stc_dmac_dmaca3_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca3_field_t;

typedef struct stc_dmac_dmacb3_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb3_field_t;

typedef struct stc_dmac_dmaca4_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca4_field_t;

typedef struct stc_dmac_dmacb4_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb4_field_t;

typedef struct stc_dmac_dmaca5_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca5_field_t;

typedef struct stc_dmac_dmacb5_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb5_field_t;

typedef struct stc_dmac_dmaca6_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca6_field_t;

typedef struct stc_dmac_dmacb6_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb6_field_t;

typedef struct stc_dmac_dmaca7_field
{
  __IO uint32_t TC         :16;
  __IO uint32_t BC         : 4;
       uint32_t RESERVED20 : 3;
  __IO uint32_t IS         : 6;
  __IO uint32_t ST         : 1;
  __IO uint32_t PB         : 1;
  __IO uint32_t EB         : 1;
} stc_dmac_dmaca7_field_t;

typedef struct stc_dmac_dmacb7_field
{
  __IO uint32_t EM         : 1;
       uint32_t RESERVED1  :15;
  __IO uint32_t SS         : 3;
  __IO uint32_t CI         : 1;
  __IO uint32_t EI         : 1;
  __IO uint32_t RD         : 1;
  __IO uint32_t RS         : 1;
  __IO uint32_t RC         : 1;
  __IO uint32_t FD         : 1;
  __IO uint32_t FS         : 1;
  __IO uint32_t TW         : 2;
  __IO uint32_t MS         : 2;
} stc_dmac_dmacb7_field_t;

/******************************************************************************
 * MTB_DWT_MODULE
 ******************************************************************************/
/* MTB_DWT_MODULE register bit fields */
typedef struct stc_mtb_dwt_fct_field
{
  __IO  uint8_t STAEN      : 2;
  __IO  uint8_t STPEN      : 2;
  __IO  uint8_t DSTA       : 2;
  __IO  uint8_t DSTP       : 2;
} stc_mtb_dwt_fct_field_t;

/******************************************************************************
 * Peripheral register structures
 ******************************************************************************/

/******************************************************************************
 * Flash_IF_MODULE
 ******************************************************************************/
/* Flash interface registers */
typedef struct
{
       uint8_t RESERVED0[4];
  union {
    __IO  uint8_t FRWTR;
    stc_flashif_frwtr_field_t FRWTR_f;
  };
       uint8_t RESERVED1[3];
  union {
    __IO  uint8_t FSTR;
    stc_flashif_fstr_field_t FSTR_f;
  };
       uint8_t RESERVED2[7];
  union {
    __IO  uint8_t FSYNDN;
    stc_flashif_fsyndn_field_t FSYNDN_f;
  };
       uint8_t RESERVED3[15];
  union {
    __IO  uint8_t FICR;
    stc_flashif_ficr_field_t FICR_f;
  };
       uint8_t RESERVED4[3];
  union {
    __IO  uint8_t FISR;
    stc_flashif_fisr_field_t FISR_f;
  };
       uint8_t RESERVED5[3];
  union {
    __IO  uint8_t FICLR;
    stc_flashif_ficlr_field_t FICLR_f;
  };
       uint8_t RESERVED6[215];
  union {
    __IO uint32_t CRTRMM;
    stc_flashif_crtrmm_field_t CRTRMM_f;
  };
}FM0P_FLASH_IF_TypeDef;

/******************************************************************************
* UNIQUE_ID_MODULE
******************************************************************************/
/* Unique ID registers */
typedef struct
{
  union {
    __IO uint32_t UIDR0;
    stc_uid_uidr0_field_t UIDR0_f;
  };
  union {
    __IO uint32_t UIDR1;
    stc_uid_uidr1_field_t UIDR1_f;
  };
}FM0P_UNIQUE_ID_TypeDef;

/******************************************************************************
 * Clock_Reset_MODULE
 ******************************************************************************/
/* Clock and reset registers */
typedef struct
{
  union {
    __IO  uint8_t SCM_CTL;
    stc_crg_scm_ctl_field_t SCM_CTL_f;
  };
       uint8_t RESERVED0[3];
  union {
    __IO  uint8_t SCM_STR;
    stc_crg_scm_str_field_t SCM_STR_f;
  };
       uint8_t RESERVED1[3];
  union {
    __IO uint32_t STB_CTL;
    stc_crg_stb_ctl_field_t STB_CTL_f;
  };
  union {
    __IO uint16_t RST_STR;
    stc_crg_rst_str_field_t RST_STR_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO  uint8_t BSC_PSR;
    stc_crg_bsc_psr_field_t BSC_PSR_f;
  };
       uint8_t RESERVED4[3];
  union {
    __IO  uint8_t APBC0_PSR;
    stc_crg_apbc0_psr_field_t APBC0_PSR_f;
  };
       uint8_t RESERVED5[3];
  union {
    __IO  uint8_t APBC1_PSR;
    stc_crg_apbc1_psr_field_t APBC1_PSR_f;
  };
       uint8_t RESERVED6[7];
  union {
    __IO  uint8_t SWC_PSR;
    stc_crg_swc_psr_field_t SWC_PSR_f;
  };
       uint8_t RESERVED7[15];
  union {
    __IO  uint8_t CSW_TMR;
    stc_crg_csw_tmr_field_t CSW_TMR_f;
  };
       uint8_t RESERVED8[3];
  union {
    __IO  uint8_t PSW_TMR;
    stc_crg_psw_tmr_field_t PSW_TMR_f;
  };
       uint8_t RESERVED9[3];
  union {
    __IO  uint8_t PLL_CTL1;
    stc_crg_pll_ctl1_field_t PLL_CTL1_f;
  };
       uint8_t RESERVED10[3];
  union {
    __IO  uint8_t PLL_CTL2;
    stc_crg_pll_ctl2_field_t PLL_CTL2_f;
  };
       uint8_t RESERVED11[3];
  union {
    __IO uint16_t CSV_CTL;
    stc_crg_csv_ctl_field_t CSV_CTL_f;
  };
       uint8_t RESERVED12[2];
  union {
    __IO  uint8_t CSV_STR;
    stc_crg_csv_str_field_t CSV_STR_f;
  };
       uint8_t RESERVED13[3];
  __IO uint16_t FCSWH_CTL;
       uint8_t RESERVED14[2];
  __IO uint16_t FCSWL_CTL;
       uint8_t RESERVED15[2];
  __IO uint16_t FCSWD_CTL;
       uint8_t RESERVED16[2];
  union {
    __IO  uint8_t DBWDT_CTL;
    stc_crg_dbwdt_ctl_field_t DBWDT_CTL_f;
  };
       uint8_t RESERVED17[11];
  union {
    __IO  uint8_t INT_ENR;
    stc_crg_int_enr_field_t INT_ENR_f;
  };
       uint8_t RESERVED18[3];
  union {
    __IO  uint8_t INT_STR;
    stc_crg_int_str_field_t INT_STR_f;
  };
       uint8_t RESERVED19[3];
  union {
    __IO  uint8_t INT_CLR;
    stc_crg_int_clr_field_t INT_CLR_f;
  };
}FM0P_CRG_TypeDef;

/******************************************************************************
 * HWWDT_MODULE
 ******************************************************************************/
/* Hardware watchdog registers */
typedef struct
{
  __IO uint32_t WDG_LDR;
  __IO uint32_t WDG_VLR;
  union {
    __IO  uint8_t WDG_CTL;
    stc_hwwdt_wdg_ctl_field_t WDG_CTL_f;
  };
       uint8_t RESERVED0[3];
  __IO  uint8_t WDG_ICL;
       uint8_t RESERVED1[3];
  union {
    __IO  uint8_t WDG_RIS;
    stc_hwwdt_wdg_ris_field_t WDG_RIS_f;
  };
        uint8_t RESERVED2[3055];
  __IO uint32_t WDG_LCK;
}FM0P_HWWDT_TypeDef;

/******************************************************************************
 * SWWDT_MODULE
 ******************************************************************************/
/* Software watchdog registers */
typedef struct
{
  __IO uint32_t WDOGLOAD;
  __IO uint32_t WDOGVALUE;
  union {
    __IO  uint8_t WDOGCONTROL;
    stc_swwdt_wdogcontrol_field_t WDOGCONTROL_f;
  };
       uint8_t RESERVED2[3];
  __IO uint32_t WDOGINTCLR;
  union {
    __IO  uint8_t WDOGRIS;
    stc_swwdt_wdogris_field_t WDOGRIS_f;
  };
       uint8_t RESERVED4[7];
  union {
    __IO  uint8_t WDOGSPMC;
    stc_swwdt_wdogspmc_field_t WDOGSPMC_f;
  };
       uint8_t RESERVED5[3047];
  __IO uint32_t WDOGLOCK;
}FM0P_SWWDT_TypeDef;

/******************************************************************************
 * DTIM_MODULE
 ******************************************************************************/
/* Dual timer 1/2 registers */
typedef struct
{
  __IO uint32_t TIMER1LOAD;
  __IO uint32_t TIMER1VALUE;
  union {
    __IO uint32_t TIMER1CONTROL;
    stc_dtim_timer1control_field_t TIMER1CONTROL_f;
  };
  __IO uint32_t TIMER1INTCLR;
  union {
    __IO uint32_t TIMER1RIS;
    stc_dtim_timer1ris_field_t TIMER1RIS_f;
  };
  union {
    __IO uint32_t TIMER1MIS;
    stc_dtim_timer1mis_field_t TIMER1MIS_f;
  };
  __IO uint32_t TIMER1BGLOAD;
       uint8_t RESERVED6[4];
  __IO uint32_t TIMER2LOAD;
  __IO uint32_t TIMER2VALUE;
  union {
    __IO uint32_t TIMER2CONTROL;
    stc_dtim_timer2control_field_t TIMER2CONTROL_f;
  };
  __IO uint32_t TIMER2INTCLR;
  union {
    __IO uint32_t TIMER2RIS;
    stc_dtim_timer2ris_field_t TIMER2RIS_f;
  };
  union {
    __IO uint32_t TIMER2MIS;
    stc_dtim_timer2mis_field_t TIMER2MIS_f;
  };
  __IO uint32_t TIMER2BGLOAD;
}FM0P_DTIM_TypeDef;

/******************************************************************************
 * MFT_FRT_MODULE
 ******************************************************************************/
/* Multifunction Timer unit 0 Free Running Timer registers */
typedef struct
{
       uint8_t RESERVED21[66];
  union {
    __IO uint16_t TCCP0;
    stc_mft_frt_tccp0_field_t TCCP0_f;
  };
       uint8_t RESERVED0[2];
  __IO uint16_t TCDT0;
  union {
    __IO uint16_t TCSA0;
    stc_mft_frt_tcsa0_field_t TCSA0_f;
  };
  union {
    __IO uint16_t TCSC0;
    stc_mft_frt_tcsc0_field_t TCSC0_f;
  };
       uint8_t RESERVED1[2];
  union {
    __IO uint16_t TCCP1;
    stc_mft_frt_tccp1_field_t TCCP1_f;
  };
       uint8_t RESERVED2[2];
  __IO uint16_t TCDT1;
  union {
    __IO uint16_t TCSA1;
    stc_mft_frt_tcsa1_field_t TCSA1_f;
  };
  union {
    __IO uint16_t TCSC1;
    stc_mft_frt_tcsc1_field_t TCSC1_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO uint16_t TCCP2;
    stc_mft_frt_tccp2_field_t TCCP2_f;
  };
       uint8_t RESERVED4[2];
  __IO uint16_t TCDT2;
  union {
    __IO uint16_t TCSA2;
    stc_mft_frt_tcsa2_field_t TCSA2_f;
  };
  union {
    __IO uint16_t TCSC2;
    stc_mft_frt_tcsc2_field_t TCSC2_f;
  };
  union {
    __IO uint32_t TCAL;
    stc_mft_frt_tcal_field_t TCAL_f;
  };
}FM0P_MFT_FRT_TypeDef;


/******************************************************************************
 * MFT_OCU_MODULE
 ******************************************************************************/
/* Multifunction Timer unit 0 Output Compare Unit registers */
typedef struct
{
       uint8_t RESERVED0[2];
  __IO uint16_t OCCP0;
       uint8_t RESERVED1[2];
  __IO uint16_t OCCP1;
       uint8_t RESERVED2[2];
  __IO uint16_t OCCP2;
       uint8_t RESERVED3[2];
  __IO uint16_t OCCP3;
       uint8_t RESERVED4[2];
  __IO uint16_t OCCP4;
       uint8_t RESERVED5[2];
  __IO uint16_t OCCP5;
  union {
    __IO  uint8_t OCSA10;
    stc_mft_ocu_ocsa10_field_t OCSA10_f;
  };
  union {
    __IO  uint8_t OCSB10;
    stc_mft_ocu_ocsb10_field_t OCSB10_f;
  };
  union {
    __IO  uint8_t OCSD10;
    stc_mft_ocu_ocsd10_field_t OCSD10_f;
  };
       uint8_t RESERVED6[1];
  union {
    __IO  uint8_t OCSA32;
    stc_mft_ocu_ocsa32_field_t OCSA32_f;
  };
  union {
    __IO  uint8_t OCSB32;
    stc_mft_ocu_ocsb32_field_t OCSB32_f;
  };
  union {
    __IO  uint8_t OCSD32;
    stc_mft_ocu_ocsd32_field_t OCSD32_f;
  };
       uint8_t RESERVED7[1];
  union {
    __IO  uint8_t OCSA54;
    stc_mft_ocu_ocsa54_field_t OCSA54_f;
  };
  union {
    __IO  uint8_t OCSB54;
    stc_mft_ocu_ocsb54_field_t OCSB54_f;
  };
  union {
    __IO  uint8_t OCSD54;
    stc_mft_ocu_ocsd54_field_t OCSD54_f;
  };
       uint8_t RESERVED8[2];
  union {
    __IO  uint8_t OCSC;
    stc_mft_ocu_ocsc_field_t OCSC_f;
  };
       uint8_t RESERVED15[2];
  union {
    __IO uint16_t OCSE0;
    stc_mft_ocu_ocse0_field_t OCSE0_f;
  };
       uint8_t RESERVED16[2];
  union {
    __IO uint32_t OCSE1;
    stc_mft_ocu_ocse1_field_t OCSE1_f;
  };
  union {
    __IO uint16_t OCSE2;
    stc_mft_ocu_ocse2_field_t OCSE2_f;
  };
       uint8_t RESERVED18[2];
  union {
    __IO uint32_t OCSE3;
    stc_mft_ocu_ocse3_field_t OCSE3_f;
  };
  union {
    __IO uint16_t OCSE4;
    stc_mft_ocu_ocse4_field_t OCSE4_f;
  };
       uint8_t RESERVED20[2];
  union {
    __IO uint32_t OCSE5;
    stc_mft_ocu_ocse5_field_t OCSE5_f;
  };
       uint8_t RESERVED21[40];
  union {
    __IO  uint8_t OCFS10;
    stc_mft_ocu_ocfs10_field_t OCFS10_f;
  };
  union {
    __IO  uint8_t OCFS32;
    stc_mft_ocu_ocfs32_field_t OCFS32_f;
  };
  union {
    __IO  uint8_t OCFS54;
    stc_mft_ocu_ocfs54_field_t OCFS54_f;
  };
}FM0P_MFT_OCU_TypeDef;

/******************************************************************************
 * MFT_WFG_MODULE
 ******************************************************************************/
/* Multifunction Timer unit 0 Waveform Generator and Noise Canceler registers */
typedef struct
{
  uint8_t RESERVED0[142];
  __IO uint16_t WFTF10;
  __IO uint16_t WFTA10;
  __IO uint16_t WFTB10;
       uint8_t RESERVED1[2];
  __IO uint16_t WFTF32;
  __IO uint16_t WFTA32;
  __IO uint16_t WFTB32;
       uint8_t RESERVED2[2];
  __IO uint16_t WFTF54;
  __IO uint16_t WFTA54;
  __IO uint16_t WFTB54;
  union {
    __IO uint16_t WFSA10;
    stc_mft_wfg_wfsa10_field_t WFSA10_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO uint16_t WFSA32;
    stc_mft_wfg_wfsa32_field_t WFSA32_f;
  };
       uint8_t RESERVED4[2];
  union {
    __IO uint16_t WFSA54;
    stc_mft_wfg_wfsa54_field_t WFSA54_f;
  };
       uint8_t RESERVED5[2];
  union {
    __IO uint16_t WFIR;
    stc_mft_wfg_wfir_field_t WFIR_f;
  };
       uint8_t RESERVED6[2];
  union {
    __IO uint16_t NZCL;
    stc_mft_wfg_nzcl_field_t NZCL_f;
  };
}FM0P_MFT_WFG_TypeDef;

/******************************************************************************
 * MFT_ICU_MODULE
 ******************************************************************************/
/* Multifunction Timer unit 0 Input Capture Unit registers */
typedef struct
{
  uint8_t RESERVED0[108];
  union {
    __IO  uint8_t ICFS10;
    stc_mft_icu_icfs10_field_t ICFS10_f;
  };
  union {
    __IO  uint8_t ICFS32;
    stc_mft_icu_icfs32_field_t ICFS32_f;
  };
  uint8_t RESERVED1[8];
  __IO uint16_t ICCP0;
       uint8_t RESERVED2[2];
  __IO uint16_t ICCP1;
       uint8_t RESERVED3[2];
  __IO uint16_t ICCP2;
       uint8_t RESERVED4[2];
  __IO uint16_t ICCP3;
  union {
    __IO  uint8_t ICSA10;
    stc_mft_icu_icsa10_field_t ICSA10_f;
  };
  union {
    __IO  uint8_t ICSB10;
    stc_mft_icu_icsb10_field_t ICSB10_f;
  };
       uint8_t RESERVED5[2];
  union {
    __IO  uint8_t ICSA32;
    stc_mft_icu_icsa32_field_t ICSA32_f;
  };
  union {
    __IO  uint8_t ICSB32;
    stc_mft_icu_icsb32_field_t ICSB32_f;
  };
}FM0P_MFT_ICU_TypeDef;

/******************************************************************************
 * MFT_ADCMP_MODULE
 ******************************************************************************/
/* Multifunction Timer unit 0 ADC Start Compare Unit registers */
typedef struct
{
  uint8_t RESERVED0[112];
  union {
    __IO  uint8_t ACFS10;
    stc_mft_adcmp_acfs10_field_t ACFS10_f;
  };
  union {
    __IO  uint8_t ACFS32;
    stc_mft_adcmp_acfs32_field_t ACFS32_f;
  };
  union {
    __IO  uint8_t ACFS54;
    stc_mft_adcmp_acfs54_field_t ACFS54_f;
  };
       uint8_t RESERVED1[71];
  union {
    __IO uint16_t ACMP0;
    stc_mft_adcmp_acmp0_field_t ACMP0_f;
  };
       uint8_t RESERVED2[2];
  union {
    __IO uint16_t ACMP1;
    stc_mft_adcmp_acmp1_field_t ACMP1_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO uint16_t ACMP2;
    stc_mft_adcmp_acmp2_field_t ACMP2_f;
  };
       uint8_t RESERVED4[2];
  union {
    __IO uint16_t ACMP3;
    stc_mft_adcmp_acmp3_field_t ACMP3_f;
  };
       uint8_t RESERVED5[2];
  union {
    __IO uint16_t ACMP4;
    stc_mft_adcmp_acmp4_field_t ACMP4_f;
  };
       uint8_t RESERVED6[2];
  union {
    __IO uint16_t ACMP5;
    stc_mft_adcmp_acmp5_field_t ACMP5_f;
  };
  union {
    __IO uint16_t ACSA;
    stc_mft_adcmp_acsa_field_t ACSA_f;
  };
       uint8_t RESERVED7[2];
  union {
    __IO  uint8_t ACSC0;
    stc_mft_adcmp_acsc0_field_t ACSC0_f;
  };
  union {
    __IO  uint8_t ACSD0;
    stc_mft_adcmp_acsd0_field_t ACSD0_f;
  };
       uint8_t RESERVED8[2];
  union {
    __IO  uint8_t ACSC1;
    stc_mft_adcmp_acsc1_field_t ACSC1_f;
  };
  union {
    __IO  uint8_t ACSD1;
    stc_mft_adcmp_acsd1_field_t ACSD1_f;
  };
       uint8_t RESERVED9[2];
  union {
    __IO  uint8_t ACSC2;
    stc_mft_adcmp_acsc2_field_t ACSC2_f;
  };
  union {
    __IO  uint8_t ACSD2;
    stc_mft_adcmp_acsd2_field_t ACSD2_f;
  };
       uint8_t RESERVED10[2];
  union {
    __IO  uint8_t ACSC3;
    stc_mft_adcmp_acsc3_field_t ACSC3_f;
  };
  union {
    __IO  uint8_t ACSD3;
    stc_mft_adcmp_acsd3_field_t ACSD3_f;
  };
       uint8_t RESERVED11[2];
  union {
    __IO  uint8_t ACSC4;
    stc_mft_adcmp_acsc4_field_t ACSC4_f;
  };
  union {
    __IO  uint8_t ACSD4;
    stc_mft_adcmp_acsd4_field_t ACSD4_f;
  };
       uint8_t RESERVED14[2];
  union {
    __IO  uint8_t ACSC5;
    stc_mft_adcmp_acsc5_field_t ACSC5_f;
  };
  union {
    __IO  uint8_t ACSD5;
    stc_mft_adcmp_acsd5_field_t ACSD5_f;
  };
}FM0P_MFT_ADCMP_TypeDef;

/******************************************************************************
 * MFT_PPG_MODULE
 ******************************************************************************/
/* Multifunction Timer PPG registers */
typedef struct
{
       uint8_t RESERVED[1]; 
  union {
    __IO uint8_t TTCR0;
    stc_mft_ppg_ttcr0_field_t TTCR0_f;
  };
       uint8_t RESERVED0[7];
  __IO uint8_t COMP0;
       uint8_t RESERVED1[2];
  __IO uint8_t COMP2;
       uint8_t RESERVED2[4];
  __IO uint8_t COMP4;
       uint8_t RESERVED3[2];
  __IO uint8_t COMP6;
       uint8_t RESERVED4[12];
  union {
    __IO uint8_t TTCR1;
    stc_mft_ppg_ttcr1_field_t TTCR1_f;
  };
       uint8_t RESERVED5[7];
  __IO uint8_t COMP1;
       uint8_t RESERVED6[2];
  __IO uint8_t COMP3;
       uint8_t RESERVED7[4];
  __IO uint8_t COMP5;
       uint8_t RESERVED8[2];
  __IO uint8_t COMP7;
       uint8_t RESERVED9[12];
  union {
    __IO uint8_t TTCR2;
    stc_mft_ppg_ttcr2_field_t TTCR2_f;
  };
       uint8_t RESERVED10[7];
  __IO uint8_t COMP8;
       uint8_t RESERVED11[2];
  __IO uint8_t COMP10;
       uint8_t RESERVED12[4];
  __IO uint8_t COMP12;
       uint8_t RESERVED13[2];
  __IO uint8_t COMP14;
       uint8_t RESERVED14[171];
  union {
    __IO uint16_t TRG0;
    stc_mft_ppg_trg0_field_t TRG0_f;
  };
       uint8_t RESERVED15[2];
  union {
    __IO uint16_t REVC0;
    stc_mft_ppg_revc0_field_t REVC0_f;
  };
       uint8_t RESERVED16[58];
  union {
    __IO uint16_t TRG1;
    stc_mft_ppg_trg1_field_t TRG1_f;
  };
       uint8_t RESERVED17[2];
  union {
    __IO uint16_t REVC1;
    stc_mft_ppg_revc1_field_t REVC1_f;
  };
       uint8_t RESERVED18[186];
  union {
    __IO  uint8_t PPGC1;
    stc_mft_ppg_ppgc1_field_t PPGC1_f;
  };
  union {
    __IO  uint8_t PPGC0;
    stc_mft_ppg_ppgc0_field_t PPGC0_f;
  };
       uint8_t RESERVED20[2];
  union {
    __IO  uint8_t PPGC3;
    stc_mft_ppg_ppgc3_field_t PPGC3_f;
  };
  union {
    __IO  uint8_t PPGC2;
    stc_mft_ppg_ppgc2_field_t PPGC2_f;
  };
       uint8_t RESERVED22[2];
  union {
    __IO  uint8_t PRLL0;
    stc_mft_ppg_prll0_field_t PRLL0_f;
  };
  union {
    __IO  uint8_t PRLH0;
    stc_mft_ppg_prlh0_field_t PRLH0_f;
  };
       uint8_t RESERVED24[2];
  union {
    __IO  uint8_t PRLL1;
    stc_mft_ppg_prll1_field_t PRLL1_f;
  };
  union {
    __IO  uint8_t PRLH1;
    stc_mft_ppg_prlh1_field_t PRLH1_f;
  };
       uint8_t RESERVED26[2];
  union {
    __IO  uint8_t PRLL2;
    stc_mft_ppg_prll2_field_t PRLL2_f;
  };
  union {
    __IO  uint8_t PRLH2;
    stc_mft_ppg_prlh2_field_t PRLH2_f;
  };
       uint8_t RESERVED28[2];
  union {
    __IO  uint8_t PRLL3;
    stc_mft_ppg_prll3_field_t PRLL3_f;
  };
  union {
    __IO  uint8_t PRLH3;
    stc_mft_ppg_prlh3_field_t PRLH3_f;
  };
       uint8_t RESERVED30[2];
  union {
    __IO  uint8_t GATEC0;
    stc_mft_ppg_gatec0_field_t GATEC0_f;
  };
       uint8_t RESERVED31[39];
  union {
    __IO  uint8_t PPGC5;
    stc_mft_ppg_ppgc5_field_t PPGC5_f;
  };
  union {
    __IO  uint8_t PPGC4;
    stc_mft_ppg_ppgc4_field_t PPGC4_f;
  };
       uint8_t RESERVED33[2];
  union {
    __IO  uint8_t PPGC7;
    stc_mft_ppg_ppgc7_field_t PPGC7_f;
  };
  union {
    __IO  uint8_t PPGC6;
    stc_mft_ppg_ppgc6_field_t PPGC6_f;
  };
       uint8_t RESERVED35[2];
  union {
    __IO  uint8_t PRLL4;
    stc_mft_ppg_prll4_field_t PRLL4_f;
  };
  union {
    __IO  uint8_t PRLH4;
    stc_mft_ppg_prlh4_field_t PRLH4_f;
  };
       uint8_t RESERVED37[2];
  union {
    __IO  uint8_t PRLL5;
    stc_mft_ppg_prll5_field_t PRLL5_f;
  };
  union {
    __IO  uint8_t PRLH5;
    stc_mft_ppg_prlh5_field_t PRLH5_f;
  };
       uint8_t RESERVED39[2];
  union {
    __IO  uint8_t PRLL6;
    stc_mft_ppg_prll6_field_t PRLL6_f;
  };
  union {
    __IO  uint8_t PRLH6;
    stc_mft_ppg_prlh6_field_t PRLH6_f;
  };
       uint8_t RESERVED41[2];
  union {
    __IO  uint8_t PRLL7;
    stc_mft_ppg_prll7_field_t PRLL7_f;
  };
  union {
    __IO  uint8_t PRLH7;
    stc_mft_ppg_prlh7_field_t PRLH7_f;
  };
       uint8_t RESERVED43[2];
  union {
    __IO  uint8_t GATEC4;
    stc_mft_ppg_gatec4_field_t GATEC4_f;
  };
       uint8_t RESERVED44[39];
  union {
    __IO  uint8_t PPGC9;
    stc_mft_ppg_ppgc9_field_t PPGC9_f;
  };
  union {
    __IO  uint8_t PPGC8;
    stc_mft_ppg_ppgc8_field_t PPGC8_f;
  };
       uint8_t RESERVED46[2];
  union {
    __IO  uint8_t PPGC11;
    stc_mft_ppg_ppgc11_field_t PPGC11_f;
  };
  union {
    __IO  uint8_t PPGC10;
    stc_mft_ppg_ppgc10_field_t PPGC10_f;
  };
       uint8_t RESERVED48[2];
  union {
    __IO  uint8_t PRLL8;
    stc_mft_ppg_prll8_field_t PRLL8_f;
  };
  union {
    __IO  uint8_t PRLH8;
    stc_mft_ppg_prlh8_field_t PRLH8_f;
  };
       uint8_t RESERVED50[2];
  union {
    __IO  uint8_t PRLL9;
    stc_mft_ppg_prll9_field_t PRLL9_f;
  };
  union {
    __IO  uint8_t PRLH9;
    stc_mft_ppg_prlh9_field_t PRLH9_f;
  };
       uint8_t RESERVED52[2];
  union {
    __IO  uint8_t PRLL10;
    stc_mft_ppg_prll10_field_t PRLL10_f;
  };
  union {
    __IO  uint8_t PRLH10;
    stc_mft_ppg_prlh10_field_t PRLH10_f;
  };
       uint8_t RESERVED54[2];
  union {
    __IO  uint8_t PRLL11;
    stc_mft_ppg_prll11_field_t PRLL11_f;
  };
  union {
    __IO  uint8_t PRLH11;
    stc_mft_ppg_prlh11_field_t PRLH11_f;
  };
       uint8_t RESERVED56[2];
  union {
    __IO  uint8_t GATEC8;
    stc_mft_ppg_gatec8_field_t GATEC8_f;
  };
       uint8_t RESERVED57[39];
  union {
    __IO  uint8_t PPGC13;
    stc_mft_ppg_ppgc13_field_t PPGC13_f;
  };
  union {
    __IO  uint8_t PPGC12;
    stc_mft_ppg_ppgc12_field_t PPGC12_f;
  };
       uint8_t RESERVED59[2];
  union {
    __IO  uint8_t PPGC15;
    stc_mft_ppg_ppgc15_field_t PPGC15_f;
  };
  union {
    __IO  uint8_t PPGC14;
    stc_mft_ppg_ppgc14_field_t PPGC14_f;
  };
       uint8_t RESERVED61[2];
  union {
    __IO  uint8_t PRLL12;
    stc_mft_ppg_prll12_field_t PRLL12_f;
  };
  union {
    __IO  uint8_t PRLH12;
    stc_mft_ppg_prlh12_field_t PRLH12_f;
  };
       uint8_t RESERVED63[2];
  union {
    __IO  uint8_t PRLL13;
    stc_mft_ppg_prll13_field_t PRLL13_f;
  };
  union {
    __IO  uint8_t PRLH13;
    stc_mft_ppg_prlh13_field_t PRLH13_f;
  };
       uint8_t RESERVED65[2];
  union {
    __IO  uint8_t PRLL14;
    stc_mft_ppg_prll14_field_t PRLL14_f;
  };
  union {
    __IO  uint8_t PRLH14;
    stc_mft_ppg_prlh14_field_t PRLH14_f;
  };
       uint8_t RESERVED67[2];
  union {
    __IO  uint8_t PRLL15;
    stc_mft_ppg_prll15_field_t PRLL15_f;
  };
  union {
    __IO  uint8_t PRLH15;
    stc_mft_ppg_prlh15_field_t PRLH15_f;
  };
       uint8_t RESERVED69[2];
  union {
    __IO  uint8_t GATEC12;
    stc_mft_ppg_gatec12_field_t GATEC12_f;
  };
       uint8_t RESERVED70[39];
  union {
    __IO  uint8_t PPGC17;
    stc_mft_ppg_ppgc17_field_t PPGC17_f;
  };
  union {
    __IO  uint8_t PPGC16;
    stc_mft_ppg_ppgc16_field_t PPGC16_f;
  };
       uint8_t RESERVED72[2];
  union {
    __IO  uint8_t PPGC19;
    stc_mft_ppg_ppgc19_field_t PPGC19_f;
  };
  union {
    __IO  uint8_t PPGC18;
    stc_mft_ppg_ppgc18_field_t PPGC18_f;
  };
       uint8_t RESERVED74[2];
  union {
    __IO  uint8_t PRLL16;
    stc_mft_ppg_prll16_field_t PRLL16_f;
  };
  union {
    __IO  uint8_t PRLH16;
    stc_mft_ppg_prlh16_field_t PRLH16_f;
  };
       uint8_t RESERVED76[2];
  union {
    __IO  uint8_t PRLL17;
    stc_mft_ppg_prll17_field_t PRLL17_f;
  };
  union {
    __IO  uint8_t PRLH17;
    stc_mft_ppg_prlh17_field_t PRLH17_f;
  };
       uint8_t RESERVED78[2];
  union {
    __IO  uint8_t PRLL18;
    stc_mft_ppg_prll18_field_t PRLL18_f;
  };
  union {
    __IO  uint8_t PRLH18;
    stc_mft_ppg_prlh18_field_t PRLH18_f;
  };
       uint8_t RESERVED80[2];
  union {
    __IO  uint8_t PRLL19;
    stc_mft_ppg_prll19_field_t PRLL19_f;
  };
  union {
    __IO  uint8_t PRLH19;
    stc_mft_ppg_prlh19_field_t PRLH19_f;
  };
       uint8_t RESERVED82[2];
  union {
    __IO  uint8_t GATEC16;
    stc_mft_ppg_gatec16_field_t GATEC16_f;
  };
       uint8_t RESERVED83[39];
  union {
    __IO  uint8_t PPGC21;
    stc_mft_ppg_ppgc21_field_t PPGC21_f;
  };
  union {
    __IO  uint8_t PPGC20;
    stc_mft_ppg_ppgc20_field_t PPGC20_f;
  };
       uint8_t RESERVED85[2];
  union {
    __IO  uint8_t PPGC23;
    stc_mft_ppg_ppgc23_field_t PPGC23_f;
  };
  union {
    __IO  uint8_t PPGC22;
    stc_mft_ppg_ppgc22_field_t PPGC22_f;
  };
       uint8_t RESERVED87[2];
  union {
    __IO  uint8_t PRLL20;
    stc_mft_ppg_prll20_field_t PRLL20_f;
  };
  union {
    __IO  uint8_t PRLH20;
    stc_mft_ppg_prlh20_field_t PRLH20_f;
  };
       uint8_t RESERVED89[2];
  union {
    __IO  uint8_t PRLL21;
    stc_mft_ppg_prll21_field_t PRLL21_f;
  };
  union {
    __IO  uint8_t PRLH21;
    stc_mft_ppg_prlh21_field_t PRLH21_f;
  };
       uint8_t RESERVED91[2];
  union {
    __IO  uint8_t PRLL22;
    stc_mft_ppg_prll22_field_t PRLL22_f;
  };
  union {
    __IO  uint8_t PRLH22;
    stc_mft_ppg_prlh22_field_t PRLH22_f;
  };
       uint8_t RESERVED93[2];
  union {
    __IO  uint8_t PRLL23;
    stc_mft_ppg_prll23_field_t PRLL23_f;
  };
  union {
    __IO  uint8_t PRLH23;
    stc_mft_ppg_prlh23_field_t PRLH23_f;
  };
       uint8_t RESERVED95[2];
  union {
    __IO  uint8_t GATEC20;
    stc_mft_ppg_gatec20_field_t GATEC20_f;
  };
       uint8_t RESERVED96[39];
  union {
    __IO  uint8_t IGBTC;
    stc_mft_ppg_igbtc_field_t IGBTC_f;
  };
}FM0P_MFT_PPG_TypeDef;

/******************************************************************************
 * BT_PPG_MODULE
 ******************************************************************************/
/* Base Timer 0 PPG registers */
typedef struct
{
  __IO uint16_t PRLL;
        uint8_t RESERVED0[2];
  __IO uint16_t PRLH;
        uint8_t RESERVED1[2];
  __IO uint16_t TMR;
        uint8_t RESERVED2[2];
  union {
    __IO uint16_t TMCR;
    stc_bt_ppg_tmcr_field_t TMCR_f;
  };
        uint8_t RESERVED3[2];
  union {
    __IO  uint8_t STC;
    stc_bt_ppg_stc_field_t STC_f;
  };
  union {
    __IO  uint8_t TMCR2;
    stc_bt_ppg_tmcr2_field_t TMCR2_f;
  };
}FM0P_BT_PPG_TypeDef;

/******************************************************************************
 * BT_PWM_MODULE
 ******************************************************************************/
/* Base Timer 0 PWM registers */
typedef struct
{
  __IO uint16_t PCSR;
        uint8_t RESERVED0[2];
  __IO uint16_t PDUT;
        uint8_t RESERVED1[2];
  __IO uint16_t TMR;
        uint8_t RESERVED2[2];
  union {
    __IO uint16_t TMCR;
    stc_bt_pwm_tmcr_field_t TMCR_f;
  };
        uint8_t RESERVED3[2];
  union {
    __IO  uint8_t STC;
    stc_bt_pwm_stc_field_t STC_f;
  };
  union {
    __IO  uint8_t TMCR2;
    stc_bt_pwm_tmcr2_field_t TMCR2_f;
  };
}FM0P_BT_PWM_TypeDef;

/******************************************************************************
 * BT_RT_MODULE
 ******************************************************************************/
/* Base Timer 0 RT registers */
typedef struct
{
  __IO uint16_t PCSR;
        uint8_t RESERVED0[6];
  __IO uint16_t TMR;
        uint8_t RESERVED1[2];
  union {
    __IO uint16_t TMCR;
    stc_bt_rt_tmcr_field_t TMCR_f;
  };
        uint8_t RESERVED2[2];
  union {
    __IO  uint8_t STC;
    stc_bt_rt_stc_field_t STC_f;
  };
  union {
    __IO  uint8_t TMCR2;
    stc_bt_rt_tmcr2_field_t TMCR2_f;
  };
}FM0P_BT_RT_TypeDef;

/******************************************************************************
 * BT_PWC_MODULE
 ******************************************************************************/
/* Base Timer 0 PWC registers */
typedef struct
{
        uint8_t RESERVED0[4];
  __IO uint16_t DTBF;
        uint8_t RESERVED1[6];
  union {
    __IO uint16_t TMCR;
    stc_bt_pwc_tmcr_field_t TMCR_f;
  };
        uint8_t RESERVED2[2];
  union {
    __IO  uint8_t STC;
    stc_bt_pwc_stc_field_t STC_f;
  };
  union {
    __IO  uint8_t TMCR2;
    stc_bt_pwc_tmcr2_field_t TMCR2_f;
  };
}FM0P_BT_PWC_TypeDef;

/******************************************************************************
 * BTIOSEL03_MODULE
 ******************************************************************************/
/* Base Timer I/O selector channel 0 - channel 3 registers */
typedef struct
{
  union {
    __IO uint16_t BTSEL0123;
    stc_btiosel03_btsel0123_field_t BTSEL0123_f;
  };
}FM0P_BTIOSEL03_TypeDef;

/******************************************************************************
 * SBSSR_MODULE
 ******************************************************************************/
/* Software based Simulation Startup (Base Timer) register */
typedef struct
{
  union {
    __IO uint16_t BTSSSR;
    stc_sbssr_btsssr_field_t BTSSSR_f;
  };
}FM0P_SBSSR_TypeDef;

/******************************************************************************
 * QPRC_MODULE
 ******************************************************************************/
/* Quad position and revolution counter channel 0 registers */
typedef struct
{
  __IO uint16_t QPCR;
       uint8_t RESERVED0[2];
  __IO uint16_t QRCR;
       uint8_t RESERVED1[2];
  __IO uint16_t QPCCR;
       uint8_t RESERVED2[2];
  __IO uint16_t QPRCR;
       uint8_t RESERVED3[2];
  __IO uint16_t QMPR;
       uint8_t RESERVED4[2];
  union {
    __IO  uint8_t QICRL;
    stc_qprc0_qicrl_field_t QICRL_f;
  };
  union {
    __IO  uint8_t QICRH;
    stc_qprc0_qicrh_field_t QICRH_f;
  };
       uint8_t RESERVED6[2];
  union {
    __IO  uint8_t QCRL;
    stc_qprc0_qcrl_field_t QCRL_f;
  };
  union {
    __IO  uint8_t QCRH;
    stc_qprc0_qcrh_field_t QCRH_f;
  };
       uint8_t RESERVED8[2];
  union {
    __IO uint16_t QECR;
    stc_qprc0_qecr_field_t QECR_f;
  };
       uint8_t RESERVED9[30];
  __IO uint16_t QRCRR;
  __IO uint16_t QPCRR;
}FM0P_QPRC_TypeDef;

/******************************************************************************
 * QPRC_NF_MODULE
 ******************************************************************************/
/* QPRC_NF registers */
typedef struct
{
  union {
    __IO  uint8_t NFCTLA;
    stc_qprc0_nf_nfctla_field_t NFCTLA_f;
  };
       uint8_t RESERVED0[3];
  union {
    __IO  uint8_t NFCTLB;
    stc_qprc0_nf_nfctlb_field_t NFCTLB_f;
  };
       uint8_t RESERVED1[3];
  union {
    __IO  uint8_t NFCTLZ;
    stc_qprc0_nf_nfctlz_field_t NFCTLZ_f;
  };
}FM0P_QPRC_NF_TypeDef;

/******************************************************************************
 * ADC12_MODULE
 ******************************************************************************/
/* ADC0 registers */
typedef struct
{
  union {
    __IO  uint8_t ADSR;
    stc_adc0_adsr_field_t ADSR_f;
  };
  union {
    __IO  uint8_t ADCR;
    stc_adc0_adcr_field_t ADCR_f;
  };
       uint8_t RESERVED1[6];
  union {
    __IO  uint8_t SFNS;
    stc_adc0_sfns_field_t SFNS_f;
  };
  union {
    __IO  uint8_t SCCR;
    stc_adc0_sccr_field_t SCCR_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO uint32_t SCFD;
    stc_adc0_scfd_field_t SCFD_f;
  };
  union {
    __IO  uint8_t SCIS2;
    stc_adc0_scis2_field_t SCIS2_f;
  };
  union {
    __IO  uint8_t SCIS3;
    stc_adc0_scis3_field_t SCIS3_f;
  };
       uint8_t RESERVED6[2];
  union {
    __IO  uint8_t SCIS0;
    stc_adc0_scis0_field_t SCIS0_f;
  };
  union {
    __IO  uint8_t SCIS1;
    stc_adc0_scis1_field_t SCIS1_f;
  };
       uint8_t RESERVED8[2];
  union {
    __IO  uint8_t PFNS;
    stc_adc0_pfns_field_t PFNS_f;
  };
  union {
    __IO  uint8_t PCCR;
    stc_adc0_pccr_field_t PCCR_f;
  };
       uint8_t RESERVED10[2];
  union {
    __IO uint32_t PCFD;
    stc_adc0_pcfd_field_t PCFD_f;
  };
  union {
    __IO  uint8_t PCIS;
    stc_adc0_pcis_field_t PCIS_f;
  };
       uint8_t RESERVED12[3];
  union {
    __IO  uint8_t CMPCR;
    stc_adc0_cmpcr_field_t CMPCR_f;
  };
       uint8_t RESERVED13[1];
  union {
    __IO uint16_t CMPD;
    stc_adc0_cmpd_field_t CMPD_f;
  };
  union {
    __IO  uint8_t ADSS2;
    stc_adc0_adss2_field_t ADSS2_f;
  };
  union {
    __IO  uint8_t ADSS3;
    stc_adc0_adss3_field_t ADSS3_f;
  };
       uint8_t RESERVED16[2];
  union {
    __IO  uint8_t ADSS0;
    stc_adc0_adss0_field_t ADSS0_f;
  };
  union {
    __IO  uint8_t ADSS1;
    stc_adc0_adss1_field_t ADSS1_f;
  };
       uint8_t RESERVED18[2];
  union {
    __IO  uint8_t ADST1;
    stc_adc0_adst1_field_t ADST1_f;
  };
  union {
    __IO  uint8_t ADST0;
    stc_adc0_adst0_field_t ADST0_f;
  };
       uint8_t RESERVED20[2];
  union {
    __IO  uint8_t ADCT;
    stc_adc0_adct_field_t ADCT_f;
  };
       uint8_t RESERVED21[3];
  union {
    __IO  uint8_t PRTSL;
    stc_adc0_prtsl_field_t PRTSL_f;
  };
  union {
    __IO  uint8_t SCTSL;
    stc_adc0_sctsl_field_t SCTSL_f;
  };
       uint8_t RESERVED23[2];
  union {
    __IO uint16_t ADCEN;
    stc_adc0_adcen_field_t ADCEN_f;
  };
       uint8_t RESERVED24[6];
  union {
    __IO uint32_t WCMRCIF;
    stc_adc0_wcmrcif_field_t WCMRCIF_f;
  };
  union {
    __IO uint32_t WCMRCOT;
    stc_adc0_wcmrcot_field_t WCMRCOT_f;
  };
  union {
    __IO  uint8_t WCMPCR;
    stc_adc0_wcmpcr_field_t WCMPCR_f;
  };
  union {
    __IO  uint8_t WCMPSR;
    stc_adc0_wcmpsr_field_t WCMPSR_f;
  };
       uint8_t RESERVED28[2];
  union {
    __IO uint16_t WCMPDL;
    stc_adc0_wcmpdl_field_t WCMPDL_f;
  };
  union {
    __IO uint16_t WCMPDH;
    stc_adc0_wcmpdh_field_t WCMPDH_f;
  };
}FM0P_ADC_TypeDef;

/******************************************************************************
 * CRTRIM_MODULE
 ******************************************************************************/
/* CR trimming registers */
typedef struct
{
  union {
    __IO  uint8_t MCR_PSR;
    stc_crtrim_mcr_psr_field_t MCR_PSR_f;
  };
       uint8_t RESERVED0[3];
  union {
    __IO uint16_t MCR_FTRM;
    stc_crtrim_mcr_ftrm_field_t MCR_FTRM_f;
  };
       uint8_t RESERVED1[2];
  union {
    __IO  uint8_t MCR_TTRM;
    stc_crtrim_mcr_ttrm_field_t MCR_TTRM_f;
  };
       uint8_t RESERVED2[3];
  union {
    __IO uint32_t MCR_RLR;
    stc_crtrim_mcr_rlr_field_t MCR_RLR_f;
  };
}FM0P_CRTRIM_TypeDef;

/******************************************************************************
 * EXTI_MODULE
 ******************************************************************************/
/* External interrupt registers */
typedef struct
{
  union {
    __IO uint32_t ENIR;
    stc_exti_enir_field_t ENIR_f;
  };
  union {
    __IO uint32_t EIRR;
    stc_exti_eirr_field_t EIRR_f;
  };
  union {
    __IO uint32_t EICL;
    stc_exti_eicl_field_t EICL_f;
  };
  union {
    __IO uint32_t ELVR;
    stc_exti_elvr_field_t ELVR_f;
  };
       uint8_t RESERVED5[4];
  union {
    __IO uint16_t NMIRR;
    stc_exti_nmirr_field_t NMIRR_f;
  };
       uint8_t RESERVED6[2];
  union {
    __IO uint16_t NMICL;
    stc_exti_nmicl_field_t NMICL_f;
  };
}FM0P_EXTI_TypeDef;

/******************************************************************************
 * INTREQ_MODULE
 ******************************************************************************/
/* Interrupt request read registers */
typedef struct
{
  union {
    __IO uint32_t DRQSEL;
    stc_intreq_drqsel_field_t DRQSEL_f;
  };
       uint8_t RESERVED0[8];
  union {
    __IO uint32_t IRQCMODE;
    stc_intreq_irqcmode_field_t IRQCMODE_f;
  };
  union {
    __IO uint32_t EXC02MON;
    stc_intreq_exc02mon_field_t EXC02MON_f;
  };
  union {
    __IO uint32_t IRQ00MON;
    stc_intreq_irq00mon_field_t IRQ00MON_f;
  };
  union {
    __IO uint32_t IRQ01MON;
    stc_intreq_irq01mon_field_t IRQ01MON_f;
  };
  union {
    __IO uint32_t IRQ02MON;
    stc_intreq_irq02mon_field_t IRQ02MON_f;
  };
  union {
    __IO uint32_t IRQ03MON;
    stc_intreq_irq03mon_field_t IRQ03MON_f;
  };
  union {
    __IO uint32_t IRQ04MON;
    stc_intreq_irq04mon_field_t IRQ04MON_f;
  };
  union {
    __IO uint32_t IRQ05MON;
    stc_intreq_irq05mon_field_t IRQ05MON_f;
  };
  union {
    __IO uint32_t IRQ06MON;
    stc_intreq_irq06mon_field_t IRQ06MON_f;
  };
  union {
    __IO uint32_t IRQ07MON;
    stc_intreq_irq07mon_field_t IRQ07MON_f;
  };
  union {
    __IO uint32_t IRQ08MON;
    stc_intreq_irq08mon_field_t IRQ08MON_f;
  };
  union {
    __IO uint32_t IRQ09MON;
    stc_intreq_irq09mon_field_t IRQ09MON_f;
  };
  union {
    __IO uint32_t IRQ10MON;
    stc_intreq_irq10mon_field_t IRQ10MON_f;
  };
  union {
    __IO uint32_t IRQ11MON;
    stc_intreq_irq11mon_field_t IRQ11MON_f;
  };
  union {
    __IO uint32_t IRQ12MON;
    stc_intreq_irq12mon_field_t IRQ12MON_f;
  };
  union {
    __IO uint32_t IRQ13MON;
    stc_intreq_irq13mon_field_t IRQ13MON_f;
  };
  union {
    __IO uint32_t IRQ14MON;
    stc_intreq_irq14mon_field_t IRQ14MON_f;
  };
  union {
    __IO uint32_t IRQ15MON;
    stc_intreq_irq15mon_field_t IRQ15MON_f;
  };
  union {
    __IO uint32_t IRQ16MON;
    stc_intreq_irq16mon_field_t IRQ16MON_f;
  };
  union {
    __IO uint32_t IRQ17MON;
    stc_intreq_irq17mon_field_t IRQ17MON_f;
  };
  union {
    __IO uint32_t IRQ18MON;
    stc_intreq_irq18mon_field_t IRQ18MON_f;
  };
  union {
    __IO uint32_t IRQ19MON;
    stc_intreq_irq19mon_field_t IRQ19MON_f;
  };
  union {
    __IO uint32_t IRQ20MON;
    stc_intreq_irq20mon_field_t IRQ20MON_f;
  };
  union {
    __IO uint32_t IRQ21MON;
    stc_intreq_irq21mon_field_t IRQ21MON_f;
  };
  union {
    __IO uint32_t IRQ22MON;
    stc_intreq_irq22mon_field_t IRQ22MON_f;
  };
  union {
    __IO uint32_t IRQ23MON;
    stc_intreq_irq23mon_field_t IRQ23MON_f;
  };
  union {
    __IO uint32_t IRQ24MON;
    stc_intreq_irq24mon_field_t IRQ24MON_f;
  };
  union {
    __IO uint32_t IRQ25MON;
    stc_intreq_irq25mon_field_t IRQ25MON_f;
  };
  union {
    __IO uint32_t IRQ26MON;
    stc_intreq_irq26mon_field_t IRQ26MON_f;
  };
  union {
    __IO uint32_t IRQ27MON;
    stc_intreq_irq27mon_field_t IRQ27MON_f;
  };
  union {
    __IO uint32_t IRQ28MON;
    stc_intreq_irq28mon_field_t IRQ28MON_f;
  };
  union {
    __IO uint32_t IRQ29MON;
    stc_intreq_irq29mon_field_t IRQ29MON_f;
  };
  union {
    __IO uint32_t IRQ30MON;
    stc_intreq_irq30mon_field_t IRQ30MON_f;
  };
  union {
    __IO uint32_t IRQ31MON;
    stc_intreq_irq31mon_field_t IRQ31MON_f;
  };
}FM0P_INTREQ_TypeDef;

/******************************************************************************
 * GPIO_MODULE
 ******************************************************************************/
/* General purpose I/O registers */
typedef struct
{
  union {
    __IO uint32_t PFR0;
    stc_gpio_pfr0_field_t PFR0_f;
  };
  union {
    __IO uint32_t PFR1;
    stc_gpio_pfr1_field_t PFR1_f;
  };
  union {
    __IO uint32_t PFR2;
    stc_gpio_pfr2_field_t PFR2_f;
  };
  union {
    __IO uint32_t PFR3;
    stc_gpio_pfr3_field_t PFR3_f;
  };
  union {
    __IO uint32_t PFR4;
    stc_gpio_pfr4_field_t PFR4_f;
  };
  union {
    __IO uint32_t PFR5;
    stc_gpio_pfr5_field_t PFR5_f;
  };
  union {
    __IO uint32_t PFR6;
    stc_gpio_pfr6_field_t PFR6_f;
  };
       uint8_t RESERVED6[4];
  union {
    __IO uint32_t PFR8;
    stc_gpio_pfr8_field_t PFR8_f;
  };
       uint8_t RESERVED7[20];
  union {
    __IO uint32_t PFRE;
    stc_gpio_pfre_field_t PFRE_f;
  };
       uint8_t RESERVED8[196];
  union {
    __IO uint32_t PCR0;
    stc_gpio_pcr0_field_t PCR0_f;
  };
  union {
    __IO uint32_t PCR1;
    stc_gpio_pcr1_field_t PCR1_f;
  };
  union {
    __IO uint32_t PCR2;
    stc_gpio_pcr2_field_t PCR2_f;
  };
  union {
    __IO uint32_t PCR3;
    stc_gpio_pcr3_field_t PCR3_f;
  };
  union {
    __IO uint32_t PCR4;
    stc_gpio_pcr4_field_t PCR4_f;
  };
  union {
    __IO uint32_t PCR5;
    stc_gpio_pcr5_field_t PCR5_f;
  };
  union {
    __IO uint32_t PCR6;
    stc_gpio_pcr6_field_t PCR6_f;
  };
       uint8_t RESERVED15[4];
  union {
    __IO uint32_t PCR8;
    stc_gpio_pcr8_field_t PCR8_f;
  };
       uint8_t RESERVED16[20];
  union {
    __IO uint32_t PCRE;
    stc_gpio_pcre_field_t PCRE_f;
  };
       uint8_t RESERVED17[196];
  union {
    __IO uint32_t DDR0;
    stc_gpio_ddr0_field_t DDR0_f;
  };
  union {
    __IO uint32_t DDR1;
    stc_gpio_ddr1_field_t DDR1_f;
  };
  union {
    __IO uint32_t DDR2;
    stc_gpio_ddr2_field_t DDR2_f;
  };
  union {
    __IO uint32_t DDR3;
    stc_gpio_ddr3_field_t DDR3_f;
  };
  union {
    __IO uint32_t DDR4;
    stc_gpio_ddr4_field_t DDR4_f;
  };
  union {
    __IO uint32_t DDR5;
    stc_gpio_ddr5_field_t DDR5_f;
  };
  union {
    __IO uint32_t DDR6;
    stc_gpio_ddr6_field_t DDR6_f;
  };
       uint8_t RESERVED24[4];
  union {
    __IO uint32_t DDR8;
    stc_gpio_ddr8_field_t DDR8_f;
  };
       uint8_t RESERVED25[20];
  union {
    __IO uint32_t DDRE;
    stc_gpio_ddre_field_t DDRE_f;
  };
       uint8_t RESERVED26[196];
  union {
    __IO uint32_t PDIR0;
    stc_gpio_pdir0_field_t PDIR0_f;
  };
  union {
    __IO uint32_t PDIR1;
    stc_gpio_pdir1_field_t PDIR1_f;
  };
  union {
    __IO uint32_t PDIR2;
    stc_gpio_pdir2_field_t PDIR2_f;
  };
  union {
    __IO uint32_t PDIR3;
    stc_gpio_pdir3_field_t PDIR3_f;
  };
  union {
    __IO uint32_t PDIR4;
    stc_gpio_pdir4_field_t PDIR4_f;
  };
  union {
    __IO uint32_t PDIR5;
    stc_gpio_pdir5_field_t PDIR5_f;
  };
  union {
    __IO uint32_t PDIR6;
    stc_gpio_pdir6_field_t PDIR6_f;
  };
       uint8_t RESERVED33[4];
  union {
    __IO uint32_t PDIR8;
    stc_gpio_pdir8_field_t PDIR8_f;
  };
       uint8_t RESERVED34[20];
  union {
    __IO uint32_t PDIRE;
    stc_gpio_pdire_field_t PDIRE_f;
  };
       uint8_t RESERVED35[196];
  union {
    __IO uint32_t PDOR0;
    stc_gpio_pdor0_field_t PDOR0_f;
  };
  union {
    __IO uint32_t PDOR1;
    stc_gpio_pdor1_field_t PDOR1_f;
  };
  union {
    __IO uint32_t PDOR2;
    stc_gpio_pdor2_field_t PDOR2_f;
  };
  union {
    __IO uint32_t PDOR3;
    stc_gpio_pdor3_field_t PDOR3_f;
  };
  union {
    __IO uint32_t PDOR4;
    stc_gpio_pdor4_field_t PDOR4_f;
  };
  union {
    __IO uint32_t PDOR5;
    stc_gpio_pdor5_field_t PDOR5_f;
  };
  union {
    __IO uint32_t PDOR6;
    stc_gpio_pdor6_field_t PDOR6_f;
  };
       uint8_t RESERVED42[4];
  union {
    __IO uint32_t PDOR8;
    stc_gpio_pdor8_field_t PDOR8_f;
  };
       uint8_t RESERVED43[20];
  union {
    __IO uint32_t PDORE;
    stc_gpio_pdore_field_t PDORE_f;
  };
       uint8_t RESERVED44[196];
  union {
    __IO uint32_t ADE;
    stc_gpio_ade_field_t ADE_f;
  };
       uint8_t RESERVED45[124];
  union {
    __IO uint32_t SPSR;
    stc_gpio_spsr_field_t SPSR_f;
  };
       uint8_t RESERVED46[124];
  union {
    __IO uint32_t EPFR00;
    stc_gpio_epfr00_field_t EPFR00_f;
  };
  union {
    __IO uint32_t EPFR01;
    stc_gpio_epfr01_field_t EPFR01_f;
  };
  union {
    __IO uint32_t EPFR02;
    stc_gpio_epfr02_field_t EPFR02_f;
  };
  union {
    __IO uint32_t EPFR03;
    stc_gpio_epfr03_field_t EPFR03_f;
  };
  union {
    __IO uint32_t EPFR04;
    stc_gpio_epfr04_field_t EPFR04_f;
  };
  union {
    __IO uint32_t EPFR05;
    stc_gpio_epfr05_field_t EPFR05_f;
  };
  union {
    __IO uint32_t EPFR06;
    stc_gpio_epfr06_field_t EPFR06_f;
  };
  union {
    __IO uint32_t EPFR07;
    stc_gpio_epfr07_field_t EPFR07_f;
  };
  union {
    __IO uint32_t EPFR08;
    stc_gpio_epfr08_field_t EPFR08_f;
  };
  union {
    __IO uint32_t EPFR09;
    stc_gpio_epfr09_field_t EPFR09_f;
  };
       uint8_t RESERVED55[8];
  union {
    __IO uint32_t EPFR12;
    stc_gpio_epfr12_field_t EPFR12_f;
  };
  union {
    __IO uint32_t EPFR13;
    stc_gpio_epfr13_field_t EPFR13_f;
  };
  union {
    __IO uint32_t EPFR14;
    stc_gpio_epfr14_field_t EPFR14_f;
  };
  union {
    __IO uint32_t EPFR15;
    stc_gpio_epfr15_field_t EPFR15_f;
  };
  union {
    __IO uint32_t EPFR16;
    stc_gpio_epfr16_field_t EPFR16_f;
  };
  union {
    __IO uint32_t EPFR17;
    stc_gpio_epfr17_field_t EPFR17_f;
  };
  union {
    __IO uint32_t EPFR18;
    stc_gpio_epfr18_field_t EPFR18_f;
  };
       uint8_t RESERVED60[8];
  union {
    __IO uint32_t EPFR21;
    stc_gpio_epfr21_field_t EPFR21_f;
  };
  union {
    __IO uint32_t EPFR22;
    stc_gpio_epfr22_field_t EPFR22_f;
  };
       uint8_t RESERVED62[164];
  union {
    __IO uint32_t PZR0;
    stc_gpio_pzr0_field_t PZR0_f;
  };
  union {
    __IO uint32_t PZR1;
    stc_gpio_pzr1_field_t PZR1_f;
  };
  union {
    __IO uint32_t PZR2;
    stc_gpio_pzr2_field_t PZR2_f;
  };
  union {
    __IO uint32_t PZR3;
    stc_gpio_pzr3_field_t PZR3_f;
  };
  union {
    __IO uint32_t PZR4;
    stc_gpio_pzr4_field_t PZR4_f;
  };
  union {
    __IO uint32_t PZR5;
    stc_gpio_pzr5_field_t PZR5_f;
  };
  union {
    __IO uint32_t PZR6;
    stc_gpio_pzr6_field_t PZR6_f;
  };
       uint8_t RESERVED69[4];
  union {
    __IO uint32_t PZR8;
    stc_gpio_pzr8_field_t PZR8_f;
  };
       uint8_t RESERVED70[20];
  union {
    __IO uint32_t PZRE;
    stc_gpio_pzre_field_t PZRE_f;
  };
       uint8_t RESERVED71[452];
  union {
    __IO uint32_t FPOER0;
    stc_gpio_fpoer0_field_t FPOER0_f;
  };
  union {
    __IO uint32_t FPOER1;
    stc_gpio_fpoer1_field_t FPOER1_f;
  };
  union {
    __IO uint32_t FPOER2;
    stc_gpio_fpoer2_field_t FPOER2_f;
  };
  union {
    __IO uint32_t FPOER3;
    stc_gpio_fpoer3_field_t FPOER3_f;
  };
  union {
    __IO uint32_t FPOER4;
    stc_gpio_fpoer4_field_t FPOER4_f;
  };
  union {
    __IO uint32_t FPOER5;
    stc_gpio_fpoer5_field_t FPOER5_f;
  };
  union {
    __IO uint32_t FPOER6;
    stc_gpio_fpoer6_field_t FPOER6_f;
  };
       uint8_t RESERVED78[4];
  union {
    __IO uint32_t FPOER8;
    stc_gpio_fpoer8_field_t FPOER8_f;
  };
       uint8_t RESERVED79[20];
  union {
    __IO uint32_t FPOERE;
    stc_gpio_fpoere_field_t FPOERE_f;
  };
}FM0P_GPIO_TypeDef;

/******************************************************************************
 * LVD_MODULE
 ******************************************************************************/
/* Low voltage detection registers */
typedef struct
{
  union {
    __IO uint16_t LVD_CTL;
    stc_lvd_lvd_ctl_field_t LVD_CTL_f;
  };
       uint8_t RESERVED0[2];
  union {
    __IO  uint8_t LVD_STR;
    stc_lvd_lvd_str_field_t LVD_STR_f;
  };
       uint8_t RESERVED1[3];
  union {
    __IO  uint8_t LVD_CLR;
    stc_lvd_lvd_clr_field_t LVD_CLR_f;
  };
       uint8_t RESERVED2[3];
  union {
    __IO uint32_t LVD_RLR;
    stc_lvd_lvd_rlr_field_t LVD_RLR_f;
  };
  union {
    __IO  uint8_t LVD_STR2;
    stc_lvd_lvd_str2_field_t LVD_STR2_f;
  };
}FM0P_LVD_TypeDef;

/******************************************************************************
 * DS_MODULE
 ******************************************************************************/
/* Deep standby mode control registers */
typedef struct
{
  union {
    __IO  uint8_t REG_CTL;
    stc_ds_reg_ctl_field_t REG_CTL_f;
  };
       uint8_t RESERVED0[3];
  union {
    __IO  uint8_t RCK_CTL;
    stc_ds_rck_ctl_field_t RCK_CTL_f;
  };
       uint8_t RESERVED1[1787];
  union {
    __IO  uint8_t PMD_CTL;
    stc_ds_pmd_ctl_field_t PMD_CTL_f;
  };
       uint8_t RESERVED2[3];
  union {
    __IO  uint8_t WRFSR;
    stc_ds_wrfsr_field_t WRFSR_f;
  };
       uint8_t RESERVED3[3];
  union {
    __IO uint16_t WIFSR;
    stc_ds_wifsr_field_t WIFSR_f;
  };
       uint8_t RESERVED4[2];
  union {
    __IO uint16_t WIER;
    stc_ds_wier_field_t WIER_f;
  };
       uint8_t RESERVED5[2];
  union {
    __IO  uint8_t WILVR;
    stc_ds_wilvr_field_t WILVR_f;
  };
       uint8_t RESERVED6[3];
  union {
    __IO  uint8_t DSRAMR;
    stc_ds_dsramr_field_t DSRAMR_f;
  };
       uint8_t RESERVED7[235];
  __IO  uint8_t BUR01;
  __IO  uint8_t BUR02;
  __IO  uint8_t BUR03;
  __IO  uint8_t BUR04;
  __IO  uint8_t BUR05;
  __IO  uint8_t BUR06;
  __IO  uint8_t BUR07;
  __IO  uint8_t BUR08;
  __IO  uint8_t BUR09;
  __IO  uint8_t BUR10;
  __IO  uint8_t BUR11;
  __IO  uint8_t BUR12;
  __IO  uint8_t BUR13;
  __IO  uint8_t BUR14;
  __IO  uint8_t BUR15;
  __IO  uint8_t BUR16;
}FM0P_DS_TypeDef;

/******************************************************************************
 * MFS_UART_MODULE
 ******************************************************************************/
/* UART channel 0, 1, 3 registers */
typedef struct
{
  union {
    __IO  uint8_t SMR;
    stc_mfs_uart_smr_field_t SMR_f;
  };
  union {
    __IO  uint8_t SCR;
    stc_mfs_uart_scr_field_t SCR_f;
  };
  uint8_t RESERVED0[2];
  union {
    __IO  uint8_t ESCR;
    stc_mfs_uart_escr_field_t ESCR_f;
  };
  union {
    __IO  uint8_t SSR;
    stc_mfs_uart_ssr_field_t SSR_f;
  };
  uint8_t RESERVED1[2];
  union {
    __IO uint16_t RDR;
    __IO uint16_t TDR;
  };
  uint8_t RESERVED2[2];
  union {
    __IO uint16_t BGR;
    stc_mfs_uart_bgr_field_t BGR_f;
  };
  uint8_t RESERVED3[6];
  union {
    __IO  uint8_t FCR0;
    stc_mfs_uart_fcr0_field_t FCR0_f;
  };
  union {
    __IO  uint8_t FCR1;
    stc_mfs_uart_fcr1_field_t FCR1_f;
  };
  uint8_t RESERVED4[2];
  __IO  uint8_t FBYTE1;
  __IO  uint8_t FBYTE2;
}FM0P_MFS_UART_TypeDef;

/******************************************************************************
 * MFS_CSIO_MODULE
 ******************************************************************************/
/* CSIO channel 0, 1, 3 registers */
typedef struct
{
  union {
    __IO  uint8_t SMR;
    stc_mfs_csio_smr_field_t SMR_f;
  };
  union {
    __IO  uint8_t SCR;
    stc_mfs_csio_scr_field_t SCR_f;
  };
  uint8_t RESERVED0[2];
  union {
    __IO  uint8_t ESCR;
    stc_mfs_csio_escr_field_t ESCR_f;
  };
  union {
    __IO  uint8_t SSR;
    stc_mfs_csio_ssr_field_t SSR_f;
  };
  uint8_t RESERVED1[2];
  union {
    __IO uint16_t RDR;
    __IO uint16_t TDR;
  };
  uint8_t RESERVED2[2];
  union {
    __IO uint16_t BGR;
    stc_mfs_csio_bgr_field_t BGR_f;
  };
  uint8_t RESERVED3[6];
  union {
    __IO  uint8_t FCR0;
    stc_mfs_csio_fcr0_field_t FCR0_f;
  };
  union {
    __IO  uint8_t FCR1;
    stc_mfs_csio_fcr1_field_t FCR1_f;
  };
  uint8_t RESERVED4[2];
  __IO  uint8_t FBYTE1;
  __IO  uint8_t FBYTE2;
  uint8_t RESERVED5[2];
  union {
    __IO  uint8_t SCSTR0;
    stc_mfs_csio_scstr0_field_t SCSTR0_f;
  };
  union {
    __IO  uint8_t SCSTR1;
    stc_mfs_csio_scstr1_field_t SCSTR1_f;
  };
  uint8_t RESERVED6[2];
  union {
    __IO uint16_t SCSTR32;
    stc_mfs_csio_scstr32_field_t SCSTR32_f;
  };
  uint8_t RESERVED7[2];
  union {
    __IO uint16_t SACSR;
    stc_mfs_csio_sacsr_field_t SACSR_f;
  };
  uint8_t RESERVED8[2];
  union {
    __IO uint16_t STMR;
    stc_mfs_csio_stmr_field_t STMR_f;
  };
       uint8_t RESERVED52[2];
  union {
    __IO uint16_t STMCR;
    stc_mfs_csio_stmcr_field_t STMCR_f;
  };
       uint8_t RESERVED9[2];
  union {
    __IO uint16_t SCSCR;
    stc_mfs_csio_scscr_field_t SCSCR_f;
  };
       uint8_t RESERVED57[2];
  union {
    __IO uint8_t SCSFR0;
    stc_mfs_csio_scsfr0_field_t SCSFR0_f;
  };
  union {
    __IO uint8_t SCSFR1;
    stc_mfs_csio_scsfr1_field_t SCSFR1_f;
  };
       uint8_t RESERVED58[2];
  union {
    __IO uint8_t SCSFR2;
    stc_mfs_csio_scsfr2_field_t SCSFR2_f;
  };
       uint8_t RESERVED10[3];
  __IO  uint8_t TBYTE0;
  __IO  uint8_t TBYTE1;
       uint8_t RESERVED56[2];
  __IO  uint8_t TBYTE2;
  __IO  uint8_t TBYTE3;
}FM0P_MFS_CSIO_TypeDef;

/******************************************************************************
 * MFS_LIN_MODULE
 ******************************************************************************/
/* LIN channel 0, 1, 3 registers */
typedef struct
{
  union {
    __IO  uint8_t SMR;
    stc_mfs_lin_smr_field_t SMR_f;
  };
  union {
    __IO  uint8_t SCR;
    stc_mfs_lin_scr_field_t SCR_f;
  };
  uint8_t RESERVED0[2];
  union {
    __IO  uint8_t ESCR;
    stc_mfs_lin_escr_field_t ESCR_f;
  };
   union {
    __IO  uint8_t SSR;
    stc_mfs_lin_ssr_field_t SSR_f;
  };
  uint8_t RESERVED1[2];
  union {
    __IO uint16_t RDR;
    __IO uint16_t TDR;
  };
  uint8_t RESERVED2[2];
  union {
    __IO uint16_t BGR;
    stc_mfs_lin_bgr_field_t BGR_f;
  };
  uint8_t RESERVED3[6];
  union {
    __IO  uint8_t FCR0;
    stc_mfs_lin_fcr0_field_t FCR0_f;
  };
  union {
    __IO  uint8_t FCR1;
    stc_mfs_lin_fcr1_field_t FCR1_f;
  };
  uint8_t RESERVED4[2];
  __IO  uint8_t FBYTE1;
  __IO  uint8_t FBYTE2;
}FM0P_MFS_LIN_TypeDef;

/******************************************************************************
 * MFS_I2C_MODULE
 ******************************************************************************/
/* I2C channel 0, 1, 3 registers */
typedef struct
{
  union {
    __IO  uint8_t SMR;
    stc_mfs_i2c_smr_field_t SMR_f;
  };
  union {
    __IO  uint8_t IBCR;
    stc_mfs_i2c_ibcr_field_t IBCR_f;
  };
       uint8_t RESERVED0[2]; 
  union {
    __IO  uint8_t IBSR;
    stc_mfs_i2c_ibsr_field_t IBSR_f;
  };
  union {
    __IO  uint8_t SSR;
    stc_mfs_i2c_ssr_field_t SSR_f;
  };
    uint8_t RESERVED1[2];
  union {
    __IO uint16_t RDR;
    __IO uint16_t TDR;
  };
    uint8_t RESERVED2[2];
  union {
    __IO uint16_t BGR;
    stc_mfs_i2c_bgr_field_t BGR_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO  uint8_t ISBA;
    stc_mfs_i2c_isba_field_t ISBA_f;
  };
  union {
    __IO  uint8_t ISMK;
    stc_mfs_i2c_ismk_field_t ISMK_f;
  };
       uint8_t RESERVED4[2];
  union {
    __IO  uint8_t FCR0;
    stc_mfs_i2c_fcr0_field_t FCR0_f;
  };
  union {
    __IO  uint8_t FCR1;
    stc_mfs_i2c_fcr1_field_t FCR1_f;
  };
        uint8_t RESERVED5[2];
  __IO  uint8_t FBYTE1;
  __IO  uint8_t FBYTE2;
        uint8_t RESERVED6[3];
  union {
    __IO  uint8_t EIBCR;
    stc_mfs_i2c_eibcr_field_t EIBCR_f;
  };
}FM0P_MFS_I2C_TypeDef;

/******************************************************************************
 * CRC_MODULE
 ******************************************************************************/
/* CRC registers */
typedef struct
{
  union {
    __IO  uint8_t CRCCR;
    stc_crc_crccr_field_t CRCCR_f;
  };
       uint8_t RESERVED0[3];
  union {
    __IO uint32_t CRCINIT;
    stc_crc_crcinit_field_t CRCINIT_f;
  };
  union {
    __IO uint32_t CRCIN;
    stc_crc_crcin_field_t CRCIN_f;
  };
  union {
    __IO uint32_t CRCR;
    stc_crc_crcr_field_t CRCR_f;
  };
}FM0P_CRC_TypeDef;

/******************************************************************************
 * WC_MODULE
 ******************************************************************************/
/* Watch counter registers */
typedef struct
{
  union {
    __IO  uint8_t WCRD;
    stc_wc_wcrd_field_t WCRD_f;
  };
  union {
    __IO  uint8_t WCRL;
    stc_wc_wcrl_field_t WCRL_f;
  };
  union {
    __IO  uint8_t WCCR;
    stc_wc_wccr_field_t WCCR_f;
  };
       uint8_t RESERVED2[13];
  union {
    __IO uint16_t CLK_SEL;
    stc_wc_clk_sel_field_t CLK_SEL_f;
  };
       uint8_t RESERVED3[2];
  union {
    __IO  uint8_t CLK_EN;
    stc_wc_clk_en_field_t CLK_EN_f;
  };
}FM0P_WC_TypeDef;

/******************************************************************************
 * RTC_MODULE
 ******************************************************************************/
/* Realtime clock registers */
typedef struct
{
  union {
    __IO uint32_t WTCR1;
    stc_rtc_wtcr1_field_t WTCR1_f;
  };
  union {
    __IO uint32_t WTCR2;
    stc_rtc_wtcr2_field_t WTCR2_f;
  };
  union {
    __IO uint32_t WTBR;
    stc_rtc_wtbr_field_t WTBR_f;
  };
  union {
    __IO  uint8_t WTSR;
    stc_rtc_wtsr_field_t WTSR_f;
  };
  union {
    __IO  uint8_t WTMIR;
    stc_rtc_wtmir_field_t WTMIR_f;
  };
  union {
    __IO  uint8_t WTHR;
    stc_rtc_wthr_field_t WTHR_f;
  };
  union {
    __IO  uint8_t WTDR;
    stc_rtc_wtdr_field_t WTDR_f;
  };
  union {
    __IO  uint8_t WTDW;
    stc_rtc_wtdw_field_t WTDW_f;
  };
  union {
    __IO  uint8_t WTMOR;
    stc_rtc_wtmor_field_t WTMOR_f;
  };
  union {
    __IO  uint8_t WTYR;
    stc_rtc_wtyr_field_t WTYR_f;
  };
       uint8_t RESERVED9[2];
  union {
    __IO  uint8_t ALMIR;
    stc_rtc_almir_field_t ALMIR_f;
  };
  union {
    __IO  uint8_t ALHR;
    stc_rtc_alhr_field_t ALHR_f;
  };
  union {
    __IO  uint8_t ALDR;
    stc_rtc_aldr_field_t ALDR_f;
  };
       uint8_t RESERVED12[1];
  union {
    __IO  uint8_t ALMOR;
    stc_rtc_almor_field_t ALMOR_f;
  };
  union {
    __IO  uint8_t ALYR;
    stc_rtc_alyr_field_t ALYR_f;
  };
       uint8_t RESERVED14[1];
  union {
    __IO uint32_t WTTR;
    stc_rtc_wttr_field_t WTTR_f;
  };
  union {
    __IO  uint8_t WTCLKS;
    stc_rtc_wtclks_field_t WTCLKS_f;
  };
  union {
    __IO  uint8_t WTCLKM;
    stc_rtc_wtclkm_field_t WTCLKM_f;
  };
       uint8_t RESERVED17[2];
  union {
    __IO  uint16_t WTCAL;
    stc_rtc_wtcal_field_t WTCAL_f;
  };
  union {
    __IO  uint8_t WTCALEN;
    stc_rtc_wtcalen_field_t WTCALEN_f;
  };
       uint8_t RESERVED19[1];
  union {
    __IO  uint8_t WTDIV;
    stc_rtc_wtdiv_field_t WTDIV_f;
  };
  union {
    __IO  uint8_t WTDIVEN;
    stc_rtc_wtdiven_field_t WTDIVEN_f;
  };
       uint8_t RESERVED22[2];
  union {
    __IO  uint8_t WTCALPRD;
    stc_rtc_wtcalprd_field_t WTCALPRD_f;
  };
       uint8_t RESERVED24[3];
  union {
    __IO  uint8_t WTCOSEL;
    stc_rtc_wtcosel_field_t WTCOSEL_f;
  };
}FM0P_RTC_TypeDef;

/******************************************************************************
 * LSCRP_MODULE
 ******************************************************************************/
/* LSCRP registers */
typedef struct
{
  union {
    __IO  uint8_t LCR_PRSLD;
    stc_lscrp_lcr_prsld_field_t LCR_PRSLD_f;
  };
}FM0P_LSCRP_TypeDef;

/******************************************************************************
 * PCG_MODULE
 ******************************************************************************/
/* PCG registers */
typedef struct
{
  union {
    __IO uint32_t CKEN0;
    stc_pcg_cken0_field_t CKEN0_f;
  };
  union {
    __IO uint32_t MRST0;
    stc_pcg_mrst0_field_t MRST0_f;
  };
       uint8_t RESERVED1[8];
  union {
    __IO uint32_t CKEN1;
    stc_pcg_cken1_field_t CKEN1_f;
  };
  union {
    __IO uint32_t MRST1;
    stc_pcg_mrst1_field_t MRST1_f;
  };
       uint8_t RESERVED3[8];
  union {
    __IO uint32_t CKEN2;
    stc_pcg_cken2_field_t CKEN2_f;
  };
  union {
    __IO uint32_t MRST2;
    stc_pcg_mrst2_field_t MRST2_f;
  };
}FM0P_PCG_TypeDef;

/******************************************************************************
 * DMAC_MODULE
 ******************************************************************************/
/* DMA controller */
typedef struct
{
  union {
    __IO uint32_t DMACR;
    stc_dmac_dmacr_field_t DMACR_f;
  };
       uint8_t RESERVED0[12];
  union {
    __IO uint32_t DMACA0;
    stc_dmac_dmaca0_field_t DMACA0_f;
  };
  union {
    __IO uint32_t DMACB0;
    stc_dmac_dmacb0_field_t DMACB0_f;
  };
  __IO uint32_t DMACSA0;
  __IO uint32_t DMACDA0;
  union {
    __IO uint32_t DMACA1;
    stc_dmac_dmaca1_field_t DMACA1_f;
  };
  union {
    __IO uint32_t DMACB1;
    stc_dmac_dmacb1_field_t DMACB1_f;
  };
  __IO uint32_t DMACSA1;
  __IO uint32_t DMACDA1;
  union {
    __IO uint32_t DMACA2;
    stc_dmac_dmaca2_field_t DMACA2_f;
  };
  union {
    __IO uint32_t DMACB2;
    stc_dmac_dmacb2_field_t DMACB2_f;
  };
  __IO uint32_t DMACSA2;
  __IO uint32_t DMACDA2;
  union {
    __IO uint32_t DMACA3;
    stc_dmac_dmaca3_field_t DMACA3_f;
  };
  union {
    __IO uint32_t DMACB3;
    stc_dmac_dmacb3_field_t DMACB3_f;
  };
  __IO uint32_t DMACSA3;
  __IO uint32_t DMACDA3;
  union {
    __IO uint32_t DMACA4;
    stc_dmac_dmaca4_field_t DMACA4_f;
  };
  union {
    __IO uint32_t DMACB4;
    stc_dmac_dmacb4_field_t DMACB4_f;
  };
  __IO uint32_t DMACSA4;
  __IO uint32_t DMACDA4;
  union {
    __IO uint32_t DMACA5;
    stc_dmac_dmaca5_field_t DMACA5_f;
  };
  union {
    __IO uint32_t DMACB5;
    stc_dmac_dmacb5_field_t DMACB5_f;
  };
  __IO uint32_t DMACSA5;
  __IO uint32_t DMACDA5;
  union {
    __IO uint32_t DMACA6;
    stc_dmac_dmaca6_field_t DMACA6_f;
  };
  union {
    __IO uint32_t DMACB6;
    stc_dmac_dmacb6_field_t DMACB6_f;
  };
  __IO uint32_t DMACSA6;
  __IO uint32_t DMACDA6;
  union {
    __IO uint32_t DMACA7;
    stc_dmac_dmaca7_field_t DMACA7_f;
  };
  union {
    __IO uint32_t DMACB7;
    stc_dmac_dmacb7_field_t DMACB7_f;
  };
  __IO uint32_t DMACSA7;
  __IO uint32_t DMACDA7;
}FM0P_DMAC_TypeDef;

/******************************************************************************
 * MTB_DWT_MODULE
 ******************************************************************************/
/* MTB_DWT registers */
typedef struct
{
  __IO uint32_t CMP_ADDR_START;
  __IO uint32_t CMP_DATA_START;
  __IO uint32_t CMP_MASK_START;
       uint8_t RESERVED2[4];
  __IO uint32_t CMP_ADDR_STOP;
  __IO uint32_t CMP_DATA_STOP;
  __IO uint32_t CMP_MASK_STOP;
       uint8_t RESERVED5[4];
  union {
    __IO  uint8_t FCT;
    stc_mtb_dwt_fct_field_t FCT_f;
  };
       uint8_t RESERVED6[4015];
  __IO uint32_t PID4;
  __IO uint32_t PID5;
  __IO uint32_t PID6;
  __IO uint32_t PID7;
  __IO uint32_t PID0;
  __IO uint32_t PID1;
  __IO uint32_t PID2;
  __IO uint32_t PID3;
  __IO uint32_t CID0;
  __IO uint32_t CID1;
  __IO uint32_t CID2;
  __IO uint32_t CID3;
}FM0P_MTB_DWT_TypeDef;

/******************************************************************************
 * FASTIO_MODULE
 ******************************************************************************/
/* FASTIO registers */
typedef struct
{
  union {
    __IO uint32_t FPDIR0;
    stc_fastio_fpdir0_field_t FPDIR0_f;
  };
  union {
    __IO uint32_t FPDIR1;
    stc_fastio_fpdir1_field_t FPDIR1_f;
  };
  union {
    __IO uint32_t FPDIR2;
    stc_fastio_fpdir2_field_t FPDIR2_f;
  };
  union {
    __IO uint32_t FPDIR3;
    stc_fastio_fpdir3_field_t FPDIR3_f;
  };
  union {
    __IO uint32_t FPDIR4;
    stc_fastio_fpdir4_field_t FPDIR4_f;
  };
  union {
    __IO uint32_t FPDIR5;
    stc_fastio_fpdir5_field_t FPDIR5_f;
  };
  union {
    __IO uint32_t FPDIR6;
    stc_fastio_fpdir6_field_t FPDIR6_f;
  };
       uint8_t RESERVED6[4];
  union {
    __IO uint32_t FPDIR8;
    stc_fastio_fpdir8_field_t FPDIR8_f;
  };
       uint8_t RESERVED7[20];
  union {
    __IO uint32_t FPDIRE;
    stc_fastio_fpdire_field_t FPDIRE_f;
  };
       uint8_t RESERVED8[4];
  union {
    __IO uint32_t FPDOR0;
    stc_fastio_fpdor0_field_t FPDOR0_f;
  };
  union {
    __IO uint32_t FPDOR1;
    stc_fastio_fpdor1_field_t FPDOR1_f;
  };
  union {
    __IO uint32_t FPDOR2;
    stc_fastio_fpdor2_field_t FPDOR2_f;
  };
  union {
    __IO uint32_t FPDOR3;
    stc_fastio_fpdor3_field_t FPDOR3_f;
  };
  union {
    __IO uint32_t FPDOR4;
    stc_fastio_fpdor4_field_t FPDOR4_f;
  };
  union {
    __IO uint32_t FPDOR5;
    stc_fastio_fpdor5_field_t FPDOR5_f;
  };
  union {
    __IO uint32_t FPDOR6;
    stc_fastio_fpdor6_field_t FPDOR6_f;
  };
       uint8_t RESERVED15[4];
  union {
    __IO uint32_t FPDOR8;
    stc_fastio_fpdor8_field_t FPDOR8_f;
  };
       uint8_t RESERVED16[20];
  union {
    __IO uint32_t FPDORE;
    stc_fastio_fpdore_field_t FPDORE_f;
  };
       uint8_t RESERVED17[4];
  union {
    __IO uint32_t M_FPDIR0;
    stc_fastio_m_fpdir0_field_t M_FPDIR0_f;
  };
  union {
    __IO uint32_t M_FPDIR1;
    stc_fastio_m_fpdir1_field_t M_FPDIR1_f;
  };
       uint8_t RESERVED19[56];
  union {
    __IO uint32_t M_FPDOR0;
    stc_fastio_m_fpdor0_field_t M_FPDOR0_f;
  };
  union {
    __IO uint32_t M_FPDOR1;
    stc_fastio_m_fpdor1_field_t M_FPDOR1_f;
  };
}FM0P_FASTIO_TypeDef;

/******************************************************************************
 * Peripheral memory map
 ******************************************************************************/
#define FM0P_FLASH_BASE        (0x00000000UL)                 /* Flash Base                             */
#define FM0P_PERIPH_BASE       (0x40000000UL)                 /* Peripheral  Base                       */
#define FM0P_CM0P_BASE         (0xE0000000UL)                 /* CM0P Private                            */

#define FM0P_FLASH_IF_BASE     (FM0P_PERIPH_BASE + 0x00000UL)  /* Flash interface registers              */
#define FM0P_UNIQUE_ID_BASE    (FM0P_PERIPH_BASE + 0x00200UL)  /* Unique ID registers                    */
#define FM0P_CRG_BASE          (FM0P_PERIPH_BASE + 0x10000UL)  /* Clock and reset registers              */
#define FM0P_HWWDT_BASE        (FM0P_PERIPH_BASE + 0x11000UL)  /* Hardware watchdog registers            */
#define FM0P_SWWDT_BASE        (FM0P_PERIPH_BASE + 0x12000UL)  /* Software watchdog registers            */
#define FM0P_DTIM_BASE         (FM0P_PERIPH_BASE + 0x15000UL)  /* Dual timer 1/2 registers               */
#define FM0P_MFT0_FRT_BASE     (FM0P_PERIPH_BASE + 0x20100UL)  /* Multifunction Timer unit 0 Free Running Timer registers */
#define FM0P_MFT0_OCU_BASE     (FM0P_PERIPH_BASE + 0x20100UL)  /* Multifunction Timer unit 0 Output Compare Unit registers */
#define FM0P_MFT0_WFG_BASE     (FM0P_PERIPH_BASE + 0x20100UL)  /* Multifunction Timer unit 0 Waveform Generator and Noise Canceler registers */
#define FM0P_MFT0_ICU_BASE     (FM0P_PERIPH_BASE + 0x20100UL)  /* Multifunction Timer unit 0 Input Capture Unit registers */
#define FM0P_MFT0_ADCMP_BASE   (FM0P_PERIPH_BASE + 0x20100UL)  /* Multifunction Timer unit 0 ADC Start Compare Unit registers */
#define FM0P_MFT_PPG_BASE      (FM0P_PERIPH_BASE + 0x24000UL)  /* Multifunction Timer PPG registers      */
#define FM0P_BT0_PPG_BASE      (FM0P_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PPG registers             */
#define FM0P_BT0_PWM_BASE      (FM0P_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PWM registers             */
#define FM0P_BT0_RT_BASE       (FM0P_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 RT registers              */
#define FM0P_BT0_PWC_BASE      (FM0P_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PWC registers             */
#define FM0P_BT1_PPG_BASE      (FM0P_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PPG registers             */
#define FM0P_BT1_PWM_BASE      (FM0P_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PWM registers             */
#define FM0P_BT1_RT_BASE       (FM0P_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 RT registers              */
#define FM0P_BT1_PWC_BASE      (FM0P_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PWC registers             */
#define FM0P_BT2_PPG_BASE      (FM0P_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PPG registers             */
#define FM0P_BT2_PWM_BASE      (FM0P_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PWM registers             */
#define FM0P_BT2_RT_BASE       (FM0P_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 RT registers              */
#define FM0P_BT2_PWC_BASE      (FM0P_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PWC registers             */
#define FM0P_BT3_PPG_BASE      (FM0P_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PPG registers             */
#define FM0P_BT3_PWM_BASE      (FM0P_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PWM registers             */
#define FM0P_BT3_RT_BASE       (FM0P_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 RT registers              */
#define FM0P_BT3_PWC_BASE      (FM0P_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PWC registers             */
#define FM0P_BTIOSEL03_BASE    (FM0P_PERIPH_BASE + 0x25100UL)  /* Base Timer I/O selector channel 0 - channel 3 registers */
#define FM0P_SBSSR_BASE        (FM0P_PERIPH_BASE + 0x25FFCUL)  /* Software based Simulation Startup (Base Timer) register */
#define FM0P_QPRC0_BASE        (FM0P_PERIPH_BASE + 0x26000UL)  /* Quad position and revolution counter channel 0 registers */
#define FM0P_QPRC0_NF_BASE     (FM0P_PERIPH_BASE + 0x26100UL)  /* Quad position and revolution counter channel 0 noise Control Register*/
#define FM0P_ADC0_BASE         (FM0P_PERIPH_BASE + 0x27000UL)  /* 12-bit ADC unit 0 registers            */
#define FM0P_CRTRIM_BASE       (FM0P_PERIPH_BASE + 0x2E000UL)  /* CR trimming registers                  */
#define FM0P_EXTI_BASE         (FM0P_PERIPH_BASE + 0x30000UL)  /* External interrupt registers           */
#define FM0P_INTREQ_BASE       (FM0P_PERIPH_BASE + 0x31000UL)  /* Interrupt request read registers       */
#define FM0P_GPIO_BASE         (FM0P_PERIPH_BASE + 0x33000UL)  /* General purpose I/O registers          */
#define FM0P_LVD_BASE          (FM0P_PERIPH_BASE + 0x35000UL)  /* Low voltage detection registers        */
#define FM0P_DS_BASE           (FM0P_PERIPH_BASE + 0x35100UL)  /* Deep stanby mode control registers     */
#define FM0P_MFS0_UART_BASE    (FM0P_PERIPH_BASE + 0x38000UL)  /* UART asynchronous channel 0 registers  */
#define FM0P_MFS0_CSIO_BASE    (FM0P_PERIPH_BASE + 0x38000UL)  /* UART synchronous channel 0 registers   */
#define FM0P_MFS0_LIN_BASE     (FM0P_PERIPH_BASE + 0x38000UL)  /* LIN channel 0 registers                */
#define FM0P_MFS0_I2C_BASE     (FM0P_PERIPH_BASE + 0x38000UL)  /* I2C channel 0 registers                */
#define FM0P_MFS1_UART_BASE    (FM0P_PERIPH_BASE + 0x38100UL)  /* UART asynchronous channel 1 registers  */
#define FM0P_MFS1_CSIO_BASE    (FM0P_PERIPH_BASE + 0x38100UL)  /* UART synchronous channel 1 registers   */
#define FM0P_MFS1_LIN_BASE     (FM0P_PERIPH_BASE + 0x38100UL)  /* LIN channel 1 registers                */
#define FM0P_MFS1_I2C_BASE     (FM0P_PERIPH_BASE + 0x38100UL)  /* I2C channel 1 registers                */
#define FM0P_MFS3_UART_BASE    (FM0P_PERIPH_BASE + 0x38300UL)  /* UART asynchronous channel 3 registers  */
#define FM0P_MFS3_CSIO_BASE    (FM0P_PERIPH_BASE + 0x38300UL)  /* UART synchronous channel 3 registers   */
#define FM0P_MFS3_LIN_BASE     (FM0P_PERIPH_BASE + 0x38300UL)  /* LIN channel 3 registers                */
#define FM0P_MFS3_I2C_BASE     (FM0P_PERIPH_BASE + 0x38300UL)  /* I2C channel 3 registers                */
#define FM0P_CRC_BASE          (FM0P_PERIPH_BASE + 0x39000UL)  /* CRC registers                          */
#define FM0P_WC_BASE           (FM0P_PERIPH_BASE + 0x3A000UL)  /* Watch counter registers                */
#define FM0P_RTC_BASE          (FM0P_PERIPH_BASE + 0x3B000UL)  /* Realtime clock  registers              */
#define FM0P_LSCRP_BASE        (FM0P_PERIPH_BASE + 0x3C000UL)  /* Low-speed CR Prescaler Gating registers*/
#define FM0P_PCG_BASE          (FM0P_PERIPH_BASE + 0x3C100UL)  /* Peripheral Clock Gating registers      */
#define FM0P_DMAC_BASE         (FM0P_PERIPH_BASE + 0x60000UL)  /* DMA controller                         */
#define FM0P_MTB_DWT_BASE      (0xF0001000UL)                  /* MTB DWT                                */
#define FM0P_FASTIO_BASE       (0xF8000000UL)                  /* Fast GPIO                              */

/******************************************************************************
 * Peripheral declaration
 ******************************************************************************/
#define FM0P_FLASH_IF    ((FM0P_FLASH_IF_TypeDef *)FM0P_FLASH_IF_BASE)
#define FM0P_UNIQUE_ID   ((FM0P_UNIQUE_ID_TypeDef *)FM0P_UNIQUE_ID_BASE)
#define FM0P_CRG         ((FM0P_CRG_TypeDef *)FM0P_CRG_BASE)
#define FM0P_HWWDT       ((FM0P_HWWDT_TypeDef *)FM0P_HWWDT_BASE)
#define FM0P_SWWDT       ((FM0P_SWWDT_TypeDef *)FM0P_SWWDT_BASE)
#define FM0P_DTIM        ((FM0P_DTIM_TypeDef *)FM0P_DTIM_BASE)
#define FM0P_MFT0_FRT    ((FM0P_MFT_FRT_TypeDef *)FM0P_MFT0_FRT_BASE)
#define FM0P_MFT0_OCU    ((FM0P_MFT_OCU_TypeDef *)FM0P_MFT0_OCU_BASE)
#define FM0P_MFT0_WFG    ((FM0P_MFT_WFG_TypeDef *)FM0P_MFT0_WFG_BASE)
#define FM0P_MFT0_ICU    ((FM0P_MFT_ICU_TypeDef *)FM0P_MFT0_ICU_BASE)
#define FM0P_MFT0_ADCMP  ((FM0P_MFT_ADCMP_TypeDef *)FM0P_MFT0_ADCMP_BASE)
#define FM0P_MFT_PPG     ((FM0P_MFT_PPG_TypeDef *)FM0P_MFT_PPG_BASE)
#define FM0P_BT0_PPG     ((FM0P_BT_PPG_TypeDef *)FM0P_BT0_PPG_BASE)
#define FM0P_BT0_PWM     ((FM0P_BT_PWM_TypeDef *)FM0P_BT0_PWM_BASE)
#define FM0P_BT0_RT      ((FM0P_BT_RT_TypeDef *)FM0P_BT0_RT_BASE)
#define FM0P_BT0_PWC     ((FM0P_BT_PWC_TypeDef *)FM0P_BT0_PWC_BASE)
#define FM0P_BT1_PPG     ((FM0P_BT_PPG_TypeDef *)FM0P_BT1_PPG_BASE)
#define FM0P_BT1_PWM     ((FM0P_BT_PWM_TypeDef *)FM0P_BT1_PWM_BASE)
#define FM0P_BT1_RT      ((FM0P_BT_RT_TypeDef *)FM0P_BT1_RT_BASE)
#define FM0P_BT1_PWC     ((FM0P_BT_PWC_TypeDef *)FM0P_BT1_PWC_BASE)
#define FM0P_BT2_PPG     ((FM0P_BT_PPG_TypeDef *)FM0P_BT2_PPG_BASE)
#define FM0P_BT2_PWM     ((FM0P_BT_PWM_TypeDef *)FM0P_BT2_PWM_BASE)
#define FM0P_BT2_RT      ((FM0P_BT_RT_TypeDef *)FM0P_BT2_RT_BASE)
#define FM0P_BT2_PWC     ((FM0P_BT_PWC_TypeDef *)FM0P_BT2_PWC_BASE)
#define FM0P_BT3_PPG     ((FM0P_BT_PPG_TypeDef *)FM0P_BT3_PPG_BASE)
#define FM0P_BT3_PWM     ((FM0P_BT_PWM_TypeDef *)FM0P_BT3_PWM_BASE)
#define FM0P_BT3_RT      ((FM0P_BT_RT_TypeDef *)FM0P_BT3_RT_BASE)
#define FM0P_BT3_PWC     ((FM0P_BT_PWC_TypeDef *)FM0P_BT3_PWC_BASE)
#define FM0P_BTIOSEL03   ((FM0P_BTIOSEL03_TypeDef *)FM0P_BTIOSEL03_BASE)
#define FM0P_SBSSR       ((FM0P_SBSSR_TypeDef *)FM0P_SBSSR_BASE)
#define FM0P_QPRC0       ((FM0P_QPRC_TypeDef *)FM0P_QPRC0_BASE)
#define FM0P_QPRC0_NF    ((FM0P_QPRC_NF_TypeDef *)FM0P_QPRC0_NF_BASE)
#define FM0P_ADC0        ((FM0P_ADC_TypeDef *)FM0P_ADC0_BASE)
#define FM0P_CRTRIM      ((FM0P_CRTRIM_TypeDef *)FM0P_CRTRIM_BASE)
#define FM0P_EXTI        ((FM0P_EXTI_TypeDef *)FM0P_EXTI_BASE)
#define FM0P_INTREQ      ((FM0P_INTREQ_TypeDef *)FM0P_INTREQ_BASE)
#define FM0P_GPIO        ((FM0P_GPIO_TypeDef *)FM0P_GPIO_BASE)
#define FM0P_LVD         ((FM0P_LVD_TypeDef *)FM0P_LVD_BASE)
#define FM0P_DS          ((FM0P_DS_TypeDef *)FM0P_DS_BASE)
#define FM0P_MFS0_UART   ((FM0P_MFS_UART_TypeDef *)FM0P_MFS0_UART_BASE)
#define FM0P_MFS0_CSIO   ((FM0P_MFS_CSIO_TypeDef *)FM0P_MFS0_CSIO_BASE)
#define FM0P_MFS0_LIN    ((FM0P_MFS_LIN_TypeDef *)FM0P_MFS0_LIN_BASE)
#define FM0P_MFS0_I2C    ((FM0P_MFS_I2C_TypeDef *)FM0P_MFS0_I2C_BASE)
#define FM0P_MFS1_UART   ((FM0P_MFS_UART_TypeDef *)FM0P_MFS1_UART_BASE)
#define FM0P_MFS1_CSIO   ((FM0P_MFS_CSIO_TypeDef *)FM0P_MFS1_CSIO_BASE)
#define FM0P_MFS1_LIN    ((FM0P_MFS_LIN_TypeDef *)FM0P_MFS1_LIN_BASE)
#define FM0P_MFS1_I2C    ((FM0P_MFS_I2C_TypeDef *)FM0P_MFS1_I2C_BASE)
#define FM0P_MFS3_UART   ((FM0P_MFS_UART_TypeDef *)FM0P_MFS3_UART_BASE)
#define FM0P_MFS3_CSIO   ((FM0P_MFS_CSIO_TypeDef *)FM0P_MFS3_CSIO_BASE)
#define FM0P_MFS3_LIN    ((FM0P_MFS_LIN_TypeDef *)FM0P_MFS3_LIN_BASE)
#define FM0P_MFS3_I2C    ((FM0P_MFS_I2C_TypeDef *)FM0P_MFS3_I2C_BASE)
#define FM0P_CRC         ((FM0P_CRC_TypeDef *)FM0P_CRC_BASE)
#define FM0P_WC          ((FM0P_WC_TypeDef *)FM0P_WC_BASE)
#define FM0P_RTC         ((FM0P_RTC_TypeDef *)FM0P_RTC_BASE)
#define FM0P_LCSRP       ((FM0P_LSCRP_TypeDef *)FM0P_LSCRP_BASE)
#define FM0P_PCG         ((FM0P_PCG_TypeDef *)FM0P_PCG_BASE)
#define FM0P_DMAC        ((FM0P_DMAC_TypeDef *)FM0P_DMAC_BASE)
#define FM0P_MTB_DWT     ((FM0P_MTB_DWT_TypeDef *)FM0P_MTB_DWT_BASE)
#define FM0P_FASTIO      ((FM0P_FASTIO_TypeDef *)FM0P_FASTIO_BASE)

/******************************************************************************
 * Peripheral Bit Band Alias declaration
 ******************************************************************************/
/* Flash interface registers */
#define bFM0P_FLASHIF_FRWTR_RWT0               *((volatile unsigned int*)(0x42000080UL))
#define bFM0P_FLASHIF_FRWTR_RWT1               *((volatile unsigned int*)(0x42000084UL))
#define bFM0P_FLASHIF_FSTR_RDY                 *((volatile unsigned int*)(0x42000100UL))
#define bFM0P_FLASHIF_FSTR_HNG                 *((volatile unsigned int*)(0x42000104UL))
#define bFM0P_FLASHIF_FSTR_CERS                *((volatile unsigned int*)(0x42000108UL))
#define bFM0P_FLASHIF_FSTR_ESPS                *((volatile unsigned int*)(0x4200010CUL))
#define bFM0P_FLASHIF_FSTR_SERS                *((volatile unsigned int*)(0x42000110UL))
#define bFM0P_FLASHIF_FSTR_PGMS                *((volatile unsigned int*)(0x42000114UL))
#define bFM0P_FLASHIF_FSYNDN_SD0               *((volatile unsigned int*)(0x42000200UL))
#define bFM0P_FLASHIF_FSYNDN_SD1               *((volatile unsigned int*)(0x42000204UL))
#define bFM0P_FLASHIF_FSYNDN_SD2               *((volatile unsigned int*)(0x42000208UL))
#define bFM0P_FLASHIF_FSYNDN_SD3               *((volatile unsigned int*)(0x4200020CUL))
#define bFM0P_FLASHIF_FICR_RDYIE               *((volatile unsigned int*)(0x42000400UL))
#define bFM0P_FLASHIF_FICR_HANGIE              *((volatile unsigned int*)(0x42000404UL))
#define bFM0P_FLASHIF_FISR_RDYIF               *((volatile unsigned int*)(0x42000480UL))
#define bFM0P_FLASHIF_FISR_HANGIF              *((volatile unsigned int*)(0x42000484UL))
#define bFM0P_FLASHIF_FICLR_RDYC               *((volatile unsigned int*)(0x42000500UL))
#define bFM0P_FLASHIF_FICLR_HANGC              *((volatile unsigned int*)(0x42000504UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM0             *((volatile unsigned int*)(0x42002000UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM1             *((volatile unsigned int*)(0x42002004UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM2             *((volatile unsigned int*)(0x42002008UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM3             *((volatile unsigned int*)(0x4200200CUL))
#define bFM0P_FLASHIF_CRTRMM_TRMM4             *((volatile unsigned int*)(0x42002010UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM5             *((volatile unsigned int*)(0x42002014UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM6             *((volatile unsigned int*)(0x42002018UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM7             *((volatile unsigned int*)(0x4200201CUL))
#define bFM0P_FLASHIF_CRTRMM_TRMM8             *((volatile unsigned int*)(0x42002020UL))
#define bFM0P_FLASHIF_CRTRMM_TRMM9             *((volatile unsigned int*)(0x42002024UL))
#define bFM0P_FLASHIF_CRTRMM_TTRMM0            *((volatile unsigned int*)(0x42002040UL))
#define bFM0P_FLASHIF_CRTRMM_TTRMM1            *((volatile unsigned int*)(0x42002044UL))
#define bFM0P_FLASHIF_CRTRMM_TTRMM2            *((volatile unsigned int*)(0x42002048UL))
#define bFM0P_FLASHIF_CRTRMM_TTRMM3            *((volatile unsigned int*)(0x4200204CUL))
#define bFM0P_FLASHIF_CRTRMM_TTRMM4            *((volatile unsigned int*)(0x42002050UL))

/* Unique ID registers */
#define bFM0P_UID_UIDR0_UID0                   *((volatile unsigned int*)(0x42004010UL))
#define bFM0P_UID_UIDR0_UID1                   *((volatile unsigned int*)(0x42004014UL))
#define bFM0P_UID_UIDR0_UID2                   *((volatile unsigned int*)(0x42004018UL))
#define bFM0P_UID_UIDR0_UID3                   *((volatile unsigned int*)(0x4200401CUL))
#define bFM0P_UID_UIDR0_UID4                   *((volatile unsigned int*)(0x42004020UL))
#define bFM0P_UID_UIDR0_UID5                   *((volatile unsigned int*)(0x42004024UL))
#define bFM0P_UID_UIDR0_UID6                   *((volatile unsigned int*)(0x42004028UL))
#define bFM0P_UID_UIDR0_UID7                   *((volatile unsigned int*)(0x4200402CUL))
#define bFM0P_UID_UIDR0_UID8                   *((volatile unsigned int*)(0x42004030UL))
#define bFM0P_UID_UIDR0_UID9                   *((volatile unsigned int*)(0x42004034UL))
#define bFM0P_UID_UIDR0_UID10                  *((volatile unsigned int*)(0x42004038UL))
#define bFM0P_UID_UIDR0_UID11                  *((volatile unsigned int*)(0x4200403CUL))
#define bFM0P_UID_UIDR0_UID12                  *((volatile unsigned int*)(0x42004040UL))
#define bFM0P_UID_UIDR0_UID13                  *((volatile unsigned int*)(0x42004044UL))
#define bFM0P_UID_UIDR0_UID14                  *((volatile unsigned int*)(0x42004048UL))
#define bFM0P_UID_UIDR0_UID15                  *((volatile unsigned int*)(0x4200404CUL))
#define bFM0P_UID_UIDR0_UID16                  *((volatile unsigned int*)(0x42004050UL))
#define bFM0P_UID_UIDR0_UID17                  *((volatile unsigned int*)(0x42004054UL))
#define bFM0P_UID_UIDR0_UID18                  *((volatile unsigned int*)(0x42004058UL))
#define bFM0P_UID_UIDR0_UID19                  *((volatile unsigned int*)(0x4200405CUL))
#define bFM0P_UID_UIDR0_UID20                  *((volatile unsigned int*)(0x42004060UL))
#define bFM0P_UID_UIDR0_UID21                  *((volatile unsigned int*)(0x42004064UL))
#define bFM0P_UID_UIDR0_UID22                  *((volatile unsigned int*)(0x42004068UL))
#define bFM0P_UID_UIDR0_UID23                  *((volatile unsigned int*)(0x4200406CUL))
#define bFM0P_UID_UIDR0_UID24                  *((volatile unsigned int*)(0x42004070UL))
#define bFM0P_UID_UIDR0_UID25                  *((volatile unsigned int*)(0x42004074UL))
#define bFM0P_UID_UIDR0_UID26                  *((volatile unsigned int*)(0x42004078UL))
#define bFM0P_UID_UIDR0_UID27                  *((volatile unsigned int*)(0x4200407CUL))
#define bFM0P_UID_UIDR1_UID28                  *((volatile unsigned int*)(0x42004080UL))
#define bFM0P_UID_UIDR1_UID29                  *((volatile unsigned int*)(0x42004084UL))
#define bFM0P_UID_UIDR1_UID30                  *((volatile unsigned int*)(0x42004088UL))
#define bFM0P_UID_UIDR1_UID31                  *((volatile unsigned int*)(0x4200408CUL))
#define bFM0P_UID_UIDR1_UID32                  *((volatile unsigned int*)(0x42004090UL))
#define bFM0P_UID_UIDR1_UID33                  *((volatile unsigned int*)(0x42004094UL))
#define bFM0P_UID_UIDR1_UID34                  *((volatile unsigned int*)(0x42004098UL))
#define bFM0P_UID_UIDR1_UID35                  *((volatile unsigned int*)(0x4200409CUL))
#define bFM0P_UID_UIDR1_UID36                  *((volatile unsigned int*)(0x420040A0UL))
#define bFM0P_UID_UIDR1_UID37                  *((volatile unsigned int*)(0x420040A4UL))
#define bFM0P_UID_UIDR1_UID38                  *((volatile unsigned int*)(0x420040A8UL))
#define bFM0P_UID_UIDR1_UID39                  *((volatile unsigned int*)(0x420040ACUL))
#define bFM0P_UID_UIDR1_UID40                  *((volatile unsigned int*)(0x420040B0UL))

/* Clock and reset registers */
#define bFM0P_CRG_SCM_CTL_HCRE               *((volatile unsigned int*)(0x42200000UL))
#define bFM0P_CRG_SCM_CTL_MOSCE              *((volatile unsigned int*)(0x42200004UL))
#define bFM0P_CRG_SCM_CTL_SOSCE              *((volatile unsigned int*)(0x4220000CUL))
#define bFM0P_CRG_SCM_CTL_PLLE               *((volatile unsigned int*)(0x42200010UL))
#define bFM0P_CRG_SCM_CTL_RCS0               *((volatile unsigned int*)(0x42200014UL))
#define bFM0P_CRG_SCM_CTL_RCS1               *((volatile unsigned int*)(0x42200018UL))
#define bFM0P_CRG_SCM_CTL_RCS2               *((volatile unsigned int*)(0x4220001CUL))
#define bFM0P_CRG_SCM_STR_HCRDY              *((volatile unsigned int*)(0x42200080UL))
#define bFM0P_CRG_SCM_STR_MORDY              *((volatile unsigned int*)(0x42200084UL))
#define bFM0P_CRG_SCM_STR_SORDY              *((volatile unsigned int*)(0x4220008CUL))
#define bFM0P_CRG_SCM_STR_PLRDY              *((volatile unsigned int*)(0x42200090UL))
#define bFM0P_CRG_SCM_STR_RCM0               *((volatile unsigned int*)(0x42200094UL))
#define bFM0P_CRG_SCM_STR_RCM1               *((volatile unsigned int*)(0x42200098UL))
#define bFM0P_CRG_SCM_STR_RCM2               *((volatile unsigned int*)(0x4220009CUL))
#define bFM0P_CRG_STB_CTL_STM0               *((volatile unsigned int*)(0x42200100UL))
#define bFM0P_CRG_STB_CTL_STM1               *((volatile unsigned int*)(0x42200104UL))
#define bFM0P_CRG_STB_CTL_DSTM               *((volatile unsigned int*)(0x42200108UL))
#define bFM0P_CRG_STB_CTL_SPL                *((volatile unsigned int*)(0x42200110UL))
#define bFM0P_CRG_STB_CTL_KEY0               *((volatile unsigned int*)(0x42200140UL))
#define bFM0P_CRG_STB_CTL_KEY1               *((volatile unsigned int*)(0x42200144UL))
#define bFM0P_CRG_STB_CTL_KEY2               *((volatile unsigned int*)(0x42200148UL))
#define bFM0P_CRG_STB_CTL_KEY3               *((volatile unsigned int*)(0x4220014CUL))
#define bFM0P_CRG_STB_CTL_KEY4               *((volatile unsigned int*)(0x42200150UL))
#define bFM0P_CRG_STB_CTL_KEY5               *((volatile unsigned int*)(0x42200154UL))
#define bFM0P_CRG_STB_CTL_KEY6               *((volatile unsigned int*)(0x42200158UL))
#define bFM0P_CRG_STB_CTL_KEY7               *((volatile unsigned int*)(0x4220015CUL))
#define bFM0P_CRG_STB_CTL_KEY8               *((volatile unsigned int*)(0x42200160UL))
#define bFM0P_CRG_STB_CTL_KEY9               *((volatile unsigned int*)(0x42200164UL))
#define bFM0P_CRG_STB_CTL_KEY10              *((volatile unsigned int*)(0x42200168UL))
#define bFM0P_CRG_STB_CTL_KEY11              *((volatile unsigned int*)(0x4220016CUL))
#define bFM0P_CRG_STB_CTL_KEY12              *((volatile unsigned int*)(0x42200170UL))
#define bFM0P_CRG_STB_CTL_KEY13              *((volatile unsigned int*)(0x42200174UL))
#define bFM0P_CRG_STB_CTL_KEY14              *((volatile unsigned int*)(0x42200178UL))
#define bFM0P_CRG_STB_CTL_KEY15              *((volatile unsigned int*)(0x4220017CUL))
#define bFM0P_CRG_RST_STR_PONR               *((volatile unsigned int*)(0x42200180UL))
#define bFM0P_CRG_RST_STR_INITX              *((volatile unsigned int*)(0x42200184UL))
#define bFM0P_CRG_RST_STR_SWDT               *((volatile unsigned int*)(0x42200190UL))
#define bFM0P_CRG_RST_STR_HWDT               *((volatile unsigned int*)(0x42200194UL))
#define bFM0P_CRG_RST_STR_CSVR               *((volatile unsigned int*)(0x42200198UL))
#define bFM0P_CRG_RST_STR_FCSR               *((volatile unsigned int*)(0x4220019CUL))
#define bFM0P_CRG_RST_STR_SRST               *((volatile unsigned int*)(0x422001A0UL))
#define bFM0P_CRG_BSC_PSR_BSR0               *((volatile unsigned int*)(0x42200200UL))
#define bFM0P_CRG_BSC_PSR_BSR1               *((volatile unsigned int*)(0x42200204UL))
#define bFM0P_CRG_BSC_PSR_BSR2               *((volatile unsigned int*)(0x42200208UL))
#define bFM0P_CRG_APBC0_PSR_APBC00           *((volatile unsigned int*)(0x42200280UL))
#define bFM0P_CRG_APBC0_PSR_APBC01           *((volatile unsigned int*)(0x42200284UL))
#define bFM0P_CRG_APBC1_PSR_APBC10           *((volatile unsigned int*)(0x42200300UL))
#define bFM0P_CRG_APBC1_PSR_APBC11           *((volatile unsigned int*)(0x42200304UL))
#define bFM0P_CRG_APBC1_PSR_APBC1RST         *((volatile unsigned int*)(0x42200310UL))
#define bFM0P_CRG_APBC1_PSR_APBC1EN          *((volatile unsigned int*)(0x4220031CUL))
#define bFM0P_CRG_SWC_PSR_SWDS0              *((volatile unsigned int*)(0x42200400UL))
#define bFM0P_CRG_SWC_PSR_SWDS1              *((volatile unsigned int*)(0x42200404UL))
#define bFM0P_CRG_SWC_PSR_TESTB              *((volatile unsigned int*)(0x4220041CUL))
#define bFM0P_CRG_CSW_TMR_MOWT0              *((volatile unsigned int*)(0x42200600UL))
#define bFM0P_CRG_CSW_TMR_MOWT1              *((volatile unsigned int*)(0x42200604UL))
#define bFM0P_CRG_CSW_TMR_MOWT2              *((volatile unsigned int*)(0x42200608UL))
#define bFM0P_CRG_CSW_TMR_MOWT3              *((volatile unsigned int*)(0x4220060CUL))
#define bFM0P_CRG_CSW_TMR_SOWT0              *((volatile unsigned int*)(0x42200610UL))
#define bFM0P_CRG_CSW_TMR_SOWT1              *((volatile unsigned int*)(0x42200614UL))
#define bFM0P_CRG_CSW_TMR_SOWT2              *((volatile unsigned int*)(0x42200618UL))
#define bFM0P_CRG_CSW_TMR_SOWT3              *((volatile unsigned int*)(0x4220061CUL))
#define bFM0P_CRG_PSW_TMR_POWT0              *((volatile unsigned int*)(0x42200680UL))
#define bFM0P_CRG_PSW_TMR_POWT1              *((volatile unsigned int*)(0x42200684UL))
#define bFM0P_CRG_PSW_TMR_POWT2              *((volatile unsigned int*)(0x42200688UL))
#define bFM0P_CRG_PSW_TMR_PINC               *((volatile unsigned int*)(0x42200690UL))
#define bFM0P_CRG_PLL_CTL1_PLLM0             *((volatile unsigned int*)(0x42200700UL))
#define bFM0P_CRG_PLL_CTL1_PLLM1             *((volatile unsigned int*)(0x42200704UL))
#define bFM0P_CRG_PLL_CTL1_PLLM2             *((volatile unsigned int*)(0x42200708UL))
#define bFM0P_CRG_PLL_CTL1_PLLM3             *((volatile unsigned int*)(0x4220070CUL))
#define bFM0P_CRG_PLL_CTL1_PLLK0             *((volatile unsigned int*)(0x42200710UL))
#define bFM0P_CRG_PLL_CTL1_PLLK1             *((volatile unsigned int*)(0x42200714UL))
#define bFM0P_CRG_PLL_CTL1_PLLK2             *((volatile unsigned int*)(0x42200718UL))
#define bFM0P_CRG_PLL_CTL1_PLLK3             *((volatile unsigned int*)(0x4220071CUL))
#define bFM0P_CRG_PLL_CTL2_PLLN0             *((volatile unsigned int*)(0x42200780UL))
#define bFM0P_CRG_PLL_CTL2_PLLN1             *((volatile unsigned int*)(0x42200784UL))
#define bFM0P_CRG_PLL_CTL2_PLLN2             *((volatile unsigned int*)(0x42200788UL))
#define bFM0P_CRG_PLL_CTL2_PLLN3             *((volatile unsigned int*)(0x4220078CUL))
#define bFM0P_CRG_PLL_CTL2_PLLN4             *((volatile unsigned int*)(0x42200790UL))
#define bFM0P_CRG_PLL_CTL2_PLLN5             *((volatile unsigned int*)(0x42200794UL))
#define bFM0P_CRG_CSV_CTL_MCSVE              *((volatile unsigned int*)(0x42200800UL))
#define bFM0P_CRG_CSV_CTL_SCSVE              *((volatile unsigned int*)(0x42200804UL))
#define bFM0P_CRG_CSV_CTL_FCSDE              *((volatile unsigned int*)(0x42200820UL))
#define bFM0P_CRG_CSV_CTL_FCSRE              *((volatile unsigned int*)(0x42200824UL))
#define bFM0P_CRG_CSV_CTL_FCD0               *((volatile unsigned int*)(0x42200830UL))
#define bFM0P_CRG_CSV_CTL_FCD1               *((volatile unsigned int*)(0x42200834UL))
#define bFM0P_CRG_CSV_CTL_FCD2               *((volatile unsigned int*)(0x42200838UL))
#define bFM0P_CRG_CSV_STR_MCMF               *((volatile unsigned int*)(0x42200880UL))
#define bFM0P_CRG_CSV_STR_SCMF               *((volatile unsigned int*)(0x42200884UL))
#define bFM0P_CRG_DBWDT_CTL_DPSWBE           *((volatile unsigned int*)(0x42200A94UL))
#define bFM0P_CRG_DBWDT_CTL_DPHWBE           *((volatile unsigned int*)(0x42200A9CUL))
#define bFM0P_CRG_INT_ENR_MCSE               *((volatile unsigned int*)(0x42200C00UL))
#define bFM0P_CRG_INT_ENR_SCSE               *((volatile unsigned int*)(0x42200C04UL))
#define bFM0P_CRG_INT_ENR_PCSE               *((volatile unsigned int*)(0x42200C08UL))
#define bFM0P_CRG_INT_ENR_FCSE               *((volatile unsigned int*)(0x42200C14UL))
#define bFM0P_CRG_INT_STR_MCSI               *((volatile unsigned int*)(0x42200C80UL))
#define bFM0P_CRG_INT_STR_SCSI               *((volatile unsigned int*)(0x42200C84UL))
#define bFM0P_CRG_INT_STR_PCSI               *((volatile unsigned int*)(0x42200C88UL))
#define bFM0P_CRG_INT_STR_FCSI               *((volatile unsigned int*)(0x42200C94UL))
#define bFM0P_CRG_INT_CLR_MCSC               *((volatile unsigned int*)(0x42200D00UL))
#define bFM0P_CRG_INT_CLR_SCSC               *((volatile unsigned int*)(0x42200D04UL))
#define bFM0P_CRG_INT_CLR_PCSC               *((volatile unsigned int*)(0x42200D08UL))
#define bFM0P_CRG_INT_CLR_FCSC               *((volatile unsigned int*)(0x42200D14UL))

/* Hardware watchdog registers */
#define bFM0P_HWWDT_WDG_CTL_INTEN              *((volatile unsigned int*)(0x42220100UL))
#define bFM0P_HWWDT_WDG_CTL_RESEN              *((volatile unsigned int*)(0x42220104UL))
#define bFM0P_HWWDT_WDG_RIS_RIS                *((volatile unsigned int*)(0x42220200UL))

/* Software watchdog registers */
#define bFM0P_SWWDT_WDOGCONTROL_INTEN          *((volatile unsigned int*)(0x42240100UL))
#define bFM0P_SWWDT_WDOGCONTROL_RESEN          *((volatile unsigned int*)(0x42240104UL))
#define bFM0P_SWWDT_WDOGCONTROL_TWD0           *((volatile unsigned int*)(0x42240108UL))
#define bFM0P_SWWDT_WDOGCONTROL_TWD1           *((volatile unsigned int*)(0x4224010CUL))
#define bFM0P_SWWDT_WDOGCONTROL_SPM            *((volatile unsigned int*)(0x42240110UL))
#define bFM0P_SWWDT_WDOGRIS_RIS                *((volatile unsigned int*)(0x42240200UL))
#define bFM0P_SWWDT_WDOGSPMC_TGR               *((volatile unsigned int*)(0x42240300UL))

/* Dual timer 1/2 registers */
#define bFM0P_DTIM_TIMER1CONTROL_ONESHOT       *((volatile unsigned int*)(0x422A0100UL))
#define bFM0P_DTIM_TIMER1CONTROL_TIMERSIZE     *((volatile unsigned int*)(0x422A0104UL))
#define bFM0P_DTIM_TIMER1CONTROL_TIMERPRE0     *((volatile unsigned int*)(0x422A0108UL))
#define bFM0P_DTIM_TIMER1CONTROL_TIMERPRE1     *((volatile unsigned int*)(0x422A010CUL))
#define bFM0P_DTIM_TIMER1CONTROL_INTENABLE     *((volatile unsigned int*)(0x422A0114UL))
#define bFM0P_DTIM_TIMER1CONTROL_TIMERMODE     *((volatile unsigned int*)(0x422A0118UL))
#define bFM0P_DTIM_TIMER1CONTROL_TIMEREN       *((volatile unsigned int*)(0x422A011CUL))
#define bFM0P_DTIM_TIMER1RIS_TIMER1RIS         *((volatile unsigned int*)(0x422A0200UL))
#define bFM0P_DTIM_TIMER1MIS_TIMER1MIS         *((volatile unsigned int*)(0x422A0280UL))
#define bFM0P_DTIM_TIMER2CONTROL_ONESHOT       *((volatile unsigned int*)(0x422A0500UL))
#define bFM0P_DTIM_TIMER2CONTROL_TIMERSIZE     *((volatile unsigned int*)(0x422A0504UL))
#define bFM0P_DTIM_TIMER2CONTROL_TIMERPRE0     *((volatile unsigned int*)(0x422A0508UL))
#define bFM0P_DTIM_TIMER2CONTROL_TIMERPRE1     *((volatile unsigned int*)(0x422A050CUL))
#define bFM0P_DTIM_TIMER2CONTROL_INTENABLE     *((volatile unsigned int*)(0x422A0514UL))
#define bFM0P_DTIM_TIMER2CONTROL_TIMERMODE     *((volatile unsigned int*)(0x422A0518UL))
#define bFM0P_DTIM_TIMER2CONTROL_TIMEREN       *((volatile unsigned int*)(0x422A051CUL))
#define bFM0P_DTIM_TIMER2RIS_TIMER1RIS         *((volatile unsigned int*)(0x422A0600UL))
#define bFM0P_DTIM_TIMER2MIS_TIMER1MIS         *((volatile unsigned int*)(0x422A0680UL))

/* Multifunction Timer unit 0 Free Running Timer registers */
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP016       *((volatile unsigned int*)(0x424008C0UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP017       *((volatile unsigned int*)(0x424008C4UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP018       *((volatile unsigned int*)(0x424008C8UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP019       *((volatile unsigned int*)(0x424008CCUL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP020       *((volatile unsigned int*)(0x424008D0UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP021       *((volatile unsigned int*)(0x424008D4UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP022       *((volatile unsigned int*)(0x424008D8UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP023       *((volatile unsigned int*)(0x424008DCUL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP024       *((volatile unsigned int*)(0x424008E0UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP025       *((volatile unsigned int*)(0x424008E4UL))
#define bFM0P_MFT0_FRT_TCDT0_FRT_TCCP026       *((volatile unsigned int*)(0x424008E8UL))
#define bFM0P_MFT0_FRT_TCSA0_CLK0              *((volatile unsigned int*)(0x42400900UL))
#define bFM0P_MFT0_FRT_TCSA0_CLK1              *((volatile unsigned int*)(0x42400904UL))
#define bFM0P_MFT0_FRT_TCSA0_CLK2              *((volatile unsigned int*)(0x42400908UL))
#define bFM0P_MFT0_FRT_TCSA0_CLK3              *((volatile unsigned int*)(0x4240090CUL))
#define bFM0P_MFT0_FRT_TCSA0_SCLR              *((volatile unsigned int*)(0x42400910UL))
#define bFM0P_MFT0_FRT_TCSA0_MODE              *((volatile unsigned int*)(0x42400914UL))
#define bFM0P_MFT0_FRT_TCSA0_STOP              *((volatile unsigned int*)(0x42400918UL))
#define bFM0P_MFT0_FRT_TCSA0_BFE               *((volatile unsigned int*)(0x4240091CUL))
#define bFM0P_MFT0_FRT_TCSA0_ICRE              *((volatile unsigned int*)(0x42400920UL))
#define bFM0P_MFT0_FRT_TCSA0_ICLR              *((volatile unsigned int*)(0x42400924UL))
#define bFM0P_MFT0_FRT_TCSA0_IRQZE             *((volatile unsigned int*)(0x42400934UL))
#define bFM0P_MFT0_FRT_TCSA0_IRQZF             *((volatile unsigned int*)(0x42400938UL))
#define bFM0P_MFT0_FRT_TCSA0_ECKE              *((volatile unsigned int*)(0x4240093CUL))
#define bFM0P_MFT0_FRT_TCSC0_MSZI0             *((volatile unsigned int*)(0x42400940UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZI1             *((volatile unsigned int*)(0x42400944UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZI2             *((volatile unsigned int*)(0x42400948UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZI3             *((volatile unsigned int*)(0x4240094CUL))
#define bFM0P_MFT0_FRT_TCSC0_MSPI0             *((volatile unsigned int*)(0x42400950UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPI1             *((volatile unsigned int*)(0x42400954UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPI2             *((volatile unsigned int*)(0x42400958UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPI3             *((volatile unsigned int*)(0x4240095CUL))
#define bFM0P_MFT0_FRT_TCSC0_MSZC0             *((volatile unsigned int*)(0x42400960UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZC1             *((volatile unsigned int*)(0x42400964UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZC2             *((volatile unsigned int*)(0x42400968UL))
#define bFM0P_MFT0_FRT_TCSC0_MSZC3             *((volatile unsigned int*)(0x4240096CUL))
#define bFM0P_MFT0_FRT_TCSC0_MSPC0             *((volatile unsigned int*)(0x42400970UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPC1             *((volatile unsigned int*)(0x42400974UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPC2             *((volatile unsigned int*)(0x42400978UL))
#define bFM0P_MFT0_FRT_TCSC0_MSPC3             *((volatile unsigned int*)(0x4240097CUL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP016       *((volatile unsigned int*)(0x42400A40UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP017       *((volatile unsigned int*)(0x42400A44UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP018       *((volatile unsigned int*)(0x42400A48UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP019       *((volatile unsigned int*)(0x42400A4CUL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP020       *((volatile unsigned int*)(0x42400A50UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP021       *((volatile unsigned int*)(0x42400A54UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP022       *((volatile unsigned int*)(0x42400A58UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP023       *((volatile unsigned int*)(0x42400A5CUL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP024       *((volatile unsigned int*)(0x42400A60UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP025       *((volatile unsigned int*)(0x42400A64UL))
#define bFM0P_MFT0_FRT_TCDT1_FRT_TCCP026       *((volatile unsigned int*)(0x42400A68UL))
#define bFM0P_MFT0_FRT_TCSA1_CLK0              *((volatile unsigned int*)(0x42400A80UL))
#define bFM0P_MFT0_FRT_TCSA1_CLK1              *((volatile unsigned int*)(0x42400A84UL))
#define bFM0P_MFT0_FRT_TCSA1_CLK2              *((volatile unsigned int*)(0x42400A88UL))
#define bFM0P_MFT0_FRT_TCSA1_CLK3              *((volatile unsigned int*)(0x42400A8CUL))
#define bFM0P_MFT0_FRT_TCSA1_SCLR              *((volatile unsigned int*)(0x42400A90UL))
#define bFM0P_MFT0_FRT_TCSA1_MODE              *((volatile unsigned int*)(0x42400A94UL))
#define bFM0P_MFT0_FRT_TCSA1_STOP              *((volatile unsigned int*)(0x42400A98UL))
#define bFM0P_MFT0_FRT_TCSA1_BFE               *((volatile unsigned int*)(0x42400A9CUL))
#define bFM0P_MFT0_FRT_TCSA1_ICRE              *((volatile unsigned int*)(0x42400AA0UL))
#define bFM0P_MFT0_FRT_TCSA1_ICLR              *((volatile unsigned int*)(0x42400AA4UL))
#define bFM0P_MFT0_FRT_TCSA1_IRQZE             *((volatile unsigned int*)(0x42400AB4UL))
#define bFM0P_MFT0_FRT_TCSA1_IRQZF             *((volatile unsigned int*)(0x42400AB8UL))
#define bFM0P_MFT0_FRT_TCSA1_ECKE              *((volatile unsigned int*)(0x42400ABCUL))
#define bFM0P_MFT0_FRT_TCSC1_MSZI0             *((volatile unsigned int*)(0x42400AC0UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZI1             *((volatile unsigned int*)(0x42400AC4UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZI2             *((volatile unsigned int*)(0x42400AC8UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZI3             *((volatile unsigned int*)(0x42400ACCUL))
#define bFM0P_MFT0_FRT_TCSC1_MSPI0             *((volatile unsigned int*)(0x42400AD0UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPI1             *((volatile unsigned int*)(0x42400AD4UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPI2             *((volatile unsigned int*)(0x42400AD8UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPI3             *((volatile unsigned int*)(0x42400ADCUL))
#define bFM0P_MFT0_FRT_TCSC1_MSZC0             *((volatile unsigned int*)(0x42400AE0UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZC1             *((volatile unsigned int*)(0x42400AE4UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZC2             *((volatile unsigned int*)(0x42400AE8UL))
#define bFM0P_MFT0_FRT_TCSC1_MSZC3             *((volatile unsigned int*)(0x42400AECUL))
#define bFM0P_MFT0_FRT_TCSC1_MSPC0             *((volatile unsigned int*)(0x42400AF0UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPC1             *((volatile unsigned int*)(0x42400AF4UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPC2             *((volatile unsigned int*)(0x42400AF8UL))
#define bFM0P_MFT0_FRT_TCSC1_MSPC3             *((volatile unsigned int*)(0x42400AFCUL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP016       *((volatile unsigned int*)(0x42400BC0UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP017       *((volatile unsigned int*)(0x42400BC4UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP018       *((volatile unsigned int*)(0x42400BC8UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP019       *((volatile unsigned int*)(0x42400BCCUL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP020       *((volatile unsigned int*)(0x42400BD0UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP021       *((volatile unsigned int*)(0x42400BD4UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP022       *((volatile unsigned int*)(0x42400BD8UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP023       *((volatile unsigned int*)(0x42400BDCUL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP024       *((volatile unsigned int*)(0x42400BE0UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP025       *((volatile unsigned int*)(0x42400BE4UL))
#define bFM0P_MFT0_FRT_TCDT2_FRT_TCCP026       *((volatile unsigned int*)(0x42400BE8UL))
#define bFM0P_MFT0_FRT_TCSA2_CLK0              *((volatile unsigned int*)(0x42400C00UL))
#define bFM0P_MFT0_FRT_TCSA2_CLK1              *((volatile unsigned int*)(0x42400C04UL))
#define bFM0P_MFT0_FRT_TCSA2_CLK2              *((volatile unsigned int*)(0x42400C08UL))
#define bFM0P_MFT0_FRT_TCSA2_CLK3              *((volatile unsigned int*)(0x42400C0CUL))
#define bFM0P_MFT0_FRT_TCSA2_SCLR              *((volatile unsigned int*)(0x42400C10UL))
#define bFM0P_MFT0_FRT_TCSA2_MODE              *((volatile unsigned int*)(0x42400C14UL))
#define bFM0P_MFT0_FRT_TCSA2_STOP              *((volatile unsigned int*)(0x42400C18UL))
#define bFM0P_MFT0_FRT_TCSA2_BFE               *((volatile unsigned int*)(0x42400C1CUL))
#define bFM0P_MFT0_FRT_TCSA2_ICRE              *((volatile unsigned int*)(0x42400C20UL))
#define bFM0P_MFT0_FRT_TCSA2_ICLR              *((volatile unsigned int*)(0x42400C24UL))
#define bFM0P_MFT0_FRT_TCSA2_IRQZE             *((volatile unsigned int*)(0x42400C34UL))
#define bFM0P_MFT0_FRT_TCSA2_IRQZF             *((volatile unsigned int*)(0x42400C38UL))
#define bFM0P_MFT0_FRT_TCSA2_ECKE              *((volatile unsigned int*)(0x42400C3CUL))
#define bFM0P_MFT0_FRT_TCSC2_MSZI0             *((volatile unsigned int*)(0x42400C40UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZI1             *((volatile unsigned int*)(0x42400C44UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZI2             *((volatile unsigned int*)(0x42400C48UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZI3             *((volatile unsigned int*)(0x42400C4CUL))
#define bFM0P_MFT0_FRT_TCSC2_MSPI0             *((volatile unsigned int*)(0x42400C50UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPI1             *((volatile unsigned int*)(0x42400C54UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPI2             *((volatile unsigned int*)(0x42400C58UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPI3             *((volatile unsigned int*)(0x42400C5CUL))
#define bFM0P_MFT0_FRT_TCSC2_MSZC0             *((volatile unsigned int*)(0x42400C60UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZC1             *((volatile unsigned int*)(0x42400C64UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZC2             *((volatile unsigned int*)(0x42400C68UL))
#define bFM0P_MFT0_FRT_TCSC2_MSZC3             *((volatile unsigned int*)(0x42400C6CUL))
#define bFM0P_MFT0_FRT_TCSC2_MSPC0             *((volatile unsigned int*)(0x42400C70UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPC1             *((volatile unsigned int*)(0x42400C74UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPC2             *((volatile unsigned int*)(0x42400C78UL))
#define bFM0P_MFT0_FRT_TCSC2_MSPC3             *((volatile unsigned int*)(0x42400C7CUL))
#define bFM0P_MFT0_FRT_TCAL_STOP00             *((volatile unsigned int*)(0x42400C80UL))
#define bFM0P_MFT0_FRT_TCAL_STOP01             *((volatile unsigned int*)(0x42400C84UL))
#define bFM0P_MFT0_FRT_TCAL_STOP02             *((volatile unsigned int*)(0x42400C88UL))
#define bFM0P_MFT0_FRT_TCAL_STOP10             *((volatile unsigned int*)(0x42400C8CUL))
#define bFM0P_MFT0_FRT_TCAL_STOP11             *((volatile unsigned int*)(0x42400C90UL))
#define bFM0P_MFT0_FRT_TCAL_STOP12             *((volatile unsigned int*)(0x42400C94UL))
#define bFM0P_MFT0_FRT_TCAL_STOP20             *((volatile unsigned int*)(0x42400C98UL))
#define bFM0P_MFT0_FRT_TCAL_STOP21             *((volatile unsigned int*)(0x42400C9CUL))
#define bFM0P_MFT0_FRT_TCAL_STOP22             *((volatile unsigned int*)(0x42400CA0UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR00             *((volatile unsigned int*)(0x42400CC0UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR01             *((volatile unsigned int*)(0x42400CC4UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR02             *((volatile unsigned int*)(0x42400CC8UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR10             *((volatile unsigned int*)(0x42400CCCUL))
#define bFM0P_MFT0_FRT_TCAL_SCLR11             *((volatile unsigned int*)(0x42400CD0UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR12             *((volatile unsigned int*)(0x42400CD4UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR20             *((volatile unsigned int*)(0x42400CD8UL))
#define bFM0P_MFT0_FRT_TCAL_SCLR21             *((volatile unsigned int*)(0x42400CDCUL))
#define bFM0P_MFT0_FRT_TCAL_SCLR22             *((volatile unsigned int*)(0x42400CE0UL))

/* Multifunction Timer unit 0 Output Compare Unit registers */
#define bFM0P_MFT0_OCU_OCSA10_CST0             *((volatile unsigned int*)(0x42400300UL))
#define bFM0P_MFT0_OCU_OCSA10_CST1             *((volatile unsigned int*)(0x42400304UL))
#define bFM0P_MFT0_OCU_OCSA10_IOE0             *((volatile unsigned int*)(0x42400310UL))
#define bFM0P_MFT0_OCU_OCSA10_IOE1             *((volatile unsigned int*)(0x42400314UL))
#define bFM0P_MFT0_OCU_OCSA10_IOP0             *((volatile unsigned int*)(0x42400318UL))
#define bFM0P_MFT0_OCU_OCSA10_IOP1             *((volatile unsigned int*)(0x4240031CUL))
#define bFM0P_MFT0_OCU_OCSB10_OTD0             *((volatile unsigned int*)(0x42400320UL))
#define bFM0P_MFT0_OCU_OCSB10_OTD1             *((volatile unsigned int*)(0x42400324UL))
#define bFM0P_MFT0_OCU_OCSB10_CMOD             *((volatile unsigned int*)(0x42400330UL))
#define bFM0P_MFT0_OCU_OCSB10_FM4              *((volatile unsigned int*)(0x4240033CUL))
#define bFM0P_MFT0_OCU_OCSD10_OCCP0BUFE0       *((volatile unsigned int*)(0x42400340UL))
#define bFM0P_MFT0_OCU_OCSD10_OCCP0BUFE1       *((volatile unsigned int*)(0x42400344UL))
#define bFM0P_MFT0_OCU_OCSD10_OCCP1BUFE0       *((volatile unsigned int*)(0x42400348UL))
#define bFM0P_MFT0_OCU_OCSD10_OCCP1BUFE1       *((volatile unsigned int*)(0x4240034CUL))
#define bFM0P_MFT0_OCU_OCSD10_OCSE0BUFE0       *((volatile unsigned int*)(0x42400350UL))
#define bFM0P_MFT0_OCU_OCSD10_OCSE0BUFE1       *((volatile unsigned int*)(0x42400354UL))
#define bFM0P_MFT0_OCU_OCSD10_OCSE1BUFE0       *((volatile unsigned int*)(0x42400358UL))
#define bFM0P_MFT0_OCU_OCSD10_OCSE1BUFE1       *((volatile unsigned int*)(0x4240035CUL))
#define bFM0P_MFT0_OCU_OCSA32_CST0             *((volatile unsigned int*)(0x42400380UL))
#define bFM0P_MFT0_OCU_OCSA32_CST1             *((volatile unsigned int*)(0x42400384UL))
#define bFM0P_MFT0_OCU_OCSA32_IOE0             *((volatile unsigned int*)(0x42400390UL))
#define bFM0P_MFT0_OCU_OCSA32_IOE1             *((volatile unsigned int*)(0x42400394UL))
#define bFM0P_MFT0_OCU_OCSA32_IOP0             *((volatile unsigned int*)(0x42400398UL))
#define bFM0P_MFT0_OCU_OCSA32_IOP1             *((volatile unsigned int*)(0x4240039CUL))
#define bFM0P_MFT0_OCU_OCSB32_OTD0             *((volatile unsigned int*)(0x424003A0UL))
#define bFM0P_MFT0_OCU_OCSB32_OTD1             *((volatile unsigned int*)(0x424003A4UL))
#define bFM0P_MFT0_OCU_OCSB32_CMOD             *((volatile unsigned int*)(0x424003B0UL))
#define bFM0P_MFT0_OCU_OCSB32_FM4              *((volatile unsigned int*)(0x424003BCUL))
#define bFM0P_MFT0_OCU_OCSD32_OCCP0BUFE0       *((volatile unsigned int*)(0x424003C0UL))
#define bFM0P_MFT0_OCU_OCSD32_OCCP0BUFE1       *((volatile unsigned int*)(0x424003C4UL))
#define bFM0P_MFT0_OCU_OCSD32_OCCP1BUFE0       *((volatile unsigned int*)(0x424003C8UL))
#define bFM0P_MFT0_OCU_OCSD32_OCCP1BUFE1       *((volatile unsigned int*)(0x424003CCUL))
#define bFM0P_MFT0_OCU_OCSD32_OCSE0BUFE0       *((volatile unsigned int*)(0x424003D0UL))
#define bFM0P_MFT0_OCU_OCSD32_OCSE0BUFE1       *((volatile unsigned int*)(0x424003D4UL))
#define bFM0P_MFT0_OCU_OCSD32_OCSE1BUFE0       *((volatile unsigned int*)(0x424003D8UL))
#define bFM0P_MFT0_OCU_OCSD32_OCSE1BUFE1       *((volatile unsigned int*)(0x424003DCUL))
#define bFM0P_MFT0_OCU_OCSA54_CST0             *((volatile unsigned int*)(0x42400400UL))
#define bFM0P_MFT0_OCU_OCSA54_CST1             *((volatile unsigned int*)(0x42400404UL))
#define bFM0P_MFT0_OCU_OCSA54_IOE0             *((volatile unsigned int*)(0x42400410UL))
#define bFM0P_MFT0_OCU_OCSA54_IOE1             *((volatile unsigned int*)(0x42400414UL))
#define bFM0P_MFT0_OCU_OCSA54_IOP0             *((volatile unsigned int*)(0x42400418UL))
#define bFM0P_MFT0_OCU_OCSA54_IOP1             *((volatile unsigned int*)(0x4240041CUL))
#define bFM0P_MFT0_OCU_OCSB54_OTD0             *((volatile unsigned int*)(0x42400420UL))
#define bFM0P_MFT0_OCU_OCSB54_OTD1             *((volatile unsigned int*)(0x42400424UL))
#define bFM0P_MFT0_OCU_OCSB54_CMOD             *((volatile unsigned int*)(0x42400430UL))
#define bFM0P_MFT0_OCU_OCSB54_FM4              *((volatile unsigned int*)(0x4240043CUL))
#define bFM0P_MFT0_OCU_OCSD54_OCCP0BUFE0       *((volatile unsigned int*)(0x42400440UL))
#define bFM0P_MFT0_OCU_OCSD54_OCCP0BUFE1       *((volatile unsigned int*)(0x42400444UL))
#define bFM0P_MFT0_OCU_OCSD54_OCCP1BUFE0       *((volatile unsigned int*)(0x42400448UL))
#define bFM0P_MFT0_OCU_OCSD54_OCCP1BUFE1       *((volatile unsigned int*)(0x4240044CUL))
#define bFM0P_MFT0_OCU_OCSD54_OCSE0BUFE0       *((volatile unsigned int*)(0x42400450UL))
#define bFM0P_MFT0_OCU_OCSD54_OCSE0BUFE1       *((volatile unsigned int*)(0x42400454UL))
#define bFM0P_MFT0_OCU_OCSD54_OCSE1BUFE0       *((volatile unsigned int*)(0x42400458UL))
#define bFM0P_MFT0_OCU_OCSD54_OCSE1BUFE1       *((volatile unsigned int*)(0x4240045CUL))
#define bFM0P_MFT0_OCU_OCSC_MOD0               *((volatile unsigned int*)(0x424004A0UL))
#define bFM0P_MFT0_OCU_OCSC_MOD1               *((volatile unsigned int*)(0x424004A4UL))
#define bFM0P_MFT0_OCU_OCSC_MOD2               *((volatile unsigned int*)(0x424004A8UL))
#define bFM0P_MFT0_OCU_OCSC_MOD3               *((volatile unsigned int*)(0x424004ACUL))
#define bFM0P_MFT0_OCU_OCSC_MOD4               *((volatile unsigned int*)(0x424004B0UL))
#define bFM0P_MFT0_OCU_OCSC_MOD5               *((volatile unsigned int*)(0x424004B4UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE0             *((volatile unsigned int*)(0x42400500UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE1             *((volatile unsigned int*)(0x42400504UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE2             *((volatile unsigned int*)(0x42400508UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE3             *((volatile unsigned int*)(0x4240050CUL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE4             *((volatile unsigned int*)(0x42400510UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE5             *((volatile unsigned int*)(0x42400514UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE6             *((volatile unsigned int*)(0x42400518UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE7             *((volatile unsigned int*)(0x4240051CUL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE8             *((volatile unsigned int*)(0x42400520UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE9             *((volatile unsigned int*)(0x42400524UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE10            *((volatile unsigned int*)(0x42400528UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE11            *((volatile unsigned int*)(0x4240052CUL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE12            *((volatile unsigned int*)(0x42400530UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE13            *((volatile unsigned int*)(0x42400534UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE14            *((volatile unsigned int*)(0x42400538UL))
#define bFM0P_MFT0_OCU_OCSE0_OCSE15            *((volatile unsigned int*)(0x4240053CUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE0             *((volatile unsigned int*)(0x42400580UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE1             *((volatile unsigned int*)(0x42400584UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE2             *((volatile unsigned int*)(0x42400588UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE3             *((volatile unsigned int*)(0x4240058CUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE4             *((volatile unsigned int*)(0x42400590UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE5             *((volatile unsigned int*)(0x42400594UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE6             *((volatile unsigned int*)(0x42400598UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE7             *((volatile unsigned int*)(0x4240059CUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE8             *((volatile unsigned int*)(0x424005A0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE9             *((volatile unsigned int*)(0x424005A4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE10            *((volatile unsigned int*)(0x424005A8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE11            *((volatile unsigned int*)(0x424005ACUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE12            *((volatile unsigned int*)(0x424005B0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE13            *((volatile unsigned int*)(0x424005B4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE14            *((volatile unsigned int*)(0x424005B8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE15            *((volatile unsigned int*)(0x424005BCUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE16            *((volatile unsigned int*)(0x424005C0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE17            *((volatile unsigned int*)(0x424005C4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE18            *((volatile unsigned int*)(0x424005C8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE19            *((volatile unsigned int*)(0x424005CCUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE20            *((volatile unsigned int*)(0x424005D0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE21            *((volatile unsigned int*)(0x424005D4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE22            *((volatile unsigned int*)(0x424005D8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE23            *((volatile unsigned int*)(0x424005DCUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE24            *((volatile unsigned int*)(0x424005E0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE25            *((volatile unsigned int*)(0x424005E4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE26            *((volatile unsigned int*)(0x424005E8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE27            *((volatile unsigned int*)(0x424005ECUL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE28            *((volatile unsigned int*)(0x424005F0UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE29            *((volatile unsigned int*)(0x424005F4UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE30            *((volatile unsigned int*)(0x424005F8UL))
#define bFM0P_MFT0_OCU_OCSE1_OCSE31            *((volatile unsigned int*)(0x424005FCUL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE0             *((volatile unsigned int*)(0x42400600UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE1             *((volatile unsigned int*)(0x42400604UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE2             *((volatile unsigned int*)(0x42400608UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE3             *((volatile unsigned int*)(0x4240060CUL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE4             *((volatile unsigned int*)(0x42400610UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE5             *((volatile unsigned int*)(0x42400614UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE6             *((volatile unsigned int*)(0x42400618UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE7             *((volatile unsigned int*)(0x4240061CUL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE8             *((volatile unsigned int*)(0x42400620UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE9             *((volatile unsigned int*)(0x42400624UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE10            *((volatile unsigned int*)(0x42400628UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE11            *((volatile unsigned int*)(0x4240062CUL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE12            *((volatile unsigned int*)(0x42400630UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE13            *((volatile unsigned int*)(0x42400634UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE14            *((volatile unsigned int*)(0x42400638UL))
#define bFM0P_MFT0_OCU_OCSE2_OCSE15            *((volatile unsigned int*)(0x4240063CUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE0             *((volatile unsigned int*)(0x42400680UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE1             *((volatile unsigned int*)(0x42400684UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE2             *((volatile unsigned int*)(0x42400688UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE3             *((volatile unsigned int*)(0x4240068CUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE4             *((volatile unsigned int*)(0x42400690UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE5             *((volatile unsigned int*)(0x42400694UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE6             *((volatile unsigned int*)(0x42400698UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE7             *((volatile unsigned int*)(0x4240069CUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE8             *((volatile unsigned int*)(0x424006A0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE9             *((volatile unsigned int*)(0x424006A4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE10            *((volatile unsigned int*)(0x424006A8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE11            *((volatile unsigned int*)(0x424006ACUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE12            *((volatile unsigned int*)(0x424006B0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE13            *((volatile unsigned int*)(0x424006B4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE14            *((volatile unsigned int*)(0x424006B8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE15            *((volatile unsigned int*)(0x424006BCUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE16            *((volatile unsigned int*)(0x424006C0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE17            *((volatile unsigned int*)(0x424006C4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE18            *((volatile unsigned int*)(0x424006C8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE19            *((volatile unsigned int*)(0x424006CCUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE20            *((volatile unsigned int*)(0x424006D0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE21            *((volatile unsigned int*)(0x424006D4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE22            *((volatile unsigned int*)(0x424006D8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE23            *((volatile unsigned int*)(0x424006DCUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE24            *((volatile unsigned int*)(0x424006E0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE25            *((volatile unsigned int*)(0x424006E4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE26            *((volatile unsigned int*)(0x424006E8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE27            *((volatile unsigned int*)(0x424006ECUL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE28            *((volatile unsigned int*)(0x424006F0UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE29            *((volatile unsigned int*)(0x424006F4UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE30            *((volatile unsigned int*)(0x424006F8UL))
#define bFM0P_MFT0_OCU_OCSE3_OCSE31            *((volatile unsigned int*)(0x424006FCUL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE0             *((volatile unsigned int*)(0x42400700UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE1             *((volatile unsigned int*)(0x42400704UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE2             *((volatile unsigned int*)(0x42400708UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE3             *((volatile unsigned int*)(0x4240070CUL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE4             *((volatile unsigned int*)(0x42400710UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE5             *((volatile unsigned int*)(0x42400714UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE6             *((volatile unsigned int*)(0x42400718UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE7             *((volatile unsigned int*)(0x4240071CUL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE8             *((volatile unsigned int*)(0x42400720UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE9             *((volatile unsigned int*)(0x42400724UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE10            *((volatile unsigned int*)(0x42400728UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE11            *((volatile unsigned int*)(0x4240072CUL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE12            *((volatile unsigned int*)(0x42400730UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE13            *((volatile unsigned int*)(0x42400734UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE14            *((volatile unsigned int*)(0x42400738UL))
#define bFM0P_MFT0_OCU_OCSE4_OCSE15            *((volatile unsigned int*)(0x4240073CUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE0             *((volatile unsigned int*)(0x42400780UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE1             *((volatile unsigned int*)(0x42400784UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE2             *((volatile unsigned int*)(0x42400788UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE3             *((volatile unsigned int*)(0x4240078CUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE4             *((volatile unsigned int*)(0x42400790UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE5             *((volatile unsigned int*)(0x42400794UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE6             *((volatile unsigned int*)(0x42400798UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE7             *((volatile unsigned int*)(0x4240079CUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE8             *((volatile unsigned int*)(0x424007A0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE9             *((volatile unsigned int*)(0x424007A4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE10            *((volatile unsigned int*)(0x424007A8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE11            *((volatile unsigned int*)(0x424007ACUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE12            *((volatile unsigned int*)(0x424007B0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE13            *((volatile unsigned int*)(0x424007B4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE14            *((volatile unsigned int*)(0x424007B8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE15            *((volatile unsigned int*)(0x424007BCUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE16            *((volatile unsigned int*)(0x424007C0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE17            *((volatile unsigned int*)(0x424007C4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE18            *((volatile unsigned int*)(0x424007C8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE19            *((volatile unsigned int*)(0x424007CCUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE20            *((volatile unsigned int*)(0x424007D0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE21            *((volatile unsigned int*)(0x424007D4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE22            *((volatile unsigned int*)(0x424007D8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE23            *((volatile unsigned int*)(0x424007DCUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE24            *((volatile unsigned int*)(0x424007E0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE25            *((volatile unsigned int*)(0x424007E4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE26            *((volatile unsigned int*)(0x424007E8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE27            *((volatile unsigned int*)(0x424007ECUL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE28            *((volatile unsigned int*)(0x424007F0UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE29            *((volatile unsigned int*)(0x424007F4UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE30            *((volatile unsigned int*)(0x424007F8UL))
#define bFM0P_MFT0_OCU_OCSE5_OCSE31            *((volatile unsigned int*)(0x424007FCUL))
#define bFM0P_MFT0_OCU_OCFS10_FSO00            *((volatile unsigned int*)(0x42400D00UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO01            *((volatile unsigned int*)(0x42400D04UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO02            *((volatile unsigned int*)(0x42400D08UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO03            *((volatile unsigned int*)(0x42400D0CUL))
#define bFM0P_MFT0_OCU_OCFS10_FSO10            *((volatile unsigned int*)(0x42400D10UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO11            *((volatile unsigned int*)(0x42400D14UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO12            *((volatile unsigned int*)(0x42400D18UL))
#define bFM0P_MFT0_OCU_OCFS10_FSO13            *((volatile unsigned int*)(0x42400D1CUL))
#define bFM0P_MFT0_OCU_OCFS32_FSO00            *((volatile unsigned int*)(0x42400D20UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO01            *((volatile unsigned int*)(0x42400D24UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO02            *((volatile unsigned int*)(0x42400D28UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO03            *((volatile unsigned int*)(0x42400D2CUL))
#define bFM0P_MFT0_OCU_OCFS32_FSO10            *((volatile unsigned int*)(0x42400D30UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO11            *((volatile unsigned int*)(0x42400D34UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO12            *((volatile unsigned int*)(0x42400D38UL))
#define bFM0P_MFT0_OCU_OCFS32_FSO13            *((volatile unsigned int*)(0x42400D3CUL))
#define bFM0P_MFT0_OCU_OCFS54_FSO00            *((volatile unsigned int*)(0x42400D40UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO01            *((volatile unsigned int*)(0x42400D44UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO02            *((volatile unsigned int*)(0x42400D48UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO03            *((volatile unsigned int*)(0x42400D4CUL))
#define bFM0P_MFT0_OCU_OCFS54_FSO10            *((volatile unsigned int*)(0x42400D50UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO11            *((volatile unsigned int*)(0x42400D54UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO12            *((volatile unsigned int*)(0x42400D58UL))
#define bFM0P_MFT0_OCU_OCFS54_FSO13            *((volatile unsigned int*)(0x42400D5CUL))

/* Multifunction Timer unit 0 Waveform Generator and Noise Canceler registers */
#define bFM0P_MFT0_WFG_WFSA10_DCK0             *((volatile unsigned int*)(0x42401480UL))
#define bFM0P_MFT0_WFG_WFSA10_DCK1             *((volatile unsigned int*)(0x42401484UL))
#define bFM0P_MFT0_WFG_WFSA10_DCK2             *((volatile unsigned int*)(0x42401488UL))
#define bFM0P_MFT0_WFG_WFSA10_TMD0             *((volatile unsigned int*)(0x4240148CUL))
#define bFM0P_MFT0_WFG_WFSA10_TMD1             *((volatile unsigned int*)(0x42401490UL))
#define bFM0P_MFT0_WFG_WFSA10_TMD2             *((volatile unsigned int*)(0x42401494UL))
#define bFM0P_MFT0_WFG_WFSA10_GTEN0            *((volatile unsigned int*)(0x42401498UL))
#define bFM0P_MFT0_WFG_WFSA10_GTEN1            *((volatile unsigned int*)(0x4240149CUL))
#define bFM0P_MFT0_WFG_WFSA10_PSEL0            *((volatile unsigned int*)(0x424014A0UL))
#define bFM0P_MFT0_WFG_WFSA10_PSEL1            *((volatile unsigned int*)(0x424014A4UL))
#define bFM0P_MFT0_WFG_WFSA10_PGEN0            *((volatile unsigned int*)(0x424014A8UL))
#define bFM0P_MFT0_WFG_WFSA10_PGEN1            *((volatile unsigned int*)(0x424014ACUL))
#define bFM0P_MFT0_WFG_WFSA10_DMOD0            *((volatile unsigned int*)(0x424014B0UL))
#define bFM0P_MFT0_WFG_WFSA10_DMOD1            *((volatile unsigned int*)(0x424014B4UL))
#define bFM0P_MFT0_WFG_WFSA32_DCK0             *((volatile unsigned int*)(0x42401500UL))
#define bFM0P_MFT0_WFG_WFSA32_DCK1             *((volatile unsigned int*)(0x42401504UL))
#define bFM0P_MFT0_WFG_WFSA32_DCK2             *((volatile unsigned int*)(0x42401508UL))
#define bFM0P_MFT0_WFG_WFSA32_TMD0             *((volatile unsigned int*)(0x4240150CUL))
#define bFM0P_MFT0_WFG_WFSA32_TMD1             *((volatile unsigned int*)(0x42401510UL))
#define bFM0P_MFT0_WFG_WFSA32_TMD2             *((volatile unsigned int*)(0x42401514UL))
#define bFM0P_MFT0_WFG_WFSA32_GTEN0            *((volatile unsigned int*)(0x42401518UL))
#define bFM0P_MFT0_WFG_WFSA32_GTEN1            *((volatile unsigned int*)(0x4240151CUL))
#define bFM0P_MFT0_WFG_WFSA32_PSEL0            *((volatile unsigned int*)(0x42401520UL))
#define bFM0P_MFT0_WFG_WFSA32_PSEL1            *((volatile unsigned int*)(0x42401524UL))
#define bFM0P_MFT0_WFG_WFSA32_PGEN0            *((volatile unsigned int*)(0x42401528UL))
#define bFM0P_MFT0_WFG_WFSA32_PGEN1            *((volatile unsigned int*)(0x4240152CUL))
#define bFM0P_MFT0_WFG_WFSA32_DMOD0            *((volatile unsigned int*)(0x42401530UL))
#define bFM0P_MFT0_WFG_WFSA32_DMOD1            *((volatile unsigned int*)(0x42401534UL))
#define bFM0P_MFT0_WFG_WFSA54_DCK0             *((volatile unsigned int*)(0x42401580UL))
#define bFM0P_MFT0_WFG_WFSA54_DCK1             *((volatile unsigned int*)(0x42401584UL))
#define bFM0P_MFT0_WFG_WFSA54_DCK2             *((volatile unsigned int*)(0x42401588UL))
#define bFM0P_MFT0_WFG_WFSA54_TMD0             *((volatile unsigned int*)(0x4240158CUL))
#define bFM0P_MFT0_WFG_WFSA54_TMD1             *((volatile unsigned int*)(0x42401590UL))
#define bFM0P_MFT0_WFG_WFSA54_TMD2             *((volatile unsigned int*)(0x42401594UL))
#define bFM0P_MFT0_WFG_WFSA54_GTEN0            *((volatile unsigned int*)(0x42401598UL))
#define bFM0P_MFT0_WFG_WFSA54_GTEN1            *((volatile unsigned int*)(0x4240159CUL))
#define bFM0P_MFT0_WFG_WFSA54_PSEL0            *((volatile unsigned int*)(0x424015A0UL))
#define bFM0P_MFT0_WFG_WFSA54_PSEL1            *((volatile unsigned int*)(0x424015A4UL))
#define bFM0P_MFT0_WFG_WFSA54_PGEN0            *((volatile unsigned int*)(0x424015A8UL))
#define bFM0P_MFT0_WFG_WFSA54_PGEN1            *((volatile unsigned int*)(0x424015ACUL))
#define bFM0P_MFT0_WFG_WFSA54_DMOD0            *((volatile unsigned int*)(0x424015B0UL))
#define bFM0P_MFT0_WFG_WFSA54_DMOD1            *((volatile unsigned int*)(0x424015B4UL))
#define bFM0P_MFT0_WFG_WFIR_DTIFA              *((volatile unsigned int*)(0x42401600UL))
#define bFM0P_MFT0_WFG_WFIR_DTICA              *((volatile unsigned int*)(0x42401604UL))
#define bFM0P_MFT0_WFG_WFIR_DTIFB              *((volatile unsigned int*)(0x42401608UL))
#define bFM0P_MFT0_WFG_WFIR_DTICB              *((volatile unsigned int*)(0x4240160CUL))
#define bFM0P_MFT0_WFG_WFIR_TMIF10             *((volatile unsigned int*)(0x42401610UL))
#define bFM0P_MFT0_WFG_WFIR_TMIC10             *((volatile unsigned int*)(0x42401614UL))
#define bFM0P_MFT0_WFG_WFIR_TMIE10             *((volatile unsigned int*)(0x42401618UL))
#define bFM0P_MFT0_WFG_WFIR_TMIS10             *((volatile unsigned int*)(0x4240161CUL))
#define bFM0P_MFT0_WFG_WFIR_TMIF32             *((volatile unsigned int*)(0x42401620UL))
#define bFM0P_MFT0_WFG_WFIR_TMIC32             *((volatile unsigned int*)(0x42401624UL))
#define bFM0P_MFT0_WFG_WFIR_TMIE32             *((volatile unsigned int*)(0x42401628UL))
#define bFM0P_MFT0_WFG_WFIR_TMIS32             *((volatile unsigned int*)(0x4240162CUL))
#define bFM0P_MFT0_WFG_WFIR_TMIF54             *((volatile unsigned int*)(0x42401630UL))
#define bFM0P_MFT0_WFG_WFIR_TMIC54             *((volatile unsigned int*)(0x42401634UL))
#define bFM0P_MFT0_WFG_WFIR_TMIE54             *((volatile unsigned int*)(0x42401638UL))
#define bFM0P_MFT0_WFG_WFIR_TMIS54             *((volatile unsigned int*)(0x4240163CUL))
#define bFM0P_MFT0_WFG_NZCL_DTIEA              *((volatile unsigned int*)(0x42401680UL))
#define bFM0P_MFT0_WFG_NZCL_NWS0               *((volatile unsigned int*)(0x42401684UL))
#define bFM0P_MFT0_WFG_NZCL_NWS1               *((volatile unsigned int*)(0x42401688UL))
#define bFM0P_MFT0_WFG_NZCL_NWS2               *((volatile unsigned int*)(0x4240168CUL))
#define bFM0P_MFT0_WFG_NZCL_SDTI               *((volatile unsigned int*)(0x42401690UL))
#define bFM0P_MFT0_WFG_NZCL_DTIEB              *((volatile unsigned int*)(0x42401694UL))
#define bFM0P_MFT0_WFG_NZCL_DIMA               *((volatile unsigned int*)(0x424016A0UL))
#define bFM0P_MFT0_WFG_NZCL_DIMB               *((volatile unsigned int*)(0x424016A4UL))
#define bFM0P_MFT0_WFG_NZCL_WIM10              *((volatile unsigned int*)(0x424016B0UL))
#define bFM0P_MFT0_WFG_NZCL_WIM32              *((volatile unsigned int*)(0x424016B4UL))
#define bFM0P_MFT0_WFG_NZCL_WIM54              *((volatile unsigned int*)(0x424016B8UL))

/* Multifunction Timer unit 0 Input Capture Unit registers */
#define bFM0P_MFT0_ICU_ICFS10_FSI00            *((volatile unsigned int*)(0x42400D80UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI01            *((volatile unsigned int*)(0x42400D84UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI02            *((volatile unsigned int*)(0x42400D88UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI03            *((volatile unsigned int*)(0x42400D8CUL))
#define bFM0P_MFT0_ICU_ICFS10_FSI10            *((volatile unsigned int*)(0x42400D90UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI11            *((volatile unsigned int*)(0x42400D94UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI12            *((volatile unsigned int*)(0x42400D98UL))
#define bFM0P_MFT0_ICU_ICFS10_FSI13            *((volatile unsigned int*)(0x42400D9CUL))
#define bFM0P_MFT0_ICU_ICFS32_FSI00            *((volatile unsigned int*)(0x42400DA0UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI01            *((volatile unsigned int*)(0x42400DA4UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI02            *((volatile unsigned int*)(0x42400DA8UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI03            *((volatile unsigned int*)(0x42400DACUL))
#define bFM0P_MFT0_ICU_ICFS32_FSI10            *((volatile unsigned int*)(0x42400DB0UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI11            *((volatile unsigned int*)(0x42400DB4UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI12            *((volatile unsigned int*)(0x42400DB8UL))
#define bFM0P_MFT0_ICU_ICFS32_FSI13            *((volatile unsigned int*)(0x42400DBCUL))
#define bFM0P_MFT0_ICU_ICSA10_EG00             *((volatile unsigned int*)(0x42401080UL))
#define bFM0P_MFT0_ICU_ICSA10_EG01             *((volatile unsigned int*)(0x42401084UL))
#define bFM0P_MFT0_ICU_ICSA10_EG10             *((volatile unsigned int*)(0x42401088UL))
#define bFM0P_MFT0_ICU_ICSA10_EG11             *((volatile unsigned int*)(0x4240108CUL))
#define bFM0P_MFT0_ICU_ICSA10_ICE0             *((volatile unsigned int*)(0x42401090UL))
#define bFM0P_MFT0_ICU_ICSA10_ICE1             *((volatile unsigned int*)(0x42401094UL))
#define bFM0P_MFT0_ICU_ICSA10_ICP0             *((volatile unsigned int*)(0x42401098UL))
#define bFM0P_MFT0_ICU_ICSA10_ICP1             *((volatile unsigned int*)(0x4240109CUL))
#define bFM0P_MFT0_ICU_ICSB10_IEI0             *((volatile unsigned int*)(0x424010A0UL))
#define bFM0P_MFT0_ICU_ICSB10_IEI1             *((volatile unsigned int*)(0x424010A4UL))
#define bFM0P_MFT0_ICU_ICSA32_EG00             *((volatile unsigned int*)(0x42401100UL))
#define bFM0P_MFT0_ICU_ICSA32_EG01             *((volatile unsigned int*)(0x42401104UL))
#define bFM0P_MFT0_ICU_ICSA32_EG10             *((volatile unsigned int*)(0x42401108UL))
#define bFM0P_MFT0_ICU_ICSA32_EG11             *((volatile unsigned int*)(0x4240110CUL))
#define bFM0P_MFT0_ICU_ICSA32_ICE0             *((volatile unsigned int*)(0x42401110UL))
#define bFM0P_MFT0_ICU_ICSA32_ICE1             *((volatile unsigned int*)(0x42401114UL))
#define bFM0P_MFT0_ICU_ICSA32_ICP0             *((volatile unsigned int*)(0x42401118UL))
#define bFM0P_MFT0_ICU_ICSA32_ICP1             *((volatile unsigned int*)(0x4240111CUL))
#define bFM0P_MFT0_ICU_ICSB32_IEI0             *((volatile unsigned int*)(0x42401120UL))
#define bFM0P_MFT0_ICU_ICSB32_IEI1             *((volatile unsigned int*)(0x42401124UL))

/* Multifunction Timer unit 0 ADC Start Compare Unit registers */
#define bFM0P_MFT0_ADCMP_ACFS10_FSA00          *((volatile unsigned int*)(0x42400E00UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA01          *((volatile unsigned int*)(0x42400E04UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA02          *((volatile unsigned int*)(0x42400E08UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA03          *((volatile unsigned int*)(0x42400E0CUL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA10          *((volatile unsigned int*)(0x42400E10UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA11          *((volatile unsigned int*)(0x42400E14UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA12          *((volatile unsigned int*)(0x42400E18UL))
#define bFM0P_MFT0_ADCMP_ACFS10_FSA13          *((volatile unsigned int*)(0x42400E1CUL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA00          *((volatile unsigned int*)(0x42400E20UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA01          *((volatile unsigned int*)(0x42400E24UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA02          *((volatile unsigned int*)(0x42400E28UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA03          *((volatile unsigned int*)(0x42400E2CUL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA10          *((volatile unsigned int*)(0x42400E30UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA11          *((volatile unsigned int*)(0x42400E34UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA12          *((volatile unsigned int*)(0x42400E38UL))
#define bFM0P_MFT0_ADCMP_ACFS32_FSA13          *((volatile unsigned int*)(0x42400E3CUL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA00          *((volatile unsigned int*)(0x42400E40UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA01          *((volatile unsigned int*)(0x42400E44UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA02          *((volatile unsigned int*)(0x42400E48UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA03          *((volatile unsigned int*)(0x42400E4CUL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA10          *((volatile unsigned int*)(0x42400E50UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA11          *((volatile unsigned int*)(0x42400E54UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA12          *((volatile unsigned int*)(0x42400E58UL))
#define bFM0P_MFT0_ADCMP_ACFS54_FSA13          *((volatile unsigned int*)(0x42400E5CUL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP0           *((volatile unsigned int*)(0x42401740UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP1           *((volatile unsigned int*)(0x42401744UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP2           *((volatile unsigned int*)(0x42401748UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP3           *((volatile unsigned int*)(0x4240174CUL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP4           *((volatile unsigned int*)(0x42401750UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP5           *((volatile unsigned int*)(0x42401754UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP6           *((volatile unsigned int*)(0x42401758UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP7           *((volatile unsigned int*)(0x4240175CUL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP8           *((volatile unsigned int*)(0x42401760UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP9           *((volatile unsigned int*)(0x42401764UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP10          *((volatile unsigned int*)(0x42401768UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP11          *((volatile unsigned int*)(0x4240176CUL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP12          *((volatile unsigned int*)(0x42401770UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP13          *((volatile unsigned int*)(0x42401774UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP14          *((volatile unsigned int*)(0x42401778UL))
#define bFM0P_MFT0_ADCMP_ACMP0_ACMP15          *((volatile unsigned int*)(0x4240177CUL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP0           *((volatile unsigned int*)(0x424017C0UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP1           *((volatile unsigned int*)(0x424017C4UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP2           *((volatile unsigned int*)(0x424017C8UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP3           *((volatile unsigned int*)(0x424017CCUL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP4           *((volatile unsigned int*)(0x424017D0UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP5           *((volatile unsigned int*)(0x424017D4UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP6           *((volatile unsigned int*)(0x424017D8UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP7           *((volatile unsigned int*)(0x424017DCUL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP8           *((volatile unsigned int*)(0x424017E0UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP9           *((volatile unsigned int*)(0x424017E4UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP10          *((volatile unsigned int*)(0x424017E8UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP11          *((volatile unsigned int*)(0x424017ECUL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP12          *((volatile unsigned int*)(0x424017F0UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP13          *((volatile unsigned int*)(0x424017F4UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP14          *((volatile unsigned int*)(0x424017F8UL))
#define bFM0P_MFT0_ADCMP_ACMP1_ACMP15          *((volatile unsigned int*)(0x424017FCUL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP0           *((volatile unsigned int*)(0x42401840UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP1           *((volatile unsigned int*)(0x42401844UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP2           *((volatile unsigned int*)(0x42401848UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP3           *((volatile unsigned int*)(0x4240184CUL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP4           *((volatile unsigned int*)(0x42401850UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP5           *((volatile unsigned int*)(0x42401854UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP6           *((volatile unsigned int*)(0x42401858UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP7           *((volatile unsigned int*)(0x4240185CUL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP8           *((volatile unsigned int*)(0x42401860UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP9           *((volatile unsigned int*)(0x42401864UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP10          *((volatile unsigned int*)(0x42401868UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP11          *((volatile unsigned int*)(0x4240186CUL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP12          *((volatile unsigned int*)(0x42401870UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP13          *((volatile unsigned int*)(0x42401874UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP14          *((volatile unsigned int*)(0x42401878UL))
#define bFM0P_MFT0_ADCMP_ACMP2_ACMP15          *((volatile unsigned int*)(0x4240187CUL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP0           *((volatile unsigned int*)(0x424018C0UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP1           *((volatile unsigned int*)(0x424018C4UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP2           *((volatile unsigned int*)(0x424018C8UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP3           *((volatile unsigned int*)(0x424018CCUL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP4           *((volatile unsigned int*)(0x424018D0UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP5           *((volatile unsigned int*)(0x424018D4UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP6           *((volatile unsigned int*)(0x424018D8UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP7           *((volatile unsigned int*)(0x424018DCUL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP8           *((volatile unsigned int*)(0x424018E0UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP9           *((volatile unsigned int*)(0x424018E4UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP10          *((volatile unsigned int*)(0x424018E8UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP11          *((volatile unsigned int*)(0x424018ECUL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP12          *((volatile unsigned int*)(0x424018F0UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP13          *((volatile unsigned int*)(0x424018F4UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP14          *((volatile unsigned int*)(0x424018F8UL))
#define bFM0P_MFT0_ADCMP_ACMP3_ACMP15          *((volatile unsigned int*)(0x424018FCUL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP0           *((volatile unsigned int*)(0x42401940UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP1           *((volatile unsigned int*)(0x42401944UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP2           *((volatile unsigned int*)(0x42401948UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP3           *((volatile unsigned int*)(0x4240194CUL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP4           *((volatile unsigned int*)(0x42401950UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP5           *((volatile unsigned int*)(0x42401954UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP6           *((volatile unsigned int*)(0x42401958UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP7           *((volatile unsigned int*)(0x4240195CUL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP8           *((volatile unsigned int*)(0x42401960UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP9           *((volatile unsigned int*)(0x42401964UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP10          *((volatile unsigned int*)(0x42401968UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP11          *((volatile unsigned int*)(0x4240196CUL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP12          *((volatile unsigned int*)(0x42401970UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP13          *((volatile unsigned int*)(0x42401974UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP14          *((volatile unsigned int*)(0x42401978UL))
#define bFM0P_MFT0_ADCMP_ACMP4_ACMP15          *((volatile unsigned int*)(0x4240197CUL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP0           *((volatile unsigned int*)(0x424019C0UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP1           *((volatile unsigned int*)(0x424019C4UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP2           *((volatile unsigned int*)(0x424019C8UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP3           *((volatile unsigned int*)(0x424019CCUL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP4           *((volatile unsigned int*)(0x424019D0UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP5           *((volatile unsigned int*)(0x424019D4UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP6           *((volatile unsigned int*)(0x424019D8UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP7           *((volatile unsigned int*)(0x424019DCUL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP8           *((volatile unsigned int*)(0x424019E0UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP9           *((volatile unsigned int*)(0x424019E4UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP10          *((volatile unsigned int*)(0x424019E8UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP11          *((volatile unsigned int*)(0x424019ECUL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP12          *((volatile unsigned int*)(0x424019F0UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP13          *((volatile unsigned int*)(0x424019F4UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP14          *((volatile unsigned int*)(0x424019F8UL))
#define bFM0P_MFT0_ADCMP_ACMP5_ACMP15          *((volatile unsigned int*)(0x424019FCUL))
#define bFM0P_MFT0_ADCMP_ACSA_CE00            *((volatile unsigned int*)(0x42401A00UL))
#define bFM0P_MFT0_ADCMP_ACSA_CE01            *((volatile unsigned int*)(0x42401A04UL))
#define bFM0P_MFT0_ADCMP_ACSA_CE10            *((volatile unsigned int*)(0x42401A08UL))
#define bFM0P_MFT0_ADCMP_ACSA_CE11            *((volatile unsigned int*)(0x42401A0CUL))
#define bFM0P_MFT0_ADCMP_ACSA_CE20            *((volatile unsigned int*)(0x42401A10UL))
#define bFM0P_MFT0_ADCMP_ACSA_CE21            *((volatile unsigned int*)(0x42401A14UL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL00           *((volatile unsigned int*)(0x42401A20UL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL01           *((volatile unsigned int*)(0x42401A24UL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL10           *((volatile unsigned int*)(0x42401A28UL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL11           *((volatile unsigned int*)(0x42401A2CUL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL20           *((volatile unsigned int*)(0x42401A30UL))
#define bFM0P_MFT0_ADCMP_ACSA_SEL21           *((volatile unsigned int*)(0x42401A34UL))
#define bFM0P_MFT0_ADCMP_ACSC0_BUFE0           *((volatile unsigned int*)(0x42401A80UL))
#define bFM0P_MFT0_ADCMP_ACSC0_BUFE1           *((volatile unsigned int*)(0x42401A84UL))
#define bFM0P_MFT0_ADCMP_ACSC0_ADSEL0          *((volatile unsigned int*)(0x42401A88UL))
#define bFM0P_MFT0_ADCMP_ACSC0_ADSEL1          *((volatile unsigned int*)(0x42401A8CUL))
#define bFM0P_MFT0_ADCMP_ACSC0_ADSEL2          *((volatile unsigned int*)(0x42401A90UL))
#define bFM0P_MFT0_ADCMP_ACSD0_AMOD            *((volatile unsigned int*)(0x42401AA0UL))
#define bFM0P_MFT0_ADCMP_ACSD0_OCUS            *((volatile unsigned int*)(0x42401AA4UL))
#define bFM0P_MFT0_ADCMP_ACSD0_DE              *((volatile unsigned int*)(0x42401AB0UL))
#define bFM0P_MFT0_ADCMP_ACSD0_PE              *((volatile unsigned int*)(0x42401AB4UL))
#define bFM0P_MFT0_ADCMP_ACSD0_UE              *((volatile unsigned int*)(0x42401AB8UL))
#define bFM0P_MFT0_ADCMP_ACSD0_ZE              *((volatile unsigned int*)(0x42401ABCUL))
#define bFM0P_MFT0_ADCMP_ACSC1_BUFE0           *((volatile unsigned int*)(0x42401B00UL))
#define bFM0P_MFT0_ADCMP_ACSC1_BUFE1           *((volatile unsigned int*)(0x42401B04UL))
#define bFM0P_MFT0_ADCMP_ACSC1_ADSEL0          *((volatile unsigned int*)(0x42401B08UL))
#define bFM0P_MFT0_ADCMP_ACSC1_ADSEL1          *((volatile unsigned int*)(0x42401B0CUL))
#define bFM0P_MFT0_ADCMP_ACSC1_ADSEL2          *((volatile unsigned int*)(0x42401B10UL))
#define bFM0P_MFT0_ADCMP_ACSD1_AMOD            *((volatile unsigned int*)(0x42401B20UL))
#define bFM0P_MFT0_ADCMP_ACSD1_OCUS            *((volatile unsigned int*)(0x42401B24UL))
#define bFM0P_MFT0_ADCMP_ACSD1_DE              *((volatile unsigned int*)(0x42401B30UL))
#define bFM0P_MFT0_ADCMP_ACSD1_PE              *((volatile unsigned int*)(0x42401B34UL))
#define bFM0P_MFT0_ADCMP_ACSD1_UE              *((volatile unsigned int*)(0x42401B38UL))
#define bFM0P_MFT0_ADCMP_ACSD1_ZE              *((volatile unsigned int*)(0x42401B3CUL))
#define bFM0P_MFT0_ADCMP_ACSC2_BUFE0           *((volatile unsigned int*)(0x42401B80UL))
#define bFM0P_MFT0_ADCMP_ACSC2_BUFE1           *((volatile unsigned int*)(0x42401B84UL))
#define bFM0P_MFT0_ADCMP_ACSC2_ADSEL0          *((volatile unsigned int*)(0x42401B88UL))
#define bFM0P_MFT0_ADCMP_ACSC2_ADSEL1          *((volatile unsigned int*)(0x42401B8CUL))
#define bFM0P_MFT0_ADCMP_ACSC2_ADSEL2          *((volatile unsigned int*)(0x42401B90UL))
#define bFM0P_MFT0_ADCMP_ACSD2_AMOD            *((volatile unsigned int*)(0x42401BA0UL))
#define bFM0P_MFT0_ADCMP_ACSD2_OCUS            *((volatile unsigned int*)(0x42401BA4UL))
#define bFM0P_MFT0_ADCMP_ACSD2_DE              *((volatile unsigned int*)(0x42401BB0UL))
#define bFM0P_MFT0_ADCMP_ACSD2_PE              *((volatile unsigned int*)(0x42401BB4UL))
#define bFM0P_MFT0_ADCMP_ACSD2_UE              *((volatile unsigned int*)(0x42401BB8UL))
#define bFM0P_MFT0_ADCMP_ACSD2_ZE              *((volatile unsigned int*)(0x42401BBCUL))
#define bFM0P_MFT0_ADCMP_ACSC3_BUFE0           *((volatile unsigned int*)(0x42401C00UL))
#define bFM0P_MFT0_ADCMP_ACSC3_BUFE1           *((volatile unsigned int*)(0x42401C04UL))
#define bFM0P_MFT0_ADCMP_ACSC3_ADSEL0          *((volatile unsigned int*)(0x42401C08UL))
#define bFM0P_MFT0_ADCMP_ACSC3_ADSEL1          *((volatile unsigned int*)(0x42401C0CUL))
#define bFM0P_MFT0_ADCMP_ACSC3_ADSEL2          *((volatile unsigned int*)(0x42401C10UL))
#define bFM0P_MFT0_ADCMP_ACSD3_AMOD            *((volatile unsigned int*)(0x42401C20UL))
#define bFM0P_MFT0_ADCMP_ACSD3_OCUS            *((volatile unsigned int*)(0x42401C24UL))
#define bFM0P_MFT0_ADCMP_ACSD3_DE              *((volatile unsigned int*)(0x42401C30UL))
#define bFM0P_MFT0_ADCMP_ACSD3_PE              *((volatile unsigned int*)(0x42401C34UL))
#define bFM0P_MFT0_ADCMP_ACSD3_UE              *((volatile unsigned int*)(0x42401C38UL))
#define bFM0P_MFT0_ADCMP_ACSD3_ZE              *((volatile unsigned int*)(0x42401C3CUL))
#define bFM0P_MFT0_ADCMP_ACSC4_BUFE0           *((volatile unsigned int*)(0x42401C80UL))
#define bFM0P_MFT0_ADCMP_ACSC4_BUFE1           *((volatile unsigned int*)(0x42401C84UL))
#define bFM0P_MFT0_ADCMP_ACSC4_ADSEL0          *((volatile unsigned int*)(0x42401C88UL))
#define bFM0P_MFT0_ADCMP_ACSC4_ADSEL1          *((volatile unsigned int*)(0x42401C8CUL))
#define bFM0P_MFT0_ADCMP_ACSC4_ADSEL2          *((volatile unsigned int*)(0x42401C90UL))
#define bFM0P_MFT0_ADCMP_ACSD4_AMOD            *((volatile unsigned int*)(0x42401CA0UL))
#define bFM0P_MFT0_ADCMP_ACSD4_OCUS            *((volatile unsigned int*)(0x42401CA4UL))
#define bFM0P_MFT0_ADCMP_ACSD4_DE              *((volatile unsigned int*)(0x42401CB0UL))
#define bFM0P_MFT0_ADCMP_ACSD4_PE              *((volatile unsigned int*)(0x42401CB4UL))
#define bFM0P_MFT0_ADCMP_ACSD4_UE              *((volatile unsigned int*)(0x42401CB8UL))
#define bFM0P_MFT0_ADCMP_ACSD4_ZE              *((volatile unsigned int*)(0x42401CBCUL))
#define bFM0P_MFT0_ADCMP_ACSC5_BUFE0           *((volatile unsigned int*)(0x42401D00UL))
#define bFM0P_MFT0_ADCMP_ACSC5_BUFE1           *((volatile unsigned int*)(0x42401D04UL))
#define bFM0P_MFT0_ADCMP_ACSC5_ADSEL0          *((volatile unsigned int*)(0x42401D08UL))
#define bFM0P_MFT0_ADCMP_ACSC5_ADSEL1          *((volatile unsigned int*)(0x42401D0CUL))
#define bFM0P_MFT0_ADCMP_ACSC5_ADSEL2          *((volatile unsigned int*)(0x42401D10UL))
#define bFM0P_MFT0_ADCMP_ACSD5_AMOD            *((volatile unsigned int*)(0x42401D20UL))
#define bFM0P_MFT0_ADCMP_ACSD5_OCUS            *((volatile unsigned int*)(0x42401D24UL))
#define bFM0P_MFT0_ADCMP_ACSD5_DE              *((volatile unsigned int*)(0x42401D30UL))
#define bFM0P_MFT0_ADCMP_ACSD5_PE              *((volatile unsigned int*)(0x42401D34UL))
#define bFM0P_MFT0_ADCMP_ACSD5_UE              *((volatile unsigned int*)(0x42401D38UL))
#define bFM0P_MFT0_ADCMP_ACSD5_ZE              *((volatile unsigned int*)(0x42401D3CUL))


/* Multifunction Timer PPG registers */
#define bFM0P_MFT_PPG_TTCR0_STR0               *((volatile unsigned int*)(0x42480060UL))
#define bFM0P_MFT_PPG_TTCR0_MONI0              *((volatile unsigned int*)(0x42480064UL))
#define bFM0P_MFT_PPG_TTCR0_CS00               *((volatile unsigned int*)(0x42480068UL))
#define bFM0P_MFT_PPG_TTCR0_CS01               *((volatile unsigned int*)(0x4248006CUL))
#define bFM0P_MFT_PPG_TTCR0_TRG0O              *((volatile unsigned int*)(0x42480070UL))
#define bFM0P_MFT_PPG_TTCR0_TRG2O              *((volatile unsigned int*)(0x42480074UL))
#define bFM0P_MFT_PPG_TTCR0_TRG4O              *((volatile unsigned int*)(0x42480078UL))
#define bFM0P_MFT_PPG_TTCR0_TRG6O              *((volatile unsigned int*)(0x4248007CUL))
#define bFM0P_MFT_PPG_TTCR1_STR1               *((volatile unsigned int*)(0x42480420UL))
#define bFM0P_MFT_PPG_TTCR1_MONI1              *((volatile unsigned int*)(0x42480424UL))
#define bFM0P_MFT_PPG_TTCR1_CS10               *((volatile unsigned int*)(0x42480428UL))
#define bFM0P_MFT_PPG_TTCR1_CS11               *((volatile unsigned int*)(0x4248042CUL))
#define bFM0P_MFT_PPG_TTCR1_TRG1O              *((volatile unsigned int*)(0x42480430UL))
#define bFM0P_MFT_PPG_TTCR1_TRG3O              *((volatile unsigned int*)(0x42480434UL))
#define bFM0P_MFT_PPG_TTCR1_TRG5O              *((volatile unsigned int*)(0x42480438UL))
#define bFM0P_MFT_PPG_TTCR1_TRG7O              *((volatile unsigned int*)(0x4248043CUL))
#define bFM0P_MFT_PPG_TTCR2_STR2               *((volatile unsigned int*)(0x42480820UL))
#define bFM0P_MFT_PPG_TTCR2_MONI2              *((volatile unsigned int*)(0x42480824UL))
#define bFM0P_MFT_PPG_TTCR2_CS20               *((volatile unsigned int*)(0x42480828UL))
#define bFM0P_MFT_PPG_TTCR2_CS21               *((volatile unsigned int*)(0x4248082CUL))
#define bFM0P_MFT_PPG_TTCR2_TRG16O             *((volatile unsigned int*)(0x42480830UL))
#define bFM0P_MFT_PPG_TTCR2_TRG18O             *((volatile unsigned int*)(0x42480834UL))
#define bFM0P_MFT_PPG_TTCR2_TRG20O             *((volatile unsigned int*)(0x42480838UL))
#define bFM0P_MFT_PPG_TTCR2_TRG22O             *((volatile unsigned int*)(0x4248083CUL))
#define bFM0P_MFT_PPG_TRG_PEN00                *((volatile unsigned int*)(0x42482000UL))
#define bFM0P_MFT_PPG_TRG_PEN01                *((volatile unsigned int*)(0x42482004UL))
#define bFM0P_MFT_PPG_TRG_PEN02                *((volatile unsigned int*)(0x42482008UL))
#define bFM0P_MFT_PPG_TRG_PEN03                *((volatile unsigned int*)(0x4248200CUL))
#define bFM0P_MFT_PPG_TRG_PEN04                *((volatile unsigned int*)(0x42482010UL))
#define bFM0P_MFT_PPG_TRG_PEN05                *((volatile unsigned int*)(0x42482014UL))
#define bFM0P_MFT_PPG_TRG_PEN06                *((volatile unsigned int*)(0x42482018UL))
#define bFM0P_MFT_PPG_TRG_PEN07                *((volatile unsigned int*)(0x4248201CUL))
#define bFM0P_MFT_PPG_TRG_PEN08                *((volatile unsigned int*)(0x42482020UL))
#define bFM0P_MFT_PPG_TRG_PEN09                *((volatile unsigned int*)(0x42482024UL))
#define bFM0P_MFT_PPG_TRG_PEN10                *((volatile unsigned int*)(0x42482028UL))
#define bFM0P_MFT_PPG_TRG_PEN11                *((volatile unsigned int*)(0x4248202CUL))
#define bFM0P_MFT_PPG_TRG_PEN12                *((volatile unsigned int*)(0x42482030UL))
#define bFM0P_MFT_PPG_TRG_PEN13                *((volatile unsigned int*)(0x42482034UL))
#define bFM0P_MFT_PPG_TRG_PEN14                *((volatile unsigned int*)(0x42482038UL))
#define bFM0P_MFT_PPG_TRG_PEN15                *((volatile unsigned int*)(0x4248203CUL))
#define bFM0P_MFT_PPG_REVC0_REV00              *((volatile unsigned int*)(0x42482080UL))
#define bFM0P_MFT_PPG_REVC0_REV01              *((volatile unsigned int*)(0x42482084UL))
#define bFM0P_MFT_PPG_REVC0_REV02              *((volatile unsigned int*)(0x42482088UL))
#define bFM0P_MFT_PPG_REVC0_REV03              *((volatile unsigned int*)(0x4248208CUL))
#define bFM0P_MFT_PPG_REVC0_REV04              *((volatile unsigned int*)(0x42482090UL))
#define bFM0P_MFT_PPG_REVC0_REV05              *((volatile unsigned int*)(0x42482094UL))
#define bFM0P_MFT_PPG_REVC0_REV06              *((volatile unsigned int*)(0x42482098UL))
#define bFM0P_MFT_PPG_REVC0_REV07              *((volatile unsigned int*)(0x4248209CUL))
#define bFM0P_MFT_PPG_REVC0_REV08              *((volatile unsigned int*)(0x424820A0UL))
#define bFM0P_MFT_PPG_REVC0_REV09              *((volatile unsigned int*)(0x424820A4UL))
#define bFM0P_MFT_PPG_REVC0_REV10              *((volatile unsigned int*)(0x424820A8UL))
#define bFM0P_MFT_PPG_REVC0_REV11              *((volatile unsigned int*)(0x424820ACUL))
#define bFM0P_MFT_PPG_REVC0_REV12              *((volatile unsigned int*)(0x424820B0UL))
#define bFM0P_MFT_PPG_REVC0_REV13              *((volatile unsigned int*)(0x424820B4UL))
#define bFM0P_MFT_PPG_REVC0_REV14              *((volatile unsigned int*)(0x424820B8UL))
#define bFM0P_MFT_PPG_REVC0_REV15              *((volatile unsigned int*)(0x424820BCUL))
#define bFM0P_MFT_PPG_TRG1_PEN16               *((volatile unsigned int*)(0x42482800UL))
#define bFM0P_MFT_PPG_TRG1_PEN17               *((volatile unsigned int*)(0x42482804UL))
#define bFM0P_MFT_PPG_TRG1_PEN18               *((volatile unsigned int*)(0x42482808UL))
#define bFM0P_MFT_PPG_TRG1_PEN19               *((volatile unsigned int*)(0x4248280CUL))
#define bFM0P_MFT_PPG_TRG1_PEN20               *((volatile unsigned int*)(0x42482810UL))
#define bFM0P_MFT_PPG_TRG1_PEN21               *((volatile unsigned int*)(0x42482814UL))
#define bFM0P_MFT_PPG_TRG1_PEN22               *((volatile unsigned int*)(0x42482818UL))
#define bFM0P_MFT_PPG_TRG1_PEN23               *((volatile unsigned int*)(0x4248281CUL))
#define bFM0P_MFT_PPG_REVC1_REV16              *((volatile unsigned int*)(0x42482880UL))
#define bFM0P_MFT_PPG_REVC1_REV17              *((volatile unsigned int*)(0x42482884UL))
#define bFM0P_MFT_PPG_REVC1_REV18              *((volatile unsigned int*)(0x42482888UL))
#define bFM0P_MFT_PPG_REVC1_REV19              *((volatile unsigned int*)(0x4248288CUL))
#define bFM0P_MFT_PPG_REVC1_REV20              *((volatile unsigned int*)(0x42482890UL))
#define bFM0P_MFT_PPG_REVC1_REV21              *((volatile unsigned int*)(0x42482894UL))
#define bFM0P_MFT_PPG_REVC1_REV22              *((volatile unsigned int*)(0x42482898UL))
#define bFM0P_MFT_PPG_REVC1_REV23              *((volatile unsigned int*)(0x4248289CUL))
#define bFM0P_MFT_PPG_PPGC1_TTRG               *((volatile unsigned int*)(0x42484000UL))
#define bFM0P_MFT_PPG_PPGC1_MD0                *((volatile unsigned int*)(0x42484004UL))
#define bFM0P_MFT_PPG_PPGC1_MD1                *((volatile unsigned int*)(0x42484008UL))
#define bFM0P_MFT_PPG_PPGC1_PCS0               *((volatile unsigned int*)(0x4248400CUL))
#define bFM0P_MFT_PPG_PPGC1_PCS1               *((volatile unsigned int*)(0x42484010UL))
#define bFM0P_MFT_PPG_PPGC1_INTM               *((volatile unsigned int*)(0x42484014UL))
#define bFM0P_MFT_PPG_PPGC1_PUF                *((volatile unsigned int*)(0x42484018UL))
#define bFM0P_MFT_PPG_PPGC1_PIE                *((volatile unsigned int*)(0x4248401CUL))
#define bFM0P_MFT_PPG_PPGC0_TTRG               *((volatile unsigned int*)(0x42484020UL))
#define bFM0P_MFT_PPG_PPGC0_MD0                *((volatile unsigned int*)(0x42484024UL))
#define bFM0P_MFT_PPG_PPGC0_MD1                *((volatile unsigned int*)(0x42484028UL))
#define bFM0P_MFT_PPG_PPGC0_PCS0               *((volatile unsigned int*)(0x4248402CUL))
#define bFM0P_MFT_PPG_PPGC0_PCS1               *((volatile unsigned int*)(0x42484030UL))
#define bFM0P_MFT_PPG_PPGC0_INTM               *((volatile unsigned int*)(0x42484034UL))
#define bFM0P_MFT_PPG_PPGC0_PUF                *((volatile unsigned int*)(0x42484038UL))
#define bFM0P_MFT_PPG_PPGC0_PIE                *((volatile unsigned int*)(0x4248403CUL))
#define bFM0P_MFT_PPG_PPGC3_TTRG               *((volatile unsigned int*)(0x42484080UL))
#define bFM0P_MFT_PPG_PPGC3_MD0                *((volatile unsigned int*)(0x42484084UL))
#define bFM0P_MFT_PPG_PPGC3_MD1                *((volatile unsigned int*)(0x42484088UL))
#define bFM0P_MFT_PPG_PPGC3_PCS0               *((volatile unsigned int*)(0x4248408CUL))
#define bFM0P_MFT_PPG_PPGC3_PCS1               *((volatile unsigned int*)(0x42484090UL))
#define bFM0P_MFT_PPG_PPGC3_INTM               *((volatile unsigned int*)(0x42484094UL))
#define bFM0P_MFT_PPG_PPGC3_PUF                *((volatile unsigned int*)(0x42484098UL))
#define bFM0P_MFT_PPG_PPGC3_PIE                *((volatile unsigned int*)(0x4248409CUL))
#define bFM0P_MFT_PPG_PPGC2_TTRG               *((volatile unsigned int*)(0x424840A0UL))
#define bFM0P_MFT_PPG_PPGC2_MD0                *((volatile unsigned int*)(0x424840A4UL))
#define bFM0P_MFT_PPG_PPGC2_MD1                *((volatile unsigned int*)(0x424840A8UL))
#define bFM0P_MFT_PPG_PPGC2_PCS0               *((volatile unsigned int*)(0x424840ACUL))
#define bFM0P_MFT_PPG_PPGC2_PCS1               *((volatile unsigned int*)(0x424840B0UL))
#define bFM0P_MFT_PPG_PPGC2_INTM               *((volatile unsigned int*)(0x424840B4UL))
#define bFM0P_MFT_PPG_PPGC2_PUF                *((volatile unsigned int*)(0x424840B8UL))
#define bFM0P_MFT_PPG_PPGC2_PIE                *((volatile unsigned int*)(0x424840BCUL))
#define bFM0P_MFT_PPG_PRLL0_PRLL0              *((volatile unsigned int*)(0x42484100UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL1              *((volatile unsigned int*)(0x42484104UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL2              *((volatile unsigned int*)(0x42484108UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL3              *((volatile unsigned int*)(0x4248410CUL))
#define bFM0P_MFT_PPG_PRLL0_PRLL4              *((volatile unsigned int*)(0x42484110UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL5              *((volatile unsigned int*)(0x42484114UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL6              *((volatile unsigned int*)(0x42484118UL))
#define bFM0P_MFT_PPG_PRLL0_PRLL7              *((volatile unsigned int*)(0x4248411CUL))
#define bFM0P_MFT_PPG_PRLH0_PRLH0              *((volatile unsigned int*)(0x42484120UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH1              *((volatile unsigned int*)(0x42484124UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH2              *((volatile unsigned int*)(0x42484128UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH3              *((volatile unsigned int*)(0x4248412CUL))
#define bFM0P_MFT_PPG_PRLH0_PRLH4              *((volatile unsigned int*)(0x42484130UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH5              *((volatile unsigned int*)(0x42484134UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH6              *((volatile unsigned int*)(0x42484138UL))
#define bFM0P_MFT_PPG_PRLH0_PRLH7              *((volatile unsigned int*)(0x4248413CUL))
#define bFM0P_MFT_PPG_PRLL1_PRLL0              *((volatile unsigned int*)(0x42484180UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL1              *((volatile unsigned int*)(0x42484184UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL2              *((volatile unsigned int*)(0x42484188UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL3              *((volatile unsigned int*)(0x4248418CUL))
#define bFM0P_MFT_PPG_PRLL1_PRLL4              *((volatile unsigned int*)(0x42484190UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL5              *((volatile unsigned int*)(0x42484194UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL6              *((volatile unsigned int*)(0x42484198UL))
#define bFM0P_MFT_PPG_PRLL1_PRLL7              *((volatile unsigned int*)(0x4248419CUL))
#define bFM0P_MFT_PPG_PRLH1_PRLH0              *((volatile unsigned int*)(0x424841A0UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH1              *((volatile unsigned int*)(0x424841A4UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH2              *((volatile unsigned int*)(0x424841A8UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH3              *((volatile unsigned int*)(0x424841ACUL))
#define bFM0P_MFT_PPG_PRLH1_PRLH4              *((volatile unsigned int*)(0x424841B0UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH5              *((volatile unsigned int*)(0x424841B4UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH6              *((volatile unsigned int*)(0x424841B8UL))
#define bFM0P_MFT_PPG_PRLH1_PRLH7              *((volatile unsigned int*)(0x424841BCUL))
#define bFM0P_MFT_PPG_PRLL2_PRLL0              *((volatile unsigned int*)(0x42484200UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL1              *((volatile unsigned int*)(0x42484204UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL2              *((volatile unsigned int*)(0x42484208UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL3              *((volatile unsigned int*)(0x4248420CUL))
#define bFM0P_MFT_PPG_PRLL2_PRLL4              *((volatile unsigned int*)(0x42484210UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL5              *((volatile unsigned int*)(0x42484214UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL6              *((volatile unsigned int*)(0x42484218UL))
#define bFM0P_MFT_PPG_PRLL2_PRLL7              *((volatile unsigned int*)(0x4248421CUL))
#define bFM0P_MFT_PPG_PRLH2_PRLH0              *((volatile unsigned int*)(0x42484220UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH1              *((volatile unsigned int*)(0x42484224UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH2              *((volatile unsigned int*)(0x42484228UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH3              *((volatile unsigned int*)(0x4248422CUL))
#define bFM0P_MFT_PPG_PRLH2_PRLH4              *((volatile unsigned int*)(0x42484230UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH5              *((volatile unsigned int*)(0x42484234UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH6              *((volatile unsigned int*)(0x42484238UL))
#define bFM0P_MFT_PPG_PRLH2_PRLH7              *((volatile unsigned int*)(0x4248423CUL))
#define bFM0P_MFT_PPG_PRLL3_PRLL0              *((volatile unsigned int*)(0x42484280UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL1              *((volatile unsigned int*)(0x42484284UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL2              *((volatile unsigned int*)(0x42484288UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL3              *((volatile unsigned int*)(0x4248428CUL))
#define bFM0P_MFT_PPG_PRLL3_PRLL4              *((volatile unsigned int*)(0x42484290UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL5              *((volatile unsigned int*)(0x42484294UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL6              *((volatile unsigned int*)(0x42484298UL))
#define bFM0P_MFT_PPG_PRLL3_PRLL7              *((volatile unsigned int*)(0x4248429CUL))
#define bFM0P_MFT_PPG_PRLH3_PRLH0              *((volatile unsigned int*)(0x424842A0UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH1              *((volatile unsigned int*)(0x424842A4UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH2              *((volatile unsigned int*)(0x424842A8UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH3              *((volatile unsigned int*)(0x424842ACUL))
#define bFM0P_MFT_PPG_PRLH3_PRLH4              *((volatile unsigned int*)(0x424842B0UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH5              *((volatile unsigned int*)(0x424842B4UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH6              *((volatile unsigned int*)(0x424842B8UL))
#define bFM0P_MFT_PPG_PRLH3_PRLH7              *((volatile unsigned int*)(0x424842BCUL))
#define bFM0P_MFT_PPG_GATEC0_EDGE0             *((volatile unsigned int*)(0x42484300UL))
#define bFM0P_MFT_PPG_GATEC0_STRG0             *((volatile unsigned int*)(0x42484304UL))
#define bFM0P_MFT_PPG_GATEC0_EDGE2             *((volatile unsigned int*)(0x42484310UL))
#define bFM0P_MFT_PPG_GATEC0_STRG2             *((volatile unsigned int*)(0x42484314UL))
#define bFM0P_MFT_PPG_PPGC5_TTRG               *((volatile unsigned int*)(0x42484800UL))
#define bFM0P_MFT_PPG_PPGC5_MD0                *((volatile unsigned int*)(0x42484804UL))
#define bFM0P_MFT_PPG_PPGC5_MD1                *((volatile unsigned int*)(0x42484808UL))
#define bFM0P_MFT_PPG_PPGC5_PCS0               *((volatile unsigned int*)(0x4248480CUL))
#define bFM0P_MFT_PPG_PPGC5_PCS1               *((volatile unsigned int*)(0x42484810UL))
#define bFM0P_MFT_PPG_PPGC5_INTM               *((volatile unsigned int*)(0x42484814UL))
#define bFM0P_MFT_PPG_PPGC5_PUF                *((volatile unsigned int*)(0x42484818UL))
#define bFM0P_MFT_PPG_PPGC5_PIE                *((volatile unsigned int*)(0x4248481CUL))
#define bFM0P_MFT_PPG_PPGC4_TTRG               *((volatile unsigned int*)(0x42484820UL))
#define bFM0P_MFT_PPG_PPGC4_MD0                *((volatile unsigned int*)(0x42484824UL))
#define bFM0P_MFT_PPG_PPGC4_MD1                *((volatile unsigned int*)(0x42484828UL))
#define bFM0P_MFT_PPG_PPGC4_PCS0               *((volatile unsigned int*)(0x4248482CUL))
#define bFM0P_MFT_PPG_PPGC4_PCS1               *((volatile unsigned int*)(0x42484830UL))
#define bFM0P_MFT_PPG_PPGC4_INTM               *((volatile unsigned int*)(0x42484834UL))
#define bFM0P_MFT_PPG_PPGC4_PUF                *((volatile unsigned int*)(0x42484838UL))
#define bFM0P_MFT_PPG_PPGC4_PIE                *((volatile unsigned int*)(0x4248483CUL))
#define bFM0P_MFT_PPG_PPGC7_TTRG               *((volatile unsigned int*)(0x42484880UL))
#define bFM0P_MFT_PPG_PPGC7_MD0                *((volatile unsigned int*)(0x42484884UL))
#define bFM0P_MFT_PPG_PPGC7_MD1                *((volatile unsigned int*)(0x42484888UL))
#define bFM0P_MFT_PPG_PPGC7_PCS0               *((volatile unsigned int*)(0x4248488CUL))
#define bFM0P_MFT_PPG_PPGC7_PCS1               *((volatile unsigned int*)(0x42484890UL))
#define bFM0P_MFT_PPG_PPGC7_INTM               *((volatile unsigned int*)(0x42484894UL))
#define bFM0P_MFT_PPG_PPGC7_PUF                *((volatile unsigned int*)(0x42484898UL))
#define bFM0P_MFT_PPG_PPGC7_PIE                *((volatile unsigned int*)(0x4248489CUL))
#define bFM0P_MFT_PPG_PPGC6_TTRG               *((volatile unsigned int*)(0x424848A0UL))
#define bFM0P_MFT_PPG_PPGC6_MD0                *((volatile unsigned int*)(0x424848A4UL))
#define bFM0P_MFT_PPG_PPGC6_MD1                *((volatile unsigned int*)(0x424848A8UL))
#define bFM0P_MFT_PPG_PPGC6_PCS0               *((volatile unsigned int*)(0x424848ACUL))
#define bFM0P_MFT_PPG_PPGC6_PCS1               *((volatile unsigned int*)(0x424848B0UL))
#define bFM0P_MFT_PPG_PPGC6_INTM               *((volatile unsigned int*)(0x424848B4UL))
#define bFM0P_MFT_PPG_PPGC6_PUF                *((volatile unsigned int*)(0x424848B8UL))
#define bFM0P_MFT_PPG_PPGC6_PIE                *((volatile unsigned int*)(0x424848BCUL))
#define bFM0P_MFT_PPG_PRLL4_PRLL0              *((volatile unsigned int*)(0x42484900UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL1              *((volatile unsigned int*)(0x42484904UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL2              *((volatile unsigned int*)(0x42484908UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL3              *((volatile unsigned int*)(0x4248490CUL))
#define bFM0P_MFT_PPG_PRLL4_PRLL4              *((volatile unsigned int*)(0x42484910UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL5              *((volatile unsigned int*)(0x42484914UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL6              *((volatile unsigned int*)(0x42484918UL))
#define bFM0P_MFT_PPG_PRLL4_PRLL7              *((volatile unsigned int*)(0x4248491CUL))
#define bFM0P_MFT_PPG_PRLH4_PRLH0              *((volatile unsigned int*)(0x42484920UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH1              *((volatile unsigned int*)(0x42484924UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH2              *((volatile unsigned int*)(0x42484928UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH3              *((volatile unsigned int*)(0x4248492CUL))
#define bFM0P_MFT_PPG_PRLH4_PRLH4              *((volatile unsigned int*)(0x42484930UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH5              *((volatile unsigned int*)(0x42484934UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH6              *((volatile unsigned int*)(0x42484938UL))
#define bFM0P_MFT_PPG_PRLH4_PRLH7              *((volatile unsigned int*)(0x4248493CUL))
#define bFM0P_MFT_PPG_PRLL5_PRLL0              *((volatile unsigned int*)(0x42484980UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL1              *((volatile unsigned int*)(0x42484984UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL2              *((volatile unsigned int*)(0x42484988UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL3              *((volatile unsigned int*)(0x4248498CUL))
#define bFM0P_MFT_PPG_PRLL5_PRLL4              *((volatile unsigned int*)(0x42484990UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL5              *((volatile unsigned int*)(0x42484994UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL6              *((volatile unsigned int*)(0x42484998UL))
#define bFM0P_MFT_PPG_PRLL5_PRLL7              *((volatile unsigned int*)(0x4248499CUL))
#define bFM0P_MFT_PPG_PRLH5_PRLH0              *((volatile unsigned int*)(0x424849A0UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH1              *((volatile unsigned int*)(0x424849A4UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH2              *((volatile unsigned int*)(0x424849A8UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH3              *((volatile unsigned int*)(0x424849ACUL))
#define bFM0P_MFT_PPG_PRLH5_PRLH4              *((volatile unsigned int*)(0x424849B0UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH5              *((volatile unsigned int*)(0x424849B4UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH6              *((volatile unsigned int*)(0x424849B8UL))
#define bFM0P_MFT_PPG_PRLH5_PRLH7              *((volatile unsigned int*)(0x424849BCUL))
#define bFM0P_MFT_PPG_PRLL6_PRLL0              *((volatile unsigned int*)(0x42484A00UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL1              *((volatile unsigned int*)(0x42484A04UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL2              *((volatile unsigned int*)(0x42484A08UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL3              *((volatile unsigned int*)(0x42484A0CUL))
#define bFM0P_MFT_PPG_PRLL6_PRLL4              *((volatile unsigned int*)(0x42484A10UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL5              *((volatile unsigned int*)(0x42484A14UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL6              *((volatile unsigned int*)(0x42484A18UL))
#define bFM0P_MFT_PPG_PRLL6_PRLL7              *((volatile unsigned int*)(0x42484A1CUL))
#define bFM0P_MFT_PPG_PRLH6_PRLH0              *((volatile unsigned int*)(0x42484A20UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH1              *((volatile unsigned int*)(0x42484A24UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH2              *((volatile unsigned int*)(0x42484A28UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH3              *((volatile unsigned int*)(0x42484A2CUL))
#define bFM0P_MFT_PPG_PRLH6_PRLH4              *((volatile unsigned int*)(0x42484A30UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH5              *((volatile unsigned int*)(0x42484A34UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH6              *((volatile unsigned int*)(0x42484A38UL))
#define bFM0P_MFT_PPG_PRLH6_PRLH7              *((volatile unsigned int*)(0x42484A3CUL))
#define bFM0P_MFT_PPG_PRLL7_PRLL0              *((volatile unsigned int*)(0x42484A80UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL1              *((volatile unsigned int*)(0x42484A84UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL2              *((volatile unsigned int*)(0x42484A88UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL3              *((volatile unsigned int*)(0x42484A8CUL))
#define bFM0P_MFT_PPG_PRLL7_PRLL4              *((volatile unsigned int*)(0x42484A90UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL5              *((volatile unsigned int*)(0x42484A94UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL6              *((volatile unsigned int*)(0x42484A98UL))
#define bFM0P_MFT_PPG_PRLL7_PRLL7              *((volatile unsigned int*)(0x42484A9CUL))
#define bFM0P_MFT_PPG_PRLH7_PRLH0              *((volatile unsigned int*)(0x42484AA0UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH1              *((volatile unsigned int*)(0x42484AA4UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH2              *((volatile unsigned int*)(0x42484AA8UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH3              *((volatile unsigned int*)(0x42484AACUL))
#define bFM0P_MFT_PPG_PRLH7_PRLH4              *((volatile unsigned int*)(0x42484AB0UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH5              *((volatile unsigned int*)(0x42484AB4UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH6              *((volatile unsigned int*)(0x42484AB8UL))
#define bFM0P_MFT_PPG_PRLH7_PRLH7              *((volatile unsigned int*)(0x42484ABCUL))
#define bFM0P_MFT_PPG_GATEC4_EDGE4             *((volatile unsigned int*)(0x42484B00UL))
#define bFM0P_MFT_PPG_GATEC4_STRG4             *((volatile unsigned int*)(0x42484B04UL))
#define bFM0P_MFT_PPG_GATEC4_EDGE6             *((volatile unsigned int*)(0x42484B10UL))
#define bFM0P_MFT_PPG_GATEC4_STRG6             *((volatile unsigned int*)(0x42484B14UL))
#define bFM0P_MFT_PPG_PPGC9_TTRG               *((volatile unsigned int*)(0x42485000UL))
#define bFM0P_MFT_PPG_PPGC9_MD0                *((volatile unsigned int*)(0x42485004UL))
#define bFM0P_MFT_PPG_PPGC9_MD1                *((volatile unsigned int*)(0x42485008UL))
#define bFM0P_MFT_PPG_PPGC9_PCS0               *((volatile unsigned int*)(0x4248500CUL))
#define bFM0P_MFT_PPG_PPGC9_PCS1               *((volatile unsigned int*)(0x42485010UL))
#define bFM0P_MFT_PPG_PPGC9_INTM               *((volatile unsigned int*)(0x42485014UL))
#define bFM0P_MFT_PPG_PPGC9_PUF                *((volatile unsigned int*)(0x42485018UL))
#define bFM0P_MFT_PPG_PPGC9_PIE                *((volatile unsigned int*)(0x4248501CUL))
#define bFM0P_MFT_PPG_PPGC8_TTRG               *((volatile unsigned int*)(0x42485020UL))
#define bFM0P_MFT_PPG_PPGC8_MD0                *((volatile unsigned int*)(0x42485024UL))
#define bFM0P_MFT_PPG_PPGC8_MD1                *((volatile unsigned int*)(0x42485028UL))
#define bFM0P_MFT_PPG_PPGC8_PCS0               *((volatile unsigned int*)(0x4248502CUL))
#define bFM0P_MFT_PPG_PPGC8_PCS1               *((volatile unsigned int*)(0x42485030UL))
#define bFM0P_MFT_PPG_PPGC8_INTM               *((volatile unsigned int*)(0x42485034UL))
#define bFM0P_MFT_PPG_PPGC8_PUF                *((volatile unsigned int*)(0x42485038UL))
#define bFM0P_MFT_PPG_PPGC8_PIE                *((volatile unsigned int*)(0x4248503CUL))
#define bFM0P_MFT_PPG_PPGC11_TTRG              *((volatile unsigned int*)(0x42485080UL))
#define bFM0P_MFT_PPG_PPGC11_MD0               *((volatile unsigned int*)(0x42485084UL))
#define bFM0P_MFT_PPG_PPGC11_MD1               *((volatile unsigned int*)(0x42485088UL))
#define bFM0P_MFT_PPG_PPGC11_PCS0              *((volatile unsigned int*)(0x4248508CUL))
#define bFM0P_MFT_PPG_PPGC11_PCS1              *((volatile unsigned int*)(0x42485090UL))
#define bFM0P_MFT_PPG_PPGC11_INTM              *((volatile unsigned int*)(0x42485094UL))
#define bFM0P_MFT_PPG_PPGC11_PUF               *((volatile unsigned int*)(0x42485098UL))
#define bFM0P_MFT_PPG_PPGC11_PIE               *((volatile unsigned int*)(0x4248509CUL))
#define bFM0P_MFT_PPG_PPGC10_TTRG              *((volatile unsigned int*)(0x424850A0UL))
#define bFM0P_MFT_PPG_PPGC10_MD0               *((volatile unsigned int*)(0x424850A4UL))
#define bFM0P_MFT_PPG_PPGC10_MD1               *((volatile unsigned int*)(0x424850A8UL))
#define bFM0P_MFT_PPG_PPGC10_PCS0              *((volatile unsigned int*)(0x424850ACUL))
#define bFM0P_MFT_PPG_PPGC10_PCS1              *((volatile unsigned int*)(0x424850B0UL))
#define bFM0P_MFT_PPG_PPGC10_INTM              *((volatile unsigned int*)(0x424850B4UL))
#define bFM0P_MFT_PPG_PPGC10_PUF               *((volatile unsigned int*)(0x424850B8UL))
#define bFM0P_MFT_PPG_PPGC10_PIE               *((volatile unsigned int*)(0x424850BCUL))
#define bFM0P_MFT_PPG_PRLL8_PRLL0              *((volatile unsigned int*)(0x42485100UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL1              *((volatile unsigned int*)(0x42485104UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL2              *((volatile unsigned int*)(0x42485108UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL3              *((volatile unsigned int*)(0x4248510CUL))
#define bFM0P_MFT_PPG_PRLL8_PRLL4              *((volatile unsigned int*)(0x42485110UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL5              *((volatile unsigned int*)(0x42485114UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL6              *((volatile unsigned int*)(0x42485118UL))
#define bFM0P_MFT_PPG_PRLL8_PRLL7              *((volatile unsigned int*)(0x4248511CUL))
#define bFM0P_MFT_PPG_PRLH8_PRLH0              *((volatile unsigned int*)(0x42485120UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH1              *((volatile unsigned int*)(0x42485124UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH2              *((volatile unsigned int*)(0x42485128UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH3              *((volatile unsigned int*)(0x4248512CUL))
#define bFM0P_MFT_PPG_PRLH8_PRLH4              *((volatile unsigned int*)(0x42485130UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH5              *((volatile unsigned int*)(0x42485134UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH6              *((volatile unsigned int*)(0x42485138UL))
#define bFM0P_MFT_PPG_PRLH8_PRLH7              *((volatile unsigned int*)(0x4248513CUL))
#define bFM0P_MFT_PPG_PRLL9_PRLL0              *((volatile unsigned int*)(0x42485180UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL1              *((volatile unsigned int*)(0x42485184UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL2              *((volatile unsigned int*)(0x42485188UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL3              *((volatile unsigned int*)(0x4248518CUL))
#define bFM0P_MFT_PPG_PRLL9_PRLL4              *((volatile unsigned int*)(0x42485190UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL5              *((volatile unsigned int*)(0x42485194UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL6              *((volatile unsigned int*)(0x42485198UL))
#define bFM0P_MFT_PPG_PRLL9_PRLL7              *((volatile unsigned int*)(0x4248519CUL))
#define bFM0P_MFT_PPG_PRLH9_PRLH0              *((volatile unsigned int*)(0x424851A0UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH1              *((volatile unsigned int*)(0x424851A4UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH2              *((volatile unsigned int*)(0x424851A8UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH3              *((volatile unsigned int*)(0x424851ACUL))
#define bFM0P_MFT_PPG_PRLH9_PRLH4              *((volatile unsigned int*)(0x424851B0UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH5              *((volatile unsigned int*)(0x424851B4UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH6              *((volatile unsigned int*)(0x424851B8UL))
#define bFM0P_MFT_PPG_PRLH9_PRLH7              *((volatile unsigned int*)(0x424851BCUL))
#define bFM0P_MFT_PPG_PRLL10_PRLL0             *((volatile unsigned int*)(0x42485200UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL1             *((volatile unsigned int*)(0x42485204UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL2             *((volatile unsigned int*)(0x42485208UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL3             *((volatile unsigned int*)(0x4248520CUL))
#define bFM0P_MFT_PPG_PRLL10_PRLL4             *((volatile unsigned int*)(0x42485210UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL5             *((volatile unsigned int*)(0x42485214UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL6             *((volatile unsigned int*)(0x42485218UL))
#define bFM0P_MFT_PPG_PRLL10_PRLL7             *((volatile unsigned int*)(0x4248521CUL))
#define bFM0P_MFT_PPG_PRLH10_PRLH0             *((volatile unsigned int*)(0x42485220UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH1             *((volatile unsigned int*)(0x42485224UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH2             *((volatile unsigned int*)(0x42485228UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH3             *((volatile unsigned int*)(0x4248522CUL))
#define bFM0P_MFT_PPG_PRLH10_PRLH4             *((volatile unsigned int*)(0x42485230UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH5             *((volatile unsigned int*)(0x42485234UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH6             *((volatile unsigned int*)(0x42485238UL))
#define bFM0P_MFT_PPG_PRLH10_PRLH7             *((volatile unsigned int*)(0x4248523CUL))
#define bFM0P_MFT_PPG_PRLL11_PRLL0             *((volatile unsigned int*)(0x42485280UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL1             *((volatile unsigned int*)(0x42485284UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL2             *((volatile unsigned int*)(0x42485288UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL3             *((volatile unsigned int*)(0x4248528CUL))
#define bFM0P_MFT_PPG_PRLL11_PRLL4             *((volatile unsigned int*)(0x42485290UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL5             *((volatile unsigned int*)(0x42485294UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL6             *((volatile unsigned int*)(0x42485298UL))
#define bFM0P_MFT_PPG_PRLL11_PRLL7             *((volatile unsigned int*)(0x4248529CUL))
#define bFM0P_MFT_PPG_PRLH11_PRLH0             *((volatile unsigned int*)(0x424852A0UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH1             *((volatile unsigned int*)(0x424852A4UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH2             *((volatile unsigned int*)(0x424852A8UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH3             *((volatile unsigned int*)(0x424852ACUL))
#define bFM0P_MFT_PPG_PRLH11_PRLH4             *((volatile unsigned int*)(0x424852B0UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH5             *((volatile unsigned int*)(0x424852B4UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH6             *((volatile unsigned int*)(0x424852B8UL))
#define bFM0P_MFT_PPG_PRLH11_PRLH7             *((volatile unsigned int*)(0x424852BCUL))
#define bFM0P_MFT_PPG_GATEC8_EDGE8             *((volatile unsigned int*)(0x42485300UL))
#define bFM0P_MFT_PPG_GATEC8_STRG8             *((volatile unsigned int*)(0x42485304UL))
#define bFM0P_MFT_PPG_GATEC8_EDGE10            *((volatile unsigned int*)(0x42485310UL))
#define bFM0P_MFT_PPG_GATEC8_STRG10            *((volatile unsigned int*)(0x42485314UL))
#define bFM0P_MFT_PPG_PPGC13_TTRG              *((volatile unsigned int*)(0x42485800UL))
#define bFM0P_MFT_PPG_PPGC13_MD0               *((volatile unsigned int*)(0x42485804UL))
#define bFM0P_MFT_PPG_PPGC13_MD1               *((volatile unsigned int*)(0x42485808UL))
#define bFM0P_MFT_PPG_PPGC13_PCS0              *((volatile unsigned int*)(0x4248580CUL))
#define bFM0P_MFT_PPG_PPGC13_PCS1              *((volatile unsigned int*)(0x42485810UL))
#define bFM0P_MFT_PPG_PPGC13_INTM              *((volatile unsigned int*)(0x42485814UL))
#define bFM0P_MFT_PPG_PPGC13_PUF               *((volatile unsigned int*)(0x42485818UL))
#define bFM0P_MFT_PPG_PPGC13_PIE               *((volatile unsigned int*)(0x4248581CUL))
#define bFM0P_MFT_PPG_PPGC12_TTRG              *((volatile unsigned int*)(0x42485820UL))
#define bFM0P_MFT_PPG_PPGC12_MD0               *((volatile unsigned int*)(0x42485824UL))
#define bFM0P_MFT_PPG_PPGC12_MD1               *((volatile unsigned int*)(0x42485828UL))
#define bFM0P_MFT_PPG_PPGC12_PCS0              *((volatile unsigned int*)(0x4248582CUL))
#define bFM0P_MFT_PPG_PPGC12_PCS1              *((volatile unsigned int*)(0x42485830UL))
#define bFM0P_MFT_PPG_PPGC12_INTM              *((volatile unsigned int*)(0x42485834UL))
#define bFM0P_MFT_PPG_PPGC12_PUF               *((volatile unsigned int*)(0x42485838UL))
#define bFM0P_MFT_PPG_PPGC12_PIE               *((volatile unsigned int*)(0x4248583CUL))
#define bFM0P_MFT_PPG_PPGC15_TTRG              *((volatile unsigned int*)(0x42485880UL))
#define bFM0P_MFT_PPG_PPGC15_MD0               *((volatile unsigned int*)(0x42485884UL))
#define bFM0P_MFT_PPG_PPGC15_MD1               *((volatile unsigned int*)(0x42485888UL))
#define bFM0P_MFT_PPG_PPGC15_PCS0              *((volatile unsigned int*)(0x4248588CUL))
#define bFM0P_MFT_PPG_PPGC15_PCS1              *((volatile unsigned int*)(0x42485890UL))
#define bFM0P_MFT_PPG_PPGC15_INTM              *((volatile unsigned int*)(0x42485894UL))
#define bFM0P_MFT_PPG_PPGC15_PUF               *((volatile unsigned int*)(0x42485898UL))
#define bFM0P_MFT_PPG_PPGC15_PIE               *((volatile unsigned int*)(0x4248589CUL))
#define bFM0P_MFT_PPG_PPGC14_TTRG              *((volatile unsigned int*)(0x424858A0UL))
#define bFM0P_MFT_PPG_PPGC14_MD0               *((volatile unsigned int*)(0x424858A4UL))
#define bFM0P_MFT_PPG_PPGC14_MD1               *((volatile unsigned int*)(0x424858A8UL))
#define bFM0P_MFT_PPG_PPGC14_PCS0              *((volatile unsigned int*)(0x424858ACUL))
#define bFM0P_MFT_PPG_PPGC14_PCS1              *((volatile unsigned int*)(0x424858B0UL))
#define bFM0P_MFT_PPG_PPGC14_INTM              *((volatile unsigned int*)(0x424858B4UL))
#define bFM0P_MFT_PPG_PPGC14_PUF               *((volatile unsigned int*)(0x424858B8UL))
#define bFM0P_MFT_PPG_PPGC14_PIE               *((volatile unsigned int*)(0x424858BCUL))
#define bFM0P_MFT_PPG_PRLL12_PRLL0             *((volatile unsigned int*)(0x42485900UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL1             *((volatile unsigned int*)(0x42485904UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL2             *((volatile unsigned int*)(0x42485908UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL3             *((volatile unsigned int*)(0x4248590CUL))
#define bFM0P_MFT_PPG_PRLL12_PRLL4             *((volatile unsigned int*)(0x42485910UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL5             *((volatile unsigned int*)(0x42485914UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL6             *((volatile unsigned int*)(0x42485918UL))
#define bFM0P_MFT_PPG_PRLL12_PRLL7             *((volatile unsigned int*)(0x4248591CUL))
#define bFM0P_MFT_PPG_PRLH12_PRLH0             *((volatile unsigned int*)(0x42485920UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH1             *((volatile unsigned int*)(0x42485924UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH2             *((volatile unsigned int*)(0x42485928UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH3             *((volatile unsigned int*)(0x4248592CUL))
#define bFM0P_MFT_PPG_PRLH12_PRLH4             *((volatile unsigned int*)(0x42485930UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH5             *((volatile unsigned int*)(0x42485934UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH6             *((volatile unsigned int*)(0x42485938UL))
#define bFM0P_MFT_PPG_PRLH12_PRLH7             *((volatile unsigned int*)(0x4248593CUL))
#define bFM0P_MFT_PPG_PRLL13_PRLL0             *((volatile unsigned int*)(0x42485980UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL1             *((volatile unsigned int*)(0x42485984UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL2             *((volatile unsigned int*)(0x42485988UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL3             *((volatile unsigned int*)(0x4248598CUL))
#define bFM0P_MFT_PPG_PRLL13_PRLL4             *((volatile unsigned int*)(0x42485990UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL5             *((volatile unsigned int*)(0x42485994UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL6             *((volatile unsigned int*)(0x42485998UL))
#define bFM0P_MFT_PPG_PRLL13_PRLL7             *((volatile unsigned int*)(0x4248599CUL))
#define bFM0P_MFT_PPG_PRLH13_PRLH0             *((volatile unsigned int*)(0x424859A0UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH1             *((volatile unsigned int*)(0x424859A4UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH2             *((volatile unsigned int*)(0x424859A8UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH3             *((volatile unsigned int*)(0x424859ACUL))
#define bFM0P_MFT_PPG_PRLH13_PRLH4             *((volatile unsigned int*)(0x424859B0UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH5             *((volatile unsigned int*)(0x424859B4UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH6             *((volatile unsigned int*)(0x424859B8UL))
#define bFM0P_MFT_PPG_PRLH13_PRLH7             *((volatile unsigned int*)(0x424859BCUL))
#define bFM0P_MFT_PPG_PRLL14_PRLL0             *((volatile unsigned int*)(0x42485A00UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL1             *((volatile unsigned int*)(0x42485A04UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL2             *((volatile unsigned int*)(0x42485A08UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL3             *((volatile unsigned int*)(0x42485A0CUL))
#define bFM0P_MFT_PPG_PRLL14_PRLL4             *((volatile unsigned int*)(0x42485A10UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL5             *((volatile unsigned int*)(0x42485A14UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL6             *((volatile unsigned int*)(0x42485A18UL))
#define bFM0P_MFT_PPG_PRLL14_PRLL7             *((volatile unsigned int*)(0x42485A1CUL))
#define bFM0P_MFT_PPG_PRLH14_PRLH0             *((volatile unsigned int*)(0x42485A20UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH1             *((volatile unsigned int*)(0x42485A24UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH2             *((volatile unsigned int*)(0x42485A28UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH3             *((volatile unsigned int*)(0x42485A2CUL))
#define bFM0P_MFT_PPG_PRLH14_PRLH4             *((volatile unsigned int*)(0x42485A30UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH5             *((volatile unsigned int*)(0x42485A34UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH6             *((volatile unsigned int*)(0x42485A38UL))
#define bFM0P_MFT_PPG_PRLH14_PRLH7             *((volatile unsigned int*)(0x42485A3CUL))
#define bFM0P_MFT_PPG_PRLL15_PRLL0             *((volatile unsigned int*)(0x42485A80UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL1             *((volatile unsigned int*)(0x42485A84UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL2             *((volatile unsigned int*)(0x42485A88UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL3             *((volatile unsigned int*)(0x42485A8CUL))
#define bFM0P_MFT_PPG_PRLL15_PRLL4             *((volatile unsigned int*)(0x42485A90UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL5             *((volatile unsigned int*)(0x42485A94UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL6             *((volatile unsigned int*)(0x42485A98UL))
#define bFM0P_MFT_PPG_PRLL15_PRLL7             *((volatile unsigned int*)(0x42485A9CUL))
#define bFM0P_MFT_PPG_PRLH15_PRLH0             *((volatile unsigned int*)(0x42485AA0UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH1             *((volatile unsigned int*)(0x42485AA4UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH2             *((volatile unsigned int*)(0x42485AA8UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH3             *((volatile unsigned int*)(0x42485AACUL))
#define bFM0P_MFT_PPG_PRLH15_PRLH4             *((volatile unsigned int*)(0x42485AB0UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH5             *((volatile unsigned int*)(0x42485AB4UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH6             *((volatile unsigned int*)(0x42485AB8UL))
#define bFM0P_MFT_PPG_PRLH15_PRLH7             *((volatile unsigned int*)(0x42485ABCUL))
#define bFM0P_MFT_PPG_GATEC12_EDGE12           *((volatile unsigned int*)(0x42485B00UL))
#define bFM0P_MFT_PPG_GATEC12_STRG12           *((volatile unsigned int*)(0x42485B04UL))
#define bFM0P_MFT_PPG_GATEC12_EDGE14           *((volatile unsigned int*)(0x42485B10UL))
#define bFM0P_MFT_PPG_GATEC12_STRG14           *((volatile unsigned int*)(0x42485B14UL))
#define bFM0P_MFT_PPG_PPGC17_TTRG              *((volatile unsigned int*)(0x42486000UL))
#define bFM0P_MFT_PPG_PPGC17_MD0               *((volatile unsigned int*)(0x42486004UL))
#define bFM0P_MFT_PPG_PPGC17_MD1               *((volatile unsigned int*)(0x42486008UL))
#define bFM0P_MFT_PPG_PPGC17_PCS0              *((volatile unsigned int*)(0x4248600CUL))
#define bFM0P_MFT_PPG_PPGC17_PCS1              *((volatile unsigned int*)(0x42486010UL))
#define bFM0P_MFT_PPG_PPGC17_INTM              *((volatile unsigned int*)(0x42486014UL))
#define bFM0P_MFT_PPG_PPGC17_PUF               *((volatile unsigned int*)(0x42486018UL))
#define bFM0P_MFT_PPG_PPGC17_PIE               *((volatile unsigned int*)(0x4248601CUL))
#define bFM0P_MFT_PPG_PPGC16_TTRG              *((volatile unsigned int*)(0x42486020UL))
#define bFM0P_MFT_PPG_PPGC16_MD0               *((volatile unsigned int*)(0x42486024UL))
#define bFM0P_MFT_PPG_PPGC16_MD1               *((volatile unsigned int*)(0x42486028UL))
#define bFM0P_MFT_PPG_PPGC16_PCS0              *((volatile unsigned int*)(0x4248602CUL))
#define bFM0P_MFT_PPG_PPGC16_PCS1              *((volatile unsigned int*)(0x42486030UL))
#define bFM0P_MFT_PPG_PPGC16_INTM              *((volatile unsigned int*)(0x42486034UL))
#define bFM0P_MFT_PPG_PPGC16_PUF               *((volatile unsigned int*)(0x42486038UL))
#define bFM0P_MFT_PPG_PPGC16_PIE               *((volatile unsigned int*)(0x4248603CUL))
#define bFM0P_MFT_PPG_PPGC19_TTRG              *((volatile unsigned int*)(0x42486080UL))
#define bFM0P_MFT_PPG_PPGC19_MD0               *((volatile unsigned int*)(0x42486084UL))
#define bFM0P_MFT_PPG_PPGC19_MD1               *((volatile unsigned int*)(0x42486088UL))
#define bFM0P_MFT_PPG_PPGC19_PCS0              *((volatile unsigned int*)(0x4248608CUL))
#define bFM0P_MFT_PPG_PPGC19_PCS1              *((volatile unsigned int*)(0x42486090UL))
#define bFM0P_MFT_PPG_PPGC19_INTM              *((volatile unsigned int*)(0x42486094UL))
#define bFM0P_MFT_PPG_PPGC19_PUF               *((volatile unsigned int*)(0x42486098UL))
#define bFM0P_MFT_PPG_PPGC19_PIE               *((volatile unsigned int*)(0x4248609CUL))
#define bFM0P_MFT_PPG_PPGC18_TTRG              *((volatile unsigned int*)(0x424860A0UL))
#define bFM0P_MFT_PPG_PPGC18_MD0               *((volatile unsigned int*)(0x424860A4UL))
#define bFM0P_MFT_PPG_PPGC18_MD1               *((volatile unsigned int*)(0x424860A8UL))
#define bFM0P_MFT_PPG_PPGC18_PCS0              *((volatile unsigned int*)(0x424860ACUL))
#define bFM0P_MFT_PPG_PPGC18_PCS1              *((volatile unsigned int*)(0x424860B0UL))
#define bFM0P_MFT_PPG_PPGC18_INTM              *((volatile unsigned int*)(0x424860B4UL))
#define bFM0P_MFT_PPG_PPGC18_PUF               *((volatile unsigned int*)(0x424860B8UL))
#define bFM0P_MFT_PPG_PPGC18_PIE               *((volatile unsigned int*)(0x424860BCUL))
#define bFM0P_MFT_PPG_PRLL16_PRLL0             *((volatile unsigned int*)(0x42486100UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL1             *((volatile unsigned int*)(0x42486104UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL2             *((volatile unsigned int*)(0x42486108UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL3             *((volatile unsigned int*)(0x4248610CUL))
#define bFM0P_MFT_PPG_PRLL16_PRLL4             *((volatile unsigned int*)(0x42486110UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL5             *((volatile unsigned int*)(0x42486114UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL6             *((volatile unsigned int*)(0x42486118UL))
#define bFM0P_MFT_PPG_PRLL16_PRLL7             *((volatile unsigned int*)(0x4248611CUL))
#define bFM0P_MFT_PPG_PRLH16_PRLH0             *((volatile unsigned int*)(0x42486120UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH1             *((volatile unsigned int*)(0x42486124UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH2             *((volatile unsigned int*)(0x42486128UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH3             *((volatile unsigned int*)(0x4248612CUL))
#define bFM0P_MFT_PPG_PRLH16_PRLH4             *((volatile unsigned int*)(0x42486130UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH5             *((volatile unsigned int*)(0x42486134UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH6             *((volatile unsigned int*)(0x42486138UL))
#define bFM0P_MFT_PPG_PRLH16_PRLH7             *((volatile unsigned int*)(0x4248613CUL))
#define bFM0P_MFT_PPG_PRLL17_PRLL0             *((volatile unsigned int*)(0x42486180UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL1             *((volatile unsigned int*)(0x42486184UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL2             *((volatile unsigned int*)(0x42486188UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL3             *((volatile unsigned int*)(0x4248618CUL))
#define bFM0P_MFT_PPG_PRLL17_PRLL4             *((volatile unsigned int*)(0x42486190UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL5             *((volatile unsigned int*)(0x42486194UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL6             *((volatile unsigned int*)(0x42486198UL))
#define bFM0P_MFT_PPG_PRLL17_PRLL7             *((volatile unsigned int*)(0x4248619CUL))
#define bFM0P_MFT_PPG_PRLH17_PRLH0             *((volatile unsigned int*)(0x424861A0UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH1             *((volatile unsigned int*)(0x424861A4UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH2             *((volatile unsigned int*)(0x424861A8UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH3             *((volatile unsigned int*)(0x424861ACUL))
#define bFM0P_MFT_PPG_PRLH17_PRLH4             *((volatile unsigned int*)(0x424861B0UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH5             *((volatile unsigned int*)(0x424861B4UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH6             *((volatile unsigned int*)(0x424861B8UL))
#define bFM0P_MFT_PPG_PRLH17_PRLH7             *((volatile unsigned int*)(0x424861BCUL))
#define bFM0P_MFT_PPG_PRLL18_PRLL0             *((volatile unsigned int*)(0x42486200UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL1             *((volatile unsigned int*)(0x42486204UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL2             *((volatile unsigned int*)(0x42486208UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL3             *((volatile unsigned int*)(0x4248620CUL))
#define bFM0P_MFT_PPG_PRLL18_PRLL4             *((volatile unsigned int*)(0x42486210UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL5             *((volatile unsigned int*)(0x42486214UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL6             *((volatile unsigned int*)(0x42486218UL))
#define bFM0P_MFT_PPG_PRLL18_PRLL7             *((volatile unsigned int*)(0x4248621CUL))
#define bFM0P_MFT_PPG_PRLH18_PRLH0             *((volatile unsigned int*)(0x42486220UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH1             *((volatile unsigned int*)(0x42486224UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH2             *((volatile unsigned int*)(0x42486228UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH3             *((volatile unsigned int*)(0x4248622CUL))
#define bFM0P_MFT_PPG_PRLH18_PRLH4             *((volatile unsigned int*)(0x42486230UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH5             *((volatile unsigned int*)(0x42486234UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH6             *((volatile unsigned int*)(0x42486238UL))
#define bFM0P_MFT_PPG_PRLH18_PRLH7             *((volatile unsigned int*)(0x4248623CUL))
#define bFM0P_MFT_PPG_PRLL19_PRLL0             *((volatile unsigned int*)(0x42486280UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL1             *((volatile unsigned int*)(0x42486284UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL2             *((volatile unsigned int*)(0x42486288UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL3             *((volatile unsigned int*)(0x4248628CUL))
#define bFM0P_MFT_PPG_PRLL19_PRLL4             *((volatile unsigned int*)(0x42486290UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL5             *((volatile unsigned int*)(0x42486294UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL6             *((volatile unsigned int*)(0x42486298UL))
#define bFM0P_MFT_PPG_PRLL19_PRLL7             *((volatile unsigned int*)(0x4248629CUL))
#define bFM0P_MFT_PPG_PRLH19_PRLH0             *((volatile unsigned int*)(0x424862A0UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH1             *((volatile unsigned int*)(0x424862A4UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH2             *((volatile unsigned int*)(0x424862A8UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH3             *((volatile unsigned int*)(0x424862ACUL))
#define bFM0P_MFT_PPG_PRLH19_PRLH4             *((volatile unsigned int*)(0x424862B0UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH5             *((volatile unsigned int*)(0x424862B4UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH6             *((volatile unsigned int*)(0x424862B8UL))
#define bFM0P_MFT_PPG_PRLH19_PRLH7             *((volatile unsigned int*)(0x424862BCUL))
#define bFM0P_MFT_PPG_GATEC16_EDGE16           *((volatile unsigned int*)(0x42486300UL))
#define bFM0P_MFT_PPG_GATEC16_STRG16           *((volatile unsigned int*)(0x42486304UL))
#define bFM0P_MFT_PPG_GATEC16_EDGE18           *((volatile unsigned int*)(0x42486310UL))
#define bFM0P_MFT_PPG_GATEC16_STRG18           *((volatile unsigned int*)(0x42486314UL))
#define bFM0P_MFT_PPG_PPGC21_TTRG              *((volatile unsigned int*)(0x42486800UL))
#define bFM0P_MFT_PPG_PPGC21_MD0               *((volatile unsigned int*)(0x42486804UL))
#define bFM0P_MFT_PPG_PPGC21_MD1               *((volatile unsigned int*)(0x42486808UL))
#define bFM0P_MFT_PPG_PPGC21_PCS0              *((volatile unsigned int*)(0x4248680CUL))
#define bFM0P_MFT_PPG_PPGC21_PCS1              *((volatile unsigned int*)(0x42486810UL))
#define bFM0P_MFT_PPG_PPGC21_INTM              *((volatile unsigned int*)(0x42486814UL))
#define bFM0P_MFT_PPG_PPGC21_PUF               *((volatile unsigned int*)(0x42486818UL))
#define bFM0P_MFT_PPG_PPGC21_PIE               *((volatile unsigned int*)(0x4248681CUL))
#define bFM0P_MFT_PPG_PPGC20_TTRG              *((volatile unsigned int*)(0x42486820UL))
#define bFM0P_MFT_PPG_PPGC20_MD0               *((volatile unsigned int*)(0x42486824UL))
#define bFM0P_MFT_PPG_PPGC20_MD1               *((volatile unsigned int*)(0x42486828UL))
#define bFM0P_MFT_PPG_PPGC20_PCS0              *((volatile unsigned int*)(0x4248682CUL))
#define bFM0P_MFT_PPG_PPGC20_PCS1              *((volatile unsigned int*)(0x42486830UL))
#define bFM0P_MFT_PPG_PPGC20_INTM              *((volatile unsigned int*)(0x42486834UL))
#define bFM0P_MFT_PPG_PPGC20_PUF               *((volatile unsigned int*)(0x42486838UL))
#define bFM0P_MFT_PPG_PPGC20_PIE               *((volatile unsigned int*)(0x4248683CUL))
#define bFM0P_MFT_PPG_PPGC23_TTRG              *((volatile unsigned int*)(0x42486880UL))
#define bFM0P_MFT_PPG_PPGC23_MD0               *((volatile unsigned int*)(0x42486884UL))
#define bFM0P_MFT_PPG_PPGC23_MD1               *((volatile unsigned int*)(0x42486888UL))
#define bFM0P_MFT_PPG_PPGC23_PCS0              *((volatile unsigned int*)(0x4248688CUL))
#define bFM0P_MFT_PPG_PPGC23_PCS1              *((volatile unsigned int*)(0x42486890UL))
#define bFM0P_MFT_PPG_PPGC23_INTM              *((volatile unsigned int*)(0x42486894UL))
#define bFM0P_MFT_PPG_PPGC23_PUF               *((volatile unsigned int*)(0x42486898UL))
#define bFM0P_MFT_PPG_PPGC23_PIE               *((volatile unsigned int*)(0x4248689CUL))
#define bFM0P_MFT_PPG_PPGC22_TTRG              *((volatile unsigned int*)(0x424868A0UL))
#define bFM0P_MFT_PPG_PPGC22_MD0               *((volatile unsigned int*)(0x424868A4UL))
#define bFM0P_MFT_PPG_PPGC22_MD1               *((volatile unsigned int*)(0x424868A8UL))
#define bFM0P_MFT_PPG_PPGC22_PCS0              *((volatile unsigned int*)(0x424868ACUL))
#define bFM0P_MFT_PPG_PPGC22_PCS1              *((volatile unsigned int*)(0x424868B0UL))
#define bFM0P_MFT_PPG_PPGC22_INTM              *((volatile unsigned int*)(0x424868B4UL))
#define bFM0P_MFT_PPG_PPGC22_PUF               *((volatile unsigned int*)(0x424868B8UL))
#define bFM0P_MFT_PPG_PPGC22_PIE               *((volatile unsigned int*)(0x424868BCUL))
#define bFM0P_MFT_PPG_PRLL20_PRLL0             *((volatile unsigned int*)(0x42486900UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL1             *((volatile unsigned int*)(0x42486904UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL2             *((volatile unsigned int*)(0x42486908UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL3             *((volatile unsigned int*)(0x4248690CUL))
#define bFM0P_MFT_PPG_PRLL20_PRLL4             *((volatile unsigned int*)(0x42486910UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL5             *((volatile unsigned int*)(0x42486914UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL6             *((volatile unsigned int*)(0x42486918UL))
#define bFM0P_MFT_PPG_PRLL20_PRLL7             *((volatile unsigned int*)(0x4248691CUL))
#define bFM0P_MFT_PPG_PRLH20_PRLH0             *((volatile unsigned int*)(0x42486920UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH1             *((volatile unsigned int*)(0x42486924UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH2             *((volatile unsigned int*)(0x42486928UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH3             *((volatile unsigned int*)(0x4248692CUL))
#define bFM0P_MFT_PPG_PRLH20_PRLH4             *((volatile unsigned int*)(0x42486930UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH5             *((volatile unsigned int*)(0x42486934UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH6             *((volatile unsigned int*)(0x42486938UL))
#define bFM0P_MFT_PPG_PRLH20_PRLH7             *((volatile unsigned int*)(0x4248693CUL))
#define bFM0P_MFT_PPG_PRLL21_PRLL0             *((volatile unsigned int*)(0x42486980UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL1             *((volatile unsigned int*)(0x42486984UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL2             *((volatile unsigned int*)(0x42486988UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL3             *((volatile unsigned int*)(0x4248698CUL))
#define bFM0P_MFT_PPG_PRLL21_PRLL4             *((volatile unsigned int*)(0x42486990UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL5             *((volatile unsigned int*)(0x42486994UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL6             *((volatile unsigned int*)(0x42486998UL))
#define bFM0P_MFT_PPG_PRLL21_PRLL7             *((volatile unsigned int*)(0x4248699CUL))
#define bFM0P_MFT_PPG_PRLH21_PRLH0             *((volatile unsigned int*)(0x424869A0UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH1             *((volatile unsigned int*)(0x424869A4UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH2             *((volatile unsigned int*)(0x424869A8UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH3             *((volatile unsigned int*)(0x424869ACUL))
#define bFM0P_MFT_PPG_PRLH21_PRLH4             *((volatile unsigned int*)(0x424869B0UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH5             *((volatile unsigned int*)(0x424869B4UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH6             *((volatile unsigned int*)(0x424869B8UL))
#define bFM0P_MFT_PPG_PRLH21_PRLH7             *((volatile unsigned int*)(0x424869BCUL))
#define bFM0P_MFT_PPG_PRLL22_PRLL0             *((volatile unsigned int*)(0x42486A00UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL1             *((volatile unsigned int*)(0x42486A04UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL2             *((volatile unsigned int*)(0x42486A08UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL3             *((volatile unsigned int*)(0x42486A0CUL))
#define bFM0P_MFT_PPG_PRLL22_PRLL4             *((volatile unsigned int*)(0x42486A10UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL5             *((volatile unsigned int*)(0x42486A14UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL6             *((volatile unsigned int*)(0x42486A18UL))
#define bFM0P_MFT_PPG_PRLL22_PRLL7             *((volatile unsigned int*)(0x42486A1CUL))
#define bFM0P_MFT_PPG_PRLH22_PRLH0             *((volatile unsigned int*)(0x42486A20UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH1             *((volatile unsigned int*)(0x42486A24UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH2             *((volatile unsigned int*)(0x42486A28UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH3             *((volatile unsigned int*)(0x42486A2CUL))
#define bFM0P_MFT_PPG_PRLH22_PRLH4             *((volatile unsigned int*)(0x42486A30UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH5             *((volatile unsigned int*)(0x42486A34UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH6             *((volatile unsigned int*)(0x42486A38UL))
#define bFM0P_MFT_PPG_PRLH22_PRLH7             *((volatile unsigned int*)(0x42486A3CUL))
#define bFM0P_MFT_PPG_PRLL23_PRLL0             *((volatile unsigned int*)(0x42486A80UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL1             *((volatile unsigned int*)(0x42486A84UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL2             *((volatile unsigned int*)(0x42486A88UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL3             *((volatile unsigned int*)(0x42486A8CUL))
#define bFM0P_MFT_PPG_PRLL23_PRLL4             *((volatile unsigned int*)(0x42486A90UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL5             *((volatile unsigned int*)(0x42486A94UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL6             *((volatile unsigned int*)(0x42486A98UL))
#define bFM0P_MFT_PPG_PRLL23_PRLL7             *((volatile unsigned int*)(0x42486A9CUL))
#define bFM0P_MFT_PPG_PRLH23_PRLH0             *((volatile unsigned int*)(0x42486AA0UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH1             *((volatile unsigned int*)(0x42486AA4UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH2             *((volatile unsigned int*)(0x42486AA8UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH3             *((volatile unsigned int*)(0x42486AACUL))
#define bFM0P_MFT_PPG_PRLH23_PRLH4             *((volatile unsigned int*)(0x42486AB0UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH5             *((volatile unsigned int*)(0x42486AB4UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH6             *((volatile unsigned int*)(0x42486AB8UL))
#define bFM0P_MFT_PPG_PRLH23_PRLH7             *((volatile unsigned int*)(0x42486ABCUL))
#define bFM0P_MFT_PPG_GATEC20_EDGE20           *((volatile unsigned int*)(0x42486B00UL))
#define bFM0P_MFT_PPG_GATEC20_STRG20           *((volatile unsigned int*)(0x42486B04UL))
#define bFM0P_MFT_PPG_GATEC20_EDGE22           *((volatile unsigned int*)(0x42486B10UL))
#define bFM0P_MFT_PPG_GATEC20_STRG22           *((volatile unsigned int*)(0x42486B14UL))
#define bFM0P_MFT_PPG_IGBTC_IGBTMD             *((volatile unsigned int*)(0x42487000UL))
#define bFM0P_MFT_PPG_IGBTC_IGTRGLV            *((volatile unsigned int*)(0x42487004UL))
#define bFM0P_MFT_PPG_IGBTC_IGOSEL0            *((volatile unsigned int*)(0x42487008UL))
#define bFM0P_MFT_PPG_IGBTC_IGOSEL1            *((volatile unsigned int*)(0x4248700CUL))
#define bFM0P_MFT_PPG_IGBTC_IGNFW0             *((volatile unsigned int*)(0x42487010UL))
#define bFM0P_MFT_PPG_IGBTC_IGNFW1             *((volatile unsigned int*)(0x42487014UL))
#define bFM0P_MFT_PPG_IGBTC_IGNFW2             *((volatile unsigned int*)(0x42487018UL))
#define bFM0P_MFT_PPG_IGBTC_IGATIH             *((volatile unsigned int*)(0x4248701CUL))

/* Base Timer 0 PPG registers */
#define bFM0P_BT0_PPG_TMCR_STRG                *((volatile unsigned int*)(0x424A0180UL))
#define bFM0P_BT0_PPG_TMCR_CTEN                *((volatile unsigned int*)(0x424A0184UL))
#define bFM0P_BT0_PPG_TMCR_MDSE                *((volatile unsigned int*)(0x424A0188UL))
#define bFM0P_BT0_PPG_TMCR_OSEL                *((volatile unsigned int*)(0x424A018CUL))
#define bFM0P_BT0_PPG_TMCR_FMD0                *((volatile unsigned int*)(0x424A0190UL))
#define bFM0P_BT0_PPG_TMCR_FMD1                *((volatile unsigned int*)(0x424A0194UL))
#define bFM0P_BT0_PPG_TMCR_FMD2                *((volatile unsigned int*)(0x424A0198UL))
#define bFM0P_BT0_PPG_TMCR_EGS0                *((volatile unsigned int*)(0x424A01A0UL))
#define bFM0P_BT0_PPG_TMCR_EGS1                *((volatile unsigned int*)(0x424A01A4UL))
#define bFM0P_BT0_PPG_TMCR_PMSK                *((volatile unsigned int*)(0x424A01A8UL))
#define bFM0P_BT0_PPG_TMCR_RTGEN               *((volatile unsigned int*)(0x424A01ACUL))
#define bFM0P_BT0_PPG_TMCR_CKS0                *((volatile unsigned int*)(0x424A01B0UL))
#define bFM0P_BT0_PPG_TMCR_CKS1                *((volatile unsigned int*)(0x424A01B4UL))
#define bFM0P_BT0_PPG_TMCR_CKS2                *((volatile unsigned int*)(0x424A01B8UL))
#define bFM0P_BT0_PPG_STC_UDIR                 *((volatile unsigned int*)(0x424A0200UL))
#define bFM0P_BT0_PPG_STC_TGIR                 *((volatile unsigned int*)(0x424A0208UL))
#define bFM0P_BT0_PPG_STC_UDIE                 *((volatile unsigned int*)(0x424A0210UL))
#define bFM0P_BT0_PPG_STC_TGIE                 *((volatile unsigned int*)(0x424A0218UL))
#define bFM0P_BT0_PPG_TMCR2_CKS3               *((volatile unsigned int*)(0x424A0220UL))

/* Base Timer 0 PWM registers */
#define bFM0P_BT0_PWM_TMCR_STRG                *((volatile unsigned int*)(0x424A0180UL))
#define bFM0P_BT0_PWM_TMCR_CTEN                *((volatile unsigned int*)(0x424A0184UL))
#define bFM0P_BT0_PWM_TMCR_MDSE                *((volatile unsigned int*)(0x424A0188UL))
#define bFM0P_BT0_PWM_TMCR_OSEL                *((volatile unsigned int*)(0x424A018CUL))
#define bFM0P_BT0_PWM_TMCR_FMD0                *((volatile unsigned int*)(0x424A0190UL))
#define bFM0P_BT0_PWM_TMCR_FMD1                *((volatile unsigned int*)(0x424A0194UL))
#define bFM0P_BT0_PWM_TMCR_FMD2                *((volatile unsigned int*)(0x424A0198UL))
#define bFM0P_BT0_PWM_TMCR_EGS0                *((volatile unsigned int*)(0x424A01A0UL))
#define bFM0P_BT0_PWM_TMCR_EGS1                *((volatile unsigned int*)(0x424A01A4UL))
#define bFM0P_BT0_PWM_TMCR_PMSK                *((volatile unsigned int*)(0x424A01A8UL))
#define bFM0P_BT0_PWM_TMCR_RTGEN               *((volatile unsigned int*)(0x424A01ACUL))
#define bFM0P_BT0_PWM_TMCR_CKS0                *((volatile unsigned int*)(0x424A01B0UL))
#define bFM0P_BT0_PWM_TMCR_CKS1                *((volatile unsigned int*)(0x424A01B4UL))
#define bFM0P_BT0_PWM_TMCR_CKS2                *((volatile unsigned int*)(0x424A01B8UL))
#define bFM0P_BT0_PWM_STC_UDIR                 *((volatile unsigned int*)(0x424A0200UL))
#define bFM0P_BT0_PWM_STC_DTIR                 *((volatile unsigned int*)(0x424A0204UL))
#define bFM0P_BT0_PWM_STC_TGIR                 *((volatile unsigned int*)(0x424A0208UL))
#define bFM0P_BT0_PWM_STC_UDIE                 *((volatile unsigned int*)(0x424A0210UL))
#define bFM0P_BT0_PWM_STC_DTIE                 *((volatile unsigned int*)(0x424A0214UL))
#define bFM0P_BT0_PWM_STC_TGIE                 *((volatile unsigned int*)(0x424A0218UL))
#define bFM0P_BT0_PWM_TMCR2_CKS3               *((volatile unsigned int*)(0x424A0220UL))

/* Base Timer 0 RT registers */
#define bFM0P_BT0_RT_TMCR_STRG                 *((volatile unsigned int*)(0x424A0180UL))
#define bFM0P_BT0_RT_TMCR_CTEN                 *((volatile unsigned int*)(0x424A0184UL))
#define bFM0P_BT0_RT_TMCR_MDSE                 *((volatile unsigned int*)(0x424A0188UL))
#define bFM0P_BT0_RT_TMCR_OSEL                 *((volatile unsigned int*)(0x424A018CUL))
#define bFM0P_BT0_RT_TMCR_FMD0                 *((volatile unsigned int*)(0x424A0190UL))
#define bFM0P_BT0_RT_TMCR_FMD1                 *((volatile unsigned int*)(0x424A0194UL))
#define bFM0P_BT0_RT_TMCR_FMD2                 *((volatile unsigned int*)(0x424A0198UL))
#define bFM0P_BT0_RT_TMCR_T32                  *((volatile unsigned int*)(0x424A019CUL))
#define bFM0P_BT0_RT_TMCR_EGS0                 *((volatile unsigned int*)(0x424A01A0UL))
#define bFM0P_BT0_RT_TMCR_EGS1                 *((volatile unsigned int*)(0x424A01A4UL))
#define bFM0P_BT0_RT_TMCR_CKS0                 *((volatile unsigned int*)(0x424A01B0UL))
#define bFM0P_BT0_RT_TMCR_CKS1                 *((volatile unsigned int*)(0x424A01B4UL))
#define bFM0P_BT0_RT_TMCR_CKS2                 *((volatile unsigned int*)(0x424A01B8UL))
#define bFM0P_BT0_RT_STC_UDIR                  *((volatile unsigned int*)(0x424A0200UL))
#define bFM0P_BT0_RT_STC_TGIR                  *((volatile unsigned int*)(0x424A0208UL))
#define bFM0P_BT0_RT_STC_UDIE                  *((volatile unsigned int*)(0x424A0210UL))
#define bFM0P_BT0_RT_STC_TGIE                  *((volatile unsigned int*)(0x424A0218UL))
#define bFM0P_BT0_RT_TMCR2_CKS3                *((volatile unsigned int*)(0x424A0220UL))
#define bFM0P_BT0_RT_TMCR2_GATE                *((volatile unsigned int*)(0x424A023CUL))

/* Base Timer 0 PWC registers */
#define bFM0P_BT0_PWC_TMCR_CTEN                *((volatile unsigned int*)(0x424A0184UL))
#define bFM0P_BT0_PWC_TMCR_MDSE                *((volatile unsigned int*)(0x424A0188UL))
#define bFM0P_BT0_PWC_TMCR_FMD0                *((volatile unsigned int*)(0x424A0190UL))
#define bFM0P_BT0_PWC_TMCR_FMD1                *((volatile unsigned int*)(0x424A0194UL))
#define bFM0P_BT0_PWC_TMCR_FMD2                *((volatile unsigned int*)(0x424A0198UL))
#define bFM0P_BT0_PWC_TMCR_T32                 *((volatile unsigned int*)(0x424A019CUL))
#define bFM0P_BT0_PWC_TMCR_EGS0                *((volatile unsigned int*)(0x424A01A0UL))
#define bFM0P_BT0_PWC_TMCR_EGS1                *((volatile unsigned int*)(0x424A01A4UL))
#define bFM0P_BT0_PWC_TMCR_EGS2                *((volatile unsigned int*)(0x424A01A8UL))
#define bFM0P_BT0_PWC_TMCR_CKS0                *((volatile unsigned int*)(0x424A01B0UL))
#define bFM0P_BT0_PWC_TMCR_CKS1                *((volatile unsigned int*)(0x424A01B4UL))
#define bFM0P_BT0_PWC_TMCR_CKS2                *((volatile unsigned int*)(0x424A01B8UL))
#define bFM0P_BT0_PWC_STC_OVIR                 *((volatile unsigned int*)(0x424A0200UL))
#define bFM0P_BT0_PWC_STC_EDIR                 *((volatile unsigned int*)(0x424A0208UL))
#define bFM0P_BT0_PWC_STC_OVIE                 *((volatile unsigned int*)(0x424A0210UL))
#define bFM0P_BT0_PWC_STC_EDIE                 *((volatile unsigned int*)(0x424A0218UL))
#define bFM0P_BT0_PWC_STC_ERR                  *((volatile unsigned int*)(0x424A021CUL))
#define bFM0P_BT0_PWC_TMCR2_CKS3               *((volatile unsigned int*)(0x424A0220UL))

/* Base Timer 1 PPG registers */
#define bFM0P_BT1_PPG_TMCR_STRG                 *((volatile unsigned int*)(0x424A0980UL))
#define bFM0P_BT1_PPG_TMCR_CTEN                 *((volatile unsigned int*)(0x424A0984UL))
#define bFM0P_BT1_PPG_TMCR_MDSE                 *((volatile unsigned int*)(0x424A0988UL))
#define bFM0P_BT1_PPG_TMCR_OSEL                 *((volatile unsigned int*)(0x424A098CUL))
#define bFM0P_BT1_PPG_TMCR_FMD0                 *((volatile unsigned int*)(0x424A0090UL))
#define bFM0P_BT1_PPG_TMCR_FMD1                 *((volatile unsigned int*)(0x424A0994UL))
#define bFM0P_BT1_PPG_TMCR_FMD2                 *((volatile unsigned int*)(0x424A0998UL))
#define bFM0P_BT1_PPG_TMCR_EGS0                 *((volatile unsigned int*)(0x424A09A0UL))
#define bFM0P_BT1_PPG_TMCR_EGS1                 *((volatile unsigned int*)(0x424A09A4UL))
#define bFM0P_BT1_PPG_TMCR_PMSK                 *((volatile unsigned int*)(0x424A09A8UL))
#define bFM0P_BT1_PPG_TMCR_RTGEN                *((volatile unsigned int*)(0x424A09ACUL))
#define bFM0P_BT1_PPG_TMCR_CKS0                 *((volatile unsigned int*)(0x424A09B0UL))
#define bFM0P_BT1_PPG_TMCR_CKS1                 *((volatile unsigned int*)(0x424A09B4UL))
#define bFM0P_BT1_PPG_TMCR_CKS2                 *((volatile unsigned int*)(0x424A09B8UL))
#define bFM0P_BT1_PPG_STC_UDIR                  *((volatile unsigned int*)(0x424A0A00UL))
#define bFM0P_BT1_PPG_STC_TGIR                  *((volatile unsigned int*)(0x424A0A08UL))
#define bFM0P_BT1_PPG_STC_UDIE                  *((volatile unsigned int*)(0x424A0A10UL))
#define bFM0P_BT1_PPG_STC_TGIE                  *((volatile unsigned int*)(0x424A0A18UL))
#define bFM0P_BT1_PPG_TMCR2_CKS3                *((volatile unsigned int*)(0x424A0A20UL))

/* Base Timer 1 PWM registers */
#define bFM0P_BT1_PWM_TMCR_STRG                 *((volatile unsigned int*)(0x424A0980UL))
#define bFM0P_BT1_PWM_TMCR_CTEN                 *((volatile unsigned int*)(0x424A0984UL))
#define bFM0P_BT1_PWM_TMCR_MDSE                 *((volatile unsigned int*)(0x424A0988UL))
#define bFM0P_BT1_PWM_TMCR_OSEL                 *((volatile unsigned int*)(0x424A098CUL))
#define bFM0P_BT1_PWM_TMCR_FMD0                 *((volatile unsigned int*)(0x424A0990UL))
#define bFM0P_BT1_PWM_TMCR_FMD1                 *((volatile unsigned int*)(0x424A0994UL))
#define bFM0P_BT1_PWM_TMCR_FMD2                 *((volatile unsigned int*)(0x424A0998UL))
#define bFM0P_BT1_PWM_TMCR_EGS0                 *((volatile unsigned int*)(0x424A09A0UL))
#define bFM0P_BT1_PWM_TMCR_EGS1                 *((volatile unsigned int*)(0x424A09A4UL))
#define bFM0P_BT1_PWM_TMCR_PMSK                 *((volatile unsigned int*)(0x424A09A8UL))
#define bFM0P_BT1_PWM_TMCR_RTGEN                *((volatile unsigned int*)(0x424A09ACUL))
#define bFM0P_BT1_PWM_TMCR_CKS0                 *((volatile unsigned int*)(0x424A09B0UL))
#define bFM0P_BT1_PWM_TMCR_CKS1                 *((volatile unsigned int*)(0x424A09B4UL))
#define bFM0P_BT1_PWM_TMCR_CKS2                 *((volatile unsigned int*)(0x424A09B8UL))
#define bFM0P_BT1_PWM_STC_UDIR                  *((volatile unsigned int*)(0x424A0A00UL))
#define bFM0P_BT1_PWM_STC_DTIR                  *((volatile unsigned int*)(0x424A0A04UL))
#define bFM0P_BT1_PWM_STC_TGIR                  *((volatile unsigned int*)(0x424A0A08UL))
#define bFM0P_BT1_PWM_STC_UDIE                  *((volatile unsigned int*)(0x424A0A10UL))
#define bFM0P_BT1_PWM_STC_DTIE                  *((volatile unsigned int*)(0x424A0A14UL))
#define bFM0P_BT1_PWM_STC_TGIE                  *((volatile unsigned int*)(0x424A0A18UL))
#define bFM0P_BT1_PWM_TMCR2_CKS3                *((volatile unsigned int*)(0x424A0A20UL))

/* Base Timer 1 RT registers */
#define bFM0P_BT1_RT_TMCR_STRG                  *((volatile unsigned int*)(0x424A0980UL))
#define bFM0P_BT1_RT_TMCR_CTEN                  *((volatile unsigned int*)(0x424A0984UL))
#define bFM0P_BT1_RT_TMCR_MDSE                  *((volatile unsigned int*)(0x424A0988UL))
#define bFM0P_BT1_RT_TMCR_OSEL                  *((volatile unsigned int*)(0x424A098CUL))
#define bFM0P_BT1_RT_TMCR_FMD0                  *((volatile unsigned int*)(0x424A0990UL))
#define bFM0P_BT1_RT_TMCR_FMD1                  *((volatile unsigned int*)(0x424A0994UL))
#define bFM0P_BT1_RT_TMCR_FMD2                  *((volatile unsigned int*)(0x424A0998UL))
#define bFM0P_BT1_RT_TMCR_T32                   *((volatile unsigned int*)(0x424A099CUL))
#define bFM0P_BT1_RT_TMCR_EGS0                  *((volatile unsigned int*)(0x424A09A0UL))
#define bFM0P_BT1_RT_TMCR_EGS1                  *((volatile unsigned int*)(0x424A09A4UL))
#define bFM0P_BT1_RT_TMCR_CKS0                  *((volatile unsigned int*)(0x424A09B0UL))
#define bFM0P_BT1_RT_TMCR_CKS1                  *((volatile unsigned int*)(0x424A09B4UL))
#define bFM0P_BT1_RT_TMCR_CKS2                  *((volatile unsigned int*)(0x424A09B8UL))
#define bFM0P_BT1_RT_STC_UDIR                   *((volatile unsigned int*)(0x424A0A00UL))
#define bFM0P_BT1_RT_STC_TGIR                   *((volatile unsigned int*)(0x424A0A08UL))
#define bFM0P_BT1_RT_STC_UDIE                   *((volatile unsigned int*)(0x424A0A10UL))
#define bFM0P_BT1_RT_STC_TGIE                   *((volatile unsigned int*)(0x424A0A18UL))
#define bFM0P_BT1_RT_TMCR2_CKS3                 *((volatile unsigned int*)(0x424A0A20UL))
#define bFM0P_BT1_RT_TMCR2_GATE                 *((volatile unsigned int*)(0x424A0A3CUL))

/* Base Timer 1 PWC registers */
#define bFM0P_BT1_PWC_TMCR_CTEN                 *((volatile unsigned int*)(0x424A0984UL))
#define bFM0P_BT1_PWC_TMCR_MDSE                 *((volatile unsigned int*)(0x424A0988UL))
#define bFM0P_BT1_PWC_TMCR_FMD0                 *((volatile unsigned int*)(0x424A0990UL))
#define bFM0P_BT1_PWC_TMCR_FMD1                 *((volatile unsigned int*)(0x424A0994UL))
#define bFM0P_BT1_PWC_TMCR_FMD2                 *((volatile unsigned int*)(0x424A0998UL))
#define bFM0P_BT1_PWC_TMCR_T32                  *((volatile unsigned int*)(0x424A099CUL))
#define bFM0P_BT1_PWC_TMCR_EGS0                 *((volatile unsigned int*)(0x424A09A0UL))
#define bFM0P_BT1_PWC_TMCR_EGS1                 *((volatile unsigned int*)(0x424A09A4UL))
#define bFM0P_BT1_PWC_TMCR_EGS2                 *((volatile unsigned int*)(0x424A09A8UL))
#define bFM0P_BT1_PWC_TMCR_CKS0                 *((volatile unsigned int*)(0x424A09B0UL))
#define bFM0P_BT1_PWC_TMCR_CKS1                 *((volatile unsigned int*)(0x424A09B4UL))
#define bFM0P_BT1_PWC_TMCR_CKS2                 *((volatile unsigned int*)(0x424A09B8UL))
#define bFM0P_BT1_PWC_STC_OVIR                  *((volatile unsigned int*)(0x424A0A00UL))
#define bFM0P_BT1_PWC_STC_EDIR                  *((volatile unsigned int*)(0x424A0A08UL))
#define bFM0P_BT1_PWC_STC_OVIE                  *((volatile unsigned int*)(0x424A0A10UL))
#define bFM0P_BT1_PWC_STC_EDIE                  *((volatile unsigned int*)(0x424A0A18UL))
#define bFM0P_BT1_PWC_STC_ERR                   *((volatile unsigned int*)(0x424A0A1CUL))
#define bFM0P_BT1_PWC_TMCR2_CKS3                *((volatile unsigned int*)(0x424A0A20UL))

/* Base Timer 2 PPG registers */
#define bFM0P_BT2_PPG_TMCR_STRG                 *((volatile unsigned int*)(0x424A1180UL))
#define bFM0P_BT2_PPG_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1184UL))
#define bFM0P_BT2_PPG_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1188UL))
#define bFM0P_BT2_PPG_TMCR_OSEL                 *((volatile unsigned int*)(0x424A118CUL))
#define bFM0P_BT2_PPG_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1190UL))
#define bFM0P_BT2_PPG_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1194UL))
#define bFM0P_BT2_PPG_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1198UL))
#define bFM0P_BT2_PPG_TMCR_EGS0                 *((volatile unsigned int*)(0x424A11A0UL))
#define bFM0P_BT2_PPG_TMCR_EGS1                 *((volatile unsigned int*)(0x424A11A4UL))
#define bFM0P_BT2_PPG_TMCR_PMSK                 *((volatile unsigned int*)(0x424A11A8UL))
#define bFM0P_BT2_PPG_TMCR_RTGEN                *((volatile unsigned int*)(0x424A11ACUL))
#define bFM0P_BT2_PPG_TMCR_CKS0                 *((volatile unsigned int*)(0x424A11B0UL))
#define bFM0P_BT2_PPG_TMCR_CKS1                 *((volatile unsigned int*)(0x424A11B4UL))
#define bFM0P_BT2_PPG_TMCR_CKS2                 *((volatile unsigned int*)(0x424A11B8UL))
#define bFM0P_BT2_PPG_STC_UDIR                  *((volatile unsigned int*)(0x424A1200UL))
#define bFM0P_BT2_PPG_STC_TGIR                  *((volatile unsigned int*)(0x424A1208UL))
#define bFM0P_BT2_PPG_STC_UDIE                  *((volatile unsigned int*)(0x424A1210UL))
#define bFM0P_BT2_PPG_STC_TGIE                  *((volatile unsigned int*)(0x424A1218UL))
#define bFM0P_BT2_PPG_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1220UL))

/* Base Timer 2 PWM registers */
#define bFM0P_BT2_PWM_TMCR_STRG                 *((volatile unsigned int*)(0x424A1180UL))
#define bFM0P_BT2_PWM_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1184UL))
#define bFM0P_BT2_PWM_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1188UL))
#define bFM0P_BT2_PWM_TMCR_OSEL                 *((volatile unsigned int*)(0x424A118CUL))
#define bFM0P_BT2_PWM_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1190UL))
#define bFM0P_BT2_PWM_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1194UL))
#define bFM0P_BT2_PWM_TMCR_FMD2                 *((volatile unsigned int*)(0x424A11A0UL))
#define bFM0P_BT2_PWM_TMCR_EGS0                 *((volatile unsigned int*)(0x424A11A0UL))
#define bFM0P_BT2_PWM_TMCR_EGS1                 *((volatile unsigned int*)(0x424A11A4UL))
#define bFM0P_BT2_PWM_TMCR_PMSK                 *((volatile unsigned int*)(0x424A11A8UL))
#define bFM0P_BT2_PWM_TMCR_RTGEN                *((volatile unsigned int*)(0x424A11ACUL))
#define bFM0P_BT2_PWM_TMCR_CKS0                 *((volatile unsigned int*)(0x424A11B0UL))
#define bFM0P_BT2_PWM_TMCR_CKS1                 *((volatile unsigned int*)(0x424A11B4UL))
#define bFM0P_BT2_PWM_TMCR_CKS2                 *((volatile unsigned int*)(0x424A11B8UL))
#define bFM0P_BT2_PWM_STC_UDIR                  *((volatile unsigned int*)(0x424A1200UL))
#define bFM0P_BT2_PWM_STC_DTIR                  *((volatile unsigned int*)(0x424A1204UL))
#define bFM0P_BT2_PWM_STC_TGIR                  *((volatile unsigned int*)(0x424A1208UL))
#define bFM0P_BT2_PWM_STC_UDIE                  *((volatile unsigned int*)(0x424A1210UL))
#define bFM0P_BT2_PWM_STC_DTIE                  *((volatile unsigned int*)(0x424A1214UL))
#define bFM0P_BT2_PWM_STC_TGIE                  *((volatile unsigned int*)(0x424A1218UL))
#define bFM0P_BT2_PWM_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1220UL))

/* Base Timer 2 RT registers */
#define bFM0P_BT2_RT_TMCR_STRG                  *((volatile unsigned int*)(0x424A1180UL))
#define bFM0P_BT2_RT_TMCR_CTEN                  *((volatile unsigned int*)(0x424A1184UL))
#define bFM0P_BT2_RT_TMCR_MDSE                  *((volatile unsigned int*)(0x424A1188UL))
#define bFM0P_BT2_RT_TMCR_OSEL                  *((volatile unsigned int*)(0x424A118CUL))
#define bFM0P_BT2_PPG_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1190UL))
#define bFM0P_BT2_PPG_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1194UL))
#define bFM0P_BT2_PPG_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1198UL))
#define bFM0P_BT2_RT_TMCR_T32                   *((volatile unsigned int*)(0x424A119CUL))
#define bFM0P_BT2_RT_TMCR_EGS0                  *((volatile unsigned int*)(0x424A11A0UL))
#define bFM0P_BT2_RT_TMCR_EGS1                  *((volatile unsigned int*)(0x424A11A4UL))
#define bFM0P_BT2_RT_TMCR_CKS0                  *((volatile unsigned int*)(0x424A11B0UL))
#define bFM0P_BT2_RT_TMCR_CKS1                  *((volatile unsigned int*)(0x424A11B4UL))
#define bFM0P_BT2_RT_TMCR_CKS2                  *((volatile unsigned int*)(0x424A11B8UL))
#define bFM0P_BT2_RT_STC_UDIR                   *((volatile unsigned int*)(0x424A1200UL))
#define bFM0P_BT2_RT_STC_TGIR                   *((volatile unsigned int*)(0x424A1208UL))
#define bFM0P_BT2_RT_STC_UDIE                   *((volatile unsigned int*)(0x424A1210UL))
#define bFM0P_BT2_RT_STC_TGIE                   *((volatile unsigned int*)(0x424A1218UL))
#define bFM0P_BT2_RT_TMCR2_CKS3                 *((volatile unsigned int*)(0x424A1220UL))
#define bFM0P_BT2_RT_TMCR2_GATE                 *((volatile unsigned int*)(0x424A123CUL))

/* Base Timer 2 PWC registers */
#define bFM0P_BT2_PWC_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1184UL))
#define bFM0P_BT2_PWC_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1188UL))
#define bFM0P_BT2_PWC_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1190UL))
#define bFM0P_BT2_PWC_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1194UL))
#define bFM0P_BT2_PWC_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1198UL))
#define bFM0P_BT2_PWC_TMCR_T32                  *((volatile unsigned int*)(0x424A119CUL))
#define bFM0P_BT2_PWC_TMCR_EGS0                 *((volatile unsigned int*)(0x424A11A0UL))
#define bFM0P_BT2_PWC_TMCR_EGS1                 *((volatile unsigned int*)(0x424A11A4UL))
#define bFM0P_BT2_PWC_TMCR_EGS2                 *((volatile unsigned int*)(0x424A11A8UL))
#define bFM0P_BT2_PWC_TMCR_CKS0                 *((volatile unsigned int*)(0x424A11B0UL))
#define bFM0P_BT2_PWC_TMCR_CKS1                 *((volatile unsigned int*)(0x424A11B4UL))
#define bFM0P_BT2_PWC_TMCR_CKS2                 *((volatile unsigned int*)(0x424A11B8UL))
#define bFM0P_BT2_PWC_STC_OVIR                  *((volatile unsigned int*)(0x424A1200UL))
#define bFM0P_BT2_PWC_STC_EDIR                  *((volatile unsigned int*)(0x424A1208UL))
#define bFM0P_BT2_PWC_STC_OVIE                  *((volatile unsigned int*)(0x424A1210UL))
#define bFM0P_BT2_PWC_STC_EDIE                  *((volatile unsigned int*)(0x424A1218UL))
#define bFM0P_BT2_PWC_STC_ERR                   *((volatile unsigned int*)(0x424A121CUL))
#define bFM0P_BT2_PWC_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1220UL))

/* Base Timer 3 PPG registers */
#define bFM0P_BT3_PPG_TMCR_STRG                 *((volatile unsigned int*)(0x424A1980UL))
#define bFM0P_BT3_PPG_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1984UL))
#define bFM0P_BT3_PPG_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1988UL))
#define bFM0P_BT3_PPG_TMCR_OSEL                 *((volatile unsigned int*)(0x424A198CUL))
#define bFM0P_BT3_PPG_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1990UL))
#define bFM0P_BT3_PPG_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1994UL))
#define bFM0P_BT3_PPG_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1998UL))
#define bFM0P_BT3_PPG_TMCR_EGS0                 *((volatile unsigned int*)(0x424A19A0UL))
#define bFM0P_BT3_PPG_TMCR_EGS1                 *((volatile unsigned int*)(0x424A19A4UL))
#define bFM0P_BT3_PPG_TMCR_PMSK                 *((volatile unsigned int*)(0x424A19A8UL))
#define bFM0P_BT3_PPG_TMCR_RTGEN                *((volatile unsigned int*)(0x424A19ACUL))
#define bFM0P_BT3_PPG_TMCR_CKS0                 *((volatile unsigned int*)(0x424A19B0UL))
#define bFM0P_BT3_PPG_TMCR_CKS1                 *((volatile unsigned int*)(0x424A19B4UL))
#define bFM0P_BT3_PPG_TMCR_CKS2                 *((volatile unsigned int*)(0x424A19B8UL))
#define bFM0P_BT3_PPG_STC_UDIR                  *((volatile unsigned int*)(0x424A1A00UL))
#define bFM0P_BT3_PPG_STC_TGIR                  *((volatile unsigned int*)(0x424A1A08UL))
#define bFM0P_BT3_PPG_STC_UDIE                  *((volatile unsigned int*)(0x424A1A10UL))
#define bFM0P_BT3_PPG_STC_TGIE                  *((volatile unsigned int*)(0x424A1A18UL))
#define bFM0P_BT3_PPG_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1A20UL))

/* Base Timer 3 PWM registers */
#define bFM0P_BT3_PWM_TMCR_STRG                 *((volatile unsigned int*)(0x424A1980UL))
#define bFM0P_BT3_PWM_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1984UL))
#define bFM0P_BT3_PWM_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1988UL))
#define bFM0P_BT3_PWM_TMCR_OSEL                 *((volatile unsigned int*)(0x424A198CUL))
#define bFM0P_BT3_PWM_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1990UL))
#define bFM0P_BT3_PWM_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1994UL))
#define bFM0P_BT3_PWM_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1998UL))
#define bFM0P_BT3_PWM_TMCR_EGS0                 *((volatile unsigned int*)(0x424A19A0UL))
#define bFM0P_BT3_PWM_TMCR_EGS1                 *((volatile unsigned int*)(0x424A19A4UL))
#define bFM0P_BT3_PWM_TMCR_PMSK                 *((volatile unsigned int*)(0x424A19A8UL))
#define bFM0P_BT3_PWM_TMCR_RTGEN                *((volatile unsigned int*)(0x424A19ACUL))
#define bFM0P_BT3_PWM_TMCR_CKS0                 *((volatile unsigned int*)(0x424A19B0UL))
#define bFM0P_BT3_PWM_TMCR_CKS1                 *((volatile unsigned int*)(0x424A19B4UL))
#define bFM0P_BT3_PWM_TMCR_CKS2                 *((volatile unsigned int*)(0x424A19B8UL))
#define bFM0P_BT3_PWM_STC_UDIR                  *((volatile unsigned int*)(0x424A1A00UL))
#define bFM0P_BT3_PWM_STC_DTIR                  *((volatile unsigned int*)(0x424A1A04UL))
#define bFM0P_BT3_PWM_STC_TGIR                  *((volatile unsigned int*)(0x424A1A08UL))
#define bFM0P_BT3_PWM_STC_UDIE                  *((volatile unsigned int*)(0x424A1A10UL))
#define bFM0P_BT3_PWM_STC_DTIE                  *((volatile unsigned int*)(0x424A1A14UL))
#define bFM0P_BT3_PWM_STC_TGIE                  *((volatile unsigned int*)(0x424A1A18UL))
#define bFM0P_BT3_PWM_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1A20UL))

/* Base Timer 3 RT registers */
#define bFM0P_BT3_RT_TMCR_STRG                  *((volatile unsigned int*)(0x424A1980UL))
#define bFM0P_BT3_RT_TMCR_CTEN                  *((volatile unsigned int*)(0x424A1984UL))
#define bFM0P_BT3_RT_TMCR_MDSE                  *((volatile unsigned int*)(0x424A1988UL))
#define bFM0P_BT3_RT_TMCR_OSEL                  *((volatile unsigned int*)(0x424A198CUL))
#define bFM0P_BT3_RT_TMCR_FMD0                  *((volatile unsigned int*)(0x424A1990UL))
#define bFM0P_BT3_RT_TMCR_FMD1                  *((volatile unsigned int*)(0x424A1994UL))
#define bFM0P_BT3_RT_TMCR_FMD2                  *((volatile unsigned int*)(0x424A1998UL))
#define bFM0P_BT3_RT_TMCR_T32                   *((volatile unsigned int*)(0x424A199CUL))
#define bFM0P_BT3_RT_TMCR_EGS0                  *((volatile unsigned int*)(0x424A19A0UL))
#define bFM0P_BT3_RT_TMCR_EGS1                  *((volatile unsigned int*)(0x424A19A4UL))
#define bFM0P_BT3_RT_TMCR_CKS0                  *((volatile unsigned int*)(0x424A19B0UL))
#define bFM0P_BT3_RT_TMCR_CKS1                  *((volatile unsigned int*)(0x424A19B4UL))
#define bFM0P_BT3_RT_TMCR_CKS2                  *((volatile unsigned int*)(0x424A19B8UL))
#define bFM0P_BT3_RT_STC_UDIR                   *((volatile unsigned int*)(0x424A1A00UL))
#define bFM0P_BT3_RT_STC_TGIR                   *((volatile unsigned int*)(0x424A1A08UL))
#define bFM0P_BT3_RT_STC_UDIE                   *((volatile unsigned int*)(0x424A1A10UL))
#define bFM0P_BT3_RT_STC_TGIE                   *((volatile unsigned int*)(0x424A1A18UL))
#define bFM0P_BT3_RT_TMCR2_CKS3                 *((volatile unsigned int*)(0x424A1A20UL))
#define bFM0P_BT3_RT_TMCR2_GATE                 *((volatile unsigned int*)(0x424A1A32UL))

/* Base Timer 3 PWC registers */
#define bFM0P_BT3_PWC_TMCR_CTEN                 *((volatile unsigned int*)(0x424A1984UL))
#define bFM0P_BT3_PWC_TMCR_MDSE                 *((volatile unsigned int*)(0x424A1988UL))
#define bFM0P_BT3_PWC_TMCR_FMD0                 *((volatile unsigned int*)(0x424A1990UL))
#define bFM0P_BT3_PWC_TMCR_FMD1                 *((volatile unsigned int*)(0x424A1994UL))
#define bFM0P_BT3_PWC_TMCR_FMD2                 *((volatile unsigned int*)(0x424A1998UL))
#define bFM0P_BT3_PWC_TMCR_T32                  *((volatile unsigned int*)(0x424A199CUL))
#define bFM0P_BT3_PWC_TMCR_EGS0                 *((volatile unsigned int*)(0x424A19A0UL))
#define bFM0P_BT3_PWC_TMCR_EGS1                 *((volatile unsigned int*)(0x424A19A4UL))
#define bFM0P_BT3_PWC_TMCR_EGS2                 *((volatile unsigned int*)(0x424A19A8UL))
#define bFM0P_BT3_PWC_TMCR_CKS0                 *((volatile unsigned int*)(0x424A19B0UL))
#define bFM0P_BT3_PWC_TMCR_CKS1                 *((volatile unsigned int*)(0x424A19B4UL))
#define bFM0P_BT3_PWC_TMCR_CKS2                 *((volatile unsigned int*)(0x424A19B8UL))
#define bFM0P_BT3_PWC_STC_OVIR                  *((volatile unsigned int*)(0x424A1A00UL))
#define bFM0P_BT3_PWC_STC_EDIR                  *((volatile unsigned int*)(0x424A1A08UL))
#define bFM0P_BT3_PWC_STC_OVIE                  *((volatile unsigned int*)(0x424A1A10UL))
#define bFM0P_BT3_PWC_STC_EDIE                  *((volatile unsigned int*)(0x424A1A18UL))
#define bFM0P_BT3_PWC_STC_ERR                   *((volatile unsigned int*)(0x424A1A1CUL))
#define bFM0P_BT3_PWC_TMCR2_CKS3                *((volatile unsigned int*)(0x424A1A20UL))

/* Base Timer I/O selector channel 0 - channel 3 registers */
#define bFM0P_BTIOSEL03_BTSEL0123_SEL01_0       *((volatile unsigned int*)(0x424A2020UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL01_1       *((volatile unsigned int*)(0x424A2024UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL01_2       *((volatile unsigned int*)(0x424A2028UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL01_3       *((volatile unsigned int*)(0x424A202CUL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL23_0       *((volatile unsigned int*)(0x424A2030UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL23_1       *((volatile unsigned int*)(0x424A2034UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL23_2       *((volatile unsigned int*)(0x424A2038UL))
#define bFM0P_BTIOSEL03_BTSEL0123_SEL23_3       *((volatile unsigned int*)(0x424A203CUL))

/* Software based Simulation Startup (Base Timer) register */
#define bFM0P_SBSSR_BTSSSR_SSSR0               *((volatile unsigned int*)(0x424BFF80UL))
#define bFM0P_SBSSR_BTSSSR_SSSR1               *((volatile unsigned int*)(0x424BFF84UL))
#define bFM0P_SBSSR_BTSSSR_SSSR2               *((volatile unsigned int*)(0x424BFF88UL))
#define bFM0P_SBSSR_BTSSSR_SSSR3               *((volatile unsigned int*)(0x424BFF8CUL))

/* Quad position and revolution counter channel 0 registers */
#define bFM0P_QPRC0_QICRL_QPCMIE               *((volatile unsigned int*)(0x424C0280UL))
#define bFM0P_QPRC0_QICRL_QPCMF                *((volatile unsigned int*)(0x424C0284UL))
#define bFM0P_QPRC0_QICRL_QPRCMIE              *((volatile unsigned int*)(0x424C0288UL))
#define bFM0P_QPRC0_QICRL_QPRCMF               *((volatile unsigned int*)(0x424C028CUL))
#define bFM0P_QPRC0_QICRL_OUZIE                *((volatile unsigned int*)(0x424C0290UL))
#define bFM0P_QPRC0_QICRL_UFDF                 *((volatile unsigned int*)(0x424C0294UL))
#define bFM0P_QPRC0_QICRL_OFDF                 *((volatile unsigned int*)(0x424C0298UL))
#define bFM0P_QPRC0_QICRL_ZIIF                 *((volatile unsigned int*)(0x424C029CUL))
#define bFM0P_QPRC0_QICRH_CDCIE                *((volatile unsigned int*)(0x424C02A0UL))
#define bFM0P_QPRC0_QICRH_CDCF                 *((volatile unsigned int*)(0x424C02A4UL))
#define bFM0P_QPRC0_QICRH_DIRPC                *((volatile unsigned int*)(0x424C02A8UL))
#define bFM0P_QPRC0_QICRH_DIROU                *((volatile unsigned int*)(0x424C02ACUL))
#define bFM0P_QPRC0_QICRH_QPCNRCMIE            *((volatile unsigned int*)(0x424C02B0UL))
#define bFM0P_QPRC0_QICRH_QPCNRCMF             *((volatile unsigned int*)(0x424C02B4UL))
#define bFM0P_QPRC0_QCRL_PCM0                  *((volatile unsigned int*)(0x424C0300UL))
#define bFM0P_QPRC0_QCRL_PCM1                  *((volatile unsigned int*)(0x424C0304UL))
#define bFM0P_QPRC0_QCRL_RCM0                  *((volatile unsigned int*)(0x424C0308UL))
#define bFM0P_QPRC0_QCRL_RCM1                  *((volatile unsigned int*)(0x424C030CUL))
#define bFM0P_QPRC0_QCRL_PSTP                  *((volatile unsigned int*)(0x424C0310UL))
#define bFM0P_QPRC0_QCRL_CGSC                  *((volatile unsigned int*)(0x424C0314UL))
#define bFM0P_QPRC0_QCRL_RSEL                  *((volatile unsigned int*)(0x424C0318UL))
#define bFM0P_QPRC0_QCRL_SWAP                  *((volatile unsigned int*)(0x424C031CUL))
#define bFM0P_QPRC0_QCRH_PCRM0                 *((volatile unsigned int*)(0x424C0320UL))
#define bFM0P_QPRC0_QCRH_PCRM1                 *((volatile unsigned int*)(0x424C0324UL))
#define bFM0P_QPRC0_QCRH_AES0                  *((volatile unsigned int*)(0x424C0328UL))
#define bFM0P_QPRC0_QCRH_AES1                  *((volatile unsigned int*)(0x424C032CUL))
#define bFM0P_QPRC0_QCRH_BES0                  *((volatile unsigned int*)(0x424C0330UL))
#define bFM0P_QPRC0_QCRH_BES1                  *((volatile unsigned int*)(0x424C0334UL))
#define bFM0P_QPRC0_QCRH_CGE0                  *((volatile unsigned int*)(0x424C0338UL))
#define bFM0P_QPRC0_QCRH_CGE1                  *((volatile unsigned int*)(0x424C033CUL))
#define bFM0P_QPRC0_QECR_ORNGMD                *((volatile unsigned int*)(0x424C0380UL))
#define bFM0P_QPRC0_QECR_ORNGF                 *((volatile unsigned int*)(0x424C0384UL))
#define bFM0P_QPRC0_QECR_ORNGIE                *((volatile unsigned int*)(0x424C0388UL))

/* QPRC0_NF registers */
#define bFM0P_QPRC0_NF_NFCTLA_AINNWS0          *((volatile unsigned int*)(0x424C2000UL))
#define bFM0P_QPRC0_NF_NFCTLA_AINNWS1          *((volatile unsigned int*)(0x424C2004UL))
#define bFM0P_QPRC0_NF_NFCTLA_AINNWS2          *((volatile unsigned int*)(0x424C2008UL))
#define bFM0P_QPRC0_NF_NFCTLA_AINLV            *((volatile unsigned int*)(0x424C2010UL))
#define bFM0P_QPRC0_NF_NFCTLA_AINMD            *((volatile unsigned int*)(0x424C2014UL))
#define bFM0P_QPRC0_NF_NFCTLB_BINNWS0          *((volatile unsigned int*)(0x424C2080UL))
#define bFM0P_QPRC0_NF_NFCTLB_BINNWS1          *((volatile unsigned int*)(0x424C2084UL))
#define bFM0P_QPRC0_NF_NFCTLB_BINNWS2          *((volatile unsigned int*)(0x424C2088UL))
#define bFM0P_QPRC0_NF_NFCTLB_BINLV            *((volatile unsigned int*)(0x424C2090UL))
#define bFM0P_QPRC0_NF_NFCTLB_BINMD            *((volatile unsigned int*)(0x424C2094UL))
#define bFM0P_QPRC0_NF_NFCTLZ_ZINNWS0          *((volatile unsigned int*)(0x424C2100UL))
#define bFM0P_QPRC0_NF_NFCTLZ_ZINNWS1          *((volatile unsigned int*)(0x424C2104UL))
#define bFM0P_QPRC0_NF_NFCTLZ_ZINNWS2          *((volatile unsigned int*)(0x424C2108UL))
#define bFM0P_QPRC0_NF_NFCTLZ_ZINLV            *((volatile unsigned int*)(0x424C2110UL))
#define bFM0P_QPRC0_NF_NFCTLZ_ZINMD            *((volatile unsigned int*)(0x424C2114UL))

/* 12-bit ADC unit 0 registers */
#define bFM0P_ADC0_ADSR_SCS                    *((volatile unsigned int*)(0x424E0000UL))
#define bFM0P_ADC0_ADSR_PCS                    *((volatile unsigned int*)(0x424E0004UL))
#define bFM0P_ADC0_ADSR_PCNS                   *((volatile unsigned int*)(0x424E0008UL))
#define bFM0P_ADC0_ADSR_FDAS                   *((volatile unsigned int*)(0x424E0018UL))
#define bFM0P_ADC0_ADSR_ADSTP                  *((volatile unsigned int*)(0x424E001CUL))
#define bFM0P_ADC0_ADCR_OVRIE                  *((volatile unsigned int*)(0x424E0020UL))
#define bFM0P_ADC0_ADCR_CMPIE                  *((volatile unsigned int*)(0x424E0024UL))
#define bFM0P_ADC0_ADCR_PCIE                   *((volatile unsigned int*)(0x424E0028UL))
#define bFM0P_ADC0_ADCR_SCIE                   *((volatile unsigned int*)(0x424E002CUL))
#define bFM0P_ADC0_ADCR_CMPIF                  *((volatile unsigned int*)(0x424E0034UL))
#define bFM0P_ADC0_ADCR_PCIF                   *((volatile unsigned int*)(0x424E0038UL))
#define bFM0P_ADC0_ADCR_SCIF                   *((volatile unsigned int*)(0x424E003CUL))
#define bFM0P_ADC0_SFNS_SFS0                   *((volatile unsigned int*)(0x424E0100UL))
#define bFM0P_ADC0_SFNS_SFS1                   *((volatile unsigned int*)(0x424E0104UL))
#define bFM0P_ADC0_SFNS_SFS2                   *((volatile unsigned int*)(0x424E0108UL))
#define bFM0P_ADC0_SFNS_SFS3                   *((volatile unsigned int*)(0x424E010CUL))
#define bFM0P_ADC0_SCCR_SSTR                   *((volatile unsigned int*)(0x424E0120UL))
#define bFM0P_ADC0_SCCR_SHEN                   *((volatile unsigned int*)(0x424E0124UL))
#define bFM0P_ADC0_SCCR_RPT                    *((volatile unsigned int*)(0x424E0128UL))
#define bFM0P_ADC0_SCCR_SFCLR                  *((volatile unsigned int*)(0x424E0130UL))
#define bFM0P_ADC0_SCCR_SOVR                   *((volatile unsigned int*)(0x424E0134UL))
#define bFM0P_ADC0_SCCR_SFUL                   *((volatile unsigned int*)(0x424E0138UL))
#define bFM0P_ADC0_SCCR_SEMP                   *((volatile unsigned int*)(0x424E013CUL))
#define bFM0P_ADC0_SCFD_SC0                    *((volatile unsigned int*)(0x424E0180UL))
#define bFM0P_ADC0_SCFD_SC1                    *((volatile unsigned int*)(0x424E0184UL))
#define bFM0P_ADC0_SCFD_SC2                    *((volatile unsigned int*)(0x424E0188UL))
#define bFM0P_ADC0_SCFD_SC3                    *((volatile unsigned int*)(0x424E018CUL))
#define bFM0P_ADC0_SCFD_SC4                    *((volatile unsigned int*)(0x424E0190UL))
#define bFM0P_ADC0_SCFD_RS0                    *((volatile unsigned int*)(0x424E01A0UL))
#define bFM0P_ADC0_SCFD_RS1                    *((volatile unsigned int*)(0x424E01A4UL))
#define bFM0P_ADC0_SCFD_INVL                   *((volatile unsigned int*)(0x424E01B0UL))
#define bFM0P_ADC0_SCFD_SD0                    *((volatile unsigned int*)(0x424E01D0UL))
#define bFM0P_ADC0_SCFD_SD1                    *((volatile unsigned int*)(0x424E01D4UL))
#define bFM0P_ADC0_SCFD_SD2                    *((volatile unsigned int*)(0x424E01D8UL))
#define bFM0P_ADC0_SCFD_SD3                    *((volatile unsigned int*)(0x424E01DCUL))
#define bFM0P_ADC0_SCFD_SD4                    *((volatile unsigned int*)(0x424E01E0UL))
#define bFM0P_ADC0_SCFD_SD5                    *((volatile unsigned int*)(0x424E01E4UL))
#define bFM0P_ADC0_SCFD_SD6                    *((volatile unsigned int*)(0x424E01E8UL))
#define bFM0P_ADC0_SCFD_SD7                    *((volatile unsigned int*)(0x424E01ECUL))
#define bFM0P_ADC0_SCFD_SD8                    *((volatile unsigned int*)(0x424E01F0UL))
#define bFM0P_ADC0_SCFD_SD9                    *((volatile unsigned int*)(0x424E01F4UL))
#define bFM0P_ADC0_SCFD_SD10                   *((volatile unsigned int*)(0x424E01F8UL))
#define bFM0P_ADC0_SCFD_SD11                   *((volatile unsigned int*)(0x424E01FCUL))
#define bFM0P_ADC0_SCIS2_AN16                  *((volatile unsigned int*)(0x424E0200UL))
#define bFM0P_ADC0_SCIS2_AN17                  *((volatile unsigned int*)(0x424E0204UL))
#define bFM0P_ADC0_SCIS2_AN18                  *((volatile unsigned int*)(0x424E0208UL))
#define bFM0P_ADC0_SCIS2_AN19                  *((volatile unsigned int*)(0x424E020CUL))
#define bFM0P_ADC0_SCIS2_AN20                  *((volatile unsigned int*)(0x424E0210UL))
#define bFM0P_ADC0_SCIS2_AN21                  *((volatile unsigned int*)(0x424E0214UL))
#define bFM0P_ADC0_SCIS2_AN22                  *((volatile unsigned int*)(0x424E0218UL))
#define bFM0P_ADC0_SCIS2_AN23                  *((volatile unsigned int*)(0x424E021CUL))
#define bFM0P_ADC0_SCIS3_AN24                  *((volatile unsigned int*)(0x424E0220UL))
#define bFM0P_ADC0_SCIS3_AN25                  *((volatile unsigned int*)(0x424E0224UL))
#define bFM0P_ADC0_SCIS3_AN26                  *((volatile unsigned int*)(0x424E0228UL))
#define bFM0P_ADC0_SCIS3_AN27                  *((volatile unsigned int*)(0x424E022CUL))
#define bFM0P_ADC0_SCIS3_AN28                  *((volatile unsigned int*)(0x424E0230UL))
#define bFM0P_ADC0_SCIS3_AN29                  *((volatile unsigned int*)(0x424E0234UL))
#define bFM0P_ADC0_SCIS3_AN30                  *((volatile unsigned int*)(0x424E0238UL))
#define bFM0P_ADC0_SCIS3_AN31                  *((volatile unsigned int*)(0x424E023CUL))
#define bFM0P_ADC0_SCIS0_AN0                   *((volatile unsigned int*)(0x424E0280UL))
#define bFM0P_ADC0_SCIS0_AN1                   *((volatile unsigned int*)(0x424E0284UL))
#define bFM0P_ADC0_SCIS0_AN2                   *((volatile unsigned int*)(0x424E0288UL))
#define bFM0P_ADC0_SCIS0_AN3                   *((volatile unsigned int*)(0x424E028CUL))
#define bFM0P_ADC0_SCIS0_AN4                   *((volatile unsigned int*)(0x424E0290UL))
#define bFM0P_ADC0_SCIS0_AN5                   *((volatile unsigned int*)(0x424E0294UL))
#define bFM0P_ADC0_SCIS0_AN6                   *((volatile unsigned int*)(0x424E0298UL))
#define bFM0P_ADC0_SCIS0_AN7                   *((volatile unsigned int*)(0x424E029CUL))
#define bFM0P_ADC0_SCIS1_AN8                   *((volatile unsigned int*)(0x424E02A0UL))
#define bFM0P_ADC0_SCIS1_AN9                   *((volatile unsigned int*)(0x424E02A4UL))
#define bFM0P_ADC0_SCIS1_AN10                  *((volatile unsigned int*)(0x424E02A8UL))
#define bFM0P_ADC0_SCIS1_AN11                  *((volatile unsigned int*)(0x424E02ACUL))
#define bFM0P_ADC0_SCIS1_AN12                  *((volatile unsigned int*)(0x424E02B0UL))
#define bFM0P_ADC0_SCIS1_AN13                  *((volatile unsigned int*)(0x424E02B4UL))
#define bFM0P_ADC0_SCIS1_AN14                  *((volatile unsigned int*)(0x424E02B8UL))
#define bFM0P_ADC0_SCIS1_AN15                  *((volatile unsigned int*)(0x424E02BCUL))
#define bFM0P_ADC0_PFNS_PFS0                   *((volatile unsigned int*)(0x424E0300UL))
#define bFM0P_ADC0_PFNS_PFS1                   *((volatile unsigned int*)(0x424E0304UL))
#define bFM0P_ADC0_PFNS_TEST0                  *((volatile unsigned int*)(0x424E0310UL))
#define bFM0P_ADC0_PFNS_TEST1                  *((volatile unsigned int*)(0x424E0314UL))
#define bFM0P_ADC0_PCCR_PSTR                   *((volatile unsigned int*)(0x424E0320UL))
#define bFM0P_ADC0_PCCR_PHEN                   *((volatile unsigned int*)(0x424E0324UL))
#define bFM0P_ADC0_PCCR_PEEN                   *((volatile unsigned int*)(0x424E0328UL))
#define bFM0P_ADC0_PCCR_ESCE                   *((volatile unsigned int*)(0x424E032CUL))
#define bFM0P_ADC0_PCCR_PFCLR                  *((volatile unsigned int*)(0x424E0330UL))
#define bFM0P_ADC0_PCCR_POVR                   *((volatile unsigned int*)(0x424E0334UL))
#define bFM0P_ADC0_PCCR_PFUL                   *((volatile unsigned int*)(0x424E0338UL))
#define bFM0P_ADC0_PCCR_PEMP                   *((volatile unsigned int*)(0x424E033CUL))
#define bFM0P_ADC0_PCFD_PC0                    *((volatile unsigned int*)(0x424E0380UL))
#define bFM0P_ADC0_PCFD_PC1                    *((volatile unsigned int*)(0x424E0384UL))
#define bFM0P_ADC0_PCFD_PC2                    *((volatile unsigned int*)(0x424E0388UL))
#define bFM0P_ADC0_PCFD_PC3                    *((volatile unsigned int*)(0x424E038CUL))
#define bFM0P_ADC0_PCFD_PC4                    *((volatile unsigned int*)(0x424E0390UL))
#define bFM0P_ADC0_PCFD_RS0                    *((volatile unsigned int*)(0x424E03A0UL))
#define bFM0P_ADC0_PCFD_RS1                    *((volatile unsigned int*)(0x424E03A4UL))
#define bFM0P_ADC0_PCFD_RS2                    *((volatile unsigned int*)(0x424E03A8UL))
#define bFM0P_ADC0_PCFD_INVL                   *((volatile unsigned int*)(0x424E03B0UL))
#define bFM0P_ADC0_PCFD_PD0                    *((volatile unsigned int*)(0x424E03D0UL))
#define bFM0P_ADC0_PCFD_PD1                    *((volatile unsigned int*)(0x424E03D4UL))
#define bFM0P_ADC0_PCFD_PD2                    *((volatile unsigned int*)(0x424E03D8UL))
#define bFM0P_ADC0_PCFD_PD3                    *((volatile unsigned int*)(0x424E03DCUL))
#define bFM0P_ADC0_PCFD_PD4                    *((volatile unsigned int*)(0x424E03E0UL))
#define bFM0P_ADC0_PCFD_PD5                    *((volatile unsigned int*)(0x424E03E4UL))
#define bFM0P_ADC0_PCFD_PD6                    *((volatile unsigned int*)(0x424E03E8UL))
#define bFM0P_ADC0_PCFD_PD7                    *((volatile unsigned int*)(0x424E03ECUL))
#define bFM0P_ADC0_PCFD_PD8                    *((volatile unsigned int*)(0x424E03F0UL))
#define bFM0P_ADC0_PCFD_PD9                    *((volatile unsigned int*)(0x424E03F4UL))
#define bFM0P_ADC0_PCFD_PD10                   *((volatile unsigned int*)(0x424E03F8UL))
#define bFM0P_ADC0_PCFD_PD11                   *((volatile unsigned int*)(0x424E03FCUL))
#define bFM0P_ADC0_PCIS_P1A0                   *((volatile unsigned int*)(0x424E0400UL))
#define bFM0P_ADC0_PCIS_P1A1                   *((volatile unsigned int*)(0x424E0404UL))
#define bFM0P_ADC0_PCIS_P1A2                   *((volatile unsigned int*)(0x424E0408UL))
#define bFM0P_ADC0_PCIS_P2A0                   *((volatile unsigned int*)(0x424E040CUL))
#define bFM0P_ADC0_PCIS_P2A1                   *((volatile unsigned int*)(0x424E0410UL))
#define bFM0P_ADC0_PCIS_P2A2                   *((volatile unsigned int*)(0x424E0414UL))
#define bFM0P_ADC0_PCIS_P2A3                   *((volatile unsigned int*)(0x424E0418UL))
#define bFM0P_ADC0_PCIS_P2A4                   *((volatile unsigned int*)(0x424E041CUL))
#define bFM0P_ADC0_CMPCR_CCH0                  *((volatile unsigned int*)(0x424E0480UL))
#define bFM0P_ADC0_CMPCR_CCH1                  *((volatile unsigned int*)(0x424E0484UL))
#define bFM0P_ADC0_CMPCR_CCH2                  *((volatile unsigned int*)(0x424E0488UL))
#define bFM0P_ADC0_CMPCR_CCH3                  *((volatile unsigned int*)(0x424E048CUL))
#define bFM0P_ADC0_CMPCR_CCH4                  *((volatile unsigned int*)(0x424E0490UL))
#define bFM0P_ADC0_CMPCR_CMD0                  *((volatile unsigned int*)(0x424E0494UL))
#define bFM0P_ADC0_CMPCR_CMD1                  *((volatile unsigned int*)(0x424E0498UL))
#define bFM0P_ADC0_CMPCR_CMPEN                 *((volatile unsigned int*)(0x424E049CUL))
#define bFM0P_ADC0_CMPD_CMAD0                  *((volatile unsigned int*)(0x424E04D8UL))
#define bFM0P_ADC0_CMPD_CMAD1                  *((volatile unsigned int*)(0x424E04DCUL))
#define bFM0P_ADC0_CMPD_CMAD2                  *((volatile unsigned int*)(0x424E04E0UL))
#define bFM0P_ADC0_CMPD_CMAD3                  *((volatile unsigned int*)(0x424E04E4UL))
#define bFM0P_ADC0_CMPD_CMAD4                  *((volatile unsigned int*)(0x424E04E8UL))
#define bFM0P_ADC0_CMPD_CMAD5                  *((volatile unsigned int*)(0x424E04ECUL))
#define bFM0P_ADC0_CMPD_CMAD6                  *((volatile unsigned int*)(0x424E04F0UL))
#define bFM0P_ADC0_CMPD_CMAD7                  *((volatile unsigned int*)(0x424E04F4UL))
#define bFM0P_ADC0_CMPD_CMAD8                  *((volatile unsigned int*)(0x424E04F8UL))
#define bFM0P_ADC0_CMPD_CMAD9                  *((volatile unsigned int*)(0x424E04FCUL))
#define bFM0P_ADC0_ADSS2_TS16                  *((volatile unsigned int*)(0x424E0500UL))
#define bFM0P_ADC0_ADSS2_TS17                  *((volatile unsigned int*)(0x424E0504UL))
#define bFM0P_ADC0_ADSS2_TS18                  *((volatile unsigned int*)(0x424E0508UL))
#define bFM0P_ADC0_ADSS2_TS19                  *((volatile unsigned int*)(0x424E050CUL))
#define bFM0P_ADC0_ADSS2_TS20                  *((volatile unsigned int*)(0x424E0510UL))
#define bFM0P_ADC0_ADSS2_TS21                  *((volatile unsigned int*)(0x424E0514UL))
#define bFM0P_ADC0_ADSS2_TS22                  *((volatile unsigned int*)(0x424E0518UL))
#define bFM0P_ADC0_ADSS2_TS23                  *((volatile unsigned int*)(0x424E051CUL))
#define bFM0P_ADC0_ADSS3_TS24                  *((volatile unsigned int*)(0x424E0520UL))
#define bFM0P_ADC0_ADSS3_TS25                  *((volatile unsigned int*)(0x424E0524UL))
#define bFM0P_ADC0_ADSS3_TS26                  *((volatile unsigned int*)(0x424E0528UL))
#define bFM0P_ADC0_ADSS3_TS27                  *((volatile unsigned int*)(0x424E052CUL))
#define bFM0P_ADC0_ADSS3_TS28                  *((volatile unsigned int*)(0x424E0530UL))
#define bFM0P_ADC0_ADSS3_TS29                  *((volatile unsigned int*)(0x424E0534UL))
#define bFM0P_ADC0_ADSS3_TS30                  *((volatile unsigned int*)(0x424E0538UL))
#define bFM0P_ADC0_ADSS3_TS31                  *((volatile unsigned int*)(0x424E053CUL))
#define bFM0P_ADC0_ADSS0_TS0                   *((volatile unsigned int*)(0x424E0580UL))
#define bFM0P_ADC0_ADSS0_TS1                   *((volatile unsigned int*)(0x424E0584UL))
#define bFM0P_ADC0_ADSS0_TS2                   *((volatile unsigned int*)(0x424E0588UL))
#define bFM0P_ADC0_ADSS0_TS3                   *((volatile unsigned int*)(0x424E058CUL))
#define bFM0P_ADC0_ADSS0_TS4                   *((volatile unsigned int*)(0x424E0590UL))
#define bFM0P_ADC0_ADSS0_TS5                   *((volatile unsigned int*)(0x424E0594UL))
#define bFM0P_ADC0_ADSS0_TS6                   *((volatile unsigned int*)(0x424E0598UL))
#define bFM0P_ADC0_ADSS0_TS7                   *((volatile unsigned int*)(0x424E059CUL))
#define bFM0P_ADC0_ADSS1_TS8                   *((volatile unsigned int*)(0x424E05A0UL))
#define bFM0P_ADC0_ADSS1_TS9                   *((volatile unsigned int*)(0x424E05A4UL))
#define bFM0P_ADC0_ADSS1_TS10                  *((volatile unsigned int*)(0x424E05A8UL))
#define bFM0P_ADC0_ADSS1_TS11                  *((volatile unsigned int*)(0x424E05ACUL))
#define bFM0P_ADC0_ADSS1_TS12                  *((volatile unsigned int*)(0x424E05B0UL))
#define bFM0P_ADC0_ADSS1_TS13                  *((volatile unsigned int*)(0x424E05B4UL))
#define bFM0P_ADC0_ADSS1_TS14                  *((volatile unsigned int*)(0x424E05B8UL))
#define bFM0P_ADC0_ADSS1_TS15                  *((volatile unsigned int*)(0x424E05BCUL))
#define bFM0P_ADC0_ADST1_ST10                  *((volatile unsigned int*)(0x424E0600UL))
#define bFM0P_ADC0_ADST1_ST11                  *((volatile unsigned int*)(0x424E0604UL))
#define bFM0P_ADC0_ADST1_ST12                  *((volatile unsigned int*)(0x424E0608UL))
#define bFM0P_ADC0_ADST1_ST13                  *((volatile unsigned int*)(0x424E060CUL))
#define bFM0P_ADC0_ADST1_ST14                  *((volatile unsigned int*)(0x424E0610UL))
#define bFM0P_ADC0_ADST1_STX10                 *((volatile unsigned int*)(0x424E0614UL))
#define bFM0P_ADC0_ADST1_STX11                 *((volatile unsigned int*)(0x424E0618UL))
#define bFM0P_ADC0_ADST1_STX12                 *((volatile unsigned int*)(0x424E061CUL))
#define bFM0P_ADC0_ADST0_ST00                  *((volatile unsigned int*)(0x424E0620UL))
#define bFM0P_ADC0_ADST0_ST01                  *((volatile unsigned int*)(0x424E0624UL))
#define bFM0P_ADC0_ADST0_ST02                  *((volatile unsigned int*)(0x424E0628UL))
#define bFM0P_ADC0_ADST0_ST03                  *((volatile unsigned int*)(0x424E062CUL))
#define bFM0P_ADC0_ADST0_ST04                  *((volatile unsigned int*)(0x424E0630UL))
#define bFM0P_ADC0_ADST0_STX00                 *((volatile unsigned int*)(0x424E0634UL))
#define bFM0P_ADC0_ADST0_STX01                 *((volatile unsigned int*)(0x424E0638UL))
#define bFM0P_ADC0_ADST0_STX02                 *((volatile unsigned int*)(0x424E063CUL))
#define bFM0P_ADC0_ADCT_CT0                    *((volatile unsigned int*)(0x424E0680UL))
#define bFM0P_ADC0_ADCT_CT1                    *((volatile unsigned int*)(0x424E0684UL))
#define bFM0P_ADC0_ADCT_CT2                    *((volatile unsigned int*)(0x424E0688UL))
#define bFM0P_ADC0_ADCT_CT3                    *((volatile unsigned int*)(0x424E068CUL))
#define bFM0P_ADC0_ADCT_CT4                    *((volatile unsigned int*)(0x424E0690UL))
#define bFM0P_ADC0_ADCT_CT5                    *((volatile unsigned int*)(0x424E0694UL))
#define bFM0P_ADC0_ADCT_CT6                    *((volatile unsigned int*)(0x424E0698UL))
#define bFM0P_ADC0_ADCT_CT7                    *((volatile unsigned int*)(0x424E069CUL))
#define bFM0P_ADC0_PRTSL_PRTSL0                *((volatile unsigned int*)(0x424E0700UL))
#define bFM0P_ADC0_PRTSL_PRTSL1                *((volatile unsigned int*)(0x424E0704UL))
#define bFM0P_ADC0_PRTSL_PRTSL2                *((volatile unsigned int*)(0x424E0708UL))
#define bFM0P_ADC0_PRTSL_PRTSL3                *((volatile unsigned int*)(0x424E070CUL))
#define bFM0P_ADC0_SCTSL_SCTSL0                *((volatile unsigned int*)(0x424E0720UL))
#define bFM0P_ADC0_SCTSL_SCTSL1                *((volatile unsigned int*)(0x424E0724UL))
#define bFM0P_ADC0_SCTSL_SCTSL2                *((volatile unsigned int*)(0x424E0728UL))
#define bFM0P_ADC0_SCTSL_SCTSL3                *((volatile unsigned int*)(0x424E072CUL))
#define bFM0P_ADC0_ADCEN_ENBL                  *((volatile unsigned int*)(0x424E0780UL))
#define bFM0P_ADC0_ADCEN_READY                 *((volatile unsigned int*)(0x424E0784UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME0             *((volatile unsigned int*)(0x424E07A0UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME1             *((volatile unsigned int*)(0x424E07A4UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME2             *((volatile unsigned int*)(0x424E07A8UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME3             *((volatile unsigned int*)(0x424E07ACUL))
#define bFM0P_ADC0_ADCEN_ENBLTIME4             *((volatile unsigned int*)(0x424E07B0UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME5             *((volatile unsigned int*)(0x424E07B4UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME6             *((volatile unsigned int*)(0x424E07B8UL))
#define bFM0P_ADC0_ADCEN_ENBLTIME7             *((volatile unsigned int*)(0x424E07BCUL))
#define bFM0P_ADC0_WCMRCIF_RCINT               *((volatile unsigned int*)(0x424E0880UL))
#define bFM0P_ADC0_WCMRCOT_RCOOF               *((volatile unsigned int*)(0x424E0900UL))
#define bFM0P_ADC0_WCMPCR_RCOE                 *((volatile unsigned int*)(0x424E0988UL))
#define bFM0P_ADC0_WCMPCR_RCOIE                *((volatile unsigned int*)(0x424E098CUL))
#define bFM0P_ADC0_WCMPCR_RCOIRS               *((volatile unsigned int*)(0x424E0990UL))
#define bFM0P_ADC0_WCMPCR_RCODC0               *((volatile unsigned int*)(0x424E0994UL))
#define bFM0P_ADC0_WCMPCR_RCODC1               *((volatile unsigned int*)(0x424E0998UL))
#define bFM0P_ADC0_WCMPCR_RCODC2               *((volatile unsigned int*)(0x424E099CUL))
#define bFM0P_ADC0_WCMPSR_WCCH0                *((volatile unsigned int*)(0x424E09A0UL))
#define bFM0P_ADC0_WCMPSR_WCCH1                *((volatile unsigned int*)(0x424E09A4UL))
#define bFM0P_ADC0_WCMPSR_WCCH2                *((volatile unsigned int*)(0x424E09A8UL))
#define bFM0P_ADC0_WCMPSR_WCCH3                *((volatile unsigned int*)(0x424E09ACUL))
#define bFM0P_ADC0_WCMPSR_WCCH4                *((volatile unsigned int*)(0x424E09B0UL))
#define bFM0P_ADC0_WCMPSR_WCMD                 *((volatile unsigned int*)(0x424E09B4UL))
#define bFM0P_ADC0_WCMPDL_CMLD0                *((volatile unsigned int*)(0x424E0A18UL))
#define bFM0P_ADC0_WCMPDL_CMLD1                *((volatile unsigned int*)(0x424E0A1CUL))
#define bFM0P_ADC0_WCMPDL_CMLD2                *((volatile unsigned int*)(0x424E0A20UL))
#define bFM0P_ADC0_WCMPDL_CMLD3                *((volatile unsigned int*)(0x424E0A24UL))
#define bFM0P_ADC0_WCMPDL_CMLD4                *((volatile unsigned int*)(0x424E0A28UL))
#define bFM0P_ADC0_WCMPDL_CMLD5                *((volatile unsigned int*)(0x424E0A2CUL))
#define bFM0P_ADC0_WCMPDL_CMLD6                *((volatile unsigned int*)(0x424E0A30UL))
#define bFM0P_ADC0_WCMPDL_CMLD7                *((volatile unsigned int*)(0x424E0A34UL))
#define bFM0P_ADC0_WCMPDL_CMLD8                *((volatile unsigned int*)(0x424E0A38UL))
#define bFM0P_ADC0_WCMPDL_CMLD9                *((volatile unsigned int*)(0x424E0A3CUL))
#define bFM0P_ADC0_WCMPDH_CMHD0                *((volatile unsigned int*)(0x424E0A58UL))
#define bFM0P_ADC0_WCMPDH_CMHD1                *((volatile unsigned int*)(0x424E0A5CUL))
#define bFM0P_ADC0_WCMPDH_CMHD2                *((volatile unsigned int*)(0x424E0A60UL))
#define bFM0P_ADC0_WCMPDH_CMHD3                *((volatile unsigned int*)(0x424E0A64UL))
#define bFM0P_ADC0_WCMPDH_CMHD4                *((volatile unsigned int*)(0x424E0A68UL))
#define bFM0P_ADC0_WCMPDH_CMHD5                *((volatile unsigned int*)(0x424E0A6CUL))
#define bFM0P_ADC0_WCMPDH_CMHD6                *((volatile unsigned int*)(0x424E0A70UL))
#define bFM0P_ADC0_WCMPDH_CMHD7                *((volatile unsigned int*)(0x424E0A74UL))
#define bFM0P_ADC0_WCMPDH_CMHD8                *((volatile unsigned int*)(0x424E0A78UL))
#define bFM0P_ADC0_WCMPDH_CMHD9                *((volatile unsigned int*)(0x424E0A7CUL))

/* CR trimming registers */
#define bFM0P_CRTRIM_MCR_PSR_CSR0              *((volatile unsigned int*)(0x425C0000UL))
#define bFM0P_CRTRIM_MCR_PSR_CSR1              *((volatile unsigned int*)(0x425C0004UL))
#define bFM0P_CRTRIM_MCR_PSR_CSR2              *((volatile unsigned int*)(0x425C0008UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD0             *((volatile unsigned int*)(0x425C0080UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD1             *((volatile unsigned int*)(0x425C0084UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD2             *((volatile unsigned int*)(0x425C0088UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD3             *((volatile unsigned int*)(0x425C008CUL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD4             *((volatile unsigned int*)(0x425C0090UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD5             *((volatile unsigned int*)(0x425C0094UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD6             *((volatile unsigned int*)(0x425C0098UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD7             *((volatile unsigned int*)(0x425C009CUL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD8             *((volatile unsigned int*)(0x425C00A0UL))
#define bFM0P_CRTRIM_MCR_FTRM_TRD9             *((volatile unsigned int*)(0x425C00A4UL))
#define bFM0P_CRTRIM_MCR_TTRM_TRT0             *((volatile unsigned int*)(0x425C0100UL))
#define bFM0P_CRTRIM_MCR_TTRM_TRT1             *((volatile unsigned int*)(0x425C0104UL))
#define bFM0P_CRTRIM_MCR_TTRM_TRT2             *((volatile unsigned int*)(0x425C0108UL))
#define bFM0P_CRTRIM_MCR_TTRM_TRT3             *((volatile unsigned int*)(0x425C010CUL))
#define bFM0P_CRTRIM_MCR_TTRM_TRT4             *((volatile unsigned int*)(0x425C0110UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK0           *((volatile unsigned int*)(0x425C0180UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK1           *((volatile unsigned int*)(0x425C0184UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK2           *((volatile unsigned int*)(0x425C0188UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK3           *((volatile unsigned int*)(0x425C018CUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK4           *((volatile unsigned int*)(0x425C0190UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK5           *((volatile unsigned int*)(0x425C0194UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK6           *((volatile unsigned int*)(0x425C0198UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK7           *((volatile unsigned int*)(0x425C019CUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK8           *((volatile unsigned int*)(0x425C01A0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK9           *((volatile unsigned int*)(0x425C01A4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK10          *((volatile unsigned int*)(0x425C01A8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK11          *((volatile unsigned int*)(0x425C01ACUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK12          *((volatile unsigned int*)(0x425C01B0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK13          *((volatile unsigned int*)(0x425C01B4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK14          *((volatile unsigned int*)(0x425C01B8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK15          *((volatile unsigned int*)(0x425C01BCUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK16          *((volatile unsigned int*)(0x425C01C0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK17          *((volatile unsigned int*)(0x425C01C4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK18          *((volatile unsigned int*)(0x425C01C8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK19          *((volatile unsigned int*)(0x425C01CCUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK20          *((volatile unsigned int*)(0x425C01D0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK21          *((volatile unsigned int*)(0x425C01D4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK22          *((volatile unsigned int*)(0x425C01D8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK23          *((volatile unsigned int*)(0x425C01DCUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK24          *((volatile unsigned int*)(0x425C01E0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK25          *((volatile unsigned int*)(0x425C01E4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK26          *((volatile unsigned int*)(0x425C01E8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK27          *((volatile unsigned int*)(0x425C01ECUL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK28          *((volatile unsigned int*)(0x425C01F0UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK29          *((volatile unsigned int*)(0x425C01F4UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK30          *((volatile unsigned int*)(0x425C01F8UL))
#define bFM0P_CRTRIM_MCR_RLR_TRMLCK31          *((volatile unsigned int*)(0x425C01FCUL))

/* External interrupt registers */
#define bFM0P_EXTI_ENIR_EN0                    *((volatile unsigned int*)(0x42600000UL))
#define bFM0P_EXTI_ENIR_EN1                    *((volatile unsigned int*)(0x42600004UL))
#define bFM0P_EXTI_ENIR_EN2                    *((volatile unsigned int*)(0x42600008UL))
#define bFM0P_EXTI_ENIR_EN3                    *((volatile unsigned int*)(0x4260000CUL))
#define bFM0P_EXTI_ENIR_EN4                    *((volatile unsigned int*)(0x42600010UL))
#define bFM0P_EXTI_ENIR_EN5                    *((volatile unsigned int*)(0x42600014UL))
#define bFM0P_EXTI_ENIR_EN6                    *((volatile unsigned int*)(0x42600018UL))
#define bFM0P_EXTI_ENIR_EN15                   *((volatile unsigned int*)(0x4260003CUL))
#define bFM0P_EXTI_EIRR_ER0                    *((volatile unsigned int*)(0x42600080UL))
#define bFM0P_EXTI_EIRR_ER1                    *((volatile unsigned int*)(0x42600084UL))
#define bFM0P_EXTI_EIRR_ER2                    *((volatile unsigned int*)(0x42600088UL))
#define bFM0P_EXTI_EIRR_ER3                    *((volatile unsigned int*)(0x4260008CUL))
#define bFM0P_EXTI_EIRR_ER4                    *((volatile unsigned int*)(0x42600090UL))
#define bFM0P_EXTI_EIRR_ER5                    *((volatile unsigned int*)(0x42600094UL))
#define bFM0P_EXTI_EIRR_ER6                    *((volatile unsigned int*)(0x42600098UL))
#define bFM0P_EXTI_EIRR_ER15                   *((volatile unsigned int*)(0x426000BCUL))
#define bFM0P_EXTI_EICL_ECL0                   *((volatile unsigned int*)(0x42600100UL))
#define bFM0P_EXTI_EICL_ECL1                   *((volatile unsigned int*)(0x42600104UL))
#define bFM0P_EXTI_EICL_ECL2                   *((volatile unsigned int*)(0x42600108UL))
#define bFM0P_EXTI_EICL_ECL3                   *((volatile unsigned int*)(0x4260010CUL))
#define bFM0P_EXTI_EICL_ECL4                   *((volatile unsigned int*)(0x42600110UL))
#define bFM0P_EXTI_EICL_ECL5                   *((volatile unsigned int*)(0x42600114UL))
#define bFM0P_EXTI_EICL_ECL6                   *((volatile unsigned int*)(0x42600118UL))
#define bFM0P_EXTI_EICL_ECL15                  *((volatile unsigned int*)(0x4260013CUL))
#define bFM0P_EXTI_ELVR_LA0                    *((volatile unsigned int*)(0x42600180UL))
#define bFM0P_EXTI_ELVR_LB0                    *((volatile unsigned int*)(0x42600184UL))
#define bFM0P_EXTI_ELVR_LA1                    *((volatile unsigned int*)(0x42600188UL))
#define bFM0P_EXTI_ELVR_LB1                    *((volatile unsigned int*)(0x4260018CUL))
#define bFM0P_EXTI_ELVR_LA2                    *((volatile unsigned int*)(0x42600190UL))
#define bFM0P_EXTI_ELVR_LB2                    *((volatile unsigned int*)(0x42600194UL))
#define bFM0P_EXTI_ELVR_LA3                    *((volatile unsigned int*)(0x42600198UL))
#define bFM0P_EXTI_ELVR_LB3                    *((volatile unsigned int*)(0x4260019CUL))
#define bFM0P_EXTI_ELVR_LA4                    *((volatile unsigned int*)(0x426001A0UL))
#define bFM0P_EXTI_ELVR_LB4                    *((volatile unsigned int*)(0x426001A4UL))
#define bFM0P_EXTI_ELVR_LA5                    *((volatile unsigned int*)(0x426001A8UL))
#define bFM0P_EXTI_ELVR_LB5                    *((volatile unsigned int*)(0x426001ACUL))
#define bFM0P_EXTI_ELVR_LA6                    *((volatile unsigned int*)(0x426001B0UL))
#define bFM0P_EXTI_ELVR_LB6                    *((volatile unsigned int*)(0x426001B4UL))
#define bFM0P_EXTI_ELVR_LA15                   *((volatile unsigned int*)(0x426001F8UL))
#define bFM0P_EXTI_ELVR_LB15                   *((volatile unsigned int*)(0x426001FCUL))
#define bFM0P_EXTI_NMIRR_NR                    *((volatile unsigned int*)(0x42600280UL))
#define bFM0P_EXTI_NMICL_NCL                   *((volatile unsigned int*)(0x42600300UL))

/* INTREQ registers */
#define bFM0P_INTREQ_DRQSEL_ADCSCAN0           *((volatile unsigned int*)(0x42620014UL))
#define bFM0P_INTREQ_DRQSEL_ADCSCAN1           *((volatile unsigned int*)(0x42620018UL))
#define bFM0P_INTREQ_DRQSEL_ADCSCAN2           *((volatile unsigned int*)(0x4262001CUL))
#define bFM0P_INTREQ_DRQSEL_IRQ0BT0            *((volatile unsigned int*)(0x42620020UL))
#define bFM0P_INTREQ_DRQSEL_IRQ0BT2            *((volatile unsigned int*)(0x42620024UL))
#define bFM0P_INTREQ_DRQSEL_IRQ0BT4            *((volatile unsigned int*)(0x42620028UL))
#define bFM0P_INTREQ_DRQSEL_IRQ0BT6            *((volatile unsigned int*)(0x4262002CUL))
#define bFM0P_INTREQ_DRQSEL_MFS0RX             *((volatile unsigned int*)(0x42620030UL))
#define bFM0P_INTREQ_DRQSEL_MFS0TX             *((volatile unsigned int*)(0x42620034UL))
#define bFM0P_INTREQ_DRQSEL_MFS1RX             *((volatile unsigned int*)(0x42620038UL))
#define bFM0P_INTREQ_DRQSEL_MFS1TX             *((volatile unsigned int*)(0x4262003CUL))
#define bFM0P_INTREQ_DRQSEL_MFS2RX             *((volatile unsigned int*)(0x42620040UL))
#define bFM0P_INTREQ_DRQSEL_MFS2TX             *((volatile unsigned int*)(0x42620044UL))
#define bFM0P_INTREQ_DRQSEL_MFS3RX             *((volatile unsigned int*)(0x42620048UL))
#define bFM0P_INTREQ_DRQSEL_MFS3TX             *((volatile unsigned int*)(0x4262004CUL))
#define bFM0P_INTREQ_DRQSEL_MFS4RX             *((volatile unsigned int*)(0x42620050UL))
#define bFM0P_INTREQ_DRQSEL_MFS4TX             *((volatile unsigned int*)(0x42620054UL))
#define bFM0P_INTREQ_DRQSEL_MFS5RX             *((volatile unsigned int*)(0x42620058UL))
#define bFM0P_INTREQ_DRQSEL_MFS5TX             *((volatile unsigned int*)(0x4262005CUL))
#define bFM0P_INTREQ_DRQSEL_MFS6RX             *((volatile unsigned int*)(0x42620060UL))
#define bFM0P_INTREQ_DRQSEL_MFS6TX             *((volatile unsigned int*)(0x42620064UL))
#define bFM0P_INTREQ_DRQSEL_MFS7RX             *((volatile unsigned int*)(0x42620068UL))
#define bFM0P_INTREQ_DRQSEL_MFS7TX             *((volatile unsigned int*)(0x4262006CUL))
#define bFM0P_INTREQ_DRQSEL_EXINT0             *((volatile unsigned int*)(0x42620070UL))
#define bFM0P_INTREQ_DRQSEL_EXINT1             *((volatile unsigned int*)(0x42620074UL))
#define bFM0P_INTREQ_DRQSEL_EXINT2             *((volatile unsigned int*)(0x42620078UL))
#define bFM0P_INTREQ_DRQSEL_EXINT3             *((volatile unsigned int*)(0x4262007CUL))
#define bFM0P_INTREQ_IRQCMODE_IRQCMODE         *((volatile unsigned int*)(0x42620180UL))
#define bFM0P_INTREQ_EXC02MON_NMI              *((volatile unsigned int*)(0x42620200UL))
#define bFM0P_INTREQ_EXC02MON_HWINT            *((volatile unsigned int*)(0x42620204UL))
#define bFM0P_INTREQ_IRQ00MON_FCSINT           *((volatile unsigned int*)(0x42620280UL))
#define bFM0P_INTREQ_IRQ01MON_SWWDTINT         *((volatile unsigned int*)(0x42620300UL))
#define bFM0P_INTREQ_IRQ02MON_LVDINT           *((volatile unsigned int*)(0x42620380UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE0INT0        *((volatile unsigned int*)(0x42620400UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE0INT1        *((volatile unsigned int*)(0x42620404UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE0INT2        *((volatile unsigned int*)(0x42620408UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE0INT3        *((volatile unsigned int*)(0x4262040CUL))
#define bFM0P_INTREQ_IRQ03MON_WAVE1INT0        *((volatile unsigned int*)(0x42620410UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE1INT1        *((volatile unsigned int*)(0x42620414UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE1INT2        *((volatile unsigned int*)(0x42620418UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE1INT3        *((volatile unsigned int*)(0x4262041CUL))
#define bFM0P_INTREQ_IRQ03MON_WAVE2INT0        *((volatile unsigned int*)(0x42620420UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE2INT1        *((volatile unsigned int*)(0x42620424UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE2INT2        *((volatile unsigned int*)(0x42620428UL))
#define bFM0P_INTREQ_IRQ03MON_WAVE2INT3        *((volatile unsigned int*)(0x4262042CUL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT0          *((volatile unsigned int*)(0x42620480UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT1          *((volatile unsigned int*)(0x42620484UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT2          *((volatile unsigned int*)(0x42620488UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT3          *((volatile unsigned int*)(0x4262048CUL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT4          *((volatile unsigned int*)(0x42620490UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT5          *((volatile unsigned int*)(0x42620494UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT6          *((volatile unsigned int*)(0x42620498UL))
#define bFM0P_INTREQ_IRQ04MON_EXTINT7          *((volatile unsigned int*)(0x4262049CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT8          *((volatile unsigned int*)(0x42620500UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT9          *((volatile unsigned int*)(0x42620504UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT10         *((volatile unsigned int*)(0x42620508UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT11         *((volatile unsigned int*)(0x4262050CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT12         *((volatile unsigned int*)(0x42620510UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT13         *((volatile unsigned int*)(0x42620514UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT14         *((volatile unsigned int*)(0x42620518UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT15         *((volatile unsigned int*)(0x4262051CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT16         *((volatile unsigned int*)(0x42620520UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT17         *((volatile unsigned int*)(0x42620524UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT18         *((volatile unsigned int*)(0x42620528UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT19         *((volatile unsigned int*)(0x4262052CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT20         *((volatile unsigned int*)(0x42620530UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT21         *((volatile unsigned int*)(0x42620534UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT22         *((volatile unsigned int*)(0x42620538UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT23         *((volatile unsigned int*)(0x4262053CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT24         *((volatile unsigned int*)(0x42620540UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT25         *((volatile unsigned int*)(0x42620544UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT26         *((volatile unsigned int*)(0x42620548UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT27         *((volatile unsigned int*)(0x4262054CUL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT28         *((volatile unsigned int*)(0x42620550UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT29         *((volatile unsigned int*)(0x42620554UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT30         *((volatile unsigned int*)(0x42620558UL))
#define bFM0P_INTREQ_IRQ05MON_EXTINT31         *((volatile unsigned int*)(0x4262055CUL))
#define bFM0P_INTREQ_IRQ06MON_TIMINT0          *((volatile unsigned int*)(0x42620580UL))
#define bFM0P_INTREQ_IRQ06MON_TIMINT1          *((volatile unsigned int*)(0x42620584UL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT0         *((volatile unsigned int*)(0x42620588UL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT1         *((volatile unsigned int*)(0x4262058CUL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT2         *((volatile unsigned int*)(0x42620590UL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT3         *((volatile unsigned int*)(0x42620594UL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT4         *((volatile unsigned int*)(0x42620598UL))
#define bFM0P_INTREQ_IRQ06MON_QUD0INT5         *((volatile unsigned int*)(0x4262059CUL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT0         *((volatile unsigned int*)(0x426205A0UL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT1         *((volatile unsigned int*)(0x426205A4UL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT2         *((volatile unsigned int*)(0x426205A8UL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT3         *((volatile unsigned int*)(0x426205ACUL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT4         *((volatile unsigned int*)(0x426205B0UL))
#define bFM0P_INTREQ_IRQ06MON_QUD1INT5         *((volatile unsigned int*)(0x426205B4UL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT0         *((volatile unsigned int*)(0x426205B8UL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT1         *((volatile unsigned int*)(0x426205BCUL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT2         *((volatile unsigned int*)(0x426205C0UL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT3         *((volatile unsigned int*)(0x426205C4UL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT4         *((volatile unsigned int*)(0x426205C8UL))
#define bFM0P_INTREQ_IRQ06MON_QUD2INT5         *((volatile unsigned int*)(0x426205CCUL))
#define bFM0P_INTREQ_IRQ07MON_MFSINT0          *((volatile unsigned int*)(0x42620600UL))
#define bFM0P_INTREQ_IRQ07MON_MFSINT1          *((volatile unsigned int*)(0x42620604UL))
#define bFM0P_INTREQ_IRQ08MON_MFSINT0          *((volatile unsigned int*)(0x42620680UL))
#define bFM0P_INTREQ_IRQ08MON_MFSINT1          *((volatile unsigned int*)(0x42620684UL))
#define bFM0P_INTREQ_IRQ08MON_MFSINT2          *((volatile unsigned int*)(0x42620688UL))
#define bFM0P_INTREQ_IRQ08MON_MFSINT3          *((volatile unsigned int*)(0x4262068CUL))
#define bFM0P_INTREQ_IRQ09MON_MFSINT0          *((volatile unsigned int*)(0x42620700UL))
#define bFM0P_INTREQ_IRQ09MON_MFSINT1          *((volatile unsigned int*)(0x42620704UL))
#define bFM0P_INTREQ_IRQ10MON_MFSINT0          *((volatile unsigned int*)(0x42620780UL))
#define bFM0P_INTREQ_IRQ10MON_MFSINT1          *((volatile unsigned int*)(0x42620784UL))
#define bFM0P_INTREQ_IRQ10MON_MFSINT2          *((volatile unsigned int*)(0x42620788UL))
#define bFM0P_INTREQ_IRQ10MON_MFSINT3          *((volatile unsigned int*)(0x4262078CUL))
#define bFM0P_INTREQ_IRQ11MON_MFSINT0          *((volatile unsigned int*)(0x42620800UL))
#define bFM0P_INTREQ_IRQ11MON_MFSINT1          *((volatile unsigned int*)(0x42620804UL))
#define bFM0P_INTREQ_IRQ12MON_MFSINT0          *((volatile unsigned int*)(0x42620880UL))
#define bFM0P_INTREQ_IRQ12MON_MFSINT1          *((volatile unsigned int*)(0x42620884UL))
#define bFM0P_INTREQ_IRQ12MON_MFSINT2          *((volatile unsigned int*)(0x42620888UL))
#define bFM0P_INTREQ_IRQ12MON_MFSINT3          *((volatile unsigned int*)(0x4262088CUL))
#define bFM0P_INTREQ_IRQ13MON_MFSINT0          *((volatile unsigned int*)(0x42620900UL))
#define bFM0P_INTREQ_IRQ13MON_MFSINT1          *((volatile unsigned int*)(0x42620904UL))
#define bFM0P_INTREQ_IRQ14MON_MFSINT0          *((volatile unsigned int*)(0x42620980UL))
#define bFM0P_INTREQ_IRQ14MON_MFSINT1          *((volatile unsigned int*)(0x42620984UL))
#define bFM0P_INTREQ_IRQ14MON_MFSINT2          *((volatile unsigned int*)(0x42620988UL))
#define bFM0P_INTREQ_IRQ14MON_MFSINT3          *((volatile unsigned int*)(0x4262098CUL))
#define bFM0P_INTREQ_IRQ15MON_MFSINT0          *((volatile unsigned int*)(0x42620A00UL))
#define bFM0P_INTREQ_IRQ15MON_MFSINT1          *((volatile unsigned int*)(0x42620A04UL))
#define bFM0P_INTREQ_IRQ16MON_MFSINT0          *((volatile unsigned int*)(0x42620A80UL))
#define bFM0P_INTREQ_IRQ16MON_MFSINT1          *((volatile unsigned int*)(0x42620A84UL))
#define bFM0P_INTREQ_IRQ16MON_MFSINT2          *((volatile unsigned int*)(0x42620A88UL))
#define bFM0P_INTREQ_IRQ16MON_MFSINT3          *((volatile unsigned int*)(0x42620A8CUL))
#define bFM0P_INTREQ_IRQ17MON_MFSINT0          *((volatile unsigned int*)(0x42620B00UL))
#define bFM0P_INTREQ_IRQ17MON_MFSINT1          *((volatile unsigned int*)(0x42620B04UL))
#define bFM0P_INTREQ_IRQ18MON_MFSINT0          *((volatile unsigned int*)(0x42620B80UL))
#define bFM0P_INTREQ_IRQ18MON_MFSINT1          *((volatile unsigned int*)(0x42620B84UL))
#define bFM0P_INTREQ_IRQ18MON_MFSINT2          *((volatile unsigned int*)(0x42620B88UL))
#define bFM0P_INTREQ_IRQ18MON_MFSINT3          *((volatile unsigned int*)(0x42620B8CUL))
#define bFM0P_INTREQ_IRQ19MON_MFSINT0          *((volatile unsigned int*)(0x42620C00UL))
#define bFM0P_INTREQ_IRQ19MON_MFSINT1          *((volatile unsigned int*)(0x42620C04UL))
#define bFM0P_INTREQ_IRQ19MON_DMAINT0          *((volatile unsigned int*)(0x42620C10UL))
#define bFM0P_INTREQ_IRQ20MON_MFSINT0          *((volatile unsigned int*)(0x42620C80UL))
#define bFM0P_INTREQ_IRQ20MON_MFSINT1          *((volatile unsigned int*)(0x42620C84UL))
#define bFM0P_INTREQ_IRQ20MON_MFSINT2          *((volatile unsigned int*)(0x42620C88UL))
#define bFM0P_INTREQ_IRQ20MON_MFSINT3          *((volatile unsigned int*)(0x42620C8CUL))
#define bFM0P_INTREQ_IRQ20MON_DMAINT1          *((volatile unsigned int*)(0x42620C90UL))
#define bFM0P_INTREQ_IRQ21MON_MFSINT0          *((volatile unsigned int*)(0x42620D00UL))
#define bFM0P_INTREQ_IRQ21MON_MFSINT1          *((volatile unsigned int*)(0x42620D04UL))
#define bFM0P_INTREQ_IRQ21MON_DMAINT2          *((volatile unsigned int*)(0x42620D10UL))
#define bFM0P_INTREQ_IRQ22MON_MFSINT0          *((volatile unsigned int*)(0x42620D80UL))
#define bFM0P_INTREQ_IRQ22MON_MFSINT1          *((volatile unsigned int*)(0x42620D84UL))
#define bFM0P_INTREQ_IRQ22MON_MFSINT2          *((volatile unsigned int*)(0x42620D88UL))
#define bFM0P_INTREQ_IRQ22MON_MFSINT3          *((volatile unsigned int*)(0x42620D8CUL))
#define bFM0P_INTREQ_IRQ22MON_DMAINT3          *((volatile unsigned int*)(0x42620D90UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT0          *((volatile unsigned int*)(0x42620E00UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT1          *((volatile unsigned int*)(0x42620E04UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT2          *((volatile unsigned int*)(0x42620E08UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT3          *((volatile unsigned int*)(0x42620E0CUL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT4          *((volatile unsigned int*)(0x42620E10UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT5          *((volatile unsigned int*)(0x42620E14UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT6          *((volatile unsigned int*)(0x42620E18UL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT7          *((volatile unsigned int*)(0x42620E1CUL))
#define bFM0P_INTREQ_IRQ23MON_PPGINT8          *((volatile unsigned int*)(0x42620E20UL))
#define bFM0P_INTREQ_IRQ24MON_MOSCINT          *((volatile unsigned int*)(0x42620E80UL))
#define bFM0P_INTREQ_IRQ24MON_SOSCINT          *((volatile unsigned int*)(0x42620E84UL))
#define bFM0P_INTREQ_IRQ24MON_MPLLINT          *((volatile unsigned int*)(0x42620E88UL))
#define bFM0P_INTREQ_IRQ24MON_WCINT            *((volatile unsigned int*)(0x42620E90UL))
#define bFM0P_INTREQ_IRQ24MON_RTCINT           *((volatile unsigned int*)(0x42620E94UL))
#define bFM0P_INTREQ_IRQ25MON_ADCINT0PC        *((volatile unsigned int*)(0x42620F00UL))
#define bFM0P_INTREQ_IRQ25MON_ADCINT0SC        *((volatile unsigned int*)(0x42620F04UL))
#define bFM0P_INTREQ_IRQ25MON_ADCINT0FIFO      *((volatile unsigned int*)(0x42620F08UL))
#define bFM0P_INTREQ_IRQ25MON_ADCINT0CV        *((volatile unsigned int*)(0x42620F0CUL))
#define bFM0P_INTREQ_IRQ25MON_ADCINT0RC        *((volatile unsigned int*)(0x42620F10UL))
#define bFM0P_INTREQ_IRQ26MON_ADCINT0          *((volatile unsigned int*)(0x42620F80UL))
#define bFM0P_INTREQ_IRQ26MON_ADCINT1          *((volatile unsigned int*)(0x42620F84UL))
#define bFM0P_INTREQ_IRQ26MON_ADCINT2          *((volatile unsigned int*)(0x42620F88UL))
#define bFM0P_INTREQ_IRQ26MON_ADCINT3          *((volatile unsigned int*)(0x42620F8CUL))
#define bFM0P_INTREQ_IRQ26MON_ADCINT4          *((volatile unsigned int*)(0x42620F90UL))
#define bFM0P_INTREQ_IRQ27MON_ADCINT0          *((volatile unsigned int*)(0x42621000UL))
#define bFM0P_INTREQ_IRQ27MON_ADCINT1          *((volatile unsigned int*)(0x42621004UL))
#define bFM0P_INTREQ_IRQ27MON_ADCINT2          *((volatile unsigned int*)(0x42621008UL))
#define bFM0P_INTREQ_IRQ27MON_ADCINT3          *((volatile unsigned int*)(0x4262100CUL))
#define bFM0P_INTREQ_IRQ27MON_ADCINT4          *((volatile unsigned int*)(0x42621010UL))
#define bFM0P_INTREQ_IRQ27MON_LCDCINT          *((volatile unsigned int*)(0x42621014UL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT0         *((volatile unsigned int*)(0x42621080UL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT1         *((volatile unsigned int*)(0x42621084UL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT2         *((volatile unsigned int*)(0x42621088UL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT3         *((volatile unsigned int*)(0x4262108CUL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT4         *((volatile unsigned int*)(0x42621090UL))
#define bFM0P_INTREQ_IRQ28MON_FRT0INT5         *((volatile unsigned int*)(0x42621094UL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT0         *((volatile unsigned int*)(0x42621098UL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT1         *((volatile unsigned int*)(0x4262109CUL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT2         *((volatile unsigned int*)(0x426210A0UL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT3         *((volatile unsigned int*)(0x426210A4UL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT4         *((volatile unsigned int*)(0x426210A8UL))
#define bFM0P_INTREQ_IRQ28MON_FRT1INT5         *((volatile unsigned int*)(0x426210ACUL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT0         *((volatile unsigned int*)(0x426210B0UL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT1         *((volatile unsigned int*)(0x426210B4UL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT2         *((volatile unsigned int*)(0x426210B8UL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT3         *((volatile unsigned int*)(0x426210BCUL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT4         *((volatile unsigned int*)(0x426210C0UL))
#define bFM0P_INTREQ_IRQ28MON_FRT2INT5         *((volatile unsigned int*)(0x426210C4UL))
#define bFM0P_INTREQ_IRQ29MON_ICU0INT0         *((volatile unsigned int*)(0x42621100UL))
#define bFM0P_INTREQ_IRQ29MON_ICU0INT1         *((volatile unsigned int*)(0x42621104UL))
#define bFM0P_INTREQ_IRQ29MON_ICU0INT2         *((volatile unsigned int*)(0x42621108UL))
#define bFM0P_INTREQ_IRQ29MON_ICU0INT3         *((volatile unsigned int*)(0x4262110CUL))
#define bFM0P_INTREQ_IRQ29MON_ICU1INT0         *((volatile unsigned int*)(0x42621110UL))
#define bFM0P_INTREQ_IRQ29MON_ICU1INT1         *((volatile unsigned int*)(0x42621114UL))
#define bFM0P_INTREQ_IRQ29MON_ICU1INT2         *((volatile unsigned int*)(0x42621118UL))
#define bFM0P_INTREQ_IRQ29MON_ICU1INT3         *((volatile unsigned int*)(0x4262111CUL))
#define bFM0P_INTREQ_IRQ29MON_ICU2INT0         *((volatile unsigned int*)(0x42621120UL))
#define bFM0P_INTREQ_IRQ29MON_ICU2INT1         *((volatile unsigned int*)(0x42621124UL))
#define bFM0P_INTREQ_IRQ29MON_ICU2INT2         *((volatile unsigned int*)(0x42621128UL))
#define bFM0P_INTREQ_IRQ29MON_ICU2INT3         *((volatile unsigned int*)(0x4262112CUL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT0         *((volatile unsigned int*)(0x42621180UL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT1         *((volatile unsigned int*)(0x42621184UL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT2         *((volatile unsigned int*)(0x42621188UL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT3         *((volatile unsigned int*)(0x4262118CUL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT4         *((volatile unsigned int*)(0x42621190UL))
#define bFM0P_INTREQ_IRQ30MON_OCU0INT5         *((volatile unsigned int*)(0x42621194UL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT0         *((volatile unsigned int*)(0x42621198UL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT1         *((volatile unsigned int*)(0x4262119CUL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT2         *((volatile unsigned int*)(0x426211A0UL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT3         *((volatile unsigned int*)(0x426211A4UL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT4         *((volatile unsigned int*)(0x426211A8UL))
#define bFM0P_INTREQ_IRQ30MON_OCU1INT5         *((volatile unsigned int*)(0x426211ACUL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT0         *((volatile unsigned int*)(0x426211B0UL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT1         *((volatile unsigned int*)(0x426211B4UL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT2         *((volatile unsigned int*)(0x426211B8UL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT3         *((volatile unsigned int*)(0x426211BCUL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT4         *((volatile unsigned int*)(0x426211C0UL))
#define bFM0P_INTREQ_IRQ30MON_OCU2INT5         *((volatile unsigned int*)(0x426211C4UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT0           *((volatile unsigned int*)(0x42621200UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT1           *((volatile unsigned int*)(0x42621204UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT2           *((volatile unsigned int*)(0x42621208UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT3           *((volatile unsigned int*)(0x4262120CUL))
#define bFM0P_INTREQ_IRQ31MON_BTINT4           *((volatile unsigned int*)(0x42621210UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT5           *((volatile unsigned int*)(0x42621214UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT6           *((volatile unsigned int*)(0x42621218UL))
#define bFM0P_INTREQ_IRQ31MON_BTINT7           *((volatile unsigned int*)(0x4262121CUL))
#define bFM3_INTREQ_IRQ31MON_BTINT8            *((volatile unsigned int*)(0x42621220UL))
#define bFM3_INTREQ_IRQ31MON_BTINT9            *((volatile unsigned int*)(0x42621224UL))
#define bFM3_INTREQ_IRQ31MON_BTINT10           *((volatile unsigned int*)(0x42621228UL))
#define bFM3_INTREQ_IRQ31MON_BTINT11           *((volatile unsigned int*)(0x4262122CUL))
#define bFM3_INTREQ_IRQ31MON_BTINT12           *((volatile unsigned int*)(0x42621230UL))
#define bFM3_INTREQ_IRQ31MON_BTINT13           *((volatile unsigned int*)(0x42621234UL))
#define bFM3_INTREQ_IRQ31MON_BTINT14           *((volatile unsigned int*)(0x42621238UL))
#define bFM3_INTREQ_IRQ31MON_BTINT15           *((volatile unsigned int*)(0x4262123CUL))
#define bFM0P_INTREQ_IRQ31MON_FLASHINT         *((volatile unsigned int*)(0x4262126CUL))

/* GPIO registers */
#define bFM0P_GPIO_PFR0_P00                     *((volatile unsigned int*)(0x42660000UL))
#define bFM0P_GPIO_PFR0_P01                     *((volatile unsigned int*)(0x42660004UL))
#define bFM0P_GPIO_PFR0_P02                     *((volatile unsigned int*)(0x42660008UL))
#define bFM0P_GPIO_PFR0_P03                     *((volatile unsigned int*)(0x4266000CUL))
#define bFM0P_GPIO_PFR0_P04                     *((volatile unsigned int*)(0x42660010UL))
#define bFM0P_GPIO_PFR0_P0F                     *((volatile unsigned int*)(0x4266003CUL))
#define bFM0P_GPIO_PFR1_P10                     *((volatile unsigned int*)(0x42660080UL))
#define bFM0P_GPIO_PFR1_P11                     *((volatile unsigned int*)(0x42660084UL))
#define bFM0P_GPIO_PFR1_P12                     *((volatile unsigned int*)(0x42660088UL))
#define bFM0P_GPIO_PFR1_P13                     *((volatile unsigned int*)(0x4266008CUL))
#define bFM0P_GPIO_PFR1_P14                     *((volatile unsigned int*)(0x42660090UL))
#define bFM0P_GPIO_PFR1_P15                     *((volatile unsigned int*)(0x42660094UL))
#define bFM0P_GPIO_PFR2_P21                     *((volatile unsigned int*)(0x42660104UL))
#define bFM0P_GPIO_PFR2_P22                     *((volatile unsigned int*)(0x42660108UL))
#define bFM0P_GPIO_PFR2_P23                     *((volatile unsigned int*)(0x4266010CUL))
#define bFM0P_GPIO_PFR3_P39                     *((volatile unsigned int*)(0x426601A4UL))
#define bFM0P_GPIO_PFR3_P3A                     *((volatile unsigned int*)(0x426601A8UL))
#define bFM0P_GPIO_PFR3_P3B                     *((volatile unsigned int*)(0x426601ACUL))
#define bFM0P_GPIO_PFR3_P3C                     *((volatile unsigned int*)(0x426601B0UL))
#define bFM0P_GPIO_PFR3_P3D                     *((volatile unsigned int*)(0x426601B4UL))
#define bFM0P_GPIO_PFR3_P3E                     *((volatile unsigned int*)(0x426601B8UL))
#define bFM0P_GPIO_PFR3_P3F                     *((volatile unsigned int*)(0x426601BCUL))
#define bFM0P_GPIO_PFR4_P46                     *((volatile unsigned int*)(0x42660218UL))
#define bFM0P_GPIO_PFR4_P47                     *((volatile unsigned int*)(0x4266021CUL))
#define bFM0P_GPIO_PFR4_P49                     *((volatile unsigned int*)(0x42660224UL))
#define bFM0P_GPIO_PFR4_P4A                     *((volatile unsigned int*)(0x42660228UL))
#define bFM0P_GPIO_PFR5_P50                     *((volatile unsigned int*)(0x42660280UL))
#define bFM0P_GPIO_PFR5_P51                     *((volatile unsigned int*)(0x42660284UL))
#define bFM0P_GPIO_PFR5_P52                     *((volatile unsigned int*)(0x42660288UL))
#define bFM0P_GPIO_PFR6_P60                     *((volatile unsigned int*)(0x42660300UL))
#define bFM0P_GPIO_PFR6_P61                     *((volatile unsigned int*)(0x42660304UL))
#define bFM0P_GPIO_PFR8_P80                     *((volatile unsigned int*)(0x42660400UL))
#define bFM0P_GPIO_PFR8_P81                     *((volatile unsigned int*)(0x42660404UL))
#define bFM0P_GPIO_PFR8_P82                     *((volatile unsigned int*)(0x42660408UL))
#define bFM0P_GPIO_PFRE_PE0                     *((volatile unsigned int*)(0x42660700UL))
#define bFM0P_GPIO_PFRE_PE2                     *((volatile unsigned int*)(0x42660708UL))
#define bFM0P_GPIO_PFRE_PE3                     *((volatile unsigned int*)(0x4266070CUL))
#define bFM0P_GPIO_PCR0_P00                     *((volatile unsigned int*)(0x42662000UL))
#define bFM0P_GPIO_PCR0_P01                     *((volatile unsigned int*)(0x42662004UL))
#define bFM0P_GPIO_PCR0_P02                     *((volatile unsigned int*)(0x42662008UL))
#define bFM0P_GPIO_PCR0_P03                     *((volatile unsigned int*)(0x4266200CUL))
#define bFM0P_GPIO_PCR0_P04                     *((volatile unsigned int*)(0x42662010UL))
#define bFM0P_GPIO_PCR0_P0F                     *((volatile unsigned int*)(0x4266203CUL))
#define bFM0P_GPIO_PCR1_P10                     *((volatile unsigned int*)(0x42662080UL))
#define bFM0P_GPIO_PCR1_P11                     *((volatile unsigned int*)(0x42662084UL))
#define bFM0P_GPIO_PCR1_P12                     *((volatile unsigned int*)(0x42662088UL))
#define bFM0P_GPIO_PCR1_P13                     *((volatile unsigned int*)(0x4266208CUL))
#define bFM0P_GPIO_PCR1_P14                     *((volatile unsigned int*)(0x42662090UL))
#define bFM0P_GPIO_PCR1_P15                     *((volatile unsigned int*)(0x42662094UL))
#define bFM0P_GPIO_PCR2_P21                     *((volatile unsigned int*)(0x42662104UL))
#define bFM0P_GPIO_PCR2_P22                     *((volatile unsigned int*)(0x42662108UL))
#define bFM0P_GPIO_PCR2_P23                     *((volatile unsigned int*)(0x4266210CUL))
#define bFM0P_GPIO_PCR3_P39                     *((volatile unsigned int*)(0x426621A4UL))
#define bFM0P_GPIO_PCR3_P3A                     *((volatile unsigned int*)(0x426621A8UL))
#define bFM0P_GPIO_PCR3_P3B                     *((volatile unsigned int*)(0x426621ACUL))
#define bFM0P_GPIO_PCR3_P3C                     *((volatile unsigned int*)(0x426621B0UL))
#define bFM0P_GPIO_PCR3_P3D                     *((volatile unsigned int*)(0x426621B4UL))
#define bFM0P_GPIO_PCR3_P3E                     *((volatile unsigned int*)(0x426621B8UL))
#define bFM0P_GPIO_PCR3_P3F                     *((volatile unsigned int*)(0x426621BCUL))
#define bFM0P_GPIO_PCR4_P46                     *((volatile unsigned int*)(0x42662218UL))
#define bFM0P_GPIO_PCR4_P47                     *((volatile unsigned int*)(0x4266221CUL))
#define bFM0P_GPIO_PCR4_P49                     *((volatile unsigned int*)(0x42662224UL))
#define bFM0P_GPIO_PCR4_P4A                     *((volatile unsigned int*)(0x42662228UL))
#define bFM0P_GPIO_PCR5_P50                     *((volatile unsigned int*)(0x42662280UL))
#define bFM0P_GPIO_PCR5_P51                     *((volatile unsigned int*)(0x42662284UL))
#define bFM0P_GPIO_PCR5_P52                     *((volatile unsigned int*)(0x42662288UL))
#define bFM0P_GPIO_PCR6_P60                     *((volatile unsigned int*)(0x42662300UL))
#define bFM0P_GPIO_PCR6_P61                     *((volatile unsigned int*)(0x42662304UL))
#define bFM0P_GPIO_PCR8_P80                     *((volatile unsigned int*)(0x42662400UL))
#define bFM0P_GPIO_PCR8_P81                     *((volatile unsigned int*)(0x42662404UL))
#define bFM0P_GPIO_PCR8_P82                     *((volatile unsigned int*)(0x42662408UL))
#define bFM0P_GPIO_PCRE_PE0                     *((volatile unsigned int*)(0x42662700UL))
#define bFM0P_GPIO_PCRE_PE2                     *((volatile unsigned int*)(0x42662708UL))
#define bFM0P_GPIO_PCRE_PE3                     *((volatile unsigned int*)(0x4266270CUL))
#define bFM0P_GPIO_DDR0_P00                     *((volatile unsigned int*)(0x42664000UL))
#define bFM0P_GPIO_DDR0_P01                     *((volatile unsigned int*)(0x42664004UL))
#define bFM0P_GPIO_DDR0_P02                     *((volatile unsigned int*)(0x42664008UL))
#define bFM0P_GPIO_DDR0_P03                     *((volatile unsigned int*)(0x4266400CUL))
#define bFM0P_GPIO_DDR0_P04                     *((volatile unsigned int*)(0x42664010UL))
#define bFM0P_GPIO_DDR0_P0F                     *((volatile unsigned int*)(0x4266403CUL))
#define bFM0P_GPIO_DDR1_P10                     *((volatile unsigned int*)(0x42664080UL))
#define bFM0P_GPIO_DDR1_P11                     *((volatile unsigned int*)(0x42664084UL))
#define bFM0P_GPIO_DDR1_P12                     *((volatile unsigned int*)(0x42664088UL))
#define bFM0P_GPIO_DDR1_P13                     *((volatile unsigned int*)(0x4266408CUL))
#define bFM0P_GPIO_DDR1_P14                     *((volatile unsigned int*)(0x42664090UL))
#define bFM0P_GPIO_DDR1_P15                     *((volatile unsigned int*)(0x42664094UL))
#define bFM0P_GPIO_DDR2_P21                     *((volatile unsigned int*)(0x42664104UL))
#define bFM0P_GPIO_DDR2_P22                     *((volatile unsigned int*)(0x42664108UL))
#define bFM0P_GPIO_DDR2_P23                     *((volatile unsigned int*)(0x4266410CUL))
#define bFM0P_GPIO_DDR3_P39                     *((volatile unsigned int*)(0x426641A4UL))
#define bFM0P_GPIO_DDR3_P3A                     *((volatile unsigned int*)(0x426641A8UL))
#define bFM0P_GPIO_DDR3_P3B                     *((volatile unsigned int*)(0x426641ACUL))
#define bFM0P_GPIO_DDR3_P3C                     *((volatile unsigned int*)(0x426641B0UL))
#define bFM0P_GPIO_DDR3_P3D                     *((volatile unsigned int*)(0x426641B4UL))
#define bFM0P_GPIO_DDR3_P3E                     *((volatile unsigned int*)(0x426641B8UL))
#define bFM0P_GPIO_DDR3_P3F                     *((volatile unsigned int*)(0x426641BCUL))
#define bFM0P_GPIO_DDR4_P46                     *((volatile unsigned int*)(0x42664218UL))
#define bFM0P_GPIO_DDR4_P47                     *((volatile unsigned int*)(0x4266421CUL))
#define bFM0P_GPIO_DDR4_P49                     *((volatile unsigned int*)(0x42664224UL))
#define bFM0P_GPIO_DDR4_P4A                     *((volatile unsigned int*)(0x42664228UL))
#define bFM0P_GPIO_DDR5_P50                     *((volatile unsigned int*)(0x42664280UL))
#define bFM0P_GPIO_DDR5_P51                     *((volatile unsigned int*)(0x42664284UL))
#define bFM0P_GPIO_DDR5_P52                     *((volatile unsigned int*)(0x42664288UL))
#define bFM0P_GPIO_DDR6_P60                     *((volatile unsigned int*)(0x42664300UL))
#define bFM0P_GPIO_DDR6_P61                     *((volatile unsigned int*)(0x42664304UL))
#define bFM0P_GPIO_DDR8_P80                     *((volatile unsigned int*)(0x42664400UL))
#define bFM0P_GPIO_DDR8_P81                     *((volatile unsigned int*)(0x42664404UL))
#define bFM0P_GPIO_DDR8_P82                     *((volatile unsigned int*)(0x42664408UL))
#define bFM0P_GPIO_DDRE_PE0                     *((volatile unsigned int*)(0x42664700UL))
#define bFM0P_GPIO_DDRE_PE2                     *((volatile unsigned int*)(0x42664708UL))
#define bFM0P_GPIO_DDRE_PE3                     *((volatile unsigned int*)(0x4266470CUL))
#define bFM0P_GPIO_PDIR0_P00                    *((volatile unsigned int*)(0x42666000UL))
#define bFM0P_GPIO_PDIR0_P01                    *((volatile unsigned int*)(0x42666004UL))
#define bFM0P_GPIO_PDIR0_P02                    *((volatile unsigned int*)(0x42666008UL))
#define bFM0P_GPIO_PDIR0_P03                    *((volatile unsigned int*)(0x4266600CUL))
#define bFM0P_GPIO_PDIR0_P04                    *((volatile unsigned int*)(0x42666010UL))
#define bFM0P_GPIO_PDIR0_P0F                    *((volatile unsigned int*)(0x4266603CUL))
#define bFM0P_GPIO_PDIR1_P10                    *((volatile unsigned int*)(0x42666080UL))
#define bFM0P_GPIO_PDIR1_P11                    *((volatile unsigned int*)(0x42666084UL))
#define bFM0P_GPIO_PDIR1_P12                    *((volatile unsigned int*)(0x42666088UL))
#define bFM0P_GPIO_PDIR1_P13                    *((volatile unsigned int*)(0x4266608CUL))
#define bFM0P_GPIO_PDIR1_P14                    *((volatile unsigned int*)(0x42666090UL))
#define bFM0P_GPIO_PDIR1_P15                    *((volatile unsigned int*)(0x42666094UL))
#define bFM0P_GPIO_PDIR2_P21                    *((volatile unsigned int*)(0x42666104UL))
#define bFM0P_GPIO_PDIR2_P22                    *((volatile unsigned int*)(0x42666108UL))
#define bFM0P_GPIO_PDIR2_P23                    *((volatile unsigned int*)(0x4266610CUL))
#define bFM0P_GPIO_PDIR3_P39                    *((volatile unsigned int*)(0x426661A4UL))
#define bFM0P_GPIO_PDIR3_P3A                    *((volatile unsigned int*)(0x426661A8UL))
#define bFM0P_GPIO_PDIR3_P3B                    *((volatile unsigned int*)(0x426661ACUL))
#define bFM0P_GPIO_PDIR3_P3C                    *((volatile unsigned int*)(0x426661B0UL))
#define bFM0P_GPIO_PDIR3_P3D                    *((volatile unsigned int*)(0x426661B4UL))
#define bFM0P_GPIO_PDIR3_P3E                    *((volatile unsigned int*)(0x426661B8UL))
#define bFM0P_GPIO_PDIR3_P3F                    *((volatile unsigned int*)(0x426661BCUL))
#define bFM0P_GPIO_PDIR4_P46                    *((volatile unsigned int*)(0x42666218UL))
#define bFM0P_GPIO_PDIR4_P47                    *((volatile unsigned int*)(0x4266621CUL))
#define bFM0P_GPIO_PDIR4_P49                    *((volatile unsigned int*)(0x42666224UL))
#define bFM0P_GPIO_PDIR4_P4A                    *((volatile unsigned int*)(0x42666228UL))
#define bFM0P_GPIO_PDIR5_P50                    *((volatile unsigned int*)(0x42666280UL))
#define bFM0P_GPIO_PDIR5_P51                    *((volatile unsigned int*)(0x42666284UL))
#define bFM0P_GPIO_PDIR5_P52                    *((volatile unsigned int*)(0x42666288UL))
#define bFM0P_GPIO_PDIR6_P60                    *((volatile unsigned int*)(0x42666300UL))
#define bFM0P_GPIO_PDIR6_P61                    *((volatile unsigned int*)(0x42666304UL))
#define bFM0P_GPIO_PDIR8_P80                    *((volatile unsigned int*)(0x42666400UL))
#define bFM0P_GPIO_PDIR8_P81                    *((volatile unsigned int*)(0x42666404UL))
#define bFM0P_GPIO_PDIR8_P82                    *((volatile unsigned int*)(0x42666408UL))
#define bFM0P_GPIO_PDIRE_PE0                    *((volatile unsigned int*)(0x42666700UL))
#define bFM0P_GPIO_PDIRE_PE2                    *((volatile unsigned int*)(0x42666708UL))
#define bFM0P_GPIO_PDIRE_PE3                    *((volatile unsigned int*)(0x4266670CUL))
#define bFM0P_GPIO_PDOR0_P00                    *((volatile unsigned int*)(0x42668000UL))
#define bFM0P_GPIO_PDOR0_P01                    *((volatile unsigned int*)(0x42668004UL))
#define bFM0P_GPIO_PDOR0_P02                    *((volatile unsigned int*)(0x42668008UL))
#define bFM0P_GPIO_PDOR0_P03                    *((volatile unsigned int*)(0x4266800CUL))
#define bFM0P_GPIO_PDOR0_P04                    *((volatile unsigned int*)(0x42668010UL))
#define bFM0P_GPIO_PDOR0_P0F                    *((volatile unsigned int*)(0x4266803CUL))
#define bFM0P_GPIO_PDOR1_P10                    *((volatile unsigned int*)(0x42668080UL))
#define bFM0P_GPIO_PDOR1_P11                    *((volatile unsigned int*)(0x42668084UL))
#define bFM0P_GPIO_PDOR1_P12                    *((volatile unsigned int*)(0x42668088UL))
#define bFM0P_GPIO_PDOR1_P13                    *((volatile unsigned int*)(0x4266808CUL))
#define bFM0P_GPIO_PDOR1_P14                    *((volatile unsigned int*)(0x42668090UL))
#define bFM0P_GPIO_PDOR1_P15                    *((volatile unsigned int*)(0x42668094UL))
#define bFM0P_GPIO_PDOR2_P21                    *((volatile unsigned int*)(0x42668104UL))
#define bFM0P_GPIO_PDOR2_P22                    *((volatile unsigned int*)(0x42668108UL))
#define bFM0P_GPIO_PDOR2_P23                    *((volatile unsigned int*)(0x4266810CUL))
#define bFM0P_GPIO_PDOR3_P39                    *((volatile unsigned int*)(0x426681A4UL))
#define bFM0P_GPIO_PDOR3_P3A                    *((volatile unsigned int*)(0x426681A8UL))
#define bFM0P_GPIO_PDOR3_P3B                    *((volatile unsigned int*)(0x426681ACUL))
#define bFM0P_GPIO_PDOR3_P3C                    *((volatile unsigned int*)(0x426681B0UL))
#define bFM0P_GPIO_PDOR3_P3D                    *((volatile unsigned int*)(0x426681B4UL))
#define bFM0P_GPIO_PDOR3_P3E                    *((volatile unsigned int*)(0x426681B8UL))
#define bFM0P_GPIO_PDOR3_P3F                    *((volatile unsigned int*)(0x426681BCUL))
#define bFM0P_GPIO_PDOR4_P46                    *((volatile unsigned int*)(0x42668218UL))
#define bFM0P_GPIO_PDOR4_P47                    *((volatile unsigned int*)(0x4266821CUL))
#define bFM0P_GPIO_PDOR4_P49                    *((volatile unsigned int*)(0x42668224UL))
#define bFM0P_GPIO_PDOR4_P4A                    *((volatile unsigned int*)(0x42668228UL))
#define bFM0P_GPIO_PDOR5_P50                    *((volatile unsigned int*)(0x42668280UL))
#define bFM0P_GPIO_PDOR5_P51                    *((volatile unsigned int*)(0x42668284UL))
#define bFM0P_GPIO_PDOR5_P52                    *((volatile unsigned int*)(0x42668288UL))
#define bFM0P_GPIO_PDOR6_P60                    *((volatile unsigned int*)(0x42668300UL))
#define bFM0P_GPIO_PDOR6_P61                    *((volatile unsigned int*)(0x42668304UL))
#define bFM0P_GPIO_PDOR8_P80                    *((volatile unsigned int*)(0x42668400UL))
#define bFM0P_GPIO_PDOR8_P81                    *((volatile unsigned int*)(0x42668404UL))
#define bFM0P_GPIO_PDOR8_P82                    *((volatile unsigned int*)(0x42668408UL))
#define bFM0P_GPIO_PDORE_PE0                    *((volatile unsigned int*)(0x42668700UL))
#define bFM0P_GPIO_PDORE_PE2                    *((volatile unsigned int*)(0x42668708UL))
#define bFM0P_GPIO_PDORE_PE3                    *((volatile unsigned int*)(0x4266870CUL))
#define bFM0P_GPIO_ADE_AN00                     *((volatile unsigned int*)(0x4266A000UL))
#define bFM0P_GPIO_ADE_AN01                     *((volatile unsigned int*)(0x4266A004UL))
#define bFM0P_GPIO_ADE_AN02                     *((volatile unsigned int*)(0x4266A008UL))
#define bFM0P_GPIO_ADE_AN03                     *((volatile unsigned int*)(0x4266A00CUL))
#define bFM0P_GPIO_ADE_AN04                     *((volatile unsigned int*)(0x4266A010UL))
#define bFM0P_GPIO_ADE_AN05                     *((volatile unsigned int*)(0x4266A014UL))
#define bFM0P_GPIO_ADE_AN06                     *((volatile unsigned int*)(0x4266A018UL))
#define bFM0P_GPIO_ADE_AN07                     *((volatile unsigned int*)(0x4266A01CUL))
#define bFM0P_GPIO_SPSR_SUBXC0                  *((volatile unsigned int*)(0x4266B000UL))
#define bFM0P_GPIO_SPSR_SUBXC1                  *((volatile unsigned int*)(0x4266B004UL))
#define bFM0P_GPIO_SPSR_MAINXC0                 *((volatile unsigned int*)(0x4266B008UL))
#define bFM0P_GPIO_SPSR_MAINXC1                 *((volatile unsigned int*)(0x4266B00CUL))
#define bFM0P_GPIO_EPFR00_NMIS                  *((volatile unsigned int*)(0x4266C000UL))
#define bFM0P_GPIO_EPFR00_CROUTE0               *((volatile unsigned int*)(0x4266C004UL))
#define bFM0P_GPIO_EPFR00_CROUTE1               *((volatile unsigned int*)(0x4266C008UL))
#define bFM0P_GPIO_EPFR00_RTCCOE0               *((volatile unsigned int*)(0x4266C010UL))
#define bFM0P_GPIO_EPFR00_RTCCOE1               *((volatile unsigned int*)(0x4266C014UL))
#define bFM0P_GPIO_EPFR00_SUBOUTE0              *((volatile unsigned int*)(0x4266C018UL))
#define bFM0P_GPIO_EPFR00_SUBOUTE1              *((volatile unsigned int*)(0x4266C01CUL))
#define bFM0P_GPIO_EPFR00_SWDEN                 *((volatile unsigned int*)(0x4266C040UL))
#define bFM0P_GPIO_EPFR01_RTO00E0               *((volatile unsigned int*)(0x4266C080UL))
#define bFM0P_GPIO_EPFR01_RTO00E1               *((volatile unsigned int*)(0x4266C084UL))
#define bFM0P_GPIO_EPFR01_RTO01E0               *((volatile unsigned int*)(0x4266C088UL))
#define bFM0P_GPIO_EPFR01_RTO01E1               *((volatile unsigned int*)(0x4266C08CUL))
#define bFM0P_GPIO_EPFR01_RTO02E0               *((volatile unsigned int*)(0x4266C090UL))
#define bFM0P_GPIO_EPFR01_RTO02E1               *((volatile unsigned int*)(0x4266C094UL))
#define bFM0P_GPIO_EPFR01_RTO03E0               *((volatile unsigned int*)(0x4266C098UL))
#define bFM0P_GPIO_EPFR01_RTO03E1               *((volatile unsigned int*)(0x4266C09CUL))
#define bFM0P_GPIO_EPFR01_RTO04E0               *((volatile unsigned int*)(0x4266C0A0UL))
#define bFM0P_GPIO_EPFR01_RTO04E1               *((volatile unsigned int*)(0x4266C0A4UL))
#define bFM0P_GPIO_EPFR01_RTO05E0               *((volatile unsigned int*)(0x4266C0A8UL))
#define bFM0P_GPIO_EPFR01_RTO05E1               *((volatile unsigned int*)(0x4266C0ACUL))
#define bFM0P_GPIO_EPFR01_DTTI0C                *((volatile unsigned int*)(0x4266C0B0UL))
#define bFM0P_GPIO_EPFR01_IGTRG0                *((volatile unsigned int*)(0x4266C0B4UL))
#define bFM0P_GPIO_EPFR01_DTTI0S0               *((volatile unsigned int*)(0x4266C0C0UL))
#define bFM0P_GPIO_EPFR01_DTTI0S1               *((volatile unsigned int*)(0x4266C0C4UL))
#define bFM0P_GPIO_EPFR01_FRCK0S0               *((volatile unsigned int*)(0x4266C0C8UL))
#define bFM0P_GPIO_EPFR01_FRCK0S1               *((volatile unsigned int*)(0x4266C0CCUL))
#define bFM0P_GPIO_EPFR01_IC00S0                *((volatile unsigned int*)(0x4266C0D0UL))
#define bFM0P_GPIO_EPFR01_IC00S1                *((volatile unsigned int*)(0x4266C0D4UL))
#define bFM0P_GPIO_EPFR01_IC00S2                *((volatile unsigned int*)(0x4266C0D8UL))
#define bFM0P_GPIO_EPFR01_IC01S0                *((volatile unsigned int*)(0x4266C0DCUL))
#define bFM0P_GPIO_EPFR01_IC01S1                *((volatile unsigned int*)(0x4266C0E0UL))
#define bFM0P_GPIO_EPFR01_IC01S2                *((volatile unsigned int*)(0x4266C0E4UL))
#define bFM0P_GPIO_EPFR01_IC02S0                *((volatile unsigned int*)(0x4266C0E8UL))
#define bFM0P_GPIO_EPFR01_IC02S1                *((volatile unsigned int*)(0x4266C0ECUL))
#define bFM0P_GPIO_EPFR01_IC02S2                *((volatile unsigned int*)(0x4266C0F0UL))
#define bFM0P_GPIO_EPFR01_IC03S0                *((volatile unsigned int*)(0x4266C0F4UL))
#define bFM0P_GPIO_EPFR01_IC03S1                *((volatile unsigned int*)(0x4266C0F8UL))
#define bFM0P_GPIO_EPFR01_IC03S2                *((volatile unsigned int*)(0x4266C0FCUL))
#define bFM0P_GPIO_EPFR02_RTO10E0               *((volatile unsigned int*)(0x4266C100UL))
#define bFM0P_GPIO_EPFR02_RTO10E1               *((volatile unsigned int*)(0x4266C104UL))
#define bFM0P_GPIO_EPFR02_RTO11E0               *((volatile unsigned int*)(0x4266C108UL))
#define bFM0P_GPIO_EPFR02_RTO11E1               *((volatile unsigned int*)(0x4266C10CUL))
#define bFM0P_GPIO_EPFR02_RTO12E0               *((volatile unsigned int*)(0x4266C110UL))
#define bFM0P_GPIO_EPFR02_RTO12E1               *((volatile unsigned int*)(0x4266C114UL))
#define bFM0P_GPIO_EPFR02_RTO13E0               *((volatile unsigned int*)(0x4266C118UL))
#define bFM0P_GPIO_EPFR02_RTO13E1               *((volatile unsigned int*)(0x4266C11CUL))
#define bFM0P_GPIO_EPFR02_RTO14E0               *((volatile unsigned int*)(0x4266C120UL))
#define bFM0P_GPIO_EPFR02_RTO14E1               *((volatile unsigned int*)(0x4266C124UL))
#define bFM0P_GPIO_EPFR02_RTO15E0               *((volatile unsigned int*)(0x4266C128UL))
#define bFM0P_GPIO_EPFR02_RTO15E1               *((volatile unsigned int*)(0x4266C12CUL))
#define bFM0P_GPIO_EPFR02_DTTI1C                *((volatile unsigned int*)(0x4266C130UL))
#define bFM0P_GPIO_EPFR02_DTTI1S0               *((volatile unsigned int*)(0x4266C140UL))
#define bFM0P_GPIO_EPFR02_DTTI1S1               *((volatile unsigned int*)(0x4266C144UL))
#define bFM0P_GPIO_EPFR02_FRCK1S0               *((volatile unsigned int*)(0x4266C148UL))
#define bFM0P_GPIO_EPFR02_FRCK1S1               *((volatile unsigned int*)(0x4266C14CUL))
#define bFM0P_GPIO_EPFR02_IC10S0                *((volatile unsigned int*)(0x4266C150UL))
#define bFM0P_GPIO_EPFR02_IC10S1                *((volatile unsigned int*)(0x4266C154UL))
#define bFM0P_GPIO_EPFR02_IC10S2                *((volatile unsigned int*)(0x4266C158UL))
#define bFM0P_GPIO_EPFR02_IC11S0                *((volatile unsigned int*)(0x4266C15CUL))
#define bFM0P_GPIO_EPFR02_IC11S1                *((volatile unsigned int*)(0x4266C160UL))
#define bFM0P_GPIO_EPFR02_IC11S2                *((volatile unsigned int*)(0x4266C164UL))
#define bFM0P_GPIO_EPFR02_IC12S0                *((volatile unsigned int*)(0x4266C168UL))
#define bFM0P_GPIO_EPFR02_IC12S1                *((volatile unsigned int*)(0x4266C16CUL))
#define bFM0P_GPIO_EPFR02_IC12S2                *((volatile unsigned int*)(0x4266C170UL))
#define bFM0P_GPIO_EPFR02_IC13S0                *((volatile unsigned int*)(0x4266C174UL))
#define bFM0P_GPIO_EPFR02_IC13S1                *((volatile unsigned int*)(0x4266C178UL))
#define bFM0P_GPIO_EPFR02_IC13S2                *((volatile unsigned int*)(0x4266C17CUL))
#define bFM0P_GPIO_EPFR03_RTO20E0               *((volatile unsigned int*)(0x4266C180UL))
#define bFM0P_GPIO_EPFR03_RTO20E1               *((volatile unsigned int*)(0x4266C184UL))
#define bFM0P_GPIO_EPFR03_RTO21E0               *((volatile unsigned int*)(0x4266C188UL))
#define bFM0P_GPIO_EPFR03_RTO21E1               *((volatile unsigned int*)(0x4266C18CUL))
#define bFM0P_GPIO_EPFR03_RTO22E0               *((volatile unsigned int*)(0x4266C190UL))
#define bFM0P_GPIO_EPFR03_RTO22E1               *((volatile unsigned int*)(0x4266C194UL))
#define bFM0P_GPIO_EPFR03_RTO23E0               *((volatile unsigned int*)(0x4266C198UL))
#define bFM0P_GPIO_EPFR03_RTO23E1               *((volatile unsigned int*)(0x4266C19CUL))
#define bFM0P_GPIO_EPFR03_RTO24E0               *((volatile unsigned int*)(0x4266C1A0UL))
#define bFM0P_GPIO_EPFR03_RTO24E1               *((volatile unsigned int*)(0x4266C1A4UL))
#define bFM0P_GPIO_EPFR03_RTO25E0               *((volatile unsigned int*)(0x4266C1A8UL))
#define bFM0P_GPIO_EPFR03_RTO25E1               *((volatile unsigned int*)(0x4266C1ACUL))
#define bFM0P_GPIO_EPFR03_DTTI2C                *((volatile unsigned int*)(0x4266C1B0UL))
#define bFM0P_GPIO_EPFR03_DTTI2S0               *((volatile unsigned int*)(0x4266C1C0UL))
#define bFM0P_GPIO_EPFR03_DTTI2S1               *((volatile unsigned int*)(0x4266C1C4UL))
#define bFM0P_GPIO_EPFR03_FRCK2S0               *((volatile unsigned int*)(0x4266C1C8UL))
#define bFM0P_GPIO_EPFR03_FRCK2S1               *((volatile unsigned int*)(0x4266C1CCUL))
#define bFM0P_GPIO_EPFR03_IC20S0                *((volatile unsigned int*)(0x4266C1D0UL))
#define bFM0P_GPIO_EPFR03_IC20S1                *((volatile unsigned int*)(0x4266C1D4UL))
#define bFM0P_GPIO_EPFR03_IC20S2                *((volatile unsigned int*)(0x4266C1D8UL))
#define bFM0P_GPIO_EPFR03_IC21S0                *((volatile unsigned int*)(0x4266C1DCUL))
#define bFM0P_GPIO_EPFR03_IC21S1                *((volatile unsigned int*)(0x4266C1E0UL))
#define bFM0P_GPIO_EPFR03_IC21S2                *((volatile unsigned int*)(0x4266C1E4UL))
#define bFM0P_GPIO_EPFR03_IC22S0                *((volatile unsigned int*)(0x4266C1E8UL))
#define bFM0P_GPIO_EPFR03_IC22S1                *((volatile unsigned int*)(0x4266C1ECUL))
#define bFM0P_GPIO_EPFR03_IC22S2                *((volatile unsigned int*)(0x4266C1F0UL))
#define bFM0P_GPIO_EPFR03_IC23S0                *((volatile unsigned int*)(0x4266C1F4UL))
#define bFM0P_GPIO_EPFR03_IC23S1                *((volatile unsigned int*)(0x4266C1F8UL))
#define bFM0P_GPIO_EPFR03_IC23S2                *((volatile unsigned int*)(0x4266C1FCUL))
#define bFM0P_GPIO_EPFR04_TIOA0E0               *((volatile unsigned int*)(0x4266C208UL))
#define bFM0P_GPIO_EPFR04_TIOA0E1               *((volatile unsigned int*)(0x4266C20CUL))
#define bFM0P_GPIO_EPFR04_TIOB0S0               *((volatile unsigned int*)(0x4266C210UL))
#define bFM0P_GPIO_EPFR04_TIOB0S1               *((volatile unsigned int*)(0x4266C214UL))
#define bFM0P_GPIO_EPFR04_TIOB0S2               *((volatile unsigned int*)(0x4266C218UL))
#define bFM0P_GPIO_EPFR04_TIOA1S0               *((volatile unsigned int*)(0x4266C220UL))
#define bFM0P_GPIO_EPFR04_TIOA1S1               *((volatile unsigned int*)(0x4266C224UL))
#define bFM0P_GPIO_EPFR04_TIOA1E0               *((volatile unsigned int*)(0x4266C228UL))
#define bFM0P_GPIO_EPFR04_TIOA1E1               *((volatile unsigned int*)(0x4266C22CUL))
#define bFM0P_GPIO_EPFR04_TIOB1S0               *((volatile unsigned int*)(0x4266C230UL))
#define bFM0P_GPIO_EPFR04_TIOB1S1               *((volatile unsigned int*)(0x4266C234UL))
#define bFM0P_GPIO_EPFR04_TIOA2E0               *((volatile unsigned int*)(0x4266C248UL))
#define bFM0P_GPIO_EPFR04_TIOA2E1               *((volatile unsigned int*)(0x4266C24CUL))
#define bFM0P_GPIO_EPFR04_TIOB2S0               *((volatile unsigned int*)(0x4266C250UL))
#define bFM0P_GPIO_EPFR04_TIOB2S1               *((volatile unsigned int*)(0x4266C254UL))
#define bFM0P_GPIO_EPFR04_TIOA3S0               *((volatile unsigned int*)(0x4266C260UL))
#define bFM0P_GPIO_EPFR04_TIOA3S1               *((volatile unsigned int*)(0x4266C264UL))
#define bFM0P_GPIO_EPFR04_TIOA3E0               *((volatile unsigned int*)(0x4266C268UL))
#define bFM0P_GPIO_EPFR04_TIOA3E1               *((volatile unsigned int*)(0x4266C26CUL))
#define bFM0P_GPIO_EPFR04_TIOB3S0               *((volatile unsigned int*)(0x4266C270UL))
#define bFM0P_GPIO_EPFR04_TIOB3S1               *((volatile unsigned int*)(0x4266C274UL))
#define bFM0P_GPIO_EPFR05_TIOA4E0               *((volatile unsigned int*)(0x4266C288UL))
#define bFM0P_GPIO_EPFR05_TIOA4E1               *((volatile unsigned int*)(0x4266C28CUL))
#define bFM0P_GPIO_EPFR05_TIOB4S0               *((volatile unsigned int*)(0x4266C290UL))
#define bFM0P_GPIO_EPFR05_TIOB4S1               *((volatile unsigned int*)(0x4266C294UL))
#define bFM0P_GPIO_EPFR05_TIOA5S0               *((volatile unsigned int*)(0x4266C2A0UL))
#define bFM0P_GPIO_EPFR05_TIOA5S1               *((volatile unsigned int*)(0x4266C2A4UL))
#define bFM0P_GPIO_EPFR05_TIOA5E0               *((volatile unsigned int*)(0x4266C2A8UL))
#define bFM0P_GPIO_EPFR05_TIOA5E1               *((volatile unsigned int*)(0x4266C2ACUL))
#define bFM0P_GPIO_EPFR05_TIOB5S0               *((volatile unsigned int*)(0x4266C2B0UL))
#define bFM0P_GPIO_EPFR05_TIOB5S1               *((volatile unsigned int*)(0x4266C2B4UL))
#define bFM0P_GPIO_EPFR05_TIOA6E0               *((volatile unsigned int*)(0x4266C2C8UL))
#define bFM0P_GPIO_EPFR05_TIOA6E1               *((volatile unsigned int*)(0x4266C2CCUL))
#define bFM0P_GPIO_EPFR05_TIOB6S0               *((volatile unsigned int*)(0x4266C2D0UL))
#define bFM0P_GPIO_EPFR05_TIOB6S1               *((volatile unsigned int*)(0x4266C2D4UL))
#define bFM0P_GPIO_EPFR05_TIOA7S0               *((volatile unsigned int*)(0x4266C2E0UL))
#define bFM0P_GPIO_EPFR05_TIOA7S1               *((volatile unsigned int*)(0x4266C2E4UL))
#define bFM0P_GPIO_EPFR05_TIOA7E0               *((volatile unsigned int*)(0x4266C2E8UL))
#define bFM0P_GPIO_EPFR05_TIOA7E1               *((volatile unsigned int*)(0x4266C2ECUL))
#define bFM0P_GPIO_EPFR05_TIOB7S0               *((volatile unsigned int*)(0x4266C2F0UL))
#define bFM0P_GPIO_EPFR05_TIOB7S1               *((volatile unsigned int*)(0x4266C2F4UL))
#define bFM0P_GPIO_EPFR06_EINT00S0              *((volatile unsigned int*)(0x4266C300UL))
#define bFM0P_GPIO_EPFR06_EINT00S1              *((volatile unsigned int*)(0x4266C304UL))
#define bFM0P_GPIO_EPFR06_EINT01S0              *((volatile unsigned int*)(0x4266C308UL))
#define bFM0P_GPIO_EPFR06_EINT01S1              *((volatile unsigned int*)(0x4266C30CUL))
#define bFM0P_GPIO_EPFR06_EINT02S0              *((volatile unsigned int*)(0x4266C310UL))
#define bFM0P_GPIO_EPFR06_EINT02S1              *((volatile unsigned int*)(0x4266C314UL))
#define bFM0P_GPIO_EPFR06_EINT03S0              *((volatile unsigned int*)(0x4266C318UL))
#define bFM0P_GPIO_EPFR06_EINT03S1              *((volatile unsigned int*)(0x4266C31CUL))
#define bFM0P_GPIO_EPFR06_EINT04S0              *((volatile unsigned int*)(0x4266C320UL))
#define bFM0P_GPIO_EPFR06_EINT04S1              *((volatile unsigned int*)(0x4266C324UL))
#define bFM0P_GPIO_EPFR06_EINT05S0              *((volatile unsigned int*)(0x4266C328UL))
#define bFM0P_GPIO_EPFR06_EINT05S1              *((volatile unsigned int*)(0x4266C32CUL))
#define bFM0P_GPIO_EPFR06_EINT06S0              *((volatile unsigned int*)(0x4266C330UL))
#define bFM0P_GPIO_EPFR06_EINT06S1              *((volatile unsigned int*)(0x4266C334UL))
#define bFM0P_GPIO_EPFR06_EINT07S0              *((volatile unsigned int*)(0x4266C338UL))
#define bFM0P_GPIO_EPFR06_EINT07S1              *((volatile unsigned int*)(0x4266C33CUL))
#define bFM0P_GPIO_EPFR06_EINT08S0              *((volatile unsigned int*)(0x4266C340UL))
#define bFM0P_GPIO_EPFR06_EINT08S1              *((volatile unsigned int*)(0x4266C344UL))
#define bFM0P_GPIO_EPFR06_EINT09S0              *((volatile unsigned int*)(0x4266C348UL))
#define bFM0P_GPIO_EPFR06_EINT09S1              *((volatile unsigned int*)(0x4266C34CUL))
#define bFM0P_GPIO_EPFR06_EINT10S0              *((volatile unsigned int*)(0x4266C350UL))
#define bFM0P_GPIO_EPFR06_EINT10S1              *((volatile unsigned int*)(0x4266C354UL))
#define bFM0P_GPIO_EPFR06_EINT11S0              *((volatile unsigned int*)(0x4266C358UL))
#define bFM0P_GPIO_EPFR06_EINT11S1              *((volatile unsigned int*)(0x4266C35CUL))
#define bFM0P_GPIO_EPFR06_EINT12S0              *((volatile unsigned int*)(0x4266C360UL))
#define bFM0P_GPIO_EPFR06_EINT12S1              *((volatile unsigned int*)(0x4266C364UL))
#define bFM0P_GPIO_EPFR06_EINT13S0              *((volatile unsigned int*)(0x4266C368UL))
#define bFM0P_GPIO_EPFR06_EINT13S1              *((volatile unsigned int*)(0x4266C36CUL))
#define bFM0P_GPIO_EPFR06_EINT14S0              *((volatile unsigned int*)(0x4266C370UL))
#define bFM0P_GPIO_EPFR06_EINT14S1              *((volatile unsigned int*)(0x4266C374UL))
#define bFM0P_GPIO_EPFR06_EINT15S0              *((volatile unsigned int*)(0x4266C378UL))
#define bFM0P_GPIO_EPFR06_EINT15S1              *((volatile unsigned int*)(0x4266C37CUL))
#define bFM0P_GPIO_EPFR07_SIN0S0                *((volatile unsigned int*)(0x4266C390UL))
#define bFM0P_GPIO_EPFR07_SIN0S1                *((volatile unsigned int*)(0x4266C394UL))
#define bFM0P_GPIO_EPFR07_SOT0B0                *((volatile unsigned int*)(0x4266C398UL))
#define bFM0P_GPIO_EPFR07_SOT0B1                *((volatile unsigned int*)(0x4266C39CUL))
#define bFM0P_GPIO_EPFR07_SCK0B0                *((volatile unsigned int*)(0x4266C3A0UL))
#define bFM0P_GPIO_EPFR07_SCK0B1                *((volatile unsigned int*)(0x4266C3A4UL))
#define bFM0P_GPIO_EPFR07_SIN1S0                *((volatile unsigned int*)(0x4266C3A8UL))
#define bFM0P_GPIO_EPFR07_SIN1S1                *((volatile unsigned int*)(0x4266C3ACUL))
#define bFM0P_GPIO_EPFR07_SOT1B0                *((volatile unsigned int*)(0x4266C3B0UL))
#define bFM0P_GPIO_EPFR07_SOT1B1                *((volatile unsigned int*)(0x4266C3B4UL))
#define bFM0P_GPIO_EPFR07_SCK1B0                *((volatile unsigned int*)(0x4266C3B8UL))
#define bFM0P_GPIO_EPFR07_SCK1B1                *((volatile unsigned int*)(0x4266C3BCUL))
#define bFM0P_GPIO_EPFR07_SIN2S0                *((volatile unsigned int*)(0x4266C3C0UL))
#define bFM0P_GPIO_EPFR07_SIN2S1                *((volatile unsigned int*)(0x4266C3C4UL))
#define bFM0P_GPIO_EPFR07_SOT2B0                *((volatile unsigned int*)(0x4266C3C8UL))
#define bFM0P_GPIO_EPFR07_SOT2B1                *((volatile unsigned int*)(0x4266C3CCUL))
#define bFM0P_GPIO_EPFR07_SCK2B0                *((volatile unsigned int*)(0x4266C3D0UL))
#define bFM0P_GPIO_EPFR07_SCK2B1                *((volatile unsigned int*)(0x4266C3D4UL))
#define bFM0P_GPIO_EPFR07_SIN3S0                *((volatile unsigned int*)(0x4266C3D8UL))
#define bFM0P_GPIO_EPFR07_SIN3S1                *((volatile unsigned int*)(0x4266C3DCUL))
#define bFM0P_GPIO_EPFR07_SOT3B0                *((volatile unsigned int*)(0x4266C3E0UL))
#define bFM0P_GPIO_EPFR07_SOT3B1                *((volatile unsigned int*)(0x4266C3E4UL))
#define bFM0P_GPIO_EPFR07_SCK3B0                *((volatile unsigned int*)(0x4266C3E8UL))
#define bFM0P_GPIO_EPFR07_SCK3B1                *((volatile unsigned int*)(0x4266C3ECUL))
#define bFM0P_GPIO_EPFR08_RTS4E0                *((volatile unsigned int*)(0x4266C400UL))
#define bFM0P_GPIO_EPFR08_RTS4E1                *((volatile unsigned int*)(0x4266C404UL))
#define bFM0P_GPIO_EPFR08_CTS4S0                *((volatile unsigned int*)(0x4266C408UL))
#define bFM0P_GPIO_EPFR08_CTS4S1                *((volatile unsigned int*)(0x4266C40CUL))
#define bFM0P_GPIO_EPFR08_SIN4S0                *((volatile unsigned int*)(0x4266C410UL))
#define bFM0P_GPIO_EPFR08_SIN4S1                *((volatile unsigned int*)(0x4266C414UL))
#define bFM0P_GPIO_EPFR08_SOT4B0                *((volatile unsigned int*)(0x4266C418UL))
#define bFM0P_GPIO_EPFR08_SOT4B1                *((volatile unsigned int*)(0x4266C41CUL))
#define bFM0P_GPIO_EPFR08_SCK4B0                *((volatile unsigned int*)(0x4266C420UL))
#define bFM0P_GPIO_EPFR08_SCK4B1                *((volatile unsigned int*)(0x4266C424UL))
#define bFM0P_GPIO_EPFR08_SIN5S0                *((volatile unsigned int*)(0x4266C428UL))
#define bFM0P_GPIO_EPFR08_SIN5S1                *((volatile unsigned int*)(0x4266C42CUL))
#define bFM0P_GPIO_EPFR08_SOT5B0                *((volatile unsigned int*)(0x4266C430UL))
#define bFM0P_GPIO_EPFR08_SOT5B1                *((volatile unsigned int*)(0x4266C434UL))
#define bFM0P_GPIO_EPFR08_SCK5B0                *((volatile unsigned int*)(0x4266C438UL))
#define bFM0P_GPIO_EPFR08_SCK5B1                *((volatile unsigned int*)(0x4266C43CUL))
#define bFM0P_GPIO_EPFR08_SIN6S0                *((volatile unsigned int*)(0x4266C440UL))
#define bFM0P_GPIO_EPFR08_SIN6S1                *((volatile unsigned int*)(0x4266C444UL))
#define bFM0P_GPIO_EPFR08_SOT6B0                *((volatile unsigned int*)(0x4266C448UL))
#define bFM0P_GPIO_EPFR08_SOT6B1                *((volatile unsigned int*)(0x4266C44CUL))
#define bFM0P_GPIO_EPFR08_SCK6B0                *((volatile unsigned int*)(0x4266C450UL))
#define bFM0P_GPIO_EPFR08_SCK6B1                *((volatile unsigned int*)(0x4266C454UL))
#define bFM0P_GPIO_EPFR08_SIN7S0                *((volatile unsigned int*)(0x4266C458UL))
#define bFM0P_GPIO_EPFR08_SIN7S1                *((volatile unsigned int*)(0x4266C45CUL))
#define bFM0P_GPIO_EPFR08_SOT7B0                *((volatile unsigned int*)(0x4266C460UL))
#define bFM0P_GPIO_EPFR08_SOT7B1                *((volatile unsigned int*)(0x4266C464UL))
#define bFM0P_GPIO_EPFR08_SCK7B0                *((volatile unsigned int*)(0x4266C468UL))
#define bFM0P_GPIO_EPFR08_SCK7B1                *((volatile unsigned int*)(0x4266C46CUL))
#define bFM0P_GPIO_EPFR09_QAIN0S0               *((volatile unsigned int*)(0x4266C480UL))
#define bFM0P_GPIO_EPFR09_QAIN0S1               *((volatile unsigned int*)(0x4266C484UL))
#define bFM0P_GPIO_EPFR09_QBIN0S0               *((volatile unsigned int*)(0x4266C488UL))
#define bFM0P_GPIO_EPFR09_QBIN0S1               *((volatile unsigned int*)(0x4266C48CUL))
#define bFM0P_GPIO_EPFR09_QZIN0S0               *((volatile unsigned int*)(0x4266C490UL))
#define bFM0P_GPIO_EPFR09_QZIN0S1               *((volatile unsigned int*)(0x4266C494UL))
#define bFM0P_GPIO_EPFR09_QAIN1S0               *((volatile unsigned int*)(0x4266C498UL))
#define bFM0P_GPIO_EPFR09_QAIN1S1               *((volatile unsigned int*)(0x4266C49CUL))
#define bFM0P_GPIO_EPFR09_QBIN1S0               *((volatile unsigned int*)(0x4266C4A0UL))
#define bFM0P_GPIO_EPFR09_QBIN1S1               *((volatile unsigned int*)(0x4266C4A4UL))
#define bFM0P_GPIO_EPFR09_QZIN1S0               *((volatile unsigned int*)(0x4266C4A8UL))
#define bFM0P_GPIO_EPFR09_QZIN1S1               *((volatile unsigned int*)(0x4266C4ACUL))
#define bFM0P_GPIO_EPFR09_ADTRG0S0              *((volatile unsigned int*)(0x4266C4B0UL))
#define bFM0P_GPIO_EPFR09_ADTRG0S1              *((volatile unsigned int*)(0x4266C4B4UL))
#define bFM0P_GPIO_EPFR09_ADTRG0S2              *((volatile unsigned int*)(0x4266C4B8UL))
#define bFM0P_GPIO_EPFR09_ADTRG0S3              *((volatile unsigned int*)(0x4266C4BCUL))
#define bFM0P_GPIO_EPFR09_ADTRG1S0              *((volatile unsigned int*)(0x4266C4C0UL))
#define bFM0P_GPIO_EPFR09_ADTRG1S1              *((volatile unsigned int*)(0x4266C4C4UL))
#define bFM0P_GPIO_EPFR09_ADTRG1S2              *((volatile unsigned int*)(0x4266C4C8UL))
#define bFM0P_GPIO_EPFR09_ADTRG1S3              *((volatile unsigned int*)(0x4266C4CCUL))
#define bFM0P_GPIO_EPFR09_ADTRG2S0              *((volatile unsigned int*)(0x4266C4D0UL))
#define bFM0P_GPIO_EPFR09_ADTRG2S1              *((volatile unsigned int*)(0x4266C4D4UL))
#define bFM0P_GPIO_EPFR09_ADTRG2S2              *((volatile unsigned int*)(0x4266C4D8UL))
#define bFM0P_GPIO_EPFR09_ADTRG2S3              *((volatile unsigned int*)(0x4266C4DCUL))
#define bFM0P_GPIO_EPFR09_CRX0S0                *((volatile unsigned int*)(0x4266C4E0UL))
#define bFM0P_GPIO_EPFR09_CRX0S1                *((volatile unsigned int*)(0x4266C4E4UL))
#define bFM0P_GPIO_EPFR09_CTX0E0                *((volatile unsigned int*)(0x4266C4E8UL))
#define bFM0P_GPIO_EPFR09_CTX0E1                *((volatile unsigned int*)(0x4266C4ECUL))
#define bFM0P_GPIO_EPFR09_CRX1S0                *((volatile unsigned int*)(0x4266C4F0UL))
#define bFM0P_GPIO_EPFR09_CRX1S1                *((volatile unsigned int*)(0x4266C4F4UL))
#define bFM0P_GPIO_EPFR09_CTX1E0                *((volatile unsigned int*)(0x4266C4F8UL))
#define bFM0P_GPIO_EPFR09_CTX1E1                *((volatile unsigned int*)(0x4266C4FCUL))
#define bFM0P_GPIO_EPFR12_TIOA8E0               *((volatile unsigned int*)(0x4266C608UL))
#define bFM0P_GPIO_EPFR12_TIOA8E1               *((volatile unsigned int*)(0x4266C60CUL))
#define bFM0P_GPIO_EPFR12_TIOB8S0               *((volatile unsigned int*)(0x4266C610UL))
#define bFM0P_GPIO_EPFR12_TIOB8S1               *((volatile unsigned int*)(0x4266C614UL))
#define bFM0P_GPIO_EPFR12_TIOA9S0               *((volatile unsigned int*)(0x4266C620UL))
#define bFM0P_GPIO_EPFR12_TIOA9S1               *((volatile unsigned int*)(0x4266C624UL))
#define bFM0P_GPIO_EPFR12_TIOA9E0               *((volatile unsigned int*)(0x4266C628UL))
#define bFM0P_GPIO_EPFR12_TIOA9E1               *((volatile unsigned int*)(0x4266C62CUL))
#define bFM0P_GPIO_EPFR12_TIOB9S0               *((volatile unsigned int*)(0x4266C630UL))
#define bFM0P_GPIO_EPFR12_TIOB9S1               *((volatile unsigned int*)(0x4266C634UL))
#define bFM0P_GPIO_EPFR12_TIOA10E0              *((volatile unsigned int*)(0x4266C648UL))
#define bFM0P_GPIO_EPFR12_TIOA10E1              *((volatile unsigned int*)(0x4266C64CUL))
#define bFM0P_GPIO_EPFR12_TIOB10S0              *((volatile unsigned int*)(0x4266C650UL))
#define bFM0P_GPIO_EPFR12_TIOB10S1              *((volatile unsigned int*)(0x4266C654UL))
#define bFM0P_GPIO_EPFR12_TIOA11S0              *((volatile unsigned int*)(0x4266C660UL))
#define bFM0P_GPIO_EPFR12_TIOA11S1              *((volatile unsigned int*)(0x4266C664UL))
#define bFM0P_GPIO_EPFR12_TIOA11E0              *((volatile unsigned int*)(0x4266C668UL))
#define bFM0P_GPIO_EPFR12_TIOA11E1              *((volatile unsigned int*)(0x4266C66CUL))
#define bFM0P_GPIO_EPFR12_TIOB11S0              *((volatile unsigned int*)(0x4266C670UL))
#define bFM0P_GPIO_EPFR12_TIOB11S1              *((volatile unsigned int*)(0x4266C674UL))
#define bFM0P_GPIO_EPFR13_TIOA12E0              *((volatile unsigned int*)(0x4266C688UL))
#define bFM0P_GPIO_EPFR13_TIOA12E1              *((volatile unsigned int*)(0x4266C68CUL))
#define bFM0P_GPIO_EPFR13_TIOB12S0              *((volatile unsigned int*)(0x4266C690UL))
#define bFM0P_GPIO_EPFR13_TIOB12S1              *((volatile unsigned int*)(0x4266C694UL))
#define bFM0P_GPIO_EPFR13_TIOB12S2              *((volatile unsigned int*)(0x4266C698UL))
#define bFM0P_GPIO_EPFR13_TIOA13S0              *((volatile unsigned int*)(0x4266C6A0UL))
#define bFM0P_GPIO_EPFR13_TIOA13S1              *((volatile unsigned int*)(0x4266C6A4UL))
#define bFM0P_GPIO_EPFR13_TIOA13E0              *((volatile unsigned int*)(0x4266C6A8UL))
#define bFM0P_GPIO_EPFR13_TIOA13E1              *((volatile unsigned int*)(0x4266C6ACUL))
#define bFM0P_GPIO_EPFR13_TIOB13S0              *((volatile unsigned int*)(0x4266C6B0UL))
#define bFM0P_GPIO_EPFR13_TIOB13S1              *((volatile unsigned int*)(0x4266C6B4UL))
#define bFM0P_GPIO_EPFR13_TIOA14E0              *((volatile unsigned int*)(0x4266C6C8UL))
#define bFM0P_GPIO_EPFR13_TIOA14E1              *((volatile unsigned int*)(0x4266C6CCUL))
#define bFM0P_GPIO_EPFR13_TIOB14S0              *((volatile unsigned int*)(0x4266C6D0UL))
#define bFM0P_GPIO_EPFR13_TIOB14S1              *((volatile unsigned int*)(0x4266C6D4UL))
#define bFM0P_GPIO_EPFR13_TIOA15S0              *((volatile unsigned int*)(0x4266C6E0UL))
#define bFM0P_GPIO_EPFR13_TIOA15S1              *((volatile unsigned int*)(0x4266C6E4UL))
#define bFM0P_GPIO_EPFR13_TIOA15E0              *((volatile unsigned int*)(0x4266C6E8UL))
#define bFM0P_GPIO_EPFR13_TIOA15E1              *((volatile unsigned int*)(0x4266C6ECUL))
#define bFM0P_GPIO_EPFR13_TIOB15S0              *((volatile unsigned int*)(0x4266C6F0UL))
#define bFM0P_GPIO_EPFR13_TIOB15S1              *((volatile unsigned int*)(0x4266C6F4UL))
#define bFM0P_GPIO_EPFR14_QAIN2S0               *((volatile unsigned int*)(0x4266C700UL))
#define bFM0P_GPIO_EPFR14_QAIN2S1               *((volatile unsigned int*)(0x4266C704UL))
#define bFM0P_GPIO_EPFR14_QBIN2S0               *((volatile unsigned int*)(0x4266C708UL))
#define bFM0P_GPIO_EPFR14_QBIN2S1               *((volatile unsigned int*)(0x4266C70CUL))
#define bFM0P_GPIO_EPFR14_QZIN2S0               *((volatile unsigned int*)(0x4266C710UL))
#define bFM0P_GPIO_EPFR14_QZIN2S1               *((volatile unsigned int*)(0x4266C714UL))
#define bFM0P_GPIO_EPFR15_EINT16S0              *((volatile unsigned int*)(0x4266C780UL))
#define bFM0P_GPIO_EPFR15_EINT16S1              *((volatile unsigned int*)(0x4266C784UL))
#define bFM0P_GPIO_EPFR15_EINT17S0              *((volatile unsigned int*)(0x4266C788UL))
#define bFM0P_GPIO_EPFR15_EINT17S1              *((volatile unsigned int*)(0x4266C78CUL))
#define bFM0P_GPIO_EPFR15_EINT18S0              *((volatile unsigned int*)(0x4266C790UL))
#define bFM0P_GPIO_EPFR15_EINT18S1              *((volatile unsigned int*)(0x4266C794UL))
#define bFM0P_GPIO_EPFR15_EINT19S0              *((volatile unsigned int*)(0x4266C798UL))
#define bFM0P_GPIO_EPFR15_EINT19S1              *((volatile unsigned int*)(0x4266C79CUL))
#define bFM0P_GPIO_EPFR15_EINT20S0              *((volatile unsigned int*)(0x4266C7A0UL))
#define bFM0P_GPIO_EPFR15_EINT20S1              *((volatile unsigned int*)(0x4266C7A4UL))
#define bFM0P_GPIO_EPFR15_EINT21S0              *((volatile unsigned int*)(0x4266C7A8UL))
#define bFM0P_GPIO_EPFR15_EINT21S1              *((volatile unsigned int*)(0x4266C7ACUL))
#define bFM0P_GPIO_EPFR15_EINT22S0              *((volatile unsigned int*)(0x4266C7B0UL))
#define bFM0P_GPIO_EPFR15_EINT22S1              *((volatile unsigned int*)(0x4266C7B4UL))
#define bFM0P_GPIO_EPFR15_EINT23S0              *((volatile unsigned int*)(0x4266C7B8UL))
#define bFM0P_GPIO_EPFR15_EINT23S1              *((volatile unsigned int*)(0x4266C7BCUL))
#define bFM0P_GPIO_EPFR15_EINT24S0              *((volatile unsigned int*)(0x4266C7C0UL))
#define bFM0P_GPIO_EPFR15_EINT24S1              *((volatile unsigned int*)(0x4266C7C4UL))
#define bFM0P_GPIO_EPFR15_EINT25S0              *((volatile unsigned int*)(0x4266C7C8UL))
#define bFM0P_GPIO_EPFR15_EINT25S1              *((volatile unsigned int*)(0x4266C7CCUL))
#define bFM0P_GPIO_EPFR15_EINT26S0              *((volatile unsigned int*)(0x4266C7D0UL))
#define bFM0P_GPIO_EPFR15_EINT26S1              *((volatile unsigned int*)(0x4266C7D4UL))
#define bFM0P_GPIO_EPFR15_EINT27S0              *((volatile unsigned int*)(0x4266C7D8UL))
#define bFM0P_GPIO_EPFR15_EINT27S1              *((volatile unsigned int*)(0x4266C7DCUL))
#define bFM0P_GPIO_EPFR15_EINT28S0              *((volatile unsigned int*)(0x4266C7E0UL))
#define bFM0P_GPIO_EPFR15_EINT28S1              *((volatile unsigned int*)(0x4266C7E4UL))
#define bFM0P_GPIO_EPFR15_EINT29S0              *((volatile unsigned int*)(0x4266C7E8UL))
#define bFM0P_GPIO_EPFR15_EINT29S1              *((volatile unsigned int*)(0x4266C7ECUL))
#define bFM0P_GPIO_EPFR15_EINT30S0              *((volatile unsigned int*)(0x4266C7F0UL))
#define bFM0P_GPIO_EPFR15_EINT30S1              *((volatile unsigned int*)(0x4266C7F4UL))
#define bFM0P_GPIO_EPFR15_EINT31S0              *((volatile unsigned int*)(0x4266C7F8UL))
#define bFM0P_GPIO_EPFR15_EINT31S1              *((volatile unsigned int*)(0x4266C7FCUL))
#define bFM0P_GPIO_EPFR16_SIN8S0                *((volatile unsigned int*)(0x4266C810UL))
#define bFM0P_GPIO_EPFR16_SIN8S1                *((volatile unsigned int*)(0x4266C814UL))
#define bFM0P_GPIO_EPFR16_SOT8B0                *((volatile unsigned int*)(0x4266C818UL))
#define bFM0P_GPIO_EPFR16_SOT8B1                *((volatile unsigned int*)(0x4266C81CUL))
#define bFM0P_GPIO_EPFR16_SCK8B0                *((volatile unsigned int*)(0x4266C820UL))
#define bFM0P_GPIO_EPFR16_SCK8B1                *((volatile unsigned int*)(0x4266C824UL))
#define bFM0P_GPIO_EPFR16_SIN9S0                *((volatile unsigned int*)(0x4266C828UL))
#define bFM0P_GPIO_EPFR16_SIN9S1                *((volatile unsigned int*)(0x4266C82CUL))
#define bFM0P_GPIO_EPFR16_SOT9B0                *((volatile unsigned int*)(0x4266C830UL))
#define bFM0P_GPIO_EPFR16_SOT9B1                *((volatile unsigned int*)(0x4266C834UL))
#define bFM0P_GPIO_EPFR16_SCK9B0                *((volatile unsigned int*)(0x4266C838UL))
#define bFM0P_GPIO_EPFR16_SCK9B1                *((volatile unsigned int*)(0x4266C83CUL))
#define bFM0P_GPIO_EPFR16_SIN10S0               *((volatile unsigned int*)(0x4266C840UL))
#define bFM0P_GPIO_EPFR16_SIN10S1               *((volatile unsigned int*)(0x4266C844UL))
#define bFM0P_GPIO_EPFR16_SOT10B0               *((volatile unsigned int*)(0x4266C848UL))
#define bFM0P_GPIO_EPFR16_SOT10B1               *((volatile unsigned int*)(0x4266C84CUL))
#define bFM0P_GPIO_EPFR16_SCK10B0               *((volatile unsigned int*)(0x4266C850UL))
#define bFM0P_GPIO_EPFR16_SCK10B1               *((volatile unsigned int*)(0x4266C854UL))
#define bFM0P_GPIO_EPFR16_SIN11S0               *((volatile unsigned int*)(0x4266C858UL))
#define bFM0P_GPIO_EPFR16_SIN11S1               *((volatile unsigned int*)(0x4266C85CUL))
#define bFM0P_GPIO_EPFR16_SOT11B0               *((volatile unsigned int*)(0x4266C860UL))
#define bFM0P_GPIO_EPFR16_SOT11B1               *((volatile unsigned int*)(0x4266C864UL))
#define bFM0P_GPIO_EPFR16_SCK11B0               *((volatile unsigned int*)(0x4266C868UL))
#define bFM0P_GPIO_EPFR16_SCK11B1               *((volatile unsigned int*)(0x4266C86CUL))
#define bFM0P_GPIO_EPFR17_SIN12S0               *((volatile unsigned int*)(0x4266C890UL))
#define bFM0P_GPIO_EPFR17_SIN12S1               *((volatile unsigned int*)(0x4266C894UL))
#define bFM0P_GPIO_EPFR17_SOT12B0               *((volatile unsigned int*)(0x4266C898UL))
#define bFM0P_GPIO_EPFR17_SOT12B1               *((volatile unsigned int*)(0x4266C89CUL))
#define bFM0P_GPIO_EPFR17_SCK12B0               *((volatile unsigned int*)(0x4266C8A0UL))
#define bFM0P_GPIO_EPFR17_SCK12B1               *((volatile unsigned int*)(0x4266C8A4UL))
#define bFM0P_GPIO_EPFR17_SIN13S0               *((volatile unsigned int*)(0x4266C8A8UL))
#define bFM0P_GPIO_EPFR17_SIN13S1               *((volatile unsigned int*)(0x4266C8ACUL))
#define bFM0P_GPIO_EPFR17_SOT13B0               *((volatile unsigned int*)(0x4266C8B0UL))
#define bFM0P_GPIO_EPFR17_SOT13B1               *((volatile unsigned int*)(0x4266C8B4UL))
#define bFM0P_GPIO_EPFR17_SCK13B0               *((volatile unsigned int*)(0x4266C8B8UL))
#define bFM0P_GPIO_EPFR17_SCK13B1               *((volatile unsigned int*)(0x4266C8BCUL))
#define bFM0P_GPIO_EPFR17_SIN14S0               *((volatile unsigned int*)(0x4266C8C0UL))
#define bFM0P_GPIO_EPFR17_SIN14S1               *((volatile unsigned int*)(0x4266C8C4UL))
#define bFM0P_GPIO_EPFR17_SOT14B0               *((volatile unsigned int*)(0x4266C8C8UL))
#define bFM0P_GPIO_EPFR17_SOT14B1               *((volatile unsigned int*)(0x4266C8CCUL))
#define bFM0P_GPIO_EPFR17_SCK14B0               *((volatile unsigned int*)(0x4266C8D0UL))
#define bFM0P_GPIO_EPFR17_SCK14B1               *((volatile unsigned int*)(0x4266C8D4UL))
#define bFM0P_GPIO_EPFR17_SIN15S0               *((volatile unsigned int*)(0x4266C8D8UL))
#define bFM0P_GPIO_EPFR17_SIN15S1               *((volatile unsigned int*)(0x4266C8DCUL))
#define bFM0P_GPIO_EPFR17_SOT15B0               *((volatile unsigned int*)(0x4266C8E0UL))
#define bFM0P_GPIO_EPFR17_SOT15B1               *((volatile unsigned int*)(0x4266C8E4UL))
#define bFM0P_GPIO_EPFR17_SCK15B0               *((volatile unsigned int*)(0x4266C8E8UL))
#define bFM0P_GPIO_EPFR17_SCK15B1               *((volatile unsigned int*)(0x4266C8ECUL))
#define bFM0P_GPIO_EPFR18_CECR0B0               *((volatile unsigned int*)(0x4266C900UL))
#define bFM0P_GPIO_EPFR18_CECR0B1               *((volatile unsigned int*)(0x4266C904UL))
#define bFM0P_GPIO_EPFR18_CECR1B0               *((volatile unsigned int*)(0x4266C908UL))
#define bFM0P_GPIO_EPFR18_CECR1B1               *((volatile unsigned int*)(0x4266C90CUL))
#define bFM0P_GPIO_EPFR21_QAIN0S                *((volatile unsigned int*)(0x4266CA80UL))
#define bFM0P_GPIO_EPFR21_QBIN0S                *((volatile unsigned int*)(0x4266CA84UL))
#define bFM0P_GPIO_EPFR21_QZIN0S                *((volatile unsigned int*)(0x4266CA88UL))
#define bFM0P_GPIO_EPFR22_SCS00B0               *((volatile unsigned int*)(0x4266CB00UL))
#define bFM0P_GPIO_EPFR22_SCS00B1               *((volatile unsigned int*)(0x4266CB04UL))
#define bFM0P_GPIO_EPFR22_SCS01E0               *((volatile unsigned int*)(0x4266CB08UL))
#define bFM0P_GPIO_EPFR22_SCS01E1               *((volatile unsigned int*)(0x4266CB0CUL))
#define bFM0P_GPIO_EPFR22_SCS10B0               *((volatile unsigned int*)(0x4266CB10UL))
#define bFM0P_GPIO_EPFR22_SCS10B1               *((volatile unsigned int*)(0x4266CB14UL))
#define bFM0P_GPIO_EPFR22_SCS11E0               *((volatile unsigned int*)(0x4266CB18UL))
#define bFM0P_GPIO_EPFR22_SCS11E1               *((volatile unsigned int*)(0x4266CB1CUL))
#define bFM0P_GPIO_EPFR22_SCS20B0               *((volatile unsigned int*)(0x4266CB20UL))
#define bFM0P_GPIO_EPFR22_SCS20B1               *((volatile unsigned int*)(0x4266CB24UL))
#define bFM0P_GPIO_EPFR22_SCS21E0               *((volatile unsigned int*)(0x4266CB28UL))
#define bFM0P_GPIO_EPFR22_SCS21E1               *((volatile unsigned int*)(0x4266CB2CUL))
#define bFM0P_GPIO_EPFR22_SCS30B0               *((volatile unsigned int*)(0x4266CB30UL))
#define bFM0P_GPIO_EPFR22_SCS30B1               *((volatile unsigned int*)(0x4266CB34UL))
#define bFM0P_GPIO_EPFR22_SCS31E0               *((volatile unsigned int*)(0x4266CB38UL))
#define bFM0P_GPIO_EPFR22_SCS31E1               *((volatile unsigned int*)(0x4266CB3CUL))
#define bFM0P_GPIO_PZR0_P00                     *((volatile unsigned int*)(0x4266E000UL))
#define bFM0P_GPIO_PZR0_P01                     *((volatile unsigned int*)(0x4266E004UL))
#define bFM0P_GPIO_PZR0_P02                     *((volatile unsigned int*)(0x4266E008UL))
#define bFM0P_GPIO_PZR0_P03                     *((volatile unsigned int*)(0x4266E00CUL))
#define bFM0P_GPIO_PZR0_P04                     *((volatile unsigned int*)(0x4266E010UL))
#define bFM0P_GPIO_PZR0_P0F                     *((volatile unsigned int*)(0x4266E03CUL))
#define bFM0P_GPIO_PZR1_P10                     *((volatile unsigned int*)(0x4266E080UL))
#define bFM0P_GPIO_PZR1_P11                     *((volatile unsigned int*)(0x4266E084UL))
#define bFM0P_GPIO_PZR1_P12                     *((volatile unsigned int*)(0x4266E088UL))
#define bFM0P_GPIO_PZR1_P13                     *((volatile unsigned int*)(0x4266E08CUL))
#define bFM0P_GPIO_PZR1_P14                     *((volatile unsigned int*)(0x4266E090UL))
#define bFM0P_GPIO_PZR1_P15                     *((volatile unsigned int*)(0x4266E094UL))
#define bFM0P_GPIO_PZR2_P21                     *((volatile unsigned int*)(0x4266E104UL))
#define bFM0P_GPIO_PZR2_P22                     *((volatile unsigned int*)(0x4266E108UL))
#define bFM0P_GPIO_PZR2_P23                     *((volatile unsigned int*)(0x4266E10CUL))
#define bFM0P_GPIO_PZR3_P39                     *((volatile unsigned int*)(0x4266E1A4UL))
#define bFM0P_GPIO_PZR3_P3A                     *((volatile unsigned int*)(0x4266E1A8UL))
#define bFM0P_GPIO_PZR3_P3B                     *((volatile unsigned int*)(0x4266E1ACUL))
#define bFM0P_GPIO_PZR3_P3C                     *((volatile unsigned int*)(0x4266E1B0UL))
#define bFM0P_GPIO_PZR3_P3D                     *((volatile unsigned int*)(0x4266E1B4UL))
#define bFM0P_GPIO_PZR3_P3E                     *((volatile unsigned int*)(0x4266E1B8UL))
#define bFM0P_GPIO_PZR3_P3F                     *((volatile unsigned int*)(0x4266E1BCUL))
#define bFM0P_GPIO_PZR4_P46                     *((volatile unsigned int*)(0x4266E218UL))
#define bFM0P_GPIO_PZR4_P47                     *((volatile unsigned int*)(0x4266E21CUL))
#define bFM0P_GPIO_PZR4_P49                     *((volatile unsigned int*)(0x4266E224UL))
#define bFM0P_GPIO_PZR4_P4A                     *((volatile unsigned int*)(0x4266E228UL))
#define bFM0P_GPIO_PZR5_P50                     *((volatile unsigned int*)(0x4266E280UL))
#define bFM0P_GPIO_PZR5_P51                     *((volatile unsigned int*)(0x4266E284UL))
#define bFM0P_GPIO_PZR5_P52                     *((volatile unsigned int*)(0x4266E288UL))
#define bFM0P_GPIO_PZR6_P60                     *((volatile unsigned int*)(0x4266E300UL))
#define bFM0P_GPIO_PZR6_P61                     *((volatile unsigned int*)(0x4266E304UL))
#define bFM0P_GPIO_PZR8_P80                     *((volatile unsigned int*)(0x4266E400UL))
#define bFM0P_GPIO_PZR8_P81                     *((volatile unsigned int*)(0x4266E404UL))
#define bFM0P_GPIO_PZR8_P82                     *((volatile unsigned int*)(0x4266E408UL))
#define bFM0P_GPIO_PZRE_PE0                     *((volatile unsigned int*)(0x4266E700UL))
#define bFM0P_GPIO_PZRE_PE2                     *((volatile unsigned int*)(0x4266E708UL))
#define bFM0P_GPIO_PZRE_PE3                     *((volatile unsigned int*)(0x4266E70CUL))

/* Fast GPIO registers */
#define bFM0P_GPIO_FPDIR0_P00                    *((volatile unsigned char*)(0xF8010004UL))
#define bFM0P_GPIO_FPDIR0_P01                    *((volatile unsigned char*)(0xF8010008UL))
#define bFM0P_GPIO_FPDIR0_P02                    *((volatile unsigned char*)(0xF8010010UL))
#define bFM0P_GPIO_FPDIR0_P03                    *((volatile unsigned char*)(0xF8010020UL))
#define bFM0P_GPIO_FPDIR0_P04                    *((volatile unsigned char*)(0xF8010040UL))
#define bFM0P_GPIO_FPDIR0_P0F                    *((volatile unsigned char*)(0xF8010201UL))
#define bFM0P_GPIO_FPDIR1_P10                    *((volatile unsigned char*)(0xF8010404UL))
#define bFM0P_GPIO_FPDIR1_P11                    *((volatile unsigned char*)(0xF8010408UL))
#define bFM0P_GPIO_FPDIR1_P12                    *((volatile unsigned char*)(0xF8010410UL))
#define bFM0P_GPIO_FPDIR1_P13                    *((volatile unsigned char*)(0xF8010420UL))
#define bFM0P_GPIO_FPDIR1_P14                    *((volatile unsigned char*)(0xF8010440UL))
#define bFM0P_GPIO_FPDIR1_P15                    *((volatile unsigned char*)(0xF8010480UL))
#define bFM0P_GPIO_FPDIR2_P21                    *((volatile unsigned char*)(0xF8010804UL))
#define bFM0P_GPIO_FPDIR2_P22                    *((volatile unsigned char*)(0xF8010808UL))
#define bFM0P_GPIO_FPDIR2_P23                    *((volatile unsigned char*)(0xF8010810UL))
#define bFM0P_GPIO_FPDIR3_P39                    *((volatile unsigned char*)(0xF8010C09UL))
#define bFM0P_GPIO_FPDIR3_P3A                    *((volatile unsigned char*)(0xF8010C11UL))
#define bFM0P_GPIO_FPDIR3_P3B                    *((volatile unsigned char*)(0xF8010C21UL))
#define bFM0P_GPIO_FPDIR3_P3C                    *((volatile unsigned char*)(0xF8010C41UL))
#define bFM0P_GPIO_FPDIR3_P3D                    *((volatile unsigned char*)(0xF8010C81UL))
#define bFM0P_GPIO_FPDIR3_P3E                    *((volatile unsigned char*)(0xF8010D01UL))
#define bFM0P_GPIO_FPDIR3_P3F                    *((volatile unsigned char*)(0xF8010E01UL))
#define bFM0P_GPIO_FPDIR4_P46                    *((volatile unsigned char*)(0xF8011100UL))
#define bFM0P_GPIO_FPDIR4_P47                    *((volatile unsigned char*)(0xF8011200UL))
#define bFM0P_GPIO_FPDIR4_P49                    *((volatile unsigned char*)(0xF8011009UL))
#define bFM0P_GPIO_FPDIR4_P4A                    *((volatile unsigned char*)(0xF8011011UL))
#define bFM0P_GPIO_FPDIR5_P50                    *((volatile unsigned char*)(0xF8011404UL))
#define bFM0P_GPIO_FPDIR5_P51                    *((volatile unsigned char*)(0xF8011408UL))
#define bFM0P_GPIO_FPDIR5_P52                    *((volatile unsigned char*)(0xF8011410UL))
#define bFM0P_GPIO_FPDIR6_P60                    *((volatile unsigned char*)(0xF8011804UL))
#define bFM0P_GPIO_FPDIR6_P61                    *((volatile unsigned char*)(0xF8011808UL))
#define bFM0P_GPIO_FPDIR8_P80                    *((volatile unsigned char*)(0xF8012004UL))
#define bFM0P_GPIO_FPDIR8_P81                    *((volatile unsigned char*)(0xF8012008UL))
#define bFM0P_GPIO_FPDIR8_P82                    *((volatile unsigned char*)(0xF8012010UL))
#define bFM0P_GPIO_FPDIRE_PE0                    *((volatile unsigned char*)(0xF8013804UL))
#define bFM0P_GPIO_FPDIRE_PE2                    *((volatile unsigned char*)(0xF8013810UL))
#define bFM0P_GPIO_FPDIRE_PE3                    *((volatile unsigned char*)(0xF8013820UL))
#define bFM0P_GPIO_FPDOR0_P00                    *((volatile unsigned char*)(0xF8014004UL))
#define bFM0P_GPIO_FPDOR0_P01                    *((volatile unsigned char*)(0xF8014008UL))
#define bFM0P_GPIO_FPDOR0_P02                    *((volatile unsigned char*)(0xF8014010UL))
#define bFM0P_GPIO_FPDOR0_P03                    *((volatile unsigned char*)(0xF8014020UL))
#define bFM0P_GPIO_FPDOR0_P04                    *((volatile unsigned char*)(0xF8014040UL))
#define bFM0P_GPIO_FPDOR0_P0F                    *((volatile unsigned char*)(0xF8014201UL))
#define bFM0P_GPIO_FPDOR1_P10                    *((volatile unsigned char*)(0xF8014404UL))
#define bFM0P_GPIO_FPDOR1_P11                    *((volatile unsigned char*)(0xF8014408UL))
#define bFM0P_GPIO_FPDOR1_P12                    *((volatile unsigned char*)(0xF8014410UL))
#define bFM0P_GPIO_FPDOR1_P13                    *((volatile unsigned char*)(0xF8014420UL))
#define bFM0P_GPIO_FPDOR1_P14                    *((volatile unsigned char*)(0xF8014440UL))
#define bFM0P_GPIO_FPDOR1_P15                    *((volatile unsigned char*)(0xF8014480UL))
#define bFM0P_GPIO_FPDOR2_P21                    *((volatile unsigned char*)(0xF8014808UL))
#define bFM0P_GPIO_FPDOR2_P22                    *((volatile unsigned char*)(0xF8014810UL))
#define bFM0P_GPIO_FPDOR2_P23                    *((volatile unsigned char*)(0xF8014820UL))
#define bFM0P_GPIO_FPDOR3_P39                    *((volatile unsigned char*)(0xF8014C09UL))
#define bFM0P_GPIO_FPDOR3_P3A                    *((volatile unsigned char*)(0xF8014C11UL))
#define bFM0P_GPIO_FPDOR3_P3B                    *((volatile unsigned char*)(0xF8014C21UL))
#define bFM0P_GPIO_FPDOR3_P3C                    *((volatile unsigned char*)(0xF8014C41UL))
#define bFM0P_GPIO_FPDOR3_P3D                    *((volatile unsigned char*)(0xF8014C81UL))
#define bFM0P_GPIO_FPDOR3_P3E                    *((volatile unsigned char*)(0xF8014D01UL))
#define bFM0P_GPIO_FPDOR3_P3F                    *((volatile unsigned char*)(0xF8014E01UL))
#define bFM0P_GPIO_FPDOR4_P46                    *((volatile unsigned char*)(0xF8015100UL))
#define bFM0P_GPIO_FPDOR4_P47                    *((volatile unsigned char*)(0xF8015200UL))
#define bFM0P_GPIO_FPDOR4_P49                    *((volatile unsigned char*)(0xF8015009UL))
#define bFM0P_GPIO_FPDOR4_P4A                    *((volatile unsigned char*)(0xF8015011UL))
#define bFM0P_GPIO_FPDOR5_P50                    *((volatile unsigned char*)(0xF8015404UL))
#define bFM0P_GPIO_FPDOR5_P51                    *((volatile unsigned char*)(0xF8015408UL))
#define bFM0P_GPIO_FPDOR5_P52                    *((volatile unsigned char*)(0xF8015410UL))
#define bFM0P_GPIO_FPDOR6_P60                    *((volatile unsigned char*)(0xF8015804UL))
#define bFM0P_GPIO_FPDOR6_P61                    *((volatile unsigned char*)(0xF8015808UL))
#define bFM0P_GPIO_FPDOR8_P80                    *((volatile unsigned char*)(0xF8016004UL))
#define bFM0P_GPIO_FPDOR8_P81                    *((volatile unsigned char*)(0xF8016008UL))
#define bFM0P_GPIO_FPDOR8_P82                    *((volatile unsigned char*)(0xF8016010UL))
#define bFM0P_GPIO_FPDORE_PE0                    *((volatile unsigned char*)(0xF8017804UL))
#define bFM0P_GPIO_FPDORE_PE2                    *((volatile unsigned char*)(0xF8017810UL))
#define bFM0P_GPIO_FPDORE_PE3                    *((volatile unsigned char*)(0xF8017820UL))
#define bFM0P_GPIO_M_FPDIR0_P00                  *((volatile unsigned char*)(0xF8018004UL))
#define bFM0P_GPIO_M_FPDIR0_P01                  *((volatile unsigned char*)(0xF8018008UL))
#define bFM0P_GPIO_M_FPDIR0_P02                  *((volatile unsigned char*)(0xF8018010UL))
#define bFM0P_GPIO_M_FPDIR0_P03                  *((volatile unsigned char*)(0xF8018020UL))
#define bFM0P_GPIO_M_FPDIR0_P04                  *((volatile unsigned char*)(0xF8018040UL))
#define bFM0P_GPIO_M_FPDIR0_P05                  *((volatile unsigned char*)(0xF8018080UL))
#define bFM0P_GPIO_M_FPDIR0_P06                  *((volatile unsigned char*)(0xF8018100UL))
#define bFM0P_GPIO_M_FPDIR0_P07                  *((volatile unsigned char*)(0xF8018200UL))
#define bFM0P_GPIO_M_FPDIR1_P10                  *((volatile unsigned char*)(0xF8018404UL))
#define bFM0P_GPIO_M_FPDIR1_P11                  *((volatile unsigned char*)(0xF8018408UL))
#define bFM0P_GPIO_M_FPDIR1_P12                  *((volatile unsigned char*)(0xF8018410UL))
#define bFM0P_GPIO_M_FPDIR1_P13                  *((volatile unsigned char*)(0xF8018420UL))
#define bFM0P_GPIO_M_FPDIR1_P14                  *((volatile unsigned char*)(0xF8018440UL))
#define bFM0P_GPIO_M_FPDIR1_P15                  *((volatile unsigned char*)(0xF8018480UL))
#define bFM0P_GPIO_M_FPDIR1_P16                  *((volatile unsigned char*)(0xF8018500UL))
#define bFM0P_GPIO_M_FPDIR1_P17                  *((volatile unsigned char*)(0xF8018600UL))
#define bFM0P_GPIO_M_FPDOR0_P00                  *((volatile unsigned char*)(0xF801C004UL))
#define bFM0P_GPIO_M_FPDOR0_P01                  *((volatile unsigned char*)(0xF801C008UL))
#define bFM0P_GPIO_M_FPDOR0_P02                  *((volatile unsigned char*)(0xF801C010UL))
#define bFM0P_GPIO_M_FPDOR0_P03                  *((volatile unsigned char*)(0xF801C020UL))
#define bFM0P_GPIO_M_FPDOR0_P04                  *((volatile unsigned char*)(0xF801C040UL))
#define bFM0P_GPIO_M_FPDOR0_P05                  *((volatile unsigned char*)(0xF801C080UL))
#define bFM0P_GPIO_M_FPDOR0_P06                  *((volatile unsigned char*)(0xF801C100UL))
#define bFM0P_GPIO_M_FPDOR0_P07                  *((volatile unsigned char*)(0xF801C200UL))
#define bFM0P_GPIO_M_FPDOR1_P10                  *((volatile unsigned char*)(0xF801C404UL))
#define bFM0P_GPIO_M_FPDOR1_P11                  *((volatile unsigned char*)(0xF801C408UL))
#define bFM0P_GPIO_M_FPDOR1_P12                  *((volatile unsigned char*)(0xF801C410UL))
#define bFM0P_GPIO_M_FPDOR1_P13                  *((volatile unsigned char*)(0xF801C420UL))
#define bFM0P_GPIO_M_FPDOR1_P14                  *((volatile unsigned char*)(0xF801C440UL))
#define bFM0P_GPIO_M_FPDOR1_P15                  *((volatile unsigned char*)(0xF801C480UL))
#define bFM0P_GPIO_M_FPDOR1_P16                  *((volatile unsigned char*)(0xF801C500UL))
#define bFM0P_GPIO_M_FPDOR1_P17                  *((volatile unsigned char*)(0xF801C600UL))

/* Low voltage detection registers */
#define bFM0P_LVD_LVD_CTL_SVHI0                *((volatile unsigned int*)(0x426A0008UL))
#define bFM0P_LVD_LVD_CTL_SVHI1                *((volatile unsigned int*)(0x426A000CUL))
#define bFM0P_LVD_LVD_CTL_SVHI2                *((volatile unsigned int*)(0x426A0010UL))
#define bFM0P_LVD_LVD_CTL_SVHI3                *((volatile unsigned int*)(0x426A0014UL))
#define bFM0P_LVD_LVD_CTL_SVHI4                *((volatile unsigned int*)(0x426A0018UL))
#define bFM0P_LVD_LVD_CTL_LVDIE                *((volatile unsigned int*)(0x426A001CUL))
#define bFM0P_LVD_LVD_CTL_SVHR0                *((volatile unsigned int*)(0x426A0028UL))
#define bFM0P_LVD_LVD_CTL_SVHR1                *((volatile unsigned int*)(0x426A002CUL))
#define bFM0P_LVD_LVD_CTL_SVHR2                *((volatile unsigned int*)(0x426A0030UL))
#define bFM0P_LVD_LVD_CTL_SVHR3                *((volatile unsigned int*)(0x426A0034UL))
#define bFM0P_LVD_LVD_CTL_SVHR4                *((volatile unsigned int*)(0x426A0038UL))
#define bFM0P_LVD_LVD_CTL_LVDRE                *((volatile unsigned int*)(0x426A003CUL))
#define bFM0P_LVD_LVD_STR_LVDIR                *((volatile unsigned int*)(0x426A009CUL))
#define bFM0P_LVD_LVD_CLR_LVDCL                *((volatile unsigned int*)(0x426A011CUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK0              *((volatile unsigned int*)(0x426A0180UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK1              *((volatile unsigned int*)(0x426A0184UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK2              *((volatile unsigned int*)(0x426A0188UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK3              *((volatile unsigned int*)(0x426A018CUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK4              *((volatile unsigned int*)(0x426A0190UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK5              *((volatile unsigned int*)(0x426A0194UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK6              *((volatile unsigned int*)(0x426A0198UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK7              *((volatile unsigned int*)(0x426A019CUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK8              *((volatile unsigned int*)(0x426A01A0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK9              *((volatile unsigned int*)(0x426A01A4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK10             *((volatile unsigned int*)(0x426A01A8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK11             *((volatile unsigned int*)(0x426A01ACUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK12             *((volatile unsigned int*)(0x426A01B0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK13             *((volatile unsigned int*)(0x426A01B4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK14             *((volatile unsigned int*)(0x426A01B8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK15             *((volatile unsigned int*)(0x426A01BCUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK16             *((volatile unsigned int*)(0x426A01C0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK17             *((volatile unsigned int*)(0x426A01C4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK18             *((volatile unsigned int*)(0x426A01C8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK19             *((volatile unsigned int*)(0x426A01CCUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK20             *((volatile unsigned int*)(0x426A01D0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK21             *((volatile unsigned int*)(0x426A01D4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK22             *((volatile unsigned int*)(0x426A01D8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK23             *((volatile unsigned int*)(0x426A01DCUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK24             *((volatile unsigned int*)(0x426A01E0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK25             *((volatile unsigned int*)(0x426A01E4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK26             *((volatile unsigned int*)(0x426A01E8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK27             *((volatile unsigned int*)(0x426A01ECUL))
#define bFM0P_LVD_LVD_RLR_LVDLCK28             *((volatile unsigned int*)(0x426A01F0UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK29             *((volatile unsigned int*)(0x426A01F4UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK30             *((volatile unsigned int*)(0x426A01F8UL))
#define bFM0P_LVD_LVD_RLR_LVDLCK31             *((volatile unsigned int*)(0x426A01FCUL))
#define bFM0P_LVD_LVD_STR2_LVDRRDY             *((volatile unsigned int*)(0x426A0218UL))
#define bFM0P_LVD_LVD_STR2_LVDIRDY             *((volatile unsigned int*)(0x426A021CUL))

/* Deep standby mode control registers */
#define bFM0P_DS_REG_CTL_ISUBSEL0              *((volatile unsigned int*)(0x426A2004UL))
#define bFM0P_DS_REG_CTL_ISUBSEL1              *((volatile unsigned int*)(0x426A2008UL))
#define bFM0P_DS_RCK_CTL_RTCCKE                *((volatile unsigned int*)(0x426A2080UL))
#define bFM0P_DS_RCK_CTL_CECCKE                *((volatile unsigned int*)(0x426A2084UL))
#define bFM0P_DS_PMD_CTL_RTCE                  *((volatile unsigned int*)(0x426B0000UL))
#define bFM0P_DS_WRFSR_WINITX                  *((volatile unsigned int*)(0x426B0080UL))
#define bFM0P_DS_WRFSR_WLVDH                   *((volatile unsigned int*)(0x426B0084UL))
#define bFM0P_DS_WIFSR_WRTCI                   *((volatile unsigned int*)(0x426B0100UL))
#define bFM0P_DS_WIFSR_WLVDI                   *((volatile unsigned int*)(0x426B0104UL))
#define bFM0P_DS_WIFSR_WUI0                    *((volatile unsigned int*)(0x426B0108UL))
#define bFM0P_DS_WIFSR_WUI1                    *((volatile unsigned int*)(0x426B010CUL))
#define bFM0P_DS_WIFSR_WUI2                    *((volatile unsigned int*)(0x426B0110UL))
#define bFM0P_DS_WIFSR_WUI3                    *((volatile unsigned int*)(0x426B0114UL))
#define bFM0P_DS_WIFSR_WUI4                    *((volatile unsigned int*)(0x426B0118UL))
#define bFM0P_DS_WIFSR_WUI5                    *((volatile unsigned int*)(0x426B011CUL))
#define bFM0P_DS_WIFSR_WCEC0I                  *((volatile unsigned int*)(0x426B0120UL))
#define bFM0P_DS_WIFSR_WCEC1I                  *((volatile unsigned int*)(0x426B0124UL))
#define bFM0P_DS_WIER_WRTCE                    *((volatile unsigned int*)(0x426B0180UL))
#define bFM0P_DS_WIER_WLVDE                    *((volatile unsigned int*)(0x426B0184UL))
#define bFM0P_DS_WIER_WUE1                     *((volatile unsigned int*)(0x426B018CUL))
#define bFM0P_DS_WIER_WUE2                     *((volatile unsigned int*)(0x426B0190UL))
#define bFM0P_DS_WIER_WUE3                     *((volatile unsigned int*)(0x426B0194UL))
#define bFM0P_DS_WIER_WUE4                     *((volatile unsigned int*)(0x426B0198UL))
#define bFM0P_DS_WIER_WUE5                     *((volatile unsigned int*)(0x426B019CUL))
#define bFM0P_DS_WIER_WCEC0E                   *((volatile unsigned int*)(0x426B01A0UL))
#define bFM0P_DS_WIER_WCEC1E                   *((volatile unsigned int*)(0x426B01A4UL))
#define bFM0P_DS_WILVR_WUI1LV                  *((volatile unsigned int*)(0x426B0200UL))
#define bFM0P_DS_WILVR_WUI2LV                  *((volatile unsigned int*)(0x426B0204UL))
#define bFM0P_DS_WILVR_WUI3LV                  *((volatile unsigned int*)(0x426B0208UL))
#define bFM0P_DS_WILVR_WUI4LV                  *((volatile unsigned int*)(0x426B020CUL))
#define bFM0P_DS_WILVR_WUI5LV                  *((volatile unsigned int*)(0x426B0210UL))
#define bFM0P_DS_DSRAMR_SRAMR0                 *((volatile unsigned int*)(0x426B0280UL))
#define bFM0P_DS_DSRAMR_SRAMR1                 *((volatile unsigned int*)(0x426B0284UL))
#define bFM0P_DS_BUR01_BUR010                  *((volatile unsigned int*)(0x426B2000UL))
#define bFM0P_DS_BUR01_BUR011                  *((volatile unsigned int*)(0x426B2004UL))
#define bFM0P_DS_BUR01_BUR012                  *((volatile unsigned int*)(0x426B2008UL))
#define bFM0P_DS_BUR01_BUR013                  *((volatile unsigned int*)(0x426B200CUL))
#define bFM0P_DS_BUR01_BUR014                  *((volatile unsigned int*)(0x426B2010UL))
#define bFM0P_DS_BUR01_BUR015                  *((volatile unsigned int*)(0x426B2014UL))
#define bFM0P_DS_BUR01_BUR016                  *((volatile unsigned int*)(0x426B2018UL))
#define bFM0P_DS_BUR01_BUR017                  *((volatile unsigned int*)(0x426B201CUL))
#define bFM0P_DS_BUR02_BUR020                  *((volatile unsigned int*)(0x426B2020UL))
#define bFM0P_DS_BUR02_BUR021                  *((volatile unsigned int*)(0x426B2024UL))
#define bFM0P_DS_BUR02_BUR022                  *((volatile unsigned int*)(0x426B2028UL))
#define bFM0P_DS_BUR02_BUR023                  *((volatile unsigned int*)(0x426B202CUL))
#define bFM0P_DS_BUR02_BUR024                  *((volatile unsigned int*)(0x426B2030UL))
#define bFM0P_DS_BUR02_BUR025                  *((volatile unsigned int*)(0x426B2034UL))
#define bFM0P_DS_BUR02_BUR026                  *((volatile unsigned int*)(0x426B2038UL))
#define bFM0P_DS_BUR02_BUR027                  *((volatile unsigned int*)(0x426B203CUL))
#define bFM0P_DS_BUR03_BUR030                  *((volatile unsigned int*)(0x426B2040UL))
#define bFM0P_DS_BUR03_BUR031                  *((volatile unsigned int*)(0x426B2044UL))
#define bFM0P_DS_BUR03_BUR032                  *((volatile unsigned int*)(0x426B2048UL))
#define bFM0P_DS_BUR03_BUR033                  *((volatile unsigned int*)(0x426B204CUL))
#define bFM0P_DS_BUR03_BUR034                  *((volatile unsigned int*)(0x426B2050UL))
#define bFM0P_DS_BUR03_BUR035                  *((volatile unsigned int*)(0x426B2054UL))
#define bFM0P_DS_BUR03_BUR036                  *((volatile unsigned int*)(0x426B2058UL))
#define bFM0P_DS_BUR03_BUR037                  *((volatile unsigned int*)(0x426B205CUL))
#define bFM0P_DS_BUR04_BUR040                  *((volatile unsigned int*)(0x426B2060UL))
#define bFM0P_DS_BUR04_BUR041                  *((volatile unsigned int*)(0x426B2064UL))
#define bFM0P_DS_BUR04_BUR042                  *((volatile unsigned int*)(0x426B2068UL))
#define bFM0P_DS_BUR04_BUR043                  *((volatile unsigned int*)(0x426B206CUL))
#define bFM0P_DS_BUR04_BUR044                  *((volatile unsigned int*)(0x426B2070UL))
#define bFM0P_DS_BUR04_BUR045                  *((volatile unsigned int*)(0x426B2074UL))
#define bFM0P_DS_BUR04_BUR046                  *((volatile unsigned int*)(0x426B2078UL))
#define bFM0P_DS_BUR04_BUR047                  *((volatile unsigned int*)(0x426B207CUL))
#define bFM0P_DS_BUR05_BUR050                  *((volatile unsigned int*)(0x426B2080UL))
#define bFM0P_DS_BUR05_BUR051                  *((volatile unsigned int*)(0x426B2084UL))
#define bFM0P_DS_BUR05_BUR052                  *((volatile unsigned int*)(0x426B2088UL))
#define bFM0P_DS_BUR05_BUR053                  *((volatile unsigned int*)(0x426B208CUL))
#define bFM0P_DS_BUR05_BUR054                  *((volatile unsigned int*)(0x426B2090UL))
#define bFM0P_DS_BUR05_BUR055                  *((volatile unsigned int*)(0x426B2094UL))
#define bFM0P_DS_BUR05_BUR056                  *((volatile unsigned int*)(0x426B2098UL))
#define bFM0P_DS_BUR05_BUR057                  *((volatile unsigned int*)(0x426B209CUL))
#define bFM0P_DS_BUR06_BUR060                  *((volatile unsigned int*)(0x426B20A0UL))
#define bFM0P_DS_BUR06_BUR061                  *((volatile unsigned int*)(0x426B20A4UL))
#define bFM0P_DS_BUR06_BUR062                  *((volatile unsigned int*)(0x426B20A8UL))
#define bFM0P_DS_BUR06_BUR063                  *((volatile unsigned int*)(0x426B20ACUL))
#define bFM0P_DS_BUR06_BUR064                  *((volatile unsigned int*)(0x426B20B0UL))
#define bFM0P_DS_BUR06_BUR065                  *((volatile unsigned int*)(0x426B20B4UL))
#define bFM0P_DS_BUR06_BUR066                  *((volatile unsigned int*)(0x426B20B8UL))
#define bFM0P_DS_BUR06_BUR067                  *((volatile unsigned int*)(0x426B20BCUL))
#define bFM0P_DS_BUR07_BUR070                  *((volatile unsigned int*)(0x426B20C0UL))
#define bFM0P_DS_BUR07_BUR071                  *((volatile unsigned int*)(0x426B20C4UL))
#define bFM0P_DS_BUR07_BUR072                  *((volatile unsigned int*)(0x426B20C8UL))
#define bFM0P_DS_BUR07_BUR073                  *((volatile unsigned int*)(0x426B20CCUL))
#define bFM0P_DS_BUR07_BUR074                  *((volatile unsigned int*)(0x426B20D0UL))
#define bFM0P_DS_BUR07_BUR075                  *((volatile unsigned int*)(0x426B20D4UL))
#define bFM0P_DS_BUR07_BUR076                  *((volatile unsigned int*)(0x426B20D8UL))
#define bFM0P_DS_BUR07_BUR077                  *((volatile unsigned int*)(0x426B20DCUL))
#define bFM0P_DS_BUR08_BUR080                  *((volatile unsigned int*)(0x426B20E0UL))
#define bFM0P_DS_BUR08_BUR081                  *((volatile unsigned int*)(0x426B20E4UL))
#define bFM0P_DS_BUR08_BUR082                  *((volatile unsigned int*)(0x426B20E8UL))
#define bFM0P_DS_BUR08_BUR083                  *((volatile unsigned int*)(0x426B20ECUL))
#define bFM0P_DS_BUR08_BUR084                  *((volatile unsigned int*)(0x426B20F0UL))
#define bFM0P_DS_BUR08_BUR085                  *((volatile unsigned int*)(0x426B20F4UL))
#define bFM0P_DS_BUR08_BUR086                  *((volatile unsigned int*)(0x426B20F8UL))
#define bFM0P_DS_BUR08_BUR087                  *((volatile unsigned int*)(0x426B20FCUL))
#define bFM0P_DS_BUR09_BUR090                  *((volatile unsigned int*)(0x426B2100UL))
#define bFM0P_DS_BUR09_BUR091                  *((volatile unsigned int*)(0x426B2104UL))
#define bFM0P_DS_BUR09_BUR092                  *((volatile unsigned int*)(0x426B2108UL))
#define bFM0P_DS_BUR09_BUR093                  *((volatile unsigned int*)(0x426B210CUL))
#define bFM0P_DS_BUR09_BUR094                  *((volatile unsigned int*)(0x426B2110UL))
#define bFM0P_DS_BUR09_BUR095                  *((volatile unsigned int*)(0x426B2114UL))
#define bFM0P_DS_BUR09_BUR096                  *((volatile unsigned int*)(0x426B2118UL))
#define bFM0P_DS_BUR09_BUR097                  *((volatile unsigned int*)(0x426B211CUL))
#define bFM0P_DS_BUR10_BUR100                  *((volatile unsigned int*)(0x426B2120UL))
#define bFM0P_DS_BUR10_BUR101                  *((volatile unsigned int*)(0x426B2124UL))
#define bFM0P_DS_BUR10_BUR102                  *((volatile unsigned int*)(0x426B2128UL))
#define bFM0P_DS_BUR10_BUR103                  *((volatile unsigned int*)(0x426B212CUL))
#define bFM0P_DS_BUR10_BUR104                  *((volatile unsigned int*)(0x426B2130UL))
#define bFM0P_DS_BUR10_BUR105                  *((volatile unsigned int*)(0x426B2134UL))
#define bFM0P_DS_BUR10_BUR106                  *((volatile unsigned int*)(0x426B2138UL))
#define bFM0P_DS_BUR10_BUR107                  *((volatile unsigned int*)(0x426B213CUL))
#define bFM0P_DS_BUR11_BUR110                  *((volatile unsigned int*)(0x426B2140UL))
#define bFM0P_DS_BUR11_BUR111                  *((volatile unsigned int*)(0x426B2144UL))
#define bFM0P_DS_BUR11_BUR112                  *((volatile unsigned int*)(0x426B2148UL))
#define bFM0P_DS_BUR11_BUR113                  *((volatile unsigned int*)(0x426B214CUL))
#define bFM0P_DS_BUR11_BUR114                  *((volatile unsigned int*)(0x426B2150UL))
#define bFM0P_DS_BUR11_BUR115                  *((volatile unsigned int*)(0x426B2154UL))
#define bFM0P_DS_BUR11_BUR116                  *((volatile unsigned int*)(0x426B2158UL))
#define bFM0P_DS_BUR11_BUR117                  *((volatile unsigned int*)(0x426B215CUL))
#define bFM0P_DS_BUR12_BUR120                  *((volatile unsigned int*)(0x426B2160UL))
#define bFM0P_DS_BUR12_BUR121                  *((volatile unsigned int*)(0x426B2164UL))
#define bFM0P_DS_BUR12_BUR122                  *((volatile unsigned int*)(0x426B2168UL))
#define bFM0P_DS_BUR12_BUR123                  *((volatile unsigned int*)(0x426B216CUL))
#define bFM0P_DS_BUR12_BUR124                  *((volatile unsigned int*)(0x426B2170UL))
#define bFM0P_DS_BUR12_BUR125                  *((volatile unsigned int*)(0x426B2174UL))
#define bFM0P_DS_BUR12_BUR126                  *((volatile unsigned int*)(0x426B2178UL))
#define bFM0P_DS_BUR12_BUR127                  *((volatile unsigned int*)(0x426B217CUL))
#define bFM0P_DS_BUR13_BUR130                  *((volatile unsigned int*)(0x426B2180UL))
#define bFM0P_DS_BUR13_BUR131                  *((volatile unsigned int*)(0x426B2184UL))
#define bFM0P_DS_BUR13_BUR132                  *((volatile unsigned int*)(0x426B2188UL))
#define bFM0P_DS_BUR13_BUR133                  *((volatile unsigned int*)(0x426B218CUL))
#define bFM0P_DS_BUR13_BUR134                  *((volatile unsigned int*)(0x426B2190UL))
#define bFM0P_DS_BUR13_BUR135                  *((volatile unsigned int*)(0x426B2194UL))
#define bFM0P_DS_BUR13_BUR136                  *((volatile unsigned int*)(0x426B2198UL))
#define bFM0P_DS_BUR13_BUR137                  *((volatile unsigned int*)(0x426B219CUL))
#define bFM0P_DS_BUR14_BUR140                  *((volatile unsigned int*)(0x426B21A0UL))
#define bFM0P_DS_BUR14_BUR141                  *((volatile unsigned int*)(0x426B21A4UL))
#define bFM0P_DS_BUR14_BUR142                  *((volatile unsigned int*)(0x426B21A8UL))
#define bFM0P_DS_BUR14_BUR143                  *((volatile unsigned int*)(0x426B21ACUL))
#define bFM0P_DS_BUR14_BUR144                  *((volatile unsigned int*)(0x426B21B0UL))
#define bFM0P_DS_BUR14_BUR145                  *((volatile unsigned int*)(0x426B21B4UL))
#define bFM0P_DS_BUR14_BUR146                  *((volatile unsigned int*)(0x426B21B8UL))
#define bFM0P_DS_BUR14_BUR147                  *((volatile unsigned int*)(0x426B21BCUL))
#define bFM0P_DS_BUR15_BUR150                  *((volatile unsigned int*)(0x426B21C0UL))
#define bFM0P_DS_BUR15_BUR151                  *((volatile unsigned int*)(0x426B21C4UL))
#define bFM0P_DS_BUR15_BUR152                  *((volatile unsigned int*)(0x426B21C8UL))
#define bFM0P_DS_BUR15_BUR153                  *((volatile unsigned int*)(0x426B21CCUL))
#define bFM0P_DS_BUR15_BUR154                  *((volatile unsigned int*)(0x426B21D0UL))
#define bFM0P_DS_BUR15_BUR155                  *((volatile unsigned int*)(0x426B21D4UL))
#define bFM0P_DS_BUR15_BUR156                  *((volatile unsigned int*)(0x426B21D8UL))
#define bFM0P_DS_BUR15_BUR157                  *((volatile unsigned int*)(0x426B21DCUL))
#define bFM0P_DS_BUR16_BUR160                  *((volatile unsigned int*)(0x426B21E0UL))
#define bFM0P_DS_BUR16_BUR161                  *((volatile unsigned int*)(0x426B21E4UL))
#define bFM0P_DS_BUR16_BUR162                  *((volatile unsigned int*)(0x426B21E8UL))
#define bFM0P_DS_BUR16_BUR163                  *((volatile unsigned int*)(0x426B21ECUL))
#define bFM0P_DS_BUR16_BUR164                  *((volatile unsigned int*)(0x426B21F0UL))
#define bFM0P_DS_BUR16_BUR165                  *((volatile unsigned int*)(0x426B21F4UL))
#define bFM0P_DS_BUR16_BUR166                  *((volatile unsigned int*)(0x426B21F8UL))
#define bFM0P_DS_BUR16_BUR167                  *((volatile unsigned int*)(0x426B21FCUL))

/* MFS UART channel 0 registers */
#define bFM0P_MFS0_UART_SMR_SOE                *((volatile unsigned int*)(0x42700000UL))
#define bFM0P_MFS0_UART_SMR_BDS                *((volatile unsigned int*)(0x42700008UL))
#define bFM0P_MFS0_UART_SMR_SBL                *((volatile unsigned int*)(0x4270000CUL))
#define bFM0P_MFS0_UART_SMR_MD0                *((volatile unsigned int*)(0x42700014UL))
#define bFM0P_MFS0_UART_SMR_MD1                *((volatile unsigned int*)(0x42700018UL))
#define bFM0P_MFS0_UART_SMR_MD2                *((volatile unsigned int*)(0x4270001CUL))
#define bFM0P_MFS0_UART_SCR_TXE                *((volatile unsigned int*)(0x42700020UL))
#define bFM0P_MFS0_UART_SCR_RXE                *((volatile unsigned int*)(0x42700024UL))
#define bFM0P_MFS0_UART_SCR_TBIE               *((volatile unsigned int*)(0x42700028UL))
#define bFM0P_MFS0_UART_SCR_TIE                *((volatile unsigned int*)(0x4270002CUL))
#define bFM0P_MFS0_UART_SCR_RIE                *((volatile unsigned int*)(0x42700030UL))
#define bFM0P_MFS0_UART_SCR_UPCL               *((volatile unsigned int*)(0x4270003CUL))
#define bFM0P_MFS0_UART_ESCR_L0                *((volatile unsigned int*)(0x42700080UL))
#define bFM0P_MFS0_UART_ESCR_L1                *((volatile unsigned int*)(0x42700084UL))
#define bFM0P_MFS0_UART_ESCR_L2                *((volatile unsigned int*)(0x42700088UL))
#define bFM0P_MFS0_UART_ESCR_P                 *((volatile unsigned int*)(0x4270008CUL))
#define bFM0P_MFS0_UART_ESCR_PEN               *((volatile unsigned int*)(0x42700090UL))
#define bFM0P_MFS0_UART_ESCR_INV               *((volatile unsigned int*)(0x42700094UL))
#define bFM0P_MFS0_UART_ESCR_ESBL              *((volatile unsigned int*)(0x42700098UL))
#define bFM0P_MFS0_UART_ESCR_FLWEN             *((volatile unsigned int*)(0x4270009CUL))
#define bFM0P_MFS0_UART_SSR_TBI                *((volatile unsigned int*)(0x427000A0UL))
#define bFM0P_MFS0_UART_SSR_TDRE               *((volatile unsigned int*)(0x427000A4UL))
#define bFM0P_MFS0_UART_SSR_RDRF               *((volatile unsigned int*)(0x427000A8UL))
#define bFM0P_MFS0_UART_SSR_ORE                *((volatile unsigned int*)(0x427000ACUL))
#define bFM0P_MFS0_UART_SSR_FRE                *((volatile unsigned int*)(0x427000B0UL))
#define bFM0P_MFS0_UART_SSR_PE                 *((volatile unsigned int*)(0x427000B4UL))
#define bFM0P_MFS0_UART_SSR_REC                *((volatile unsigned int*)(0x427000BCUL))
#define bFM0P_MFS0_UART_BGR_BGR00              *((volatile unsigned int*)(0x42700180UL))
#define bFM0P_MFS0_UART_BGR_BGR01              *((volatile unsigned int*)(0x42700184UL))
#define bFM0P_MFS0_UART_BGR_BGR02              *((volatile unsigned int*)(0x42700188UL))
#define bFM0P_MFS0_UART_BGR_BGR03              *((volatile unsigned int*)(0x4270018CUL))
#define bFM0P_MFS0_UART_BGR_BGR04              *((volatile unsigned int*)(0x42700190UL))
#define bFM0P_MFS0_UART_BGR_BGR05              *((volatile unsigned int*)(0x42700194UL))
#define bFM0P_MFS0_UART_BGR_BGR06              *((volatile unsigned int*)(0x42700198UL))
#define bFM0P_MFS0_UART_BGR_BGR07              *((volatile unsigned int*)(0x4270019CUL))
#define bFM0P_MFS0_UART_BGR_BGR10              *((volatile unsigned int*)(0x427001A0UL))
#define bFM0P_MFS0_UART_BGR_BGR11              *((volatile unsigned int*)(0x427001A4UL))
#define bFM0P_MFS0_UART_BGR_BGR12              *((volatile unsigned int*)(0x427001A8UL))
#define bFM0P_MFS0_UART_BGR_BGR13              *((volatile unsigned int*)(0x427001ACUL))
#define bFM0P_MFS0_UART_BGR_BGR14              *((volatile unsigned int*)(0x427001B0UL))
#define bFM0P_MFS0_UART_BGR_BGR15              *((volatile unsigned int*)(0x427001B4UL))
#define bFM0P_MFS0_UART_BGR_BGR16              *((volatile unsigned int*)(0x427001B8UL))
#define bFM0P_MFS0_UART_BGR_EXT                *((volatile unsigned int*)(0x427001BCUL))
#define bFM0P_MFS0_UART_FCR0_FE1               *((volatile unsigned int*)(0x42700280UL))
#define bFM0P_MFS0_UART_FCR0_FE2               *((volatile unsigned int*)(0x42700284UL))
#define bFM0P_MFS0_UART_FCR0_FCL1              *((volatile unsigned int*)(0x42700288UL))
#define bFM0P_MFS0_UART_FCR0_FCL2              *((volatile unsigned int*)(0x4270028CUL))
#define bFM0P_MFS0_UART_FCR0_FSET              *((volatile unsigned int*)(0x42700290UL))
#define bFM0P_MFS0_UART_FCR0_FLD               *((volatile unsigned int*)(0x42700294UL))
#define bFM0P_MFS0_UART_FCR0_FLST              *((volatile unsigned int*)(0x42700298UL))
#define bFM0P_MFS0_UART_FCR1_FSEL              *((volatile unsigned int*)(0x427002A0UL))
#define bFM0P_MFS0_UART_FCR1_FTIE              *((volatile unsigned int*)(0x427002A4UL))
#define bFM0P_MFS0_UART_FCR1_FDRQ              *((volatile unsigned int*)(0x427002A8UL))
#define bFM0P_MFS0_UART_FCR1_FRIIE             *((volatile unsigned int*)(0x427002ACUL))
#define bFM0P_MFS0_UART_FCR1_FLSTE             *((volatile unsigned int*)(0x427002B0UL))
/* MFS CSIO channel 0 registers */
#define bFM0P_MFS0_CSIO_SMR_SOE                *((volatile unsigned int*)(0x42700000UL))
#define bFM0P_MFS0_CSIO_SMR_SCKE               *((volatile unsigned int*)(0x42700004UL))
#define bFM0P_MFS0_CSIO_SMR_BDS                *((volatile unsigned int*)(0x42700008UL))
#define bFM0P_MFS0_CSIO_SMR_SCINV              *((volatile unsigned int*)(0x4270000CUL))
#define bFM0P_MFS0_CSIO_SMR_MD0                *((volatile unsigned int*)(0x42700014UL))
#define bFM0P_MFS0_CSIO_SMR_MD1                *((volatile unsigned int*)(0x42700018UL))
#define bFM0P_MFS0_CSIO_SMR_MD2                *((volatile unsigned int*)(0x4270001CUL))
#define bFM0P_MFS0_CSIO_SCR_TXE                *((volatile unsigned int*)(0x42700020UL))
#define bFM0P_MFS0_CSIO_SCR_RXE                *((volatile unsigned int*)(0x42700024UL))
#define bFM0P_MFS0_CSIO_SCR_TBIE               *((volatile unsigned int*)(0x42700028UL))
#define bFM0P_MFS0_CSIO_SCR_TIE                *((volatile unsigned int*)(0x4270002CUL))
#define bFM0P_MFS0_CSIO_SCR_RIE                *((volatile unsigned int*)(0x42700030UL))
#define bFM0P_MFS0_CSIO_SCR_SPI                *((volatile unsigned int*)(0x42700034UL))
#define bFM0P_MFS0_CSIO_SCR_MS                 *((volatile unsigned int*)(0x42700038UL))
#define bFM0P_MFS0_CSIO_SCR_UPCL               *((volatile unsigned int*)(0x4270003CUL))
#define bFM0P_MFS0_CSIO_ESCR_L0                *((volatile unsigned int*)(0x42700080UL))
#define bFM0P_MFS0_CSIO_ESCR_L1                *((volatile unsigned int*)(0x42700084UL))
#define bFM0P_MFS0_CSIO_ESCR_L2                *((volatile unsigned int*)(0x42700088UL))
#define bFM0P_MFS0_CSIO_ESCR_WT0               *((volatile unsigned int*)(0x4270008CUL))
#define bFM0P_MFS0_CSIO_ESCR_WT1               *((volatile unsigned int*)(0x42700090UL))
#define bFM0P_MFS0_CSIO_ESCR_CSFE              *((volatile unsigned int*)(0x42700094UL))
#define bFM0P_MFS0_CSIO_ESCR_L3                *((volatile unsigned int*)(0x42700098UL))
#define bFM0P_MFS0_CSIO_ESCR_SOP               *((volatile unsigned int*)(0x4270009CUL))
#define bFM0P_MFS0_CSIO_SSR_TBI                *((volatile unsigned int*)(0x427000A0UL))
#define bFM0P_MFS0_CSIO_SSR_TDRE               *((volatile unsigned int*)(0x427000A4UL))
#define bFM0P_MFS0_CSIO_SSR_RDRF               *((volatile unsigned int*)(0x427000A8UL))
#define bFM0P_MFS0_CSIO_SSR_ORE                *((volatile unsigned int*)(0x427000ACUL))
#define bFM0P_MFS0_CSIO_SSR_REC                *((volatile unsigned int*)(0x427000BCUL))
#define bFM0P_MFS0_CSIO_BGR_BGR00              *((volatile unsigned int*)(0x42700180UL))
#define bFM0P_MFS0_CSIO_BGR_BGR01              *((volatile unsigned int*)(0x42700184UL))
#define bFM0P_MFS0_CSIO_BGR_BGR02              *((volatile unsigned int*)(0x42700188UL))
#define bFM0P_MFS0_CSIO_BGR_BGR03              *((volatile unsigned int*)(0x4270018CUL))
#define bFM0P_MFS0_CSIO_BGR_BGR04              *((volatile unsigned int*)(0x42700190UL))
#define bFM0P_MFS0_CSIO_BGR_BGR05              *((volatile unsigned int*)(0x42700194UL))
#define bFM0P_MFS0_CSIO_BGR_BGR06              *((volatile unsigned int*)(0x42700198UL))
#define bFM0P_MFS0_CSIO_BGR_BGR07              *((volatile unsigned int*)(0x4270019CUL))
#define bFM0P_MFS0_CSIO_BGR_BGR10              *((volatile unsigned int*)(0x427001A0UL))
#define bFM0P_MFS0_CSIO_BGR_BGR11              *((volatile unsigned int*)(0x427001A4UL))
#define bFM0P_MFS0_CSIO_BGR_BGR12              *((volatile unsigned int*)(0x427001A8UL))
#define bFM0P_MFS0_CSIO_BGR_BGR13              *((volatile unsigned int*)(0x427001ACUL))
#define bFM0P_MFS0_CSIO_BGR_BGR14              *((volatile unsigned int*)(0x427001B0UL))
#define bFM0P_MFS0_CSIO_BGR_BGR15              *((volatile unsigned int*)(0x427001B4UL))
#define bFM0P_MFS0_CSIO_BGR_BGR16              *((volatile unsigned int*)(0x427001B8UL))
#define bFM0P_MFS0_CSIO_FCR0_FE1               *((volatile unsigned int*)(0x42700280UL))
#define bFM0P_MFS0_CSIO_FCR0_FE2               *((volatile unsigned int*)(0x42700284UL))
#define bFM0P_MFS0_CSIO_FCR0_FCL1              *((volatile unsigned int*)(0x42700288UL))
#define bFM0P_MFS0_CSIO_FCR0_FCL2              *((volatile unsigned int*)(0x4270028CUL))
#define bFM0P_MFS0_CSIO_FCR0_FSET              *((volatile unsigned int*)(0x42700290UL))
#define bFM0P_MFS0_CSIO_FCR0_FLD               *((volatile unsigned int*)(0x42700294UL))
#define bFM0P_MFS0_CSIO_FCR0_FLST              *((volatile unsigned int*)(0x42700298UL))
#define bFM0P_MFS0_CSIO_FCR1_FSEL              *((volatile unsigned int*)(0x427002A0UL))
#define bFM0P_MFS0_CSIO_FCR1_FTIE              *((volatile unsigned int*)(0x427002A4UL))
#define bFM0P_MFS0_CSIO_FCR1_FDRQ              *((volatile unsigned int*)(0x427002A8UL))
#define bFM0P_MFS0_CSIO_FCR1_FRIIE             *((volatile unsigned int*)(0x427002ACUL))
#define bFM0P_MFS0_CSIO_FCR1_FLSTE             *((volatile unsigned int*)(0x427002B0UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD0           *((volatile unsigned int*)(0x42700380UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD1           *((volatile unsigned int*)(0x42700384UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD2           *((volatile unsigned int*)(0x42700388UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD3           *((volatile unsigned int*)(0x4270038CUL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD4           *((volatile unsigned int*)(0x42700390UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD5           *((volatile unsigned int*)(0x42700394UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD6           *((volatile unsigned int*)(0x42700398UL))
#define bFM0P_MFS0_CSIO_SCSTR0_CSHD7           *((volatile unsigned int*)(0x4270039CUL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU0           *((volatile unsigned int*)(0x427003A0UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU1           *((volatile unsigned int*)(0x427003A4UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU2           *((volatile unsigned int*)(0x427003A8UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU3           *((volatile unsigned int*)(0x427003ACUL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU4           *((volatile unsigned int*)(0x427003B0UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU5           *((volatile unsigned int*)(0x427003B4UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU6           *((volatile unsigned int*)(0x427003B8UL))
#define bFM0P_MFS0_CSIO_SCSTR1_CSSU7           *((volatile unsigned int*)(0x427003BCUL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS0          *((volatile unsigned int*)(0x42700400UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS1          *((volatile unsigned int*)(0x42700404UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS2          *((volatile unsigned int*)(0x42700408UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS3          *((volatile unsigned int*)(0x4270040CUL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS4          *((volatile unsigned int*)(0x42700410UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS5          *((volatile unsigned int*)(0x42700414UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS6          *((volatile unsigned int*)(0x42700418UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS7          *((volatile unsigned int*)(0x4270041CUL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS8          *((volatile unsigned int*)(0x42700420UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS9          *((volatile unsigned int*)(0x42700424UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS10         *((volatile unsigned int*)(0x42700428UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS11         *((volatile unsigned int*)(0x4270042CUL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS12         *((volatile unsigned int*)(0x42700430UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS13         *((volatile unsigned int*)(0x42700434UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS14         *((volatile unsigned int*)(0x42700438UL))
#define bFM0P_MFS0_CSIO_SCSTR32_CSDS15         *((volatile unsigned int*)(0x4270043CUL))
#define bFM0P_MFS0_CSIO_SACSR_TMRE             *((volatile unsigned int*)(0x42700480UL))
#define bFM0P_MFS0_CSIO_SACSR_TDIV0            *((volatile unsigned int*)(0x42700484UL))
#define bFM0P_MFS0_CSIO_SACSR_TDIV1            *((volatile unsigned int*)(0x42700488UL))
#define bFM0P_MFS0_CSIO_SACSR_TDIV2            *((volatile unsigned int*)(0x4270048CUL))
#define bFM0P_MFS0_CSIO_SACSR_TDIV3            *((volatile unsigned int*)(0x42700490UL))
#define bFM0P_MFS0_CSIO_SACSR_TSYNE            *((volatile unsigned int*)(0x42700498UL))
#define bFM0P_MFS0_CSIO_SACSR_TINTE            *((volatile unsigned int*)(0x4270049CUL))
#define bFM0P_MFS0_CSIO_SACSR_TINT             *((volatile unsigned int*)(0x427004A0UL))
#define bFM0P_MFS0_CSIO_SACSR_CSE              *((volatile unsigned int*)(0x427004ACUL))
#define bFM0P_MFS0_CSIO_SACSR_CSEIE            *((volatile unsigned int*)(0x427004B0UL))
#define bFM0P_MFS0_CSIO_SACSR_TBEEN            *((volatile unsigned int*)(0x427004B4UL))
#define bFM0P_MFS0_CSIO_STMR_TM0               *((volatile unsigned int*)(0x42700500UL))
#define bFM0P_MFS0_CSIO_STMR_TM1               *((volatile unsigned int*)(0x42700504UL))
#define bFM0P_MFS0_CSIO_STMR_TM2               *((volatile unsigned int*)(0x42700508UL))
#define bFM0P_MFS0_CSIO_STMR_TM3               *((volatile unsigned int*)(0x4270050CUL))
#define bFM0P_MFS0_CSIO_STMR_TM4               *((volatile unsigned int*)(0x42700510UL))
#define bFM0P_MFS0_CSIO_STMR_TM5               *((volatile unsigned int*)(0x42700514UL))
#define bFM0P_MFS0_CSIO_STMR_TM6               *((volatile unsigned int*)(0x42700518UL))
#define bFM0P_MFS0_CSIO_STMR_TM7               *((volatile unsigned int*)(0x4270051CUL))
#define bFM0P_MFS0_CSIO_STMR_TM8               *((volatile unsigned int*)(0x42700520UL))
#define bFM0P_MFS0_CSIO_STMR_TM9               *((volatile unsigned int*)(0x42700524UL))
#define bFM0P_MFS0_CSIO_STMR_TM10              *((volatile unsigned int*)(0x42700528UL))
#define bFM0P_MFS0_CSIO_STMR_TM11              *((volatile unsigned int*)(0x4270052CUL))
#define bFM0P_MFS0_CSIO_STMR_TM12              *((volatile unsigned int*)(0x42700530UL))
#define bFM0P_MFS0_CSIO_STMR_TM13              *((volatile unsigned int*)(0x42700534UL))
#define bFM0P_MFS0_CSIO_STMR_TM14              *((volatile unsigned int*)(0x42700538UL))
#define bFM0P_MFS0_CSIO_STMR_TM15              *((volatile unsigned int*)(0x4270053CUL))
#define bFM0P_MFS0_CSIO_TMCR_TC0               *((volatile unsigned int*)(0x42700580UL))
#define bFM0P_MFS0_CSIO_TMCR_TC1               *((volatile unsigned int*)(0x42700584UL))
#define bFM0P_MFS0_CSIO_TMCR_TC2               *((volatile unsigned int*)(0x42700588UL))
#define bFM0P_MFS0_CSIO_TMCR_TC3               *((volatile unsigned int*)(0x4270058CUL))
#define bFM0P_MFS0_CSIO_TMCR_TC4               *((volatile unsigned int*)(0x42700590UL))
#define bFM0P_MFS0_CSIO_TMCR_TC5               *((volatile unsigned int*)(0x42700594UL))
#define bFM0P_MFS0_CSIO_TMCR_TC6               *((volatile unsigned int*)(0x42700598UL))
#define bFM0P_MFS0_CSIO_TMCR_TC7               *((volatile unsigned int*)(0x4270059CUL))
#define bFM0P_MFS0_CSIO_TMCR_TC8               *((volatile unsigned int*)(0x427005A0UL))
#define bFM0P_MFS0_CSIO_TMCR_TC9               *((volatile unsigned int*)(0x427005A4UL))
#define bFM0P_MFS0_CSIO_TMCR_TC10              *((volatile unsigned int*)(0x427005A8UL))
#define bFM0P_MFS0_CSIO_TMCR_TC11              *((volatile unsigned int*)(0x427005ACUL))
#define bFM0P_MFS0_CSIO_TMCR_TC12              *((volatile unsigned int*)(0x427005B0UL))
#define bFM0P_MFS0_CSIO_TMCR_TC13              *((volatile unsigned int*)(0x427005B4UL))
#define bFM0P_MFS0_CSIO_TMCR_TC14              *((volatile unsigned int*)(0x427005B8UL))
#define bFM0P_MFS0_CSIO_TMCR_TC15              *((volatile unsigned int*)(0x427005BCUL))
#define bFM0P_MFS0_CSIO_SCSCR_CSOE             *((volatile unsigned int*)(0x42700600UL))
#define bFM0P_MFS0_CSIO_SCSCR_CSEN0            *((volatile unsigned int*)(0x42700604UL))
#define bFM0P_MFS0_CSIO_SCSCR_CSEN1            *((volatile unsigned int*)(0x42700608UL))
#define bFM0P_MFS0_CSIO_SCSCR_CSEN2            *((volatile unsigned int*)(0x4270060CUL))
#define bFM0P_MFS0_CSIO_SCSCR_CSEN3            *((volatile unsigned int*)(0x42700610UL))
#define bFM0P_MFS0_CSIO_SCSCR_CSLVL            *((volatile unsigned int*)(0x42700614UL))
#define bFM0P_MFS0_CSIO_SCSCR_CDIV0            *((volatile unsigned int*)(0x42700618UL))
#define bFM0P_MFS0_CSIO_SCSCR_CDIV1            *((volatile unsigned int*)(0x4270061CUL))
#define bFM0P_MFS0_CSIO_SCSCR_CDIV2            *((volatile unsigned int*)(0x42700620UL))
#define bFM0P_MFS0_CSIO_SCSCR_SCAM             *((volatile unsigned int*)(0x42700624UL))
#define bFM0P_MFS0_CSIO_SCSCR_SCD0             *((volatile unsigned int*)(0x42700628UL))
#define bFM0P_MFS0_CSIO_SCSCR_SCD1             *((volatile unsigned int*)(0x4270062CUL))
#define bFM0P_MFS0_CSIO_SCSCR_SED0             *((volatile unsigned int*)(0x42700630UL))
#define bFM0P_MFS0_CSIO_SCSCR_SED1             *((volatile unsigned int*)(0x42700634UL))
#define bFM0P_MFS0_CSIO_SCSCR_SST0             *((volatile unsigned int*)(0x42700638UL))
#define bFM0P_MFS0_CSIO_SCSCR_SST1             *((volatile unsigned int*)(0x4270063CUL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1L0           *((volatile unsigned int*)(0x42700680UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1L1           *((volatile unsigned int*)(0x42700684UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1L2           *((volatile unsigned int*)(0x42700688UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1L3           *((volatile unsigned int*)(0x4270068CUL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1BDS          *((volatile unsigned int*)(0x42700690UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1SPI          *((volatile unsigned int*)(0x42700694UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1SCINV        *((volatile unsigned int*)(0x42700698UL))
#define bFM0P_MFS0_CSIO_SCSFR0_CS1CSLVL        *((volatile unsigned int*)(0x4270069CUL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2L0           *((volatile unsigned int*)(0x427006A0UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2L1           *((volatile unsigned int*)(0x427006A4UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2L2           *((volatile unsigned int*)(0x427006A8UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2L3           *((volatile unsigned int*)(0x427006ACUL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2BDS          *((volatile unsigned int*)(0x427006B0UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2SPI          *((volatile unsigned int*)(0x427006B4UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2SCINV        *((volatile unsigned int*)(0x427006B8UL))
#define bFM0P_MFS0_CSIO_SCSFR1_CS2CSLVL        *((volatile unsigned int*)(0x427006BCUL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3L0           *((volatile unsigned int*)(0x42700700UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3L1           *((volatile unsigned int*)(0x42700704UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3L2           *((volatile unsigned int*)(0x42700708UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3L3           *((volatile unsigned int*)(0x4270070CUL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3BDS          *((volatile unsigned int*)(0x42700710UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3SPI          *((volatile unsigned int*)(0x42700714UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3SCINV        *((volatile unsigned int*)(0x42700718UL))
#define bFM0P_MFS0_CSIO_SCSFR3_CS3CSLVL        *((volatile unsigned int*)(0x4270071CUL))

/* MFS LIN channel 0 registers */
#define bFM0P_MFS0_LIN_SMR_SOE                 *((volatile unsigned int*)(0x42700000UL))
#define bFM0P_MFS0_LIN_SMR_SBL                 *((volatile unsigned int*)(0x4270000CUL))
#define bFM0P_MFS0_LIN_SMR_MD0                 *((volatile unsigned int*)(0x42700014UL))
#define bFM0P_MFS0_LIN_SMR_MD1                 *((volatile unsigned int*)(0x42700018UL))
#define bFM0P_MFS0_LIN_SMR_MD2                 *((volatile unsigned int*)(0x4270001CUL))
#define bFM0P_MFS0_LIN_SCR_TXE                 *((volatile unsigned int*)(0x42700020UL))
#define bFM0P_MFS0_LIN_SCR_RXE                 *((volatile unsigned int*)(0x42700024UL))
#define bFM0P_MFS0_LIN_SCR_TBIE                *((volatile unsigned int*)(0x42700028UL))
#define bFM0P_MFS0_LIN_SCR_TIE                 *((volatile unsigned int*)(0x4270002CUL))
#define bFM0P_MFS0_LIN_SCR_RIE                 *((volatile unsigned int*)(0x42700030UL))
#define bFM0P_MFS0_LIN_SCR_LBR                 *((volatile unsigned int*)(0x42700034UL))
#define bFM0P_MFS0_LIN_SCR_MS                  *((volatile unsigned int*)(0x42700038UL))
#define bFM0P_MFS0_LIN_SCR_UPCL                *((volatile unsigned int*)(0x4270003CUL))
#define bFM0P_MFS0_LIN_ESCR_DEL0               *((volatile unsigned int*)(0x42700080UL))
#define bFM0P_MFS0_LIN_ESCR_DEL1               *((volatile unsigned int*)(0x42700084UL))
#define bFM0P_MFS0_LIN_ESCR_LBL0               *((volatile unsigned int*)(0x42700088UL))
#define bFM0P_MFS0_LIN_ESCR_LBL1               *((volatile unsigned int*)(0x4270008CUL))
#define bFM0P_MFS0_LIN_ESCR_LBIE               *((volatile unsigned int*)(0x42700090UL))
#define bFM0P_MFS0_LIN_ESCR_ESBL               *((volatile unsigned int*)(0x42700098UL))
#define bFM0P_MFS0_LIN_SSR_TBI                 *((volatile unsigned int*)(0x427000A0UL))
#define bFM0P_MFS0_LIN_SSR_TDRE                *((volatile unsigned int*)(0x427000A4UL))
#define bFM0P_MFS0_LIN_SSR_RDRF                *((volatile unsigned int*)(0x427000A8UL))
#define bFM0P_MFS0_LIN_SSR_ORE                 *((volatile unsigned int*)(0x427000ACUL))
#define bFM0P_MFS0_LIN_SSR_FRE                 *((volatile unsigned int*)(0x427000B0UL))
#define bFM0P_MFS0_LIN_SSR_LBD                 *((volatile unsigned int*)(0x427000B4UL))
#define bFM0P_MFS0_LIN_SSR_REC                 *((volatile unsigned int*)(0x427000BCUL))
#define bFM0P_MFS0_LIN_BGR_BGR00               *((volatile unsigned int*)(0x42700180UL))
#define bFM0P_MFS0_LIN_BGR_BGR01               *((volatile unsigned int*)(0x42700184UL))
#define bFM0P_MFS0_LIN_BGR_BGR02               *((volatile unsigned int*)(0x42700188UL))
#define bFM0P_MFS0_LIN_BGR_BGR03               *((volatile unsigned int*)(0x4270018CUL))
#define bFM0P_MFS0_LIN_BGR_BGR04               *((volatile unsigned int*)(0x42700190UL))
#define bFM0P_MFS0_LIN_BGR_BGR05               *((volatile unsigned int*)(0x42700194UL))
#define bFM0P_MFS0_LIN_BGR_BGR06               *((volatile unsigned int*)(0x42700198UL))
#define bFM0P_MFS0_LIN_BGR_BGR07               *((volatile unsigned int*)(0x4270019CUL))
#define bFM0P_MFS0_LIN_BGR_BGR10               *((volatile unsigned int*)(0x427001A0UL))
#define bFM0P_MFS0_LIN_BGR_BGR11               *((volatile unsigned int*)(0x427001A4UL))
#define bFM0P_MFS0_LIN_BGR_BGR12               *((volatile unsigned int*)(0x427001A8UL))
#define bFM0P_MFS0_LIN_BGR_BGR13               *((volatile unsigned int*)(0x427001ACUL))
#define bFM0P_MFS0_LIN_BGR_BGR14               *((volatile unsigned int*)(0x427001B0UL))
#define bFM0P_MFS0_LIN_BGR_BGR15               *((volatile unsigned int*)(0x427001B4UL))
#define bFM0P_MFS0_LIN_BGR_BGR16               *((volatile unsigned int*)(0x427001B8UL))
#define bFM0P_MFS0_LIN_BGR_EXT                 *((volatile unsigned int*)(0x427001BCUL))
#define bFM0P_MFS0_LIN_FCR0_FE1                *((volatile unsigned int*)(0x42700280UL))
#define bFM0P_MFS0_LIN_FCR0_FE2                *((volatile unsigned int*)(0x42700284UL))
#define bFM0P_MFS0_LIN_FCR0_FCL1               *((volatile unsigned int*)(0x42700288UL))
#define bFM0P_MFS0_LIN_FCR0_FCL2               *((volatile unsigned int*)(0x4270028CUL))
#define bFM0P_MFS0_LIN_FCR0_FSET               *((volatile unsigned int*)(0x42700290UL))
#define bFM0P_MFS0_LIN_FCR0_FLD                *((volatile unsigned int*)(0x42700294UL))
#define bFM0P_MFS0_LIN_FCR0_FLST               *((volatile unsigned int*)(0x42700298UL))
#define bFM0P_MFS0_LIN_FCR1_FSEL               *((volatile unsigned int*)(0x427002A0UL))
#define bFM0P_MFS0_LIN_FCR1_FTIE               *((volatile unsigned int*)(0x427002A4UL))
#define bFM0P_MFS0_LIN_FCR1_FDRQ               *((volatile unsigned int*)(0x427002A8UL))
#define bFM0P_MFS0_LIN_FCR1_FRIIE              *((volatile unsigned int*)(0x427002ACUL))
#define bFM0P_MFS0_LIN_FCR1_FLSTE              *((volatile unsigned int*)(0x427002B0UL))

/* MFS I2C channel 0 registers */
#define bFM0P_MFS0_I2C_SMR_TIE                 *((volatile unsigned int*)(0x42700008UL))
#define bFM0P_MFS0_I2C_SMR_RIE                 *((volatile unsigned int*)(0x4270000CUL))
#define bFM0P_MFS0_I2C_SMR_MD0                 *((volatile unsigned int*)(0x42700014UL))
#define bFM0P_MFS0_I2C_SMR_MD1                 *((volatile unsigned int*)(0x42700018UL))
#define bFM0P_MFS0_I2C_SMR_MD2                 *((volatile unsigned int*)(0x4270001CUL))
#define bFM0P_MFS0_I2C_IBCR_INT                *((volatile unsigned int*)(0x42700020UL))
#define bFM0P_MFS0_I2C_IBCR_BER                *((volatile unsigned int*)(0x42700024UL))
#define bFM0P_MFS0_I2C_IBCR_INTE               *((volatile unsigned int*)(0x42700028UL))
#define bFM0P_MFS0_I2C_IBCR_CNDE               *((volatile unsigned int*)(0x4270002CUL))
#define bFM0P_MFS0_I2C_IBCR_WSEL               *((volatile unsigned int*)(0x42700030UL))
#define bFM0P_MFS0_I2C_IBCR_ACKE               *((volatile unsigned int*)(0x42700034UL))
#define bFM0P_MFS0_I2C_IBCR_ACT_SCC            *((volatile unsigned int*)(0x42700038UL))
#define bFM0P_MFS0_I2C_IBCR_MSS                *((volatile unsigned int*)(0x4270003CUL))
#define bFM0P_MFS0_I2C_IBSR_BB                 *((volatile unsigned int*)(0x42700080UL))
#define bFM0P_MFS0_I2C_IBSR_SPC                *((volatile unsigned int*)(0x42700084UL))
#define bFM0P_MFS0_I2C_IBSR_RSC                *((volatile unsigned int*)(0x42700088UL))
#define bFM0P_MFS0_I2C_IBSR_AL                 *((volatile unsigned int*)(0x4270008CUL))
#define bFM0P_MFS0_I2C_IBSR_TRX                *((volatile unsigned int*)(0x42700090UL))
#define bFM0P_MFS0_I2C_IBSR_RSA                *((volatile unsigned int*)(0x42700094UL))
#define bFM0P_MFS0_I2C_IBSR_RACK               *((volatile unsigned int*)(0x42700098UL))
#define bFM0P_MFS0_I2C_IBSR_FBT                *((volatile unsigned int*)(0x4270009CUL))
#define bFM0P_MFS0_I2C_SSR_TBI                 *((volatile unsigned int*)(0x427000A0UL))
#define bFM0P_MFS0_I2C_SSR_TDRE                *((volatile unsigned int*)(0x427000A4UL))
#define bFM0P_MFS0_I2C_SSR_RDRF                *((volatile unsigned int*)(0x427000A8UL))
#define bFM0P_MFS0_I2C_SSR_ORE                 *((volatile unsigned int*)(0x427000ACUL))
#define bFM0P_MFS0_I2C_SSR_TBIE                *((volatile unsigned int*)(0x427000B0UL))
#define bFM0P_MFS0_I2C_SSR_DMA                 *((volatile unsigned int*)(0x427000B4UL))
#define bFM0P_MFS0_I2C_SSR_TSET                *((volatile unsigned int*)(0x427000B8UL))
#define bFM0P_MFS0_I2C_SSR_REC                 *((volatile unsigned int*)(0x427000BCUL))
#define bFM0P_MFS0_I2C_BGR_BGR00               *((volatile unsigned int*)(0x42700180UL))
#define bFM0P_MFS0_I2C_BGR_BGR01               *((volatile unsigned int*)(0x42700184UL))
#define bFM0P_MFS0_I2C_BGR_BGR02               *((volatile unsigned int*)(0x42700188UL))
#define bFM0P_MFS0_I2C_BGR_BGR03               *((volatile unsigned int*)(0x4270018CUL))
#define bFM0P_MFS0_I2C_BGR_BGR04               *((volatile unsigned int*)(0x42700190UL))
#define bFM0P_MFS0_I2C_BGR_BGR05               *((volatile unsigned int*)(0x42700194UL))
#define bFM0P_MFS0_I2C_BGR_BGR06               *((volatile unsigned int*)(0x42700198UL))
#define bFM0P_MFS0_I2C_BGR_BGR07               *((volatile unsigned int*)(0x4270019CUL))
#define bFM0P_MFS0_I2C_BGR_BGR10               *((volatile unsigned int*)(0x427001A0UL))
#define bFM0P_MFS0_I2C_BGR_BGR11               *((volatile unsigned int*)(0x427001A4UL))
#define bFM0P_MFS0_I2C_BGR_BGR12               *((volatile unsigned int*)(0x427001A8UL))
#define bFM0P_MFS0_I2C_BGR_BGR13               *((volatile unsigned int*)(0x427001ACUL))
#define bFM0P_MFS0_I2C_BGR_BGR14               *((volatile unsigned int*)(0x427001B0UL))
#define bFM0P_MFS0_I2C_BGR_BGR15               *((volatile unsigned int*)(0x427001B4UL))
#define bFM0P_MFS0_I2C_BGR_BGR16               *((volatile unsigned int*)(0x427001B8UL))
#define bFM0P_MFS0_I2C_ISBA_SA0                *((volatile unsigned int*)(0x42700200UL))
#define bFM0P_MFS0_I2C_ISBA_SA1                *((volatile unsigned int*)(0x42700204UL))
#define bFM0P_MFS0_I2C_ISBA_SA2                *((volatile unsigned int*)(0x42700208UL))
#define bFM0P_MFS0_I2C_ISBA_SA3                *((volatile unsigned int*)(0x4270020CUL))
#define bFM0P_MFS0_I2C_ISBA_SA4                *((volatile unsigned int*)(0x42700210UL))
#define bFM0P_MFS0_I2C_ISBA_SA5                *((volatile unsigned int*)(0x42700214UL))
#define bFM0P_MFS0_I2C_ISBA_SA6                *((volatile unsigned int*)(0x42700218UL))
#define bFM0P_MFS0_I2C_ISBA_SAEN               *((volatile unsigned int*)(0x4270021CUL))
#define bFM0P_MFS0_I2C_ISMK_SM0                *((volatile unsigned int*)(0x42700220UL))
#define bFM0P_MFS0_I2C_ISMK_SM1                *((volatile unsigned int*)(0x42700224UL))
#define bFM0P_MFS0_I2C_ISMK_SM2                *((volatile unsigned int*)(0x42700228UL))
#define bFM0P_MFS0_I2C_ISMK_SM3                *((volatile unsigned int*)(0x4270022CUL))
#define bFM0P_MFS0_I2C_ISMK_SM4                *((volatile unsigned int*)(0x42700230UL))
#define bFM0P_MFS0_I2C_ISMK_SM5                *((volatile unsigned int*)(0x42700234UL))
#define bFM0P_MFS0_I2C_ISMK_SM6                *((volatile unsigned int*)(0x42700238UL))
#define bFM0P_MFS0_I2C_ISMK_EN                 *((volatile unsigned int*)(0x4270023CUL))
#define bFM0P_MFS0_I2C_FCR0_FE1                *((volatile unsigned int*)(0x42700280UL))
#define bFM0P_MFS0_I2C_FCR0_FE2                *((volatile unsigned int*)(0x42700284UL))
#define bFM0P_MFS0_I2C_FCR0_FCL1               *((volatile unsigned int*)(0x42700288UL))
#define bFM0P_MFS0_I2C_FCR0_FCL2               *((volatile unsigned int*)(0x4270028CUL))
#define bFM0P_MFS0_I2C_FCR0_FSET               *((volatile unsigned int*)(0x42700290UL))
#define bFM0P_MFS0_I2C_FCR0_FLD                *((volatile unsigned int*)(0x42700294UL))
#define bFM0P_MFS0_I2C_FCR0_FLST               *((volatile unsigned int*)(0x42700298UL))
#define bFM0P_MFS0_I2C_FCR1_FSEL               *((volatile unsigned int*)(0x427002A0UL))
#define bFM0P_MFS0_I2C_FCR1_FTIE               *((volatile unsigned int*)(0x427002A4UL))
#define bFM0P_MFS0_I2C_FCR1_FDRQ               *((volatile unsigned int*)(0x427002A8UL))
#define bFM0P_MFS0_I2C_FCR1_FRIIE              *((volatile unsigned int*)(0x427002ACUL))
#define bFM0P_MFS0_I2C_FCR1_FLSTE              *((volatile unsigned int*)(0x427002B0UL))
#define bFM0P_MFS0_I2C_EIBCR_BEC               *((volatile unsigned int*)(0x427003A0UL))
#define bFM0P_MFS0_I2C_EIBCR_SOCE              *((volatile unsigned int*)(0x427003A4UL))
#define bFM0P_MFS0_I2C_EIBCR_SCLC              *((volatile unsigned int*)(0x427003A8UL))
#define bFM0P_MFS0_I2C_EIBCR_SDAC              *((volatile unsigned int*)(0x427003ACUL))
#define bFM0P_MFS0_I2C_EIBCR_SCLS              *((volatile unsigned int*)(0x427003B0UL))
#define bFM0P_MFS0_I2C_EIBCR_SDAS              *((volatile unsigned int*)(0x427003B4UL))

/* MFS UART channel 1 registers */
#define bFM0P_MFS1_UART_SMR_SOE                *((volatile unsigned int*)(0x42702000UL))
#define bFM0P_MFS1_UART_SMR_BDS                *((volatile unsigned int*)(0x42702008UL))
#define bFM0P_MFS1_UART_SMR_SBL                *((volatile unsigned int*)(0x4270200CUL))
#define bFM0P_MFS1_UART_SMR_MD0                *((volatile unsigned int*)(0x42702014UL))
#define bFM0P_MFS1_UART_SMR_MD1                *((volatile unsigned int*)(0x42702018UL))
#define bFM0P_MFS1_UART_SMR_MD2                *((volatile unsigned int*)(0x4270201CUL))
#define bFM0P_MFS1_UART_SCR_TXE                *((volatile unsigned int*)(0x42702020UL))
#define bFM0P_MFS1_UART_SCR_RXE                *((volatile unsigned int*)(0x42702024UL))
#define bFM0P_MFS1_UART_SCR_TBIE               *((volatile unsigned int*)(0x42702028UL))
#define bFM0P_MFS1_UART_SCR_TIE                *((volatile unsigned int*)(0x4270202CUL))
#define bFM0P_MFS1_UART_SCR_RIE                *((volatile unsigned int*)(0x42702030UL))
#define bFM0P_MFS1_UART_SCR_UPCL               *((volatile unsigned int*)(0x4270203CUL))
#define bFM0P_MFS1_UART_ESCR_L0                *((volatile unsigned int*)(0x42702080UL))
#define bFM0P_MFS1_UART_ESCR_L1                *((volatile unsigned int*)(0x42702084UL))
#define bFM0P_MFS1_UART_ESCR_L2                *((volatile unsigned int*)(0x42702088UL))
#define bFM0P_MFS1_UART_ESCR_P                 *((volatile unsigned int*)(0x4270208CUL))
#define bFM0P_MFS1_UART_ESCR_PEN               *((volatile unsigned int*)(0x42702090UL))
#define bFM0P_MFS1_UART_ESCR_INV               *((volatile unsigned int*)(0x42702094UL))
#define bFM0P_MFS1_UART_ESCR_ESBL              *((volatile unsigned int*)(0x42702098UL))
#define bFM0P_MFS1_UART_ESCR_FLWEN             *((volatile unsigned int*)(0x4270209CUL))
#define bFM0P_MFS1_UART_SSR_TBI                *((volatile unsigned int*)(0x427020A0UL))
#define bFM0P_MFS1_UART_SSR_TDRE               *((volatile unsigned int*)(0x427020A4UL))
#define bFM0P_MFS1_UART_SSR_RDRF               *((volatile unsigned int*)(0x427020A8UL))
#define bFM0P_MFS1_UART_SSR_ORE                *((volatile unsigned int*)(0x427020ACUL))
#define bFM0P_MFS1_UART_SSR_FRE                *((volatile unsigned int*)(0x427020B0UL))
#define bFM0P_MFS1_UART_SSR_PE                 *((volatile unsigned int*)(0x427020B4UL))
#define bFM0P_MFS1_UART_SSR_REC                *((volatile unsigned int*)(0x427020BCUL))
#define bFM0P_MFS1_UART_BGR_BGR00              *((volatile unsigned int*)(0x42702180UL))
#define bFM0P_MFS1_UART_BGR_BGR01              *((volatile unsigned int*)(0x42702184UL))
#define bFM0P_MFS1_UART_BGR_BGR02              *((volatile unsigned int*)(0x42702188UL))
#define bFM0P_MFS1_UART_BGR_BGR03              *((volatile unsigned int*)(0x4270218CUL))
#define bFM0P_MFS1_UART_BGR_BGR04              *((volatile unsigned int*)(0x42702190UL))
#define bFM0P_MFS1_UART_BGR_BGR05              *((volatile unsigned int*)(0x42702194UL))
#define bFM0P_MFS1_UART_BGR_BGR06              *((volatile unsigned int*)(0x42702198UL))
#define bFM0P_MFS1_UART_BGR_BGR07              *((volatile unsigned int*)(0x4270219CUL))
#define bFM0P_MFS1_UART_BGR_BGR10              *((volatile unsigned int*)(0x427021A0UL))
#define bFM0P_MFS1_UART_BGR_BGR11              *((volatile unsigned int*)(0x427021A4UL))
#define bFM0P_MFS1_UART_BGR_BGR12              *((volatile unsigned int*)(0x427021A8UL))
#define bFM0P_MFS1_UART_BGR_BGR13              *((volatile unsigned int*)(0x427021ACUL))
#define bFM0P_MFS1_UART_BGR_BGR14              *((volatile unsigned int*)(0x427021B0UL))
#define bFM0P_MFS1_UART_BGR_BGR15              *((volatile unsigned int*)(0x427021B4UL))
#define bFM0P_MFS1_UART_BGR_BGR16              *((volatile unsigned int*)(0x427021B8UL))
#define bFM0P_MFS1_UART_BGR_EXT                *((volatile unsigned int*)(0x427021BCUL))
#define bFM0P_MFS1_UART_FCR0_FE1               *((volatile unsigned int*)(0x42702280UL))
#define bFM0P_MFS1_UART_FCR0_FE2               *((volatile unsigned int*)(0x42702284UL))
#define bFM0P_MFS1_UART_FCR0_FCL1              *((volatile unsigned int*)(0x42702288UL))
#define bFM0P_MFS1_UART_FCR0_FCL2              *((volatile unsigned int*)(0x4270228CUL))
#define bFM0P_MFS1_UART_FCR0_FSET              *((volatile unsigned int*)(0x42702290UL))
#define bFM0P_MFS1_UART_FCR0_FLD               *((volatile unsigned int*)(0x42702294UL))
#define bFM0P_MFS1_UART_FCR0_FLST              *((volatile unsigned int*)(0x42702298UL))
#define bFM0P_MFS1_UART_FCR0_FE1               *((volatile unsigned int*)(0x42702280UL))
#define bFM0P_MFS1_UART_FCR0_FE2               *((volatile unsigned int*)(0x42702284UL))
#define bFM0P_MFS1_UART_FCR0_FCL1              *((volatile unsigned int*)(0x42702288UL))
#define bFM0P_MFS1_UART_FCR0_FCL2              *((volatile unsigned int*)(0x4270228CUL))
#define bFM0P_MFS1_UART_FCR0_FSET              *((volatile unsigned int*)(0x42702290UL))
#define bFM0P_MFS1_UART_FCR0_FLD               *((volatile unsigned int*)(0x42702294UL))
#define bFM0P_MFS1_UART_FCR0_FLST              *((volatile unsigned int*)(0x42702298UL))
#define bFM0P_MFS1_UART_FCR1_FSEL              *((volatile unsigned int*)(0x427022A0UL))
#define bFM0P_MFS1_UART_FCR1_FTIE              *((volatile unsigned int*)(0x427022A4UL))
#define bFM0P_MFS1_UART_FCR1_FDRQ              *((volatile unsigned int*)(0x427022A8UL))
#define bFM0P_MFS1_UART_FCR1_FRIIE             *((volatile unsigned int*)(0x427022ACUL))
#define bFM0P_MFS1_UART_FCR1_FLSTE             *((volatile unsigned int*)(0x427022B0UL))

/* MFS CSIO channel 1 registers */
#define bFM0P_MFS1_CSIO_SMR_SOE                *((volatile unsigned int*)(0x42702000UL))
#define bFM0P_MFS1_CSIO_SMR_SCKE               *((volatile unsigned int*)(0x42702004UL))
#define bFM0P_MFS1_CSIO_SMR_BDS                *((volatile unsigned int*)(0x42702008UL))
#define bFM0P_MFS1_CSIO_SMR_SCINV              *((volatile unsigned int*)(0x4270200CUL))
#define bFM0P_MFS1_CSIO_SMR_MD0                *((volatile unsigned int*)(0x42702014UL))
#define bFM0P_MFS1_CSIO_SMR_MD1                *((volatile unsigned int*)(0x42702018UL))
#define bFM0P_MFS1_CSIO_SMR_MD2                *((volatile unsigned int*)(0x4270201CUL))
#define bFM0P_MFS1_CSIO_SCR_TXE                *((volatile unsigned int*)(0x42702020UL))
#define bFM0P_MFS1_CSIO_SCR_RXE                *((volatile unsigned int*)(0x42702024UL))
#define bFM0P_MFS1_CSIO_SCR_TBIE               *((volatile unsigned int*)(0x42702028UL))
#define bFM0P_MFS1_CSIO_SCR_TIE                *((volatile unsigned int*)(0x4270202CUL))
#define bFM0P_MFS1_CSIO_SCR_RIE                *((volatile unsigned int*)(0x42702030UL))
#define bFM0P_MFS1_CSIO_SCR_SPI                *((volatile unsigned int*)(0x42702034UL))
#define bFM0P_MFS1_CSIO_SCR_MS                 *((volatile unsigned int*)(0x42702038UL))
#define bFM0P_MFS1_CSIO_SCR_UPCL               *((volatile unsigned int*)(0x4270203CUL))
#define bFM0P_MFS1_CSIO_ESCR_L0                *((volatile unsigned int*)(0x42702080UL))
#define bFM0P_MFS1_CSIO_ESCR_L1                *((volatile unsigned int*)(0x42702084UL))
#define bFM0P_MFS1_CSIO_ESCR_L2                *((volatile unsigned int*)(0x42702088UL))
#define bFM0P_MFS1_CSIO_ESCR_WT0               *((volatile unsigned int*)(0x4270208CUL))
#define bFM0P_MFS1_CSIO_ESCR_WT1               *((volatile unsigned int*)(0x42702090UL))
#define bFM0P_MFS1_CSIO_ESCR_CSFE              *((volatile unsigned int*)(0x42702094UL))
#define bFM0P_MFS1_CSIO_ESCR_L3                *((volatile unsigned int*)(0x42702098UL))
#define bFM0P_MFS1_CSIO_ESCR_SOP               *((volatile unsigned int*)(0x4270209CUL))
#define bFM0P_MFS1_CSIO_SSR_TBI                *((volatile unsigned int*)(0x427020A0UL))
#define bFM0P_MFS1_CSIO_SSR_TDRE               *((volatile unsigned int*)(0x427020A4UL))
#define bFM0P_MFS1_CSIO_SSR_RDRF               *((volatile unsigned int*)(0x427020A8UL))
#define bFM0P_MFS1_CSIO_SSR_ORE                *((volatile unsigned int*)(0x427020ACUL))
#define bFM0P_MFS1_CSIO_SSR_REC                *((volatile unsigned int*)(0x427020BCUL))
#define bFM0P_MFS1_CSIO_BGR_BGR00              *((volatile unsigned int*)(0x42702180UL))
#define bFM0P_MFS1_CSIO_BGR_BGR01              *((volatile unsigned int*)(0x42702184UL))
#define bFM0P_MFS1_CSIO_BGR_BGR02              *((volatile unsigned int*)(0x42702188UL))
#define bFM0P_MFS1_CSIO_BGR_BGR03              *((volatile unsigned int*)(0x4270218CUL))
#define bFM0P_MFS1_CSIO_BGR_BGR04              *((volatile unsigned int*)(0x42702190UL))
#define bFM0P_MFS1_CSIO_BGR_BGR05              *((volatile unsigned int*)(0x42702194UL))
#define bFM0P_MFS1_CSIO_BGR_BGR06              *((volatile unsigned int*)(0x42702198UL))
#define bFM0P_MFS1_CSIO_BGR_BGR07              *((volatile unsigned int*)(0x4270219CUL))
#define bFM0P_MFS1_CSIO_BGR_BGR10              *((volatile unsigned int*)(0x427021A0UL))
#define bFM0P_MFS1_CSIO_BGR_BGR11              *((volatile unsigned int*)(0x427021A4UL))
#define bFM0P_MFS1_CSIO_BGR_BGR12              *((volatile unsigned int*)(0x427021A8UL))
#define bFM0P_MFS1_CSIO_BGR_BGR13              *((volatile unsigned int*)(0x427021ACUL))
#define bFM0P_MFS1_CSIO_BGR_BGR14              *((volatile unsigned int*)(0x427021B0UL))
#define bFM0P_MFS1_CSIO_BGR_BGR15              *((volatile unsigned int*)(0x427021B4UL))
#define bFM0P_MFS1_CSIO_BGR_BGR16              *((volatile unsigned int*)(0x427021B8UL))
#define bFM0P_MFS1_CSIO_FCR0_FE1               *((volatile unsigned int*)(0x42702280UL))
#define bFM0P_MFS1_CSIO_FCR0_FE2               *((volatile unsigned int*)(0x42702284UL))
#define bFM0P_MFS1_CSIO_FCR0_FCL1              *((volatile unsigned int*)(0x42702288UL))
#define bFM0P_MFS1_CSIO_FCR0_FCL2              *((volatile unsigned int*)(0x4270228CUL))
#define bFM0P_MFS1_CSIO_FCR0_FSET              *((volatile unsigned int*)(0x42702290UL))
#define bFM0P_MFS1_CSIO_FCR0_FLD               *((volatile unsigned int*)(0x42702294UL))
#define bFM0P_MFS1_CSIO_FCR0_FLST              *((volatile unsigned int*)(0x42702298UL))
#define bFM0P_MFS1_CSIO_FCR1_FSEL              *((volatile unsigned int*)(0x427022A0UL))
#define bFM0P_MFS1_CSIO_FCR1_FTIE              *((volatile unsigned int*)(0x427022A4UL))
#define bFM0P_MFS1_CSIO_FCR1_FDRQ              *((volatile unsigned int*)(0x427022A8UL))
#define bFM0P_MFS1_CSIO_FCR1_FRIIE             *((volatile unsigned int*)(0x427022ACUL))
#define bFM0P_MFS1_CSIO_FCR1_FLSTE             *((volatile unsigned int*)(0x427022B0UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD0           *((volatile unsigned int*)(0x42702380UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD1           *((volatile unsigned int*)(0x42702384UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD2           *((volatile unsigned int*)(0x42702388UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD3           *((volatile unsigned int*)(0x4270238CUL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD4           *((volatile unsigned int*)(0x42702390UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD5           *((volatile unsigned int*)(0x42702394UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD6           *((volatile unsigned int*)(0x42702398UL))
#define bFM0P_MFS1_CSIO_SCSTR0_CSHD7           *((volatile unsigned int*)(0x4270239CUL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU0           *((volatile unsigned int*)(0x427023A0UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU1           *((volatile unsigned int*)(0x427023A4UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU2           *((volatile unsigned int*)(0x427023A8UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU3           *((volatile unsigned int*)(0x427023ACUL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU4           *((volatile unsigned int*)(0x427023B0UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU5           *((volatile unsigned int*)(0x427023B4UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU6           *((volatile unsigned int*)(0x427023B8UL))
#define bFM0P_MFS1_CSIO_SCSTR1_CSSU7           *((volatile unsigned int*)(0x427023BCUL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS0          *((volatile unsigned int*)(0x42702400UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS1          *((volatile unsigned int*)(0x42702404UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS2          *((volatile unsigned int*)(0x42702408UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS3          *((volatile unsigned int*)(0x4270240CUL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS4          *((volatile unsigned int*)(0x42702410UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS5          *((volatile unsigned int*)(0x42702414UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS6          *((volatile unsigned int*)(0x42702418UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS7          *((volatile unsigned int*)(0x4270241CUL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS8          *((volatile unsigned int*)(0x42702420UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS9          *((volatile unsigned int*)(0x42702424UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS10         *((volatile unsigned int*)(0x42702428UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS11         *((volatile unsigned int*)(0x4270242CUL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS12         *((volatile unsigned int*)(0x42702430UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS13         *((volatile unsigned int*)(0x42702434UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS14         *((volatile unsigned int*)(0x42702438UL))
#define bFM0P_MFS1_CSIO_SCSTR32_CSDS15         *((volatile unsigned int*)(0x4270243CUL))
#define bFM0P_MFS1_CSIO_SACSR_TMRE             *((volatile unsigned int*)(0x42702480UL))
#define bFM0P_MFS1_CSIO_SACSR_TDIV0            *((volatile unsigned int*)(0x42702484UL))
#define bFM0P_MFS1_CSIO_SACSR_TDIV1            *((volatile unsigned int*)(0x42702488UL))
#define bFM0P_MFS1_CSIO_SACSR_TDIV2            *((volatile unsigned int*)(0x4270248CUL))
#define bFM0P_MFS1_CSIO_SACSR_TDIV3            *((volatile unsigned int*)(0x42702490UL))
#define bFM0P_MFS1_CSIO_SACSR_TSYNE            *((volatile unsigned int*)(0x42702498UL))
#define bFM0P_MFS1_CSIO_SACSR_TINTE            *((volatile unsigned int*)(0x4270249CUL))
#define bFM0P_MFS1_CSIO_SACSR_TINT             *((volatile unsigned int*)(0x427024A0UL))
#define bFM0P_MFS1_CSIO_SACSR_CSE              *((volatile unsigned int*)(0x427024ACUL))
#define bFM0P_MFS1_CSIO_SACSR_CSEIE            *((volatile unsigned int*)(0x427024B0UL))
#define bFM0P_MFS1_CSIO_SACSR_TBEEN            *((volatile unsigned int*)(0x427024B4UL))
#define bFM0P_MFS1_CSIO_STMR_TM0               *((volatile unsigned int*)(0x42702500UL))
#define bFM0P_MFS1_CSIO_STMR_TM1               *((volatile unsigned int*)(0x42702504UL))
#define bFM0P_MFS1_CSIO_STMR_TM2               *((volatile unsigned int*)(0x42702508UL))
#define bFM0P_MFS1_CSIO_STMR_TM3               *((volatile unsigned int*)(0x4270250CUL))
#define bFM0P_MFS1_CSIO_STMR_TM4               *((volatile unsigned int*)(0x42702510UL))
#define bFM0P_MFS1_CSIO_STMR_TM5               *((volatile unsigned int*)(0x42702514UL))
#define bFM0P_MFS1_CSIO_STMR_TM6               *((volatile unsigned int*)(0x42702518UL))
#define bFM0P_MFS1_CSIO_STMR_TM7               *((volatile unsigned int*)(0x4270251CUL))
#define bFM0P_MFS1_CSIO_STMR_TM8               *((volatile unsigned int*)(0x42702520UL))
#define bFM0P_MFS1_CSIO_STMR_TM9               *((volatile unsigned int*)(0x42702524UL))
#define bFM0P_MFS1_CSIO_STMR_TM10              *((volatile unsigned int*)(0x42702528UL))
#define bFM0P_MFS1_CSIO_STMR_TM11              *((volatile unsigned int*)(0x4270252CUL))
#define bFM0P_MFS1_CSIO_STMR_TM12              *((volatile unsigned int*)(0x42702530UL))
#define bFM0P_MFS1_CSIO_STMR_TM13              *((volatile unsigned int*)(0x42702534UL))
#define bFM0P_MFS1_CSIO_STMR_TM14              *((volatile unsigned int*)(0x42702538UL))
#define bFM0P_MFS1_CSIO_STMR_TM15              *((volatile unsigned int*)(0x4270253CUL))
#define bFM0P_MFS1_CSIO_TMCR_TC0               *((volatile unsigned int*)(0x42702580UL))
#define bFM0P_MFS1_CSIO_TMCR_TC1               *((volatile unsigned int*)(0x42702584UL))
#define bFM0P_MFS1_CSIO_TMCR_TC2               *((volatile unsigned int*)(0x42702588UL))
#define bFM0P_MFS1_CSIO_TMCR_TC3               *((volatile unsigned int*)(0x4270258CUL))
#define bFM0P_MFS1_CSIO_TMCR_TC4               *((volatile unsigned int*)(0x42702590UL))
#define bFM0P_MFS1_CSIO_TMCR_TC5               *((volatile unsigned int*)(0x42702594UL))
#define bFM0P_MFS1_CSIO_TMCR_TC6               *((volatile unsigned int*)(0x42702598UL))
#define bFM0P_MFS1_CSIO_TMCR_TC7               *((volatile unsigned int*)(0x4270259CUL))
#define bFM0P_MFS1_CSIO_TMCR_TC8               *((volatile unsigned int*)(0x427025A0UL))
#define bFM0P_MFS1_CSIO_TMCR_TC9               *((volatile unsigned int*)(0x427025A4UL))
#define bFM0P_MFS1_CSIO_TMCR_TC10              *((volatile unsigned int*)(0x427025A8UL))
#define bFM0P_MFS1_CSIO_TMCR_TC11              *((volatile unsigned int*)(0x427025ACUL))
#define bFM0P_MFS1_CSIO_TMCR_TC12              *((volatile unsigned int*)(0x427025B0UL))
#define bFM0P_MFS1_CSIO_TMCR_TC13              *((volatile unsigned int*)(0x427025B4UL))
#define bFM0P_MFS1_CSIO_TMCR_TC14              *((volatile unsigned int*)(0x427025B8UL))
#define bFM0P_MFS1_CSIO_TMCR_TC15              *((volatile unsigned int*)(0x427025BCUL))
#define bFM0P_MFS1_CSIO_SCSCR_CSOE             *((volatile unsigned int*)(0x42702600UL))
#define bFM0P_MFS1_CSIO_SCSCR_CSEN0            *((volatile unsigned int*)(0x42702604UL))
#define bFM0P_MFS1_CSIO_SCSCR_CSEN1            *((volatile unsigned int*)(0x42702608UL))
#define bFM0P_MFS1_CSIO_SCSCR_CSEN2            *((volatile unsigned int*)(0x4270260CUL))
#define bFM0P_MFS1_CSIO_SCSCR_CSEN3            *((volatile unsigned int*)(0x42702610UL))
#define bFM0P_MFS1_CSIO_SCSCR_CSLVL            *((volatile unsigned int*)(0x42702614UL))
#define bFM0P_MFS1_CSIO_SCSCR_CDIV0            *((volatile unsigned int*)(0x42702618UL))
#define bFM0P_MFS1_CSIO_SCSCR_CDIV1            *((volatile unsigned int*)(0x4270261CUL))
#define bFM0P_MFS1_CSIO_SCSCR_CDIV2            *((volatile unsigned int*)(0x42702620UL))
#define bFM0P_MFS1_CSIO_SCSCR_SCAM             *((volatile unsigned int*)(0x42702624UL))
#define bFM0P_MFS1_CSIO_SCSCR_SCD0             *((volatile unsigned int*)(0x42702628UL))
#define bFM0P_MFS1_CSIO_SCSCR_SCD1             *((volatile unsigned int*)(0x4270262CUL))
#define bFM0P_MFS1_CSIO_SCSCR_SED0             *((volatile unsigned int*)(0x42702630UL))
#define bFM0P_MFS1_CSIO_SCSCR_SED1             *((volatile unsigned int*)(0x42702634UL))
#define bFM0P_MFS1_CSIO_SCSCR_SST0             *((volatile unsigned int*)(0x42702638UL))
#define bFM0P_MFS1_CSIO_SCSCR_SST1             *((volatile unsigned int*)(0x4270263CUL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1L0           *((volatile unsigned int*)(0x42702680UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1L1           *((volatile unsigned int*)(0x42702684UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1L2           *((volatile unsigned int*)(0x42702688UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1L3           *((volatile unsigned int*)(0x4270268CUL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1BDS          *((volatile unsigned int*)(0x42702690UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1SPI          *((volatile unsigned int*)(0x42702694UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1SCINV        *((volatile unsigned int*)(0x42702698UL))
#define bFM0P_MFS1_CSIO_SCSFR0_CS1CSLVL        *((volatile unsigned int*)(0x4270269CUL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2L0           *((volatile unsigned int*)(0x427026A0UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2L1           *((volatile unsigned int*)(0x427026A4UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2L2           *((volatile unsigned int*)(0x427026A8UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2L3           *((volatile unsigned int*)(0x427026ACUL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2BDS          *((volatile unsigned int*)(0x427026B0UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2SPI          *((volatile unsigned int*)(0x427026B4UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2SCINV        *((volatile unsigned int*)(0x427026B8UL))
#define bFM0P_MFS1_CSIO_SCSFR1_CS2CSLVL        *((volatile unsigned int*)(0x427026BCUL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3L0           *((volatile unsigned int*)(0x42702700UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3L1           *((volatile unsigned int*)(0x42702704UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3L2           *((volatile unsigned int*)(0x42702708UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3L3           *((volatile unsigned int*)(0x4270270CUL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3BDS          *((volatile unsigned int*)(0x42702710UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3SPI          *((volatile unsigned int*)(0x42702714UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3SCINV        *((volatile unsigned int*)(0x42702718UL))
#define bFM0P_MFS1_CSIO_SCSFR3_CS3CSLVL        *((volatile unsigned int*)(0x4270271CUL))

/* MFS LIN channel 1 registers */
#define bFM0P_MFS1_LIN_SMR_SOE                 *((volatile unsigned int*)(0x42702000UL))
#define bFM0P_MFS1_LIN_SMR_SBL                 *((volatile unsigned int*)(0x4270200CUL))
#define bFM0P_MFS1_LIN_SMR_MD0                 *((volatile unsigned int*)(0x42702014UL))
#define bFM0P_MFS1_LIN_SMR_MD1                 *((volatile unsigned int*)(0x42702018UL))
#define bFM0P_MFS1_LIN_SMR_MD2                 *((volatile unsigned int*)(0x4270201CUL))
#define bFM0P_MFS1_LIN_SCR_TXE                 *((volatile unsigned int*)(0x42702020UL))
#define bFM0P_MFS1_LIN_SCR_RXE                 *((volatile unsigned int*)(0x42702024UL))
#define bFM0P_MFS1_LIN_SCR_TBIE                *((volatile unsigned int*)(0x42702028UL))
#define bFM0P_MFS1_LIN_SCR_TIE                 *((volatile unsigned int*)(0x4270202CUL))
#define bFM0P_MFS1_LIN_SCR_RIE                 *((volatile unsigned int*)(0x42702030UL))
#define bFM0P_MFS1_LIN_SCR_LBR                 *((volatile unsigned int*)(0x42702034UL))
#define bFM0P_MFS1_LIN_SCR_MS                  *((volatile unsigned int*)(0x42702038UL))
#define bFM0P_MFS1_LIN_SCR_UPCL                *((volatile unsigned int*)(0x4270203CUL))
#define bFM0P_MFS1_LIN_ESCR_DEL0               *((volatile unsigned int*)(0x42702080UL))
#define bFM0P_MFS1_LIN_ESCR_DEL1               *((volatile unsigned int*)(0x42702084UL))
#define bFM0P_MFS1_LIN_ESCR_LBL0               *((volatile unsigned int*)(0x42702088UL))
#define bFM0P_MFS1_LIN_ESCR_LBL1               *((volatile unsigned int*)(0x4270208CUL))
#define bFM0P_MFS1_LIN_ESCR_LBIE               *((volatile unsigned int*)(0x42702090UL))
#define bFM0P_MFS1_LIN_ESCR_ESBL               *((volatile unsigned int*)(0x42702098UL))
#define bFM0P_MFS1_LIN_SSR_TBI                 *((volatile unsigned int*)(0x427020A0UL))
#define bFM0P_MFS1_LIN_SSR_TDRE                *((volatile unsigned int*)(0x427020A4UL))
#define bFM0P_MFS1_LIN_SSR_RDRF                *((volatile unsigned int*)(0x427020A8UL))
#define bFM0P_MFS1_LIN_SSR_ORE                 *((volatile unsigned int*)(0x427020ACUL))
#define bFM0P_MFS1_LIN_SSR_FRE                 *((volatile unsigned int*)(0x427020B0UL))
#define bFM0P_MFS1_LIN_SSR_LBD                 *((volatile unsigned int*)(0x427020B4UL))
#define bFM0P_MFS1_LIN_SSR_REC                 *((volatile unsigned int*)(0x427020BCUL))
#define bFM0P_MFS1_LIN_BGR_BGR00               *((volatile unsigned int*)(0x42702180UL))
#define bFM0P_MFS1_LIN_BGR_BGR01               *((volatile unsigned int*)(0x42702184UL))
#define bFM0P_MFS1_LIN_BGR_BGR02               *((volatile unsigned int*)(0x42702188UL))
#define bFM0P_MFS1_LIN_BGR_BGR03               *((volatile unsigned int*)(0x4270218CUL))
#define bFM0P_MFS1_LIN_BGR_BGR04               *((volatile unsigned int*)(0x42702190UL))
#define bFM0P_MFS1_LIN_BGR_BGR05               *((volatile unsigned int*)(0x42702194UL))
#define bFM0P_MFS1_LIN_BGR_BGR06               *((volatile unsigned int*)(0x42702198UL))
#define bFM0P_MFS1_LIN_BGR_BGR07               *((volatile unsigned int*)(0x4270219CUL))
#define bFM0P_MFS1_LIN_BGR_BGR10               *((volatile unsigned int*)(0x427021A0UL))
#define bFM0P_MFS1_LIN_BGR_BGR11               *((volatile unsigned int*)(0x427021A4UL))
#define bFM0P_MFS1_LIN_BGR_BGR12               *((volatile unsigned int*)(0x427021A8UL))
#define bFM0P_MFS1_LIN_BGR_BGR13               *((volatile unsigned int*)(0x427021ACUL))
#define bFM0P_MFS1_LIN_BGR_BGR14               *((volatile unsigned int*)(0x427021B0UL))
#define bFM0P_MFS1_LIN_BGR_BGR15               *((volatile unsigned int*)(0x427021B4UL))
#define bFM0P_MFS1_LIN_BGR_BGR16               *((volatile unsigned int*)(0x427021B8UL))
#define bFM0P_MFS1_LIN_BGR_EXT                 *((volatile unsigned int*)(0x427021BCUL))
#define bFM0P_MFS1_LIN_FCR0_FE1                *((volatile unsigned int*)(0x42702280UL))
#define bFM0P_MFS1_LIN_FCR0_FE2                *((volatile unsigned int*)(0x42702284UL))
#define bFM0P_MFS1_LIN_FCR0_FCL1               *((volatile unsigned int*)(0x42702288UL))
#define bFM0P_MFS1_LIN_FCR0_FCL2               *((volatile unsigned int*)(0x4270228CUL))
#define bFM0P_MFS1_LIN_FCR0_FSET               *((volatile unsigned int*)(0x42702290UL))
#define bFM0P_MFS1_LIN_FCR0_FLD                *((volatile unsigned int*)(0x42702294UL))
#define bFM0P_MFS1_LIN_FCR0_FLST               *((volatile unsigned int*)(0x42702298UL))
#define bFM0P_MFS1_LIN_FCR1_FSEL               *((volatile unsigned int*)(0x427022A0UL))
#define bFM0P_MFS1_LIN_FCR1_FTIE               *((volatile unsigned int*)(0x427022A4UL))
#define bFM0P_MFS1_LIN_FCR1_FDRQ               *((volatile unsigned int*)(0x427022A8UL))
#define bFM0P_MFS1_LIN_FCR1_FRIIE              *((volatile unsigned int*)(0x427022ACUL))
#define bFM0P_MFS1_LIN_FCR1_FLSTE              *((volatile unsigned int*)(0x427022B0UL))

/* MFS I2C channel 1 registers */
#define bFM0P_MFS1_I2C_SMR_TIE                 *((volatile unsigned int*)(0x42702008UL))
#define bFM0P_MFS1_I2C_SMR_RIE                 *((volatile unsigned int*)(0x4270200CUL))
#define bFM0P_MFS1_I2C_SMR_MD0                 *((volatile unsigned int*)(0x42702014UL))
#define bFM0P_MFS1_I2C_SMR_MD1                 *((volatile unsigned int*)(0x42702018UL))
#define bFM0P_MFS1_I2C_SMR_MD2                 *((volatile unsigned int*)(0x4270201CUL))
#define bFM0P_MFS1_I2C_IBCR_INT                *((volatile unsigned int*)(0x42702020UL))
#define bFM0P_MFS1_I2C_IBCR_BER                *((volatile unsigned int*)(0x42702024UL))
#define bFM0P_MFS1_I2C_IBCR_INTE               *((volatile unsigned int*)(0x42702028UL))
#define bFM0P_MFS1_I2C_IBCR_CNDE               *((volatile unsigned int*)(0x4270202CUL))
#define bFM0P_MFS1_I2C_IBCR_WSEL               *((volatile unsigned int*)(0x42702030UL))
#define bFM0P_MFS1_I2C_IBCR_ACKE               *((volatile unsigned int*)(0x42702034UL))
#define bFM0P_MFS1_I2C_IBCR_ACT_SCC            *((volatile unsigned int*)(0x42702038UL))
#define bFM0P_MFS1_I2C_IBCR_MSS                *((volatile unsigned int*)(0x4270203CUL))
#define bFM0P_MFS1_I2C_IBSR_BB                 *((volatile unsigned int*)(0x42702080UL))
#define bFM0P_MFS1_I2C_IBSR_SPC                *((volatile unsigned int*)(0x42702084UL))
#define bFM0P_MFS1_I2C_IBSR_RSC                *((volatile unsigned int*)(0x42702088UL))
#define bFM0P_MFS1_I2C_IBSR_AL                 *((volatile unsigned int*)(0x4270208CUL))
#define bFM0P_MFS1_I2C_IBSR_TRX                *((volatile unsigned int*)(0x42702090UL))
#define bFM0P_MFS1_I2C_IBSR_RSA                *((volatile unsigned int*)(0x42702094UL))
#define bFM0P_MFS1_I2C_IBSR_RACK               *((volatile unsigned int*)(0x42702098UL))
#define bFM0P_MFS1_I2C_IBSR_FBT                *((volatile unsigned int*)(0x4270209CUL))
#define bFM0P_MFS1_I2C_SSR_TBI                 *((volatile unsigned int*)(0x427020A0UL))
#define bFM0P_MFS1_I2C_SSR_TDRE                *((volatile unsigned int*)(0x427020A4UL))
#define bFM0P_MFS1_I2C_SSR_RDRF                *((volatile unsigned int*)(0x427020A8UL))
#define bFM0P_MFS1_I2C_SSR_ORE                 *((volatile unsigned int*)(0x427020ACUL))
#define bFM0P_MFS1_I2C_SSR_TBIE                *((volatile unsigned int*)(0x427020B0UL))
#define bFM0P_MFS1_I2C_SSR_DMA                 *((volatile unsigned int*)(0x427020B4UL))
#define bFM0P_MFS1_I2C_SSR_TSET                *((volatile unsigned int*)(0x427020B8UL))
#define bFM0P_MFS1_I2C_SSR_REC                 *((volatile unsigned int*)(0x427020BCUL))
#define bFM0P_MFS1_I2C_BGR_BGR00               *((volatile unsigned int*)(0x42702180UL))
#define bFM0P_MFS1_I2C_BGR_BGR01               *((volatile unsigned int*)(0x42702184UL))
#define bFM0P_MFS1_I2C_BGR_BGR02               *((volatile unsigned int*)(0x42702188UL))
#define bFM0P_MFS1_I2C_BGR_BGR03               *((volatile unsigned int*)(0x4270218CUL))
#define bFM0P_MFS1_I2C_BGR_BGR04               *((volatile unsigned int*)(0x42702190UL))
#define bFM0P_MFS1_I2C_BGR_BGR05               *((volatile unsigned int*)(0x42702194UL))
#define bFM0P_MFS1_I2C_BGR_BGR06               *((volatile unsigned int*)(0x42702198UL))
#define bFM0P_MFS1_I2C_BGR_BGR07               *((volatile unsigned int*)(0x4270219CUL))
#define bFM0P_MFS1_I2C_BGR_BGR10               *((volatile unsigned int*)(0x427021A0UL))
#define bFM0P_MFS1_I2C_BGR_BGR11               *((volatile unsigned int*)(0x427021A4UL))
#define bFM0P_MFS1_I2C_BGR_BGR12               *((volatile unsigned int*)(0x427021A8UL))
#define bFM0P_MFS1_I2C_BGR_BGR13               *((volatile unsigned int*)(0x427021ACUL))
#define bFM0P_MFS1_I2C_BGR_BGR14               *((volatile unsigned int*)(0x427021B0UL))
#define bFM0P_MFS1_I2C_BGR_BGR15               *((volatile unsigned int*)(0x427021B4UL))
#define bFM0P_MFS1_I2C_BGR_BGR16               *((volatile unsigned int*)(0x427021B8UL))
#define bFM0P_MFS1_I2C_ISBA_SA0                *((volatile unsigned int*)(0x42702200UL))
#define bFM0P_MFS1_I2C_ISBA_SA1                *((volatile unsigned int*)(0x42702204UL))
#define bFM0P_MFS1_I2C_ISBA_SA2                *((volatile unsigned int*)(0x42702208UL))
#define bFM0P_MFS1_I2C_ISBA_SA3                *((volatile unsigned int*)(0x4270220CUL))
#define bFM0P_MFS1_I2C_ISBA_SA4                *((volatile unsigned int*)(0x42702210UL))
#define bFM0P_MFS1_I2C_ISBA_SA5                *((volatile unsigned int*)(0x42702214UL))
#define bFM0P_MFS1_I2C_ISBA_SA6                *((volatile unsigned int*)(0x42702218UL))
#define bFM0P_MFS1_I2C_ISBA_SAEN               *((volatile unsigned int*)(0x4270221CUL))
#define bFM0P_MFS1_I2C_ISMK_SM0                *((volatile unsigned int*)(0x42702220UL))
#define bFM0P_MFS1_I2C_ISMK_SM1                *((volatile unsigned int*)(0x42702224UL))
#define bFM0P_MFS1_I2C_ISMK_SM2                *((volatile unsigned int*)(0x42702228UL))
#define bFM0P_MFS1_I2C_ISMK_SM3                *((volatile unsigned int*)(0x4270222CUL))
#define bFM0P_MFS1_I2C_ISMK_SM4                *((volatile unsigned int*)(0x42702230UL))
#define bFM0P_MFS1_I2C_ISMK_SM5                *((volatile unsigned int*)(0x42702234UL))
#define bFM0P_MFS1_I2C_ISMK_SM6                *((volatile unsigned int*)(0x42702238UL))
#define bFM0P_MFS1_I2C_ISMK_EN                 *((volatile unsigned int*)(0x4270223CUL))
#define bFM0P_MFS1_I2C_FCR0_FE1                *((volatile unsigned int*)(0x42702280UL))
#define bFM0P_MFS1_I2C_FCR0_FE2                *((volatile unsigned int*)(0x42702284UL))
#define bFM0P_MFS1_I2C_FCR0_FCL1               *((volatile unsigned int*)(0x42702288UL))
#define bFM0P_MFS1_I2C_FCR0_FCL2               *((volatile unsigned int*)(0x4270228CUL))
#define bFM0P_MFS1_I2C_FCR0_FSET               *((volatile unsigned int*)(0x42702290UL))
#define bFM0P_MFS1_I2C_FCR0_FLD                *((volatile unsigned int*)(0x42702294UL))
#define bFM0P_MFS1_I2C_FCR0_FLST               *((volatile unsigned int*)(0x42702298UL))
#define bFM0P_MFS1_I2C_FCR1_FSEL               *((volatile unsigned int*)(0x427022A0UL))
#define bFM0P_MFS1_I2C_FCR1_FTIE               *((volatile unsigned int*)(0x427022A4UL))
#define bFM0P_MFS1_I2C_FCR1_FDRQ               *((volatile unsigned int*)(0x427022A8UL))
#define bFM0P_MFS1_I2C_FCR1_FRIIE              *((volatile unsigned int*)(0x427022ACUL))
#define bFM0P_MFS1_I2C_FCR1_FLSTE              *((volatile unsigned int*)(0x427022B0UL))
#define bFM0P_MFS1_I2C_EIBCR_BEC               *((volatile unsigned int*)(0x427023A0UL))
#define bFM0P_MFS1_I2C_EIBCR_SOCE              *((volatile unsigned int*)(0x427023A4UL))
#define bFM0P_MFS1_I2C_EIBCR_SCLC              *((volatile unsigned int*)(0x427023A8UL))
#define bFM0P_MFS1_I2C_EIBCR_SDAC              *((volatile unsigned int*)(0x427023ACUL))
#define bFM0P_MFS1_I2C_EIBCR_SCLS              *((volatile unsigned int*)(0x427023B0UL))
#define bFM0P_MFS1_I2C_EIBCR_SDAS              *((volatile unsigned int*)(0x427023B4UL))

/* MFS3 UART channel 3 register */
#define bFM0P_MFS3_UART_SMR_SOE                *((volatile unsigned int*)(0x42706000UL))
#define bFM0P_MFS3_UART_SMR_BDS                *((volatile unsigned int*)(0x42706008UL))
#define bFM0P_MFS3_UART_SMR_SBL                *((volatile unsigned int*)(0x4270600CUL))
#define bFM0P_MFS3_UART_SMR_MD0                *((volatile unsigned int*)(0x42706014UL))
#define bFM0P_MFS3_UART_SMR_MD1                *((volatile unsigned int*)(0x42706018UL))
#define bFM0P_MFS3_UART_SMR_MD2                *((volatile unsigned int*)(0x4270601CUL))
#define bFM0P_MFS3_UART_SCR_TXE                *((volatile unsigned int*)(0x42706020UL))
#define bFM0P_MFS3_UART_SCR_RXE                *((volatile unsigned int*)(0x42706024UL))
#define bFM0P_MFS3_UART_SCR_TBIE               *((volatile unsigned int*)(0x42706028UL))
#define bFM0P_MFS3_UART_SCR_TIE                *((volatile unsigned int*)(0x4270602CUL))
#define bFM0P_MFS3_UART_SCR_RIE                *((volatile unsigned int*)(0x42706030UL))
#define bFM0P_MFS3_UART_SCR_UPCL               *((volatile unsigned int*)(0x4270603CUL))
#define bFM0P_MFS3_UART_ESCR_L0                *((volatile unsigned int*)(0x42706080UL))
#define bFM0P_MFS3_UART_ESCR_L1                *((volatile unsigned int*)(0x42706084UL))
#define bFM0P_MFS3_UART_ESCR_L2                *((volatile unsigned int*)(0x42706088UL))
#define bFM0P_MFS3_UART_ESCR_P                 *((volatile unsigned int*)(0x4270608CUL))
#define bFM0P_MFS3_UART_ESCR_PEN               *((volatile unsigned int*)(0x42706090UL))
#define bFM0P_MFS3_UART_ESCR_INV               *((volatile unsigned int*)(0x42706094UL))
#define bFM0P_MFS3_UART_ESCR_ESBL              *((volatile unsigned int*)(0x42706098UL))
#define bFM0P_MFS3_UART_ESCR_FLWEN             *((volatile unsigned int*)(0x4270609CUL))
#define bFM0P_MFS3_UART_SSR_TBI                *((volatile unsigned int*)(0x427060A0UL))
#define bFM0P_MFS3_UART_SSR_TDRE               *((volatile unsigned int*)(0x427060A4UL))
#define bFM0P_MFS3_UART_SSR_RDRF               *((volatile unsigned int*)(0x427060A8UL))
#define bFM0P_MFS3_UART_SSR_ORE                *((volatile unsigned int*)(0x427060ACUL))
#define bFM0P_MFS3_UART_SSR_FRE                *((volatile unsigned int*)(0x427060B0UL))
#define bFM0P_MFS3_UART_SSR_PE                 *((volatile unsigned int*)(0x427060B4UL))
#define bFM0P_MFS3_UART_SSR_REC                *((volatile unsigned int*)(0x427060BCUL))
#define bFM0P_MFS3_UART_BGR_BGR00              *((volatile unsigned int*)(0x42706180UL))
#define bFM0P_MFS3_UART_BGR_BGR01              *((volatile unsigned int*)(0x42706184UL))
#define bFM0P_MFS3_UART_BGR_BGR02              *((volatile unsigned int*)(0x42706188UL))
#define bFM0P_MFS3_UART_BGR_BGR03              *((volatile unsigned int*)(0x4270618CUL))
#define bFM0P_MFS3_UART_BGR_BGR04              *((volatile unsigned int*)(0x42706190UL))
#define bFM0P_MFS3_UART_BGR_BGR05              *((volatile unsigned int*)(0x42706194UL))
#define bFM0P_MFS3_UART_BGR_BGR06              *((volatile unsigned int*)(0x42706198UL))
#define bFM0P_MFS3_UART_BGR_BGR07              *((volatile unsigned int*)(0x4270619CUL))
#define bFM0P_MFS3_UART_BGR_BGR10              *((volatile unsigned int*)(0x427061A0UL))
#define bFM0P_MFS3_UART_BGR_BGR11              *((volatile unsigned int*)(0x427061A4UL))
#define bFM0P_MFS3_UART_BGR_BGR12              *((volatile unsigned int*)(0x427061A8UL))
#define bFM0P_MFS3_UART_BGR_BGR13              *((volatile unsigned int*)(0x427061ACUL))
#define bFM0P_MFS3_UART_BGR_BGR14              *((volatile unsigned int*)(0x427061B0UL))
#define bFM0P_MFS3_UART_BGR_BGR15              *((volatile unsigned int*)(0x427061B4UL))
#define bFM0P_MFS3_UART_BGR_BGR16              *((volatile unsigned int*)(0x427061B8UL))
#define bFM0P_MFS3_UART_BGR_EXT                *((volatile unsigned int*)(0x427061BCUL))
#define bFM0P_MFS3_UART_FCR0_FE1               *((volatile unsigned int*)(0x42706280UL))
#define bFM0P_MFS3_UART_FCR0_FE2               *((volatile unsigned int*)(0x42706284UL))
#define bFM0P_MFS3_UART_FCR0_FCL1              *((volatile unsigned int*)(0x42706288UL))
#define bFM0P_MFS3_UART_FCR0_FCL2              *((volatile unsigned int*)(0x4270628CUL))
#define bFM0P_MFS3_UART_FCR0_FSET              *((volatile unsigned int*)(0x42706290UL))
#define bFM0P_MFS3_UART_FCR0_FLD               *((volatile unsigned int*)(0x42706294UL))
#define bFM0P_MFS3_UART_FCR0_FLST              *((volatile unsigned int*)(0x42706298UL))
#define bFM0P_MFS3_UART_FCR1_FSEL              *((volatile unsigned int*)(0x427062A0UL))
#define bFM0P_MFS3_UART_FCR1_FTIE              *((volatile unsigned int*)(0x427062A4UL))
#define bFM0P_MFS3_UART_FCR1_FDRQ              *((volatile unsigned int*)(0x427062A8UL))
#define bFM0P_MFS3_UART_FCR1_FRIIE             *((volatile unsigned int*)(0x427062ACUL))
#define bFM0P_MFS3_UART_FCR1_FLSTE             *((volatile unsigned int*)(0x427062B0UL))

/* MFS3 CSIO channel 3 register */
#define bFM0P_MFS3_CSIO_SMR_SOE                *((volatile unsigned int*)(0x42706000UL))
#define bFM0P_MFS3_CSIO_SMR_SCKE               *((volatile unsigned int*)(0x42706004UL))
#define bFM0P_MFS3_CSIO_SMR_BDS                *((volatile unsigned int*)(0x42706008UL))
#define bFM0P_MFS3_CSIO_SMR_SCINV              *((volatile unsigned int*)(0x4270600CUL))
#define bFM0P_MFS3_CSIO_SMR_MD0                *((volatile unsigned int*)(0x42706014UL))
#define bFM0P_MFS3_CSIO_SMR_MD1                *((volatile unsigned int*)(0x42706018UL))
#define bFM0P_MFS3_CSIO_SMR_MD2                *((volatile unsigned int*)(0x4270601CUL))
#define bFM0P_MFS3_CSIO_SCR_TXE                *((volatile unsigned int*)(0x42706020UL))
#define bFM0P_MFS3_CSIO_SCR_RXE                *((volatile unsigned int*)(0x42706024UL))
#define bFM0P_MFS3_CSIO_SCR_TBIE               *((volatile unsigned int*)(0x42706028UL))
#define bFM0P_MFS3_CSIO_SCR_TIE                *((volatile unsigned int*)(0x4270602CUL))
#define bFM0P_MFS3_CSIO_SCR_RIE                *((volatile unsigned int*)(0x42706030UL))
#define bFM0P_MFS3_CSIO_SCR_SPI                *((volatile unsigned int*)(0x42706034UL))
#define bFM0P_MFS3_CSIO_SCR_MS                 *((volatile unsigned int*)(0x42706038UL))
#define bFM0P_MFS3_CSIO_SCR_UPCL               *((volatile unsigned int*)(0x4270603CUL))
#define bFM0P_MFS3_CSIO_ESCR_L0                *((volatile unsigned int*)(0x42706080UL))
#define bFM0P_MFS3_CSIO_ESCR_L1                *((volatile unsigned int*)(0x42706084UL))
#define bFM0P_MFS3_CSIO_ESCR_L2                *((volatile unsigned int*)(0x42706088UL))
#define bFM0P_MFS3_CSIO_ESCR_WT0               *((volatile unsigned int*)(0x4270608CUL))
#define bFM0P_MFS3_CSIO_ESCR_WT1               *((volatile unsigned int*)(0x42706090UL))
#define bFM0P_MFS3_CSIO_ESCR_CSFE              *((volatile unsigned int*)(0x42706094UL))
#define bFM0P_MFS3_CSIO_ESCR_L3                *((volatile unsigned int*)(0x42706098UL))
#define bFM0P_MFS3_CSIO_ESCR_SOP               *((volatile unsigned int*)(0x4270609CUL))
#define bFM0P_MFS3_CSIO_SSR_TBI                *((volatile unsigned int*)(0x427060A0UL))
#define bFM0P_MFS3_CSIO_SSR_TDRE               *((volatile unsigned int*)(0x427060A4UL))
#define bFM0P_MFS3_CSIO_SSR_RDRF               *((volatile unsigned int*)(0x427060A8UL))
#define bFM0P_MFS3_CSIO_SSR_ORE                *((volatile unsigned int*)(0x427060ACUL))
#define bFM0P_MFS3_CSIO_SSR_REC                *((volatile unsigned int*)(0x427060BCUL))
#define bFM0P_MFS3_CSIO_BGR_BGR00              *((volatile unsigned int*)(0x42706180UL))
#define bFM0P_MFS3_CSIO_BGR_BGR01              *((volatile unsigned int*)(0x42706184UL))
#define bFM0P_MFS3_CSIO_BGR_BGR02              *((volatile unsigned int*)(0x42706188UL))
#define bFM0P_MFS3_CSIO_BGR_BGR03              *((volatile unsigned int*)(0x4270618CUL))
#define bFM0P_MFS3_CSIO_BGR_BGR04              *((volatile unsigned int*)(0x42706190UL))
#define bFM0P_MFS3_CSIO_BGR_BGR05              *((volatile unsigned int*)(0x42706194UL))
#define bFM0P_MFS3_CSIO_BGR_BGR06              *((volatile unsigned int*)(0x42706198UL))
#define bFM0P_MFS3_CSIO_BGR_BGR07              *((volatile unsigned int*)(0x4270619CUL))
#define bFM0P_MFS3_CSIO_BGR_BGR10              *((volatile unsigned int*)(0x427061A0UL))
#define bFM0P_MFS3_CSIO_BGR_BGR11              *((volatile unsigned int*)(0x427061A4UL))
#define bFM0P_MFS3_CSIO_BGR_BGR12              *((volatile unsigned int*)(0x427061A8UL))
#define bFM0P_MFS3_CSIO_BGR_BGR13              *((volatile unsigned int*)(0x427061ACUL))
#define bFM0P_MFS3_CSIO_BGR_BGR14              *((volatile unsigned int*)(0x427061B0UL))
#define bFM0P_MFS3_CSIO_BGR_BGR15              *((volatile unsigned int*)(0x427061B4UL))
#define bFM0P_MFS3_CSIO_BGR_BGR16              *((volatile unsigned int*)(0x427061B8UL))
#define bFM0P_MFS3_CSIO_FCR0_FE1               *((volatile unsigned int*)(0x42706280UL))
#define bFM0P_MFS3_CSIO_FCR0_FE2               *((volatile unsigned int*)(0x42706284UL))
#define bFM0P_MFS3_CSIO_FCR0_FCL1              *((volatile unsigned int*)(0x42706288UL))
#define bFM0P_MFS3_CSIO_FCR0_FCL2              *((volatile unsigned int*)(0x4270628CUL))
#define bFM0P_MFS3_CSIO_FCR0_FSET              *((volatile unsigned int*)(0x42706290UL))
#define bFM0P_MFS3_CSIO_FCR0_FLD               *((volatile unsigned int*)(0x42706294UL))
#define bFM0P_MFS3_CSIO_FCR0_FLST              *((volatile unsigned int*)(0x42706298UL))
#define bFM0P_MFS3_CSIO_FCR1_FSEL              *((volatile unsigned int*)(0x427062A0UL))
#define bFM0P_MFS3_CSIO_FCR1_FTIE              *((volatile unsigned int*)(0x427062A4UL))
#define bFM0P_MFS3_CSIO_FCR1_FDRQ              *((volatile unsigned int*)(0x427062A8UL))
#define bFM0P_MFS3_CSIO_FCR1_FRIIE             *((volatile unsigned int*)(0x427062ACUL))
#define bFM0P_MFS3_CSIO_FCR1_FLSTE             *((volatile unsigned int*)(0x427062B0UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD0           *((volatile unsigned int*)(0x42706380UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD1           *((volatile unsigned int*)(0x42706384UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD2           *((volatile unsigned int*)(0x42706388UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD3           *((volatile unsigned int*)(0x4270638CUL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD4           *((volatile unsigned int*)(0x42706390UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD5           *((volatile unsigned int*)(0x42706394UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD6           *((volatile unsigned int*)(0x42706398UL))
#define bFM0P_MFS3_CSIO_SCSTR0_CSHD7           *((volatile unsigned int*)(0x4270639CUL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU0           *((volatile unsigned int*)(0x427063A0UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU1           *((volatile unsigned int*)(0x427063A4UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU2           *((volatile unsigned int*)(0x427063A8UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU3           *((volatile unsigned int*)(0x427063ACUL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU4           *((volatile unsigned int*)(0x427063B0UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU5           *((volatile unsigned int*)(0x427063B4UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU6           *((volatile unsigned int*)(0x427063B8UL))
#define bFM0P_MFS3_CSIO_SCSTR1_CSSU7           *((volatile unsigned int*)(0x427063BCUL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS0          *((volatile unsigned int*)(0x42706400UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS1          *((volatile unsigned int*)(0x42706404UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS2          *((volatile unsigned int*)(0x42706408UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS3          *((volatile unsigned int*)(0x4270640CUL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS4          *((volatile unsigned int*)(0x42706410UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS5          *((volatile unsigned int*)(0x42706414UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS6          *((volatile unsigned int*)(0x42706418UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS7          *((volatile unsigned int*)(0x4270641CUL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS8          *((volatile unsigned int*)(0x42706420UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS9          *((volatile unsigned int*)(0x42706424UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS10         *((volatile unsigned int*)(0x42706428UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS11         *((volatile unsigned int*)(0x4270642CUL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS12         *((volatile unsigned int*)(0x42706430UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS13         *((volatile unsigned int*)(0x42706434UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS14         *((volatile unsigned int*)(0x42706438UL))
#define bFM0P_MFS3_CSIO_SCSTR32_CSDS15         *((volatile unsigned int*)(0x4270643CUL))
#define bFM0P_MFS3_CSIO_SACSR_TMRE             *((volatile unsigned int*)(0x42706480UL))
#define bFM0P_MFS3_CSIO_SACSR_TDIV0            *((volatile unsigned int*)(0x42706484UL))
#define bFM0P_MFS3_CSIO_SACSR_TDIV1            *((volatile unsigned int*)(0x42706488UL))
#define bFM0P_MFS3_CSIO_SACSR_TDIV2            *((volatile unsigned int*)(0x4270648CUL))
#define bFM0P_MFS3_CSIO_SACSR_TDIV3            *((volatile unsigned int*)(0x42706490UL))
#define bFM0P_MFS3_CSIO_SACSR_TSYNE            *((volatile unsigned int*)(0x42706498UL))
#define bFM0P_MFS3_CSIO_SACSR_TINTE            *((volatile unsigned int*)(0x4270649CUL))
#define bFM0P_MFS3_CSIO_SACSR_TINT             *((volatile unsigned int*)(0x427064A0UL))
#define bFM0P_MFS3_CSIO_SACSR_CSE              *((volatile unsigned int*)(0x427064ACUL))
#define bFM0P_MFS3_CSIO_SACSR_CSEIE            *((volatile unsigned int*)(0x427064B0UL))
#define bFM0P_MFS3_CSIO_SACSR_TBEEN            *((volatile unsigned int*)(0x427064B4UL))
#define bFM0P_MFS3_CSIO_STMR_TM0               *((volatile unsigned int*)(0x42706500UL))
#define bFM0P_MFS3_CSIO_STMR_TM1               *((volatile unsigned int*)(0x42706504UL))
#define bFM0P_MFS3_CSIO_STMR_TM2               *((volatile unsigned int*)(0x42706508UL))
#define bFM0P_MFS3_CSIO_STMR_TM3               *((volatile unsigned int*)(0x4270650CUL))
#define bFM0P_MFS3_CSIO_STMR_TM4               *((volatile unsigned int*)(0x42706510UL))
#define bFM0P_MFS3_CSIO_STMR_TM5               *((volatile unsigned int*)(0x42706514UL))
#define bFM0P_MFS3_CSIO_STMR_TM6               *((volatile unsigned int*)(0x42706518UL))
#define bFM0P_MFS3_CSIO_STMR_TM7               *((volatile unsigned int*)(0x4270651CUL))
#define bFM0P_MFS3_CSIO_STMR_TM8               *((volatile unsigned int*)(0x42706520UL))
#define bFM0P_MFS3_CSIO_STMR_TM9               *((volatile unsigned int*)(0x42706524UL))
#define bFM0P_MFS3_CSIO_STMR_TM10              *((volatile unsigned int*)(0x42706528UL))
#define bFM0P_MFS3_CSIO_STMR_TM11              *((volatile unsigned int*)(0x4270652CUL))
#define bFM0P_MFS3_CSIO_STMR_TM12              *((volatile unsigned int*)(0x42706530UL))
#define bFM0P_MFS3_CSIO_STMR_TM13              *((volatile unsigned int*)(0x42706534UL))
#define bFM0P_MFS3_CSIO_STMR_TM14              *((volatile unsigned int*)(0x42706538UL))
#define bFM0P_MFS3_CSIO_STMR_TM15              *((volatile unsigned int*)(0x4270653CUL))
#define bFM0P_MFS3_CSIO_TMCR_TC0               *((volatile unsigned int*)(0x42706580UL))
#define bFM0P_MFS3_CSIO_TMCR_TC1               *((volatile unsigned int*)(0x42706584UL))
#define bFM0P_MFS3_CSIO_TMCR_TC2               *((volatile unsigned int*)(0x42706588UL))
#define bFM0P_MFS3_CSIO_TMCR_TC3               *((volatile unsigned int*)(0x4270658CUL))
#define bFM0P_MFS3_CSIO_TMCR_TC4               *((volatile unsigned int*)(0x42706590UL))
#define bFM0P_MFS3_CSIO_TMCR_TC5               *((volatile unsigned int*)(0x42706594UL))
#define bFM0P_MFS3_CSIO_TMCR_TC6               *((volatile unsigned int*)(0x42706598UL))
#define bFM0P_MFS3_CSIO_TMCR_TC7               *((volatile unsigned int*)(0x4270659CUL))
#define bFM0P_MFS3_CSIO_TMCR_TC8               *((volatile unsigned int*)(0x427065A0UL))
#define bFM0P_MFS3_CSIO_TMCR_TC9               *((volatile unsigned int*)(0x427065A4UL))
#define bFM0P_MFS3_CSIO_TMCR_TC10              *((volatile unsigned int*)(0x427065A8UL))
#define bFM0P_MFS3_CSIO_TMCR_TC11              *((volatile unsigned int*)(0x427065ACUL))
#define bFM0P_MFS3_CSIO_TMCR_TC12              *((volatile unsigned int*)(0x427065B0UL))
#define bFM0P_MFS3_CSIO_TMCR_TC13              *((volatile unsigned int*)(0x427065B4UL))
#define bFM0P_MFS3_CSIO_TMCR_TC14              *((volatile unsigned int*)(0x427065B8UL))
#define bFM0P_MFS3_CSIO_TMCR_TC15              *((volatile unsigned int*)(0x427065BCUL))
#define bFM0P_MFS3_CSIO_SCSCR_CSOE             *((volatile unsigned int*)(0x42706600UL))
#define bFM0P_MFS3_CSIO_SCSCR_CSEN0            *((volatile unsigned int*)(0x42706604UL))
#define bFM0P_MFS3_CSIO_SCSCR_CSEN1            *((volatile unsigned int*)(0x42706608UL))
#define bFM0P_MFS3_CSIO_SCSCR_CSEN2            *((volatile unsigned int*)(0x4270660CUL))
#define bFM0P_MFS3_CSIO_SCSCR_CSEN3            *((volatile unsigned int*)(0x42706610UL))
#define bFM0P_MFS3_CSIO_SCSCR_CSLVL            *((volatile unsigned int*)(0x42706614UL))
#define bFM0P_MFS3_CSIO_SCSCR_CDIV0            *((volatile unsigned int*)(0x42706618UL))
#define bFM0P_MFS3_CSIO_SCSCR_CDIV1            *((volatile unsigned int*)(0x4270661CUL))
#define bFM0P_MFS3_CSIO_SCSCR_CDIV2            *((volatile unsigned int*)(0x42706620UL))
#define bFM0P_MFS3_CSIO_SCSCR_SCAM             *((volatile unsigned int*)(0x42706624UL))
#define bFM0P_MFS3_CSIO_SCSCR_SCD0             *((volatile unsigned int*)(0x42706628UL))
#define bFM0P_MFS3_CSIO_SCSCR_SCD1             *((volatile unsigned int*)(0x4270662CUL))
#define bFM0P_MFS3_CSIO_SCSCR_SED0             *((volatile unsigned int*)(0x42706630UL))
#define bFM0P_MFS3_CSIO_SCSCR_SED1             *((volatile unsigned int*)(0x42706634UL))
#define bFM0P_MFS3_CSIO_SCSCR_SST0             *((volatile unsigned int*)(0x42706638UL))
#define bFM0P_MFS3_CSIO_SCSCR_SST1             *((volatile unsigned int*)(0x4270663CUL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1L0           *((volatile unsigned int*)(0x42706680UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1L1           *((volatile unsigned int*)(0x42706684UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1L2           *((volatile unsigned int*)(0x42706688UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1L3           *((volatile unsigned int*)(0x4270668CUL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1BDS          *((volatile unsigned int*)(0x42706690UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1SPI          *((volatile unsigned int*)(0x42706694UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1SCINV        *((volatile unsigned int*)(0x42706698UL))
#define bFM0P_MFS3_CSIO_SCSFR0_CS1CSLVL        *((volatile unsigned int*)(0x4270669CUL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2L0           *((volatile unsigned int*)(0x427066A0UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2L1           *((volatile unsigned int*)(0x427066A4UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2L2           *((volatile unsigned int*)(0x427066A8UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2L3           *((volatile unsigned int*)(0x427066ACUL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2BDS          *((volatile unsigned int*)(0x427066B0UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2SPI          *((volatile unsigned int*)(0x427066B4UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2SCINV        *((volatile unsigned int*)(0x427066B8UL))
#define bFM0P_MFS3_CSIO_SCSFR1_CS2CSLVL        *((volatile unsigned int*)(0x427066BCUL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3L0           *((volatile unsigned int*)(0x42706700UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3L1           *((volatile unsigned int*)(0x42706704UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3L2           *((volatile unsigned int*)(0x42706708UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3L3           *((volatile unsigned int*)(0x4270670CUL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3BDS          *((volatile unsigned int*)(0x42706710UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3SPI          *((volatile unsigned int*)(0x42706714UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3SCINV        *((volatile unsigned int*)(0x42706718UL))
#define bFM0P_MFS3_CSIO_SCSFR3_CS3CSLVL        *((volatile unsigned int*)(0x4270671CUL))

/* MFS3 LIN channel 3 register */
#define bFM0P_MFS3_LIN_SMR_SOE                 *((volatile unsigned int*)(0x42706000UL))
#define bFM0P_MFS3_LIN_SMR_SBL                 *((volatile unsigned int*)(0x4270600CUL))
#define bFM0P_MFS3_LIN_SMR_MD0                 *((volatile unsigned int*)(0x42706014UL))
#define bFM0P_MFS3_LIN_SMR_MD1                 *((volatile unsigned int*)(0x42706018UL))
#define bFM0P_MFS3_LIN_SMR_MD2                 *((volatile unsigned int*)(0x4270601CUL))
#define bFM0P_MFS3_LIN_SCR_TXE                 *((volatile unsigned int*)(0x42706020UL))
#define bFM0P_MFS3_LIN_SCR_RXE                 *((volatile unsigned int*)(0x42706024UL))
#define bFM0P_MFS3_LIN_SCR_TBIE                *((volatile unsigned int*)(0x42706028UL))
#define bFM0P_MFS3_LIN_SCR_TIE                 *((volatile unsigned int*)(0x4270602CUL))
#define bFM0P_MFS3_LIN_SCR_RIE                 *((volatile unsigned int*)(0x42706030UL))
#define bFM0P_MFS3_LIN_SCR_LBR                 *((volatile unsigned int*)(0x42706034UL))
#define bFM0P_MFS3_LIN_SCR_MS                  *((volatile unsigned int*)(0x42706038UL))
#define bFM0P_MFS3_LIN_SCR_UPCL                *((volatile unsigned int*)(0x4270603CUL))
#define bFM0P_MFS3_LIN_ESCR_DEL0               *((volatile unsigned int*)(0x42706080UL))
#define bFM0P_MFS3_LIN_ESCR_DEL1               *((volatile unsigned int*)(0x42706084UL))
#define bFM0P_MFS3_LIN_ESCR_LBL0               *((volatile unsigned int*)(0x42706088UL))
#define bFM0P_MFS3_LIN_ESCR_LBL1               *((volatile unsigned int*)(0x4270608CUL))
#define bFM0P_MFS3_LIN_ESCR_LBIE               *((volatile unsigned int*)(0x42706090UL))
#define bFM0P_MFS3_LIN_ESCR_ESBL               *((volatile unsigned int*)(0x42706098UL))
#define bFM0P_MFS3_LIN_SSR_TBI                 *((volatile unsigned int*)(0x427060A0UL))
#define bFM0P_MFS3_LIN_SSR_TDRE                *((volatile unsigned int*)(0x427060A4UL))
#define bFM0P_MFS3_LIN_SSR_RDRF                *((volatile unsigned int*)(0x427060A8UL))
#define bFM0P_MFS3_LIN_SSR_ORE                 *((volatile unsigned int*)(0x427060ACUL))
#define bFM0P_MFS3_LIN_SSR_FRE                 *((volatile unsigned int*)(0x427060B0UL))
#define bFM0P_MFS3_LIN_SSR_LBD                 *((volatile unsigned int*)(0x427060B4UL))
#define bFM0P_MFS3_LIN_SSR_REC                 *((volatile unsigned int*)(0x427060BCUL))
#define bFM0P_MFS3_LIN_BGR_BGR00               *((volatile unsigned int*)(0x42706180UL))
#define bFM0P_MFS3_LIN_BGR_BGR01               *((volatile unsigned int*)(0x42706184UL))
#define bFM0P_MFS3_LIN_BGR_BGR02               *((volatile unsigned int*)(0x42706188UL))
#define bFM0P_MFS3_LIN_BGR_BGR03               *((volatile unsigned int*)(0x4270618CUL))
#define bFM0P_MFS3_LIN_BGR_BGR04               *((volatile unsigned int*)(0x42706190UL))
#define bFM0P_MFS3_LIN_BGR_BGR05               *((volatile unsigned int*)(0x42706194UL))
#define bFM0P_MFS3_LIN_BGR_BGR06               *((volatile unsigned int*)(0x42706198UL))
#define bFM0P_MFS3_LIN_BGR_BGR07               *((volatile unsigned int*)(0x4270619CUL))
#define bFM0P_MFS3_LIN_BGR_BGR10               *((volatile unsigned int*)(0x427061A0UL))
#define bFM0P_MFS3_LIN_BGR_BGR11               *((volatile unsigned int*)(0x427061A4UL))
#define bFM0P_MFS3_LIN_BGR_BGR12               *((volatile unsigned int*)(0x427061A8UL))
#define bFM0P_MFS3_LIN_BGR_BGR13               *((volatile unsigned int*)(0x427061ACUL))
#define bFM0P_MFS3_LIN_BGR_BGR14               *((volatile unsigned int*)(0x427061B0UL))
#define bFM0P_MFS3_LIN_BGR_BGR15               *((volatile unsigned int*)(0x427061B4UL))
#define bFM0P_MFS3_LIN_BGR_BGR16               *((volatile unsigned int*)(0x427061B8UL))
#define bFM0P_MFS3_LIN_BGR_EXT                 *((volatile unsigned int*)(0x427061BCUL))
#define bFM0P_MFS3_LIN_FCR0_FE1                *((volatile unsigned int*)(0x42706280UL))
#define bFM0P_MFS3_LIN_FCR0_FE2                *((volatile unsigned int*)(0x42706284UL))
#define bFM0P_MFS3_LIN_FCR0_FCL1               *((volatile unsigned int*)(0x42706288UL))
#define bFM0P_MFS3_LIN_FCR0_FCL2               *((volatile unsigned int*)(0x4270628CUL))
#define bFM0P_MFS3_LIN_FCR0_FSET               *((volatile unsigned int*)(0x42706290UL))
#define bFM0P_MFS3_LIN_FCR0_FLD                *((volatile unsigned int*)(0x42706294UL))
#define bFM0P_MFS3_LIN_FCR0_FLST               *((volatile unsigned int*)(0x42706298UL))
#define bFM0P_MFS3_LIN_FCR1_FSEL               *((volatile unsigned int*)(0x427062A0UL))
#define bFM0P_MFS3_LIN_FCR1_FTIE               *((volatile unsigned int*)(0x427062A4UL))
#define bFM0P_MFS3_LIN_FCR1_FDRQ               *((volatile unsigned int*)(0x427062A8UL))
#define bFM0P_MFS3_LIN_FCR1_FRIIE              *((volatile unsigned int*)(0x427062ACUL))
#define bFM0P_MFS3_LIN_FCR1_FLSTE              *((volatile unsigned int*)(0x427062B0UL))

/* MFS3 I2C channel 3 register */
#define bFM0P_MFS3_I2C_SMR_TIE                 *((volatile unsigned int*)(0x42706008UL))
#define bFM0P_MFS3_I2C_SMR_RIE                 *((volatile unsigned int*)(0x4270600CUL))
#define bFM0P_MFS3_I2C_SMR_MD0                 *((volatile unsigned int*)(0x42706014UL))
#define bFM0P_MFS3_I2C_SMR_MD1                 *((volatile unsigned int*)(0x42706018UL))
#define bFM0P_MFS3_I2C_SMR_MD2                 *((volatile unsigned int*)(0x4270601CUL))
#define bFM0P_MFS3_I2C_IBCR_INT                *((volatile unsigned int*)(0x42706020UL))
#define bFM0P_MFS3_I2C_IBCR_BER                *((volatile unsigned int*)(0x42706024UL))
#define bFM0P_MFS3_I2C_IBCR_INTE               *((volatile unsigned int*)(0x42706028UL))
#define bFM0P_MFS3_I2C_IBCR_CNDE               *((volatile unsigned int*)(0x4270602CUL))
#define bFM0P_MFS3_I2C_IBCR_WSEL               *((volatile unsigned int*)(0x42706030UL))
#define bFM0P_MFS3_I2C_IBCR_ACKE               *((volatile unsigned int*)(0x42706034UL))
#define bFM0P_MFS3_I2C_IBCR_ACT_SCC            *((volatile unsigned int*)(0x42706038UL))
#define bFM0P_MFS3_I2C_IBCR_MSS                *((volatile unsigned int*)(0x4270603CUL))
#define bFM0P_MFS3_I2C_IBSR_BB                 *((volatile unsigned int*)(0x42706080UL))
#define bFM0P_MFS3_I2C_IBSR_SPC                *((volatile unsigned int*)(0x42706084UL))
#define bFM0P_MFS3_I2C_IBSR_RSC                *((volatile unsigned int*)(0x42706088UL))
#define bFM0P_MFS3_I2C_IBSR_AL                 *((volatile unsigned int*)(0x4270608CUL))
#define bFM0P_MFS3_I2C_IBSR_TRX                *((volatile unsigned int*)(0x42706090UL))
#define bFM0P_MFS3_I2C_IBSR_RSA                *((volatile unsigned int*)(0x42706094UL))
#define bFM0P_MFS3_I2C_IBSR_RACK               *((volatile unsigned int*)(0x42706098UL))
#define bFM0P_MFS3_I2C_IBSR_FBT                *((volatile unsigned int*)(0x4270609CUL))
#define bFM0P_MFS3_I2C_SSR_TBI                 *((volatile unsigned int*)(0x427060A0UL))
#define bFM0P_MFS3_I2C_SSR_TDRE                *((volatile unsigned int*)(0x427060A4UL))
#define bFM0P_MFS3_I2C_SSR_RDRF                *((volatile unsigned int*)(0x427060A8UL))
#define bFM0P_MFS3_I2C_SSR_ORE                 *((volatile unsigned int*)(0x427060ACUL))
#define bFM0P_MFS3_I2C_SSR_TBIE                *((volatile unsigned int*)(0x427060B0UL))
#define bFM0P_MFS3_I2C_SSR_DMA                 *((volatile unsigned int*)(0x427060B4UL))
#define bFM0P_MFS3_I2C_SSR_TSET                *((volatile unsigned int*)(0x427060B8UL))
#define bFM0P_MFS3_I2C_SSR_REC                 *((volatile unsigned int*)(0x427060BCUL))
#define bFM0P_MFS3_I2C_BGR_BGR00               *((volatile unsigned int*)(0x42706180UL))
#define bFM0P_MFS3_I2C_BGR_BGR01               *((volatile unsigned int*)(0x42706184UL))
#define bFM0P_MFS3_I2C_BGR_BGR02               *((volatile unsigned int*)(0x42706188UL))
#define bFM0P_MFS3_I2C_BGR_BGR03               *((volatile unsigned int*)(0x4270618CUL))
#define bFM0P_MFS3_I2C_BGR_BGR04               *((volatile unsigned int*)(0x42706190UL))
#define bFM0P_MFS3_I2C_BGR_BGR05               *((volatile unsigned int*)(0x42706194UL))
#define bFM0P_MFS3_I2C_BGR_BGR06               *((volatile unsigned int*)(0x42706198UL))
#define bFM0P_MFS3_I2C_BGR_BGR07               *((volatile unsigned int*)(0x4270619CUL))
#define bFM0P_MFS3_I2C_BGR_BGR10               *((volatile unsigned int*)(0x427061A0UL))
#define bFM0P_MFS3_I2C_BGR_BGR11               *((volatile unsigned int*)(0x427061A4UL))
#define bFM0P_MFS3_I2C_BGR_BGR12               *((volatile unsigned int*)(0x427061A8UL))
#define bFM0P_MFS3_I2C_BGR_BGR13               *((volatile unsigned int*)(0x427061ACUL))
#define bFM0P_MFS3_I2C_BGR_BGR14               *((volatile unsigned int*)(0x427061B0UL))
#define bFM0P_MFS3_I2C_BGR_BGR15               *((volatile unsigned int*)(0x427061B4UL))
#define bFM0P_MFS3_I2C_BGR_BGR16               *((volatile unsigned int*)(0x427061B8UL))
#define bFM0P_MFS3_I2C_ISBA_SA0                *((volatile unsigned int*)(0x42706200UL))
#define bFM0P_MFS3_I2C_ISBA_SA1                *((volatile unsigned int*)(0x42706204UL))
#define bFM0P_MFS3_I2C_ISBA_SA2                *((volatile unsigned int*)(0x42706208UL))
#define bFM0P_MFS3_I2C_ISBA_SA3                *((volatile unsigned int*)(0x4270620CUL))
#define bFM0P_MFS3_I2C_ISBA_SA4                *((volatile unsigned int*)(0x42706210UL))
#define bFM0P_MFS3_I2C_ISBA_SA5                *((volatile unsigned int*)(0x42706214UL))
#define bFM0P_MFS3_I2C_ISBA_SA6                *((volatile unsigned int*)(0x42706218UL))
#define bFM0P_MFS3_I2C_ISBA_SAEN               *((volatile unsigned int*)(0x4270621CUL))
#define bFM0P_MFS3_I2C_ISMK_SM0                *((volatile unsigned int*)(0x42706220UL))
#define bFM0P_MFS3_I2C_ISMK_SM1                *((volatile unsigned int*)(0x42706224UL))
#define bFM0P_MFS3_I2C_ISMK_SM2                *((volatile unsigned int*)(0x42706228UL))
#define bFM0P_MFS3_I2C_ISMK_SM3                *((volatile unsigned int*)(0x4270622CUL))
#define bFM0P_MFS3_I2C_ISMK_SM4                *((volatile unsigned int*)(0x42706230UL))
#define bFM0P_MFS3_I2C_ISMK_SM5                *((volatile unsigned int*)(0x42706234UL))
#define bFM0P_MFS3_I2C_ISMK_SM6                *((volatile unsigned int*)(0x42706238UL))
#define bFM0P_MFS3_I2C_ISMK_EN                 *((volatile unsigned int*)(0x4270623CUL))
#define bFM0P_MFS3_I2C_FCR0_FE1                *((volatile unsigned int*)(0x42706280UL))
#define bFM0P_MFS3_I2C_FCR0_FE2                *((volatile unsigned int*)(0x42706284UL))
#define bFM0P_MFS3_I2C_FCR0_FCL1               *((volatile unsigned int*)(0x42706288UL))
#define bFM0P_MFS3_I2C_FCR0_FCL2               *((volatile unsigned int*)(0x4270628CUL))
#define bFM0P_MFS3_I2C_FCR0_FSET               *((volatile unsigned int*)(0x42706290UL))
#define bFM0P_MFS3_I2C_FCR0_FLD                *((volatile unsigned int*)(0x42706294UL))
#define bFM0P_MFS3_I2C_FCR0_FLST               *((volatile unsigned int*)(0x42706298UL))
#define bFM0P_MFS3_I2C_FCR1_FSEL               *((volatile unsigned int*)(0x427062A0UL))
#define bFM0P_MFS3_I2C_FCR1_FTIE               *((volatile unsigned int*)(0x427062A4UL))
#define bFM0P_MFS3_I2C_FCR1_FDRQ               *((volatile unsigned int*)(0x427062A8UL))
#define bFM0P_MFS3_I2C_FCR1_FRIIE              *((volatile unsigned int*)(0x427062ACUL))
#define bFM0P_MFS3_I2C_FCR1_FLSTE              *((volatile unsigned int*)(0x427062B0UL))
#define bFM0P_MFS3_I2C_EIBCR_BEC               *((volatile unsigned int*)(0x427063A0UL))
#define bFM0P_MFS3_I2C_EIBCR_SOCE              *((volatile unsigned int*)(0x427063A4UL))
#define bFM0P_MFS3_I2C_EIBCR_SCLC              *((volatile unsigned int*)(0x427063A8UL))
#define bFM0P_MFS3_I2C_EIBCR_SDAC              *((volatile unsigned int*)(0x427063ACUL))
#define bFM0P_MFS3_I2C_EIBCR_SCLS              *((volatile unsigned int*)(0x427063B0UL))
#define bFM0P_MFS3_I2C_EIBCR_SDAS              *((volatile unsigned int*)(0x427063B4UL))

/* CRC registers */
#define bFM0P_CRC_CRCCR_INIT                   *((volatile unsigned int*)(0x42720000UL))
#define bFM0P_CRC_CRCCR_CRC32                  *((volatile unsigned int*)(0x42720004UL))
#define bFM0P_CRC_CRCCR_LTLEND                 *((volatile unsigned int*)(0x42720008UL))
#define bFM0P_CRC_CRCCR_LSBFST                 *((volatile unsigned int*)(0x4272000CUL))
#define bFM0P_CRC_CRCCR_CRCLTE                 *((volatile unsigned int*)(0x42720010UL))
#define bFM0P_CRC_CRCCR_CRCLSF                 *((volatile unsigned int*)(0x42720014UL))
#define bFM0P_CRC_CRCCR_FXOR                   *((volatile unsigned int*)(0x42720018UL))
#define bFM0P_CRC_CRCINIT_D0                   *((volatile unsigned int*)(0x42720080UL))
#define bFM0P_CRC_CRCINIT_D1                   *((volatile unsigned int*)(0x42720084UL))
#define bFM0P_CRC_CRCINIT_D2                   *((volatile unsigned int*)(0x42720088UL))
#define bFM0P_CRC_CRCINIT_D3                   *((volatile unsigned int*)(0x4272008CUL))
#define bFM0P_CRC_CRCINIT_D4                   *((volatile unsigned int*)(0x42720090UL))
#define bFM0P_CRC_CRCINIT_D5                   *((volatile unsigned int*)(0x42720094UL))
#define bFM0P_CRC_CRCINIT_D6                   *((volatile unsigned int*)(0x42720098UL))
#define bFM0P_CRC_CRCINIT_D7                   *((volatile unsigned int*)(0x4272009CUL))
#define bFM0P_CRC_CRCINIT_D8                   *((volatile unsigned int*)(0x427200A0UL))
#define bFM0P_CRC_CRCINIT_D9                   *((volatile unsigned int*)(0x427200A4UL))
#define bFM0P_CRC_CRCINIT_D10                  *((volatile unsigned int*)(0x427200A8UL))
#define bFM0P_CRC_CRCINIT_D11                  *((volatile unsigned int*)(0x427200ACUL))
#define bFM0P_CRC_CRCINIT_D12                  *((volatile unsigned int*)(0x427200B0UL))
#define bFM0P_CRC_CRCINIT_D13                  *((volatile unsigned int*)(0x427200B4UL))
#define bFM0P_CRC_CRCINIT_D14                  *((volatile unsigned int*)(0x427200B8UL))
#define bFM0P_CRC_CRCINIT_D15                  *((volatile unsigned int*)(0x427200BCUL))
#define bFM0P_CRC_CRCINIT_D16                  *((volatile unsigned int*)(0x427200C0UL))
#define bFM0P_CRC_CRCINIT_D17                  *((volatile unsigned int*)(0x427200C4UL))
#define bFM0P_CRC_CRCINIT_D18                  *((volatile unsigned int*)(0x427200C8UL))
#define bFM0P_CRC_CRCINIT_D19                  *((volatile unsigned int*)(0x427200CCUL))
#define bFM0P_CRC_CRCINIT_D20                  *((volatile unsigned int*)(0x427200D0UL))
#define bFM0P_CRC_CRCINIT_D21                  *((volatile unsigned int*)(0x427200D4UL))
#define bFM0P_CRC_CRCINIT_D22                  *((volatile unsigned int*)(0x427200D8UL))
#define bFM0P_CRC_CRCINIT_D23                  *((volatile unsigned int*)(0x427200DCUL))
#define bFM0P_CRC_CRCINIT_D24                  *((volatile unsigned int*)(0x427200E0UL))
#define bFM0P_CRC_CRCINIT_D25                  *((volatile unsigned int*)(0x427200E4UL))
#define bFM0P_CRC_CRCINIT_D26                  *((volatile unsigned int*)(0x427200E8UL))
#define bFM0P_CRC_CRCINIT_D27                  *((volatile unsigned int*)(0x427200ECUL))
#define bFM0P_CRC_CRCINIT_D28                  *((volatile unsigned int*)(0x427200F0UL))
#define bFM0P_CRC_CRCINIT_D29                  *((volatile unsigned int*)(0x427200F4UL))
#define bFM0P_CRC_CRCINIT_D30                  *((volatile unsigned int*)(0x427200F8UL))
#define bFM0P_CRC_CRCINIT_D31                  *((volatile unsigned int*)(0x427200FCUL))
#define bFM0P_CRC_CRCIN_D0                     *((volatile unsigned int*)(0x42720100UL))
#define bFM0P_CRC_CRCIN_D1                     *((volatile unsigned int*)(0x42720104UL))
#define bFM0P_CRC_CRCIN_D2                     *((volatile unsigned int*)(0x42720108UL))
#define bFM0P_CRC_CRCIN_D3                     *((volatile unsigned int*)(0x4272010CUL))
#define bFM0P_CRC_CRCIN_D4                     *((volatile unsigned int*)(0x42720110UL))
#define bFM0P_CRC_CRCIN_D5                     *((volatile unsigned int*)(0x42720114UL))
#define bFM0P_CRC_CRCIN_D6                     *((volatile unsigned int*)(0x42720118UL))
#define bFM0P_CRC_CRCIN_D7                     *((volatile unsigned int*)(0x4272011CUL))
#define bFM0P_CRC_CRCIN_D8                     *((volatile unsigned int*)(0x42720120UL))
#define bFM0P_CRC_CRCIN_D9                     *((volatile unsigned int*)(0x42720124UL))
#define bFM0P_CRC_CRCIN_D10                    *((volatile unsigned int*)(0x42720128UL))
#define bFM0P_CRC_CRCIN_D11                    *((volatile unsigned int*)(0x4272012CUL))
#define bFM0P_CRC_CRCIN_D12                    *((volatile unsigned int*)(0x42720130UL))
#define bFM0P_CRC_CRCIN_D13                    *((volatile unsigned int*)(0x42720134UL))
#define bFM0P_CRC_CRCIN_D14                    *((volatile unsigned int*)(0x42720138UL))
#define bFM0P_CRC_CRCIN_D15                    *((volatile unsigned int*)(0x4272013CUL))
#define bFM0P_CRC_CRCIN_D16                    *((volatile unsigned int*)(0x42720140UL))
#define bFM0P_CRC_CRCIN_D17                    *((volatile unsigned int*)(0x42720144UL))
#define bFM0P_CRC_CRCIN_D18                    *((volatile unsigned int*)(0x42720148UL))
#define bFM0P_CRC_CRCIN_D19                    *((volatile unsigned int*)(0x4272014CUL))
#define bFM0P_CRC_CRCIN_D20                    *((volatile unsigned int*)(0x42720150UL))
#define bFM0P_CRC_CRCIN_D21                    *((volatile unsigned int*)(0x42720154UL))
#define bFM0P_CRC_CRCIN_D22                    *((volatile unsigned int*)(0x42720158UL))
#define bFM0P_CRC_CRCIN_D23                    *((volatile unsigned int*)(0x4272015CUL))
#define bFM0P_CRC_CRCIN_D24                    *((volatile unsigned int*)(0x42720160UL))
#define bFM0P_CRC_CRCIN_D25                    *((volatile unsigned int*)(0x42720164UL))
#define bFM0P_CRC_CRCIN_D26                    *((volatile unsigned int*)(0x42720168UL))
#define bFM0P_CRC_CRCIN_D27                    *((volatile unsigned int*)(0x4272016CUL))
#define bFM0P_CRC_CRCIN_D28                    *((volatile unsigned int*)(0x42720170UL))
#define bFM0P_CRC_CRCIN_D29                    *((volatile unsigned int*)(0x42720174UL))
#define bFM0P_CRC_CRCIN_D30                    *((volatile unsigned int*)(0x42720178UL))
#define bFM0P_CRC_CRCIN_D31                    *((volatile unsigned int*)(0x4272017CUL))
#define bFM0P_CRC_CRCR_D0                      *((volatile unsigned int*)(0x42720180UL))
#define bFM0P_CRC_CRCR_D1                      *((volatile unsigned int*)(0x42720184UL))
#define bFM0P_CRC_CRCR_D2                      *((volatile unsigned int*)(0x42720188UL))
#define bFM0P_CRC_CRCR_D3                      *((volatile unsigned int*)(0x4272018CUL))
#define bFM0P_CRC_CRCR_D4                      *((volatile unsigned int*)(0x42720190UL))
#define bFM0P_CRC_CRCR_D5                      *((volatile unsigned int*)(0x42720194UL))
#define bFM0P_CRC_CRCR_D6                      *((volatile unsigned int*)(0x42720198UL))
#define bFM0P_CRC_CRCR_D7                      *((volatile unsigned int*)(0x4272019CUL))
#define bFM0P_CRC_CRCR_D8                      *((volatile unsigned int*)(0x427201A0UL))
#define bFM0P_CRC_CRCR_D9                      *((volatile unsigned int*)(0x427201A4UL))
#define bFM0P_CRC_CRCR_D10                     *((volatile unsigned int*)(0x427201A8UL))
#define bFM0P_CRC_CRCR_D11                     *((volatile unsigned int*)(0x427201ACUL))
#define bFM0P_CRC_CRCR_D12                     *((volatile unsigned int*)(0x427201B0UL))
#define bFM0P_CRC_CRCR_D13                     *((volatile unsigned int*)(0x427201B4UL))
#define bFM0P_CRC_CRCR_D14                     *((volatile unsigned int*)(0x427201B8UL))
#define bFM0P_CRC_CRCR_D15                     *((volatile unsigned int*)(0x427201BCUL))
#define bFM0P_CRC_CRCR_D16                     *((volatile unsigned int*)(0x427201C0UL))
#define bFM0P_CRC_CRCR_D17                     *((volatile unsigned int*)(0x427201C4UL))
#define bFM0P_CRC_CRCR_D18                     *((volatile unsigned int*)(0x427201C8UL))
#define bFM0P_CRC_CRCR_D19                     *((volatile unsigned int*)(0x427201CCUL))
#define bFM0P_CRC_CRCR_D20                     *((volatile unsigned int*)(0x427201D0UL))
#define bFM0P_CRC_CRCR_D21                     *((volatile unsigned int*)(0x427201D4UL))
#define bFM0P_CRC_CRCR_D22                     *((volatile unsigned int*)(0x427201D8UL))
#define bFM0P_CRC_CRCR_D23                     *((volatile unsigned int*)(0x427201DCUL))
#define bFM0P_CRC_CRCR_D24                     *((volatile unsigned int*)(0x427201E0UL))
#define bFM0P_CRC_CRCR_D25                     *((volatile unsigned int*)(0x427201E4UL))
#define bFM0P_CRC_CRCR_D26                     *((volatile unsigned int*)(0x427201E8UL))
#define bFM0P_CRC_CRCR_D27                     *((volatile unsigned int*)(0x427201ECUL))
#define bFM0P_CRC_CRCR_D28                     *((volatile unsigned int*)(0x427201F0UL))
#define bFM0P_CRC_CRCR_D29                     *((volatile unsigned int*)(0x427201F4UL))
#define bFM0P_CRC_CRCR_D30                     *((volatile unsigned int*)(0x427201F8UL))
#define bFM0P_CRC_CRCR_D31                     *((volatile unsigned int*)(0x427201FCUL))

/* Watch counter registers */
#define bFM0P_WC_WCRD_CTR0                     *((volatile unsigned int*)(0x42740000UL))
#define bFM0P_WC_WCRD_CTR1                     *((volatile unsigned int*)(0x42740004UL))
#define bFM0P_WC_WCRD_CTR2                     *((volatile unsigned int*)(0x42740008UL))
#define bFM0P_WC_WCRD_CTR3                     *((volatile unsigned int*)(0x4274000CUL))
#define bFM0P_WC_WCRD_CTR4                     *((volatile unsigned int*)(0x42740010UL))
#define bFM0P_WC_WCRD_CTR5                     *((volatile unsigned int*)(0x42740014UL))
#define bFM0P_WC_WCRL_RLC0                     *((volatile unsigned int*)(0x42740020UL))
#define bFM0P_WC_WCRL_RLC1                     *((volatile unsigned int*)(0x42740024UL))
#define bFM0P_WC_WCRL_RLC2                     *((volatile unsigned int*)(0x42740028UL))
#define bFM0P_WC_WCRL_RLC3                     *((volatile unsigned int*)(0x4274002CUL))
#define bFM0P_WC_WCRL_RLC4                     *((volatile unsigned int*)(0x42740030UL))
#define bFM0P_WC_WCRL_RLC5                     *((volatile unsigned int*)(0x42740034UL))
#define bFM0P_WC_WCCR_WCIF                     *((volatile unsigned int*)(0x42740040UL))
#define bFM0P_WC_WCCR_WCIE                     *((volatile unsigned int*)(0x42740044UL))
#define bFM0P_WC_WCCR_CS0                      *((volatile unsigned int*)(0x42740048UL))
#define bFM0P_WC_WCCR_CS1                      *((volatile unsigned int*)(0x4274004CUL))
#define bFM0P_WC_WCCR_WCOP                     *((volatile unsigned int*)(0x42740058UL))
#define bFM0P_WC_WCCR_WCEN                     *((volatile unsigned int*)(0x4274005CUL))
#define bFM0P_WC_CLK_SEL_SEL_IN0               *((volatile unsigned int*)(0x42740200UL))
#define bFM0P_WC_CLK_SEL_SEL_IN1               *((volatile unsigned int*)(0x42740204UL))
#define bFM0P_WC_CLK_SEL_SEL_OUT0              *((volatile unsigned int*)(0x42740220UL))
#define bFM0P_WC_CLK_SEL_SEL_OUT1              *((volatile unsigned int*)(0x42740224UL))
#define bFM0P_WC_CLK_SEL_SEL_OUT2              *((volatile unsigned int*)(0x42740228UL))
#define bFM0P_WC_CLK_EN_CLK_EN                 *((volatile unsigned int*)(0x42740280UL))
#define bFM0P_WC_CLK_EN_CLK_EN_R               *((volatile unsigned int*)(0x42740284UL))

/* Realtime clock registers */
#define bFM0P_RTC_WTCR1_ST                     *((volatile unsigned int*)(0x42760000UL))
#define bFM0P_RTC_WTCR1_RUN                    *((volatile unsigned int*)(0x42760008UL))
#define bFM0P_RTC_WTCR1_SRST                   *((volatile unsigned int*)(0x4276000CUL))
#define bFM0P_RTC_WTCR1_SCST                   *((volatile unsigned int*)(0x42760010UL))
#define bFM0P_RTC_WTCR1_SCRST                  *((volatile unsigned int*)(0x42760014UL))
#define bFM0P_RTC_WTCR1_BUSY                   *((volatile unsigned int*)(0x42760018UL))
#define bFM0P_RTC_WTCR1_MIEN                   *((volatile unsigned int*)(0x42760020UL))
#define bFM0P_RTC_WTCR1_HEN                    *((volatile unsigned int*)(0x42760024UL))
#define bFM0P_RTC_WTCR1_DEN                    *((volatile unsigned int*)(0x42760028UL))
#define bFM0P_RTC_WTCR1_MOEN                   *((volatile unsigned int*)(0x4276002CUL))
#define bFM0P_RTC_WTCR1_YEN                    *((volatile unsigned int*)(0x42760030UL))
#define bFM0P_RTC_WTCR1_INTSSI                 *((volatile unsigned int*)(0x42760040UL))
#define bFM0P_RTC_WTCR1_INTSI                  *((volatile unsigned int*)(0x42760044UL))
#define bFM0P_RTC_WTCR1_INTMI                  *((volatile unsigned int*)(0x42760048UL))
#define bFM0P_RTC_WTCR1_INTHI                  *((volatile unsigned int*)(0x4276004CUL))
#define bFM0P_RTC_WTCR1_INTTMI                 *((volatile unsigned int*)(0x42760050UL))
#define bFM0P_RTC_WTCR1_INTALI                 *((volatile unsigned int*)(0x42760054UL))
#define bFM0P_RTC_WTCR1_INTERI                 *((volatile unsigned int*)(0x42760058UL))
#define bFM0P_RTC_WTCR1_INTCRI                 *((volatile unsigned int*)(0x4276005CUL))
#define bFM0P_RTC_WTCR1_INTSSIE                *((volatile unsigned int*)(0x42760060UL))
#define bFM0P_RTC_WTCR1_INTSIE                 *((volatile unsigned int*)(0x42760064UL))
#define bFM0P_RTC_WTCR1_INTMIE                 *((volatile unsigned int*)(0x42760068UL))
#define bFM0P_RTC_WTCR1_INTHIE                 *((volatile unsigned int*)(0x4276006CUL))
#define bFM0P_RTC_WTCR1_INTTMIE                *((volatile unsigned int*)(0x42760070UL))
#define bFM0P_RTC_WTCR1_INTALIE                *((volatile unsigned int*)(0x42760074UL))
#define bFM0P_RTC_WTCR1_INTERIE                *((volatile unsigned int*)(0x42760078UL))
#define bFM0P_RTC_WTCR1_INTCRIE                *((volatile unsigned int*)(0x4276007CUL))
#define bFM0P_RTC_WTCR2_CREAD                  *((volatile unsigned int*)(0x42760080UL))
#define bFM0P_RTC_WTCR2_TMST                   *((volatile unsigned int*)(0x427600A0UL))
#define bFM0P_RTC_WTCR2_TMEN                   *((volatile unsigned int*)(0x427600A4UL))
#define bFM0P_RTC_WTCR2_TMRUN                  *((volatile unsigned int*)(0x427600A8UL))
#define bFM0P_RTC_WTBR_BR0                     *((volatile unsigned int*)(0x42760100UL))
#define bFM0P_RTC_WTBR_BR1                     *((volatile unsigned int*)(0x42760104UL))
#define bFM0P_RTC_WTBR_BR2                     *((volatile unsigned int*)(0x42760108UL))
#define bFM0P_RTC_WTBR_BR3                     *((volatile unsigned int*)(0x4276010CUL))
#define bFM0P_RTC_WTBR_BR4                     *((volatile unsigned int*)(0x42760110UL))
#define bFM0P_RTC_WTBR_BR5                     *((volatile unsigned int*)(0x42760114UL))
#define bFM0P_RTC_WTBR_BR6                     *((volatile unsigned int*)(0x42760118UL))
#define bFM0P_RTC_WTBR_BR7                     *((volatile unsigned int*)(0x4276011CUL))
#define bFM0P_RTC_WTBR_BR8                     *((volatile unsigned int*)(0x42760120UL))
#define bFM0P_RTC_WTBR_BR9                     *((volatile unsigned int*)(0x42760124UL))
#define bFM0P_RTC_WTBR_BR10                    *((volatile unsigned int*)(0x42760128UL))
#define bFM0P_RTC_WTBR_BR11                    *((volatile unsigned int*)(0x4276012CUL))
#define bFM0P_RTC_WTBR_BR12                    *((volatile unsigned int*)(0x42760130UL))
#define bFM0P_RTC_WTBR_BR13                    *((volatile unsigned int*)(0x42760134UL))
#define bFM0P_RTC_WTBR_BR14                    *((volatile unsigned int*)(0x42760138UL))
#define bFM0P_RTC_WTBR_BR15                    *((volatile unsigned int*)(0x4276013CUL))
#define bFM0P_RTC_WTBR_BR16                    *((volatile unsigned int*)(0x42760140UL))
#define bFM0P_RTC_WTBR_BR17                    *((volatile unsigned int*)(0x42760144UL))
#define bFM0P_RTC_WTBR_BR18                    *((volatile unsigned int*)(0x42760148UL))
#define bFM0P_RTC_WTBR_BR19                    *((volatile unsigned int*)(0x4276014CUL))
#define bFM0P_RTC_WTBR_BR20                    *((volatile unsigned int*)(0x42760150UL))
#define bFM0P_RTC_WTBR_BR21                    *((volatile unsigned int*)(0x42760154UL))
#define bFM0P_RTC_WTBR_BR22                    *((volatile unsigned int*)(0x42760158UL))
#define bFM0P_RTC_WTBR_BR23                    *((volatile unsigned int*)(0x4276015CUL))
#define bFM0P_RTC_WTSR_S0                      *((volatile unsigned int*)(0x42760180UL))
#define bFM0P_RTC_WTSR_S1                      *((volatile unsigned int*)(0x42760184UL))
#define bFM0P_RTC_WTSR_S2                      *((volatile unsigned int*)(0x42760188UL))
#define bFM0P_RTC_WTSR_S3                      *((volatile unsigned int*)(0x4276018CUL))
#define bFM0P_RTC_WTSR_TS0                     *((volatile unsigned int*)(0x42760190UL))
#define bFM0P_RTC_WTSR_TS1                     *((volatile unsigned int*)(0x42760194UL))
#define bFM0P_RTC_WTSR_TS2                     *((volatile unsigned int*)(0x42760198UL))
#define bFM0P_RTC_WTMIR_MI0                    *((volatile unsigned int*)(0x427601A0UL))
#define bFM0P_RTC_WTMIR_MI1                    *((volatile unsigned int*)(0x427601A4UL))
#define bFM0P_RTC_WTMIR_MI2                    *((volatile unsigned int*)(0x427601A8UL))
#define bFM0P_RTC_WTMIR_MI3                    *((volatile unsigned int*)(0x427601ACUL))
#define bFM0P_RTC_WTMIR_TMI0                   *((volatile unsigned int*)(0x427601B0UL))
#define bFM0P_RTC_WTMIR_TMI1                   *((volatile unsigned int*)(0x427601B4UL))
#define bFM0P_RTC_WTMIR_TMI2                   *((volatile unsigned int*)(0x427601B8UL))
#define bFM0P_RTC_WTHR_H0                      *((volatile unsigned int*)(0x427601C0UL))
#define bFM0P_RTC_WTHR_H1                      *((volatile unsigned int*)(0x427601C4UL))
#define bFM0P_RTC_WTHR_H2                      *((volatile unsigned int*)(0x427601C8UL))
#define bFM0P_RTC_WTHR_H3                      *((volatile unsigned int*)(0x427601CCUL))
#define bFM0P_RTC_WTHR_TH0                     *((volatile unsigned int*)(0x427601D0UL))
#define bFM0P_RTC_WTHR_TH1                     *((volatile unsigned int*)(0x427601D4UL))
#define bFM0P_RTC_WTDR_D0                      *((volatile unsigned int*)(0x427601E0UL))
#define bFM0P_RTC_WTDR_D1                      *((volatile unsigned int*)(0x427601E4UL))
#define bFM0P_RTC_WTDR_D2                      *((volatile unsigned int*)(0x427601E8UL))
#define bFM0P_RTC_WTDR_D3                      *((volatile unsigned int*)(0x427601ECUL))
#define bFM0P_RTC_WTDR_TD0                     *((volatile unsigned int*)(0x427601F0UL))
#define bFM0P_RTC_WTDR_TD1                     *((volatile unsigned int*)(0x427601F4UL))
#define bFM0P_RTC_WTDW_DW0                     *((volatile unsigned int*)(0x42760200UL))
#define bFM0P_RTC_WTDW_DW1                     *((volatile unsigned int*)(0x42760204UL))
#define bFM0P_RTC_WTDW_DW2                     *((volatile unsigned int*)(0x42760208UL))
#define bFM0P_RTC_WTMOR_MO0                    *((volatile unsigned int*)(0x42760220UL))
#define bFM0P_RTC_WTMOR_MO1                    *((volatile unsigned int*)(0x42760224UL))
#define bFM0P_RTC_WTMOR_MO2                    *((volatile unsigned int*)(0x42760228UL))
#define bFM0P_RTC_WTMOR_MO3                    *((volatile unsigned int*)(0x4276022CUL))
#define bFM0P_RTC_WTMOR_TMO                    *((volatile unsigned int*)(0x42760230UL))
#define bFM0P_RTC_WTYR_Y0                      *((volatile unsigned int*)(0x42760240UL))
#define bFM0P_RTC_WTYR_Y1                      *((volatile unsigned int*)(0x42760244UL))
#define bFM0P_RTC_WTYR_Y2                      *((volatile unsigned int*)(0x42760248UL))
#define bFM0P_RTC_WTYR_Y3                      *((volatile unsigned int*)(0x4276024CUL))
#define bFM0P_RTC_WTYR_TY0                     *((volatile unsigned int*)(0x42760250UL))
#define bFM0P_RTC_WTYR_TY1                     *((volatile unsigned int*)(0x42760254UL))
#define bFM0P_RTC_WTYR_TY2                     *((volatile unsigned int*)(0x42760258UL))
#define bFM0P_RTC_WTYR_TY3                     *((volatile unsigned int*)(0x4276025CUL))
#define bFM0P_RTC_ALMIR_AMI0                   *((volatile unsigned int*)(0x427602A0UL))
#define bFM0P_RTC_ALMIR_AMI1                   *((volatile unsigned int*)(0x427602A4UL))
#define bFM0P_RTC_ALMIR_AMI2                   *((volatile unsigned int*)(0x427602A8UL))
#define bFM0P_RTC_ALMIR_AMI3                   *((volatile unsigned int*)(0x427602ACUL))
#define bFM0P_RTC_ALMIR_TAMI0                  *((volatile unsigned int*)(0x427602B0UL))
#define bFM0P_RTC_ALMIR_TAMI1                  *((volatile unsigned int*)(0x427602B4UL))
#define bFM0P_RTC_ALMIR_TAMI2                  *((volatile unsigned int*)(0x427602B8UL))
#define bFM0P_RTC_ALHR_AH0                     *((volatile unsigned int*)(0x427602C0UL))
#define bFM0P_RTC_ALHR_AH1                     *((volatile unsigned int*)(0x427602C4UL))
#define bFM0P_RTC_ALHR_AH2                     *((volatile unsigned int*)(0x427602C8UL))
#define bFM0P_RTC_ALHR_AH3                     *((volatile unsigned int*)(0x427602CCUL))
#define bFM0P_RTC_ALHR_TAH0                    *((volatile unsigned int*)(0x427602D0UL))
#define bFM0P_RTC_ALHR_TAH1                    *((volatile unsigned int*)(0x427602D4UL))
#define bFM0P_RTC_ALDR_AD0                     *((volatile unsigned int*)(0x427602E0UL))
#define bFM0P_RTC_ALDR_AD1                     *((volatile unsigned int*)(0x427602E4UL))
#define bFM0P_RTC_ALDR_AD2                     *((volatile unsigned int*)(0x427602E8UL))
#define bFM0P_RTC_ALDR_AD3                     *((volatile unsigned int*)(0x427602ECUL))
#define bFM0P_RTC_ALDR_TAD0                    *((volatile unsigned int*)(0x427602F0UL))
#define bFM0P_RTC_ALDR_TAD1                    *((volatile unsigned int*)(0x427602F4UL))
#define bFM0P_RTC_ALMOR_AMO0                   *((volatile unsigned int*)(0x42760320UL))
#define bFM0P_RTC_ALMOR_AMO1                   *((volatile unsigned int*)(0x42760324UL))
#define bFM0P_RTC_ALMOR_AMO2                   *((volatile unsigned int*)(0x42760328UL))
#define bFM0P_RTC_ALMOR_AMO3                   *((volatile unsigned int*)(0x4276032CUL))
#define bFM0P_RTC_ALMOR_TAMO                   *((volatile unsigned int*)(0x42760330UL))
#define bFM0P_RTC_ALYR_AY0                     *((volatile unsigned int*)(0x42760340UL))
#define bFM0P_RTC_ALYR_AY1                     *((volatile unsigned int*)(0x42760344UL))
#define bFM0P_RTC_ALYR_AY2                     *((volatile unsigned int*)(0x42760348UL))
#define bFM0P_RTC_ALYR_AY3                     *((volatile unsigned int*)(0x4276034CUL))
#define bFM0P_RTC_ALYR_TAY0                    *((volatile unsigned int*)(0x42760350UL))
#define bFM0P_RTC_ALYR_TAY1                    *((volatile unsigned int*)(0x42760354UL))
#define bFM0P_RTC_ALYR_TAY2                    *((volatile unsigned int*)(0x42760358UL))
#define bFM0P_RTC_ALYR_TAY3                    *((volatile unsigned int*)(0x4276035CUL))
#define bFM0P_RTC_WTTR_TM0                     *((volatile unsigned int*)(0x42760380UL))
#define bFM0P_RTC_WTTR_TM1                     *((volatile unsigned int*)(0x42760384UL))
#define bFM0P_RTC_WTTR_TM2                     *((volatile unsigned int*)(0x42760388UL))
#define bFM0P_RTC_WTTR_TM3                     *((volatile unsigned int*)(0x4276038CUL))
#define bFM0P_RTC_WTTR_TM4                     *((volatile unsigned int*)(0x42760390UL))
#define bFM0P_RTC_WTTR_TM5                     *((volatile unsigned int*)(0x42760394UL))
#define bFM0P_RTC_WTTR_TM6                     *((volatile unsigned int*)(0x42760398UL))
#define bFM0P_RTC_WTTR_TM7                     *((volatile unsigned int*)(0x4276039CUL))
#define bFM0P_RTC_WTTR_TM8                     *((volatile unsigned int*)(0x427603A0UL))
#define bFM0P_RTC_WTTR_TM9                     *((volatile unsigned int*)(0x427603A4UL))
#define bFM0P_RTC_WTTR_TM10                    *((volatile unsigned int*)(0x427603A8UL))
#define bFM0P_RTC_WTTR_TM11                    *((volatile unsigned int*)(0x427603ACUL))
#define bFM0P_RTC_WTTR_TM12                    *((volatile unsigned int*)(0x427603B0UL))
#define bFM0P_RTC_WTTR_TM13                    *((volatile unsigned int*)(0x427603B4UL))
#define bFM0P_RTC_WTTR_TM14                    *((volatile unsigned int*)(0x427603B8UL))
#define bFM0P_RTC_WTTR_TM15                    *((volatile unsigned int*)(0x427603BCUL))
#define bFM0P_RTC_WTTR_TM16                    *((volatile unsigned int*)(0x427603C0UL))
#define bFM0P_RTC_WTTR_TM17                    *((volatile unsigned int*)(0x427603C4UL))
#define bFM0P_RTC_WTCLKS_WTCLKS                *((volatile unsigned int*)(0x42760400UL))
#define bFM0P_RTC_WTCLKM_WTCLKM0               *((volatile unsigned int*)(0x42760420UL))
#define bFM0P_RTC_WTCLKM_WTCLKM1               *((volatile unsigned int*)(0x42760424UL))
#define bFM0P_RTC_WTCAL_WTCAL0                 *((volatile unsigned int*)(0x42760480UL))
#define bFM0P_RTC_WTCAL_WTCAL1                 *((volatile unsigned int*)(0x42760484UL))
#define bFM0P_RTC_WTCAL_WTCAL2                 *((volatile unsigned int*)(0x42760488UL))
#define bFM0P_RTC_WTCAL_WTCAL3                 *((volatile unsigned int*)(0x4276048CUL))
#define bFM0P_RTC_WTCAL_WTCAL4                 *((volatile unsigned int*)(0x42760490UL))
#define bFM0P_RTC_WTCAL_WTCAL5                 *((volatile unsigned int*)(0x42760494UL))
#define bFM0P_RTC_WTCAL_WTCAL6                 *((volatile unsigned int*)(0x42760498UL))
#define bFM0P_RTC_WTCAL_WTCAL7                 *((volatile unsigned int*)(0x4276049CUL))
#define bFM0P_RTC_WTCAL_WTCAL8                 *((volatile unsigned int*)(0x427604A0UL))
#define bFM0P_RTC_WTCAL_WTCAL9                 *((volatile unsigned int*)(0x427604A4UL))
#define bFM0P_RTC_WTCALEN_WTCALEN              *((volatile unsigned int*)(0x427604C0UL))
#define bFM0P_RTC_WTDIV_WTDIV0                 *((volatile unsigned int*)(0x42760500UL))
#define bFM0P_RTC_WTDIV_WTDIV1                 *((volatile unsigned int*)(0x42760504UL))
#define bFM0P_RTC_WTDIV_WTDIV2                 *((volatile unsigned int*)(0x42760508UL))
#define bFM0P_RTC_WTDIV_WTDIV3                 *((volatile unsigned int*)(0x4276050CUL))
#define bFM0P_RTC_WTDIVEN_WTDIVEN              *((volatile unsigned int*)(0x42760520UL))
#define bFM0P_RTC_WTDIVEN_WTDIVRDY             *((volatile unsigned int*)(0x42760524UL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD0           *((volatile unsigned int*)(0x42760580UL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD1           *((volatile unsigned int*)(0x42760584UL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD2           *((volatile unsigned int*)(0x42760588UL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD3           *((volatile unsigned int*)(0x4276058CUL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD4           *((volatile unsigned int*)(0x42760590UL))
#define bFM0P_RTC_WTCALPRD_WTCALPRD5           *((volatile unsigned int*)(0x42760594UL))
#define bFM0P_RTC_WTCOSEL_WTCOSEL              *((volatile unsigned int*)(0x42760600UL))

/* LSCRP registers */
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD0       *((volatile unsigned int*)(0x42780000UL))
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD1       *((volatile unsigned int*)(0x42780004UL))
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD2       *((volatile unsigned int*)(0x42780008UL))
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD3       *((volatile unsigned int*)(0x4278000CUL))
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD4       *((volatile unsigned int*)(0x42780010UL))
#define bFM0P_LSCRP_LCR_PRSLD_LCR_PRSLD5       *((volatile unsigned int*)(0x42780014UL))

/* PCG registers */
#define bFM0P_PCG_CKEN0_MFSCK0                 *((volatile unsigned int*)(0x42782000UL))
#define bFM0P_PCG_CKEN0_MFSCK1                 *((volatile unsigned int*)(0x42782004UL))
#define bFM0P_PCG_CKEN0_MFSCK2                 *((volatile unsigned int*)(0x42782008UL))
#define bFM0P_PCG_CKEN0_MFSCK3                 *((volatile unsigned int*)(0x4278200CUL))
#define bFM0P_PCG_CKEN0_MFSCK4                 *((volatile unsigned int*)(0x42782010UL))
#define bFM0P_PCG_CKEN0_MFSCK5                 *((volatile unsigned int*)(0x42782014UL))
#define bFM0P_PCG_CKEN0_MFSCK6                 *((volatile unsigned int*)(0x42782018UL))
#define bFM0P_PCG_CKEN0_MFSCK7                 *((volatile unsigned int*)(0x4278201CUL))
#define bFM0P_PCG_CKEN0_MFSCK8                 *((volatile unsigned int*)(0x42782020UL))
#define bFM0P_PCG_CKEN0_MFSCK9                 *((volatile unsigned int*)(0x42782024UL))
#define bFM0P_PCG_CKEN0_MFSCK10                *((volatile unsigned int*)(0x42782028UL))
#define bFM0P_PCG_CKEN0_MFSCK11                *((volatile unsigned int*)(0x4278202CUL))
#define bFM0P_PCG_CKEN0_MFSCK12                *((volatile unsigned int*)(0x42782030UL))
#define bFM0P_PCG_CKEN0_MFSCK13                *((volatile unsigned int*)(0x42782034UL))
#define bFM0P_PCG_CKEN0_MFSCK14                *((volatile unsigned int*)(0x42782038UL))
#define bFM0P_PCG_CKEN0_MFSCK15                *((volatile unsigned int*)(0x4278203CUL))
#define bFM0P_PCG_CKEN0_ADCCK0                 *((volatile unsigned int*)(0x42782040UL))
#define bFM0P_PCG_CKEN0_ADCCK1                 *((volatile unsigned int*)(0x42782044UL))
#define bFM0P_PCG_CKEN0_ADCCK2                 *((volatile unsigned int*)(0x42782048UL))
#define bFM0P_PCG_CKEN0_ADCCK3                 *((volatile unsigned int*)(0x4278204CUL))
#define bFM0P_PCG_CKEN0_DMACK                  *((volatile unsigned int*)(0x42782060UL))
#define bFM0P_PCG_CKEN0_GIOCK                  *((volatile unsigned int*)(0x42782070UL))
#define bFM0P_PCG_MRST0_MFSRST0                *((volatile unsigned int*)(0x42782080UL))
#define bFM0P_PCG_MRST0_MFSRST1                *((volatile unsigned int*)(0x42782084UL))
#define bFM0P_PCG_MRST0_MFSRST2                *((volatile unsigned int*)(0x42782088UL))
#define bFM0P_PCG_MRST0_MFSRST3                *((volatile unsigned int*)(0x4278208CUL))
#define bFM0P_PCG_MRST0_MFSRST4                *((volatile unsigned int*)(0x42782090UL))
#define bFM0P_PCG_MRST0_MFSRST5                *((volatile unsigned int*)(0x42782094UL))
#define bFM0P_PCG_MRST0_MFSRST6                *((volatile unsigned int*)(0x42782098UL))
#define bFM0P_PCG_MRST0_MFSRST7                *((volatile unsigned int*)(0x4278209CUL))
#define bFM0P_PCG_MRST0_MFSRST8                *((volatile unsigned int*)(0x427820A0UL))
#define bFM0P_PCG_MRST0_MFSRST9                *((volatile unsigned int*)(0x427820A4UL))
#define bFM0P_PCG_MRST0_MFSRST10               *((volatile unsigned int*)(0x427820A8UL))
#define bFM0P_PCG_MRST0_MFSRST11               *((volatile unsigned int*)(0x427820ACUL))
#define bFM0P_PCG_MRST0_MFSRST12               *((volatile unsigned int*)(0x427820B0UL))
#define bFM0P_PCG_MRST0_MFSRST13               *((volatile unsigned int*)(0x427820B4UL))
#define bFM0P_PCG_MRST0_MFSRST14               *((volatile unsigned int*)(0x427820B8UL))
#define bFM0P_PCG_MRST0_MFSRST15               *((volatile unsigned int*)(0x427820BCUL))
#define bFM0P_PCG_MRST0_ADCRST0                *((volatile unsigned int*)(0x427820C0UL))
#define bFM0P_PCG_MRST0_ADCRST1                *((volatile unsigned int*)(0x427820C4UL))
#define bFM0P_PCG_MRST0_ADCRST2                *((volatile unsigned int*)(0x427820C8UL))
#define bFM0P_PCG_MRST0_ADCRST3                *((volatile unsigned int*)(0x427820CCUL))
#define bFM0P_PCG_MRST0_DMARST                 *((volatile unsigned int*)(0x427820E0UL))
#define bFM0P_PCG_CKEN1_BTMCK0                 *((volatile unsigned int*)(0x42782200UL))
#define bFM0P_PCG_CKEN1_BTMCK1                 *((volatile unsigned int*)(0x42782204UL))
#define bFM0P_PCG_CKEN1_BTMCK2                 *((volatile unsigned int*)(0x42782208UL))
#define bFM0P_PCG_CKEN1_BTMCK3                 *((volatile unsigned int*)(0x4278220CUL))
#define bFM0P_PCG_CKEN1_MFTCK0                 *((volatile unsigned int*)(0x42782220UL))
#define bFM0P_PCG_CKEN1_MFTCK1                 *((volatile unsigned int*)(0x42782224UL))
#define bFM0P_PCG_CKEN1_MFTCK2                 *((volatile unsigned int*)(0x42782228UL))
#define bFM0P_PCG_CKEN1_MFTCK3                 *((volatile unsigned int*)(0x4278222CUL))
#define bFM0P_PCG_CKEN1_QDUCK0                 *((volatile unsigned int*)(0x42782240UL))
#define bFM0P_PCG_CKEN1_QDUCK1                 *((volatile unsigned int*)(0x42782244UL))
#define bFM0P_PCG_CKEN1_QDUCK2                 *((volatile unsigned int*)(0x42782248UL))
#define bFM0P_PCG_CKEN1_QDUCK3                 *((volatile unsigned int*)(0x4278224CUL))
#define bFM0P_PCG_MRST1_BTMRST0                *((volatile unsigned int*)(0x42782280UL))
#define bFM0P_PCG_MRST1_BTMRST1                *((volatile unsigned int*)(0x42782284UL))
#define bFM0P_PCG_MRST1_BTMRST2                *((volatile unsigned int*)(0x42782288UL))
#define bFM0P_PCG_MRST1_BTMRST3                *((volatile unsigned int*)(0x4278228CUL))
#define bFM0P_PCG_MRST1_MFTRST0                *((volatile unsigned int*)(0x427822A0UL))
#define bFM0P_PCG_MRST1_MFTRST1                *((volatile unsigned int*)(0x427822A4UL))
#define bFM0P_PCG_MRST1_MFTRST2                *((volatile unsigned int*)(0x427822A8UL))
#define bFM0P_PCG_MRST1_MFTRST3                *((volatile unsigned int*)(0x427822ACUL))
#define bFM0P_PCG_MRST1_QDURST0                *((volatile unsigned int*)(0x427822C0UL))
#define bFM0P_PCG_MRST1_QDURST1                *((volatile unsigned int*)(0x427822C4UL))
#define bFM0P_PCG_MRST1_QDURST2                *((volatile unsigned int*)(0x427822C8UL))
#define bFM0P_PCG_MRST1_QDURST3                *((volatile unsigned int*)(0x427822CCUL))
#define bFM0P_PCG_CKEN2_CANCK0                 *((volatile unsigned int*)(0x42782410UL))
#define bFM0P_PCG_CKEN2_CANCK1                 *((volatile unsigned int*)(0x42782414UL))
#define bFM0P_PCG_MRST2_CANRST0                *((volatile unsigned int*)(0x42782490UL))
#define bFM0P_PCG_MRST2_CANRST1                *((volatile unsigned int*)(0x42782494UL))

/* DMA controller */
#define bFM0P_DMAC_DMACR_DH0                   *((volatile unsigned int*)(0x42C00060UL))
#define bFM0P_DMAC_DMACR_DH1                   *((volatile unsigned int*)(0x42C00064UL))
#define bFM0P_DMAC_DMACR_DH2                   *((volatile unsigned int*)(0x42C00068UL))
#define bFM0P_DMAC_DMACR_DH3                   *((volatile unsigned int*)(0x42C0006CUL))
#define bFM0P_DMAC_DMACR_PR                    *((volatile unsigned int*)(0x42C00070UL))
#define bFM0P_DMAC_DMACR_DS                    *((volatile unsigned int*)(0x42C00078UL))
#define bFM0P_DMAC_DMACR_DE                    *((volatile unsigned int*)(0x42C0007CUL))
#define bFM0P_DMAC_DMACA0_TC0                  *((volatile unsigned int*)(0x42C00200UL))
#define bFM0P_DMAC_DMACA0_TC1                  *((volatile unsigned int*)(0x42C00204UL))
#define bFM0P_DMAC_DMACA0_TC2                  *((volatile unsigned int*)(0x42C00208UL))
#define bFM0P_DMAC_DMACA0_TC3                  *((volatile unsigned int*)(0x42C0020CUL))
#define bFM0P_DMAC_DMACA0_TC4                  *((volatile unsigned int*)(0x42C00210UL))
#define bFM0P_DMAC_DMACA0_TC5                  *((volatile unsigned int*)(0x42C00214UL))
#define bFM0P_DMAC_DMACA0_TC6                  *((volatile unsigned int*)(0x42C00218UL))
#define bFM0P_DMAC_DMACA0_TC7                  *((volatile unsigned int*)(0x42C0021CUL))
#define bFM0P_DMAC_DMACA0_TC8                  *((volatile unsigned int*)(0x42C00220UL))
#define bFM0P_DMAC_DMACA0_TC9                  *((volatile unsigned int*)(0x42C00224UL))
#define bFM0P_DMAC_DMACA0_TC10                 *((volatile unsigned int*)(0x42C00228UL))
#define bFM0P_DMAC_DMACA0_TC11                 *((volatile unsigned int*)(0x42C0022CUL))
#define bFM0P_DMAC_DMACA0_TC12                 *((volatile unsigned int*)(0x42C00230UL))
#define bFM0P_DMAC_DMACA0_TC13                 *((volatile unsigned int*)(0x42C00234UL))
#define bFM0P_DMAC_DMACA0_TC14                 *((volatile unsigned int*)(0x42C00238UL))
#define bFM0P_DMAC_DMACA0_TC15                 *((volatile unsigned int*)(0x42C0023CUL))
#define bFM0P_DMAC_DMACA0_BC0                  *((volatile unsigned int*)(0x42C00240UL))
#define bFM0P_DMAC_DMACA0_BC1                  *((volatile unsigned int*)(0x42C00244UL))
#define bFM0P_DMAC_DMACA0_BC2                  *((volatile unsigned int*)(0x42C00248UL))
#define bFM0P_DMAC_DMACA0_BC3                  *((volatile unsigned int*)(0x42C0024CUL))
#define bFM0P_DMAC_DMACA0_IS0                  *((volatile unsigned int*)(0x42C0025CUL))
#define bFM0P_DMAC_DMACA0_IS1                  *((volatile unsigned int*)(0x42C00260UL))
#define bFM0P_DMAC_DMACA0_IS2                  *((volatile unsigned int*)(0x42C00264UL))
#define bFM0P_DMAC_DMACA0_IS3                  *((volatile unsigned int*)(0x42C00268UL))
#define bFM0P_DMAC_DMACA0_IS4                  *((volatile unsigned int*)(0x42C0026CUL))
#define bFM0P_DMAC_DMACA0_IS5                  *((volatile unsigned int*)(0x42C00270UL))
#define bFM0P_DMAC_DMACA0_ST                   *((volatile unsigned int*)(0x42C00274UL))
#define bFM0P_DMAC_DMACA0_PB                   *((volatile unsigned int*)(0x42C00278UL))
#define bFM0P_DMAC_DMACA0_EB                   *((volatile unsigned int*)(0x42C0027CUL))
#define bFM0P_DMAC_DMACB0_EM                   *((volatile unsigned int*)(0x42C00280UL))
#define bFM0P_DMAC_DMACB0_SS0                  *((volatile unsigned int*)(0x42C002C0UL))
#define bFM0P_DMAC_DMACB0_SS1                  *((volatile unsigned int*)(0x42C002C4UL))
#define bFM0P_DMAC_DMACB0_SS2                  *((volatile unsigned int*)(0x42C002C8UL))
#define bFM0P_DMAC_DMACB0_CI                   *((volatile unsigned int*)(0x42C002CCUL))
#define bFM0P_DMAC_DMACB0_EI                   *((volatile unsigned int*)(0x42C002D0UL))
#define bFM0P_DMAC_DMACB0_RD                   *((volatile unsigned int*)(0x42C002D4UL))
#define bFM0P_DMAC_DMACB0_RS                   *((volatile unsigned int*)(0x42C002D8UL))
#define bFM0P_DMAC_DMACB0_RC                   *((volatile unsigned int*)(0x42C002DCUL))
#define bFM0P_DMAC_DMACB0_FD                   *((volatile unsigned int*)(0x42C002E0UL))
#define bFM0P_DMAC_DMACB0_FS                   *((volatile unsigned int*)(0x42C002E4UL))
#define bFM0P_DMAC_DMACB0_TW0                  *((volatile unsigned int*)(0x42C002E8UL))
#define bFM0P_DMAC_DMACB0_TW1                  *((volatile unsigned int*)(0x42C002ECUL))
#define bFM0P_DMAC_DMACB0_MS0                  *((volatile unsigned int*)(0x42C002F0UL))
#define bFM0P_DMAC_DMACB0_MS1                  *((volatile unsigned int*)(0x42C002F4UL))
#define bFM0P_DMAC_DMACA1_TC0                  *((volatile unsigned int*)(0x42C00400UL))
#define bFM0P_DMAC_DMACA1_TC1                  *((volatile unsigned int*)(0x42C00404UL))
#define bFM0P_DMAC_DMACA1_TC2                  *((volatile unsigned int*)(0x42C00408UL))
#define bFM0P_DMAC_DMACA1_TC3                  *((volatile unsigned int*)(0x42C0040CUL))
#define bFM0P_DMAC_DMACA1_TC4                  *((volatile unsigned int*)(0x42C00410UL))
#define bFM0P_DMAC_DMACA1_TC5                  *((volatile unsigned int*)(0x42C00414UL))
#define bFM0P_DMAC_DMACA1_TC6                  *((volatile unsigned int*)(0x42C00418UL))
#define bFM0P_DMAC_DMACA1_TC7                  *((volatile unsigned int*)(0x42C0041CUL))
#define bFM0P_DMAC_DMACA1_TC8                  *((volatile unsigned int*)(0x42C00420UL))
#define bFM0P_DMAC_DMACA1_TC9                  *((volatile unsigned int*)(0x42C00424UL))
#define bFM0P_DMAC_DMACA1_TC10                 *((volatile unsigned int*)(0x42C00428UL))
#define bFM0P_DMAC_DMACA1_TC11                 *((volatile unsigned int*)(0x42C0042CUL))
#define bFM0P_DMAC_DMACA1_TC12                 *((volatile unsigned int*)(0x42C00430UL))
#define bFM0P_DMAC_DMACA1_TC13                 *((volatile unsigned int*)(0x42C00434UL))
#define bFM0P_DMAC_DMACA1_TC14                 *((volatile unsigned int*)(0x42C00438UL))
#define bFM0P_DMAC_DMACA1_TC15                 *((volatile unsigned int*)(0x42C0043CUL))
#define bFM0P_DMAC_DMACA1_BC0                  *((volatile unsigned int*)(0x42C00440UL))
#define bFM0P_DMAC_DMACA1_BC1                  *((volatile unsigned int*)(0x42C00444UL))
#define bFM0P_DMAC_DMACA1_BC2                  *((volatile unsigned int*)(0x42C00448UL))
#define bFM0P_DMAC_DMACA1_BC3                  *((volatile unsigned int*)(0x42C0044CUL))
#define bFM0P_DMAC_DMACA1_IS0                  *((volatile unsigned int*)(0x42C0045CUL))
#define bFM0P_DMAC_DMACA1_IS1                  *((volatile unsigned int*)(0x42C00460UL))
#define bFM0P_DMAC_DMACA1_IS2                  *((volatile unsigned int*)(0x42C00464UL))
#define bFM0P_DMAC_DMACA1_IS3                  *((volatile unsigned int*)(0x42C00468UL))
#define bFM0P_DMAC_DMACA1_IS4                  *((volatile unsigned int*)(0x42C0046CUL))
#define bFM0P_DMAC_DMACA1_IS5                  *((volatile unsigned int*)(0x42C00470UL))
#define bFM0P_DMAC_DMACA1_ST                   *((volatile unsigned int*)(0x42C00474UL))
#define bFM0P_DMAC_DMACA1_PB                   *((volatile unsigned int*)(0x42C00478UL))
#define bFM0P_DMAC_DMACA1_EB                   *((volatile unsigned int*)(0x42C0047CUL))
#define bFM0P_DMAC_DMACB1_EM                   *((volatile unsigned int*)(0x42C00480UL))
#define bFM0P_DMAC_DMACB1_SS0                  *((volatile unsigned int*)(0x42C004C0UL))
#define bFM0P_DMAC_DMACB1_SS1                  *((volatile unsigned int*)(0x42C004C4UL))
#define bFM0P_DMAC_DMACB1_SS2                  *((volatile unsigned int*)(0x42C004C8UL))
#define bFM0P_DMAC_DMACB1_CI                   *((volatile unsigned int*)(0x42C004CCUL))
#define bFM0P_DMAC_DMACB1_EI                   *((volatile unsigned int*)(0x42C004D0UL))
#define bFM0P_DMAC_DMACB1_RD                   *((volatile unsigned int*)(0x42C004D4UL))
#define bFM0P_DMAC_DMACB1_RS                   *((volatile unsigned int*)(0x42C004D8UL))
#define bFM0P_DMAC_DMACB1_RC                   *((volatile unsigned int*)(0x42C004DCUL))
#define bFM0P_DMAC_DMACB1_FD                   *((volatile unsigned int*)(0x42C004E0UL))
#define bFM0P_DMAC_DMACB1_FS                   *((volatile unsigned int*)(0x42C004E4UL))
#define bFM0P_DMAC_DMACB1_TW0                  *((volatile unsigned int*)(0x42C004E8UL))
#define bFM0P_DMAC_DMACB1_TW1                  *((volatile unsigned int*)(0x42C004ECUL))
#define bFM0P_DMAC_DMACB1_MS0                  *((volatile unsigned int*)(0x42C004F0UL))
#define bFM0P_DMAC_DMACB1_MS1                  *((volatile unsigned int*)(0x42C004F4UL))
#define bFM0P_DMAC_DMACA2_TC0                  *((volatile unsigned int*)(0x42C00600UL))
#define bFM0P_DMAC_DMACA2_TC1                  *((volatile unsigned int*)(0x42C00604UL))
#define bFM0P_DMAC_DMACA2_TC2                  *((volatile unsigned int*)(0x42C00608UL))
#define bFM0P_DMAC_DMACA2_TC3                  *((volatile unsigned int*)(0x42C0060CUL))
#define bFM0P_DMAC_DMACA2_TC4                  *((volatile unsigned int*)(0x42C00610UL))
#define bFM0P_DMAC_DMACA2_TC5                  *((volatile unsigned int*)(0x42C00614UL))
#define bFM0P_DMAC_DMACA2_TC6                  *((volatile unsigned int*)(0x42C00618UL))
#define bFM0P_DMAC_DMACA2_TC7                  *((volatile unsigned int*)(0x42C0061CUL))
#define bFM0P_DMAC_DMACA2_TC8                  *((volatile unsigned int*)(0x42C00620UL))
#define bFM0P_DMAC_DMACA2_TC9                  *((volatile unsigned int*)(0x42C00624UL))
#define bFM0P_DMAC_DMACA2_TC10                 *((volatile unsigned int*)(0x42C00628UL))
#define bFM0P_DMAC_DMACA2_TC11                 *((volatile unsigned int*)(0x42C0062CUL))
#define bFM0P_DMAC_DMACA2_TC12                 *((volatile unsigned int*)(0x42C00630UL))
#define bFM0P_DMAC_DMACA2_TC13                 *((volatile unsigned int*)(0x42C00634UL))
#define bFM0P_DMAC_DMACA2_TC14                 *((volatile unsigned int*)(0x42C00638UL))
#define bFM0P_DMAC_DMACA2_TC15                 *((volatile unsigned int*)(0x42C0063CUL))
#define bFM0P_DMAC_DMACA2_BC0                  *((volatile unsigned int*)(0x42C00640UL))
#define bFM0P_DMAC_DMACA2_BC1                  *((volatile unsigned int*)(0x42C00644UL))
#define bFM0P_DMAC_DMACA2_BC2                  *((volatile unsigned int*)(0x42C00648UL))
#define bFM0P_DMAC_DMACA2_BC3                  *((volatile unsigned int*)(0x42C0064CUL))
#define bFM0P_DMAC_DMACA2_IS0                  *((volatile unsigned int*)(0x42C0065CUL))
#define bFM0P_DMAC_DMACA2_IS1                  *((volatile unsigned int*)(0x42C00660UL))
#define bFM0P_DMAC_DMACA2_IS2                  *((volatile unsigned int*)(0x42C00664UL))
#define bFM0P_DMAC_DMACA2_IS3                  *((volatile unsigned int*)(0x42C00668UL))
#define bFM0P_DMAC_DMACA2_IS4                  *((volatile unsigned int*)(0x42C0066CUL))
#define bFM0P_DMAC_DMACA2_IS5                  *((volatile unsigned int*)(0x42C00670UL))
#define bFM0P_DMAC_DMACA2_ST                   *((volatile unsigned int*)(0x42C00674UL))
#define bFM0P_DMAC_DMACA2_PB                   *((volatile unsigned int*)(0x42C00678UL))
#define bFM0P_DMAC_DMACA2_EB                   *((volatile unsigned int*)(0x42C0067CUL))
#define bFM0P_DMAC_DMACB2_EM                   *((volatile unsigned int*)(0x42C00680UL))
#define bFM0P_DMAC_DMACB2_SS0                  *((volatile unsigned int*)(0x42C006C0UL))
#define bFM0P_DMAC_DMACB2_SS1                  *((volatile unsigned int*)(0x42C006C4UL))
#define bFM0P_DMAC_DMACB2_SS2                  *((volatile unsigned int*)(0x42C006C8UL))
#define bFM0P_DMAC_DMACB2_CI                   *((volatile unsigned int*)(0x42C006CCUL))
#define bFM0P_DMAC_DMACB2_EI                   *((volatile unsigned int*)(0x42C006D0UL))
#define bFM0P_DMAC_DMACB2_RD                   *((volatile unsigned int*)(0x42C006D4UL))
#define bFM0P_DMAC_DMACB2_RS                   *((volatile unsigned int*)(0x42C006D8UL))
#define bFM0P_DMAC_DMACB2_RC                   *((volatile unsigned int*)(0x42C006DCUL))
#define bFM0P_DMAC_DMACB2_FD                   *((volatile unsigned int*)(0x42C006E0UL))
#define bFM0P_DMAC_DMACB2_FS                   *((volatile unsigned int*)(0x42C006E4UL))
#define bFM0P_DMAC_DMACB2_TW0                  *((volatile unsigned int*)(0x42C006E8UL))
#define bFM0P_DMAC_DMACB2_TW1                  *((volatile unsigned int*)(0x42C006ECUL))
#define bFM0P_DMAC_DMACB2_MS0                  *((volatile unsigned int*)(0x42C006F0UL))
#define bFM0P_DMAC_DMACB2_MS1                  *((volatile unsigned int*)(0x42C006F4UL))
#define bFM0P_DMAC_DMACA3_TC0                  *((volatile unsigned int*)(0x42C00800UL))
#define bFM0P_DMAC_DMACA3_TC1                  *((volatile unsigned int*)(0x42C00804UL))
#define bFM0P_DMAC_DMACA3_TC2                  *((volatile unsigned int*)(0x42C00808UL))
#define bFM0P_DMAC_DMACA3_TC3                  *((volatile unsigned int*)(0x42C0080CUL))
#define bFM0P_DMAC_DMACA3_TC4                  *((volatile unsigned int*)(0x42C00810UL))
#define bFM0P_DMAC_DMACA3_TC5                  *((volatile unsigned int*)(0x42C00814UL))
#define bFM0P_DMAC_DMACA3_TC6                  *((volatile unsigned int*)(0x42C00818UL))
#define bFM0P_DMAC_DMACA3_TC7                  *((volatile unsigned int*)(0x42C0081CUL))
#define bFM0P_DMAC_DMACA3_TC8                  *((volatile unsigned int*)(0x42C00820UL))
#define bFM0P_DMAC_DMACA3_TC9                  *((volatile unsigned int*)(0x42C00824UL))
#define bFM0P_DMAC_DMACA3_TC10                 *((volatile unsigned int*)(0x42C00828UL))
#define bFM0P_DMAC_DMACA3_TC11                 *((volatile unsigned int*)(0x42C0082CUL))
#define bFM0P_DMAC_DMACA3_TC12                 *((volatile unsigned int*)(0x42C00830UL))
#define bFM0P_DMAC_DMACA3_TC13                 *((volatile unsigned int*)(0x42C00834UL))
#define bFM0P_DMAC_DMACA3_TC14                 *((volatile unsigned int*)(0x42C00838UL))
#define bFM0P_DMAC_DMACA3_TC15                 *((volatile unsigned int*)(0x42C0083CUL))
#define bFM0P_DMAC_DMACA3_BC0                  *((volatile unsigned int*)(0x42C00840UL))
#define bFM0P_DMAC_DMACA3_BC1                  *((volatile unsigned int*)(0x42C00844UL))
#define bFM0P_DMAC_DMACA3_BC2                  *((volatile unsigned int*)(0x42C00848UL))
#define bFM0P_DMAC_DMACA3_BC3                  *((volatile unsigned int*)(0x42C0084CUL))
#define bFM0P_DMAC_DMACA3_IS0                  *((volatile unsigned int*)(0x42C0085CUL))
#define bFM0P_DMAC_DMACA3_IS1                  *((volatile unsigned int*)(0x42C00860UL))
#define bFM0P_DMAC_DMACA3_IS2                  *((volatile unsigned int*)(0x42C00864UL))
#define bFM0P_DMAC_DMACA3_IS3                  *((volatile unsigned int*)(0x42C00868UL))
#define bFM0P_DMAC_DMACA3_IS4                  *((volatile unsigned int*)(0x42C0086CUL))
#define bFM0P_DMAC_DMACA3_IS5                  *((volatile unsigned int*)(0x42C00870UL))
#define bFM0P_DMAC_DMACA3_ST                   *((volatile unsigned int*)(0x42C00874UL))
#define bFM0P_DMAC_DMACA3_PB                   *((volatile unsigned int*)(0x42C00878UL))
#define bFM0P_DMAC_DMACA3_EB                   *((volatile unsigned int*)(0x42C0087CUL))
#define bFM0P_DMAC_DMACB3_EM                   *((volatile unsigned int*)(0x42C00880UL))
#define bFM0P_DMAC_DMACB3_SS0                  *((volatile unsigned int*)(0x42C008C0UL))
#define bFM0P_DMAC_DMACB3_SS1                  *((volatile unsigned int*)(0x42C008C4UL))
#define bFM0P_DMAC_DMACB3_SS2                  *((volatile unsigned int*)(0x42C008C8UL))
#define bFM0P_DMAC_DMACB3_CI                   *((volatile unsigned int*)(0x42C008CCUL))
#define bFM0P_DMAC_DMACB3_EI                   *((volatile unsigned int*)(0x42C008D0UL))
#define bFM0P_DMAC_DMACB3_RD                   *((volatile unsigned int*)(0x42C008D4UL))
#define bFM0P_DMAC_DMACB3_RS                   *((volatile unsigned int*)(0x42C008D8UL))
#define bFM0P_DMAC_DMACB3_RC                   *((volatile unsigned int*)(0x42C008DCUL))
#define bFM0P_DMAC_DMACB3_FD                   *((volatile unsigned int*)(0x42C008E0UL))
#define bFM0P_DMAC_DMACB3_FS                   *((volatile unsigned int*)(0x42C008E4UL))
#define bFM0P_DMAC_DMACB3_TW0                  *((volatile unsigned int*)(0x42C008E8UL))
#define bFM0P_DMAC_DMACB3_TW1                  *((volatile unsigned int*)(0x42C008ECUL))
#define bFM0P_DMAC_DMACB3_MS0                  *((volatile unsigned int*)(0x42C008F0UL))
#define bFM0P_DMAC_DMACB3_MS1                  *((volatile unsigned int*)(0x42C008F4UL))
#define bFM0P_DMAC_DMACA4_TC0                  *((volatile unsigned int*)(0x42C00A00UL))
#define bFM0P_DMAC_DMACA4_TC1                  *((volatile unsigned int*)(0x42C00A04UL))
#define bFM0P_DMAC_DMACA4_TC2                  *((volatile unsigned int*)(0x42C00A08UL))
#define bFM0P_DMAC_DMACA4_TC3                  *((volatile unsigned int*)(0x42C00A0CUL))
#define bFM0P_DMAC_DMACA4_TC4                  *((volatile unsigned int*)(0x42C00A10UL))
#define bFM0P_DMAC_DMACA4_TC5                  *((volatile unsigned int*)(0x42C00A14UL))
#define bFM0P_DMAC_DMACA4_TC6                  *((volatile unsigned int*)(0x42C00A18UL))
#define bFM0P_DMAC_DMACA4_TC7                  *((volatile unsigned int*)(0x42C00A1CUL))
#define bFM0P_DMAC_DMACA4_TC8                  *((volatile unsigned int*)(0x42C00A20UL))
#define bFM0P_DMAC_DMACA4_TC9                  *((volatile unsigned int*)(0x42C00A24UL))
#define bFM0P_DMAC_DMACA4_TC10                 *((volatile unsigned int*)(0x42C00A28UL))
#define bFM0P_DMAC_DMACA4_TC11                 *((volatile unsigned int*)(0x42C00A2CUL))
#define bFM0P_DMAC_DMACA4_TC12                 *((volatile unsigned int*)(0x42C00A30UL))
#define bFM0P_DMAC_DMACA4_TC13                 *((volatile unsigned int*)(0x42C00A34UL))
#define bFM0P_DMAC_DMACA4_TC14                 *((volatile unsigned int*)(0x42C00A38UL))
#define bFM0P_DMAC_DMACA4_TC15                 *((volatile unsigned int*)(0x42C00A3CUL))
#define bFM0P_DMAC_DMACA4_BC0                  *((volatile unsigned int*)(0x42C00A40UL))
#define bFM0P_DMAC_DMACA4_BC1                  *((volatile unsigned int*)(0x42C00A44UL))
#define bFM0P_DMAC_DMACA4_BC2                  *((volatile unsigned int*)(0x42C00A48UL))
#define bFM0P_DMAC_DMACA4_BC3                  *((volatile unsigned int*)(0x42C00A4CUL))
#define bFM0P_DMAC_DMACA4_IS0                  *((volatile unsigned int*)(0x42C00A5CUL))
#define bFM0P_DMAC_DMACA4_IS1                  *((volatile unsigned int*)(0x42C00A60UL))
#define bFM0P_DMAC_DMACA4_IS2                  *((volatile unsigned int*)(0x42C00A64UL))
#define bFM0P_DMAC_DMACA4_IS3                  *((volatile unsigned int*)(0x42C00A68UL))
#define bFM0P_DMAC_DMACA4_IS4                  *((volatile unsigned int*)(0x42C00A6CUL))
#define bFM0P_DMAC_DMACA4_IS5                  *((volatile unsigned int*)(0x42C00A70UL))
#define bFM0P_DMAC_DMACA4_ST                   *((volatile unsigned int*)(0x42C00A74UL))
#define bFM0P_DMAC_DMACA4_PB                   *((volatile unsigned int*)(0x42C00A78UL))
#define bFM0P_DMAC_DMACA4_EB                   *((volatile unsigned int*)(0x42C00A7CUL))
#define bFM0P_DMAC_DMACB4_EM                   *((volatile unsigned int*)(0x42C00A80UL))
#define bFM0P_DMAC_DMACB4_SS0                  *((volatile unsigned int*)(0x42C00AC0UL))
#define bFM0P_DMAC_DMACB4_SS1                  *((volatile unsigned int*)(0x42C00AC4UL))
#define bFM0P_DMAC_DMACB4_SS2                  *((volatile unsigned int*)(0x42C00AC8UL))
#define bFM0P_DMAC_DMACB4_CI                   *((volatile unsigned int*)(0x42C00ACCUL))
#define bFM0P_DMAC_DMACB4_EI                   *((volatile unsigned int*)(0x42C00AD0UL))
#define bFM0P_DMAC_DMACB4_RD                   *((volatile unsigned int*)(0x42C00AD4UL))
#define bFM0P_DMAC_DMACB4_RS                   *((volatile unsigned int*)(0x42C00AD8UL))
#define bFM0P_DMAC_DMACB4_RC                   *((volatile unsigned int*)(0x42C00ADCUL))
#define bFM0P_DMAC_DMACB4_FD                   *((volatile unsigned int*)(0x42C00AE0UL))
#define bFM0P_DMAC_DMACB4_FS                   *((volatile unsigned int*)(0x42C00AE4UL))
#define bFM0P_DMAC_DMACB4_TW0                  *((volatile unsigned int*)(0x42C00AE8UL))
#define bFM0P_DMAC_DMACB4_TW1                  *((volatile unsigned int*)(0x42C00AECUL))
#define bFM0P_DMAC_DMACB4_MS0                  *((volatile unsigned int*)(0x42C00AF0UL))
#define bFM0P_DMAC_DMACB4_MS1                  *((volatile unsigned int*)(0x42C00AF4UL))
#define bFM0P_DMAC_DMACA5_TC0                  *((volatile unsigned int*)(0x42C00C00UL))
#define bFM0P_DMAC_DMACA5_TC1                  *((volatile unsigned int*)(0x42C00C04UL))
#define bFM0P_DMAC_DMACA5_TC2                  *((volatile unsigned int*)(0x42C00C08UL))
#define bFM0P_DMAC_DMACA5_TC3                  *((volatile unsigned int*)(0x42C00C0CUL))
#define bFM0P_DMAC_DMACA5_TC4                  *((volatile unsigned int*)(0x42C00C10UL))
#define bFM0P_DMAC_DMACA5_TC5                  *((volatile unsigned int*)(0x42C00C14UL))
#define bFM0P_DMAC_DMACA5_TC6                  *((volatile unsigned int*)(0x42C00C18UL))
#define bFM0P_DMAC_DMACA5_TC7                  *((volatile unsigned int*)(0x42C00C1CUL))
#define bFM0P_DMAC_DMACA5_TC8                  *((volatile unsigned int*)(0x42C00C20UL))
#define bFM0P_DMAC_DMACA5_TC9                  *((volatile unsigned int*)(0x42C00C24UL))
#define bFM0P_DMAC_DMACA5_TC10                 *((volatile unsigned int*)(0x42C00C28UL))
#define bFM0P_DMAC_DMACA5_TC11                 *((volatile unsigned int*)(0x42C00C2CUL))
#define bFM0P_DMAC_DMACA5_TC12                 *((volatile unsigned int*)(0x42C00C30UL))
#define bFM0P_DMAC_DMACA5_TC13                 *((volatile unsigned int*)(0x42C00C34UL))
#define bFM0P_DMAC_DMACA5_TC14                 *((volatile unsigned int*)(0x42C00C38UL))
#define bFM0P_DMAC_DMACA5_TC15                 *((volatile unsigned int*)(0x42C00C3CUL))
#define bFM0P_DMAC_DMACA5_BC0                  *((volatile unsigned int*)(0x42C00C40UL))
#define bFM0P_DMAC_DMACA5_BC1                  *((volatile unsigned int*)(0x42C00C44UL))
#define bFM0P_DMAC_DMACA5_BC2                  *((volatile unsigned int*)(0x42C00C48UL))
#define bFM0P_DMAC_DMACA5_BC3                  *((volatile unsigned int*)(0x42C00C4CUL))
#define bFM0P_DMAC_DMACA5_IS0                  *((volatile unsigned int*)(0x42C00C5CUL))
#define bFM0P_DMAC_DMACA5_IS1                  *((volatile unsigned int*)(0x42C00C60UL))
#define bFM0P_DMAC_DMACA5_IS2                  *((volatile unsigned int*)(0x42C00C64UL))
#define bFM0P_DMAC_DMACA5_IS3                  *((volatile unsigned int*)(0x42C00C68UL))
#define bFM0P_DMAC_DMACA5_IS4                  *((volatile unsigned int*)(0x42C00C6CUL))
#define bFM0P_DMAC_DMACA5_IS5                  *((volatile unsigned int*)(0x42C00C70UL))
#define bFM0P_DMAC_DMACA5_ST                   *((volatile unsigned int*)(0x42C00C74UL))
#define bFM0P_DMAC_DMACA5_PB                   *((volatile unsigned int*)(0x42C00C78UL))
#define bFM0P_DMAC_DMACA5_EB                   *((volatile unsigned int*)(0x42C00C7CUL))
#define bFM0P_DMAC_DMACB5_EM                   *((volatile unsigned int*)(0x42C00C80UL))
#define bFM0P_DMAC_DMACB5_SS0                  *((volatile unsigned int*)(0x42C00CC0UL))
#define bFM0P_DMAC_DMACB5_SS1                  *((volatile unsigned int*)(0x42C00CC4UL))
#define bFM0P_DMAC_DMACB5_SS2                  *((volatile unsigned int*)(0x42C00CC8UL))
#define bFM0P_DMAC_DMACB5_CI                   *((volatile unsigned int*)(0x42C00CCCUL))
#define bFM0P_DMAC_DMACB5_EI                   *((volatile unsigned int*)(0x42C00CD0UL))
#define bFM0P_DMAC_DMACB5_RD                   *((volatile unsigned int*)(0x42C00CD4UL))
#define bFM0P_DMAC_DMACB5_RS                   *((volatile unsigned int*)(0x42C00CD8UL))
#define bFM0P_DMAC_DMACB5_RC                   *((volatile unsigned int*)(0x42C00CDCUL))
#define bFM0P_DMAC_DMACB5_FD                   *((volatile unsigned int*)(0x42C00CE0UL))
#define bFM0P_DMAC_DMACB5_FS                   *((volatile unsigned int*)(0x42C00CE4UL))
#define bFM0P_DMAC_DMACB5_TW0                  *((volatile unsigned int*)(0x42C00CE8UL))
#define bFM0P_DMAC_DMACB5_TW1                  *((volatile unsigned int*)(0x42C00CECUL))
#define bFM0P_DMAC_DMACB5_MS0                  *((volatile unsigned int*)(0x42C00CF0UL))
#define bFM0P_DMAC_DMACB5_MS1                  *((volatile unsigned int*)(0x42C00CF4UL))
#define bFM0P_DMAC_DMACA6_TC0                  *((volatile unsigned int*)(0x42C00E00UL))
#define bFM0P_DMAC_DMACA6_TC1                  *((volatile unsigned int*)(0x42C00E04UL))
#define bFM0P_DMAC_DMACA6_TC2                  *((volatile unsigned int*)(0x42C00E08UL))
#define bFM0P_DMAC_DMACA6_TC3                  *((volatile unsigned int*)(0x42C00E0CUL))
#define bFM0P_DMAC_DMACA6_TC4                  *((volatile unsigned int*)(0x42C00E10UL))
#define bFM0P_DMAC_DMACA6_TC5                  *((volatile unsigned int*)(0x42C00E14UL))
#define bFM0P_DMAC_DMACA6_TC6                  *((volatile unsigned int*)(0x42C00E18UL))
#define bFM0P_DMAC_DMACA6_TC7                  *((volatile unsigned int*)(0x42C00E1CUL))
#define bFM0P_DMAC_DMACA6_TC8                  *((volatile unsigned int*)(0x42C00E20UL))
#define bFM0P_DMAC_DMACA6_TC9                  *((volatile unsigned int*)(0x42C00E24UL))
#define bFM0P_DMAC_DMACA6_TC10                 *((volatile unsigned int*)(0x42C00E28UL))
#define bFM0P_DMAC_DMACA6_TC11                 *((volatile unsigned int*)(0x42C00E2CUL))
#define bFM0P_DMAC_DMACA6_TC12                 *((volatile unsigned int*)(0x42C00E30UL))
#define bFM0P_DMAC_DMACA6_TC13                 *((volatile unsigned int*)(0x42C00E34UL))
#define bFM0P_DMAC_DMACA6_TC14                 *((volatile unsigned int*)(0x42C00E38UL))
#define bFM0P_DMAC_DMACA6_TC15                 *((volatile unsigned int*)(0x42C00E3CUL))
#define bFM0P_DMAC_DMACA6_BC0                  *((volatile unsigned int*)(0x42C00E40UL))
#define bFM0P_DMAC_DMACA6_BC1                  *((volatile unsigned int*)(0x42C00E44UL))
#define bFM0P_DMAC_DMACA6_BC2                  *((volatile unsigned int*)(0x42C00E48UL))
#define bFM0P_DMAC_DMACA6_BC3                  *((volatile unsigned int*)(0x42C00E4CUL))
#define bFM0P_DMAC_DMACA6_IS0                  *((volatile unsigned int*)(0x42C00E5CUL))
#define bFM0P_DMAC_DMACA6_IS1                  *((volatile unsigned int*)(0x42C00E60UL))
#define bFM0P_DMAC_DMACA6_IS2                  *((volatile unsigned int*)(0x42C00E64UL))
#define bFM0P_DMAC_DMACA6_IS3                  *((volatile unsigned int*)(0x42C00E68UL))
#define bFM0P_DMAC_DMACA6_IS4                  *((volatile unsigned int*)(0x42C00E6CUL))
#define bFM0P_DMAC_DMACA6_IS5                  *((volatile unsigned int*)(0x42C00E70UL))
#define bFM0P_DMAC_DMACA6_ST                   *((volatile unsigned int*)(0x42C00E74UL))
#define bFM0P_DMAC_DMACA6_PB                   *((volatile unsigned int*)(0x42C00E78UL))
#define bFM0P_DMAC_DMACA6_EB                   *((volatile unsigned int*)(0x42C00E7CUL))
#define bFM0P_DMAC_DMACB6_EM                   *((volatile unsigned int*)(0x42C00E80UL))
#define bFM0P_DMAC_DMACB6_SS0                  *((volatile unsigned int*)(0x42C00EC0UL))
#define bFM0P_DMAC_DMACB6_SS1                  *((volatile unsigned int*)(0x42C00EC4UL))
#define bFM0P_DMAC_DMACB6_SS2                  *((volatile unsigned int*)(0x42C00EC8UL))
#define bFM0P_DMAC_DMACB6_CI                   *((volatile unsigned int*)(0x42C00ECCUL))
#define bFM0P_DMAC_DMACB6_EI                   *((volatile unsigned int*)(0x42C00ED0UL))
#define bFM0P_DMAC_DMACB6_RD                   *((volatile unsigned int*)(0x42C00ED4UL))
#define bFM0P_DMAC_DMACB6_RS                   *((volatile unsigned int*)(0x42C00ED8UL))
#define bFM0P_DMAC_DMACB6_RC                   *((volatile unsigned int*)(0x42C00EDCUL))
#define bFM0P_DMAC_DMACB6_FD                   *((volatile unsigned int*)(0x42C00EE0UL))
#define bFM0P_DMAC_DMACB6_FS                   *((volatile unsigned int*)(0x42C00EE4UL))
#define bFM0P_DMAC_DMACB6_TW0                  *((volatile unsigned int*)(0x42C00EE8UL))
#define bFM0P_DMAC_DMACB6_TW1                  *((volatile unsigned int*)(0x42C00EECUL))
#define bFM0P_DMAC_DMACB6_MS0                  *((volatile unsigned int*)(0x42C00EF0UL))
#define bFM0P_DMAC_DMACB6_MS1                  *((volatile unsigned int*)(0x42C00EF4UL))
#define bFM0P_DMAC_DMACA7_TC0                  *((volatile unsigned int*)(0x42C01000UL))
#define bFM0P_DMAC_DMACA7_TC1                  *((volatile unsigned int*)(0x42C01004UL))
#define bFM0P_DMAC_DMACA7_TC2                  *((volatile unsigned int*)(0x42C01008UL))
#define bFM0P_DMAC_DMACA7_TC3                  *((volatile unsigned int*)(0x42C0100CUL))
#define bFM0P_DMAC_DMACA7_TC4                  *((volatile unsigned int*)(0x42C01010UL))
#define bFM0P_DMAC_DMACA7_TC5                  *((volatile unsigned int*)(0x42C01014UL))
#define bFM0P_DMAC_DMACA7_TC6                  *((volatile unsigned int*)(0x42C01018UL))
#define bFM0P_DMAC_DMACA7_TC7                  *((volatile unsigned int*)(0x42C0101CUL))
#define bFM0P_DMAC_DMACA7_TC8                  *((volatile unsigned int*)(0x42C01020UL))
#define bFM0P_DMAC_DMACA7_TC9                  *((volatile unsigned int*)(0x42C01024UL))
#define bFM0P_DMAC_DMACA7_TC10                 *((volatile unsigned int*)(0x42C01028UL))
#define bFM0P_DMAC_DMACA7_TC11                 *((volatile unsigned int*)(0x42C0102CUL))
#define bFM0P_DMAC_DMACA7_TC12                 *((volatile unsigned int*)(0x42C01030UL))
#define bFM0P_DMAC_DMACA7_TC13                 *((volatile unsigned int*)(0x42C01034UL))
#define bFM0P_DMAC_DMACA7_TC14                 *((volatile unsigned int*)(0x42C01038UL))
#define bFM0P_DMAC_DMACA7_TC15                 *((volatile unsigned int*)(0x42C0103CUL))
#define bFM0P_DMAC_DMACA7_BC0                  *((volatile unsigned int*)(0x42C01040UL))
#define bFM0P_DMAC_DMACA7_BC1                  *((volatile unsigned int*)(0x42C01044UL))
#define bFM0P_DMAC_DMACA7_BC2                  *((volatile unsigned int*)(0x42C01048UL))
#define bFM0P_DMAC_DMACA7_BC3                  *((volatile unsigned int*)(0x42C0104CUL))
#define bFM0P_DMAC_DMACA7_IS0                  *((volatile unsigned int*)(0x42C0105CUL))
#define bFM0P_DMAC_DMACA7_IS1                  *((volatile unsigned int*)(0x42C01060UL))
#define bFM0P_DMAC_DMACA7_IS2                  *((volatile unsigned int*)(0x42C01064UL))
#define bFM0P_DMAC_DMACA7_IS3                  *((volatile unsigned int*)(0x42C01068UL))
#define bFM0P_DMAC_DMACA7_IS4                  *((volatile unsigned int*)(0x42C0106CUL))
#define bFM0P_DMAC_DMACA7_IS5                  *((volatile unsigned int*)(0x42C01070UL))
#define bFM0P_DMAC_DMACA7_ST                   *((volatile unsigned int*)(0x42C01074UL))
#define bFM0P_DMAC_DMACA7_PB                   *((volatile unsigned int*)(0x42C01078UL))
#define bFM0P_DMAC_DMACA7_EB                   *((volatile unsigned int*)(0x42C0107CUL))
#define bFM0P_DMAC_DMACB7_EM                   *((volatile unsigned int*)(0x42C01080UL))
#define bFM0P_DMAC_DMACB7_SS0                  *((volatile unsigned int*)(0x42C010C0UL))
#define bFM0P_DMAC_DMACB7_SS1                  *((volatile unsigned int*)(0x42C010C4UL))
#define bFM0P_DMAC_DMACB7_SS2                  *((volatile unsigned int*)(0x42C010C8UL))
#define bFM0P_DMAC_DMACB7_CI                   *((volatile unsigned int*)(0x42C010CCUL))
#define bFM0P_DMAC_DMACB7_EI                   *((volatile unsigned int*)(0x42C010D0UL))
#define bFM0P_DMAC_DMACB7_RD                   *((volatile unsigned int*)(0x42C010D4UL))
#define bFM0P_DMAC_DMACB7_RS                   *((volatile unsigned int*)(0x42C010D8UL))
#define bFM0P_DMAC_DMACB7_RC                   *((volatile unsigned int*)(0x42C010DCUL))
#define bFM0P_DMAC_DMACB7_FD                   *((volatile unsigned int*)(0x42C010E0UL))
#define bFM0P_DMAC_DMACB7_FS                   *((volatile unsigned int*)(0x42C010E4UL))
#define bFM0P_DMAC_DMACB7_TW0                  *((volatile unsigned int*)(0x42C010E8UL))
#define bFM0P_DMAC_DMACB7_TW1                  *((volatile unsigned int*)(0x42C010ECUL))
#define bFM0P_DMAC_DMACB7_MS0                  *((volatile unsigned int*)(0x42C010F0UL))
#define bFM0P_DMAC_DMACB7_MS1                  *((volatile unsigned int*)(0x42C010F4UL))

#ifdef __cplusplus
}
#endif

#endif /* _S6E1A1_H_ */
