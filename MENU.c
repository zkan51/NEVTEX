#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "str.h"
#include "28.h"

char CheckFlag = 0;
static WM_MESSAGE ColorSel;
extern char* ptipText;
extern WM_HWIN ToolTip_BUTTON[2];
extern WM_HWIN ToolTipText0;
extern WM_HWIN ToolTipText1;
static int MenuThird = 0;
GUI_RECT *pRect;
static int MenuActiveId;
static char RevSel[5][26] = {0}; //频道接收设置
static int Receiveindex = 0;
static char OutPutSel[2][26] = {0}; //输出设置
static int OutPutIndex = 0;
char MenuSel = 0;
char Color = 0; //颜色0:白底,1:黑底
	MENU_Handle hMenu;  // 主菜单
	//二级菜单
	MENU_Handle hSiteSel1,hInfoSel1,hPortSet,hSysSet;  // 站点选择，信息选择，端口设置，系统设置
	//三级菜单
	MENU_Handle hFourCel,hInterCel1,hLocal1,hLocal2,hChinaCel;//四频道同步选择，国际频道，本地频道，中文频道
	MENU_Handle hSiteSel2,hInfoSel2; //站点选择，信息选择
	MENU_Handle hDispSet,hAlarmSet,hKeySound,hTimeSet,   // 显示设置 ，报警音，按键音设置，时间设置，语言设置，
				hLanguaSet,hAntenSet,hSoftUpdate,hReset; //天线设置，软件更新，恢复出厂设置
	// 四级菜单
	MENU_Handle hReceive,hOutput; // 接收， 输出
	MENU_Handle hUncolor,hSleep; // 反色，睡眠
	WM_HWIN Menuwin;
	
	static void _SetMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_SetItem(hMenu,Item.Id,&Item);
}

static void _AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_AddItem(hMenu, &Item);
}
//
//
//
static void MenuCall(WM_MESSAGE* pMsg)
{
	WM_HWIN hWin  = pMsg->hWin;
	const WM_KEY_INFO *pInfo;
	int MenuID;
 MenuID = WM_GetId(hWin);
	switch (pMsg->MsgId)
	{
	 	case USER_MSG_SKIN:
				    //MENU_SetBkColor(hWin,MENU_CI_ENABLED,GUI_GRAY);
				    break;
		
 		case WM_KEY:
 			   pInfo = (WM_KEY_INFO*)pMsg->Data.p;
						 switch (pInfo->Key)			
						 {
								case GUI_KEY_PRINT:
									    WM_BringToTop(PrintWin);
								     WM_SetFocus(WM_GetDialogItem(PrintWin,ID_PrintMenu));
								     break;
								case GUI_KEY_MENU:		  
									    WM_BringToTop(mainwin);
								     WM_SetFocus (mainwin);
								  	  break;
								
						  	case GUI_KEY_RIGHT:
						  	case GUI_KEY_LEFT:
									     if (MenuActiveId >= ID_FOUR_RECEIVE_0 && MenuActiveId <= ID_CHS_RECEIVE_4) //设置接收不接受
														{   
															   Receiveindex = MenuActiveId - 2081;
																		//Receiveindex %= 5;
															   if (RevSel[Receiveindex/5][Receiveindex] == 0)
																		{
  																			sprintf(pStrBuf,"%c""%s",Receiveindex%5+65,"不接收");
																			 _SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																			 RevSel[Receiveindex/5][Receiveindex] = 1;
																		}
																		else
																		{
																			 sprintf(pStrBuf,"%c""%s",Receiveindex%5+65,"接收");
																			 _SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																			 RevSel[Receiveindex/5][Receiveindex] = 0;
																		}
														}
														else if (MenuActiveId >= ID_SITE_OUTPUT_0 && MenuActiveId <= ID_INFO_OUTPUT_0) //设置输出、不输出
														{
															   OutPutIndex = MenuActiveId - 2160;
															   if (OutPutSel[OutPutIndex/5][OutPutIndex] == 0)
																		{
  																			sprintf(pStrBuf,"%c""%s",OutPutIndex%5+65,"不输出");
																			 _SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																			 OutPutSel[OutPutIndex/5][OutPutIndex] = 1;
																		}
																		else
																		{
																			 sprintf(pStrBuf,"%c""%s",OutPutIndex%5+65,"输出");
																			 _SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																			 OutPutSel[OutPutIndex/5][OutPutIndex] = 0;
																		}
														}
														
														if (MenuActiveId == ID_INVERSE)  //显示设置
														{
															   if (Color == 0)
																		{
  																			Color = 1;
																					_SetMenuItem(hWin,0,"反色显示 关闭",MenuActiveId,0);
																			  ColorSel.MsgId = USER_MSG_SKIN;
																			  ColorSel.hWinSrc = hWin;
																			  ColorSel.Data.v = Color;
																			  WM_BroadcastMessage(&ColorSel);
																		}
																		else 
																		{
																			  Color = 0;
																			  _SetMenuItem(hWin,0,"反色显示 开启",MenuActiveId,0);
																			  ColorSel.MsgId = USER_MSG_SKIN;
																			  ColorSel.hWinSrc = hWin;
																			  ColorSel.Data.v = Color;
																			  WM_BroadcastMessage(&ColorSel);
																		}
														}
								     	break;
									case GUI_KEY_ESCAPE:
												  MenuThird = 0;
									     if (MenuActiveId >= ID_SITESEL && MenuActiveId <= ID_SYSSET)
														break;
									case GUI_KEY_ENTER:
														MenuThird = 0;
									
									default :
									    MENU_Callback(pMsg);
								    	break;
				 		}		
					 	break;
			case WM_POST_PAINT:
				    
				    if(MenuID == ID_MENU)
								{
									  GUI_SetColor(GUI_BLACK);
									  GUI_SetPenSize(1);
									  GUI_DrawLine(127,0,127,156);
									  GUI_DrawLine(0,156,127,156);
								}
				    break;
								
			default :
			MENU_Callback(pMsg);
			break;
	}
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN         hWin;
	MENU_MSG_DATA * pData;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		 case USER_MSG_SKIN:		     
			     GUI_SetBkColor(GUI_GRAY);
			     //MENU_SetBkColor(hM)
			     //MENU_SetDefaultBkColor(MENU_CI_ENABLED,GUI_GRAY);
// 				    if (pMsg->Data.v == 0)
// 				       WINDOW_SetBkColor(hWin,GUI_WHITE);
// 								else WINDOW_SetBkColor(hWin,GUI_GRAY);
				    break;
			
			case WM_PAINT:
								GUI_SetBkColor(GUI_WHITE);
								GUI_Clear();
								GUI_SetFont(&GUI_Font24);
								GUI_SetColor(GUI_BLACK);
								GUI_DispStringAt("按▲▼键选择选项，ENT 键进入下一级菜单，按 ESC 键返回上一级菜单，按 MENU 键退出菜单",27,440);
			     GUI_SetColor(GUI_BLACK);
			     GUI_SetFont(&GUI_Font30);
			     GUI_DispStringAt("主菜单",25,25);
			     GUI_DrawLine(0,59,127,59);
			     GUI_DrawLine(127,20,127,59);
			     GUI_DrawLine(0,20,127,20);
								break;
		
			case WM_MENU:
								pData = (MENU_MSG_DATA*)pMsg->Data.p;
								switch (pData->MsgType) 
								{
										case MENU_ON_ITEMSELECT:  // 选中
													MENU_SetSel(hMenu, 0);
													MenuSel = 0;
										   MenuActiveId = ID_SITESEL;
													switch (pData->ItemId)
													{
																case ID_SYSSET_SOFTUPDATE:
				// 																	ToolTipMsg.MsgId = USER_MSG_SOFTUPDATE;
				// 																	ToolTipMsg.Data.v = SOFT_UPDATE_0;   //是否检测有软件更新，0:未检测到，1:需要更新，2:无需更新
				// 																	ToolTipMsg.Data.p = "未检测到软件新版本";
				// 												     ToolTipMsg.hWinSrc = hWin;
				// 																	ToolTipMsg.hWin = ToolTip;
				// 																	WM_SendMessage (ToolTipMsg.hWin,&ToolTipMsg);
																
																					ptipText = "未检测到系统更新文件";
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip);
																					WM_HideWindow(ToolTip_BUTTON[0]);
																					WM_HideWindow(ToolTip_BUTTON[1]);
																					WM_ShowWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,ptipText);
																					break;
																	
																	case ID_SYSSET_RESET:
																					ptipText = "请确定是否恢复出厂设置？";
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[1]);
																					WM_HideWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,ptipText);
																					break;
																	
																		case ID_SYSSET_CHECK:
																					CheckFlag = 1;
																					ptipText = "请确认是否开始自检？";
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[1]);
																					WM_HideWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,ptipText);		
																					break;
													}
													break;
													
										case MENU_ON_ITEMACTIVATE:  //高亮
															MenuActiveId = pData->ItemId;
															switch(pData->ItemId) 
															{
						{ //用于修正子菜单的窗口位置											
																	case ID_SITESEL:
																						MenuSel = 0;
																						break;
																	case ID_INFOSEL:
																						MenuSel = 1;
																						break;
																	case ID_PORTSET:
																						MenuSel = 2;
																						break;
																	case ID_SYSSET:
																						MenuSel = 3;
																						break;
							
							
																	case ID_FOUR_RECEIVE_0:
																			if (MenuThird == 0)
																			{
																				if (MenuSel == 0)
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hFourCel,130,0);
																						}
																						else
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hFourCel,130,40);
																						}
																			}
																			break;
																			
																	case ID_INT_RECEIVE_0:
																			if (MenuThird == 0)
																			{
																						if (MenuSel == 0)
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hInterCel1,130,0); 
																						}
																						else
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hInterCel1,130,40);
																						}
																			}
																					break;
																	case ID_LOC1_RECEIVE_0:
																			if (MenuThird == 0)
																			{
																						if (MenuSel == 0)
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hLocal1,130,0); 
																						}
																						else
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hLocal1,130,40);
																						}
																			}
																					break;
																	case ID_LOC2_RECEIVE_0:
																			if (MenuThird == 0)
																			{
																						if (MenuSel == 0)
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hLocal2,130,0); 
																						}
																						else
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hLocal2,130,40);
																						}
																			}
																						break;
																	case ID_CHS_RECEIVE_0:
																			if (MenuThird == 0)
																			{
																						if (MenuSel == 0)
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hChinaCel,130,0); 
																						}
																						else
																						{
																								MenuThird = 1;
																								WM_MoveWindow(hChinaCel,130,40);
																						}
																			}
																						break;
																	
																	//端口-站点选择
																	case ID_SITE_OUTPUT_0:
																		if (MenuThird == 0)
																		{
																				MenuThird = 1;
																				WM_MoveWindow(hSiteSel2,130,82);
																		}
																		break;
																	case ID_INFO_OUTPUT_0:
																		if (MenuThird == 0)
																		{
																				MenuThird = 1;
																				WM_MoveWindow(hInfoSel2,130,82);
																		}
																		break;				
																	
																	//系统设置
																	case ID_INVERSE:
																			if (MenuThird == 0)
																			{
																					MenuThird = 1;
																					WM_MoveWindow(hDispSet,128,55);
																			}
																						break;
																			
																	case ID_ALAR_INFOTYPE:
																			if (MenuThird == 0)
																			{
																						MenuThird = 1;
																						WM_MoveWindow(hAlarmSet,128,55);
																			}
																						break;				
																			
																	case ID_KEYSOUND:
																		if (MenuThird == 0)
																		{
																				MenuThird = 1;
																				WM_MoveWindow(hKeySound,128,55);
																		}
																		break;		
																		
																	case ID_TIME:
																			if (MenuThird == 0)
																			{
																						MenuThird = 1;
																						WM_MoveWindow(hTimeSet,128,55);
																			}
																						break;		
																			
																	case ID_LANGUAGE:
																			if (MenuThird == 0)
																			{
																						MenuThird = 1; 
																						WM_MoveWindow(hLanguaSet,128,55);
																			}
																						break;		
																			
																	case ID_ANTEN:
																			if (MenuThird == 0)
																			{
																						MenuThird = 1;
																						WM_MoveWindow(hAntenSet,128,55);
																			}
																						break;	
						}													
															}
										break;
								}
									break;
					}
	WM_DefaultProc(pMsg);
}


/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN MenuWinCreate(void) {
  WM_HWIN hWin;

		//hWin = 	FRAMEWIN_CreateEx(0, 0, 800, 480, WM_HBKWIN, WM_CF_SHOW, FRAMEWIN_CF_MOVEABLE, 0, "Application with menu", _cbDialog);
	  hWin = WM_CreateWindow(0, 0, 800, 480,WM_CF_SHOW, _cbDialog, 0);
		// 一级菜单
	//创建
		hMenu = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_MENU); // 主菜单
	 hSiteSel1 =  MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_SITESEL); //站点选择
		hInfoSel1 = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_INFOSEL);  //信息选择
		hPortSet =  MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_PORTSET); //端口设置
		hSysSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_SYSSET);  //系统设置
	
  WM_SetCallback(hMenu,&MenuCall);	
		WM_SetCallback(hSiteSel1,&MenuCall);	
	 WM_SetCallback(hInfoSel1,&MenuCall);	
	 WM_SetCallback(hPortSet,&MenuCall);	
		WM_SetCallback(hSysSet,&MenuCall);	
	
	 hFourCel = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_FOURCAN); //四频道 
		hInterCel1 = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_INTERCEL); //国际频道
		hLocal1 = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_LOCAL1);   //本地频道1
		hLocal2 = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_LOCAL2);   //本地频道2
		hChinaCel = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_CHS);				//中文频道
	
	 hSiteSel2 = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hInfoSel2 = MENU_CreateEx(0,0,100,202,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		
		MENU_SetBorderSize(hMenu,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hMenu,MENU_BI_RIGHT,20);
		
		MENU_SetBorderSize(hSiteSel1,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hSiteSel1,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hInfoSel1,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hInfoSel1,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hPortSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hPortSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hSysSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hSysSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hFourCel,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hFourCel,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hInterCel1,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hInterCel1,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hLocal1,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hLocal1,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hLocal2,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hLocal2,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hChinaCel,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hChinaCel,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hSiteSel2,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hSiteSel2,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hInfoSel2,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hInfoSel2,MENU_BI_RIGHT,10);
		
		//显示设置，报警音，按键音设置，时间设置，语言设置，天线设置，软件更新，恢复出厂设置
		hDispSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hAlarmSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hKeySound = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hTimeSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hLanguaSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		hAntenSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		
		MENU_SetBorderSize(hDispSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hDispSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hAlarmSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hAlarmSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hKeySound,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hKeySound,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hTimeSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hTimeSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hLanguaSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hLanguaSet,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hAntenSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hAntenSet,MENU_BI_RIGHT,20);
		//hSoftUpdate = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		//hReset = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,0);
		WM_SetCallback(hFourCel,&MenuCall);	
		WM_SetCallback(hInterCel1,&MenuCall);	
		WM_SetCallback(hLocal1,&MenuCall);	
		WM_SetCallback(hLocal2,&MenuCall);	
		WM_SetCallback(hChinaCel,&MenuCall);	
		WM_SetCallback(hSiteSel2,&MenuCall);	
		WM_SetCallback(hInfoSel2,&MenuCall);
		
		WM_SetCallback(hDispSet,&MenuCall);	
		WM_SetCallback(hAlarmSet,&MenuCall);	
		WM_SetCallback(hKeySound,&MenuCall);	
		WM_SetCallback(hTimeSet,&MenuCall);	
		WM_SetCallback(hLanguaSet,&MenuCall);	
		WM_SetCallback(hAntenSet,&MenuCall);			
	 //hReceive = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_RECEIVE);
// 		
// 		
	//添加主菜单
		_AddMenuItem(hMenu,   hSiteSel1,       "站点选择",      ID_SITESEL,    0);
		_AddMenuItem(hMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hMenu,   hInfoSel1,       "信息选择",      ID_INFOSEL,    0);
		_AddMenuItem(hMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hMenu,   hPortSet,        "端口设置",      ID_PORTSET,    0);
		_AddMenuItem(hMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hMenu,   hSysSet,         "系统设置",      ID_SYSSET,    0);
		
		//
		//二级菜单添加
		//
		//添加站点选择
			_AddMenuItem(hSiteSel1,   hFourCel,        "四频道同步选择",      ID_FOURCAN,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hInterCel1,      "国际频道",      0,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hLocal1,         "本地频道I",      0,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hLocal2,         "本地频道II",      0,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hChinaCel,       "中文频道",      0,    0);
			
   //添加信息选择
		 _AddMenuItem(hInfoSel1,   hFourCel,        "四频道同步选择",      0,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hInterCel1,      "国际频道",      0,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hLocal1,         "本地频道I",      0,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hLocal2,         "本地频道II",      0,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hChinaCel,       "中文频道",      0,   0);
			
			//添加端口设置
			_AddMenuItem(hPortSet,   hSiteSel2,        "站点选择",      0,    0);
			_AddMenuItem(hPortSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hPortSet,   hInfoSel2,        "信息选择",      0,   0);

			//添加系统设置
			_AddMenuItem(hSysSet,   hDispSet,        "显示设置",      0,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hAlarmSet,       "报警音设置",      0,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hKeySound,       "按键音设置",      0,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hTimeSet,        "时间设定",      0,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hLanguaSet,      "语言设置",      0,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hAntenSet,       "天线设置",      0,   0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   0,   "软件更新",      ID_SYSSET_SOFTUPDATE,   0);
			_AddMenuItem(hSysSet,   0,      0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   0,   "恢复出厂设置", ID_SYSSET_RESET,   0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   0,   "启动自检",      ID_SYSSET_CHECK,   0);
		
		//
		//三级菜单添加
		//
		_AddMenuItem(hFourCel,   0,        "A接收",      ID_FOUR_RECEIVE_0,    0);
		_AddMenuItem(hFourCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFourCel,   0,        "B接收",      ID_FOUR_RECEIVE_1,    0);
		_AddMenuItem(hFourCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFourCel,   0,        "C接收",      ID_FOUR_RECEIVE_2,    0);
		_AddMenuItem(hFourCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFourCel,   0,        "D接收",      ID_FOUR_RECEIVE_3,    0);
		_AddMenuItem(hFourCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFourCel,   0,        "E接收",      ID_FOUR_RECEIVE_4,    0);
		
		
		_AddMenuItem(hInterCel1,   0,        "A接收",      ID_INT_RECEIVE_0,    0);
		_AddMenuItem(hInterCel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInterCel1,   0,        "B接收",      ID_INT_RECEIVE_1,    0);
		_AddMenuItem(hInterCel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInterCel1,   0,        "C接收",      ID_INT_RECEIVE_2,    0);
		_AddMenuItem(hInterCel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInterCel1,   0,        "D接收",      ID_INT_RECEIVE_3,    0);
		_AddMenuItem(hInterCel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInterCel1,   0,        "E接收",      ID_INT_RECEIVE_4,    0);		
		
		_AddMenuItem(hLocal1,   0,        "A接收",      ID_LOC1_RECEIVE_0,    0);
		_AddMenuItem(hLocal1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal1,   0,        "B接收",      ID_LOC1_RECEIVE_1,    0);
		_AddMenuItem(hLocal1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal1,   0,        "C接收",      ID_LOC1_RECEIVE_2,    0);
		_AddMenuItem(hLocal1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal1,   0,        "D接收",      ID_LOC1_RECEIVE_3,    0);
		_AddMenuItem(hLocal1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal1,   0,        "E接收",      ID_LOC1_RECEIVE_4,    0);		
		
		_AddMenuItem(hLocal2,   0,        "A接收",      ID_LOC2_RECEIVE_0,    0);
		_AddMenuItem(hLocal2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal2,   0,        "B接收",      ID_LOC2_RECEIVE_1,    0);
		_AddMenuItem(hLocal2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal2,   0,        "C接收",      ID_LOC2_RECEIVE_2,    0);
		_AddMenuItem(hLocal2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal2,   0,        "D接收",      ID_LOC2_RECEIVE_3,    0);
		_AddMenuItem(hLocal2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hLocal2,   0,        "E接收",      ID_LOC2_RECEIVE_4,    0);				
		
		_AddMenuItem(hChinaCel,   0,        "A接收",      ID_CHS_RECEIVE_0,    0);
		_AddMenuItem(hChinaCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hChinaCel,   0,        "B接收",      ID_CHS_RECEIVE_1,    0);
		_AddMenuItem(hChinaCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hChinaCel,   0,        "C接收",      ID_CHS_RECEIVE_2,    0);
		_AddMenuItem(hChinaCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hChinaCel,   0,        "D接收",      ID_CHS_RECEIVE_3,    0);
		_AddMenuItem(hChinaCel,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hChinaCel,   0,        "E接收",      ID_CHS_RECEIVE_4,    0);			
		
		_AddMenuItem(hSiteSel2,   0,        "A输出",      ID_SITE_OUTPUT_0  ,    0);
		_AddMenuItem(hSiteSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSel2,   0,        "B输出",      ID_SITE_OUTPUT_1  ,    0);
		_AddMenuItem(hSiteSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSel2,   0,        "C输出",      ID_SITE_OUTPUT_2  ,    0);
		_AddMenuItem(hSiteSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSel2,   0,        "D输出",      ID_SITE_OUTPUT_3  ,    0);
		_AddMenuItem(hSiteSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSel2,   0,        "E输出",      ID_SITE_OUTPUT_4  ,    0);
		
		_AddMenuItem(hInfoSel2,   0,        "A输出",      ID_INFO_OUTPUT_0  ,    0);
		_AddMenuItem(hInfoSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSel2,   0,        "B输出",      ID_INFO_OUTPUT_1  ,    0);
		_AddMenuItem(hInfoSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSel2,   0,        "C输出",      ID_INFO_OUTPUT_2  ,    0);
		_AddMenuItem(hInfoSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSel2,   0,        "D输出",      ID_INFO_OUTPUT_3  ,    0);
		_AddMenuItem(hInfoSel2,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSel2,   0,        "E输出",      ID_INFO_OUTPUT_4  ,    0);		
		 
		_AddMenuItem(hDispSet,   0,        "反色显示 开启",      ID_INVERSE  ,    0);	
		_AddMenuItem(hDispSet,   0,       0,     0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hDispSet,   0,        "睡眠设置开启",      0  ,    0);		
		
		_AddMenuItem(hAlarmSet,   0,        "A类信息",      ID_ALAR_INFOTYPE ,    0);	
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "B类信息",      0 ,    0);
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "C类信息",      0 ,    0);
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "D类信息",      0 ,    0);
		
		_AddMenuItem(hKeySound,   0,        "开启",      ID_KEYSOUND ,    0);
		_AddMenuItem(hTimeSet,   0,         "UTC",      ID_TIME ,    0);
		_AddMenuItem(hLanguaSet,   0,       "简体中文",      ID_LANGUAGE ,    0);
		_AddMenuItem(hAntenSet,   0,        "有源天线",      ID_ANTEN ,    0);
		
  	MENU_Attach (hMenu,hWin,0,60,0,0,0);
	//FRAMEWIN_AddMenu(hWin, hMenu);
 	WM_SetFocus(hMenu);
  MENU_SetSel(hMenu, 0);
  return hWin;
}