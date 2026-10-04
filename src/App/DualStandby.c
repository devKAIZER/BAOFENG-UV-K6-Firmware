#include "includes.h"

STR_DUAL dualStandby;

extern void DualChannelSwitch2Main(void)
{
    g_CurrentVfo = &g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB];
    g_ChannelVfoInfo.dualAB = g_ChannelVfoInfo.switchAB;
    dualStandby.dualRxFlag = OFF;
}

extern void DualStandbyWorkON(void)
{
    if ((g_radioInform.dualRxFlag == 1) && (alarmDat.alarmStates == 0))
    {
        dualStandby.dualOnFlag = ON;
        dualStandby.UpdateFalg = OFF;
    }
}

extern void DualStandbyWorkOFF(void)
{
    if (dualStandby.dualRxFlag == ON)
    {
        dualStandby.UpdateFalg = OFF;
    }
    // 
    DualChannelSwitch2Main();
    g_ChannelVfoInfo.currentChannelNum = g_ChannelVfoInfo.channelNum[g_ChannelVfoInfo.switchAB];

    // 
    dualStandby.dualOnFlag = OFF;
    g_rfRxState = RX_READY;
}

extern void ResetDualRxTime(void)
{
    dualStandby.dualRxTime = 100;
}

extern void DualStandbyTask(void)
{

    if (dualStandby.dualOnFlag == OFF || dualStandby.dualRxTime)
    { // 
        return;
    }
    if (DtmfGetMatchStatue())
    {
        return;
    }

    dualStandby.dualRxTime = 100;

    if (g_rfRxState != GET_CALL)
    { // Wait Rx Mode
        return;
    }

    if (CheckPowerBusy() == ON)
    { // 
        return;
    }
    if (dualStandby.dualRxFlag == ON)
    {
        dualStandby.dualRxFlag = OFF;
        g_ChannelVfoInfo.dualAB = g_ChannelVfoInfo.switchAB;
    }
    else
    {
        dualStandby.dualRxFlag = ON;
        g_ChannelVfoInfo.dualAB = (g_ChannelVfoInfo.switchAB + 1) & 1;
    }
    g_CurrentVfo = &g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.dualAB];
    g_rfRxState = RX_READY;
}
