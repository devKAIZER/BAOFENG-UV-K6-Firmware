#include "includes.h"

static U8 periodSqlLevel = 0xff;
static U8 sqCnt = 0;
static U8 rogerToneStage = 0;
static U8 rogerToneTicks = 0;
static U8 rogerPatternIndex = 0;
static U8 rogerPatternCount = 0;
static U8 rogerPatternInGap = 0;
static U8 rogerPatternMode = 0;
static U8 totEndPending = 0;

typedef struct
{
    U16 frequency;
    U8 durationTicks;
    U8 gapTicks;
} STR_ROGER_TONE;

static const STR_ROGER_TONE RogerClassic[] =
{
    {F1200HZ, 10, 3},
    {F900HZ, 15, 0}
};
static const STR_ROGER_TONE RogerDouble[] =
{
    {F1000HZ, 10, 5},
    {F1000HZ, 10, 0}
};
static const STR_ROGER_TONE RogerDescend[] =
{
    {F1200HZ, 10, 3},
    {F1000HZ, 10, 3},
    {F800HZ, 15, 0}
};
static const STR_ROGER_TONE RogerAscend[] =
{
    {F800HZ, 10, 3},
    {F1000HZ, 10, 3},
    {F1200HZ, 15, 0}
};
static const STR_ROGER_TONE RogerTwoTone[] =
{
    {F1000HZ, 15, 5},
    {F1400HZ, 20, 0}
};
static const STR_ROGER_TONE RogerTriple[] =
{
    {F1000HZ, 8, 4},
    {F1000HZ, 8, 4},
    {F1000HZ, 15, 0}
};
static const STR_ROGER_TONE RogerRadio[] =
{
    {F1200HZ, 8, 5},
    {F1800HZ, 8, 5},
    {F1200HZ, 15, 0}
};
static const STR_ROGER_TONE RogerEcho[] =
{
    {F1400HZ, 7, 5},
    {F900HZ, 22, 0}
};
static const STR_ROGER_TONE RogerChirp[] =
{
    {F800HZ, 6, 2},
    {F1000HZ, 6, 2},
    {F1200HZ, 6, 2},
    {F1400HZ, 10, 0}
};
static const STR_ROGER_TONE RogerReverseChirp[] =
{
    {F1400HZ, 6, 2},
    {F1200HZ, 6, 2},
    {F1000HZ, 6, 2},
    {F800HZ, 10, 0}
};
static const STR_ROGER_TONE RogerRadioExtended[] =
{
    {F1200HZ, 10, 4},
    {F1500HZ, 10, 4},
    {F900HZ, 22, 0}
};
static const STR_ROGER_TONE RogerSignature[] =
{
    {F1400HZ, 7, 3},
    {F900HZ, 7, 3},
    {F1400HZ, 7, 3},
    {F900HZ, 16, 0}
};

static const STR_ROGER_TONE *RF_GetRogerPattern(U8 mode, U8 *count);

extern void GetHardWorkBand(U16 freq)
{
    if ((freq >= bandRang.bandFreq.vhfL) &&
        (freq < bandRang.bandFreq.vhfH))
    {
        g_ChannelVfoInfo.BandFlag = FREQ_BAND_VHF;
    }
    else if ((freq >= bandRang.bandFreq.vhf2L) && (freq < bandRang.bandFreq.vhf2H))
    {
        g_ChannelVfoInfo.BandFlag = FREQ_BAND_200M;
    }
    else if ((freq >= bandRang.bandFreq.B350ML) && (freq < bandRang.bandFreq.B350MH))
    {
        g_ChannelVfoInfo.BandFlag = FREQ_BAND_350M;
    }
    else if ((freq >= bandRang.bandFreq.uhfL) && (freq < bandRang.bandFreq.uhfH))
    {
        g_ChannelVfoInfo.BandFlag = FREQ_BAND_UHF;
    }
}
const U16 TxCheckFreq[][6] =
    {
        {1360, 1740, 4000, 4800, 2200, 2550}, // 
        {1440, 1480, 2220, 2250, 4200, 4500}, //  FCC 
        {1440, 1480, 4300, 4500, 4300, 4500}, //  IC  02
        {1440, 1460, 4300, 4400, 4300, 4400}, //  CE     03
        {1360, 1740, 4000, 4800, 4000, 4800}, // 04 IAN Amateur
        {1440, 1480, 4300, 4400, 4300, 4400}, //  05
};

Boolean CheckCanTxOverRange(U32 freq)
{
    U32 tempFreq;

    if (g_rfMoudel.txEn520M && (freq >= 48000000 && freq <= 52000000))
    {
        return TRUE;
    }

    if (g_sysRunPara.moduleType <= 1)
    {
        tempFreq = freq / 10000;

        if (g_rfMoudel.txEn220M && (tempFreq >= TxCheckFreq[g_sysRunPara.moduleType][4] && tempFreq < TxCheckFreq[g_sysRunPara.moduleType][5]))
        {
            return TRUE;
        }
    }

    return FALSE;
}
Boolean CheckFreqInTxFreqRange(U32 freq)
{
    U32 tempFreq;

    tempFreq = freq / 10000;

    // 
    GetHardWorkBand(tempFreq);

    if (CheckCanTxOverRange(freq) == TRUE)
    {
        return TRUE;
    }

    if (g_sysRunPara.moduleType <= 1)
    {
        if ((g_rfMoudel.txEn220M == 0) && (tempFreq >= TxCheckFreq[g_sysRunPara.moduleType][4] && tempFreq < TxCheckFreq[g_sysRunPara.moduleType][5]))
        { // 220M
            return FALSE;
        }
    }

    // 
    if (((tempFreq >= TxCheckFreq[g_sysRunPara.moduleType][0]) && (tempFreq < TxCheckFreq[g_sysRunPara.moduleType][1])) || ((tempFreq >= TxCheckFreq[g_sysRunPara.moduleType][2]) && (tempFreq < TxCheckFreq[g_sysRunPara.moduleType][3])) || ((tempFreq >= TxCheckFreq[g_sysRunPara.moduleType][4]) && (tempFreq < TxCheckFreq[g_sysRunPara.moduleType][5])))
    {
        return TRUE;
    }

    if ((tempFreq >= bandRang.bandFreq.uhfL) && (tempFreq < bandRang.bandFreq.uhfH))
    {
        return TRUE;
    }

    if ((tempFreq >= bandRang.bandFreq.B350ML) && (tempFreq < bandRang.bandFreq.B350MH))
    {
        return TRUE;
    }
    if ((tempFreq >= bandRang.bandFreq.vhf2L) && (tempFreq < bandRang.bandFreq.vhf2H))
    {
        return TRUE;
    }
    if ((tempFreq >= bandRang.bandFreq.vhfL) && (tempFreq < bandRang.bandFreq.vhfH))
    {
        return TRUE;
    }

    return FALSE;
}

void WaitPttRelease(void)
{
    Rfic_RxTxOnOffSetup(RFIC_RXON);

    Rfic_SetToneFreq(F480HZ);
    Rfic_TxSingleTone_On(0);
    SpeakerSwitch(ON);
    beepDat.beepTime = 260;
    beepDat.beepCnt = 1;

    while (PTT_GetKeyVal() == 0)
    {
        if (beepDat.beepTime == 0)
        {
            if (beepDat.beepCnt == 1)
            {
                beepDat.beepCnt = 0;
                Rfic_SetToneFreq(0);
            }
            else
            {
                beepDat.beepCnt = 1;
                Rfic_SetToneFreq(F480HZ);
            }
            beepDat.beepTime = 260;
        }
    }
    SpeakerSwitch(OFF);
    DelayMs(30);
    Rfic_TxSingleTone_Off();
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
}

extern void Radio_EnterTxMode(void)
{
    U8 beepFlag = 0, txFlag;

    ClearDisANIFlag();
    GetDtmfEditCode();

    ExitAllFunction(0);
    if (g_sysRunPara.sysRunMode == MODE_SCAN)
    {
        if (g_scanInfo.state != WAIT_RECALL)
        {
            ChannelNumChangeRead(0, 1);
            g_scanInfo.state = SCAN_IDLE;
            g_scanInfo.scanTime = 0;
            g_sysRunPara.sysRunMode = MODE_MAIN;
        }
    }

    if (g_sysRunPara.moniFlag)
    {
        ExitMoniMode();
    }

    DualStandbyWorkOFF();

    txFlag = CheckFreqInTxFreqRange(g_CurrentVfo->freqTx.frequency);

    if ((g_CurrentVfo->busyLock && g_sysRunPara.rfRxFlag.rxReceiveOn == ON) || g_radioInform.txForbid)
    { // 
        beepFlag = 1;
    }
    else if (CheckBatteryCanTx() == TRUE && txFlag == TRUE && g_sysRunPara.rfTxFlag.txEnable[g_ChannelVfoInfo.BandFlag] == 1)
    {
        g_rfState = RF_TX;
        g_rfTxState = TX_READY;
    }
    else
    {
        beepFlag = 1;
    }

    if (beepFlag)
    {
        WaitPttRelease();
        ResetTimeKeyLockAndPowerSave();
        ResetDtmfEditCode();
        return;
    }

    DisplayTxMode();
}

extern void RxReset(void)
{
    LedRxSwitch(LED_OFF);
    Rfic_SetAfout(OFF);
    SpeakerSwitch(OFF);

    g_rfRxState = RX_READY;
    g_sysRunPara.rfRxFlag.rxReceived = OFF;
    g_sysRunPara.rfRxFlag.rxReceiveOn = OFF;
    ResetTimeKeyLockAndPowerSave();
}

extern void Radio_SwitchBand(void)
{
    if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].chVfoMode == CHAN_MODE)
    {
        return;
    }

    U32 freq;
    U32 freqBand;
    U32 newFreq;

    freq = g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].freqRx.frequency;

    freqBand = freq / 10000;

    if (freqBand >= bandRang.bandFreq.vhfL && freqBand < bandRang.bandFreq.vhfH)
    {
        newFreq = bandRang.bandFreq.freqV2L;
    }

    else if (freqBand >= bandRang.bandFreq.vhf2L &&
             freqBand < bandRang.bandFreq.vhf2H)
    {
        newFreq = bandRang.bandFreq.freq350ML;
    }

    else if (freqBand >= bandRang.bandFreq.B350ML &&
             freqBand < bandRang.bandFreq.B350MH)
    {
        newFreq = bandRang.bandFreq.freqUL;
    }
    else if (freqBand >= bandRang.bandFreq.uhfL &&
             freqBand < bandRang.bandFreq.uhfH)
    {
        newFreq = bandRang.bandFreq.freqVL;
    }
    else
    {
        return;
    }

    g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
        .freqRx.frequency = newFreq;

    if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].freqDir == 1)
    {
        g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
            .freqTx.frequency =
            newFreq +
            g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
                .freqOffset;
    }
    else if (g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].freqDir == 2)
    {
        g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
            .freqTx.frequency =
            newFreq -
            g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
                .freqOffset;
    }
    else
    {
        g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB]
            .freqTx.frequency = newFreq;
    }

    VfoFrequency2Buf(
        newFreq,
        g_ChannelVfoInfo.vfoInfo[g_ChannelVfoInfo.switchAB].freq,
        8);

    GetHardWorkBand(newFreq / 10000);

    RxReset();

    DisplayRadioHome();

    BeepOut(BEEP_FASTSW);
}

extern void RfOff(void)
{
    LedTxSwitch(LED_OFF);
    LedRxSwitch(LED_OFF);
    RF_PowerSet(g_ChannelVfoInfo.BandFlag, PWR_OFF);
    SpeakerSwitch(OFF);
    Rfic_SetAfout(OFF);
}

extern void RF_TxEnd(void)
{
    LedTxSwitch(LED_OFF);

    if (g_CurrentVfo->pttIdMode != 0)
    {
        DtmfRstMatchTimer(1);
    }

    g_rfTxState = TX_STOP;
    g_sysRunPara.rfTxFlag.totTime = 0;
    g_sysRunPara.rfTxFlag.voxDetDly = 10;
    g_sysRunPara.rfTxFlag.voxWorkDly = 0;
    g_rfRxState = RX_READY;

    if (g_radioInform.rptrl)
    {
        g_sysRunPara.rfTxFlag.relayTailSetTime = g_radioInform.rptrl + 2;
    }
}

extern void RF_TxRoger(void)
{
    if (g_radioInform.txOffTone == 1)
    {
        if (alarmDat.alarmStates)
        {
            DtmfSendTxOver();
        }
        else
        {
            rogerToneStage = 1;
            rogerToneTicks = 8;
            Rfic_TxSingleTone_On(1);
            Rfic_SetToneFreq(F1000HZ);
            g_rfTxState = TX_ROGER_BEEP;
            return;
        }
    }
    else if (g_radioInform.txOffTone >= 2 && g_radioInform.txOffTone <= 13)
    {
        const STR_ROGER_TONE *pattern;

        rogerPatternMode = g_radioInform.txOffTone;
        pattern = RF_GetRogerPattern(rogerPatternMode, &rogerPatternCount);
        if (pattern != NULL && rogerPatternCount != 0)
        {
            rogerPatternIndex = 0;
            rogerPatternInGap = 0;
            rogerToneTicks = pattern[0].durationTicks;
            Rfic_TxSingleTone_On(1);
            Rfic_SetToneFreq(pattern[0].frequency);
            g_rfTxState = TX_ROGER_PATTERN;
            return;
        }
    }

    if (g_radioInform.tailSwitch)
    {
        RF_SendTail(ON);
        DelayMs(300);
    }
    RF_TxEnd();
}

static const STR_ROGER_TONE *RF_GetRogerPattern(U8 mode, U8 *count)
{
    switch (mode)
    {
    case 2:
        *count = sizeof(RogerClassic) / sizeof(RogerClassic[0]);
        return RogerClassic;
    case 3:
        *count = sizeof(RogerDouble) / sizeof(RogerDouble[0]);
        return RogerDouble;
    case 4:
        *count = sizeof(RogerDescend) / sizeof(RogerDescend[0]);
        return RogerDescend;
    case 5:
        *count = sizeof(RogerAscend) / sizeof(RogerAscend[0]);
        return RogerAscend;
    case 6:
        *count = sizeof(RogerTwoTone) / sizeof(RogerTwoTone[0]);
        return RogerTwoTone;
    case 7:
        *count = sizeof(RogerTriple) / sizeof(RogerTriple[0]);
        return RogerTriple;
    case 8:
        *count = sizeof(RogerRadio) / sizeof(RogerRadio[0]);
        return RogerRadio;
    case 9:
        *count = sizeof(RogerEcho) / sizeof(RogerEcho[0]);
        return RogerEcho;
    case 10:
        *count = sizeof(RogerChirp) / sizeof(RogerChirp[0]);
        return RogerChirp;
    case 11:
        *count = sizeof(RogerReverseChirp) / sizeof(RogerReverseChirp[0]);
        return RogerReverseChirp;
    case 12:
        *count = sizeof(RogerRadioExtended) / sizeof(RogerRadioExtended[0]);
        return RogerRadioExtended;
    case 13:
        *count = sizeof(RogerSignature) / sizeof(RogerSignature[0]);
        return RogerSignature;
    default:
        *count = 0;
        return NULL;
    }
}

static void RF_TxRogerPatternTask(void)
{
    const STR_ROGER_TONE *pattern;

    pattern = RF_GetRogerPattern(rogerPatternMode, &rogerPatternCount);
    if (pattern == NULL || rogerPatternCount == 0)
    {
        Rfic_TxSingleTone_Off();
        RF_TxEnd();
        return;
    }

    if (rogerToneTicks != 0)
    {
        rogerToneTicks--;
        if (rogerToneTicks != 0)
        {
            return;
        }
    }

    if (rogerPatternInGap == 0 && pattern[rogerPatternIndex].gapTicks != 0)
    {
        Rfic_SetToneFreq(0);
        rogerPatternInGap = 1;
        rogerToneTicks = pattern[rogerPatternIndex].gapTicks;
        return;
    }

    rogerPatternInGap = 0;
    rogerPatternIndex++;
    if (rogerPatternIndex >= rogerPatternCount)
    {
        Rfic_TxSingleTone_Off();
        rogerToneStage = 0;
        if (g_radioInform.tailSwitch)
        {
            RF_SendTail(ON);
            DelayMs(300);
        }
        RF_TxEnd();
        return;
    }

    Rfic_SetToneFreq(pattern[rogerPatternIndex].frequency);
    rogerToneTicks = pattern[rogerPatternIndex].durationTicks;
}

static void RF_TxRogerBeepTask(void)
{
    if (rogerToneTicks != 0)
    {
        rogerToneTicks--;
        if (rogerToneTicks != 0)
        {
            return;
        }
    }

    if (rogerToneStage == 1)
    {
        Rfic_SetToneFreq(F850HZ);
        rogerToneStage = 2;
        rogerToneTicks = 8;
        return;
    }

    Rfic_TxSingleTone_Off();
    rogerToneStage = 0;
    if (g_radioInform.tailSwitch)
    {
        RF_SendTail(ON);
        DelayMs(300);
    }
    RF_TxEnd();
}

void TotTimeWarning(void)
{
    static U8 flashFlag = 0;

    if (g_radioInform.totLevel == 0)
    { // 
        return;
    }
    if (g_sysRunPara.rfTxFlag.totTime < (g_radioInform.toa * 10))
    {
        if (g_sysRunPara.rfTxFlag.totTime % 3 == 0)
        { // LED,0.3S
            if (flashFlag == 0)
            {
                LedTxSwitch(LED_FLASH);
                flashFlag = 1;
            }
        }
        else
        {
            flashFlag = 0;
        }
    }

    if (g_sysRunPara.rfTxFlag.totTime == 0)
    { // 
        if (g_sysRunPara.dtmfToneFlag == 1)
        { // 
            Rfic_SetDtmfFreq(0, 0);
            Rfic_EnterDTMFMode(0);
            Rfic_TxSingleTone_Off();
            Rfic_SetAfout(0);

            SpeakerSwitch(OFF);
            g_sysRunPara.dtmfToneFlag = 0;
            KeyScanReset();
        }
        totEndPending = 1;
        RF_TxRoger();
        return;
    }
}

extern void RF_TxTask(void)
{
    switch (g_rfTxState)
    {
    case TX_READY:
        RfOff();
        Rfic_ConfigTxMode();

        g_sysRunPara.rfTxFlag.totTime = g_radioInform.totLevel * 150;
        g_rfTxState = WAIT_PTT_RELEASE;
        if (SetAlarmCode() == FALSE)
        {
            if (g_sysRunPara.txDtmfCode.codeLen)
            {
                DtmfSendCodeOn(DTMF_TYPEIN);
            }
            else if (g_CurrentVfo->spMute == 1)
            {
                DtmfSendCodeOn(DTMF_ANI);
            }
        }
        break;
    case WAIT_PTT_RELEASE:
        TotTimeWarning();

        if (g_rfTxState != WAIT_PTT_RELEASE)
        {
            return;
        }

        if (alarmDat.alarmStates || g_sysRunPara.rfTxFlag.voxWorkDly)
        {
            return;
        }
        if (PTT_GetKeyVal() == 0)
        {
            return;
        }
        // DtmfRstMatchTimer(0);

        if (g_CurrentVfo->pttIdMode & BIT1)
        {
            DtmfSendCodeOn(g_dtmfStore.dtmfFlag & BIT1);
        }

        RF_TxRoger();
        break;
    case TX_ROGER_BEEP:
        RF_TxRogerBeepTask();
        break;
    case TX_ROGER_PATTERN:
        RF_TxRogerPatternTask();
        break;
    case ALARM_TXID:
        DtmfSendCodeOn(DTMF_ALARMID);
        g_rfTxState = WAIT_PTT_RELEASE;
        break;

    case TX_STOP:
        if (g_sysRunPara.rfTxFlag.relayTailSetTime)
        {
            return;
        }
        Rfic_SetPA(0);
        Rfic_RxTxOnOffSetup(RFIC_IDLE);
        ResetTimeKeyLockAndPowerSave();
        DisplayHomePage();
        RF_PowerSet(g_ChannelVfoInfo.BandFlag, PWR_OFF);
        g_rfTxState = TX_READY;
        g_rfState = RF_RX;
        if (totEndPending)
        {
            totEndPending = 0;
            Audio_PlayVoiceLock(vo_Txovertime);
            WaitPttRelease();
            DisplayRadioHome();
        }
        break;

    default:
        break;
    }
}

const U8 RssiLevel[5][4] =
    {
        {135, 128, 124, 120}, // V ,116
        {101, 94, 90, 86},    // U, 82
        {108, 101, 97, 93},   // 220-260, 89
        {85, 78, 74, 71},     // 350-390, 67
        {132, 128, 124, 120}  // AM ,116
};

extern void CalculateSqlLevel(void)
{
    U16 rssi;

    if (!(g_rfState == RF_RX && g_rfRxState == WAIT_RXEND))
    {
        return;
    }

    if (g_sysRunPara.rfRxFlag.rxReceiveOn == ON)
    {
        rssi = Rfic_GetRssiVal();

        if (g_radioInform.dualRxFlag == 0)
        {
            U16 low = RssiLevel[g_ChannelVfoInfo.BandFlag][3];
            U16 high = RssiLevel[g_ChannelVfoInfo.BandFlag][0];
            U8 signalLevel;

            if (rssi < low)
            {
                signalLevel = 0;
            }
            else if (rssi >= high)
            {
                signalLevel = 9;
            }
            else
            {
                signalLevel = 1 + ((rssi - low) * 8) / (high - low);
            }

            if (periodSqlLevel != signalLevel)
            {
                DisplaySingleWatchSignal(signalLevel);
                periodSqlLevel = signalLevel;
            }
            return;
        }

        // SQL
        if (rssi < RssiLevel[g_ChannelVfoInfo.BandFlag][3])
        {
            rssi = 0;
        }
        else if (rssi < RssiLevel[g_ChannelVfoInfo.BandFlag][2])
        {
            rssi = 1;
        }
        else if (rssi < RssiLevel[g_ChannelVfoInfo.BandFlag][1])
        {
            rssi = 2;
        }
        else if (rssi < RssiLevel[g_ChannelVfoInfo.BandFlag][0])
        {
            rssi = 3;
        }
        else
        {
            rssi = 4;
        }

        if (periodSqlLevel != rssi)
        {
            DisplaySingalFlag(rssi, 1);
            periodSqlLevel = rssi;
        }
    }
    else
    {
        if (periodSqlLevel != 0xff)
        {
            periodSqlLevel = 0xff;
        }
    }
}

extern void RF_RxEnd(void)
{
    LedRxSwitch(LED_OFF);

    Rfic_SetAfout(OFF);
    SpeakerSwitch(OFF);

    g_rfRxState = RX_READY;
    g_sysRunPara.rfRxFlag.rxReceived = OFF;
    g_sysRunPara.rfRxFlag.rxReceiveOn = OFF;
    periodSqlLevel = 0xff;
    g_sysRunPara.rfTxFlag.voxDetDly = 10;

    if (DtmfGetMatchStatue() == 0)
    {
        DualStandbyWorkOFF();
    }

    if (g_sysRunPara.sysRunMode == MODE_SCAN_QT)
    {
        return;
    }
    ResetTimeKeyLockAndPowerSave();

    DisplayHomePage();
}

extern Boolean Rfic_CheckCtsState(void)
{
    static U8 ctsCnt = 0;

    if (g_sysRunPara.sysRunMode == MODE_WEATHER)
    {
        return TRUE;
    }

    if (g_CurrentVfo->rx->dcsCtsType == SUBAUDIO_NONE && g_CurrentVfo->fhssFlag == 0)
    {
        return TRUE;
    }

    if (Rfic_SubaudioDetect() == 0)
    {
        ctsCnt = 0;
        return FALSE;
    }

    ctsCnt++;
    if (ctsCnt > 2)
    {
        ctsCnt = 0;
        return TRUE;
    }

    return FALSE;
}

extern void RF_RxTask(void)
{
    static U8 ctcsDetFlag, tailDetFlag;

    if (g_sysRunPara.sysRunMode == MODE_MENU)
    {
        Rfic_RxTxOnOffSetup(RFIC_IDLE);
        RF_PowerSet(g_ChannelVfoInfo.BandFlag, PWR_OFF);
        Rfic_SetAfout(OFF);
        LedRxSwitch(LED_OFF);
        g_sysRunPara.rfRxFlag.rxReceived = OFF;
        g_sysRunPara.rfRxFlag.rxReceiveOn = OFF;
        g_rfRxState = RX_READY;
        return;
    }

    if (Audio_CheckBusy() || alarmDat.alarmStates)
    {
        return;
    }

    switch (g_rfRxState)
    {
    case RX_READY:
        if (g_sysRunPara.sysRunMode == MODE_WEATHER)
        {
            WeatherInit(g_radioInform.weatherNum);
        }
        else
        {
            Rfic_ConfigRxMode();
        }
        if (g_sysRunPara.moniFlag)
        {
            LedRxSwitch(LED_ON);
            Rfic_TxSingleTone_Off();
            Rfic_SetAfout(ON);
            SpeakerSwitch(ON);
            g_rfRxState = RX_MONI;
            break;
        }
        else
        {
            if (dualStandby.dualOnFlag == OFF && (g_sysRunPara.sysRunMode == MODE_MAIN))
            {
                DualStandbyWorkON();
            }
            ResetDualRxTime();
            g_sysRunPara.rfRxFlag.rxReceived = OFF;
            g_sysRunPara.rfRxFlag.rxReceiveOn = OFF;
            g_sysRunPara.rfRxFlag.relayTailDetTime = 0;
            sqCnt = 0;
            g_rfRxState = GET_CALL;
        }
    case GET_CALL:
        if (Rfic_GetSQLinkState() == TRUE)
        {
            sqCnt++;
            if (sqCnt < 3)
            {
                return;
            }
            ResetTimeKeyLockAndPowerSave();
            ResetDualRxTime();
            g_sysRunPara.rfRxFlag.rxReceived = ON;
            LedRxSwitch(LED_ON);

            if (g_sysRunPara.sysRunMode != MODE_WEATHER)
            {
                if (Rfic_CheckCtsState() == FALSE)
                {
                    return;
                }
                if (g_CurrentVfo->spMute == 1)
                {
                    if (dtmfInfo.matchTime[g_ChannelVfoInfo.dualAB] == 0)
                    {
                        if (dtmfInfo.callType == CALLTYPE_NONE)
                        {
                            return;
                        }

                        DtmfRstMatchTimer(1);
                    }
                }
            }

            sqCnt = 0;
            if (g_radioInform.fmInterrupt == 0 && g_sysRunPara.sysRunMode == MODE_FM)
            { // 
                return;
            }
            FmEnterSleepMode();

            if (g_sysRunPara.sysRunMode == MODE_MAIN)
            {
                DisplayRxMode();
            }
            LCD_BackLightSetOn();
            Rfic_SetAfout(ON);
            if (g_sysRunPara.sysRunMode != MODE_SCAN_QT)
            {
                SpeakerSwitch(ON);
            }
            g_sysRunPara.rfRxFlag.relayTailDetTime = 20;

            g_sysRunPara.rfRxFlag.rxReceiveOn = ON;
            g_sysRunPara.rfRxFlag.rxReceived = ON;
            ctcsDetFlag = 0;
            tailDetFlag = 0;
            g_rfRxState = WAIT_RXEND;
            CalculateSqlLevel();
        }
        else
        {
            sqCnt = 0;
            if (g_sysRunPara.rfRxFlag.rxReceived == ON)
            {
                g_sysRunPara.rfRxFlag.rxReceived = OFF;
                LedRxSwitch(LED_OFF);
            }

            if (g_sysRunPara.sysRunMode == MODE_SCAN || g_sysRunPara.sysRunMode == MODE_FM || g_sysRunPara.sysRunMode == MODE_SCAN_QT)
            {
                return;
            }
            PowerSaveTask();
            DualStandbyTask();
        }
        break;

    case WAIT_RXEND:
        if (Rfic_GetSQLinkState() == FALSE)
        {
            if (sqCnt > 0)
            {
                sqCnt--;
                return;
            }
            if (g_sysRunPara.rfTxFlag.relayTailSetTime == 0)
            {
                RF_RxEnd();
            }
            ResetTimeKeyLockAndPowerSave();
        }
        else
        {
            sqCnt = 1;
            DtmfRstMatchTimer(0);

            if (g_CurrentVfo->rx->dcsCtsType)
            {
                if (Rfic_GetTail())
                { // 
                    ctcsDetFlag = 1;
                    if (tailDetFlag == 0)
                    {
                        g_sysRunPara.rfRxFlag.relayTailDetTime = 10;
                        tailDetFlag = 1;
                        if (g_sysRunPara.rfTxFlag.relayTailSetTime == 0)
                        {
                            SpeakerSwitch(OFF);
                        }
                        return;
                    }
                }
                else
                {
                    if (Rfic_CheckCtsState() == TRUE && dtmfInfo.matchTime[g_ChannelVfoInfo.dualAB] == 0)
                    {
                        if (g_sysRunPara.rfRxFlag.relayTailDetTime == 0 && ctcsDetFlag == 0)
                        { // 

                            ctcsDetFlag = 1;
                            // 
                            g_sysRunPara.rfRxFlag.relayTailDetTime = 8;
                            if (g_sysRunPara.rfTxFlag.relayTailSetTime == 0)
                            {
                                SpeakerSwitch(OFF);
                            }
                        }
                    }
                    else
                    {
                        ctcsDetFlag = 0;
                        // 
                        g_sysRunPara.rfRxFlag.relayTailDetTime = 20;
                    }
                }
            }
            else
            {
                if (Rfic_GetTail())
                {
                    ctcsDetFlag = 1;
                    if (tailDetFlag == 0)
                    {
                        tailDetFlag = 1;
                        g_sysRunPara.rfRxFlag.relayTailDetTime = 8;
                        if (g_sysRunPara.rfTxFlag.relayTailSetTime == 0)
                        {
                            SpeakerSwitch(OFF);
                        }
                        return;
                    }
                }

                if (ctcsDetFlag != 1 && g_sysRunPara.sysRunMode != MODE_SCAN_QT)
                {
                    SpeakerSwitch(ON);
                }

                if ((g_sysRunPara.rfRxFlag.relayTailDetTime == 0) && (ctcsDetFlag == 1))
                {
                    RF_RxEnd();
                }
            }
        }
        break;

    case RX_MONI:
        break;

    default:
        break;
    }
}

extern void RF_Task(void)
{
    switch (g_rfState)
    {
    case RF_TX:
        RF_TxTask();
        break;
    case RF_RX:
        RF_RxTask();
        break;
    case RF_NONE:
    default:
        break;
    }
}
