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

;/************************************************************************/
;/*  Startup for IAR                                                     */
;/*  Version     V1.0                                                   */
;/*  Date        2013-12-17                                              */
;/*  Target-mcu  S6E1A1                                                  */
;/************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)               ; Top of Stack
		DCD     Reset_Handler             ; Reset
                DCD     HWD_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

                DCD     CSV_IRQHandler            ; 0: Clock Super Visor
                DCD     SWDT_IRQHandler           ; 1: Software Watchdog Timer
                DCD     LVD_IRQHandler            ; 2: Low Voltage Detector
                DCD     MFT_WFG_DTIF_IRQHandler   ; 3: Wave Form Generator / DTIF
                DCD     EXINT0_7_IRQHandler       ; 4: External Interrupt Request ch.0 to ch.7
                DCD     DummyIRQHandler           ; 5: Reserved
                DCD     DT_QDU_IRQHandler         ; 6: Dual Timer / Quad Decoder
                DCD     MFS0_RX_IRQHandler        ; 7: MultiFunction Serial ch.0
                DCD     MFS0_TX_IRQHandler        ; 8: MultiFunction Serial ch.0
                DCD     MFS1_RX_IRQHandler        ; 9: MultiFunction Serial ch.1
                DCD     MFS1_TX_IRQHandler        ; 10: MultiFunction Serial ch.1
                DCD     DummyIRQHandler           ; 11: Reserved
                DCD     DummyIRQHandler           ; 12: Reserved
                DCD     MFS3_RX_IRQHandler        ; 13: MultiFunction Serial ch.3
                DCD     MFS3_TX_IRQHandler        ; 14: MultiFunction Serial ch.3
                DCD     DummyIRQHandler           ; 15: Reserved
                DCD     DummyIRQHandler           ; 16: Reserved
                DCD     DummyIRQHandler           ; 17: Reserved
                DCD     DummyIRQHandler           ; 18: Reserved
                DCD     DMAC0_IRQHandler          ; 19: DMAC ch.0
                DCD     DMAC1_IRQHandler          ; 20: DMAC ch.1
                DCD     DummyIRQHandler           ; 21: Reserved
                DCD     DummyIRQHandler           ; 22: Reserved
                DCD     PPG_IRQHandler            ; 23: PPG
                DCD     TIM_IRQHandler            ; 24: OSC / PLL / Watch Counter / RTC
                DCD     ADC0_IRQHandler           ; 25: ADC0
                DCD     DummyIRQHandler           ; 26: Reserved
                DCD     DummyIRQHandler           ; 27: Reserved
                DCD     MFT_FRT_IRQHandler        ; 28: Free-run Timer
                DCD     MFT_IPC_IRQHandler        ; 29: Input Capture
                DCD     MFT_OPC_IRQHandler        ; 30: Output Compare
                DCD     BT0_3_IRQHandler   		  ; 31: Base Timer ch.0 to ch.3 / Flash

                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK HWD_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HWD_Handler
                B       HWD_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler



                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                
                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK CSV_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
CSV_IRQHandler
                B       CSV_IRQHandler

                PUBWEAK SWDT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SWDT_IRQHandler
                B       SWDT_IRQHandler

                PUBWEAK LVD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
                B       LVD_IRQHandler

                PUBWEAK MFT_WFG_DTIF_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFT_WFG_DTIF_IRQHandler
                B       MFT_WFG_DTIF_IRQHandler

                PUBWEAK EXINT0_7_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
EXINT0_7_IRQHandler
                B       EXINT0_7_IRQHandler
                
                PUBWEAK DT_QDU_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DT_QDU_IRQHandler
                B       DT_QDU_IRQHandler

                PUBWEAK MFS0_RX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS0_RX_IRQHandler
                B       MFS0_RX_IRQHandler

                PUBWEAK MFS0_TX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS0_TX_IRQHandler
                B       MFS0_TX_IRQHandler

                PUBWEAK MFS1_RX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS1_RX_IRQHandler
                B       MFS1_RX_IRQHandler

                PUBWEAK MFS1_TX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS1_TX_IRQHandler
                B       MFS1_TX_IRQHandler

                PUBWEAK MFS3_RX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS3_RX_IRQHandler
                B       MFS3_RX_IRQHandler

                PUBWEAK MFS3_TX_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFS3_TX_IRQHandler
                B       MFS3_TX_IRQHandler

                PUBWEAK DMAC0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMAC0_IRQHandler
                B       DMAC0_IRQHandler

                PUBWEAK DMAC1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMAC1_IRQHandler
                B       DMAC1_IRQHandler

                PUBWEAK PPG_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PPG_IRQHandler
                B       PPG_IRQHandler

                PUBWEAK TIM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM_IRQHandler
                B       TIM_IRQHandler

                PUBWEAK ADC0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_IRQHandler
                B       ADC0_IRQHandler

                PUBWEAK MFT_FRT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFT_FRT_IRQHandler
                B       MFT_FRT_IRQHandler
                
                PUBWEAK MFT_IPC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFT_IPC_IRQHandler
                B       MFT_IPC_IRQHandler

                PUBWEAK MFT_OPC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
MFT_OPC_IRQHandler
                B       MFT_OPC_IRQHandler

                PUBWEAK BT0_3_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
BT0_3_IRQHandler
                B       BT0_3_IRQHandler

                PUBWEAK DummyIRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DummyIRQHandler
                B       DummyIRQHandler

                END
