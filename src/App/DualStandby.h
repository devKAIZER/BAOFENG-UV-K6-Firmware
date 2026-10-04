#ifndef __DUALSTANDBY_H
#define __DUALSTANDBY_H

typedef struct
{
    U8 dualRxFlag;     // ,
    U8 dualOnFlag;     // 
    U8 dualRxTime;     // 
    U8 UpdateFalg;     // 
    U8 dualResumeFlag; // 
    U8 dualResumeTime; // N
} STR_DUAL;

extern STR_DUAL dualStandby;

extern void DualChannelSwitch2Main(void);
extern void DualStandbyWorkON(void);
extern void DualStandbyWorkOFF(void);
extern void ResetDualRxTime(void);
extern void DualStandbyTask(void);

#endif
