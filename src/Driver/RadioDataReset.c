#include "includes.h"

const U8  RADIO_INFORM_DEFAULT[64] = 
{
    3, //     0 - 9
	1, //     0:   1. 1:1  2. 1:2  3. 1:3  4. 1:4
	0, // VOX 0  1 - 9
	3, //     0 - 5s
	1, //         0:   1: 
	8, // TOT         0 - 180s( 15s),  0 - 12,  0 
	1, // beep      0:   1: 
	1, //     0:   1: 
    0, //reserved (unused display/voice language selector)
	0, // DTMF    0:   1: 2:  3:  + 
	1, //     0:   1:   2:    :       
	0, // PTTID       0:     1: BOT()   2: EOT()   3:   : 
	5, // PTTLTID  0-301   
	1, // MDFA A  00: +  01: +
	1, // MDFB B  00: +  01: +
	0, // BCL          0:       1: 
	0, // AUTOLK   0:       1: 
	0, // ALMOD        0:     1:    2: 
	1, //  0:       1: 
	0, //      0:       1: A   2: B
	1, //      0:       1: 
	5, // 	0-1000MS100MS:0 1 2 3 .... 10 0 
	5, // 	0-1000MS100MS:0 1 2 3 .... 10 0     
	0, // 	0:       1:  
	1, //  	0:B	     1:A	
	0, // FM  0:	   1:
    0x11,//      0:       1: 
	0, // LOCK   	0:       1: 
    0, //  0: 1:
	2, // rtone
    0, //                
    0, //   

    5,// 0.5S -- 2.0S 0.1S 
    0,//                   
    0,
    0,  
    0, 
    0,// 
    0x00,0x00, // 

    0,//
    3,//                       
    0,//                       
    0,//                                
    0x90,0x01,// 400                  
    0xD6,0x01,// 470    

    0,                      
    0,                 
    1,5,6,0,//4  
    0,//
    0x01, //

    0xFF, 
    0X00, // 0:DTMF 1: 2TONE  2:5TONE
    0,    //, 0: 1: 
    0xFF, //8  GPS
    0,    //, 0: 1: 
    0X00, 0X00, 0X00, //60
};

const U8  DTMF_INFORM_DEFAULT[] =
{
    0X01, 0X02, 0X03, 0XFF, 0XFF, // ID
    0x00,
    0x00,
    0x03,
    0x03,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const U8  DTMF_CODE_DEFAULT[] = 
{
    0X08, 0X00, 0X08, 0X00, 0X01, 0XFF, 0XFF, 0XFF
};

const U8  CHANNEL_1_DEFAULT_DATA[20] = 
{
    0X00, 0X25, 0X76, 0X46, 0X00, 0X25, 0X76, 0X46, 
    0X00, 0X00, 0X00, 0X00, 
    0X00, 
    0X00, 
    0X00, 
    0X02,
    0X00, 0X00, 0X00, 0X00, 
};

const U8  CHANNEL_128_DEFAULT_DATA[20] = 
{
    0X00, 0X75, 0X56, 0X14, 0X00, 0X75, 0X56, 0X14, // 
    0X00, 0X00, 0X00, 0X00,                         // 
    0X00,                                           // 
    0X00,                                           // PTTID:  0 1BOT 2EOT 3BOTH
    0X00,                                           //   0   1
    0X02,                                           // BIT6  0:   1:  //BIT1 0:  1:
    0X00, 0X00, 0X00, 0X00, 
};

const U8  VFO_A_DEFAULT_DATA[32] = 
{
   4, 3, 5, 6, 2, 5, 0, 0,                          // 
   0X00, 0X00, 0X00, 0X00,                          // 
   0x00,                                            // 10
   0x00,                                            // 
   0X00,                                            // BIT4 + BIT5 -   BIT0-BIT3:
   0X00,                                            // 
   0X00,                                            //  0:    1:
   0X00,                                            // BIT6:   0:  1:
   0X01,                                            //   1:UHF   0:VHF
   0X00,                                            // : 0 - 7
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,              // :
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00               // 
};

const U8  VFO_B_DEFAULT_DATA[32] =
{
   1, 4, 5, 5, 2, 5, 0, 0,                          // 
   0X00, 0X00, 0X00, 0X00,                          // 
   0x00,                                            // 10
   0x00,                                            // 
   0X00,                                            // BIT4 + BIT5 -   BIT0-BIT3:
   0X00,                                            // 
   0X00,                                            //  0:    1:
   0X00,                                            // BIT6:   0:  1:
   0X00,                                            //   1:UHF   0:VHF
   0X00,                                            // : 0 - 7
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,              // :
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00               // 
};

const U8  ChFreqTbl[21][8] = 
{
    {0X00, 0X25, 0X49, 0X14, 0X00, 0X25, 0X49, 0X14}, // 
    {0X00, 0X25, 0X45, 0X14, 0X00, 0X25, 0X45, 0X14},
    {0X00, 0X25, 0X51, 0X14, 0X00, 0X25, 0X51, 0X14},
    {0X00, 0X25, 0X55, 0X14, 0X00, 0X25, 0X55, 0X14},
    {0X00, 0X85, 0X59, 0X14, 0X00, 0X85, 0X59, 0X14},
    {0X00, 0X25, 0X02, 0X43, 0X00, 0X25, 0X02, 0X43},
    {0X00, 0X25, 0X12, 0X43, 0X00, 0X25, 0X12, 0X43},
    {0X00, 0X25, 0X22, 0X43, 0X00, 0X25, 0X22, 0X43},
    {0X00, 0X25, 0X32, 0X43, 0X00, 0X25, 0X32, 0X43},
    {0X00, 0X25, 0X42, 0X43, 0X00, 0X25, 0X42, 0X43},
    {0X00, 0X25, 0X52, 0X43, 0X00, 0X25, 0X52, 0X43},
    {0X00, 0X25, 0X62, 0X43, 0X00, 0X25, 0X62, 0X43},
    {0X00, 0X25, 0X72, 0X43, 0X00, 0X25, 0X72, 0X43},
    {0X00, 0X25, 0X82, 0X43, 0X00, 0X25, 0X82, 0X43},
    {0X00, 0X25, 0X92, 0X43, 0X00, 0X25, 0X92, 0X43}, 
    {0X00, 0X75, 0X99, 0X43, 0X00, 0X75, 0X99, 0X43}, 
    {0X00, 0X25, 0X15, 0X43, 0X00, 0X25, 0X15, 0X43}, 
    {0X00, 0X25, 0X25, 0X43, 0X00, 0X25, 0X25, 0X43}, 
    {0X00, 0X25, 0X35, 0X43, 0X00, 0X25, 0X35, 0X43},
    {0X00, 0X25, 0X45, 0X43, 0X00, 0X25, 0X45, 0X43},
    {0X00, 0X25, 0X55, 0X43, 0X00, 0X25, 0X55, 0X43}, 
};
extern void Reset21Chans(void)
{
    U8  writeBuf[32],i;
    U32 addr = CHAN_ADDR;

    //
    SpiFlash_Erase32kBlock(CHAN_ADDR);

    memset(writeBuf,0x00,32);

    //
    writeBuf[14] = 0X00;
    writeBuf[15] = 0X06;
    for(i=0;i<21;i++)
    {
        writeBuf[12] = i % 20;
        memcpy(writeBuf,ChFreqTbl[i],8);
        if(i >= 16)
        {
            writeBuf[14] = 0X01;
        }
        SpiFlash_WriteBytes(addr, writeBuf, 32);
        addr += 32;
    }
}

/*********************************************************************
*   : ResetChannelData
* : 
* : 
* 
* :
* : 
*     
***********************************************************************/
extern void ResetChannelData(void)
{
    Reset21Chans();

    g_ChannelVfoInfo.channelNum[0] = 0;
    g_ChannelVfoInfo.channelNum[1] = 20;
    Flash_SaveSystemRunData();
}

/*********************************************************************
*   : ResetVfoModeData
* : 
* : 
* 
* :
* : 
*     
***********************************************************************/
extern void ResetVfoModeData(void)
{
    memcpy(g_ChannelVfoInfo.vfoInfo[0].freq,VFO_A_DEFAULT_DATA, 32);
    memcpy(g_ChannelVfoInfo.vfoInfo[1].freq,VFO_B_DEFAULT_DATA, 32);    

    Flash_SaveVfoData(4);
}

/*********************************************************************
*   : ResetRadioFunData
* : 
* : 
* 
* : 
* : 
*     
***********************************************************************/
extern void ResetRadioFunData(void)
{
    U8  i;
    U32 addr;
    U8  writeBuf[16] = {0x00};

    memcpy((U8  *)&g_radioInform.sqlLevel,RADIO_INFORM_DEFAULT, sizeof(STR_RADIOINFORM));
    memset(powerOnMsg,0xFF,16);

    Flash_SaveRadioImfosData();

    SpiFlash_EraseSector(DTMFINFOR_ADDR);
    SpiFlash_WriteBytes( DTMFINFOR_ADDR, DTMF_INFORM_DEFAULT, sizeof(DTMF_INFORM_DEFAULT));

    addr = DTMF_CODE_ADDR;
    memcpy(writeBuf,DTMF_CODE_DEFAULT,sizeof(DTMF_CODE_DEFAULT));
    for(i=1;i<21;i++)
    {
        if( i < 10)
        {
            writeBuf[4] = i;
        }
        else
        {
            writeBuf[4] = i % 10;
            writeBuf[3] = i / 10;
        }
        SpiFlash_WriteBytes( addr,writeBuf,sizeof(DTMF_CODE_DEFAULT));
        addr += 16;
    }

}
/*********************************************************************
*   : ResetRadioData
* : 
* : 
* 
* :
* : 
*     
***********************************************************************/
extern void ResetRadioData(void)
{
    ResetChannelData();
    ResetVfoModeData();
	ResetRadioFunData();
}

