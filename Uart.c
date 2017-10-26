/******************************************************************************/
/** \file UART.c
 **
 ** Add description here...
 **
 ** History:
 **   
 *****************************************************************************/
#include "InitMcu.h"
#include "system_s6e1a1.h"
#include "s6e1a1.h"
#include "base_types.h"
#include "Isr.h"
#include "Uart.h"
#include "Eeprom.h"

SetCommandUnion   SetCommand;
RuningStatusUnion RunParameter;

/*************************************************/

stc_uart_rec st_UartRec;

stc_uart_tx st_UartTx;

//----Modbus有关
#define MODBUS_ADDRESS                  0x55
#define MODBUS_READ                     0x03
#define MODBUS_WRITE_SINGLE             0x06
#define MODBUS_WRITE_MULTI              0x16
#define MODBUS_WRITE_AND_READ           0x60

#define MODBUS_READ_ACK                 0x03
#define MODBUS_WRITE_SINGLE_ACK         0x06
#define MODBUS_WRITE_MULTI_ACK          0x10
#define MODBUS_WRITE_AND_READ_ACK       0x60

#define READ_ORDER_START_ADDRESS        0x0000
#define READ_ORDER_END_ADDRESS          0x0003          //MODBUS 读命令的起始结束地址,见通讯协议寄存器地址定义


#define READ_STATUS_START_ADDRESS       0x0100
#define READ_STATUS_END_ADDRESS         0x010E          //MODBUS 读状态的起始结束地址

#define READ_EEPROM_START_ADDRESS       0x1020
#define READ_EEPROM_END_ADDRESS         (WRITE_EEPROM_START_ADDRESS + EEPROM_WORD_NUM -1)          //MODBUS 读eeprom的起始结束地址


#define WRITE_COMMAND_START_ADDRESS     0x0000
#define WRITE_COMMAND_END_ADDRESS       0x0005          //MODBUS 写命令的起始结束地址

#define WRITE_EEPROM_START_ADDRESS      0x1020
#define WRITE_EEPROM_END_ADDRESS        (WRITE_EEPROM_START_ADDRESS + EEPROM_WORD_NUM -1)//MODBUS 写EEPROM的起始结束地址

#define	CHECKSUM_ADDRESS		WRITE_EEPROM_END_ADDRESS		//最后一个地址是checksum,以上都是逻辑地址.与物理地址不同
/**************************************************************************
*    函数原型:void InitUart(void)
*    功    能:
**************************************************************************/
void InitUart3(void)
{
    FM0P_GPIO->PFR2_f.P22 = 1;                // act as peripheral function
    FM0P_GPIO->DDR2_f.P22 = 0;                    // input pin
    FM0P_GPIO->PCR2_f.P22 = 1;
    
    FM0P_GPIO->PFR2_f.P21 = 1;                // act as peripheral function
    FM0P_GPIO->DDR2_f.P21 = 1;   
    FM0P_GPIO->PCR2_f.P21 = 1;
    
    FM0P_GPIO->EPFR07_f.SIN0S = 0;
    FM0P_GPIO->EPFR07_f.SOT0B = 1;

    FM0P_MFS0_UART->SCR_f.UPCL = 1;       //UPCL=1 programmerble clear

    FM0P_MFS0_UART->BGR = 4165;   // Value=((bus clock/baudrate)-1) APB2=40MHz ,error>2%  bdr=9600

    FM0P_MFS0_UART->SMR = 0;   // bit7~5:MD2~0=0b000 mode0 asynchronize normal;LSB first;1 bit stop

    FM0P_MFS0_UART->SMR_f.SOE = 1; // bit0:SOE=1 serial data output enable  

    FM0P_MFS0_UART->ESCR = 0;  // bit7:FLWEN=0 hardwere flow disable  ;NRZ format; disable parity;8-bit Data length

    FM0P_MFS0_UART->SCR_f.RXE = 1;   //en rx
    FM0P_MFS0_UART->SCR_f.RIE = 1;   // en rx int 


    /*断帧定时器*/
    FM0P_BT3_RT->TMCR = 0x2030;//CKS3-CKS0:1010 -> CLK/2048,trigger input disable
    FM0P_BT3_RT->TMCR2 = 0x01;

    FM0P_BT3_RT->STC = 0x10;        //Enable underflow interrupt,Clear interupt cause
    FM0P_BT3_RT->PCSR = 78;
    FM0P_BT3_RT->TMR = 78;
    //FM0P_BT3_RT->TMCR|= 0x03;      //software trigger and count start 
}
/**************************************************************************
*    函数原型: INT16U CRC16(void)
*    功    能: 多项式X16+X12+X5+X1
**************************************************************************/ 
INT16U CRC16(INT8U *ptr,INT8U len) // ptr 为数据指针，len 为数据长度
{
    INT8U i;
    INT16U crc = 0;
    while(len--)
    {
        for(i=0x80; i!=0; i>>=1)
        {
            if((crc&0x8000)!=0) {crc<<=1; crc^=0x1021;} 
            else crc<<=1;  
            if((*ptr&i)!=0) crc^=0x1021;  
        }
        ptr++;
    }
    return(crc);
}
/**************************************************************************
*    函数原型: void ReadyUartTx(void)
*    功    能:
**************************************************************************/
void ReadyUartTx(void)
{ 
    st_UartTx.TxCount = 0;      

    FM0P_MFS0_UART->SCR_f.TIE = 1;
    FM0P_MFS0_UART->SCR_f.TXE = 1;
}

/**************************************************************************
*    函数原型: INT16U CheckSumPrc()
*    功    能: 
**************************************************************************/
INT16U CheckSumPrc()
{
    INT16U CheckCode = 0;
    INT16U RecCheck = 0; 
    INT8U  i = 0;

    
    if ((st_UartRec.RxDataBuff[1]& 0x80) == 0)
    {       //--CRC校验
            
        st_UartRec.CrcCheckFlag = 1;

        //Ptr = st_UartRec.RxDataBuff;
        CheckCode = CRC16(&st_UartRec.RxDataBuff[0],st_UartRec.MaxRxNumber);         
        
        if (CheckCode == 0x00)
        {
            return(1);              //校验码正确
        }
        else
        {
            return(0);
        }
    }
    else
    {
        st_UartRec.CrcCheckFlag = 0;
        //--累加和校验
        for (i = 0; i < (st_UartRec.MaxRxNumber - 2); i++)
        {
            CheckCode += st_UartRec.RxDataBuff[i];
        }

        RecCheck = (INT16U)((st_UartRec.RxDataBuff[st_UartRec.MaxRxNumber - 2] << 8)+ st_UartRec.RxDataBuff[st_UartRec.MaxRxNumber - 1]);

        if (CheckCode == RecCheck)
        {
            return(1);              //校验码正确
        }
        else
        {
            return(0);
        }
    }
}
/**************************************************************************
*    函数原型: INT16U GetRegisterData(INT16U Address)
*    功    能: 获取对应地址中的数据
**************************************************************************/
INT16U GetRegisterData(INT16U Address)
{
    INT8U   Offset = 0;
    INT16U  GetData = 0;
    
    if ((Address >= READ_ORDER_START_ADDRESS) && (Address <= READ_ORDER_END_ADDRESS))
    {
        Offset = (Address - READ_ORDER_START_ADDRESS);  
        
        GetData = SetCommand.SetDataArray[Offset];
    }
    else if ((Address >= READ_STATUS_START_ADDRESS) && (Address <= READ_STATUS_END_ADDRESS))
    {
        Offset = (Address - READ_STATUS_START_ADDRESS);  
        
        GetData = RunParameter.ReadDataArray[Offset];                
            
    }
    else if ((Address >= READ_EEPROM_START_ADDRESS) && (Address <= READ_EEPROM_END_ADDRESS))
    {
        //EEPROM中的参数与RAM的内容是同步的，只需要提供RAM参数就可以
        Offset = (Address - READ_EEPROM_START_ADDRESS);  
        
        GetData = EepromParameter.DataArray[Offset];      
    }
    else
    {
        GetData = 0;
    }
    
    return(GetData);
}
/**************************************************************************
*    函数原型: void ReadyReadCmdAckData(void)
*    功    能: 接收到read命令后的处理
**************************************************************************/
void ReadyReadCmdAckData(void)
{
    INT8U  i = 0;
    INT8U  ReadByteNum = 0;
    INT8U  ByteId = 0;
     
    INT16U StartAddress = 0;                                //需要读取寄存器的起始地址
    INT16U Address = 0;
    INT16U Data = 0;
     
    INT16U CheckSum = 0;

    ReadByteNum = st_UartRec.RxDataBuff[5];         //发送的数据数目=寄存器数    
    if (ReadByteNum > MAX_READ_REGISTER_NUM)
    {
        ReadByteNum = MAX_READ_REGISTER_NUM;           //最大数目限制
    }
       
    StartAddress = ((st_UartRec.RxDataBuff[2] << 8) | st_UartRec.RxDataBuff[3]);        //取首地址

    st_UartTx.TxDataBuff[0] = MODBUS_ADDRESS;
    st_UartTx.TxDataBuff[1] = st_UartRec.RxDataBuff[1];                      
    st_UartTx.TxDataBuff[2] = ReadByteNum << 1;                          //发送的byte数目

    Address = StartAddress;                 
    ByteId = 3; 
    for (i = 0; i < ReadByteNum; i++)
    {
        Data = GetRegisterData(Address);                
        st_UartTx.TxDataBuff[ByteId] = Data >> 8;                    //high byte
        ByteId++;                
        st_UartTx.TxDataBuff[ByteId] = Data;                         //low byte
        ByteId++;
        Address++;                            
    }
    
    //--根据命令判断是哪种校验和
    if ((st_UartRec.RxDataBuff[1]& 0x80) == 0)   //CRC校验
    {        
        CheckSum = CRC16(&st_UartTx.TxDataBuff[0],ByteId);
    }
    else
    {
        for (i = 0; i < ByteId; i++)
        {
            CheckSum += st_UartTx.TxDataBuff[i];         
        }
    }     

    st_UartTx.TxDataBuff[ByteId] = CheckSum >>8;                         //高位
    ByteId++;
    st_UartTx.TxDataBuff[ByteId] = CheckSum ;                            //低位
    ByteId++;  

    st_UartTx.MaxTxNumber = ByteId;   
}
/**************************************************************************
*    函数原型: void ReadyWriteSingleAckData(void)
*    功    能: 
**************************************************************************/
void ReadyWriteSingleAckData()
{
    INT8U i = 0;
    
    for (i = 0; i < st_UartRec.MaxRxNumber; i++)              //数据原样返回
    {
        st_UartTx.TxDataBuff[i] = st_UartRec.RxDataBuff[i];
    }        
    st_UartTx.MaxTxNumber = st_UartRec.MaxRxNumber;
}

/**************************************************************************
*    函数原型: void ClearErrorPrc(INT8U Command)
*    功    能: 故障清除
**************************************************************************/
void ClearErrorPrc(INT16U Command)
{ 
    if (Command & 0xffff) 
    {
        st_CompRunPar.u32ErroType = 0;
    }
}

/**************************************************************************
*    函数原型: void DecodeCommand(INT8U CommandId)
*    功    能: 执行命令
**************************************************************************/
void DecodeCommand(INT8U CommandId)
{
    if (CommandId == 0)                     
    {                
            //开关机
        if ((SetCommand.SetDataArray[CommandId] & 0x0003) == 0x0000)               
        {
            SetCompressorOff();
        }
        else if ((SetCommand.SetDataArray[CommandId] & 0x0003) == 0x0003)          
        {                
            SetCompressorOn();
        }     
    }
    else if (CommandId == 1)                //清除故障
    {
        ClearErrorPrc(SetCommand.SetDataArray[CommandId]);          
    }
    else if (CommandId == 2)                //设定目标频率
    {
        SetNewTargrt(SetCommand.SetDataArray[CommandId]); 
    }
}

/**************************************************************************
*    函数原型: void WriteData(INT16U Address, INT16U Data)
*    功    能: 
**************************************************************************/
void WriteData(INT16U TargetAddress, INT16U Data)
{
    INT8U Offset = 0;
        
    if ((TargetAddress >= WRITE_COMMAND_START_ADDRESS) && (TargetAddress <= WRITE_COMMAND_END_ADDRESS))
    {       //--写命令
        Offset = (TargetAddress - WRITE_COMMAND_START_ADDRESS);
        
        SetCommand.SetDataArray[Offset] = Data;

        if(st_CompRunPar.u16MotorInputMode == COMM_INPUT_MODE)
        {
            DecodeCommand(Offset);                // 
        }
    }
    else if ((TargetAddress >= WRITE_EEPROM_START_ADDRESS) && (TargetAddress <= WRITE_EEPROM_END_ADDRESS))
    {
        //--写EEPROM
        Offset = (TargetAddress - WRITE_EEPROM_START_ADDRESS);
        
        EepromParameter.DataArray[Offset] = Data;  
     
        UpdateEeprom(Offset,Data);           //modbus地址左移一位，用作物理EEPROM地址
    }
}

/**************************************************************************
*    函数原型: void WriteSingle(void)
*    功    能: 
**************************************************************************/
void WriteSingle(void)
{
    INT16U TargetAddress = 0;
    INT16U Data = 0;
    
    TargetAddress = ((st_UartRec.RxDataBuff[2] << 8) | st_UartRec.RxDataBuff[3]);
    
    Data = ((st_UartRec.RxDataBuff[4] << 8) | st_UartRec.RxDataBuff[5]);                                 
    WriteData(TargetAddress,Data);        
}
/**************************************************************************
*    函数原型: void WriteMulti(void)
*    功    能: 
**************************************************************************/
void WriteMulti(void)
{
    INT16U TargetAddress = 0;
    INT16U  Data = 0;
    INT8U  WriteByteNum = 0;
    INT8U  ByteId = 0;
    INT8U  i = 0;
    
    TargetAddress = ((st_UartRec.RxDataBuff[2] << 8) | st_UartRec.RxDataBuff[3]);
    WriteByteNum = st_UartRec.RxDataBuff[5];                                      //取要写的寄存器格式                   
    
    ByteId = 7;                                                     //从st_UartRec.RxDataBuff[7] 开始就是数据
    for (i = 0; i < WriteByteNum; i++)
    {
        Data = st_UartRec.RxDataBuff[ByteId] << 8;                            //取高字节 
        ByteId++;
        Data |= st_UartRec.RxDataBuff[ByteId];                                //取低字节         
        ByteId++;
        
        WriteData(TargetAddress,Data);
        TargetAddress++;
    }
}
/**************************************************************************
*    函数原型: void ReadyWritMultiAckData(void)
*    功    能: 
**************************************************************************/
void ReadyWriteMultiAckData(void)
{
    INT8U i = 0;
    INT16U CheckSum = 0;

    st_UartTx.TxDataBuff[0] = st_UartRec.RxDataBuff[0];
    st_UartTx.TxDataBuff[1] = st_UartRec.RxDataBuff[1];
    st_UartTx.TxDataBuff[2] = st_UartRec.RxDataBuff[6];                //写的字节数
    
    st_UartTx.TxDataBuff[3] = st_UartRec.RxDataBuff[2];
    st_UartTx.TxDataBuff[4] = st_UartRec.RxDataBuff[3];                //起始地址
    
    st_UartTx.TxDataBuff[5] = st_UartRec.RxDataBuff[4];
    st_UartTx.TxDataBuff[6] = st_UartRec.RxDataBuff[5];                //写入寄存器数目
    
    //--根据命令判断是哪种校验和
    if ((st_UartRec.RxDataBuff[1]& 0x80) == 0)
    {       //CRC校验
      
        CheckSum = CRC16(&st_UartTx.TxDataBuff[0],7);        
        st_UartTx.TxDataBuff[7] = CheckSum >>8;     //高位
        st_UartTx.TxDataBuff[8] = CheckSum ;        //低位
    }
    else
    {
        for (i = 0; i < 7; i++)
        {
            CheckSum += st_UartTx.TxDataBuff[i];          //Address是临时变量
        }
        
        st_UartTx.TxDataBuff[7] =(INT8U) (CheckSum >> 8);               
        st_UartTx.TxDataBuff[8] =(INT8U) (CheckSum & 0x00ff);
    }     
    
    st_UartTx.MaxTxNumber = 9;
}
/**************************************************************************
*    函数原型: void WriteNewCheckSum(void)
*    功    能: 重新计算校验和并将新的校验和写入EEPROM中
**************************************************************************/
void WriteNewCheckSum(void)
{	 
    INT16U CheckSum = 0;	
	INT16U tmp = 0;
	INT16U CheckTab = 0;
	
	//--crc校验	
	if (g_CrcCheck)
	{
	    CheckSum = CRC16(&EepromParameter.Data8UArray[0],((g_ReadDataNum - 1) << 1));
	}
	else
	{
	    CheckSum = GetAccumulateSum(&EepromParameter.Data8UArray[0],((g_ReadDataNum - 1)<< 1));
	}	
	
    EepromParameter.Data.CheckSum = CheckSum;             //注意，高低字节顺序不同，不能直接赋值
	CheckTab = ((EEPROM_WORD_NUM) << 1) - 1;
	tmp = (EepromParameter.Data8UArray[CheckTab] << 8)| EepromParameter.Data8UArray[(CheckTab -1)];	//特殊处理
	 
	
	WriteData(CHECKSUM_ADDRESS,tmp);				//更新EEPROM中的校验和,注意是逻辑地址
	 
}

/**************************************************************************
*    函数原型: void DecodeRx(void)
*    功    能: 
**************************************************************************/
void DecodeUartRx(void)
{
    INT16U CheckValue = 0;
    
    if(st_UartRec.OneFrameRecFlag == 1)
    {
        st_UartRec.OneFrameRecFlag = 0;
        CheckValue = CheckSumPrc(); 
        if(CheckValue == 1)                      //校验码正确
        {
            if ((st_UartRec.RxDataBuff[1] & 0x7f) == MODBUS_READ)
            {
                ReadyReadCmdAckData();
            }
            else if ((st_UartRec.RxDataBuff[1] & 0x7f) == MODBUS_WRITE_SINGLE)
            {                
                WriteSingle();
                WriteNewCheckSum();			//写入新的校验和
                ReadyWriteSingleAckData();
            }
            else if ((st_UartRec.RxDataBuff[1] & 0x7f) == MODBUS_WRITE_MULTI)
            {                         
                WriteMulti();
                WriteNewCheckSum();			//写入新的校验和
                ReadyWriteMultiAckData();
            }
            else if ((st_UartRec.RxDataBuff[1] & 0x7f) == MODBUS_WRITE_AND_READ)
            {
                    
            }

            
            st_UartTx.DelayTxFlag = 1;
            st_UartTx.TxDelayTime = 0;           
            
        }
        else
        {
            FM0P_MFS0_UART->SCR_f.RXE = 1;   //en rx
            FM0P_MFS0_UART->SCR_f.RIE = 1;   // en rx int 
        }  
    }
}

/**************************************************************************
*    函数原型: void ISR_UART0_Receive(void)
*    功    能:
**************************************************************************/
void ISR_UART0_Receive(void)
{
    INT8U UartData;          

    UartData = FM0P_MFS0_UART->RDR;                    //读取数据  
    
    if(FM0P_MFS0_UART->SSR & 0x38)      //Receive Error Action:PE,FRE,ORE
    {                                       	
        FM0P_MFS0_UART->SSR |= 0x80;        //REC=1:clear error(PE,FRE,ORE) flag\
              
        return;
    }

    st_UartRec.RxDataBuff[st_UartRec.RxCount] = UartData;
    st_UartRec.RxCount++;
    if(st_UartRec.RxCount >= MAX_DEF_RX_BYTE)
    {
        st_UartRec.RxCount = 0;
    } 

    FM0P_BT3_RT->TMCR &= 0xfffC;      //Disable software trigger and count stop  
    /*启动定时器，当间隔超过4ms无数据，则说明一帧数据传送结束*/   
    FM0P_BT3_RT->STC &= 0xF8;        //Enable underflow interrupt,Clear interupt cause
    FM0P_BT3_RT->PCSR = 78;          // 4MS    
    FM0P_BT3_RT->TMR = 78;
    FM0P_BT3_RT->TMCR|= 0x03;      //software trigger and count start 
}
/**************************************************************************
*    函数原型: void ISR_UART3_Transmit(void)
*    功    能:
**************************************************************************/
void ISR_UART0_Transmit(void)
{       
    if (st_UartTx.TxCount >= st_UartTx.MaxTxNumber)
    {
        st_UartTx.TxCount = 0;
         
        FM0P_MFS0_UART->SCR_f.TIE = 0;
        FM0P_MFS0_UART->SCR_f.TXE = 0;
        FM0P_MFS0_UART->SCR_f.RXE = 1;   //en rx
        FM0P_MFS0_UART->SCR_f.RIE = 1;   // en rx int 
     
    }
    else
    {
        FM0P_MFS0_UART->RDR = st_UartTx.TxDataBuff[st_UartTx.TxCount];
        st_UartTx.TxCount++;
    }
}
/**************************************************************************
*    函数原型: void UartFrameRec(void)
*    功    能:
**************************************************************************/
void UartFrameRec(void)
{    
    FM0P_BT3_RT->STC &= 0xF8;        //Enable underflow interrupt,Clear interupt cause

    FM0P_BT3_RT->TMCR &= 0xfffC;      //Disable software trigger and count stop 
   
    if(st_UartRec.RxDataBuff[0] == MODBUS_ADDRESS)
    {
        st_UartRec.MaxRxNumber = st_UartRec.RxCount;
        st_UartRec.OneFrameRecFlag = 1;
        st_UartRec.RxCount = 0;
        FM0P_MFS0_UART->SCR_f.RXE = 0;   //Disable rx
        FM0P_MFS0_UART->SCR_f.RIE = 0;   // Disable rx int 
    }
    else
    {
        st_UartRec.RxCount = 0;
    }

}

