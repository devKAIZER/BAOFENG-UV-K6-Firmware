#ifndef __DISPLAYINPUTBOX_H
    #define __DISPLAYINPUTBOX_H

#define IN_EN_L        0
#define IN_EN_U        1
#define IN_NUMBER      2
#define IME_ENMAX      3

extern U16 SJCharIndex,SJPriorChar,SJTimeout;

extern void ChkFirstInput(void);
extern U8 CharInput(String ch);
extern U8 NumToChar(U8 ch);
extern U8 NumInput(U8 ch);
extern void ClearInputBuffer(void);
extern U8 InsertChar(String  ch);
extern void ChangePos(U8 flag);
extern void ChangeInputType(void);
extern U8 BackSpaceChar(void);
extern void CheckSjTimeout(void);
extern U8 BackSpace(void);
extern U8 DrowInputWindow(void);

#endif