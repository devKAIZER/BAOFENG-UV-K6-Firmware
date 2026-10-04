#ifndef __APPFM_H
#define __APPFM_H

// FM
#define FM_FREQSW_TIME 10                 // 10ms
#define FM_SEEK_TIMEOUT 1000              //  10S
#define FM_SEEK_TIME FM_SEEK_TIMEOUT - 20 // 
#define FM_RETURN_TIME 200                // 

#define FM_MAX_CH_NUM 30 // 

// 
enum
{
    FM_STOP = 0,
    FM_SLEEP,
    FM_READY,
    FM_SEEK,
    FM_PLAY
};
typedef struct
{
    U8 mode;        // 
    U8 band;        //  0:76-108  1:65-76
    U16 freq;       // 
    U16 timeOut;    // 
    U8 fmChList[4]; // 
    U8 fmChActive;  // 
} STR_FMSTATE;

extern STR_FMSTATE fmInfo;

extern Boolean CheckFmChActive(U8 curChanNum);
extern void ResumeFmMode(void);
extern void FmBandConfig(void);
extern Boolean CheckFmVfoMode(void);
extern void FmCheckChannelActive(void);
extern void FmCheckTimeOut(void);
extern void FmEnterSleepMode(void);
extern void FMSwitchExit(void);
extern void EnterFmMode(void);
extern void ExitFmMode(void);
extern void FmTaskFunc(void);
extern void ResetFmSleepTime(void);
extern void KeyProcess_Fm(U8 keyEvent);

#endif
