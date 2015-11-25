#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
#include "POWER.h"
#define ID_WINDIW_0 (GUI_ID_USER + 0x00)

#define ID_MULTIEDIT_0   (GUI_ID_USER + 0x10)
#define ID_BUTTON_0   (GUI_ID_USER + 0x11)
#define ID_LV_0 (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_1 (GUI_ID_USER + 0x04)
#define ID_TEXT_2 (GUI_ID_USER + 0x05)
#define ID_TEXT_3 (GUI_ID_USER + 0x06)
#define ID_MENU   (GUI_ID_USER + 0x50)
#define ID_PrintMenu (GUI_ID_USER + 0x51)

WM_HWIN hMultiEdit;
SCROLLBAR_Handle hScrollbarv;
SCROLLBAR_Handle hScrollbarh;
const GUI_RECT Scrollbar = {709,0,719,355}; 
GUI_RECT ScrollbarI ;
extern int InfoId;
extern char SelRow;
extern CHAR* pCannel;
extern CHAR MenuSel;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ETWin", ID_WINDIW_0, 0,0, 800, 480, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "Button",ID_BUTTON_0,90,30,50,30,0,0,0},
  { MULTIEDIT_CreateIndirect,"mEdit", ID_MULTIEDIT_0, 40, 100, 720, 335, 0, 0, 0},
		{ TEXT_CreateIndirect,    "lock",  ID_TEXT_0, 270,25,25,30,0,0,0},

		{ TEXT_CreateIndirect,    "INT",  ID_TEXT_1, 340,28,85,30,0,0,0},
		{ TEXT_CreateIndirect,    "LOC",  ID_TEXT_2, 430,28,85,30,0,0,0},
  { TEXT_CreateIndirect,    "time", ID_TEXT_3, 520,28,230,30,0,0,0},
};

static void InfoButton (WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	static char Pagecount = 0; // 总的信息页数
	static char thisPage = 0;			//当前所处的页数
	WM_KEY_INFO *key;
	INFO *Info;
	int16_t i = 0;
	//int16_t SelRow = 0;
	switch (pMsg->MsgId)
	{
		case WM_KEY:
			    key = (WM_KEY_INFO*)pMsg->Data.p;
							switch (key->Key)
							{
								 case GUI_KEY_MENU:
										    WM_BringToTop(Menuwin);
									     WM_SetFocus(WM_GetDialogItem(Menuwin,ID_MENU));
									     MENU_SetSel(WM_GetDialogItem(Menuwin,ID_MENU),0);
									     MenuSel = 0;
														break;
									
									case GUI_KEY_PRINT:
// 										     memset(pbuff,0,800*sizeof(CHAR));
// 										     MULTIEDIT_GetText(WM_GetDialogItem(InfoText,ID_MULTIEDIT_0),pbuff,1000);
// 									      pPrint = pbuff;
// 									      while (*pPrint)
// 															{
// 																  printf("%c",*pPrint);
// 																  pPrint++;
// 															}
										    WM_BringToTop(PrintWin);
									     WM_SetFocus(WM_GetDialogItem(PrintWin,ID_PrintMenu)); 
										    break;
									
									case GUI_KEY_LOC1:
												pCannel = "  490 横";
												WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
												break;
									
									case GUI_KEY_LOC2:
												pCannel = "4209.5↓";
												WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
												break;
									
									case GUI_KEY_CHS:
												pCannel = "  486 横";
												WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
										break;		
									
									case GUI_KEY_LOCK:
														Info  = pInfoHeader;
														if (pInfoHeader)
														do 
														{
																if (Info->ID == InfoId)
																{
																		if (Info->isLocked == 0)
																		{
																					Info->isLocked = 1;
																					TEXT_SetText(WM_GetDialogItem (InfoText,ID_TEXT_0),"锁");
																					LISTVIEW_SetItemText(WM_GetDialogItem (mainwin,ID_LV_0),6,SelRow,"          锁");
																		}
																		else if (Info->isLocked == 1)
																		{									
																				Info->isLocked = 0;
																				LISTVIEW_SetItemText(WM_GetDialogItem (mainwin,ID_LV_0),6,SelRow,"");
																				TEXT_SetText(WM_GetDialogItem (InfoText,ID_TEXT_0),"");
																		}
																		break;
																}
														}while (Info = Info->pNext);	
														break;
										
									case GUI_KEY_LEFT:
														SCROLLBAR_AddValue(hScrollbarh,-50);
														break;
									
									case GUI_KEY_RIGHT:
														SCROLLBAR_AddValue(hScrollbarh,50);
														break;
								
									case GUI_KEY_ESCAPE:
														Info  = pInfoHeader;
														if (pInfoHeader)
														do 
														{
																if (Info->ID == InfoId)
																{
																		Info->state = INFO_STT_CSTOFF;
																		break;
																}
														}while (Info = Info->pNext);				
														WM_BringToTop(mainwin);
														WM_SetFocus (mainwin);
														break;
								
									case GUI_KEY_UP:
														SCROLLBAR_AddValue(hScrollbarv,-11);
														break;
													
								case GUI_KEY_DOWN:
													SCROLLBAR_AddValue(hScrollbarv,11);
													break;
							}
		     break;

		default:		
		     BUTTON_Callback(pMsg);
		     break;
	}
}


static void mytext(WM_MESSAGE *pMsg)
{
	int16_t  ID;
	ID = WM_GetId(pMsg->hWin);
		switch (pMsg->MsgId)
		{
				case WM_PAINT:
									switch (ID)
									{  
										 case ID_TEXT_1:
																GUI_SetBkColor(GUI_WHITE);
																GUI_Clear();
																GUI_SetColor(GUI_BLACK);
																GUI_FillRoundedRect(0,0,80,25,5);
																GUI_SetTextMode(GUI_TEXTMODE_TRANS);
																GUI_SetColor(GUI_WHITE);
																GUI_SetFont (&GUI_Font24);
																GUI_DispStringAt("518 横",5,2);
																break;
											
											case ID_TEXT_2:
																GUI_SetBkColor(GUI_WHITE);
																GUI_Clear();
																GUI_SetColor(GUI_BLACK);
																GUI_FillRoundedRect(0,0,80,25,5);
																GUI_SetTextMode(GUI_TEXTMODE_TRANS);
																GUI_SetColor(GUI_WHITE);
																GUI_SetFont (&GUI_Font24);
																GUI_DispStringAt(pCannel,5,2);			
														break;
									}
									break;
				
				default: 
					    TEXT_Callback(pMsg);
				     break;
		}
}

static void _cbDialog(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	WM_HWIN hButton;
	WM_KEY_INFO *Info;
	WM_HWIN hText;
	CHAR str_index,str_index1;
	int count=0;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		
		 case WM_PAINT:
								GUI_SetBkColor(GUI_WHITE);
								GUI_Clear();
								GUI_SetColor (GUI_BLACK);
								GUI_DispStringAt("信息",40,30);
								GUI_AA_DrawLine(190,0,220,60);
								GUI_AA_DrawLine(220,60,800,60);
								GUI_DispStringAt("距发射站台距离:486海里",520,435);
								GUI_DispStringAt("误字符率:00%",620,65);
				    GUI_PNG_Draw(&acPOWER,sizeof(acPOWER),755,35);
								break;
			
			case WM_INIT_DIALOG:
								hButton = WM_GetDialogItem (hWin,ID_BUTTON_0);
								BUTTON_SetBkColor (hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);
								BUTTON_SetTextColor (hButton,BUTTON_CI_UNPRESSED,GUI_BLACK);
								BUTTON_SetTextAlign (hButton,GUI_TA_HCENTER|GUI_TA_VCENTER);
								BUTTON_SetText(hButton,"所有信息");
								BUTTON_SetFocusColor (hButton,GUI_WHITE);
								WIDGET_SetEffect (hButton,&WIDGET_Effect_None);
								WM_SetCallback (hButton,&InfoButton);	
							
								hMultiEdit  = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
								MULTIEDIT_SetFont(hMultiEdit,&GUI_Font30);
								MULTIEDIT_SetReadOnly(hMultiEdit,0);
								MULTIEDIT_SetBkColor (hMultiEdit,MULTIEDIT_CI_READONLY,GUI_YELLOW);
								MULTIEDIT_SetTextColor(hMultiEdit, MULTIEDIT_CI_READONLY,GUI_RED);
								MULTIEDIT_SetWrapWord(hMultiEdit);
								hScrollbarv = SCROLLBAR_CreateAttached(hMultiEdit,SCROLLBAR_CF_VERTICAL);
							
								// TEXT0
								hText = WM_GetDialogItem(hWin,ID_TEXT_1);
								WM_SetCallback(hText,&mytext);
								
								// TEXT1
								hText = WM_GetDialogItem(hWin,ID_TEXT_2);
								WM_SetCallback(hText,&mytext);	
								
								// TIME
								hText = WM_GetDialogItem(hWin,ID_TEXT_3);
								TEXT_SetTextAlign(hText,TEXT_CF_VCENTER);
								TEXT_SetFont(hText,&GUI_Font30);
								TEXT_SetText(hText,"UTC 2015.10.24 17:30");
								break;

			default:
			     WM_DefaultProc(pMsg);
		      break;
	}
}

/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN InfoTextCreate(void) {
  WM_HWIN hWin;
	
 hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	
  return hWin;
}