#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "Setting.h"
#include "sysConf.h"
#include "skinColor.h"
#include "dlg.h"
#include "28.h"
#include "info.h"
#define ID_WINDIW_0 (GUI_ID_USER + 0x00)

#define ID_MULTIEDIT_0   (GUI_ID_USER + 0x10)
#define ID_BUTTON_0   (GUI_ID_USER + 0x11)
#define ID_LV_0 (GUI_ID_USER + 0x02)
SCROLLBAR_Handle hScrollbarv;
SCROLLBAR_Handle hScrollbarh;
const GUI_RECT Scrollbar = {709,0,719,355}; 
GUI_RECT ScrollbarI ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ETWin", ID_WINDIW_0, 0,0, 800, 480, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "Button",ID_BUTTON_0,90,10,50,30,0,0,0},
  { MULTIEDIT_CreateIndirect,"mEdit", ID_MULTIEDIT_0, 40, 70, 720, 345, 0, 0, 0}
	
};

static void InfoButton (WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	static char Pagecount = 0; // 总的信息页数
	static char thisPage = 0;			//当前所处的页数
	WM_KEY_INFO *Info;
	INFO *InfoT;
	int16_t i = 0;
	int16_t SelRow = 0;
	switch (pMsg->MsgId)
	{
			
		case WM_KEY:
			Info = (WM_KEY_INFO*)pMsg->Data.p;
		switch (Info->Key)
		{
			case GUI_KEY_LEFT:
				SCROLLBAR_AddValue(hScrollbarh,-50);
				break;
			case GUI_KEY_RIGHT:
				SCROLLBAR_AddValue(hScrollbarh,50);
				break;
			
			case GUI_KEY_BACKSPACE:
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


static void _cbDialog(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	WM_HWIN hMultiEdit;
	WM_HWIN hButton;
	WM_KEY_INFO *Info;
	CHAR str_index,str_index1;
	int count=0;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor (GUI_BLACK);
			GUI_DispStringAt("信息",40,10);
			GUI_AA_DrawLine(190,0,220,40);
			GUI_AA_DrawLine(220,40,800,40);
			GUI_DispStringAt("距发射站台距离:",580,410);
			GUI_SetFont(&GUI_Font25);
			GUI_DispStringAt("高电压警告",230,8);	
			
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
			break;
		case WM_KEY:
			Info = (WM_KEY_INFO *)pMsg->Data.p;
			switch (Info->Key)
			{
				case GUI_KEY_DOWN:
					break;
				case GUI_KEY_BACKSPACE:
					break;
			}
			break;
			
			case GUI_KEY_PGDOWN:
				INFO ("SUCCEED");
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