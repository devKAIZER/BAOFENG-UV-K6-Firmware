#include "includes.h"

const U8 InputChar[] = {"adgjmptw"};

U16 SJCharIndex,SJPriorChar,SJTimeout;

String  const * const SJCharTbl[] =
{
    "()/\\# \x30",
    ".,?!':1",
    "ABC2",
    "DEF3",
    "GHI4",
    "JKL5",
    "MNO6",
    "PQRS7",
    "TUV8",
    "WXYZ9",
    "@$%&",
    " =+-_"
};

String  const * const NUMBER_SJCharTbl[] =
{
    "0",//0
    "1",//1
    "2",//2
    "3",//3
    "4",//4
    "5",//5
    "6",//6
    "7",//7
    "8",//8
    "9",//9
    "*",
    "#"
};

U8  ChangeCapsLow(U8  ch)
{
    if(IN_EN_L == g_inputbuf.inputType)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            ch += 32;
        }
    }
    return(ch);
}

void ChkFirstInput(void)
{
    if (g_inputbuf.isFirstInput == 0xaa)
    {
        ClearInputBuffer();
        g_inputbuf.isFirstInput = 0;
    }
}

U8  CharInput(String ch)
{
    if (g_inputbuf.maxLen != 0)
    {
        if (g_inputbuf.len >= g_inputbuf.maxLen)
        {
            return (FERROR);
        }
    }
    if (g_inputbuf.len < (sizeof(g_inputbuf.buf)-1))
    {
        return (InsertChar(ch));
    }
    else
    {
        return (FERROR);
    }
}

U8  NumToChar(U8  ch)
{
    String const * ptr;

    ResetMenuExitTime();

    ChkFirstInput();
    switch(g_inputbuf.inputType)
    {
        case IN_EN_L:
        case IN_EN_U:
            ptr = SJCharTbl[ch-'0'];
            break;
        case IN_NUMBER:
        default:
            ptr = NUMBER_SJCharTbl[ch-'0'];
            break;
    }
    SJTimeout = 3;

    if (SJPriorChar == ch)
    {
        SJCharIndex++;
        while((ch =(U8 ) ptr[SJCharIndex]) == 0)
        {
            SJCharIndex = 0;
        }
        ch = ChangeCapsLow(ch);
        if(g_inputbuf.pos == 0)
        {
            return (CharInput(ch));
        }
        g_inputbuf.buf[g_inputbuf.pos-1] = ch;
        return (OK);
    }
    if((g_inputbuf.inputType == IN_NUMBER)&&((ch >='0')&&ch <='9'))
    {
        SJTimeout = 0;
        SJPriorChar = 0;
        SJCharIndex = 0;
    }
    else
    {
        SJPriorChar = ch;
        SJCharIndex = 0;
    }
    ch = ChangeCapsLow(ptr[0]);
    return (CharInput(ch));
}

extern void ChangeInputType(void)
{
    U8  typeMax;

    ResetMenuExitTime();
    if (g_menuInfo.inputMode == MENU_ONE_CHAR)
    {
        g_inputbuf.inputType++;
        typeMax = IME_ENMAX;
        if (g_inputbuf.inputType >= typeMax)
        {
            g_inputbuf.inputType = IN_EN_L;
        }
        DisplayInputType();
    }
}

void ChangePos(U8  flag)
{
    if(flag)
    {
       if (g_inputbuf.pos >= g_inputbuf.len)
        {
            g_inputbuf.pos = g_inputbuf.len;
            return;
        }
        g_inputbuf.pos++;
    }
    else
    {
        if(g_inputbuf.pos <= 1)
        {
            return;
        }
        g_inputbuf.pos--;
    }
}

U8  BackSpaceChar(void)
{
    U8  i;

    ResetMenuExitTime();
    if (0 == g_inputbuf.pos || g_inputbuf.len == 0)
    {
        return (FERROR);
    }

    g_inputbuf.isFirstInput = 0;

    g_inputbuf.pos--;

    for (i=g_inputbuf.pos; i<g_inputbuf.len; i++)
    {
        g_inputbuf.buf[i] = g_inputbuf.buf[i+1];
    }
    g_inputbuf.len--;

    g_inputbuf.buf[g_inputbuf.len] = 0;
    return (OK);
}

U8  InsertChar(String  ch)
{
    U8  i;

    for (i=g_inputbuf.len; i>g_inputbuf.pos; i--)
    {
        g_inputbuf.buf[i] = g_inputbuf.buf[i-1];
    }
    g_inputbuf.buf[g_inputbuf.pos++] =(U8 )ch;

    g_inputbuf.len++;
    return (OK);
}

extern U8  NumInput(U8  ch)
{
    ChkFirstInput();
    if (isdigit(ch) == 0)
    {
        return (FERROR);
    }
    return (CharInput(ch));
}

void ClearInputBuffer(void)
{
    g_inputbuf.len = 0;
    g_inputbuf.pos = 0;
    memset((String *)g_inputbuf.buf,0,sizeof(g_inputbuf.buf));
    SJPriorChar = 0;
    SJCharIndex = 0;
}

extern void CheckSjTimeout(void)
{
    if (SJTimeout > 0)
    {
        if (--SJTimeout == 0)
        {
            SJPriorChar = 0;
            SJCharIndex = 0;
        }
    }
}

extern U8 DrowInputWindow(void)
{
    SC5260_ClearArea(30, 2, 124, 1, 1);
    return 0;
}

U8  BackSpace(void)
{
    return BackSpaceChar();
}
