#ifndef __INC_PROGROMTYPE_H__
    #define __INC_PROGROMTYPE_H__

#define FLASH_PRO_HEAD           0xA5       //  

#define FLASH_PRO_CMD_ADDR       0x01
#define FLASH_PRO_PACKED_ADDR    0x02
#define FLASH_PRO_LEN_ADDR       0x04
#define FLASH_PRO_DATA_ADDR      0x06

//
#define PRO_CMD_HANDSHAKE        0x02
#define PRO_CMD_ADDR             0x03
#define PRO_CMD_EARSE            0x04
#define PRO_CMD_END              0x06      //
#define PRO_CMD_WRITE            0x57

#define PRO_CMD_ERROR            0xEE

//
#define ERROR_CODE_OK            0X59       //
#define ERROR_CODE_HEAD          0x01       //
#define ERROR_CODE_HAND          0x02       //
#define ERROR_CODE_CMD           0x03       //
#define ERROR_CODE_DATA          0x04       //
#define ERROR_CODE_WRITE         0x05       //Flash
#define ERROR_CODE_ADDR          0x06       //Flash

//
#define ERASE_MODE               0X45
#define ERASE_MODE_CHIP          0X01       //
#define ERASE_MODE_4K            0X02       //4k
#define ERASE_MODE_32K           0X03       //32k
#define ERASE_MODE_64K           0X04       //64k

enum{FLASH_PRG_CHECKHEAD=0,FLASH_PRG_CMD,FLASH_PRG_END,FLASH_PRG_ERROR};

typedef struct
{
    U8  cmd;                  //
    U32 StartAddr;            //Flash
    U16 packageNum;           //
    U16 length;               //
    U16 txLength;             //
    U8  txBuf[64];
}STR_FLASH_PROGROM;

extern STR_FLASH_PROGROM    flashProgrom;    

#define UART_MAX_NUM           1040        //72Flash

#define UARTBUF_NUM      144//72        //72

#define UART_TIMEOUT     2000      //2S

#define PROGROMLEN       64        //32

enum{PRG_CHECKHEAD=0,PRG_FRQRANGE,PRG_WR,PRG_END,PRG_ERROR};

typedef  void (*pFunction)(void);

typedef struct
{
    U8  states;                 //
    U8  errCnt;                 //
    U8  enterMode;              //
    U8  recFlag;                //
    U16 dataNum;                //
    U16 timeOut;                //
    U8  packageTime;            //
    U8  rxBuf[1040];    //
}STR_PROGROM;

extern STR_PROGROM progrom;

extern const U8  strModelType[];

extern Boolean CheckLinkHead(void);
extern void ProgromInit(void);
extern void CheckProgromMode(U8  rxData);
extern void UartSendBuf(U8  *buf,U16 len);
extern void EnterProgromMode(void);
extern void EnterFlashProgromMode(void);

#endif
