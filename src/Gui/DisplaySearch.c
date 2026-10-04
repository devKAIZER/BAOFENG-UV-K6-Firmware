#include "includes.h"

extern void SearchFreqModeDisplayDCSData(U8 ctsDcsType, U32 dat, U8 isStandard)
{
    String disBuf[15] = {0};
    memset( disBuf, ' ', 11 );
    LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
    if( ctsDcsType > SUBAUDIO_CTS )
    {
        if(isStandard == 1)
        {
            sprintf( disBuf, "   D%03loN ", (unsigned long)dat );
		    LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
        }
        else
        {
            sprintf( disBuf, "   %6lX", (unsigned long)dat );
		    LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
        }
	}
    else if(ctsDcsType == SUBAUDIO_CTS)
    {
        snprintf(disBuf, sizeof(disBuf), "   %3lu.%1lu",
             (unsigned long)(dat / 10U), (unsigned long)(dat % 10U));
		LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
    }
	else
	{
		sprintf( disBuf, "   NONE "  );
		LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
	}
	LCD_UpdateWorkAre();
}

extern void SearchFreqModeDisplayStepMsg( ENUM_SEARCHFREQ_STEP step )
{
    String disBuf[13]={" SEEK...  "};

    if( searchFreqImofs.band == FREQ_BAND_UHF )
    {
        LCD_DisplayText(17,108,(U8 *)"UHF",FONTSIZE_12x12,LCD_DIS_NORMAL);
    }
    else if(searchFreqImofs.band == FREQ_BAND_200M)
    {
        LCD_DisplayText(17,108,(U8 *)"200",FONTSIZE_12x12,LCD_DIS_NORMAL);
    }

    else if(searchFreqImofs.band == FREQ_BAND_350M)
    {
        LCD_DisplayText(17,108,(U8 *)"350",FONTSIZE_12x12,LCD_DIS_NORMAL);
    }
    else
    {
        LCD_DisplayText(17,108,(U8 *)"VHF",FONTSIZE_12x12,LCD_DIS_NORMAL);
    }

	if( step == STEP_SEEK_FREQ )
	{
        LCD_DisplayText(33,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);

	    memset( disBuf, ' ', 9 );
        LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
	}
	else 
	{
        LCD_DisplayText(49,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);

        sprintf(disBuf, "%3lu.%05lu",
            (unsigned long)(searchFreqImofs.freq / 100000U),
            (unsigned long)(searchFreqImofs.freq % 100000U));
        LCD_DisplayText(33,37,(U8 *)&disBuf,FONTSIZE_12x12,LCD_DIS_NORMAL);
	}

	LCD_UpdateWorkAre();
}

extern void SearchFreqDisplayHome(void )
{
    LCD_ClearWorkArea();

    LCD_DisplayText(17,46,(U8 *)"SEARCH",FONTSIZE_12x12, LCD_DIS_NORMAL);
    SearchFreqModeDisplayStepMsg(STEP_SEEK_FREQ);
}

