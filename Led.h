
/******************************************************************************/
/** \file led.h
 **
 ** Add description here...
 **
 ** History:
 **   
 *****************************************************************************/

#ifndef LED_H
#define LED_H

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
#define         SwitchOnLed1()          do{FM0P_GPIO->PDOR6_f.P61 = 0;}while(0)
#define         SwitchOffLed1()         do{FM0P_GPIO->PDOR6_f.P61 = 1;}while(0) 

typedef struct
{   
    INT8U  F_NormalFlashOn;     
    
    INT8U  DispTenTime;
    INT8U  DispUnitTime;
    INT8U  DispPeriodSecond;               //ÖÜÆÚ    

}Led_Para;
extern Led_Para st_LedPara;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
extern void InitLedPort(void);

extern void LedDisp(void);


#endif 

