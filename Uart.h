
/******************************************************************************/
/** \file uart.h
 **
 ** Add description here...
 **
 ** History:
 **   
 *****************************************************************************/

#ifndef UART_H
#define UART_H

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
#define SET_COMMAND_WORD_NUM    3
#define STATUS_WORD_NUM         7
#define MAX_READ_REGISTER_NUM   STATUS_WORD_NUM
#define MAX_WRITE_REGISTER_NUM   7                              //最大同时写的寄存器数量
#define MAX_DEF_RX_BYTE         (8 + MAX_WRITE_REGISTER_NUM * 2)        //接收最大字节取决于最大写的字节数
#define MAX_DEF_TX_BYTE         MAX_DEF_RX_BYTE   
                      
#define TX_DELAY_TIME           20

typedef union
{
	INT16U SetDataArray[SET_COMMAND_WORD_NUM];
	struct 
	{	        
		INT16U   CommandA;        		
		INT16U   ErrorClearCommand;
		INT16U   Power; 
	}Data;	
} SetCommandUnion;
extern SetCommandUnion   SetCommand;


typedef union
{
	INT16U ReadDataArray[STATUS_WORD_NUM];
	struct 
	{	        
		INT16U   CompressorStatus;              //
		INT16U   AlarmCode;   
		INT16U   CompressorSpeed;                      
		INT16U   CompPower;
		INT16S   BoardTemp;		
		INT16S   CurrentConsumption;
		INT16U   SoftwareVersion;
	}Data;
}RuningStatusUnion; 

extern RuningStatusUnion RunParameter;

typedef struct
{
    INT8U  TxDelayTime;
    INT8U  DelayTxFlag;
    INT8U  TxCount;
    INT8U  MaxTxNumber;
    INT8U  TxDataBuff[MAX_DEF_RX_BYTE];
}stc_uart_tx;

extern stc_uart_tx st_UartTx;

typedef struct
{   
    INT8U  RxCount; 
    INT8U  MaxRxNumber;
    INT8U  MaxFrameRxTime; 
    INT8U  OneFrameRecFlag;
    INT8U  CrcCheckFlag;                           //  0crc校验，1累加和校验
    INT8U  RxDataBuff[MAX_DEF_RX_BYTE];
}stc_uart_rec;

extern stc_uart_rec st_UartRec;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
extern void InitUart3(void);
extern void ReadyUartTx(void);

extern void UartFrameRec(void);
extern void ISR_UART0_Receive(void);
extern void ISR_UART0_Transmit(void);
extern void  DecodeUartRx(void);



#endif 

