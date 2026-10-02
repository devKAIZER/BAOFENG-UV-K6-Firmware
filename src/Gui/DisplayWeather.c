#include "includes.h"

extern void WeatherDisplayFreq(void)
{
    String disBuf[11] = {0};
    U32 weatherFreq = TAB_WEATHER[g_radioInform.weatherNum];
    U8 whole = (U8)(weatherFreq / 100000U);
    U32 fraction = weatherFreq % 100000U;
    
    snprintf(disBuf, sizeof(disBuf), "WX-%02u", (unsigned int)g_radioInform.weatherNum + 1U);
    LCD_DisplayText(30,85,(U8 *)disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
    
    snprintf(disBuf, sizeof(disBuf), "%03u.%05lu", (unsigned int)whole,
             (unsigned long)fraction);
    LCD_DisplayText(45,24,(U8 *)disBuf,FONTSIZE_16x16,LCD_DIS_NORMAL);
    
    LCD_UpdateWorkAre();
}

extern void WeatherDisplayHome(void)
{    
    LCD_ClearWorkArea();
    
    //显示天气预报
    LCD_DisplayPicture(14,47,ICON_WORK_WX_SIZEX,ICON_WORK_WX_SIZEY,iconWorkWeather,LCD_DIS_NORMAL);
    
    //显示收音机频率   
    WeatherDisplayFreq();
}


