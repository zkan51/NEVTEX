#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "Setting.h"
#include "sysConf.h"
#include "skinColor.h"
#include "dlg.h"
#include "28.h"

#define ID_WINDIW_0 (GUI_ID_USER + 0x00)

#define ID_MULTIEDIT_0   (GUI_ID_USER + 0x10)
#define ID_BUTTON_0   (GUI_ID_USER + 0x11)
#define PAGE  0x0401 
#define PAGE_NUM  12
WM_MESSAGE TurnPage;
CHAR *str = {"Warn1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n"};
const GUI_RECT Scrollbar = {709,0,719,355}; 
GUI_RECT ScrollbarI ;
//			hMultiEdit = MULTIEDIT_CreateEx(40,60,720,350,InfoText,WM_CF_SHOW,MULTIEDIT_CF_AUTOSCROLLBAR_V,0,0,i);

static char Info_Page (CHAR *str)  //返回信息的总页数
{
	CHAR strindex =0;
	CHAR count = 0;
	for (strindex = 0; str[strindex] != NULL; strindex++)
	{
		if (str[strindex] == '\n')
			count++;
	}
	return count/PAGE_NUM;
}

static void DispInfo(CHAR ThisPage,CHAR* str) //更改MULTEDIT文本信息
{
	CHAR str1[50] = {""};
	CHAR index = 0;
	CHAR index1 = 0;
	CHAR row= 0;
INFO ("discount = %d",ThisPage);
	for (index = 0,index1 = 0; str[index] != NULL;index++)
	{
			if (str[index] == '\n')
				row++;
			if (row >= ThisPage*PAGE_NUM)
			{
				if (ThisPage > 0 && index1 == 0)
					index++;
				str1[index1] = str[index];
				index1++;
			}
	}
	MULTIEDIT_SetText(WM_GetDialogItem(InfoText, ID_MULTIEDIT_0),str1);
}

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ETWin", ID_WINDIW_0, 0,0, 800, 480, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button",ID_BUTTON_0,40,10,100,30,0,0,0},
  { MULTIEDIT_CreateIndirect,"mEdit", ID_MULTIEDIT_0, 40, 55, 720, 360, 0, 0, 0}
	
};

static void InfoButton (WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	static char Pagecount = 0; // 总的信息页数
	static char thisPage = 0;			//当前所处的页数
	WM_KEY_INFO *Info;
	switch (pMsg->MsgId)
	{
		case WM_KEY:
			Info = (WM_KEY_INFO*)pMsg->Data.p;
		switch (Info->Key)
		{
			case GUI_KEY_BACKSPACE:
				INFO ("backtomain");
				WM_BringToTop(mainwin);
				WM_SetFocus (mainwin);
				break;
			
			case GUI_KEY_UP:
				
				TurnPage.MsgId = PAGE;
				if (thisPage >0)
					thisPage--;
				TurnPage.Data.v = thisPage;
				TurnPage.hWin = WM_GetDialogItem(InfoText, ID_MULTIEDIT_0);
				WM_SendMessage(TurnPage.hWin,&TurnPage);				
				break;
			
			case GUI_KEY_DOWN:
				INFO ("SENDMESSAGE");
				Pagecount = Info_Page(str); 
				TurnPage.MsgId = PAGE;
				if (thisPage < Pagecount)
					thisPage++;
INFO ("thisPage = %d,count = %d",thisPage,Pagecount);				
				TurnPage.Data.v = thisPage;
				TurnPage.hWin = WM_GetDialogItem(InfoText, ID_MULTIEDIT_0);
				WM_SendMessage(TurnPage.hWin,&TurnPage);
				break;
		}
		break;

		default:		
		BUTTON_Callback(pMsg);
		break;
	}
}

static void myMultiEdit(WM_MESSAGE *pMsg)
{
	const WM_KEY_INFO *Info;
	static CHAR Page = 0;
	WM_HWIN hWin = pMsg->hWin;
	//INFO ("MSG = %d",pMsg->MsgId);
	switch (pMsg->MsgId)
	{
		case PAGE:
			DispInfo (TurnPage.Data.v ,str);
		break;

		case WM_POST_PAINT :   //绘制滚动条
			Page = Info_Page(str);
			switch (TurnPage.Data.v)  
			{
				case 0:
					ScrollbarI.x0 = 709;
					ScrollbarI.y0 = 0;
					ScrollbarI.x1 = 725;
					ScrollbarI.y1 =355/(Page+1);

					GUI_SetColor(GUI_GRAY);
					GUI_FillRectEx(&Scrollbar);
					GUI_SetColor(GUI_RED);
					GUI_FillRectEx(&ScrollbarI);					
					break;
				case 1:
					ScrollbarI.x0 = 709;
					ScrollbarI.y0 = 355/(Page+1);
					ScrollbarI.x1 = 725;
					ScrollbarI.y1 =2*(355/(Page+1));
	
					GUI_SetColor(GUI_GRAY);
					GUI_FillRectEx(&Scrollbar);
					GUI_SetColor(GUI_RED);
					GUI_FillRectEx(&ScrollbarI);						
					break;
			}
			GUI_SetColor (GUI_BLACK);
			GUI_DispStringAt("误字符率:",580,5);
			GUI_SetPenSize (2);
			GUI_DrawLine(0,355,720,355);
			break;
		default:
			MULTIEDIT_Callback(pMsg);
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
			GUI_DispStringAt("信息0",40,10);
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
		  MULTIEDIT_SetText(hMultiEdit,str );
		  MULTIEDIT_SetTextColor(hMultiEdit, MULTIEDIT_CI_READONLY,GUI_RED);
 			WM_SetCallback(hMultiEdit,&myMultiEdit);
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