#include "includes.h"

STR_REMOTESCANQT g_ScanQTInfo;

extern void EnterRemoteScanQTMode(void)
{
    // 
    DualStandbyWorkOFF();

    // 
    if (g_sysRunPara.sysRunMode == MODE_MENU)
    {
        Menu_ExitMode();
    }
    ResetInputBuf();

    g_sysRunPara.sysRunMode = MODE_SCAN_QT;
    memset(&g_ScanQTInfo, 0, sizeof(g_ScanQTInfo));
    g_ScanQTInfo.timeOut = 30;
    g_ScanQTInfo.state = SCANQT_STEPUP;

    QTScanDisplayHome();
}

extern void ExitRemoteScanQTMode(void)
{
    Rfic_ScanQT_Disable();
    g_sysRunPara.sysRunMode = MODE_MAIN;
    ResetInputBuf();
    DualStandbyWorkOFF();

    // 
    DisplayRadioHome();
}

extern void TaskRemoteScanQT(void)
{
    static U8 sqCnt = 0;

    if (g_sysRunPara.sysRunMode != MODE_SCAN_QT)
    {
        return;
    }

    switch (g_ScanQTInfo.state)
    {
    case SCANQT_OFF:
        break;

    case SCANQT_STEPUP:
        if (Rfic_GetSQLinkState() == FALSE)
        {
            sqCnt = 0;
            break;
        }
        else
        {
            if (sqCnt < 5)
            {
                sqCnt++;
                break;
            }
        }

        Rfic_ScanQT_Enable(g_ScanQTInfo.dcsInverted);
        QTScanDisplayStatus(1);
        sqCnt = 0;
        g_ScanQTInfo.state = SCANQT_WAIT;
        break;

    case SCANQT_WAIT:
        if (Rfic_GetSQLinkState() == FALSE)
        {
            if (sqCnt < 5)
            {
                sqCnt++;
                break;
            }
            else
            {
                QTScanDisplayStatus(0);
                g_ScanQTInfo.state = SCANQT_STEPUP;
                break;
            }
        }
        else
        {
            sqCnt = 0;
        }

        if (g_ScanQTInfo.timeOut != 0)
        {
            g_ScanQTInfo.timeOut--;
        }
        else
        {
            g_ScanQTInfo.dcsInverted = !g_ScanQTInfo.dcsInverted;
            g_ScanQTInfo.timeOut = 30;
            g_ScanQTInfo.state = SCANQT_STEPUP;
            break;
        }

        g_ScanQTInfo.dcsCtsDat = Rfic_GetCtsDcsData();
        if (g_ScanQTInfo.dcsCtsDat != 0)
        {
            g_ScanQTInfo.dcsCtsType = Rfic_GetSCtsDcsType();
            if (g_ScanQTInfo.dcsCtsType > SUBAUDIO_CTS &&
                g_ScanQTInfo.dcsInverted)
            {
                g_ScanQTInfo.dcsCtsType = SUBAUDIO_DCS_I;
            }
            if (g_ScanQTInfo.dcsCtsType == SUBAUDIO_CTS)
            {
                g_ScanQTInfo.dcsCtsDat = g_ScanQTInfo.dcsCtsDat * 10 * 10000 / 206489;
                if (g_ScanQTInfo.dcsCtsDat > 600)
                {
                    g_ScanQTInfo.dcsCtsDat =
                        CheckIsStandardCTCSS(g_ScanQTInfo.dcsCtsDat);
                    if (g_ScanQTInfo.dcsCtsDat != 0)
                    {
                        LCD_BackLightSetOn();
                        ResetTimeKeyLockAndPowerSave();
                        QTScanDisplay(SUBAUDIO_CTS,
                                      g_ScanQTInfo.dcsCtsDat, 0);
                    }
                    else
                    {
                        g_ScanQTInfo.dcsCtsType = SUBAUDIO_NONE;
                    }
                }
                else
                {
                    QTScanDisplay(SUBAUDIO_NONE, 0, 0);
                    g_ScanQTInfo.dcsCtsType = SUBAUDIO_NONE;
                }
            }
            else
            {
                U32 tempDCS;

                tempDCS = CheckIsStandardDCS(g_ScanQTInfo.dcsCtsDat);
                if (tempDCS != 0)
                {
                    g_ScanQTInfo.dcsCtsDat = tempDCS;
                    g_ScanQTInfo.dcsIndex = searchFreqImofs.CtsResult;
                    if (g_ScanQTInfo.dcsCtsType == SUBAUDIO_DCS_I)
                    {
                        g_ScanQTInfo.dcsIndex += 105;
                    }
                    g_ScanQTInfo.isStandarDCS = 1;
                    LCD_BackLightSetOn();
                    ResetTimeKeyLockAndPowerSave();
                    QTScanDisplay(g_ScanQTInfo.dcsCtsType,
                                  g_ScanQTInfo.dcsCtsDat, 1);
                    g_ScanQTInfo.state = SCANQT_STOP;
                }
                else
                {
                    g_ScanQTInfo.dcsCtsType = SUBAUDIO_NONE;
                    g_ScanQTInfo.dcsCtsDat = 0;
                    g_ScanQTInfo.dcsIndex = 0;
                    g_ScanQTInfo.isStandarDCS = 0;
                    QTScanDisplay(SUBAUDIO_NONE, 0, 0);
                }
            }

            if (g_ScanQTInfo.dcsCtsType == SUBAUDIO_CTS ||
                g_ScanQTInfo.isStandarDCS == 1)
            {
                g_ScanQTInfo.state = SCANQT_STOP;
            }
        }

        break;

    case SCANQT_STOP:

        break;
    }
}

extern void SaveQTScanResult(void)
{
    if (g_ScanQTInfo.dcsCtsType == SUBAUDIO_CTS)
    {
        if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].chVfoMode == VFO_MODE)
        {
            g_ChannelVfoInfo.vfoInfo[g_ChannelVfoInfo.switchAB].rxDCSCTSNum = g_ScanQTInfo.dcsCtsDat;
            g_ChannelVfoInfo.vfoInfo[g_ChannelVfoInfo.switchAB].vfoFlag.Byte &= 0xFE;
        }
        else
        {
            g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].rxDCSCTSNum = g_ScanQTInfo.dcsCtsDat;
            g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].chFlag3.Byte &= 0xFE;
        }
    }
    else if (g_ScanQTInfo.dcsCtsType > SUBAUDIO_CTS)
    {
        if (g_ScanQTInfo.isStandarDCS == 1)
        {
            if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].chVfoMode == VFO_MODE)
            {
                if (g_ScanQTInfo.dcsIndex < 211)
                {                                                                             // 
                    g_ChannelVfoInfo.vfoInfo[g_ChannelVfoInfo.switchAB].vfoFlag.Byte &= 0xFE; // 
                    g_ChannelVfoInfo.vfoInfo[g_ChannelVfoInfo.switchAB].rxDCSCTSNum = g_ScanQTInfo.dcsIndex;
                }
            }
            else
            {
                if (g_ScanQTInfo.dcsIndex < 211)
                {                                                                                 // 
                    g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].chFlag3.Byte &= 0xFE; // 
                    g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].rxDCSCTSNum = g_ScanQTInfo.dcsIndex;
                }
            }
        }
    }
    ChannleVfoDataInit(g_ChannelVfoInfo.switchAB, 0);

    if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].chVfoMode == CHAN_MODE)
    {
        Flash_SaveChannelData(g_ChannelVfoInfo.currentChannelNum, (U8 *)&g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].rxFreq, g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].channelName);
    }
    else
    {
        Flash_SaveVfoData(g_ChannelVfoInfo.switchAB);
    }
}

extern void KeyProcess_ScanQt(U8 keyEvent)
{
    switch (keyEvent)
    {
    case KEYID_MENU:
        if (g_ScanQTInfo.state == SCANQT_STOP)
        {
            SaveQTScanResult();
            ExitRemoteScanQTMode();
            VoiceBroadcastWithBeepLock(vo_Confirm, BEEP_FASTSW);
        }
        else
        {
            BeepOut(BEEP_ERROR);
        }
        break;
    case KEYID_UP:
    case KEYID_DOWN:
        QTScanDisplayStatus(0);
        g_ScanQTInfo.state = SCANQT_STEPUP;
        break;

    case KEYID_EXIT:
        ExitRemoteScanQTMode();
        break;

    case KEYID_SIDEKEY1:
    case KEYID_SIDEKEY2:
    case KEYID_SIDEKEYL1:
        keyEvent = Sidekey_GetRemapEvent(keyEvent);
        if (keyEvent != KEYID_LIGHT)
        {
            keyEvent = KEYID_NONE;
        }
        SideKey_Process(keyEvent);
        break;

    default:
        BeepOut(BEEP_NULL);
        break;
    }
}
