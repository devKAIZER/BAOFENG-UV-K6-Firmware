#include "includes.h"

extern void UI_DisplayPowerOn(void)
{
    U8 picDisBuf[1024 + 1] = {0};
    U8 disbuf[32];
    U8 len;

    SC5620_SetContpastRatio(g_radioInform.brightness);

    switch (g_radioInform.OpFlag1.Bit.b3)
    {
    case 0:
        break;

    case 1:
        SpiFlash_ReadBytes(
            FLASH_PON_MSG_ADDR,
            picDisBuf,
            1024);

        SC5260_DisplayArea(
            0,
            0,
            128,
            64,
            picDisBuf,
            LCD_DIS_NORMAL);
        break;

    case 2:
    {
        U8 i = 0;
        U8 disBuf[17];

        memset(disBuf, ' ', 16);
        disBuf[16] = '\0';

        for (i = 0; i < 16; i++)
        {
            if (powerOnMsg[i] == 0xFF || powerOnMsg[i] == 0x00)
            {
                break;
            }

            disBuf[i] = powerOnMsg[i];
        }

        LCD_DisplayText(
            24,
            64 - (i * 4),
            disBuf,
            FONTSIZE_16x16,
            LCD_DIS_NORMAL);

        break;
    }

    case 3:
        DisplayBatteryVol(0);
        break;

    case 4:
    {
        U8 len;
        len = sprintf(
            (String *)disbuf,
            "%s",
            BUILD_ORIGIN);

        LCD_DisplayText(
            4,
            64 - (len << 2),
            (U8 *)disbuf,
            FONTSIZE_16x16,
            LCD_DIS_NORMAL);

        len = sprintf(
            (String *)disbuf,
            "%s",
            BUILD_AUTHOR);

        LCD_DisplayText(
            24,
            64 - (len << 2),
            (U8 *)disbuf,
            FONTSIZE_16x16,
            LCD_DIS_NORMAL);

        len = sprintf(
            (String *)disbuf,
            "%s",
            BUILD_NUMBER);

        LCD_DisplayText(
            44,
            64 - (len << 2),
            (U8 *)disbuf,
            FONTSIZE_16x16,
            LCD_DIS_NORMAL);

        break;
    }

    default:
        break;
    }

    LcdBackLightSwitch(LED_ON);
    LCD_UpdateFullScreen();
    DelaySysMs(1000);
}