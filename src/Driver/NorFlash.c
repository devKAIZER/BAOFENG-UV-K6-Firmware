#include "includes.h"

#define FLASH_USE_SPI                     SPI1   //FlashSPI              

void FlashCsDelay(void)
{
    U16 t = 1 * 14;
    while(t--){

    }
}

#define SPI_FLASH_CS_H()               GPIOA->BSRR = GPIO_Pin_2;FlashCsDelay()
#define SPI_FLASH_CS_L()               GPIOA->BRR = GPIO_Pin_2;FlashCsDelay()

#define SPIFLASH_DELAY()                  FlashCsDelay()
#define FlashDelay(x)                     DelayUs(x)    
/*********************************************************************
*   : SpiFlash_SendByte
* : SPISPI
* : 
* data:
* :
* :
*     v1.0
***********************************************************************/
U8 SpiFlash_SendByte(U8 data)
{
    U16 retry=0;
    U8 rxData;

    SPI_SendData8(FLASH_USE_SPI, data);
    while(RESET == SPI_I2S_GetFlagStatus(FLASH_USE_SPI, SPI_I2S_FLAG_TXE))
    {
        retry++;
        if(retry>3000)
        {
           return 0;
        }
    }
    rxData = SPI_ReceiveData8(FLASH_USE_SPI);
    while(SET == SPI_I2S_GetFlagStatus(FLASH_USE_SPI, SPI_I2S_FLAG_BSY))
    {
        retry++;
        if(retry>3000)
        {
           return 0;
        }
    }
    return rxData;
}
/*********************************************************************
*   : SpiFlash_GetByte
* : SPISPI
* : 
* 
* :
* :
*     v1.0
***********************************************************************/
#define SpiFlash_GetByte()   SpiFlash_SendByte(0xA5)

/*********************************************************************
*   : SpiFlash_WriteEnable
* : Flsh
* : 
* 
* :
* :
*     v1.0
***********************************************************************/
void SpiFlash_WriteEnable(void)
{
    SPI_FLASH_CS_L();  
    SpiFlash_SendByte(SPIFLASH_WRITE_ENABLE);
    SPI_FLASH_CS_H();
}
/*********************************************************************
*   : SpiFlash_WriteDisable
* : Flsh
* : 
* 
* :
* :
*     v1.0
***********************************************************************/
void SpiFlash_WriteDisable(void)
{
    SPI_FLASH_CS_L();  
    SpiFlash_SendByte(SPIFLASH_WRITE_DISABLE);
    SPI_FLASH_CS_H();
}

/*********************************************************************
*   : SpiFlash_WriteStatus
* : flash
* : 
* : type:
* : status:
* :
*     v1.0
***********************************************************************/
U8 SpiFlash_ReadStatus(U8 type)
{
    U8 status;
    U8 statusReg;

    switch(type)
    {
       case 2:
           statusReg = SPIFLASH_READSTATUS_REG2;
           break;
       case 3:
           statusReg = SPIFLASH_READSTATUS_REG3;
           break;
       case 1:
       default:
           statusReg = SPIFLASH_READSTATUS_REG1;
           break;
    }

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(statusReg);
    status = SpiFlash_GetByte();

    SPI_FLASH_CS_H();  
    return status;    
}

/*********************************************************************
*   : SpiFlash_WriteStatus
* : flash
* : 
* : status:   type:
* :
* :
*     v1.0
***********************************************************************/
void SpiFlash_WriteStatus(U8 status, U8 type)
{
    U8 statusReg;

    switch(type)
    {
       case 2:
           statusReg = SPIFLASH_WRITESTATUS_REG2;
           break;
       case 3:
           statusReg = SPIFLASH_WRITESTATUS_REG3;
           break;
       case 1:
       default:
           statusReg = SPIFLASH_WRITESTATUS_REG1;
           break;
    }

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(statusReg);
    SpiFlash_SendByte(status);

    SPI_FLASH_CS_H();  
}

/*********************************************************************
*   : SpiFlash_CheckBusy
* : Flash
* : 
* : 
* : 1:   0:
* :
*     v1.0
***********************************************************************/
Boolean SpiFlash_CheckBusy(void)
{
    U8 status;

    status = SpiFlash_ReadStatus(1);
    if( 0x01&status )
    {
        return 1;//busy
    }
    else
    {
        return 0;//ready
    }
}

/*********************************************************************
*   : SpiFlash_ReadBytes
* : 
* : 
* : addr:,24
*           *buf_p:    length: 
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_ReadBytes(U32 addr,U8 *buf_p,U16 length)
{
    U16 i;

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_READ_DATA);

    SpiFlash_SendByte((U8)(addr>>16));
    SpiFlash_SendByte((U8)(addr>>8));
    SpiFlash_SendByte((U8)addr);
    for(i=0;i<length;i++)
    {
        *buf_p = SpiFlash_GetByte();
        buf_p++;
    }

    SPI_FLASH_CS_H();    
}

/*********************************************************************
*   : SpiFlash_WriteByte_InPage
* : 
* : 
* : addr:,24
*           *buf_p:    length: 
* :
* :
*     v1.0
***********************************************************************/
void SpiFlash_WriteByte_InPage(U32 addr,const U8 *buf_p,U16 length)
{
    U16 i,time_out = 10000;

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_PAGE_PROGRAM);

    SpiFlash_SendByte((U8)(addr>>16));
    SpiFlash_SendByte((U8)(addr>>8));
    SpiFlash_SendByte((U8)addr);

    for(i=0;i<length;i++)
    {
        SpiFlash_SendByte(*buf_p);
        buf_p++;
    }

    SPI_FLASH_CS_H();  

    while(time_out--)
    {
        SPIFLASH_DELAY();
        if(!SpiFlash_CheckBusy())
        {
            break;
        }
    }   
}
/*********************************************************************
*   : SpiFlash_WriteBytes
* : 
* : 
* : addr:,24
*           *buf_p:    length: 
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_WriteBytes(U32 addr,const U8 *buf_p,U32 length)
{
    U16 page_can_write_length;
    const U8 *p;

    p = buf_p;

    page_can_write_length = SPIFLASH_PAGESIZE - (addr % SPIFLASH_PAGESIZE);

    if(length > page_can_write_length)
    {
        SpiFlash_WriteByte_InPage(addr,p,page_can_write_length);
        length -= page_can_write_length;    
        addr += page_can_write_length;
        p += page_can_write_length;
        while(length)
        {
            if(length > SPIFLASH_PAGESIZE)
            {
                SpiFlash_WriteByte_InPage(addr,p,SPIFLASH_PAGESIZE);
                length -= SPIFLASH_PAGESIZE;
                addr   += SPIFLASH_PAGESIZE;
                p      += SPIFLASH_PAGESIZE;
            }
            else
            {
                SpiFlash_WriteByte_InPage(addr,p,length);
                length = 0;
                addr += length;
                p += length;
            }
        }
    }
    else
    {
        SpiFlash_WriteByte_InPage(addr,buf_p,(U16)length);
    }
}
/*********************************************************************
*   : SpiFlash_EraseSector(4KB)
* : 
* : 
* : addr:,24,
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_EraseSector(U32 addr)
{
    U16 time_out = 60000;

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_ERASE_SECTOR);

    SpiFlash_SendByte((U8)(addr>>16));
    SpiFlash_SendByte((U8)(addr>>8));
    SpiFlash_SendByte((U8)addr);    
    SPI_FLASH_CS_H(); 

    while(time_out--)
    {
        SPIFLASH_DELAY();
        if(!SpiFlash_CheckBusy())
        {
            break;
        }
    }
}
/*********************************************************************
*   : SpiFlash_Erase32kBlock
* : 32K
* : 
* : addr:,24,12
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_Erase32kBlock(U32 addr)
{
    U16 time_out = 60000;

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_ERASE_32K_BLOCK);

    SpiFlash_SendByte((U8)(addr>>16));
    SpiFlash_SendByte((U8)(addr>>8));
    SpiFlash_SendByte((U8)addr);
    SPI_FLASH_CS_H(); 

    while(time_out--)
    {
        FlashDelay(500);
        if(!SpiFlash_CheckBusy())
        {
            break;
        }
    }  

}
/*********************************************************************
*   : SpiFlash_Erase64kBlock
* : 64K
* : 
* : addr:,24,16
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_Erase64kBlock(U32 addr)
{
    U16 time_out = 60000;

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_ERASE_64K_BLOCK);

    SpiFlash_SendByte((U8)(addr>>16));
    SpiFlash_SendByte((U8)(addr>>8));
    SpiFlash_SendByte((U8)addr);
    SPI_FLASH_CS_H();  
    //5Ms
    DelayMs(5);

    while(time_out--)
    {
        FlashDelay(500);
        if(!SpiFlash_CheckBusy())
        {
            break;
        }
    }     
}

/*********************************************************************
*   : SpiFlash_EraseChip
* : 
* : 
* 
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_EraseChip(void)
{
    U32 time_out = 60000000;

    SpiFlash_WriteEnable();

    SPI_FLASH_CS_L();  

    SpiFlash_SendByte(SPIFLASH_ERASE_CHIP);
    SPI_FLASH_CS_H();
    //100Ms
    DelayMs(100);

    while(time_out--)
    {
        FlashDelay(500);
        if(!SpiFlash_CheckBusy())
        {
            break;
        }
    }  
}
/*********************************************************************
*   : InitSpiFlash
* : SPI FlashSPI
* : 
* 
* :
* :
*     v1.0
***********************************************************************/
extern void SpiFlash_Init(void)
{ 
    SPI_InitTypeDef  SPI_InitStructure;

    SPI_FLASH_CS_H(); 
    SPI_I2S_DeInit(FLASH_USE_SPI);

    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 0;
    SPI_Init(FLASH_USE_SPI, &SPI_InitStructure);

    SPI_Cmd(FLASH_USE_SPI, ENABLE);
}

