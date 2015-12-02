#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "str.h"
#include "28.h"
#include "MenuWin.h"
#include "LANGUAGE.h"
#define ID_MENUHINT 0x54 
#define ID_MENUTEXT 0x55

char CheckFlag = 0;
WM_MESSAGE MyMessage; //自定义消息
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
static char IsSleep = 0;  //睡眠模式
char MenuSel = 0;
char Color = 0; //颜色0:白底,1:黑底
char Language = 0; //语言选择：0中文，1英文
static const MENUWIN *pLanguage;
static const TOOLTIP *pTooltip;
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
	WM_HWIN MenuHint; //提示信息
 WM_HWIN MenuText; //主菜单文本


//
//
//
static void MenuSetItemText(WM_HWIN hWin,int ID)
{
   switch (ID)
	  {
				 case ID_MENU: //主菜单
						    if (Language ==  0)
											MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,hSiteSel1,pLanguage->Menu[0],ID_SITESEL,0);
					     _SetMenuItem(hWin,hInfoSel1,pLanguage->Menu[1],ID_INFOSEL,0);
     					_SetMenuItem(hWin,hPortSet,pLanguage->Menu[2],ID_PORTSET,0);
				    	 _SetMenuItem(hWin,hSysSet,pLanguage->Menu[3],ID_SYSSET,0);
					 	   break;
					
					case ID_SITESEL: //站点选择
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,hFourCel,pLanguage->Rx_Station[0],ID_FOURCAN,0);
					     _SetMenuItem(hWin,hInterCel1,pLanguage->Rx_Station[1],ID_INTERCEL,0);
					     _SetMenuItem(hWin,hLocal1,pLanguage->Rx_Station[2],ID_LOCAL1,0);
					     _SetMenuItem(hWin,hLocal2,pLanguage->Rx_Station[3],ID_LOCAL2,0);
					     _SetMenuItem(hWin,hChinaCel,pLanguage->Rx_Station[4],ID_CHS,0);
						    break;
					
					case ID_INFOSEL: //信息选择
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,hFourCel,pLanguage->Msg_Type[0],ID_FOURCAN,0);
					     _SetMenuItem(hWin,hInterCel1,pLanguage->Msg_Type[1],ID_INTERCEL,0);
					     _SetMenuItem(hWin,hLocal1,pLanguage->Msg_Type[2],ID_LOCAL1,0);
					     _SetMenuItem(hWin,hLocal2,pLanguage->Msg_Type[3],ID_LOCAL2,0);
					     _SetMenuItem(hWin,hChinaCel,pLanguage->Msg_Type[4],ID_CHS,0);
						    break;
					
					case ID_PORTSET: //端口设置
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,hSiteSel2,pLanguage->Output_Set[0],ID_PORT_SITESEL,0);
					     _SetMenuItem(hWin,hInfoSel2,pLanguage->Output_Set[1],ID_PORT_INFOSEL,0);
						    break;
					case ID_SYSSET:  //系统设置
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,hDispSet,pLanguage->System_Set[0],ID_SYSSET_DISP,0);
					     _SetMenuItem(hWin,hAlarmSet,pLanguage->System_Set[1],ID_SYSSET_ALAR,0);
					     _SetMenuItem(hWin,hKeySound,pLanguage->System_Set[2],ID_SYSSET_KEYSOUND,0);
					     _SetMenuItem(hWin,hTimeSet,pLanguage->System_Set[3],ID_SYSSET_TIME,0);
					     _SetMenuItem(hWin,hLanguaSet,pLanguage->System_Set[4],ID_SYSSET_LANGUAGE,0);
					     _SetMenuItem(hWin,hAntenSet,pLanguage->System_Set[5],ID_SYSSET_ANTEN,0);
					     _SetMenuItem(hWin,0,pLanguage->System_Set[6],ID_SYSSET_SOFTUPDATE,0);
					     _SetMenuItem(hWin,0,pLanguage->System_Set[7],ID_SYSSET_RESET,0);
					     _SetMenuItem(hWin,0,pLanguage->System_Set[8],ID_SYSSET_CHECK,0);
						    break;
					
					case ID_FOURCAN: //四频道
						    if (Language ==  0)
										{
										   	MENU_SetFont(hWin,&GUI_Font30);
										}
										else 
										{
											 MENU_SetFont(hWin,&GUI_Font20_1);
										}
						    _SetMenuItem(hWin,0,pLanguage->IsReceive[0],ID_FOUR_RECEIVE_0,0);
					     _SetMenuItem(hWin,0,pLanguage->IsReceive[1],ID_FOUR_RECEIVE_1,0);
					     _SetMenuItem(hWin,0,pLanguage->IsReceive[2],ID_FOUR_RECEIVE_2,0);
					     _SetMenuItem(hWin,0,pLanguage->IsReceive[3],ID_FOUR_RECEIVE_3,0);
					     _SetMenuItem(hWin,0,pLanguage->IsReceive[4],ID_FOUR_RECEIVE_4,0);
					     break;
					case ID_INTERCEL: //国际频道
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsReceive[0],ID_INT_RECEIVE_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[1],ID_INT_RECEIVE_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[2],ID_INT_RECEIVE_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[3],ID_INT_RECEIVE_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[4],ID_INT_RECEIVE_4,0);
						    break;
					case ID_LOCAL1: //本地频道1
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsReceive[0],ID_LOC1_RECEIVE_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[1],ID_LOC1_RECEIVE_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[2],ID_LOC1_RECEIVE_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[3],ID_LOC1_RECEIVE_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[4],ID_LOC1_RECEIVE_4,0);
						    break;
					case ID_LOCAL2: //本地频道2
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsReceive[0],ID_LOC2_RECEIVE_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[1],ID_LOC2_RECEIVE_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[2],ID_LOC2_RECEIVE_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[3],ID_LOC2_RECEIVE_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[4],ID_LOC2_RECEIVE_4,0);
							   break;
					case ID_CHS:  //中文频道
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsReceive[0],ID_CHS_RECEIVE_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[1],ID_CHS_RECEIVE_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[2],ID_CHS_RECEIVE_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[3],ID_CHS_RECEIVE_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsReceive[4],ID_CHS_RECEIVE_4,0);
						    break;
					
					case ID_PORT_SITESEL: //
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsOutput[0],ID_SITE_OUTPUT_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[1],ID_SITE_OUTPUT_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[2],ID_SITE_OUTPUT_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[3],ID_SITE_OUTPUT_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[4],ID_SITE_OUTPUT_4,0);
										break;
					case ID_PORT_INFOSEL:
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[0],ID_SITE_OUTPUT_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[1],ID_SITE_OUTPUT_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[2],ID_SITE_OUTPUT_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[3],ID_SITE_OUTPUT_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsOutput[4],ID_SITE_OUTPUT_4,0);
						    break;
					
					case ID_SYSSET_DISP: //显示设置
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->DispSet[0],ID_INVERSE,0);
					     _SetMenuItem(hWin,0,pLanguage->DispSet[2],ID_SLEEPSET,0);
						    break;
					case ID_SYSSET_ALAR: //报警音
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->Alarm[0],ID_ALAR_INFOTYPE_0,0);
										_SetMenuItem(hWin,0,pLanguage->Alarm[1],ID_ALAR_INFOTYPE_1,0);
										_SetMenuItem(hWin,0,pLanguage->Alarm[2],ID_ALAR_INFOTYPE_2,0);
										_SetMenuItem(hWin,0,pLanguage->Alarm[3],ID_ALAR_INFOTYPE_3,0);
						    break;
					case ID_SYSSET_KEYSOUND: //按键音
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->KeyBeep[0],ID_KEYSOUND,0);
						    break;
					case ID_SYSSET_TIME: //时间
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->Time,ID_TIME,0);
						    break;
					case ID_SYSSET_LANGUAGE: //语言
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->Language,ID_LANGUAGE,0);
						    break;
					case ID_SYSSET_ANTEN: // 天线
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->Antenna[0],ID_ANTEN,0);
						    break;
					case ID_SLEEPSET: //睡眠设置
						    if (Language ==  0)
										   	MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->SleepSet,ID_SLEEPSET_0,0);
						    break;
				 
					default: 
						    break;
			}
}
//
//
//
static void MenuCall(WM_MESSAGE* pMsg)
{
	WM_HWIN hWin  = pMsg->hWin;
	const WM_KEY_INFO *pInfo;
	int MenuID;
	char i;
 MenuID = WM_GetId(hWin);
	switch (pMsg->MsgId)
	{

	 	case USER_MSG_LANGUAGE:
				     pLanguage = &Lgumenuwin[Language];
 				    MenuSetItemText(hWin,MenuID);
			      TEXT_SetText(MenuHint,"");
			     // MENU_Popup(hSysSet,hMenu,100,0,0,0,0);
			     // MENU_Popup(hLanguaSet,hSysSet,200,0,0,0,0);
 			      WM_SetFocus(hMenu);
 			      MENU_SetSel(hMenu,0);
{ //暂时修改更改完语言后菜单收起问题
			       for (i = 0; i<3; i++)
			       {
											  GUI_StoreKeyMsg(GUI_KEY_DOWN,1);
										}
										GUI_StoreKeyMsg(GUI_KEY_ENTER,1);
										for (i = 0; i<4; i++)
			       {
											  GUI_StoreKeyMsg(GUI_KEY_DOWN,1);
										}
										GUI_StoreKeyMsg(GUI_KEY_ENTER,1);
}
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
															   if (Language == 0)
																		{
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
																		else //ENGLISH
																		{
																					if (RevSel[Receiveindex/5][Receiveindex] == 0)
																					{
																								sprintf(pStrBuf,"%c"" ""%s",Receiveindex%5+65,"REJ");
																							_SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																							RevSel[Receiveindex/5][Receiveindex] = 1;
																					}
																					else
																					{
																							sprintf(pStrBuf,"%c"" ""%s",Receiveindex%5+65,"SEL");
																							_SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																							RevSel[Receiveindex/5][Receiveindex] = 0;
																					}																			
																		}
																			
														}
														else if (MenuActiveId >= ID_SITE_OUTPUT_0 && MenuActiveId <= ID_INFO_OUTPUT_0) //设置输出、不输出
														{
															   OutPutIndex = MenuActiveId - 2160;
															   if(Language == 0)
																		{
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
																		else //ENGLISH
																		{
																			  if (OutPutSel[OutPutIndex/5][OutPutIndex] == 0)
																					{
																								sprintf(pStrBuf,"%c"" ""%s",OutPutIndex%5+65,"REJ");
																							_SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																							OutPutSel[OutPutIndex/5][OutPutIndex] = 1;
																					}
																					else
																					{
																							sprintf(pStrBuf,"%c"" ""%s",OutPutIndex%5+65,"SEL");
																							_SetMenuItem(hWin,0,pStrBuf,MenuActiveId,0);
																							OutPutSel[OutPutIndex/5][OutPutIndex] = 0;
																					}
																		}																			
														}
														
														if (MenuActiveId == ID_INVERSE)  //显示设置
														{
															   if (Color == 0)
																		{
  																			Color = 1;
																					_SetMenuItem(hWin,0,"反色显示 关闭",MenuActiveId,0);
																			  MyMessage.MsgId = USER_MSG_SKIN;
																			  MyMessage.hWinSrc = hWin;
																			  MyMessage.Data.v = Color;
																			  WM_BroadcastMessage(&MyMessage);
																		}
																		else 
																		{
																			  Color = 0;
																			  _SetMenuItem(hWin,0,"反色显示 开启",MenuActiveId,0);
																			  MyMessage.MsgId = USER_MSG_SKIN;
																			  MyMessage.hWinSrc = hWin;
																			  MyMessage.Data.v = Color;
																			  WM_BroadcastMessage(&MyMessage);
																		}
														}
								     	
														if (MenuActiveId == ID_SLEEPSET) //睡眠设置
														{
															   if(IsSleep == 0)  //睡眠关闭
																		{
																			  IsSleep = 1;
																			  _SetMenuItem(hWin,0,"睡眠设置 开启",MenuActiveId,0);
																			  WM_ShowWindow(hSleep);
																			  WM_MoveWindow(hSleep,150,100);
																		}
																		else   //睡眠开启
																		{
																					IsSleep = 0;
																			  _SetMenuItem(hWin,0,"睡眠设置 关闭",MenuActiveId,0);
																			  WM_HideWindow(hSleep);
																		}
														}
														
														if(MenuActiveId == ID_LANGUAGE) //语言设定
														{
															  if(Language == 0)
																	{
																		  Language = 1;
																		  MyMessage.Data.v = Language;
																	}
																	else
																	{
																		  Language = 0;
																		  MyMessage.Data.v = Language;
																	}
																	MenuThird = 0;
																	// 发送消息
																	MyMessage.MsgId = USER_MSG_LANGUAGE;
																	MyMessage.hWinSrc = hWin;
																	WM_BroadcastMessage(&MyMessage);
														}
														break;
									case GUI_KEY_ESCAPE:
												  MenuThird = 0;
									     if (MenuActiveId >= ID_SITESEL && MenuActiveId <= ID_SYSSET)
														break;
									case GUI_KEY_ENTER:
														MenuThird = 0;
									     if (MenuActiveId == ID_SLEEPSET) //屏蔽睡眠设置ENTER操作
															   break;
									
									default :
									    MENU_Callback(pMsg);
								    	break;
				 		}		
					 	break;
			case WM_POST_PAINT:
				    if(MenuID == ID_MENU)
								{
									  GUI_SetPenSize(1);
									  GUI_SetColor(GUI_BLACK);
									  if(Language == 0)
											{
									    GUI_DrawLine(127,0,127,156);
									    GUI_DrawLine(0,156,127,156);
											}
											else //ENGLISH
											{
										   GUI_DrawLine(199,0,199,116);
									    GUI_DrawLine(0,116,199,116);											 
											}
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

		 case USER_MSG_LANGUAGE:
				    //pLanguage = &Lgumenuwin[Language];
				    //TEXT_SetText(MenuText,pLanguage->MenuTitle);
			     WM_InvalidateWindow(hWin);
				    break;
			
		 case USER_MSG_SKIN:		     
			     //GUI_SetBkColor(GUI_GRAY);
			     //MENU_SetBkColor(hM)
			     //MENU_SetDefaultBkColor(MENU_CI_ENABLED,GUI_GRAY);
// 				    if (pMsg->Data.v == 0)
// 				       WINDOW_SetBkColor(hWin,GUI_WHITE);
// 								else WINDOW_SetBkColor(hWin,GUI_GRAY);
				    break;
			
			case WM_PAINT:
								GUI_SetBkColor(GUI_WHITE);
								GUI_Clear();
			     GUI_SetColor(GUI_BLACK);
			     if (Language == 0)
								{
									 GUI_DispStringAt("主菜单",25,25);
										GUI_DrawLine(0,59,127,59);
										GUI_DrawLine(127,20,127,59);
										GUI_DrawLine(0,20,127,20);
								}
								else 
								{
									 GUI_DispStringAt("MENU",50,25);
									 GUI_DrawLine(0,59,199,59);
										GUI_DrawLine(199,20,199,59);
										GUI_DrawLine(0,20,199,20);
								}
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
																     pTooltip = &Lgutooltip[Language];
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip);
																					WM_HideWindow(ToolTip_BUTTON[0]);
																					WM_HideWindow(ToolTip_BUTTON[1]);
																					WM_ShowWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,pTooltip->Text1[0]);
																     TEXT_SetText(ToolTipText1,pTooltip->Text1[1]);
																					break;
																	
																	case ID_SYSSET_RESET:
																					pTooltip = &Lgutooltip[Language];
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[1]);
																	    BUTTON_SetText(ToolTip_BUTTON[0],pTooltip->Button[0]);
																	    BUTTON_SetText(ToolTip_BUTTON[1],pTooltip->Button[1]);
																					WM_HideWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,pTooltip->Text1[2]);
																					break;
																	
																		case ID_SYSSET_CHECK:
																	  		pTooltip = &Lgutooltip[Language];
																					CheckFlag = 1;
																					//ptipText = "请确认是否开始自检？";
																					WM_BringToTop(ToolTip);
																					WM_SetFocus(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[0]);
																					WM_ShowWindow(ToolTip_BUTTON[1]);
																	    BUTTON_SetText(ToolTip_BUTTON[0],pTooltip->Button[0]);
																	    BUTTON_SetText(ToolTip_BUTTON[1],pTooltip->Button[1]);																		
																					WM_HideWindow(ToolTipText1);
																					TEXT_SetText(ToolTipText0,pTooltip->Text1[3]);		
																					break;
													}
													break;
													
										case MENU_ON_ITEMACTIVATE:  //高亮
															MenuActiveId = pData->ItemId;
										     INFO("DFSD= %d",MenuActiveId);
										     _SetHintText(MenuHint,MenuActiveId,0);  //设置提示文本
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
							
							
																	case ID_FOUR_RECEIVE_0: //四频道同步-A接收
																		    if(Language == 0) //CHS
																						{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
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
																							}
																							else  //ENGLISH
																							{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hFourCel,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hFourCel,200,30);
																												}
																									}																								
																							}
																						break;
																			
																	case ID_INT_RECEIVE_0: //国际频道-A接收
																		   
																		    if(Language == 0) //CHS
																						{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
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
																							}
																							else  //ENGLISH
																							{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hInterCel1,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hInterCel1,200,30);
																												}
																									}																								
																							}						
																						break;
																						
																	case ID_LOC1_RECEIVE_0: // 本地频道I-A接收
																		    if(Language == 0) //CHS
																						{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
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
																							}
																							else  //ENGLISH
																							{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal1,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal1,200,30);
																												}
																									}																								
																							}
																						break;
																			
																	case ID_LOC2_RECEIVE_0:  //本地频道II-A接收
																		    if(Language == 0) //CHS
																						{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal2,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal2,200,40);
																												}
																									}
																							}
																							else  //ENGLISH
																							{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal2,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hLocal2,200,30);
																												}
																									}																								
																							}
																						break;
																			
																	case ID_CHS_RECEIVE_0:  //中文频道-A接收
																		    if(Language == 0) //CHS
																						{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
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
																							}
																							else  //ENGLISH
																							{
																									if (MenuThird == 0) 
																									{
																										if(MenuSel == 0) 
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hChinaCel,200,0);
																												}
																												else
																												{
																														MenuThird = 1;
																														WM_MoveWindow(hChinaCel,200,30);
																												}
																									}																								
																							}
																									break;
																	
																	
																	case ID_SITE_OUTPUT_0://端口-站点选择-输出
																		    if(Language == 0)
																						{
																										if (MenuThird == 0)
																										{
																												MenuThird = 1;
																												WM_MoveWindow(hSiteSel2,130,82);
																										}
																						}
																						else
																						{
																										if (MenuThird == 0)
																										{
																												MenuThird = 1;
																												WM_MoveWindow(hSiteSel2,200,61);
																										}
																							
																						}
																						break;
																		
																	case ID_INFO_OUTPUT_0:
																		    if(Language == 0)
																						{
																										if (MenuThird == 0)
																										{
																												MenuThird = 1;
																												WM_MoveWindow(hInfoSel2,130,82);
																										}
																						}
																						else
																						{
																										if (MenuThird == 0)
																										{
																												MenuThird = 1;
																												WM_MoveWindow(hInfoSel2,200,61);
																										}
																							
																						}
																						break;				
																	
																	//系统设置
																	case ID_INVERSE:  //反色显示
																		    if(Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																											MenuThird = 1;
																											WM_MoveWindow(hDispSet,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																											MenuThird = 1;
																											WM_MoveWindow(hDispSet,200,95);
																									}
																						}																							
																						break;
																			
																	case ID_ALAR_INFOTYPE_0:   //报警音设置
																		    if (Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hAlarmSet,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hAlarmSet,200,95);
																									}
																						}
																						break;				
																			
																	case ID_KEYSOUND:   //按键音设置
																		    if (Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hKeySound,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hKeySound,200,95);
																									}
																						}
																						break;		
																		
																	case ID_TIME:  //时间设定
																		    if (Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hTimeSet,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hTimeSet,200,95);
																									}
																						}
																						break;		
																			
																	case ID_LANGUAGE: //语言设定
																		    if (Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hLanguaSet,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hLanguaSet,200,95);
																									}
																						}
																						break;		
																			
																	case ID_ANTEN:
																		    if (Language == 0)
																						{
																									if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hAntenSet,128,55);
																									}
																						}
																						else
																						{
																							  if (MenuThird == 0)
																									{
																												MenuThird = 1;
																												WM_MoveWindow(hAntenSet,200,95);
																									}
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
	  MenuHint = TEXT_CreateAsChild(40,440,800,40,hWin,ID_MENUHINT,WM_CF_SHOW,"DFDS",TEXT_CF_LEFT); //提示文本
	  TEXT_SetFont(MenuHint,&GUI_Font24);
	  //MenuText = TEXT_CreateAsChild(25,25,50,30,hWin,ID_MENUTEXT,WM_CF_SHOW,"主菜单",TEXT_CF_LEFT);//静态文本主菜单
	
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
	
	 hFourCel = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_FOURCAN); //四频道 
		hInterCel1 = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_INTERCEL); //国际频道
		hLocal1 = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_LOCAL1);   //本地频道1
		hLocal2 = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_LOCAL2);   //本地频道2
		hChinaCel = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_CHS);				//中文频道
	
	 hSiteSel2 = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_PORT_SITESEL);
		hInfoSel2 = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_PORT_INFOSEL);
		MENU_SetBorderSize(hMenu,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hMenu,MENU_BI_RIGHT,20);
		
		MENU_SetBorderSize(hSiteSel1,MENU_BI_LEFT,20);
		//MENU_SetBorderSize(hSiteSel1,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hInfoSel1,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hInfoSel1,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hPortSet,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hPortSet,MENU_BI_RIGHT,20);
// 		MENU_SetBorderSize(hSysSet,MENU_BI_LEFT,20);
// 		MENU_SetBorderSize(hSysSet,MENU_BI_RIGHT,20);
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
		
		//显示设置，报警音，按键音设置，时间设置，语言设置，天线设置，软件更新，恢复出厂设置,睡眠设置
		hDispSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_DISP);
		hAlarmSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_ALAR);
		hKeySound = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_KEYSOUND);
		hTimeSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_TIME);
		hLanguaSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_LANGUAGE);
		hAntenSet = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SYSSET_ANTEN);
		hSleep = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,0,MENU_CF_VERTICAL,ID_SLEEPSET);
		
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
		WM_SetCallback(hSleep,&MenuCall);
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
			_AddMenuItem(hSiteSel1,   hInterCel1,      "国际频道",      ID_INTERCEL,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hLocal1,         "本地频道I",      ID_LOCAL1,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hLocal2,         "本地频道II",      ID_LOCAL2,    0);
			_AddMenuItem(hSiteSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSiteSel1,   hChinaCel,       "中文频道",      ID_CHS,    0);
			
   //添加信息选择
		 _AddMenuItem(hInfoSel1,   hFourCel,        "四频道同步选择",      ID_FOURCAN,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hInterCel1,      "国际频道",      ID_INTERCEL,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hLocal1,         "本地频道I",      ID_LOCAL1,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hLocal2,         "本地频道II",      ID_LOCAL2,    0);
			_AddMenuItem(hInfoSel1,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hInfoSel1,   hChinaCel,       "中文频道",      ID_CHS,   0);
			
			//添加端口设置
			_AddMenuItem(hPortSet,   hSiteSel2,        "站点选择",      ID_PORT_SITESEL,    0);
			_AddMenuItem(hPortSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hPortSet,   hInfoSel2,        "信息选择",      ID_PORT_INFOSEL,   0);

			//添加系统设置
			_AddMenuItem(hSysSet,   hDispSet,        "显示设置",      ID_SYSSET_DISP,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hAlarmSet,       "报警音设置",      ID_SYSSET_ALAR,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hKeySound,       "按键音设置",      ID_SYSSET_KEYSOUND,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hTimeSet,        "时间设定",      ID_SYSSET_TIME,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hLanguaSet,      "语言设置",      ID_SYSSET_LANGUAGE,    0);
			_AddMenuItem(hSysSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
			_AddMenuItem(hSysSet,   hAntenSet,       "天线设置",      ID_SYSSET_ANTEN,   0);
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
		_AddMenuItem(hDispSet,   hSleep,        "睡眠设置 开启",      ID_SLEEPSET  ,    0);	
		
		_AddMenuItem(hSleep,   0,        "无操作15分钟进入睡眠模式",      ID_SLEEPSET_0  ,    0);	
		
		_AddMenuItem(hAlarmSet,   0,        "A类信息",      ID_ALAR_INFOTYPE_0 ,    0);	
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "B类信息",      ID_ALAR_INFOTYPE_1 ,    0);
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "C类信息",      ID_ALAR_INFOTYPE_2 ,    0);
		_AddMenuItem(hAlarmSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hAlarmSet,   0,        "D类信息",      ID_ALAR_INFOTYPE_3 ,    0);
		
		_AddMenuItem(hKeySound,   0,        "开启",      ID_KEYSOUND ,    0);
		_AddMenuItem(hTimeSet,   0,         "UTC 2015.10.24 17:30",      ID_TIME ,    0);
		_AddMenuItem(hLanguaSet,   0,       "简体中文",      ID_LANGUAGE ,    0);
		_AddMenuItem(hAntenSet,   0,        "有源天线",      ID_ANTEN ,    0);
		
  	MENU_Attach (hMenu,hWin,0,60,0,0,0);
	//FRAMEWIN_AddMenu(hWin, hMenu);
 	WM_SetFocus(hMenu);
  MENU_SetSel(hMenu, 0);
  return hWin;
}