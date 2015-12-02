#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
#include "LANGUAGE.h"

#define ID_WINDOW_0  (GUI_ID_USER + 0x00)

#define ID_BUTTON_0  (GUI_ID_USER + 0x02)
#define ID_BUTTON_1  (GUI_ID_USER + 0x03)
#define ID_TEXT_0    (GUI_ID_USER + 0x52)
#define ID_TEXT_1    (GUI_ID_USER + 0x53)
#define ID_MENU     					(GUI_ID_USER + 0x50)
#define ID_PrintMenu     (GUI_ID_USER + 0x51)

WM_HWIN ToolTip;
WM_HWIN ToolTip_BUTTON[2];
WM_HWIN ToolTipText0;
WM_HWIN ToolTipText1;
extern CHAR CheckFlag;
static char tipText[50] = {"未检测到系统更新文件"};
extern CHAR StarPrint;
extern WM_HWIN hMultiEdit;
extern WM_HTIMER PrintTimer;
extern CHAR Language;
static char Printing = 0;
CHAR *ptipText = tipText;
WM_HTIMER CheckTimer;
static const TOOLTIP *pTooltip;

CHAR pbuff[800] ={""};

static void myButton (WM_MESSAGE *pMsg)
{
	const WM_KEY_INFO *pInfo;
	WM_HWIN thisButton  = pMsg->hWin; 
	switch(pMsg->MsgId)   
 { 
				
				case WM_KEY:
					  pInfo = (WM_KEY_INFO*)pMsg->Data.p;
				   switch (pInfo->Key)
				   {
								  case GUI_KEY_LEFT:
										case GUI_KEY_UP:
											  WM_SetFocusOnPrevChild(ToolTip);
									   	break;
										
          case GUI_KEY_DOWN:
										case GUI_KEY_RIGHT:
											  WM_SetFocusOnNextChild(ToolTip);
										   break;
										
										case GUI_KEY_ENTER:
											  if (WM_GetId(thisButton) == ID_BUTTON_1 && CheckFlag == 1)
													{
														WM_BringToTop(CheckWin);
														WM_SetFocus(CheckWin);
														CheckTimer = WM_CreateTimer(CheckWin,0,2000,0);
														break;
													}
													CheckFlag = 0;
											  WM_BringToTop(Menuwin);
										   WM_SetFocus  (WM_GetDialogItem(Menuwin,ID_MENU));
										   break;
							}
				   break;

  // USER END
			default:
				BUTTON_Callback(pMsg);
			break;
	}
}

static void _cbDialog(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	WM_HWIN hButton;
	WM_HWIN hWindow;
	WM_KEY_INFO *Info;
	int16_t xSize,ySize;
	CHAR str_index,str_index1;
	CHAR *pPrint;
	int count=0;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
								case WM_KEY:
											  Info = (WM_KEY_INFO*)pMsg->Data.p;
													switch (Info->Key)
													{
																case GUI_KEY_ESCAPE:
																	  if (StarPrint == 1)
																			{
																				 StarPrint = 0;
																				 WM_BringToTop(PrintWin);
																			  WM_SetFocus (WM_GetDialogItem(PrintWin,ID_PrintMenu));
																				 if (Printing == 1)
																					{
																				    Printing = 0;
																				    WM_DeleteTimer(PrintTimer); 
																					}
																			}
																			else
																			{
																			  WM_BringToTop(Menuwin);
																			  WM_SetFocus  (WM_GetDialogItem(Menuwin,ID_MENU));
																			}
																			break;
													}
													break;
								
					   case	WM_TIMER:
									    pTooltip = &Lgutooltip[Language];
									    if (Printing == 0) //打印
													{
																MULTIEDIT_GetText(hMultiEdit,pbuff,1000);
													   printf("%s",pbuff);
// 																pPrint = pbuff;
// 																while (*pPrint)
// 																{
// 																			printf("%c",*pPrint);
// 																			pPrint++;
// 																}
																WM_RestartTimer(PrintTimer,10000); //打印时间10s
																Printing = 1;
														}
														else if (Printing == 1) //打印完成
														{
															  Printing = 0;
																	ptipText = "打印完成";
																	TEXT_SetText(ToolTipText0,pTooltip->Text1[5]);
																	WM_DeleteTimer(PrintTimer);
														}
									    break;
		
								case WM_PAINT:
													xSize = WM_GetWindowSizeX(pMsg->hWin);
													ySize = WM_GetWindowSizeY(pMsg->hWin);
													GUI_SetColor(GUI_BLACK);
													GUI_DrawRoundedRect(0,0,xSize - 1, ySize - 1, 20);
													//GUI_DrawGradientRoundedV(0, 0, xSize - 1, ySize - 1, 20, GUI_WHITE,GUI_WHITE);
													break;
				
								case WM_CREATE:
												
									//
									// Initialization of 'bt_OK'
									//
													BUTTON_CreateEx (60,110,80,40,hWin, WM_CF_HASTRANS  ,0,ID_BUTTON_0);
													ToolTip_BUTTON[0] = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
													BUTTON_SetText(ToolTip_BUTTON[0], "否");
													WM_SetCallback(ToolTip_BUTTON[0], &myButton);
													//
													// Initialization of 'bt_Cancle'
													//
													BUTTON_CreateEx(260,  110,   80,  40,hWin,WM_CF_HASTRANS,0,ID_BUTTON_1);
													ToolTip_BUTTON[1] = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
													BUTTON_SetText(ToolTip_BUTTON[1], "是");
													WM_SetCallback(ToolTip_BUTTON[1], &myButton);
													//
													// Initialization of 'Text'
													//
													TEXT_CreateEx (0,   20,  400, 70, hWin,WM_CF_SHOW,0,ID_TEXT_0,NULL);
													ToolTipText0 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
													TEXT_SetTextColor (ToolTipText0,GUI_BLACK);
													TEXT_SetTextAlign(ToolTipText0,TEXT_CF_HCENTER | TEXT_CF_VCENTER);
													TEXT_SetText(ToolTipText0, ptipText);
													TEXT_SetFont(ToolTipText0, &GUI_Font30);
													
													TEXT_CreateEx (0,   100,  400, 40, hWin,WM_CF_SHOW,0,ID_TEXT_1,NULL);
													ToolTipText1 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
													TEXT_SetTextColor (ToolTipText1,GUI_BLACK);
													TEXT_SetTextAlign(ToolTipText1,TEXT_CF_HCENTER);
													TEXT_SetText(ToolTipText1, "按ESC键退出！");
													TEXT_SetFont(ToolTipText1, &GUI_Font30);
													// USER START (Optionally insert additional code for further widget initialization)
													// USER END				
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
WM_HWIN ToolTipCreate(void) {
  WM_HWIN hWin;
	
 // hWin = WM_CreateWindow(0, 0, 800, 480,WM_CF_SHOW, _cbDialog, 0);
	//hWin = WM_CreateWindowAsChild (0, 0, 800, 480, WM_HBKWIN, WM_CF_SHOW, &_cbDialog, 0);
		//hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	  hWin = WM_CreateWindow(200, 120, 400, 200,WM_CF_SHOW, _cbDialog, 0);
	  WM_SetHasTrans(hWin);
  return hWin;
}