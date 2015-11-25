#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
#include "POWER.h"
#define ID_WINDIW_0 (GUI_ID_USER + 0x00)
#define ID_LV_0	  (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_1 (GUI_ID_USER + 0x04)
#define ID_TEXT_2 (GUI_ID_USER + 0x05)
#define ID_TEXT_3 (GUI_ID_USER + 0x06)
#define ID_MULTIEDIT_0 (GUI_ID_USER + 0x10)
#define ID_BUTTON_0	(GUI_ID_USER + 0x011)

#define ID_MENU    (GUI_ID_USER + 0x50)
#define ID_PrintMenu (GUI_ID_USER + 0x51)

extern GUI_CONST_STORAGE GUI_BITMAP bmzhongyao;
extern GUI_CONST_STORAGE GUI_BITMAP bmsar;
extern GUI_CONST_STORAGE GUI_BITMAP bmnewmsg;
extern CHAR MenuSel;
WM_HWIN mainwin;
WM_HWIN hListview;
WM_HWIN hButton;
WM_HWIN InfoText;
SCROLLBAR_Handle LISTVSCR;
CHAR thispage = 1;
CHAR pageNum = 0;
int rowNum = 16;
int InfoId;
static char InfoType = 0;
static INFO * Info;
static int rowindex = 0;
static const GUI_RECT PageRect = {560,435,770,470}; //页码显示
char SelRow;
static char cannel[9] = "4209.5横"; //频道
CHAR  *pCannel = cannel;
static CHAR SelBottom;
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
	 { BUTTON_CreateIndirect, "Button",ID_BUTTON_0,40,30,100,30,0,0,0},
  { LISTVIEW_CreateIndirect, "LV", ID_LV_0,40,80,720,350,0,0,0},
		{ TEXT_CreateIndirect,    "INT",  ID_TEXT_0, 340,28,85,30,0,0,0},
		{ TEXT_CreateIndirect,    "LOC",  ID_TEXT_1, 430,28,88,30,0,0,0},
		{ TEXT_CreateIndirect,    "time",  ID_TEXT_2, 520,28,230,30,0,0,0},
};


//
//
//
const void Infoinit(INFO *Info,char i)  //填充行信息
{
		static int Year=0,day=0,month=0,hour=0,minute=0;
		
		LISTVIEW_AddRow(hListview,NULL);	
		sprintf(pStrBuf, (Info->ID)<10?"00%d":(Info->ID)<100?"0%d":"%d", Info->ID);
		LISTVIEW_SetItemText (hListview,0,i,pStrBuf);		  //序号
		sprintf(pStrBuf, "%s", Info->codeFormat);
		LISTVIEW_SetItemText (hListview,1,i,pStrBuf);	  //编码
	 
		Year = Info->date/10000;
		month = ((Info->date)%10000)/100;
		day = (Info->date)%100;
		sprintf (pStrBuf,month<10?"%d/0%d/%d":day<10?"%d/%d/0%d":"%d/%d/%d",Year,month,day);
		LISTVIEW_SetItemText (hListview,2,i,pStrBuf);  //年月日
		hour = (Info->time)/100;
		minute = (Info->time)%100;
		sprintf(pStrBuf,(hour<10 && minute<10)?"0%d:0%d":hour<10?"0%d:%d":minute<10?"%d:0%d":"%d:%d",hour,minute);
		LISTVIEW_SetItemText(hListview, 3, i,  pStrBuf); //时间
		LISTVIEW_SetItemText(hListview, 4, i, Info->chnl==INT?"518KHz":Info->chnl==LOC1?"490KHz":Info->chnl==LOC2?"4209.5KHz":"486KHz"); //频道
	 if (Info->type == INFO_Type_None)  //信息类型
		{
			 LISTVIEW_SetItemBitmap(hListview,5,i,25,7,NULL);
		}
		else if (Info->type == INFO_Type_VIP)
		{
			 LISTVIEW_SetItemBitmap(hListview,5,i,25,7,&bmzhongyao);
		}
		else if (Info->type == INFO_Type_Rscue)
		{
			 LISTVIEW_SetItemBitmap(hListview,5,i,25,7,&bmsar);
		}
			
	 if (Info->isLocked == 0)  //信息状态
		{
				if (Info->state == INFO_STT_New)
				{
					 LISTVIEW_SetItemBitmap(hListview,6,i,10,7,&bmnewmsg);
				}
				else LISTVIEW_SetItemText(hListview,6,i,"");
		}
		else if(Info->isLocked == 1)
		{
				if (Info->state == INFO_STT_New)
				{
						LISTVIEW_SetItemBitmap(hListview,6,i,10,7,&bmnewmsg);
						LISTVIEW_SetItemText(hListview,6,i,"          锁");
				}
				else LISTVIEW_SetItemText(hListview,6,i,"          锁");
		}
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
	switch (pMsg->MsgId)
	{
			case WM_SET_FOCUS:
								if (pMsg->Data.v)
								{
											BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,GUI_GRAY);
											BUTTON_SetTextColor(hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);
											BUTTON_SetFocusColor(hButton,GUI_GRAY);
								}
								else 	
								{
									BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);//BUTTON_SetTextColor (hButton,BUTTON_CI_UNPRESSED,GUI_BLACK);
									BUTTON_SetTextColor(hButton,BUTTON_CI_UNPRESSED,GUI_BLACK);
									BUTTON_SetFocusColor(hButton,GUI_WHITE);
								}
								BUTTON_Callback(pMsg);
								break;
		
			case WM_KEY:
				    pInfo = (WM_KEY_INFO*)pMsg->Data.p;
							switch (pInfo->Key)
							{ 
								
								 case GUI_KEY_ENTER:
										    break;
									
								 case GUI_KEY_PRINT:
														WM_BringToTop(PrintWin);
														WM_SetFocus(WM_GetDialogItem(PrintWin,ID_PrintMenu));
										    break;
									case GUI_KEY_MENU:
										    WM_BringToTop(Menuwin);
										    WM_SetFocus  (WM_GetDialogItem(Menuwin,ID_MENU));
									     MENU_SetSel (WM_GetDialogItem(Menuwin,ID_MENU),0);
									     MenuSel = 0;
										    break;
				
				     case GUI_KEY_LOC1:
							       pCannel = "  490 横";
							       WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
							       break;
									
				     case GUI_KEY_LOC2:
							       pCannel = "4209.5横";
						       	WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
							       break;
									
				     case GUI_KEY_CHS:
							       pCannel = "  486 横";
							       WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
					         break;
				  
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
												  	pageNum = 1;
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
	CHAR RowLineIndex;
	const WM_KEY_INFO *pInfo;
	int16_t  i  = 0;
	static char addrow = 0;
	hWin = pMsg->hWin;

	switch (pMsg->MsgId)
	{
		 case WM_KEY:
			     pInfo = (WM_KEY_INFO*)pMsg->Data.p;
		     switch (pInfo->Key)
	      {
								  case GUI_KEY_MENU:
											    WM_BringToTop(Menuwin);
										     WM_SetFocus(WM_GetDialogItem(Menuwin,ID_MENU));
										     MENU_SetSel(WM_GetDialogItem(Menuwin,ID_MENU),0);
										     MenuSel = 0;
											    break;
								  case GUI_KEY_PRINT:
														 WM_BringToTop(PrintWin);
														 WM_SetFocus(WM_GetDialogItem(PrintWin,ID_PrintMenu));
										     break;
										
			      	case GUI_KEY_LOC1:
							        pCannel = "  490 横";
							        WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
							        break;
										
			      	case GUI_KEY_LOC2:
															pCannel = "4209.5横";
															WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
							        break;
										
			      	case GUI_KEY_CHS:
							        pCannel = "  486 横";
															WM_InvalidateWindow(WM_GetDialogItem(mainwin,ID_TEXT_1));
												  	break;
			
			       case GUI_KEY_LOCK:							
															SelRow = LISTVIEW_GetSel(hListview);
															LISTVIEW_GetItemText(hListview,0,SelRow,pStrBuf,5);
															InfoId = atoi(pStrBuf);
															Info  = pInfoHeader;
															if (pInfoHeader)
															do 
															{
																	if (Info->ID == InfoId)
																	{
																				if (Info->isLocked == 0)
																				{      
																					LISTVIEW_SetItemText(hListview,6,SelRow,"          锁");
																					Info->isLocked = 1;
																				}
																				else if (Info->isLocked == 1)
																				{
																					LISTVIEW_SetItemText(hListview,6,SelRow,"");
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
																		WM_SetFocus(hButton);
															if (thispage>1)
															{
																		if(SelRow == 0)
																		{
																					thispage--;
																					InfoSel(InfoType,thispage);
																					WM_InvalidateRect(mainwin,&PageRect);
																					GUI_StoreKeyMsg(GUI_KEY_RIGHT,1);  //选择列表中最后一行
																					SelBottom = 1;
																		}
															}
															break;
					
									case GUI_KEY_RIGHT:
														if (SelBottom == 1)
														{
																	LISTVIEW_SetSel(hListview,7);
																	SelBottom = 0;
														}
														break;
									
									case GUI_KEY_ESCAPE:
														SelRow = LISTVIEW_GetSel(hListview);
														WM_SetFocus(hButton);
														break;
				
									case GUI_KEY_ENTER:
														SelRow = LISTVIEW_GetSel(hListview);
														LISTVIEW_GetItemText(hListview,0,SelRow,pStrBuf,5);
														InfoId = atoi(pStrBuf);
														Info  = pInfoHeader;
														if (pInfoHeader)
														do 
														{
																if (Info->ID == InfoId)
																{
																			if (Info->state == INFO_STT_New)
																				LISTVIEW_SetItemBitmap(hListview,6,SelRow,10,7,NULL);
																			if (Info->isLocked == 0)
																						TEXT_SetText(WM_GetDialogItem(InfoText,ID_TEXT_0),"");
																			else TEXT_SetText(WM_GetDialogItem(InfoText,ID_TEXT_0),"锁");
																			Info->state = INFO_STT_Choosen;
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
		
	 	case WM_POST_PAINT: //行分割线
								RowNum = LISTVIEW_GetNumRows(hListview);
								GUI_SetColor(GUI_BLACK);
								for (RowLineIndex = 0; RowLineIndex<RowNum; RowLineIndex++)
												GUI_DrawLine(0,(68+40*(RowLineIndex)),720,(68+40*(RowLineIndex)));

		 default :
			     LISTVIEW_Callback(pMsg);
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
											case ID_TEXT_0:
																GUI_SetBkColor(GUI_WHITE);
																GUI_Clear();
																GUI_SetColor(GUI_BLACK);
																GUI_FillRoundedRect(0,0,80,25,5);
																GUI_SetTextMode(GUI_TEXTMODE_TRANS);
																GUI_SetColor(GUI_WHITE);
																GUI_SetFont (&GUI_Font24);
																GUI_DispStringAt("518 横",5,2);
																break;
											
											case ID_TEXT_1:
																GUI_SetBkColor(GUI_WHITE);
																GUI_Clear();
																GUI_SetColor(GUI_BLACK);
																GUI_FillRoundedRect(0,0,83,25,5);
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
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	
	WM_HWIN hListhead;
	WM_HWIN hWin;
	WM_HWIN hText;
	const WM_KEY_INFO* pInfo;
	WM_HWIN  hItem  = 0;
  int     i  = 0;
  int     NCode;
  int     Id;
	hWin = pMsg->hWin;
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) 
	{
				case WM_PAINT:
									GUI_SetBkColor(GUI_WHITE);
									GUI_Clear();
									GUI_SetColor(GUI_BLACK);
									GUI_AA_DrawLine(190,0,220,60);
									GUI_AA_DrawLine(220,60,800,60);
									GUI_DispStringAt("所处      页/共      页",560,435);		
									GUI_DispDecAt(thispage,605,435,3);
									GUI_DispDecAt(pageNum,700,435,3);
									GUI_SetFont(&GUI_Font24);
									//GUI_DispStringAt("高电压警告",230,28);
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
							HEADER_SetFont(hListhead,&GUI_Font24);
							LISTVIEW_AddColumn(hListview,80,"序号",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,100,"信息编码",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,130,"yy/mm/dd",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,90,"hh:mm",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,120,"频道",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,100,"信息类型",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_AddColumn(hListview,100,"信息状态",GUI_TA_HCENTER|GUI_TA_VCENTER);
							LISTVIEW_SetTextAlign(hListview,6,GUI_TA_LEFT|GUI_TA_VCENTER);
							
							// TEXT0
							hText = WM_GetDialogItem(hWin,ID_TEXT_0);
							WM_SetCallback(hText,&mytext);
							
							// TEXT1
							hText = WM_GetDialogItem(hWin,ID_TEXT_1);
							WM_SetCallback(hText,&mytext);			
							
							//time
							hText = WM_GetDialogItem(hWin,ID_TEXT_2);
							TEXT_SetTextAlign(hText,TEXT_CF_VCENTER);
							TEXT_SetFont(hText,&GUI_Font30);
							TEXT_SetText(hText,"UTC 2015.10.24 17:30");
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
		hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}