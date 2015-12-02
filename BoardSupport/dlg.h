#ifndef _DLG_H
#define _DLG_H
#include "WM.h"
extern WM_HWIN mainwin;
extern WM_HWIN Menuwin;
extern WM_HWIN InfoText;
extern WM_HWIN ToolTip;
extern WM_HWIN CheckWin;
extern WM_HWIN PrintWin;

WM_HWIN mainWinCreate(void);
WM_HWIN MenuWinCreate(void);
WM_HWIN InfoTextCreate(void);
WM_HWIN CheckWinCreate(void);
WM_HWIN PrintWinCreate(void);
#endif


