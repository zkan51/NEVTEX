#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "Setting.h"
#include "sysConf.h"
#include "skinColor.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
#define ID_WINDIW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0	(GUI_ID_USER + 0x011)
#define ID_LV_0	(GUI_ID_USER + 0x02)
#define ID_MULTIEDIT_0 (GUI_ID_USER + 0x10)


WM_HWIN mainwin;
WM_HWIN hListview;
WM_HWIN hButton;
WM_HWIN InfoText;
SCROLLBAR_Handle LISTVSCR;
CHAR thispage = 1;
CHAR pageNum = 0;
int rowNum = 16;
static char InfoType = 0;
static INFO * Info;
extern void Pageit (char*);
static int rowindex = 0;
static const GUI_RECT PageRect = {560,415,770,450};
INFO TESTDATA[16] = {
	{1,"EA31",20151111,1303,INT,INFO_Type_None,INFO_STT_CSTOFF,0,strt[0]},
	{2,"LA56",20150111,303,LOC1,INFO_Type_None,INFO_STT_Choosen,0,strt[1]},
	{3,"LA46",20151101,1303,LOC1,INFO_Type_VIP,INFO_STT_None,0,strt[2]},
	{4,"ME75",20151111,1303,LOC2,INFO_Type_VIP,INFO_STT_None,0,strt[3]},
	{5,"MA50",20151112,1303,CHS,INFO_Type_Rscue,INFO_STT_None,0,strt[4]},
	{6,"OA29",20151112,1303,INT,INFO_Type_Rscue,INFO_STT_None,0,strt[5]},
	{7,"PA96",20151112,1303,INT,INFO_Type_Rscue,INFO_STT_None,0,strt[6]},
	{8,"QE57",20151112,1303,INT,INFO_Type_None,INFO_STT_None,0,strt[7]},
	{9,"QE58",20151112,1303,INT,INFO_Type_None,INFO_STT_None,0,strt[7]},
	{10,"QE59",20151112,1303,INT,INFO_Type_None,INFO_STT_None,0,strt[7]},
	{11,"MA50",20151112,1303,CHS,INFO_Type_Rscue,INFO_STT_None,0,strt[4]},
	{12,"OA29",20151112,1303,INT,INFO_Type_Rscue,INFO_STT_None,0,strt[5]},
	{13,"PA96",20151112,1303,INT,INFO_Type_Rscue,INFO_STT_None,0,strt[6]},
	{14,"QE57",20151112,1303,INT,INFO_Type_None,INFO_STT_None,0,strt[7]},
	{15,"QE58",20151112,1303,INT,INFO_Type_None,INFO_STT_None,1,strt[7]},
	{16,"QE59",20151112,1303,INT,INFO_Type_None,INFO_STT_New,1,strt[7]},
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ETWin", ID_WINDIW_0, 0,0, 800, 480, 0, 0x0, 0 },
	 { BUTTON_CreateIndirect, "Button",ID_BUTTON_0,40,10,100,30,0,0,0},
  { LISTVIEW_CreateIndirect, "LV", ID_LV_0,40,60,720,350,0,0,0}
};


//
//
//
const void Infoinit(INFO *Info,char i)
{
		static int Year=0,day=0,month=0,hour=0,minute=0;
		
		LISTVIEW_AddRow(hListview,NULL);	
		sprintf(pStrBuf, (Info->ID)<10?"00%d":(Info->ID)<100?"0%d":"%d", Info->ID);
		LISTVIEW_SetItemText (hListview,0,i,pStrBuf);		
		sprintf(pStrBuf, "%s", Info->codeFormat);
		LISTVIEW_SetItemText (hListview,1,i,pStrBuf);	
	 
		Year = Info->date/10000;
		month = ((Info->date)%10000)/100;
		day = (Info->date)%100;
		sprintf (pStrBuf,month<10?"%d/0%d/%d":day<10?"%d/%d/0%d":"%d/%d/%d",Year,month,day);
		LISTVIEW_SetItemText (hListview,2,i,pStrBuf);
		hour = (Info->time)/100;
		minute = (Info->time)%100;
		sprintf(pStrBuf,(hour<10 && minute<10)?"0%d:0%d":hour<10?"0%d:%d":minute<10?"%d:0%d":"%d:%d",hour,minute);
		LISTVIEW_SetItemText(hListview, 3, i,  pStrBuf);
		LISTVIEW_SetItemText(hListview, 4, i, Info->chnl==INT?"518KHz":Info->chnl==LOC1?"490KHz":Info->chnl==LOC2?"4209.5KHz":"486KHz");
		LISTVIEW_SetItemText(hListview, 5, i, Info->type==INFO_Type_None?"":Info->type==INFO_Type_VIP?"重要":"搜救");
	 if (Info->isLocked == 0)
		{
			if (Info->state == INFO_STT_New)
			{
				LISTVIEW_SetItemText(hListview,6,i,"新信息");
			}
			else LISTVIEW_SetItemText(hListview,6,i,"");
		}
		else if(Info->isLocked == 1)
		{
			if (Info->state == INFO_STT_New)
			{
				LISTVIEW_SetItemText(hListview,6,i,"新信息 锁");
			}
			else LISTVIEW_SetItemText(hListview,6,i,"           锁");
		}
		//LISTVIEW_SetItemText(hListview, 6, i, (Info->state==INFO_STT_New && Info->isLocked == 0)?"新信息":(Info->state==INFO_STT_New && Info->isLocked == 1)?"新信息锁":);
}

//
//信息类型
//
const void InfoSel (char Type,CHAR thpage)
{
	char index = 0;
	int16_t addrow = 0;
 Info  = INFO_LIST_Reset();
	rowindex = 0;
 if(pInfoTail)
 do
 {	
		if (Type == 0)  //所有信息
		{
			if(rowindex >= (thispage-1)*8 && rowindex < ((thispage-1)*8+8))
			{
				if (rowindex == (thispage-1)*8)
					LISTVIEW_DeleteAllRows(hListview);
				Infoinit(Info,addrow);
				addrow++;
			}
			rowindex++;			
		}
		else if (Type == 1) //重要信息
		{
			if(Info->type == INFO_Type_VIP)
			{
				if(rowindex >= (thispage-1)*8 && rowindex < ((thispage-1)*8+8))
				{
					if (rowindex == (thispage-1)*8)
						LISTVIEW_DeleteAllRows(hListview);
					Infoinit(Info,addrow);
					addrow++;
				}
			rowindex++;	
			}
		}
		else if (Type == 2) //新信息
		{
			if (Info->state == INFO_STT_New)
			{	INFO ("NEW");
				if(rowindex >= (thispage-1)*8 && rowindex < ((thispage-1)*8+8))
				{
					if (rowindex == (thispage-1)*8)
						LISTVIEW_DeleteAllRows(hListview);
					Infoinit(Info,addrow);
					addrow++;
				}
				rowindex++;	
			}
		}
		else if (Type == 3) //搜救信息
		{
			if (Info->type == INFO_Type_Rscue)
			{
			if(rowindex >= (thispage-1)*8 && rowindex < ((thispage-1)*8+8))
			{
				if (rowindex == (thispage-1)*8)
					LISTVIEW_DeleteAllRows(hListview);
				Infoinit(Info,addrow);
				addrow++;
			}
			rowindex++;	
			}	
		}
 }while(Info = INFO_LIST_hasPrev());
}


//
// Buttoncallback;
//
void mybutton (WM_MESSAGE *pMsg)
{
	WM_HWIN hWin;
	WM_KEY_INFO *pInfo;
	int column,row,row_index,del_row;
	int flag;
	hWin = pMsg->hWin;
//INFO ("MSG = %d",pMsg->MsgId);
	switch (pMsg->MsgId)
	{
		case WM_SET_FOCUS:
		if (pMsg->Data.v)
		{
					BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,GUI_GRAY);
					BUTTON_SetFocusColor(hButton,GUI_GRAY);
		}
		else 	
		{
			BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);//BUTTON_SetTextColor (hButton,BUTTON_CI_UNPRESSED,GUI_BLACK);
			BUTTON_SetFocusColor(hButton,GUI_WHITE);
		}
			BUTTON_Callback(pMsg);
		break;
		
		case WM_KEY:
			pInfo = (WM_KEY_INFO*)pMsg->Data.p;
		switch (pInfo->Key)
		{
			case GUI_KEY_UP:
				break;
			case GUI_KEY_DOWN:
				if (LISTVIEW_GetNumRows(hListview))
				{
					thispage = 1;
					WM_SetFocus(hListview);
					LISTVIEW_SetSel(hListview,0);
					WM_InvalidateRect(mainwin,&PageRect);  //刷新页数提示
				}
				break;
			
			case GUI_KEY_LEFT:
				if(InfoType > 0)
					InfoType--;
				else InfoType = 3;
				switch (InfoType)
				{
					case 0:
					BUTTON_SetText(hWin,"所有信息");
					LISTVIEW_DeleteAllRows(hListview);
					InfoSel(0,1);
					break;
					
					case 1:
						BUTTON_SetText(hWin,"重要信息");
					LISTVIEW_DeleteAllRows(hListview);
						InfoSel(1,1);
 					break;
					
					case 2:
						BUTTON_SetText(hWin,"新信息");
					LISTVIEW_DeleteAllRows(hListview);
						InfoSel(2,1);
					break;
					
					case 3:
						BUTTON_SetText(hWin,"搜救信息");
						LISTVIEW_DeleteAllRows(hListview);
						InfoSel(3,1);					
						break;
				}
				if (rowindex<8)
				{	
					pageNum = 1;
				}
				else if (rowindex%8 == 0)
					pageNum = rowindex/8;
				else pageNum = rowindex/8+1;
				
				thispage = 1;
				WM_InvalidateRect(mainwin,&PageRect);//刷新页数提示
				break;
			case GUI_KEY_RIGHT:
				InfoType++;
				if(InfoType == 4)
					InfoType = 0;
				switch (InfoType)
				{
					case 0:
						BUTTON_SetText(hWin,"所有信息");
						LISTVIEW_DeleteAllRows(hListview);
					 InfoSel(0,1);
					break;
					
					case 1:
						BUTTON_SetText(hWin,"重要信息");
						LISTVIEW_DeleteAllRows(hListview);
					 InfoSel(1,1);
					break;
					
					case 2:
						BUTTON_SetText(hWin,"新信息");
						LISTVIEW_DeleteAllRows(hListview);
					 InfoSel(2,1);
					break;
					
					case 3:
						BUTTON_SetText(hWin,"搜救信息");
						LISTVIEW_DeleteAllRows(hListview);
					 InfoSel(3,1);		
						break;
				}
				if (rowindex<8)
				{	
					pageNum = 1;
				}
				else if (rowindex%8 == 0)
					pageNum = rowindex/8;
				else pageNum = rowindex/8+1;
				
				thispage = 1;				
				WM_InvalidateRect(mainwin,&PageRect);//刷新页数提示
				break;
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
	const WM_KEY_INFO *pInfo;
	int ID;
	int16_t  i  = 0;
	static char addrow = 0;
	hWin = pMsg->hWin;

	//INFO ("MSG = %d",pMsg->MsgId);
	switch (pMsg->MsgId)
	{
		case WM_KEY:
			pInfo = (WM_KEY_INFO*)pMsg->Data.p;
		switch (pInfo->Key)
		{
			case GUI_KEY_MENU:								
				
					SelRow = LISTVIEW_GetSel(hListview);
					LISTVIEW_GetItemText(hListview,0,SelRow,pStrBuf,5);
					ID = atoi(pStrBuf);
					Info  = pInfoHeader;
					if (pInfoHeader)
					do 
					{
						if (Info->ID == ID)
						{
							if (Info->isLocked == 0)
							{                                  
								LISTVIEW_SetItemText(hListview,6,SelRow,Info->state == INFO_STT_New?"新信息 锁":"           锁");
									Info->isLocked = 1;
							}
							else if (Info->isLocked == 1)
							{
								LISTVIEW_SetItemText(hListview,6,SelRow,Info->state == INFO_STT_New?"新信息":"");
								Info->isLocked = 0;
							}
							break;
						}
					}while (Info = Info->pNext);
			 break;
					 
			case GUI_KEY_DOWN:

 				SelRow = LISTVIEW_GetSel(hListview);
				
				if (thispage < pageNum)
				{
					if (SelRow == 7)
					{
						thispage++;
						InfoSel(InfoType,thispage);
						WM_InvalidateRect(mainwin,&PageRect);
					}
				}
				break;
				
			case GUI_KEY_UP:
				

					SelRow = LISTVIEW_GetSel(hListview);

					if(SelRow == 0 && thispage == 1)
					{
						WM_SetFocus(hButton);
					}

					if (thispage>1)
					{
						if(SelRow == 0)
						{
							thispage--;
							InfoSel(InfoType,thispage);
							WM_InvalidateRect(mainwin,&PageRect);
							LISTVIEW_SetSel(hListview,7);
							INFO ("PAGETURN");
						}
					}
					
				break;
					
				case GUI_KEY_BACKSPACE:
					SelRow = LISTVIEW_GetSel(hListview);
					WM_SetFocus(hButton);
				break;
				
				case GUI_KEY_ENTER:
					SelRow = LISTVIEW_GetSel(hListview);
					LISTVIEW_GetItemText(hListview,0,SelRow,pStrBuf,5);
					ID = atoi(pStrBuf);
				INFO ("ID = %d",ID);
				 Info  = pInfoHeader;
					if (pInfoHeader)
					do 
					{
							if (Info->ID == ID)
							{
								Info->state = INFO_STT_None;
								LISTVIEW_SetItemText(hListview,6,SelRow,"");
								sprintf(pStrBuf,"%s",pStrBuf);
								BUTTON_SetText(WM_GetDialogItem(InfoText,ID_BUTTON_0),pStrBuf);
								MULTIEDIT_SetText(WM_GetDialogItem(InfoText, ID_MULTIEDIT_0),Info->pContent);
								break;
							}
					}while (Info = Info->pNext);
 					WM_BringToTop (InfoText);
 					WM_SetFocus (InfoText);
					
					break;

		}
		
		case WM_POST_PAINT:
			RowNum = LISTVIEW_GetNumRows(hListview);
				GUI_SetColor(GUI_BLACK);
				for (RowLineIndex = 0; RowLineIndex<RowNum; RowLineIndex++)
					{	GUI_DrawLine(0,(69+40*(RowLineIndex)),720,(69+40*(RowLineIndex)));
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
			GUI_AA_DrawLine(190,0,220,40);
			GUI_AA_DrawLine(220,40,800,40);
			GUI_DispStringAt("所处      页/共      页",560,415);		
 		GUI_DispDecAt(thispage,605,415,3);
			GUI_DispDecAt(pageNum,700,415,3);
			GUI_SetFont(&GUI_Font25);
			GUI_DispStringAt("高电压警告",230,8);
			GUI_SetColor(GUI_RED);
			
			break;
		
		case WM_INIT_DIALOG:
			
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
			LISTVIEW_SetTextAlign(hListview,6,GUI_TA_LEFT);
				for (i=0;	i<16; i++)
				{
					INFO_add(&TESTDATA[i]);
				}
				if (rowNum < 8)
					pageNum = 1;
				else if (rowNum%8 == 0)
					pageNum = rowNum/8;
				else pageNum = rowNum/8+1;	
				InfoSel(0,1);
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