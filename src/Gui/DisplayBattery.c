#include "includes.h"

void DisplayBatteryVol(U8 reFlash)
{
    U8 adc;
    U32 mv;
    U8 buf[20];

    (void)reFlash;

    adc = UserADC_GetValOfBatt();

    mv = ((U32)adc * 3300 * 374) / (255 * 100);

    sprintf(
        (char *)buf,
        "%lu.%02lu V",
        mv / 1000,
        (mv % 1000) / 10
    );

    LCD_DisplayText(
        24,
        32,
        buf,
        FONTSIZE_16x16,
        LCD_DIS_NORMAL
    );
}