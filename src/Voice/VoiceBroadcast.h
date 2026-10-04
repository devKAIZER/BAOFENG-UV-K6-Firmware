#ifndef __VOICEBROADCAST_H
    #define __VOICEBROADCAST_H

/******************************************************************************/

#include "VoiceIndex_Girl.h"

typedef struct
{
    U32 length;          //
    U32 dataAddr;        //
}STR_VOICE_INDEX;

//DMA
typedef struct
{
    U32 logicAddr;       //
    U32 usedLen;         //
    volatile U8  finishFlag;      //
    volatile U8  dmaBufUsed;      //
    volatile U8  dmaBufAUseFlag;  //
    volatile U8  dmaBufBUseFlag;  //
    U16 dmaBufA[1024];
    U16 dmaBufB[1024];
    U8  lastPackage;
}STR_VOICE_PLAY;

typedef struct
{
    STR_VOICE_INDEX voiceIndex;
    STR_VOICE_PLAY voicePlay;
}STR_VOICE_ONFO;

//
typedef struct
{
    U8  voiceState;     // 
    U8  busyFlag;    //
    U8  voiceCnt;       //
    U8  voiceBuf[6];    //
}STR_VOICE;

extern STR_VOICE voice;
extern STR_VOICE_ONFO g_voiceInform;
extern U8 FastChangeVoice;

extern void VoiceOutput_Interrupt(void);
extern void AudioHard_Init(void);

extern void Audio_PlayVoice(U8 Data);
extern void Audio_PlayVoiceLock(U8 Data);
extern void Audio_PlayNumInQueue(U8 Data);
extern void Audio_PlayChanNum(U8 Data);	

extern U8 Audio_CheckBusy(void);
extern void Audio_PlayStop(void);
extern void Audio_PlayTask(void);
extern void VoiceBroadcastWithBeepLock(U8 voiceDat,ENUM_BEEPMODE beepData);

#endif
