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
/** \file InitMcu.c
 **
 ** Add description here...
 **
 ** History:
 **   - 2013-09-20  0.1.0  Michael.Yang  First version 
 *****************************************************************************/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "InitMcu.h"
#include "system_s6e1a1.h"
#include "s6e1a1.h"
#include "base_types.h"
#include "Isr.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define HWD_CTL_INTEN     (0x01u)
#define HWD_CTL_RESEN     (0x02u)

#define SWD_CTL_INTEN     (0x01u)
#define SWD_CTL_RESEN     (0x02u)

#define PSW_TMR_VAL       (0x05u)

#define CLK_XTAL_FREQ                 4             // MHz   
#define CLK_SYS_FREQMULTI             9             // System clock frequency multiplication constant

#define BASE_CLK_DIV         0     //
#define APB0_CLK_DIV         0     // 
#define APB1_CLK_DIV         0     //

#define HWWDG_REG_UNLOCK_1  (0x1ACCE551u)
#define HWWDG_REG_UNLOCK_2  (0xE5331AAEu)
#define SWWDG_REG_UNLOCK    (0x1ACCE551u)

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
_stClkPara gstClkPara;

extern INT8U SystemTimeCnt;
extern INT8U  F_4Ms;
/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


/****************************************************
 Function name:    InitMcu_Nvic
 description:
 input:
 output:            none
 ****************************************************/
void InitMcu_Nvic(void)
{
 //exception priority

    NVIC_SetPriority(WFG_DTIF_IRQn,0);
    NVIC_SetPriority(SWDT_IRQn,0);
    NVIC_SetPriority(ADC0_IRQn,1);
    NVIC_SetPriority(MFS0RX_IRQn,1);
    NVIC_SetPriority(FRTIM_IRQn,2);
    NVIC_SetPriority(BTIM0_3_FLASH_IRQn,3);
    NVIC_SetPriority(MFS0TX_IRQn,3);      


 // interrupt or exception enbale

    NVIC_EnableIRQ(WFG_DTIF_IRQn);
    NVIC_EnableIRQ(SWDT_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(FRTIM_IRQn);
    NVIC_EnableIRQ(BTIM0_3_FLASH_IRQn);
    NVIC_EnableIRQ(MFS0RX_IRQn);
    NVIC_EnableIRQ(MFS0TX_IRQn);
}

void InitMcu_Clock(void)
{  
  //FM0P_CRG->SCM_CTL &= 0x1F;
#if(0)
   /*Bus clock freq setting*/
  //FM0P_CRG->SCM_CTL_f.PLLE = 0;
  
    FM0P_CRG->BSC_PSR = BASE_CLK_DIV;
    FM0P_CRG->APBC0_PSR = APB0_CLK_DIV;
    FM0P_CRG->APBC1_PSR = APB1_CLK_DIV;
     /*** Main Pll clock division setting*********/
        FM0P_CRG->PLL_CTL1 &= 0x0f;                 
    FM0P_CRG->PLL_CTL1 |= 0x00;                 //PLL input freq division setting, 0 divison
        FM0P_CRG->PLL_CTL1 &= 0xf0;                 
    FM0P_CRG->PLL_CTL1 |= 0x00;                 //PLL Voc freq division setting, 0 divison    
        FM0P_CRG->PLL_CTL2 &= 0x00;
    FM0P_CRG->PLL_CTL2 = CLK_SYS_FREQMULTI;     // PLL feedback fre division setting, CLK_SYS_FREQMULTI division
    /*stablization time setting*/
    FM0P_CRG->PSW_TMR = PSW_TMR_VAL;   //Pll stabization
    FM0P_CRG->SCM_CTL_f.PLLE = 1;
    while (FM0P_CRG->SCM_STR_f.PLRDY == 0)
      ; 
    
    //FM0P_CRG->SCM_CTL &= 0x1F;
    FM0P_CRG->SCM_CTL |= 0x40;                   //select mainPLL clock as master clock, disable all oscillation
 

    //softwathc dog clock set as default = APB0

 /**select clock mode***/

#endif

   
    gstClkPara.FreqOfPLL_Hz = CLK_XTAL_FREQ * 1000000L * (CLK_SYS_FREQMULTI + 1);
    gstClkPara.FreqOfBaseClk_Hz = gstClkPara.FreqOfPLL_Hz / (BASE_CLK_DIV + 1);
    gstClkPara.FreqOfAPB0Clk_Hz = gstClkPara.FreqOfPLL_Hz / (APB0_CLK_DIV + 1);
    gstClkPara.FreqOfAPB1Clk_Hz = gstClkPara.FreqOfPLL_Hz / (APB1_CLK_DIV + 1);
    
}


/****************************************************
 Function name:    InitMcu_Wdg
 description:
 input:
 output:            none
 ****************************************************/
void InitMcu_Wdg(void)
{
    // HWDT
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_1;
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_2;                  // unlock procesessing
    
    FM0P_HWWDT->WDG_CTL = HWD_CTL_RESEN;                       // reset enable
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_1;
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_2;
    
    FM0P_HWWDT->WDG_CTL = HWD_CTL_INTEN;                       // interrupt enable
    
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_1;
    FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_2;
    FM0P_HWWDT->WDG_LDR = 60;                                    //30 * 10us
    
    FM0P_CRG->DBWDT_CTL_f.DPHWBE = 1;                 // continue counting when tool break


    // SWDT
        FM0P_SWWDT->WDOGLOCK = SWWDG_REG_UNLOCK;                 //unlock
    FM0P_SWWDT->WDOGLOAD = 5000000;                             // 200ns * 5000000 =1s
    FM0P_SWWDT->WDOGCONTROL = SWD_CTL_RESEN;                   //SWD reset enable
    FM0P_SWWDT->WDOGCONTROL = SWD_CTL_INTEN;                   //SWD int enable, =0 to stop SWD
    
    FM0P_SWWDT->WDOGLOCK = 0;                                    //lock                 
}

void InitMcu_Gpio(void)
{    
    FM0P_GPIO->PFR4_f.P49 = 1;                // act as peripheral function
    FM0P_GPIO->DDR4_f.P49 = 0;                    // input pin
    FM0P_GPIO->PDIR4_f.P49 = 0;
    FM0P_GPIO->EPFR04_f.TIOB0S = 0;
    FM0P_GPIO->EPFR04_f.TIOB1S = 0;
    FM0P_GPIO->EPFR04_f.TIOB2S = 0;              // use as input pin of BT TIOBO_O

    FM0P_GPIO->PFR6_f.P60 = 1;                // act as peripheral function
    FM0P_GPIO->DDR6_f.P60 = 1;                  
    FM0P_GPIO->PDOR6_f.P60 = 0;
    FM0P_GPIO->EPFR04_f.TIOA2E = 3;
}


void InitMcu_CompTimerRun(void)
{ 
    FM0P_MFT0_FRT->TCSA0_f.STOP = 0;            //put FRT0 in runing state   
}
void InitMcu_CompPwmEn(void)
{
    FM0P_GPIO->PFR3 |= 0x3C00;                // configure  PDOR3.A~D act WFG
}

void InitMcu_CompPwmDis(void)
{
    FM0P_GPIO->PFR3 &= 0xC3FF;                 // configure  PDOR3.A~D act as GPIO
}



void InitMcu_CompPwm(void)
{
    FM0P_MFT0_FRT->TCSA0_f.STOP = 1;          //stop FRT0
    FM0P_MFT0_FRT->TCSA0_f.SCLR = 1;          //clear TDCT
    
    FM0P_MFT0_FRT->TCSA0_f.BFE = 1;           //enable TCCP buffer 
    FM0P_MFT0_FRT->TCSA0_f.ECKE = 0;          //PCLK as FRT as count clock
    FM0P_MFT0_FRT->TCSA0_f.MODE = 1;          //up/down count mode
    
    FM0P_MFT0_WFG->NZCL_f.DIMA = 1;           //mask DTIF interrupt    
    FM0P_MFT0_FRT->TCSA0_f.ICRE = 0;          //mask peak interrupt
    FM0P_MFT0_FRT->TCSA0_f.ICLR = 0;    
    FM0P_MFT0_FRT->TCSA0_f.IRQZE = 0;         //mask zero interrput
    FM0P_MFT0_FRT->TCSA0_f.IRQZF = 0;
    

    
    FM0P_GPIO->PDOR3 &= 0xC3ff;               //Configure PDOR3A~D output 0
    FM0P_GPIO->DDR3 |= 0x3C00;                // P3A~D as output mode
    FM0P_GPIO->PFR3 &= 0xC3FF;                // P3A~D as GPIO 
    //OCU setting
    
    FM0P_MFT0_OCU->OCSA10_f.CST0 = 0;
    FM0P_MFT0_OCU->OCSA10_f.CST1 = 0;
    FM0P_MFT0_OCU->OCSA32_f.CST0 = 0;
    FM0P_MFT0_OCU->OCSA32_f.CST1 = 0;  //enable OCU channel 1,3   
             
    
    FM0P_MFT0_OCU->OCFS10 = 0;
    FM0P_MFT0_OCU->OCFS32 = 0;              //connect FRT0 -> OCU
    
    
    
    FM0P_MFT0_OCU->OCSB10_f.OTD1 = 0;
    FM0P_MFT0_OCU->OCSB32_f.OTD1 = 0;         //RT(1,3,5) output lowlevel when CST1 = 0
    
    FM0P_MFT0_OCU->OCSA10_f.IOE1 = 0;
    FM0P_MFT0_OCU->OCSA32_f.IOE1 = 0;          //disable OCU-FRT match detection interrupt
    FM0P_MFT0_OCU->OCSA10_f.IOP1 = 0;
    FM0P_MFT0_OCU->OCSA32_f.IOP1 = 0;           //clear interrupt flag
    

    FM0P_MFT0_OCU->OCSB10_f.FM4 = 1;
    FM0P_MFT0_OCU->OCSB32_f.FM4 = 1;
    
    FM0P_MFT0_OCU->OCSE1 = 0x55A498A0;
    FM0P_MFT0_OCU->OCSE3 = 0x55A498A0;
       
    
    FM0P_MFT0_OCU->OCSB10_f.CMOD = 0;
    FM0P_MFT0_OCU->OCSB32_f.CMOD = 0;    
    FM0P_MFT0_OCU->OCSC_f.MOD1 = 1;
    FM0P_MFT0_OCU->OCSC_f.MOD3 = 1;              // set up/down count mode with active high
    
    FM0P_MFT0_OCU->OCCP0 = st_CompCtrlPwm.i16Cycle;//up
    FM0P_MFT0_OCU->OCCP1 = st_CompCtrlPwm.i16Cycle;//down
    FM0P_MFT0_OCU->OCCP2 = st_CompCtrlPwm.i16Cycle;
    FM0P_MFT0_OCU->OCCP3 = st_CompCtrlPwm.i16Cycle;
    
    FM0P_MFT0_OCU->OCSD10_f.OCCP1BUFE = 1;    
    FM0P_MFT0_OCU->OCSD32_f.OCCP1BUFE = 1;      //enable buffer mode, zero  transfer
    FM0P_MFT0_OCU->OCSD10_f.OCCP0BUFE = 1;    
    FM0P_MFT0_OCU->OCSD32_f.OCCP0BUFE = 1;    //enable buffer mode, zero transfer
    
       
    FM0P_MFT0_OCU->OCSA10_f.CST1 = 1;
    FM0P_MFT0_OCU->OCSA32_f.CST1 = 1;          //enable OCU operation
    
    //WFG setting  
    FM0P_MFT0_WFG->WFSA10 &= 0xFFC7;
    FM0P_MFT0_WFG->WFSA32 &= 0xFFC7;              
    FM0P_MFT0_WFG->WFSA10 |= 0x0020;
    FM0P_MFT0_WFG->WFSA32 |= 0x0020;            //dead-timer mode

    FM0P_MFT0_WFG->WFSA10 &= 0xCFFF;
    FM0P_MFT0_WFG->WFSA32 &= 0xCFFF;             //clear DMOD
    FM0P_MFT0_WFG->WFSA10 |= 0x0000;
    FM0P_MFT0_WFG->WFSA32 |= 0x0000;           //RTO(0) and RTO(1) outputwithout changing level
    
    
    FM0P_MFT0_WFG->WFSA10 &= 0xFFF8;
    FM0P_MFT0_WFG->WFSA32 &= 0xFFF8;              //clear DCK
    FM0P_MFT0_WFG->WFSA10 |= 0x0000;
    FM0P_MFT0_WFG->WFSA32 |= 0x0000;             //clock same as PCLK
    
    FM0P_GPIO->EPFR01 &= 0xffffff00;
    FM0P_GPIO->EPFR01 |= 0x00000055;          //use RTO0~3_0 as the output pin of WFG

    
    FM0P_GPIO->PFR3_f.P39 = 1;                // act as peripheral function
    FM0P_GPIO->DDR3_f.P39 = 0;                // output pin
    FM0P_GPIO->EPFR01_f.DTTI0S = 0;            //Use DTTI0X_0 as input pin of DTTI signal
    FM0P_GPIO->EPFR01_f.DTTI0C = 1;           //Switches GPIO by DTTIF0 for output of pins RTO00 to RTO05.
    

    
    FM0P_MFT0_WFG->NZCL &= 0xFFF1; 
    FM0P_MFT0_WFG->NZCL |= 0x0008;             //nws = 4, 32PCLK cyclesw
    FM0P_MFT0_WFG->NZCL_f.DTIEA = 1;           //enable path for digital noise filter 
    FM0P_MFT0_WFG->WFIR_f.DTICA = 1;           //clear DTIFA
    
    FM0P_MFT0_WFG->NZCL_f.DIMA = 0;            //enable DTIF interrupt
    

    //FM0P_MFT0_FRT->TCSA0_f.ICRE = 1;          //enable peak interrupt
    //FM0P_MFT0_FRT->TCSA0_f.ICLR = 0;  

  
    FM0P_MFT0_FRT->TCSA0_f.IRQZE = 1;         //enable zero interrput
    FM0P_MFT0_FRT->TCSA0_f.IRQZF = 0;
}

/****************************************************
 Function name:      Sensor_Init
 description:
 input:                  none
 output:             none
 ****************************************************/
void InitMcu_Adc(INT16U u16SampleFreq)
{	
	
    FM0P_GPIO->ADE = 0x00000000;

    /***************Set Correspond pin to analog input***********/

    FM0P_GPIO->ADE |= (0x0001 << COMP_ADC_CH_IU);
    FM0P_GPIO->ADE |= (0x0001 << COMP_ADC_CH_IV);
    FM0P_GPIO->ADE |= (0x0001 << PFC_ADC_CH_VDC);

    FM0P_GPIO->ADE |= (0x0001 << COMP_VSPD);
    FM0P_GPIO->ADE |= (0x0001 << BOARD_TEMP);
    FM0P_GPIO->ADE |= (0x0001 << COMP_SPD);
    
    /***************Assign analog input channel to ADC unit8******/
    FM0P_ADC0->SCIS0 = 0;
    FM0P_ADC0->SCIS1 = 0;
    
    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << COMP_ADC_CH_IU);
    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << COMP_ADC_CH_IV);
    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << PFC_ADC_CH_VDC);

    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << COMP_VSPD);
    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << BOARD_TEMP);
    FM0P_ADC0->SCIS0 |= (uint8_t)(1 << COMP_SPD);
    /****************Configure ADC FIFO stage*******************/

    
    //FM0P_ADC0->SFNS = ADC_SCAN_CONV_STAGE3 - 1;
    FM0P_ADC0->SFNS = ADC_SCAN_CONV_STAGE6 - 1;

    /******************* Config ADC Conversition Times ********************/
    /* Sample time = Base clock(HCLK)cycle * {(ST +1) * STX + 1}          */
    /* Comparison time = Base clock(HCLK)cycle *Compare clock frequency   */
    /*                   division ratio * 14                                  */
	//FM0P_ADC0->ADCT = 0x80;
    FM0P_ADC0->ADCT = 0x02;                    //comparision time 25ns * 4 *14 = 1400ns
    FM0P_ADC0->ADST0 &= 0xE0;
    //FM0P_ADC0->ADST0 |= ADC_ST_VALUE2;
    FM0P_ADC0->ADST0 |= ADC_ST_VALUE1;
    FM0P_ADC0->ADST0 |= (ADC_STX_VALUE0 << 5); //sampling time: 25ns * 4*((2 + 1)*1 + 3) = 600ns
    
    uint32_t ADC_ST;
    ADC_ST = ADC_ST0;
    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << COMP_ADC_CH_IU); 
    
    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << COMP_ADC_CH_IV);
    
    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << PFC_ADC_CH_VDC); 

    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << COMP_VSPD); 
    
    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << BOARD_TEMP); 

    FM0P_ADC0->ADSS0 |= (uint8_t)(ADC_ST << COMP_SPD); 
    /***************Config ADC triggered soure*******************/

    FM0P_ADC0->SCCR_f.SHEN = 1;                //enable timer activation
    FM0P_ADC0->SCTSL = 1;                      // activated by MFT

    FM0P_MFT0_ADCMP->ACFS32 = 0x00;           // connect FRT0 to ADCMP2,ADCMP3
    FM0P_MFT0_ADCMP->ACSA &= 0xFFF3;          //disable compatibility with FM3
    
    FM0P_MFT0_ADCMP->ACSC2 = 0x01;            //output ADC start trigger 0. buffer enable, tranfer buffer when frt = 0x0000;
  
    FM0P_MFT0_ADCMP->ACSD2_f.AMOD = 0;        //normal mode        
    
    FM0P_MFT0_ADCMP->ACSD2_f.UE = 1;     //enable ADCMP operation
    FM0P_MFT0_ADCMP->ACSD2_f.ZE = 1;     //enable ADCMP operation
    
    FM0P_ADC0->ADCR_f.SCIE = 1;          //enable interrupt
    FM0P_ADC0->SCCR_f.SFCLR = 1;         //clear FIFO
//enable ADC
    FM0P_ADC0->ADCEN = 0x2700;           //state transition time to 1us
    FM0P_ADC0->ADCEN_f.ENBL = 1;         //enable ADC operation
    while(FM0P_ADC0->ADCEN_f.READY == 0)
      ;
    
}

void InitMcu_Basetimer(void)
{    
    /********************Hall转速采集********************/
      //timer stop.
    FM0P_BT0_PWC->TMCR_f.CTEN = 0;
    //PWC mode
    FM0P_BT0_PWC->TMCR_f.FMD = 0x4;
    //continous mode. 0: continous, 1: one-shot
    FM0P_BT0_PWC->TMCR_f.MDSE = 0;
    //set clock and start-end edge
    FM0P_BT0_PWC->TMCR &= 0x00FF;
    FM0P_BT0_PWC->TMCR |= 0x2300;// 2:0010 Clock * 16, 25ns * 16 = 0.4us,  011:between all edges.
    //FM0P_BT0_PWC->TMCR |= 0x2200;// 2:0010 Clock * 16, 25ns * 16 = 0.4us,  falling start and falling end.
    //enable interrupt.
    //enable interrupt
    FM0P_BT0_PWC->STC_f.OVIE = 1; //enable overflow interrupt
    FM0P_BT0_PWC->STC_f.EDIE = 1; //enable measure interrupt
    //timer start.
    FM0P_BT0_PWC->TMCR_f.CTEN = 1;  

    
    /********************即时转速反馈输出********************/
   FM0P_BT2_PWM->TMCR = 0x2010;//CKS3-CKS0:1010 -> CLK/2048,trigger input disable; pwm mode
    FM0P_BT2_PWM->TMCR2 = 0x01;
	//FM0P_BT2_PWM->TMCR = 0x2010;//CKS3-CKS0:0010 -> CLK/16,trigger input disable; pwm mode
    //FM0P_BT2_PWM->TMCR2 = 0;
    FM0P_BT2_PWM->STC = 0;
    FM0P_BT2_PWM->PCSR = 78; //
    FM0P_BT2_PWM->PDUT = 39;
    //FM0P_BT2_PWM->TMCR|= 0x03;      //software trigger and count start 
    
    /********************时基定时器********************/
    st_TimerPara.SystemTimeCnt=0;
    st_TimerPara.F_4Ms=0; 

    FM0P_BT1_RT->TMCR = 0x2030;//CKS3-CKS0:1010 -> CLK/2048,trigger input disable
    FM0P_BT1_RT->TMCR2 = 0x01;

    FM0P_BT1_RT->STC = 0x10;        //Enable underflow interrupt,Clear interupt cause
    FM0P_BT1_RT->PCSR = 78;
    FM0P_BT1_RT->TMR = 78;
    FM0P_BT1_RT->TMCR|= 0x03;      //software trigger and count start 
    /********************end by fu********************/
}

 /******************************************************************************
 ** \brief Feed Software Watchdog (Call function)
 **
 ** This function feeds the Software Watchdog with the unlock, feed, and lock
 ** sequence.
 **
 ******************************************************************************/
void Swwdg_Feed(void)
{
    FM0P_SWWDT->WDOGLOCK   = SWWDG_REG_UNLOCK;   /* Release Lock */
    FM0P_SWWDT->WDOGINTCLR = 1;                  /* Clear possible interrupt and reload value */
    FM0P_SWWDT->WDOGLOCK   = 0;                  /* Lock again it! */
} /* Swwdg_Feed */
 /**
  ******************************************************************************
  ** \brief Feed Hardware Watchdog (Call function)
  **
  ** This function feeds the Hardware Watchdog with the unlock, feed, and lock
  ** sequence. Take care of the arbitrary values, because there are not checked
  ** for plausibility!
  **
  ** \param [in] u8ClearPattern1   Pattern of arbitrary value
  ** \param [in] u8ClearPattern2   Inverted arbitrary value
  **
  ******************************************************************************/
 void Hwwdg_Feed(uint8_t u8ClearPattern1, uint8_t u8ClearPattern2)
 {
     FM0P_HWWDT->WDG_LCK = HWWDG_REG_UNLOCK_1;    /* Release Lock */
     FM0P_HWWDT->WDG_ICL = u8ClearPattern1;       /* Clear possible interrupt and reload value, step 1 */
     FM0P_HWWDT->WDG_ICL = u8ClearPattern2;       /* Clear possible interrupt and reload value, step 2 */
 } /* Hwwdg_Feed */


