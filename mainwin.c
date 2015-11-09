#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "Setting.h"
#include "sysConf.h"
#include "skinColor.h"
#include "dlg.h"
#include "28.h"

#define ID_WINDIW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0	(GUI_ID_USER + 0x01)
#define ID_LV_0	(GUI_ID_USER + 0x02)
WM_HWIN mainwin;
WM_HWIN hListview;
WM_HWIN hButton;
WM_HWIN InfoText;
char InfoType = 0;
static const GUI_RECT InfoRect = {0,0,800,480};
 GUI_ConstString Alldata[8][7] = {
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","","新信息"},
	{"017","AL33","2015/09/19","10:02","518KHz","重要","新信息"},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","搜救","新信息"},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","搜救","新信息"},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","重要",""},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","重要",""},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","",""},
	{"018",	"QA74","2015/09/19","13:02","4209.5KHz","",""},
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ETWin", ID_WINDIW_0, 0,0, 800, 480, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button",ID_BUTTON_0,40,10,100,30,0,0,0},
  { LISTVIEW_CreateIndirect, "LV", ID_LV_0,40,60,720,350,0,0,0}
};

//
//选择信息类型
//
void InfoTypeChange(CHAR index,CHAR * infotype)
{
	char row_index,row,column;
	for (row_index = 0; row_index<8;row_index++) //删除所有的行
		LISTVIEW_DeleteRow(hListview,0);
	
	for (row_index = 0,row=0; row_index<8;row_index++) 
	{
		if( strncmp (Alldata[row_index][index],infotype,4) == 0)  //判断要添加的行
		{
			LISTVIEW_AddRow (hListview,NULL);												//添加所需的行
			for (column = 0; column < 7; column++)                  //填充信息
				LISTVIEW_SetItemText(hListview,column,row,Alldata[row_index][column]);
			row++;
		}
	}
}

//
// Buttoncallback;
//
void mybutton (WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	WM_KEY_INFO *Info;
	CHAR column,row,row_index,del_row;
	int flag;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_KEY:
			Info = (WM_KEY_INFO*)pMsg->Data.p;
		switch (Info->Key){

			
			case GUI_KEY_UP:
				break;
			case GUI_KEY_DOWN:
				WM_SetFocus(hListview);
				LISTVIEW_SetSel(hListview,0);
				break;
			
			case GUI_KEY_LEFT:
				if(InfoType > 0)
					InfoType--;
				else InfoType = 3;
				switch (InfoType)
				{
					case 0:
					BUTTON_SetText(hWin,"所有信息");
					row = LISTVIEW_GetNumRows(hListview);
					for (;row<8;row++)
					LISTVIEW_AddRow (hListview,NULL);
					for (row = 0; row<8; row++)
					{
						for (column = 0; column <7; column++)
							LISTVIEW_SetItemText(hListview,column,row,Alldata[row][column]);
					}
					break;
					
					case 1:
						BUTTON_SetText(hWin,"重要信息");
						InfoTypeChange (5,"重要信息");
 					break;
					
					case 2:
						BUTTON_SetText(hWin,"新信息");
						InfoTypeChange (6,"新信息");
					break;
					
					case 3:
						BUTTON_SetText(hWin,"搜救信息");
						InfoTypeChange(5,"搜救信息");
						break;
				}
				break;
			case GUI_KEY_RIGHT:
				InfoType++;
				if(InfoType == 4)
					InfoType = 0;
				switch (InfoType)
				{
					case 0:
						BUTTON_SetText(hWin,"所有信息");
					row = LISTVIEW_GetNumRows(hListview);
					for (;row<8;row++)
					LISTVIEW_AddRow (hListview,NULL);
					for (row = 0; row<8; row++)
					{
						for (column = 0; column <7; column++)
							LISTVIEW_SetItemText(hListview,column,row,Alldata[row][column]);
					}					
					break;
					
					case 1:
						BUTTON_SetText(hWin,"重要信息");
						InfoTypeChange(5,"重要信息");
					break;
					
					case 2:
						BUTTON_SetText(hWin,"新信息");
						InfoTypeChange(6,"新信息");
					break;
					
					case 3:
						BUTTON_SetText(hWin,"搜救信息");
						InfoTypeChange(5,"搜救信息");			
						break;
			}
		}
			break;
		
		default :
			BUTTON_Callback(pMsg);
		break;
	}
}
//
//ListviewCallback
//

static void mylistview(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	CHAR RowNum;
	char SelRow;
	CHAR RowLineIndex;
	const WM_KEY_INFO *Info;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_KEY:
			Info = (WM_KEY_INFO*)pMsg->Data.p;
		switch (Info->Key)
		{
			case GUI_KEY_DOWN:
				SelRow = LISTVIEW_GetSel(hListview);
			if (SelRow == 7) //翻页条件
			{INFO("SELROW");}
				break;
			case GUI_KEY_UP:
				SelRow = LISTVIEW_GetSel(hListview);
			INFO("SELROW = %d",SelRow);
 				if (0 == LISTVIEW_GetSel(hWin))
				{
					WM_SetFocus(hButton);
				}
				break;
				case GUI_KEY_BACKSPACE:
					WM_SetFocus(hButton);
				break;
				
				case GUI_KEY_ENTER:
					INFO ("ENTER");
 					WM_BringToTop (InfoText);
 					WM_SetFocus (InfoText);
 					//WM_HideWindow();
 					//WM_InvalidateArea(&InfoRect);
					break;
			
		}
		
		case WM_POST_PAINT:
			RowNum = LISTVIEW_GetNumRows(hListview);
//INFO("RowNum = %d",RowNum);
				GUI_SetColor(GUI_BLACK);
				for (RowLineIndex = 0; RowLineIndex<RowNum; RowLineIndex++)
					{	GUI_DrawLine(0,(69+40*(RowLineIndex)),720,(69+40*(RowLineIndex)));
//INFO ("RowLineIndex = %d",RowLineIndex);					
}
		
		default :
			LISTVIEW_Callback(pMsg);
		break;
	}
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	
	WM_HWIN hListhead;
	WM_HWIN hWin;
	const WM_KEY_INFO* pInfo;
	WM_HWIN  hItem  = 0;
  int     i  = 0;
  int     NCode;
  int     Id;
	hWin = pMsg->hWin;
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
		
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor(GUI_BLACK);
			//GUI_DispStringAt("所有信息",40,10);
			GUI_AA_DrawLine(190,0,220,40);
			GUI_AA_DrawLine(220,40,800,40);
			GUI_DispStringAt("所处02页/共014页",580,410);
			GUI_SetFont(&GUI_Font25);
			GUI_DispStringAt("高电压警告",230,8);
			
			break;
		
		case WM_INIT_DIALOG:
			
			//hButton = BUTTON_CreateEx(40,10,100,30,mainwin,WM_CF_SHOW,0,GUI_ID_BUTTON0);
			hButton = WM_GetDialogItem (hWin,ID_BUTTON_0);
			BUTTON_SetBkColor (hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);
			BUTTON_SetTextColor (hButton,BUTTON_CI_UNPRESSED,GUI_BLACK);
			BUTTON_SetTextAlign (hButton,GUI_TA_HCENTER|GUI_TA_VCENTER);
			BUTTON_SetText(hButton,"所有信息");
			BUTTON_SetFocusColor (hButton,GUI_WHITE);
			WIDGET_SetEffect (hButton,&WIDGET_Effect_None);
			WM_SetCallback (hButton,&mybutton);
			WM_SetFocus (hButton);
			hListview = WM_GetDialogItem (hWin,ID_LV_0);
			hListhead = LISTVIEW_GetHeader(hListview);
			LISTVIEW_SetFont(hListview,&GUI_Font30);
			LISTVIEW_SetRowHeight(hListview,40);
		  LISTVIEW_SetHeaderHeight(hListview,30);
			LISTVIEW_SetBkColor (hListview,LISTVIEW_CI_SELFOCUS,GUI_GRAY);
			LISTVIEW_SetBkColor (hListview,LISTVIEW_CI_SEL,GUI_WHITE);
			LISTVIEW_SetTextColor (hListview,LISTVIEW_CI_SEL,GUI_BLACK);
			LISTVIEW_SetTextColor(hListview,LISTVIEW_CI_SELFOCUS,GUI_WHITE);
			WIDGET_SetEffect(hListhead,&WIDGET_Effect_3D);
			HEADER_SetBkColor (hListhead,GUI_BLACK);
			HEADER_SetTextColor(hListhead,GUI_WHITE);
			HEADER_SetFont(hListhead,&GUI_Font25);
			LISTVIEW_AddColumn(hListview,80,"序号",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,100,"信息编码",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,130,"yy/mm/dd",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,90,"hh:mm",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,120,"频道",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,100,"信息类型",GUI_TA_HCENTER|GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hListview,100,"信息状态",GUI_TA_HCENTER|GUI_TA_VCENTER);
			for (i = 0; i < 8; i++)
			{
					LISTVIEW_AddRow(hListview,Alldata[i]);
			}
			WM_SetCallback (hListview,&mylistview);
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
WM_HWIN mainWinCreate(void) {
  WM_HWIN hWin;
	
 // hWin = WM_CreateWindow(0, 0, 800, 480,WM_CF_SHOW, _cbDialog, 0);
	//hWin = WM_CreateWindowAsChild (0, 0, 800, 480, WM_HBKWIN, WM_CF_SHOW, &_cbDialog, 0);
		hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}