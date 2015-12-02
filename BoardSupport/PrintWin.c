#include "DIALOG.h"
#include "MainTask.h"

#include "Config.h"
#include "dlg.h"
#include "28.h"
#include "str.h"
#include "info.h"
#include "MenuWin.h"
#include "LANGUAGE.h"

#define ID_MENU     					        (GUI_ID_USER + 0x50) // 主菜单
#define ID_PrintMenu             (GUI_ID_USER + 0x51) // 打印菜单
#define ID_PrintText             (GUI_ID_USER + 0x52) //打印选项

#define ID_Print_All             (GUI_ID_USER + 0x01)
#define ID_Print_Showing         (GUI_ID_USER + 0x02)
#define ID_Print_Frequency       (GUI_ID_USER + 0x03)
#define ID_Print_Site            (GUI_ID_USER + 0x04)
#define ID_Print_Info            (GUI_ID_USER + 0x05)

#define ID_Print_Fre_Int         (GUI_ID_USER + 0x06)
#define ID_Print_Fre_Loc1        (GUI_ID_USER + 0x07)
#define ID_Print_Fre_Loc2        (GUI_ID_USER + 0x08)
#define ID_Print_Fre_Chs         (GUI_ID_USER + 0x09)

#define ID_Print_Site_Prt        (GUI_ID_USER + 0x0a)
#define ID_Print_Site_SiteSet    (GUI_ID_USER + 0x0b)

#define ID_Print_Info_Prt        (GUI_ID_USER + 0x12)
#define ID_Print_Info_InfoSet    (GUI_ID_USER + 0x13)

#define ID_Print_Site_SiteSet_Prt_0 (GUI_ID_USER + 0x14)
#define ID_Print_Site_SiteSet_Prt_1 (GUI_ID_USER + 0x15)
#define ID_Print_Site_SiteSet_Prt_2 (GUI_ID_USER + 0x16)
#define ID_Print_Site_SiteSet_Prt_3 (GUI_ID_USER + 0x17)
#define ID_Print_Site_SiteSet_Prt_4 (GUI_ID_USER + 0x18)

#define ID_Print_Info_InfoSet_Prt_0 (GUI_ID_USER + 0x19)
#define ID_Print_Info_InfoSet_Prt_1 (GUI_ID_USER + 0x1a)
#define ID_Print_Info_InfoSet_Prt_2 (GUI_ID_USER + 0x1b)
#define ID_Print_Info_InfoSet_Prt_3 (GUI_ID_USER + 0x1c)
#define ID_Print_Info_InfoSet_Prt_4 (GUI_ID_USER + 0x1d)

WM_HWIN PrintWin; //打印窗口
WM_HWIN PrintHintText; //提示信息 
MENU_Handle hPrintMenu,hFre,hSite,hInfo,hSiteSet,hInfoSet;
static CHAR PrintMenuThird;
static int PrintActiveId;
CHAR StarPrint = 0;
//CHAR EndPrint = 0;
WM_HTIMER PrintTimer;
WM_HWIN hPrintText; //静态文本
static CHAR PrintSiteSet[26] = {0};
static int PrintSiteindex = 0;
static CHAR PrintInfoSet[26] = {0};
static int PrintInfoindex = 0;
extern char*ptipText;
extern WM_HWIN ToolTip_BUTTON[2];
extern WM_HWIN ToolTipText0;
extern WM_HWIN ToolTipText1;
extern WM_HWIN hMultiEdit;
extern CHAR MenuSel;
extern CHAR Language;
static const PRINTWIN *pLanguage;
static const TOOLTIP *pTooltip;

//
// PrintWinSetMenuText
//
static void PrintSetItemText(WM_HWIN hWin,int ID)
{
			switch (ID)
			{
				 case ID_PrintMenu:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->PrintMenu[0],ID_Print_All,0);
					     _SetMenuItem(hWin,0,pLanguage->PrintMenu[1],ID_Print_Showing,0);
					     _SetMenuItem(hWin,hFre,pLanguage->PrintMenu[2],ID_Print_Frequency,0);
					     _SetMenuItem(hWin,hSite,pLanguage->PrintMenu[3],ID_Print_Site,0);
					     _SetMenuItem(hWin,hInfo,pLanguage->PrintMenu[4],ID_Print_Info,0);
          break;	
					
     case ID_Print_Frequency:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
										_SetMenuItem(hWin,0,pLanguage->Frequency[0],ID_Print_Fre_Int,0);
										_SetMenuItem(hWin,0,pLanguage->Frequency[1],ID_Print_Fre_Loc1,0);
										_SetMenuItem(hWin,0,pLanguage->Frequency[2],ID_Print_Fre_Loc2,0);
										_SetMenuItem(hWin,0,pLanguage->Frequency[3],ID_Print_Fre_Chs,0);
          break;
					
     case ID_Print_Site:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->StaTion[0],ID_Print_Site_Prt,0);
					     _SetMenuItem(hWin,hSiteSet,pLanguage->StaTion[1],ID_Print_Site_SiteSet,0);
          break;
					
     case ID_Print_Info:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
										_SetMenuItem(hWin,0,pLanguage->InfoType[0],ID_Print_Info_Prt,0);
									 _SetMenuItem(hWin,hInfoSet,pLanguage->InfoType[1],ID_Print_Info_InfoSet,0);
          break;
					
     case ID_Print_Site_SiteSet:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
						    _SetMenuItem(hWin,0,pLanguage->IsPrint[0],ID_Print_Site_SiteSet_Prt_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[1],ID_Print_Site_SiteSet_Prt_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[2],ID_Print_Site_SiteSet_Prt_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[3],ID_Print_Site_SiteSet_Prt_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[4],ID_Print_Site_SiteSet_Prt_4,0);
										break;
					case ID_Print_Info_InfoSet:
						    if (Language ==  0)
											   MENU_SetFont(hWin,&GUI_Font30);
										else MENU_SetFont(hWin,&GUI_Font20_1);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[0],ID_Print_Info_InfoSet_Prt_0,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[1],ID_Print_Info_InfoSet_Prt_1,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[2],ID_Print_Info_InfoSet_Prt_2,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[3],ID_Print_Info_InfoSet_Prt_3,0);
										_SetMenuItem(hWin,0,pLanguage->IsPrint[4],ID_Print_Info_InfoSet_Prt_4,0);
						    break;
			}
}

//
//MenuCallback
//
static void MenuCall(WM_MESSAGE *pMsg)
{
	 WM_HWIN hWin = pMsg->hWin;
	 WM_KEY_INFO *KEY;
	 MENU_ITEM_DATA *pData;
	 int16_t PrintMenuID;
	 PrintMenuID = WM_GetId(hWin);
  switch (pMsg->MsgId)
	 {
			case USER_MSG_LANGUAGE:
				    pLanguage = &Lguprintwin[Language];
			     PrintSetItemText(hWin,PrintMenuID);
			     TEXT_SetText(PrintHintText,"");
				    break;

			case WM_KEY:
								KEY = (WM_KEY_INFO*)pMsg->Data.p;
								switch (KEY->Key)
								{
									
									  case GUI_KEY_MENU:
												    WM_BringToTop(Menuwin);
											     WM_SetFocus(WM_GetDialogItem(Menuwin,ID_MENU));
											     MENU_SetSel(WM_GetDialogItem(Menuwin,ID_MENU),0);
											     MenuSel = 0;
												    break;
											case GUI_KEY_PRINT:
												    WM_BringToTop(mainwin);
											     WM_SetFocus(mainwin);
											     break;
											
											case GUI_KEY_LEFT:
											case GUI_KEY_RIGHT:
												    if(PrintActiveId >= ID_Print_Site_SiteSet_Prt_0 && PrintActiveId <= ID_Print_Site_SiteSet_Prt_4) 
																{
																				PrintSiteindex = PrintActiveId - 2068;
																	   if (Language == 0)
																				{
																							if (PrintSiteSet[PrintSiteindex] == 0)
																							{
																											sprintf(pStrBuf,"%c""%s",PrintSiteindex+65,"不打印");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintSiteindex] = 1;
																							}
																							else
																							{																					
																											sprintf(pStrBuf,"%c""%s",PrintSiteindex+65,"打印");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintSiteindex] = 0;

																							}
																				}
																				else //english
																				{
																								if (PrintSiteSet[PrintSiteindex] == 0)
																							{
																											sprintf(pStrBuf,"%c"" ""%s",PrintSiteindex+65,"REJ");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintSiteindex] = 1;
																							}
																							else
																							{																					
																											sprintf(pStrBuf,"%c"" ""%s",PrintSiteindex+65,"SEL");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintSiteindex] = 0;

																							}																				  
																				}
																}
												    else if(PrintActiveId >= ID_Print_Info_InfoSet_Prt_0 && PrintActiveId <= ID_Print_Info_InfoSet_Prt_4)
																{
																				PrintInfoindex = PrintActiveId - 2073;
																	   if(Language == 0)
																				{
																							if (PrintInfoSet[PrintInfoindex] == 0)
																							{
																											INFO("INDEX = %d",PrintInfoindex);
																											sprintf(pStrBuf,"%c""%s",PrintInfoindex+65,"不打印");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintInfoindex] = 1;
																							}
																							else
																							{																					
																											sprintf(pStrBuf,"%c""%s",PrintInfoindex+65,"打印");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintInfoindex] = 0;

																							}
																				}
																				else  //english
																				{
																							if (PrintInfoSet[PrintInfoindex] == 0)
																							{
																											INFO("INDEX = %d",PrintInfoindex);
																											sprintf(pStrBuf,"%c"" ""%s",PrintInfoindex+65,"REJ");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintInfoindex] = 1;
																							}
																							else
																							{																					
																											sprintf(pStrBuf,"%c"" ""%s",PrintInfoindex+65,"SEL");
																											_SetMenuItem(pMsg->hWin,0,pStrBuf,PrintActiveId,0);
																											PrintSiteSet[PrintInfoindex] = 0;

																							}																					
																				}
																}																
																break;
											case GUI_KEY_ESCAPE:
																PrintMenuThird = 0;
											     if (PrintActiveId >= ID_Print_All && PrintActiveId <= ID_Print_Info)
																	   break;
																
											case GUI_KEY_ENTER:
																PrintMenuThird = 0;
											default:
														MENU_Callback(pMsg);
														break;
								}
								break;
								
			case WM_POST_PAINT:
        if(PrintMenuID == ID_PrintMenu)
								{
									  GUI_SetColor(GUI_BLACK);
									  if (Language == 0)
											{
													GUI_DrawLine(193,0,193,197);
													GUI_DrawLine(0,197,193,197);
											}
											else  //english
											{
												 GUI_DrawLine(240,0,240,147);
													GUI_DrawLine(0,147,240,147);
											}
								}									
								break;
				default:
							 MENU_Callback(pMsg);
						 	break;
		}
}

//
//  PrintWinCallback
//
static void _cbDialog(WM_MESSAGE *pMsg)
{

		WM_KEY_INFO *KEY;
 	MENU_MSG_DATA * pData;
  switch (pMsg->MsgId)
	 {
			 case USER_MSG_LANGUAGE:
					    //pLanguage = &Lguprintwin[Language];
					    //TEXT_SetText(hPrintText,pLanguage->PrintTitle);
				     break;
			 case WM_PAINT:
									GUI_SetBkColor(GUI_WHITE);
									GUI_Clear();
									GUI_SetFont(&GUI_Font30);
									GUI_SetColor(GUI_BLACK);
				     //GUI_DispStringAt("打印选项",40,25);
				     if (Language == 0)
									{
										  GUI_DispStringAt("打印选项",40,25);
												GUI_DrawLine(0,59,193,59);
												GUI_DrawLine(193,20,193,59);
												GUI_DrawLine(0,20,193,20);
									}
									else  //ENGLISH
									{
										  GUI_DispStringAt("PRINT OPTIONS",30,25);
										  GUI_DrawLine(0,59,240,59);
												GUI_DrawLine(240,20,240,59);
												GUI_DrawLine(0,20,240,20);
									}
									break;
			
				case WM_MENU:
									pData = (MENU_MSG_DATA*)pMsg->Data.p;
									switch (pData->MsgType)
									{
							    case MENU_ON_ITEMSELECT:  // 选中
												    INFO("ISOK");
												    MENU_SetSel(hPrintMenu, 0);
											     PrintActiveId = ID_Print_All;
																switch (pData->ItemId)
																{
																	  case ID_Print_Fre_Int: 
																	  case ID_Print_Fre_Loc1:
																	  case ID_Print_Fre_Loc2:
																			case ID_Print_Fre_Chs : 
																			case ID_Print_Info_Prt:
																			case ID_Print_Site_Prt:
																			case ID_Print_All:
																			case ID_Print_Showing:
																				    pTooltip = &Lgutooltip[Language];
																				    StarPrint = 1;
																								//ptipText = "正在打印......";
																								WM_BringToTop(ToolTip);
																								WM_SetFocus(ToolTip);
																								WM_HideWindow(ToolTip_BUTTON[0]);
																								WM_HideWindow(ToolTip_BUTTON[1]);
																								WM_HideWindow(ToolTipText1);
																								TEXT_SetText(ToolTipText0,pTooltip->Text1[4]);
																			
																			     PrintTimer = WM_CreateTimer(ToolTip,0,2000,0);
																			
																								break;
																}
																break;
										
												case MENU_ON_ITEMACTIVATE:  //高亮
													    PrintActiveId = pData->ItemId;
												     _SetHintText(PrintHintText,PrintActiveId,1);  //设置提示信息
																	switch (pData->ItemId)    //用于修正第三级菜单的窗口位置	
																	{
																					case ID_Print_Site_SiteSet_Prt_0:
																						    if(Language == 0)
																										{
																													if (PrintMenuThird == 0)
																													{
																																WM_MoveWindow(hSiteSet,195,81);
																																PrintMenuThird = 1;
																													}
																										}
																										else  
																										{
																											  if (PrintMenuThird == 0)
																													{
																																WM_MoveWindow(hSiteSet,240,90);
																																PrintMenuThird = 1;
																													}
																										}
																										break;
																								
																					case ID_Print_Info_InfoSet_Prt_0:
																										if (Language == 0)
																										{
																													if(PrintMenuThird == 0)
																													{
																																WM_MoveWindow(hInfoSet,195,121);
																																PrintMenuThird = 1;
																													}
																										}
																										else
																										{
																											  if(PrintMenuThird == 0)
																													{
																																WM_MoveWindow(hInfoSet,240,121);
																																PrintMenuThird = 1;
																													}
																										}
																								  break; 
                     default:
												             WM_DefaultProc(pMsg);
												            break;																								
																	}
																	break;
									  default:
												     WM_DefaultProc(pMsg);
												     break;
									}
         break;
							
			default:		
						WM_DefaultProc(pMsg);
						break;
		}
		WM_DefaultProc(pMsg);
}


/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN PrintWinCreate(void) {
		WM_HWIN hWin;
		hWin = WM_CreateWindow(0, 0, 800, 480,WM_CF_SHOW, _cbDialog, 0);
	 hPrintMenu = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_PrintMenu); //主菜单
	 PrintHintText = TEXT_CreateAsChild(40,440,800,40,hWin,ID_PrintText,WM_CF_SHOW,"",TEXT_CF_LEFT);
	 TEXT_SetFont(PrintHintText,&GUI_Font24);
	 //WIDGET_SetEffect(hMenu,&WIDGET_Effect_3D1L);
	 hFre = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_Print_Frequency); //频率分类
	 hSite = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_Print_Site); //站点分类
	 hInfo = MENU_CreateEx(0,0,0,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_Print_Info); //信息分类
	 hSiteSet = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_Print_Site_SiteSet); //站点打印设置
	 hInfoSet = MENU_CreateEx(0,0,100,0,WM_UNATTACHED,WM_CF_SHOW,MENU_CF_VERTICAL,ID_Print_Info_InfoSet); //信息打印设置
	
	//菜单回调
	 WM_SetCallback(hPrintMenu,&MenuCall);
	 WM_SetCallback(hFre,&MenuCall);
	 WM_SetCallback(hSite,&MenuCall);
	 WM_SetCallback(hInfo,&MenuCall);
	 WM_SetCallback(hSiteSet,&MenuCall);
	 WM_SetCallback(hInfoSet,&MenuCall);
	
	//左右间距
		MENU_SetBorderSize(hPrintMenu,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hPrintMenu,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hFre,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hFre,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hSite,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hSite,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hInfo,MENU_BI_LEFT,20);
		MENU_SetBorderSize(hInfo,MENU_BI_RIGHT,20);
		MENU_SetBorderSize(hSiteSet,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hSiteSet,MENU_BI_RIGHT,10);
		MENU_SetBorderSize(hInfoSet,MENU_BI_LEFT,10);
		MENU_SetBorderSize(hInfoSet,MENU_BI_RIGHT,10);
		
		//添加菜单项
		_AddMenuItem(hPrintMenu,   0,        "所有储存信息",        ID_Print_All  ,    0);
		_AddMenuItem(hPrintMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hPrintMenu,   0,        "正在显示的信息",      ID_Print_Showing  ,    0);
		_AddMenuItem(hPrintMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hPrintMenu,   hFre,     "按频率分类打印",      ID_Print_Frequency         ,    0);
		_AddMenuItem(hPrintMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hPrintMenu,   hSite,    "按站点分类打印",      ID_Print_Site              ,    0);
		_AddMenuItem(hPrintMenu,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hPrintMenu,   hInfo,    "按信息分类打印",      ID_Print_Info              ,    0);

		_AddMenuItem(hFre,   0,        "国际频道(518KHz)",       ID_Print_Fre_Int           ,    0);
		_AddMenuItem(hFre,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFre,   0,        "本地频道I(490KHz)",      ID_Print_Fre_Loc1          ,    0);
		_AddMenuItem(hFre,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFre,   0,        "本地频道II(4209.5KHz)",  ID_Print_Fre_Loc2          ,    0);
		_AddMenuItem(hFre,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hFre,   0,        "中文频道(486KHz)",       ID_Print_Fre_Chs           ,    0);

		_AddMenuItem(hSite,   0,        "打印",      ID_Print_Site_Prt          ,    0);
		_AddMenuItem(hSite,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSite,   hSiteSet, "站点设置",  ID_Print_Site_SiteSet      ,    0);

		_AddMenuItem(hSiteSet,   0,        "A打印",      ID_Print_Site_SiteSet_Prt_0   ,    0);
		_AddMenuItem(hSiteSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSet,   0,        "B打印",      ID_Print_Site_SiteSet_Prt_1  ,    0);
		_AddMenuItem(hSiteSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSet,   0,        "C打印",      ID_Print_Site_SiteSet_Prt_2  ,    0);
		_AddMenuItem(hSiteSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSet,   0,        "D打印",      ID_Print_Site_SiteSet_Prt_3  ,    0);
		_AddMenuItem(hSiteSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hSiteSet,   0,        "E打印",      ID_Print_Site_SiteSet_Prt_4  ,    0);

		_AddMenuItem(hInfo,   0,        "打印",      ID_Print_Info_Prt          ,    0);
		_AddMenuItem(hInfo,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfo,   hInfoSet, "信息设置",  ID_Print_Info_InfoSet      ,    0);

		_AddMenuItem(hInfoSet,   0,        "A打印",      ID_Print_Info_InfoSet_Prt_0   ,    0);
		_AddMenuItem(hInfoSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSet,   0,        "B打印",      ID_Print_Info_InfoSet_Prt_1  ,    0);
		_AddMenuItem(hInfoSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSet,   0,        "C打印",      ID_Print_Info_InfoSet_Prt_2  ,    0);
		_AddMenuItem(hInfoSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSet,   0,        "D打印",      ID_Print_Info_InfoSet_Prt_3,    0);
		_AddMenuItem(hInfoSet,   0,       0,      0,    MENU_IF_SEPARATOR);  //分割线
		_AddMenuItem(hInfoSet,   0,        "E打印",      ID_Print_Info_InfoSet_Prt_4  ,    0);
	
	
	 MENU_Attach (hPrintMenu,hWin,0,60,0,0,0);
 		WM_SetFocus(hPrintMenu);
//   MENU_SetSel(hMenu, 0);
  return hWin;
}

