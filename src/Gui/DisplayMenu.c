#include "includes.h"

#define EnS "abc"
#define EnL "ABC"
#define Num "123"

String disBuf[19];

const STR_MENU_ITEM MenuList[] =
    {
        {vo_Null, "CHL Name"},
        {vo_Null, "RX Frequency"},
        {vo_Null, "TX Frequency"},
        {vo_CTCSS, "R-CTCSS"},
        {vo_DCS, "R-DCS"},
        {vo_CTCSS, "T-CTCSS"},
        {vo_DCS, "T-DCS"},
        {vo_Chlbandwidth, "BandWidth"},
        {vo_power, "TXP"},
        {vo_Null, "Silence Mode"},
        {vo_Null, "TX Forbid"},
        {vo_Freqdir, "Shift DIR"},
        {vo_Offsetfreq, "OFFSET"},
        {vo_Memorychl, "MEMCH"},
        {vo_Deletechl, "DELCH"},
        {vo_Null, "VFO FreqRang"},
        {vo_Null, "Scan Mode"},
        {vo_Null, "DTMFST"},
        {vo_Null, "PTT ID"},
        {vo_Null, "PTT-LT"},
        {vo_Squelch, "Squelch"},
        {vo_savemode, "RX Save"},
        {vo_VOX, "VOX Switch"},
        {vo_Null, "VOX Level"},
        {vo_Null, "VOX Delay"},
        {vo_Txovertime, "TX OVer Time"},
        {vo_Null, "VOICE"},
        {vo_Null, "Menu HangTime"},
        {vo_Beepprompt, "BEEP PROMPT"},
        {vo_Null, "Roger Beep"},
        {vo_Null, "POWER ON TYPE"},
        {vo_Null, "Power On Tone"},
        {vo_Null, "Power on MSG"},
        {vo_Null, "POWER ON PWD"},
        {vo_Dualstandby, "Dual Watch"},
        {vo_Null, "MDF-A"},
        {vo_Null, "MDF-B"},
        {vo_Null, "RP-STE"},
        {vo_Null, "RPT-RL"},
        {vo_Null, "ALERT"},
        {vo_Step, "Freq Step"},
        {vo_Busylockout, "Busy Lockout"},
        {vo_Null, "Side Tone"},
        {vo_Null, "Alarm Mode"},
        {vo_Null, "PF1"},
        {vo_Null, "PF1 LONG PRESS"},
        {vo_Null, "PF2"},
        {vo_Null, "ABR"},
        {vo_Null, "Brightness"},
        {vo_Null, "LCD Reflex"},
        {vo_Null, "AUTOLOCK"},
        {vo_Null, "Radio Interrupt"},
        {vo_initialization, "Reset"},
        {vo_Null, "STOP WATCH"},
        {vo_Null, "VERSION"},
};

const STR_MENU_ITEM MenuFmList[] =
    {
        {vo_Null, "FM MEMCH"},
        {vo_Null, "FM BAND"},
};

const String *VoxStr[] =
    {
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10"};

const String *BatSaveEnStr[] =
    {
        "OFF",
        "1:1",
        "1:2",
        "1:4",
};

const String *OnOffEnStr[] =
    {
        "OFF",
        "ON"};

const String *OnSelEnStr[] =
    {
        "ON"};

const String *AlmodEnStr[] =
    {
        "ON SITE",
        "SEND SOUND",
        "SEND CODE"};

const String *ScanmodEnStr[] =
    {
        "TO",
        "CO",
        "SE"};

const String *PttIdSelEnStr[] =
    {
        "OFF",
        "BOT",
        "EOT",
        "BOTH"};

const String *BandEnStr[] =
    {
        "WIDE",
        "NARROW",
};

const String *TxPowerEnStr[] =
    {
        "HIGH",
        "LOW"};

const String *VfoStepStr[] =
    {
        "2.5 K",
        "5.0 K",
        "6.25 K",
        "10.0 K",
        "12.5 K",
        "20.0 K",
        "25.0 K",
        "50.0 K",
};

const String *VfoDirEnStr[] =
    {
        "OFF",
        "+",
        "-"};

const String *ChDisEnStr[] =
    {
        "NAME",
        "FREQ",
        "CH",
        "NAME+FREQ"};

const String *DtmfSetSelEnStr[] =
    {
        "OFF",
        "DT-ST",
        "ANI-ST",
        "DT+ANI"};

const String *DevResetEnStr[] =
    {
        "VFO",
        "All"};

const String *ToneEnStr[] =
    {
        " 1000hz", // 0
        " 1450hz", // 1
        " 1750hz", // 2
        " 2100hz", // 3
};

const String *PwrOnEnStr[] =
    {
        "OFF",
        "LOGO",
        "MESSAGE",
        "VOLTAGE",
        "BUILD",
    };

const String *SideKeyEnStr[] =
    {
        "None",
        "Torch On/Off",
        "Power Select ",
        "Scan On/Off",
        "VOX On/Off",
        "Alarm on/off",
        "Radio on/off",
};

const String *RxEndTailSelEnStr[] =
    {
        "OFF",
        "MDC1200"};

const String *TxEndToneEnStr[] =
    {
        "OFF",
        "STANDARD",
        "CLASSIC",
        "DOUBLE",
        "DESCEND",
        "ASCEND",
        "2-TONE",
        "TRIPLE",
        "M-RADIO",
        "ECHO",
        "CHIRP",
        "REVERSE CHIRP",
        "ROGER",
        "SIGNATURE"};

const String *ReflexEnStr[] =
    {
        "Normal",
        "Reflex"};

const String *PwrOnToneSelEnStr[] =
    {
        "None",
        "Tone",
        "Voice"};

const String *SpMuteSelEnStr[] =
    {
        "CTDCS",
        "CTDCS+Signaling",
};

const String *DualSelEnStr[] =
    {
        "OFF",
        "Double Wait",
        "Signal Wait"};

const String *FMBandItemStr[] =
    {
        "76-108Mhz",
        "65-76Mhz",
};

const U8 PttIDDelay[] = {0, 1, 2, 4, 6, 8, 10};

extern void Menu_GetSubItemString(U8 menuIndex)
{
    if (g_menuInfo.menuType == 1)
    {
        switch (menuIndex)
        {
        case 0:
            if (CheckFmChActive(g_menuInfo.selectedItem))
            {
                sprintf(disBuf, "CH-%02lu", (unsigned long)g_menuInfo.selectedItem + 1UL);
            }
            else
            {
                sprintf(disBuf, "%02lu", (unsigned long)g_menuInfo.selectedItem + 1UL);
            }
            break;
        case 1:
            sprintf(disBuf, "%s", FMBandItemStr[g_menuInfo.selectedItem]);
        default:
            break;
        }
    }
    else
    {
        switch (menuIndex)
        {
        case S_CHNAME:
            sprintf(disBuf, "%s", g_inputbuf.buf);
            break;
        case S_RXFREQ:
        case S_TXFREQ:
        case S_RXCTS:
        case S_TXCTS:
        case S_OFFSE:
        case S_VFOSCAN:
            break;
        case S_RXDCS:
        case S_TXDCS:
            if (g_menuInfo.selectedItem == 211)
            {
                if (g_sysRunPara.decoderCode)
                {
                    sprintf(disBuf, "%06lX", (unsigned long)(g_sysRunPara.decoderCode & 0xFFFFFFUL));
                }
                else
                {
                    memset(disBuf, ' ', 16);
                }
            }
            else if (g_menuInfo.selectedItem == 0 || g_menuInfo.selectedItem > 210)
            {
            sprintf(disBuf, "%s", "OFF");
            }
            else
            {
                if (g_menuInfo.selectedItem > 105)
                { // 
                    sprintf(disBuf, "D%03oI", DCS_TAB[g_menuInfo.selectedItem - 106]);
                }
                else
                { // 
                    sprintf(disBuf, "D%03oN", DCS_TAB[g_menuInfo.selectedItem - 1]);
                }
            }
            break;
        case S_WN:
            sprintf(disBuf, "%s", BandEnStr[g_menuInfo.selectedItem]);
            break;
        case S_TXPR:
            sprintf(disBuf, "%s", TxPowerEnStr[g_menuInfo.selectedItem]);
            break;
        case S_SPMUTE:
            sprintf(disBuf, "%s", SpMuteSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_SFTD:
            sprintf(disBuf, "%s", VfoDirEnStr[g_menuInfo.selectedItem]);
            break;
        case S_MEMCH:
        case S_DELCH:
            if (CheckChannelActive(g_menuInfo.selectedItem, 0))
            {
                sprintf(disBuf, "CH-%03lu", (unsigned long)g_menuInfo.selectedItem + 1UL);
            }
            else
            {
                sprintf(disBuf, "%03lu", (unsigned long)g_menuInfo.selectedItem + 1UL);
            }
            break;
        case S_SCREV:
            sprintf(disBuf, "%s", ScanmodEnStr[g_menuInfo.selectedItem]);
            break;
        case S_DTST:
            sprintf(disBuf, "%s", DtmfSetSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_PTTID:
            sprintf(disBuf, "%s", PttIdSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_PTTLT:
            sprintf(disBuf, "%dMs", PttIDDelay[g_menuInfo.selectedItem] * 100);
            break;
        case S_SQL:
            sprintf(disBuf, "%lu", (unsigned long)g_menuInfo.selectedItem);
            break;
        case S_SAVE:
            sprintf(disBuf, "%s", BatSaveEnStr[g_menuInfo.selectedItem]);
            break;
        case S_VOXLV:
            sprintf(disBuf, "%s", VoxStr[g_menuInfo.selectedItem]);
            break;
        case S_VOXDLY:
        {
            U8 time;
            time = g_menuInfo.selectedItem + 5;
            sprintf(disBuf, "%d.%dsec", time / 10, time % 10);
        }
        break;
        case S_TOT:
            if (g_menuInfo.selectedItem == 0)
            {
            sprintf(disBuf, "%s", "OFF");
            }
            else
            {
                sprintf(disBuf, "%luS", (unsigned long)(g_menuInfo.selectedItem * 15U));
            }
            break;
        case S_MENUEXIT:
            if (g_menuInfo.selectedItem == 10)
            {
                sprintf(disBuf, "60sec");
            }
            else
            {
                sprintf(disBuf, "%lusec", (unsigned long)((g_menuInfo.selectedItem + 1U) * 5U));
            }
            break;

        case S_ROGE:
            sprintf(disBuf, "%s", TxEndToneEnStr[g_menuInfo.selectedItem]);
            break;
        case S_PONTYPE:
            sprintf(disBuf, "%s", PwrOnEnStr[g_menuInfo.selectedItem]);
            break;
        case S_PONTONE:
            sprintf(disBuf, "%s", PwrOnToneSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_PONMSG:
        {
            U8 i = 0;
            memset(disBuf, 0x00, 16);
            for (i = 0; i < 16; i++)
            {
                if (powerOnMsg[i] == 0xFF || powerOnMsg[i] == 0x00)
                {
                    break;
                }
                disBuf[i] = powerOnMsg[i];
            }
        }
        break;
        case S_TDR:
            sprintf(disBuf, "%s", DualSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_MDF1:
        case S_MDF2:
            sprintf(disBuf, "%s", ChDisEnStr[g_menuInfo.selectedItem]);
            break;
        case S_RPSTE:
        case S_RPTRL:
            if (g_menuInfo.selectedItem == 0)
            {
            sprintf(disBuf, "%s", "OFF");
            }
            else
            {
                sprintf(disBuf, "%luS", (unsigned long)g_menuInfo.selectedItem);
            }
            break;
        case S_RTONE:
            sprintf(disBuf, "%s", ToneEnStr[g_menuInfo.selectedItem]);
            break;
        case S_STEP:
            sprintf(disBuf, "%s", VfoStepStr[g_menuInfo.selectedItem]);
            break;
        case S_ALMOD:
            sprintf(disBuf, "%s", AlmodEnStr[g_menuInfo.selectedItem]);
            break;
        case S_SK1:
        case S_SKL1:
        case S_SK2:
            sprintf(disBuf, "%s", SideKeyEnStr[g_menuInfo.selectedItem]);
            break;
        case S_ABR:
            if (g_menuInfo.selectedItem == 0)
            {
            sprintf(disBuf, "%s", "OFF");
            }
            else
            {
                if (g_menuInfo.selectedItem < 5)
                {
                    sprintf(disBuf, "%lusec", (unsigned long)(g_menuInfo.selectedItem * 5U));
                }
                else if (g_menuInfo.selectedItem == 5)
                {
                    sprintf(disBuf, "30sec");
                }
                else
                {
                    sprintf(disBuf, "%lumin", (unsigned long)(g_menuInfo.selectedItem - 5U));
                }
            }
            break;
        case S_BRIGHT:
            sprintf(disBuf, "%lu", (unsigned long)(g_menuInfo.selectedItem + 1U));
            break;
        case S_REFLEX:
            sprintf(disBuf, "%s", ReflexEnStr[g_menuInfo.selectedItem]);
            break;
        case S_AUTOLK:
            if (g_menuInfo.selectedItem == 0)
            {
            sprintf(disBuf, "%s", "OFF");
            }
            else
            {
                sprintf(disBuf, "%luS", (unsigned long)(g_menuInfo.selectedItem * 5U));
            }
            break;
        case S_RESET:
            sprintf(disBuf, "%s", DevResetEnStr[g_menuInfo.selectedItem]);
            break;
        case S_TXFORBID:
        case S_VOX:
        case S_VOIC:
        case S_BEEP:
        case S_PWR:
        case S_BUSYLOCK:
        case S_TAIL:
        case S_FMINT:
            sprintf(disBuf, "%s", OnOffEnStr[g_menuInfo.selectedItem]);
            break;
        case S_WATCH:
            sprintf(disBuf, "%s", OnSelEnStr[g_menuInfo.selectedItem]);
            break;
        case S_INFO:
            sprintf(disBuf, "KAI: %s", BUILD_NUMBER);
            break;
        default:
            break;
        }
    }
}

extern void Menu_DisplayFreqError(void)
{
    String disBuf[17];

    TranStrToMiddle(disBuf, (String *)"out of range!", 16);
    LCD_DisplayText(47, 0, (U8 *)disBuf, FONTSIZE_16x16, 0);
    LCD_UpdateWorkAre();

    // ʱ1Sʾɹ
    DelaySysMs(500);
}

void DisplayInputOffect(U32 selItem)
{
    U8 i, j;
    String buf[10] = {0};

    selItem = g_menuInfo.inputVal / 10;
    if (g_menuInfo.isSubMenu == 0)
    {
        sprintf(disBuf, "%lu.%04lu", (unsigned long)(selItem / 10000U), (unsigned long)(selItem % 10000U));
    }
    else
    {
        if (g_menuInfo.inputVal)
        {
            sprintf(disBuf, "%lu.%04lu", (unsigned long)(selItem / 10000U), (unsigned long)(selItem % 10000U));
        }
        else
        {
            memset(buf, '-', 7);
            buf[2] = '.';

            j = 0;
            for (i = 0; i < g_inputbuf.len; i++)
            {
                if (i == 2)
                {
                    j++;
                }
                buf[j++] = g_inputbuf.buf[i];
            }
            buf[7] = 0;
            strncpy(disBuf, buf, 16);
        }
    }
}
void DisplayInputChFreq(U32 selItem)
{
    U8 i, j;
    String buf[10] = {0};

    selItem = g_menuInfo.inputVal;
    if (g_menuInfo.isSubMenu == 0)
    {
        sprintf(disBuf, "%lu.%05lu", (unsigned long)(selItem / 100000U), (unsigned long)(selItem % 100000U));
    }
    else
    {
        if (g_menuInfo.inputVal)
        {
            sprintf(disBuf, "%lu.%05lu", (unsigned long)(selItem / 100000U), (unsigned long)(selItem % 100000U));
        }
        else
        {
            memset(buf, '-', 7);
            buf[3] = '.';

            j = 0;
            for (i = 0; i < g_inputbuf.len; i++)
            {
                if (i == 3)
                {
                    j++;
                }
                buf[j++] = g_inputbuf.buf[i];
            }
            buf[7] = 0;
            strncpy(disBuf, buf, 16);
        }
    }
}
void DisplayInputVfoScan(U32 selItem)
{
    U8 i, j;
    String buf[10] = {0};

    selItem = g_menuInfo.inputVal;
    if (g_menuInfo.isSubMenu == 0)
    {
        sprintf(disBuf, "%03lu-%03lu", (unsigned long)(selItem / 1000U), (unsigned long)(selItem % 1000U));
    }
    else
    {
        if (g_menuInfo.inputVal)
        {
            sprintf(disBuf, "%03lu-%03lu", (unsigned long)(selItem / 1000U), (unsigned long)(selItem % 1000U));
        }
        else
        {
            memset(buf, '-', 7);

            j = 0;
            for (i = 0; i < g_inputbuf.len; i++)
            {
                if (i == 3)
                {
                    j++;
                }
                buf[j++] = g_inputbuf.buf[i];
            }
            buf[7] = 0;
            strncpy(disBuf, buf, 16);
        }
    }
}

static U8 CheckCtcssInList(U16 ctcssDat)
{
    U8 i;

    if (ctcssDat == 0)
    {
        return 0;
    }

    // жƵǷ
    for (i = 0; i < 51; i++)
    {
        if (CTCS_TAB[i] == ctcssDat)
        {
            return (i);
        }
    }

    return 0xFF;
}

void GetCtcssDisBuf(U16 Index)
{
    if (Index == 0)
    {
        sprintf(disBuf, "OFF");
    }
    else if (Index == 0xFF)
    {
        sprintf(disBuf, "%lu.%luHz", (unsigned long)(g_menuInfo.inputVal / 10U), (unsigned long)(g_menuInfo.inputVal % 10U));
    }
    else
    {
        sprintf(disBuf, "%d.%dHz", CTCS_TAB[Index] / 10, CTCS_TAB[Index] % 10);
    }
}

static void ShowCtcssList(void)
{
    U8 selecteId;

    if (g_menuInfo.isSubMenu == 0)
    { // ڵһѡ˵ѡ

        if (g_menuInfo.inputVal == 0)
        {
            selecteId = 0;
        }
        else
        {
            selecteId = CheckCtcssInList(g_menuInfo.inputVal);
        }
        GetCtcssDisBuf(selecteId);
    }
    else
    {
        // selecteId = CheckCtcssInList(g_menuInfo.inputVal);
        selecteId = g_menuInfo.selectedItem;
        GetCtcssDisBuf(selecteId);
    }
}

extern void UpdateMenuDisplay(void)
{
    String lcdDisBuf[17] = {0}, headbuf[17] = {0};

    if (g_menuInfo.menuType == 1)
    {
        snprintf(headbuf, sizeof(headbuf), "%s", MenuFmList[g_menuInfo.menuIndex].nameEn);
    }
    else
    {
        snprintf(headbuf, sizeof(headbuf), "%s", MenuList[g_menuInfo.menuIndex].nameEn);
    }
    TranStrToMiddle(lcdDisBuf, headbuf, 12);
    LCD_DisplayText(20, 16, (U8 *)lcdDisBuf, FONTSIZE_16x16, LCD_DIS_NORMAL);

    sprintf(lcdDisBuf, "%02d", g_menuInfo.menuIndex);
    LCD_DisplayNumber(18, 2, (U8 *)lcdDisBuf, 0);

    TranStrToMiddle(lcdDisBuf, disBuf, 16);
    LCD_DisplayText(47, 0, (U8 *)lcdDisBuf, FONTSIZE_16x16, 0);

    if (g_menuInfo.isSubMenu)
    {
        LCD_DisplayPicture(50, 0, ICON_MENU_SEL_SIZEX, ICON_MENU_SEL_SIZEY, iconMenuSel, LCD_DIS_NORMAL);
    }

    if (g_menuInfo.inputMode == MENU_ONE_CTCSS || g_menuInfo.inputMode == MENU_ONE_DECODE)
    {
        if (g_menuInfo.inputMode == MENU_ONE_DECODE)
        {
            sprintf(lcdDisBuf, "%03lu", (unsigned long)g_menuInfo.selectedItem);
        }
        else
        {
            sprintf(lcdDisBuf, " %02lu", (unsigned long)g_menuInfo.selectedItem);
        }
        LCD_DisplayNumber(47, 109, (U8 *)lcdDisBuf, 0);
    }

    DisplayStateBar();
    LCD_UpdateWorkAre();
}

extern void DisplayInputType(void)
{
    String *str;
    String buf[6];

    if (inputTypeBack != g_inputbuf.inputType)
    {
        inputTypeBack = g_inputbuf.inputType;
        switch (g_inputbuf.inputType)
        {
        case IN_EN_L:
            str = EnS;
            break;
        case IN_EN_U:
            str = EnL;
            break;
        case IN_NUMBER:
        default:
            str = Num;
            break;
        }
        sprintf(buf, "%s", str);
        SC5260_ClearArea(10, 107, 20, 9, 1);
        LCD_DisplayNumber(11, 108, (U8 *)buf, 1);
        LCD_UpdateWorkAre();
    }
}

extern void MenuShowInputChar(void)
{
    DrowInputWindow();

    DisplayInputType();

    sprintf((String *)disBuf, "%*.*s", 16, 16, g_inputbuf.buf);
    LCD_DisplayText(47, 0, (U8 *)disBuf, FONTSIZE_16x16, 0);
    uartSendChar(disBuf[0]);

    inputTypeBack = 0xFF;
    DisplayInputType();
}

extern void Menu_Display(void)
{
    U8 i, posx;

    DisplayBattaryFlag(0);

    if (!(g_menuInfo.inputMode == MENU_ONE_CHAR && g_menuInfo.isSubMenu))
    {
        // м
        SC5260_ClearArea(41, 5, 121, 2, 1);
        posx = 5;
        for (i = 0; i < 13; i++)
        {
            SC5260_ClearArea(40, posx, 1, 1, 1);
            posx += 10;
        }
    }
    switch (g_menuInfo.inputMode)
    {
    case MENU_ONE_CHAR:
        if (g_menuInfo.isSubMenu)
        { // ʾŵƱ༭
            LCD_ClearWorkArea();
            MenuShowInputChar();
            return;
        }
        else
        {
            Menu_GetSubItemString(g_menuInfo.menuIndex);
        }
        break;
    case MENU_ONE_FREQ: // Ƶ
        if (g_menuInfo.isSubMenu == 0)
        {
            g_menuInfo.inputVal = g_menuInfo.selectedItem;
        }
        DisplayInputOffect(g_menuInfo.inputVal);

        break;
    case MENU_CH_FREQ: // Ƶ
        if (g_menuInfo.isSubMenu == 0)
        {
            g_menuInfo.inputVal = g_menuInfo.selectedItem;
        }
        DisplayInputChFreq(g_menuInfo.inputVal);

        break;
    case MENU_ONE_VFOSCAN: // ƵɨΧ
        if (g_menuInfo.isSubMenu == 0)
        {
            g_menuInfo.inputVal = g_menuInfo.selectedItem;
        }
        DisplayInputVfoScan(g_menuInfo.inputVal);
        break;

    case MENU_ONE_CTCSS: // ģƵѡ
        ShowCtcssList();
        break;
    case MENU_ONE_DIGIT:
        sprintf(disBuf, "%lu", (unsigned long)g_menuInfo.selectedItem);
        break;
    case MENU_ONE_SELECT:
    default:
        Menu_GetSubItemString(g_menuInfo.menuIndex);
        break;
    }
    UpdateMenuDisplay();
}
