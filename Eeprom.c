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
#include "Eeprom.h"

#define	 I2C_SDA_INPUT()    (FM0P_GPIO->PDIR4_f.P46)

#define  SetSdaOutput()     (FM0P_GPIO->DDR4_f.P46 = 1)
#define  SetSdaInput()      (FM0P_GPIO->DDR4_f.P46 = 0)

#define  SetSDAHigh()       (FM0P_GPIO->PDOR4_f.P46 = 1)
#define  SetSDALow()        (FM0P_GPIO->PDOR4_f.P46 = 0)
#define  SetSCLKHigh()      (FM0P_GPIO->PDOR4_f.P47 = 1)
#define  SetSCLKLow()       (FM0P_GPIO->PDOR4_f.P47 = 0)
#define	 I2C_DELAY()		{asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP");asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP"); asm("\tNOP");}

#define	 AT24C02_WR_COMMAND		0xa0		//EEPROM器件地址+写命令
#define	 AT24C02_RD_COMMAND		0Xa1		//读命令

#define  TIME_20MS       5

EEpromStrUnion    EepromParameter;
INT16U            g_ReadDataNum;
INT8U             g_ReadDataTimes;
INT8U             g_CrcCheck;                           //  1crc校验，0累加和校验
INT8U   	      g_WaitTime;


/**************************************************************************
*    函数原型:void InitIICPort(void)
*    功    能:
**************************************************************************/
void InitIICPort(void)
{
    FM0P_GPIO->SPSR_f.SUBXC0 = 0;  //X0A,X1A USED AS IO
    FM0P_GPIO->SPSR_f.SUBXC1 = 0;

    //IIC-SDA
    FM0P_GPIO->PFR4_f.P46 = 0;              // disable peripheral function 
    FM0P_GPIO->PCR4_f.P46 = 1; 
    FM0P_GPIO->DDR4_f.P46 = 1;                // output pin
    FM0P_GPIO->PDOR4_f.P46 = 1;	
  
    //IIC-SCLK
    FM0P_GPIO->PFR4_f.P47 = 0;              // disable peripheral function 
    FM0P_GPIO->PCR4_f.P47 = 1; 
    FM0P_GPIO->DDR4_f.P47 = 1;                // output pin
    FM0P_GPIO->PDOR4_f.P47 = 1;	     
}


/**************************************************************************
*    函数原型: void Delayms(unsigned char Time)
*    功    能:延时,rWaitTime一个数值为2ms
**************************************************************************/
void Delayms(INT8U Time)
{
	g_WaitTime = 0; 
	
	while(g_WaitTime < Time)
	{
        Hwwdg_Feed(0x55,0xAA);
        Swwdg_Feed();        
    }
}

/**************************************************************************
*    函数原型:void I2cStart()
*    功    能:I2C起始程序
**************************************************************************/
void I2cStart()
{
	SetSdaOutput();
	I2C_DELAY();	
	SetSDAHigh();	
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSDALow();
	I2C_DELAY();
	SetSCLKLow();	
	I2C_DELAY();
}
/**************************************************************************
*    函数原型:void I2cStop()
*    功    能:I2C起始程序
**************************************************************************/
void I2cStop()
{
	SetSdaOutput();
	I2C_DELAY();	
	SetSDALow();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSDAHigh();
	I2C_DELAY();
}
/**************************************************************************
*    函数原型:void SendAck()
*    功    能:发送ack响应
**************************************************************************/
void SendAck()
{
	SetSdaOutput();;
	I2C_DELAY();
	SetSDALow();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSCLKLow();
	I2C_DELAY();
}
/**************************************************************************
*    函数原型:void SendNoAck()
*    功    能:发送noack响应
**************************************************************************/
void SendNoAck()
{
	SetSdaOutput();
	I2C_DELAY();
	SetSDAHigh();
	I2C_DELAY();
	SetSCLKHigh();
	I2C_DELAY();
	SetSCLKLow();
	I2C_DELAY();
}
/**************************************************************************
*    函数原型:void CheckAck()
*    功    能:等待响应响应
**************************************************************************/
void CheckAck()
{
	INT8U i = 0;
	
	SetSCLKLow();
	SetSDAHigh();
	SetSdaInput();
	I2C_DELAY();
	
	SetSCLKHigh();
	while((I2C_SDA_INPUT()) && (i < 20))			//连续读取
	{
		i++;
	}
	SetSCLKLow();
	I2C_DELAY();	
}
/**************************************************************************
*    函数原型:void I2cWrite(INT8U WriteData)
*    功    能:写命令
*    输    入:WriteData 待发送的数据
*    输    出:
*    全局变量:
*    调用模块:
*    注意事项:
**************************************************************************/
void I2cWrite(INT8U WriteByte)
{
	INT8U i = 0;	 
	
	SetSdaOutput();
	I2C_DELAY();
	for(i = 0;i < 8;i++)
	{
		SetSCLKLow();
		if(WriteByte & 0x80)
        {
			SetSDAHigh();
        }
		else 
        {
			SetSDALow();	
        }
					
		WriteByte <<= 1;
		SetSCLKHigh();
		I2C_DELAY();
		SetSCLKLow();
		I2C_DELAY();		
	}	
}
/**************************************************************************
*    函数原型:INT8U I2cRead(void)
*    功    能:读命令
*    输    入:
*    输    出:return 读取到的数据ReadByte
*    全局变量:
*    调用模块:
*    注意事项:
**************************************************************************/
INT8U I2cRead(void)
{
	INT8U i = 0;
	INT8U ReadByte = 0;
	
	SetSCLKLow();	
	SetSdaInput();	
	I2C_DELAY();
	for(i = 0;i < 8;i++)
	{
		I2C_DELAY();
		
		SetSCLKHigh();
		I2C_DELAY();
				
		ReadByte <<= 1;
		
		if (I2C_SDA_INPUT())
        {
            ReadByte |= 0x01;
        }		
		
		SetSCLKLow();		
	}	
	return(ReadByte);
}
/**************************************************************************
*    函数原型:void I2cWriteNByte(INT8U WriteStartAddress,INT8U *WriteData,INT8U WriteByteNumber)
*    功    能:写若干字节
*    输    入:要读的24c02的起始地址ReadStartAddress，待写数据的指针WriteData，需要写的个数WriteByteNumber
*    输    出:
*    全局变量:
*    调用模块:I2cWrite();CheckAck();
*    注意事项:连续写最多只能写8个,//cll注:不能跨越8字节的边界,如8,16,24
**************************************************************************/
void I2cWriteNByte(INT8U WriteStartAddress, INT8U *WriteData, INT8U WriteByteNumber)
{
	INT8U i = 0;	
	
	I2cStart();	
	I2cWrite(AT24C02_WR_COMMAND);			//发写命令	
	CheckAck();
	I2cWrite(WriteStartAddress);
	CheckAck();
	
	Delayms(TIME_20MS);	
	
	for(i = 0;i < WriteByteNumber;i++)
	{
        Hwwdg_Feed(0x55,0xAA);
        Swwdg_Feed();           
	       
		I2cWrite(*WriteData);
		CheckAck();
		WriteData++;
	}
	I2cStop();
	Delayms(TIME_20MS);					//等待时间需要长一些
}
/**************************************************************************
*    函数原型:void I2cReadNByte(INT8U ReadStartAddress,INT8U *ReadData,INT8U ReadByteNumber)
*    功    能:写若干字节
*    输    入:要读的24c02的起始地址ReadStartAddress，读出数据保存的指针ReadData，需要写的个数ReadByteNumber
*    输    出:
*    全局变量:
*    调用模块:I2cWrite();I2cWrite();CheckAck();
*    注意事项:
**************************************************************************/
void I2cReadNByte(INT8U ReadStartAddress,INT8U *ReadData,INT8U ReadByteNumber)
{
	INT8U i = 0;
	
	I2cStart();
	
	I2cWrite(AT24C02_WR_COMMAND);
	CheckAck();
	I2cWrite(ReadStartAddress);
	CheckAck();
	
	I2C_DELAY();
    Hwwdg_Feed(0x55,0xAA);
    Swwdg_Feed(); 
   
	I2cStart();
		
	I2cWrite(AT24C02_RD_COMMAND);
	CheckAck();
	
	Delayms(TIME_20MS);
	
	for(i = 0;i < ReadByteNumber;i++)
	{		
		*ReadData = I2cRead();
		if(i == (ReadByteNumber - 1))
		{
			SendNoAck();		//最后一位发NOACK
		}
		else
		{
			SendAck();
	    }
		ReadData++;
		I2C_DELAY();			//此处需要稍微延迟一下，否则出错
	}		
	I2C_DELAY();				//此处需也要稍微延迟一下
	I2cStop();
	Delayms(TIME_20MS);
}
/**************************************************************************
*    函数原型: INT16U GetAccumulateSum(INT8U *ptr,INT8U len)
*    功    能:  累加和校验
**************************************************************************/
INT16U GetAccumulateSum(INT8U *ptr,INT8U len)
{
    INT8U i = 0;
    
    INT16U  AccSum = 0;
    
    for (i = 0; i < len; i++)
    {
        AccSum += *ptr;
        ptr++;
    }
    
    return(AccSum);
}

/**************************************************************************
*    函数原型: void SaveDataToEEprom()
*    功    能: 保存数据
*    说    明: 
*    参    数: 
*    返    回: 
**************************************************************************/
void SaveDefaultToEEprom(void)
{
	INT16U CheckSum = 0;
	INT8U  i = 0;
	INT8U  tmp = 0;
	
	INT16U Address = 0;
	INT8U  Data[2] = {0,0};

    EepromParameter.Data.MotorInputMode = THREE_LEVEL_MODE;
	EepromParameter.Data.MotorRunningMode = POWER_MODE;
	
	//EepromParameter.Data.HighPower = 0x3200;  //50w
	//EepromParameter.Data.MedPower  = 0x1E00;  //30w
	//EepromParameter.Data.LowPower  = 0x0A00;  //10w
	EepromParameter.Data.HighDryPowerRom = 0x3200;  //50w
	EepromParameter.Data.MedDryPowerRom  = 0x1E00;  //30w
	EepromParameter.Data.LowDryPowerRom  = 0x0A00;  //10w
	
	EepromParameter.Data.HighWetPowerRom = 0x3200;  //50w
	EepromParameter.Data.MedWetPowerRom  = 0x1E00;  //30w
	EepromParameter.Data.LowWetPowerRom  = 0x0A00;  //10w

	EepromParameter.Data.HighDrySpeedRom = 0x03E8;   //1000RPM
	EepromParameter.Data.MedDrySpeedRom  = 0x0320;  //800RPM
	EepromParameter.Data.LowDrySpeedRom  = 0x01F4;  //500RPM
	
	EepromParameter.Data.HighWetSpeedRom = 0x03E8;  //50w
	EepromParameter.Data.MedWetSpeedRom  = 0x0320;  //30w
	EepromParameter.Data.LowWetSpeedRom  = 0x01F4;  //10w
	
	EepromParameter.Data.HighSpeed = 1200;
	EepromParameter.Data.MedSpeed  = 800;
	EepromParameter.Data.LowSpeed  = 500;
	
	if (g_CrcCheck)
	{
	    CheckSum = CRC16(&EepromParameter.Data8UArray[0],((g_ReadDataNum - 1) << 1));	    
	}
	else
	{
	    CheckSum = GetAccumulateSum(&EepromParameter.Data8UArray[0],((g_ReadDataNum - 1)<< 1));
	}
	 
	EepromParameter.Data.CheckSum = CheckSum;             //注意，高低字节顺序不同，不能直接赋值
	
	for (i = 0; i <= g_ReadDataNum; i++)
	{
		tmp = (i << 1);
		Address = REAL_PARAMETER_START_ADDRESS + tmp;
		
		Data[0] = EepromParameter.Data8UArray[tmp];
		Data[1] = EepromParameter.Data8UArray[tmp + 1];
		I2cWriteNByte(Address,&Data[0],2);                  //每次写2byte
        Hwwdg_Feed(0x55,0xAA);
        Swwdg_Feed();      
	}
}

/**************************************************************************
*    函数原型: void ReadEepromData()
*    功    能: 读取数据
*    说    明: 
*    参    数: 
*    返    回: 
**************************************************************************/
void ReadEepromData(void)
{
    INT16U CheckSum = 0;
    INT16U CheckSum1 = 0;
    INT16U Address = 0;
    INT8U  i   = 0;
    INT8U  Tmp = 0;  
    INT8U  Data[2] = {0,0};
       
    g_ReadDataNum = EEPROM_WORD_NUM ;
    while(g_ReadDataTimes < 3)                                      //最多读3遍
    {
        for (i = 0; i <= g_ReadDataNum; i++)
        {
            Address = REAL_PARAMETER_START_ADDRESS + (i << 1);
            I2cReadNByte(Address,&Data[0],2);		             //每次读取2字节
            Hwwdg_Feed(0x55,0xAA);
            Swwdg_Feed(); 
                	
            EepromParameter.DataArray[i] = (Data[1] << 8) | Data[0];            
        }       
        	
        //--------判断累加校验和
        if (!g_CrcCheck)
        {            
            if (EepromParameter.Data.CheckSum == GetAccumulateSum(&EepromParameter.Data8UArray[0],((g_ReadDataNum - 1)<< 1)))
            {
                CheckSum1 = 0;
            }
            else
            {
                CheckSum1 = 0xaa;
            }
            
            if (CheckSum1 == 0)
            {
                g_ReadDataTimes = 0;
                break;
            }
            else
            {
                g_ReadDataTimes++;
            }    
        }
        else
        {                    
            //---计算CRC校验和之前，需要将EepromParameter.Data.CheckSum的高低位对调  
            Tmp = (g_ReadDataNum - 1) << 1;
            i = EepromParameter.Data8UArray[Tmp];                       //i当临时变量用
            EepromParameter.Data8UArray[Tmp] = EepromParameter.Data8UArray[Tmp + 1];
            EepromParameter.Data8UArray[Tmp +1] = i;        
            //---判断CRC校验和
            CheckSum = CRC16(&EepromParameter.Data8UArray[0],(g_ReadDataNum << 1));
		
            if (CheckSum == 0)
            {
                g_ReadDataTimes = 0;
                break;
            }
            else
            {
                g_ReadDataTimes++;
            }    
        }	    
    }          
        
    if(g_ReadDataTimes != 0)
    {
        g_ReadDataTimes = 0;        
        //----------set default		 
        SaveDefaultToEEprom();
    }     
}

/**************************************************************************
*    函数原型: void UpdateEeprom(INT8U EepromOffset, INT16U Data)
*    功    能: 
**************************************************************************/
void UpdateEeprom(INT8U EepromWordOffset, INT16U Data)
{
    INT8U EepromAddress = 0;
    INT8U aDataBuff[2] = {0,0};
    
    aDataBuff[0] = Data;		//取低位
    aDataBuff[1] = Data >> 8;	//取高位
    
    EepromAddress = (EepromWordOffset << 1) + REAL_PARAMETER_START_ADDRESS;        	//地址需要放大一倍，其中0x40为eeprom起始地址
    
    I2cWriteNByte(EepromAddress,&aDataBuff[0],2);               //写2字节
}


