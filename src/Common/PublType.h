#ifndef __INC_PUBLTYPE_H__
    #define __INC_PUBLTYPE_H__  

typedef char                String;

typedef int8_t              S8;          
typedef int16_t             S16;          
typedef int32_t             S32;       
typedef int64_t             S64; 

typedef uint8_t             U8;       
typedef uint16_t            U16;   
typedef uint32_t            U32;   
typedef uint64_t            U64;        

typedef int_fast8_t         Boolean;         // 1bit

#define __BYTE              uint8_t

typedef void (*pFunction)(void);

#define BIT0            0x0001
#define BIT1            0x0002
#define BIT2            0x0004
#define BIT3            0x0008
#define BIT4            0x0010
#define BIT5            0x0020
#define BIT6            0x0040
#define BIT7            0x0080
#define BIT8            0x0100
#define BIT9            0x0200
#define BIT10           0x0400
#define BIT11           0x0800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000  
#define BIT15           0x8000

//
#define FERROR          1
#define OK              0

typedef enum 
{
    OFF=0,ON
}ENUM_ONOFF;

typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}
bool;


enum{KEY_CLICKED=0,KEY_LONG,KEY_CONTINUE};

typedef union 
{
    U32 dest;
    U8 src[4];
}UninoU32;

#define INPUT_TIME_OUT         50
#define INPUT_DTMF_TIME_OUT    100

typedef struct
{
    U8             time;                       //
    U8             len;                        //
    U8             pos;
    U8             maxLen;                     //
    U8             inputType;                  //
    U8             isFirstInput;               //
    String         buf[20];                    //
} STR_INPUTBOX;
//----------------------------------------------------------------------------------
enum {RF_NONE=0,RF_RX,RF_TX};
enum {RX_READY=0,GET_CALL,WAIT_RXEND,RX_MONI};            //RXSTATE
enum {TX_READY=0,WAIT_PTT_RELEASE,PTT_RELEASE,TX_ROGER_BEEP,TX_ROGER_PATTERN,TX_STOP,ALARM_TXID,TX_KILLED}; //TXSTATE
enum {VFO_MODE=0,CHAN_MODE};
enum {CHAN_DISABLE=0,CHAN_ACTIVE};

//
typedef struct
{
    U16   totTime;                                //
    U16   voxDetDly;                              //  
    U16   voxWorkDly;                             //
    U16   relayTailSetTime;                       //
    U8    txChEnable;                             //
    U8    txEnable[4];                            //
}__attribute__( ( packed ) )STR_TXFLAG;
//
typedef struct
{
    U8    rxReceived;                             //,1     
    U16   relayTailDetTime;                       //
    U16   codeDetTime;                            //
    U16   rxFlashTime;                            //
    U16   txDly;                                  //
    U8    rxReceiveOn;                            //,1  
}__attribute__( ( packed ) )STR_RXFLAG;

typedef struct
{
    U8  codeLen;                                 //DTMF
    U8  code[16];                                //DTMF
}STR_DTMFTYPEIN;

typedef struct
{       
    U8    sysRunMode;
    STR_TXFLAG    rfTxFlag;
    STR_RXFLAG    rfRxFlag;
    U8    moniFlag;
    U8    ledState;                               //
    U16   keyAutoTime;                            //
    U16   lcdAutoLight;                           //
    U8    dtmfToneFlag;                           //DTMF
    U8    pttFlag;                                //PTTPTTA B 
    U8    batState;                               // 0:    1: 
    U8    lcdBackSwtch;                           //
    STR_DTMFTYPEIN txDtmfCode;                    //DTMF,
    U8    flagDisANI;                             //
    U32   decoderCode;                            //
    U8    moduleType;                             //
}STR_SYSTEM;

typedef struct
{
    U16    vhfL;
    U16    vhfH;
    U16    uhfL;
    U16    uhfH;
    U16    vhf2L;
    U16    vhf2H;
    U16    B350ML;
    U16    B350MH;
    U32    freqVL;
    U32    freqVH;
    U32    freqUL;
    U32    freqUH;
    U32    freqV2L;
    U32    freqV2H;
    U32    freq350ML;
    U32    freq350MH;
}STR_FREQBAND;

#define BAND_BUF_CNT       4  //UV

typedef struct
{
    U16 freq[2*BAND_BUF_CNT];
    U32 freq32[2*BAND_BUF_CNT];
}STR_BANDBUF;

//
typedef union
{
    STR_FREQBAND bandFreq;
    STR_BANDBUF  bandbuf;
}STR_BAND;

typedef union {
	__BYTE	Byte;
	struct {
			__BYTE	b0:1;
			__BYTE	b1:1;
			__BYTE	b2:1;
			__BYTE	b3:1;
			__BYTE	spMute:2;
			__BYTE	b6:1;
			__BYTE	b7:1;
	} Bit;
} ChParaFlag1;    

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:2;
            __BYTE  b2:1;
            __BYTE  b3:1;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE	b6:1;
			__BYTE	b7:1;
    } Bit;
}VfoParaFlag1;
/***********************************************************************************/
typedef struct
{
    U32 rxFreq;    
    U32 txFreq;      
    U16 rxDCSCTSNum; 
    U16 txDCSCTSNum; 
    U8  dtmfgroup;    
    U8  pttID;       
    U8  txPower;      
    ChParaFlag1 chFlag3; /*channel flag 3*/
                        //BIT6:        0: 25K1: 12.5K2:20K  :   
                        //BIT5 BIT4:  0:QT  1:DTMF  2:QT+DTMF  3:QT*DTMF
                        //BIT3:  00: OFF 01: ON  : 
                        //BIT2:      00: OFF 01: ON  : 
                        //BIT1: 
                        //BIT0:  0:  1: ()
    //U8  channelName[16];  //      
    U32 decoderCode;   
}STR_CHANNEL;

/***********************************************************************************/
typedef struct
{
    U8  freq[8];      
    U16 rxDCSCTSNum; 
    U16 txDCSCTSNum;  
    U8  remain0[2];

    U8  dtmfgroup;        
    U8  ANI;                       
    U8  txPower;     
    VfoParaFlag1 vfoFlag;     /*channel flag 3*/
                         //BIT6:        0: 25K1: 12.5K 2:20K  : 
                         //BIT4 BIT5: 
                         //: 
                         //BIT0:
    U8  remain1;   
    U8  STEP;         //  : 0-7    
    U8  Offset[7];  
    U8  spMute;       
    U32 decoderCode; 
}STR_VFOMODE; 

/*----------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    U32 frequency;
    U8  dcsCtsType;
    U32 dcsCtsNum;
}STR_FREQINFO;

typedef struct
{
    STR_FREQINFO freqRx;
    STR_FREQINFO freqTx;
    STR_FREQINFO *rx;    //
    STR_FREQINFO *tx;    //
    U8  wideNarrow;
    U8  txPower;
    U8  fhssFlag;
    U8  scarmble;
    U8  spMute;
    U8  busyLock;
    U8  dtmfgroup;
    U8  chVfoMode;
    U8  freqDir;
    U8  freqStep;
    U32 freqOffset;
    U8  reverseFlag;
    U8  pttIdMode;
    U8  channelName[16];
}STR_CH_VFO_INFO;

typedef struct
{
   STR_CH_VFO_INFO   chVfoInfo[2];      //AB
   STR_VFOMODE vfoInfo[2];              
   STR_CHANNEL channelInfo[2];
   U8   scanList[999/8 + 1];     //
   U8   chanActiveList[999/8 + 1];//
   U8   switchAB;         //AB
   U8   dualAB;
   U8   BandFlag;         //
   U8   haveChannel;      //
   U8   haveScan;         //
   U16  channelNum[2];
   U16  currentChannelNum;
}STR_CHANNEL_VFO;
/*----------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------*/
typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:1;
            __BYTE  b1:1;
            __BYTE  b2:1;
            __BYTE  b3:1;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE  b6:1;
            __BYTE  b7:1;
    } Bit;
}UNION_FLAG1;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:2;
            __BYTE  b2:2;
            __BYTE  b3:3;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE  b6:1;
            __BYTE  b7:1;
    } Bit;
}UNION_FLAG2;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  TxTone:1;
            __BYTE  Remain:3;
            __BYTE  AutoOff:4;
    } Bit;
}UNION_FLAG3;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  chVofA:4;
            __BYTE  chVofB:4;
    } Bit;
}UNION_VM;
/*----------------------------------------------------------------------------------------------------------
      (Radio Information)  
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{ 
    U8   sqlLevel;        //SQL          0 ~ 9 
    U8   saveLevel;       //             0:       1: 1:1     2: 1:2     3: 1:3    4: 1:4
    U8   voxLevel;        //VOX          0: 1~ 9
    U8   autoBack;        //ABR          0-5s                
    U8   dualRxFlag;      //TDR          0:       1:   (: 0: 1: A+B 2: A+C 3: B+C)  
    U8   totLevel;        //TOT        0-18015:0 1 2 3 .... 12 0      
    U8   beepsSwitch;     //BEEP           0:       1:  
    U8   voiceSw;         //VOICE    0:       1: 

    U8   remainLang;      //reserved (unused display/voice language selector slot)
    U8   dtmfTone;        //DTMF      0:   1:      2:      3:   +    
    U8   scanMode;        //SCREV      00:   01:   10:    :         
    U8   pttIdMode;       //PTTID              00:       01: BOT()   10: EOT()   11:  : 
    U8   pttIdTime;       //PTTLTID         0-3100 ms  
    U8   channleDisA;     //MDFA A  00: +  01: + (S19 0: 1: 2:)
    U8   channleDisB;     //MDFB B  00: +  01: + (S19 0: 1: 2:)     
    U8   txBusyLock;      //BCL          0:       1:   

    U8   keyAutoLock;     //AUTOLK   0:       1:    S19:OFF/5/10/15
    U8   alarmMode;       //ALMOD        0:  1:    2: 
    U8   alarmLocal;      // 0:       1: 
    U8   dualTxMode;      //TXAB         0:       1: A   2: B   3: C
    U8   tailSwitch;      //STE          0:       1: 
    U8   rpste;           //RPSTE  0-1000MS100MS:0 1 2 3 .... 10 0 
    U8   rptrl;           //RPTRL  0-1000MS100MS:0 1 2 3 .... 10 0     
    U8   txOffTone;       //ROGER 0:OFF 1:STANDARD 2-8:custom patterns 9:ECHO 10:CHIRP 11:REVERSE 12:RADIO 13:SIGNATURE

    U8   switchAB;        //     0:B       1:A
    U8   fmEnale;         //FM  1: 0:
    UNION_VM chOrVfoMode;    //4B 4A
    U8   keyLock;         //LOCK       0:       1: 
    UNION_FLAG2  OpFlag1;    //bit0~1:  :0:: 1:(logo)  2:2 3: 
                             //bit2~3:  : 0: 1:  2:
    U8   rtone;           //1750HzTone             
    U8   weatheSwitch;    // 
    U8   weatherAlert;    // 

    U8   voxDelay;        // 0.5S -- 2.0S 0.1S
    U8   menuExitTime;    //
    U8   remain0[6];      //

    U8   toa;             // 0-10S
    U8   brightness;      //
    U8   DisplayStyles;   //
    U8   scanCtcsMode;    //
    U16  vfoScanRangeL;   //
    U16  vfoScanRangeH;   //

    U8   fmInterrupt;     //  0:  1:
    U8   txForbid;        // 0: 1:
    U8   userSideKey[4];  //4
    U8   weatherNum;      //
    U8   menuSet;         // bit0: bit1: GPS()

    U8   hangUpTime;      //
    U8   signalType;      // 0:DTMF 1: 2TONE  2:5TONE
    U8   voxSwitch;       //, 0: 1:
    U8   remain1;         
    U8   pwrPwdFlag;      //
    U8   pwrPassword[3];  //6,60

}STR_RADIOINFORM;  

/*----------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    U8  alarmStates;              // 
    U8  toneFlag;                 //
    U16 alarmFreq;                //
    U16 freqSwTime;               //
    U16 ledFlashTime;             //LED
    U16 alarmTime;                //
}STR_ALARM;

/***********************************************************************************/
typedef struct
{
    U16  FmCurFreq;    //
    U16  FmCHs[30];    //
    U8   fmChNum;      //
    U8   fmChVfo;      //
} __attribute__( ( packed ) )STR_FMINFOS;

/*----------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    U8  moduleType;          
    U8  txEn220M;            //220M  220-260M
    U8  txEn350M;            //350M  350-390M
    U8  txEn520M;            //520M  480-520M
    U8  amRxEn;              // 
}STR_RF_MODELE;

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)		( ( ((hex) >> 4) * 10 ) + ((hex) & 0x0f) )
#endif

