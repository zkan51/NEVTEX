#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
WM_HWIN CheckWin;
static CHAR TimerIndex = 0;
WM_HWIN CheckText[8];
static CHAR text[50] = {""};
CHAR *pchecktext = text;
extern WM_HTIMER CheckTimer;
static void _cbDialog(WM_MESSAGE *pMsg)
{
	 WM_KEY_INFO *pKEY;
	 CHAR TimeID;
  switch(pMsg->MsgId)
	 {
			 case WM_PAINT:
									GUI_SetBkColor(GUI_WHITE);
									GUI_Clear();
					    GUI_SetFont(&GUI_Font30);
				     GUI_SetColor(GUI_BLACK);
				     GUI_DispStringAt("自检中:",100,50);
									break;
			 case WM_KEY:
					    pKEY = (WM_KEY_INFO*)pMsg->Data.p;
				     switch (pKEY->Key)
									{
										      case GUI_KEY_ESCAPE:
																	    WM_BringToTop(mainwin);
																     TimerIndex = 0;
																     WM_DeleteTimer(CheckTimer);
																     WM_SetFocus(mainwin);
																	break;
									}
					    break;
			 case WM_CREATE:
					    CheckText[0] = TEXT_CreateEx (150,   80,   600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[1] = TEXT_CreateEx (150,   120,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[2] = TEXT_CreateEx (150,   160,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[3] = TEXT_CreateEx (150,   200,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[4] = TEXT_CreateEx (150,   240,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[5] = TEXT_CreateEx (150,   280,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[6] = TEXT_CreateEx (150,   320,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
				     CheckText[7] = TEXT_CreateEx (150,   360,  600, 40, pMsg->hWin,WM_CF_SHOW,0,0,NULL);
					    break;
				
				case WM_TIMER:
				{
									if (TimerIndex == 0)
									{
										  pchecktext = "国际频道 . . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[0],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
										  TimerIndex++;
									}
									else if (TimerIndex == 1)
									{
										  pchecktext = "本地频道I. . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[1],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 2)
									{
										  pchecktext = "本地频道II . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[2],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 3)
									{
										  pchecktext = "中文频道 . . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[3],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 4)
									{
										  pchecktext = "数据内存 . . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[4],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 5)
									{
										  pchecktext = "天线单元 . . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[5],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 6)
									{
										  pchecktext = "打印端口 . . . . . . . . . . . . . . . . . . . . . 通过";
										  TEXT_SetText(CheckText[6],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex++;
									}
									else if (TimerIndex == 6)
									{
										  pchecktext = "报警铃声 . . . . . . . . . . . . . . . . . . . .  已执行";
										  TEXT_SetText(CheckText[7],pchecktext);
										  WM_RestartTimer(CheckTimer,2000);
												TimerIndex = 0;
										  WM_DeleteTimer(CheckTimer);
									}
									
									break;
					}
			default:
				  WM_DefaultProc(pMsg);
			   break;
		}
		
}


/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN CheckWinCreate(void) {
   WM_HWIN hWin;
	
	  hWin = WM_CreateWindow(0, 0, 800, 480,WM_CF_SHOW, _cbDialog, 0);
  return hWin;
}