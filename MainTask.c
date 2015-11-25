#include "GUI.h"
#include "DIALOG.h"
#include "MainTask.h"
#include "exfuns.h"
#include "logo.h"
#include "120.h"
#include "28.h"
#include "dlg.h"
#include "sound.h"
#define ID_BUTTON_0 (GUI_ID_USER + 0x11)
	static void _AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_AddItem(hMenu, &Item);
}
void MainTask(void)
{
   GUI_MEMDEV_Handle hMem0;
   
	  SND_SelectID(SND_ID_WLCM);
   GUI_Init();	
   WM_SetCreateFlags(WM_CF_MEMDEV);
   //开机界面
   hMem0 = GUI_MEMDEV_Create(0,0,800,480);
   GUI_MEMDEV_Select(hMem0);
   GUI_SetBkColor (GUI_WHITE);
   GUI_Clear();
   
   /// Welcome logo 
   GUI_SetColor (GUI_BLACK);
   GUI_SetFont (&GUI_Font120);
   GUI_DispStringAt("NAVTEX RECEIVER",90,LCD_GetYSize()/3+60);
   GUI_PNG_Draw (&acLogo,sizeof(acLogo),120,LCD_GetYSize()/4);  
   GUI_MEMDEV_Select(0);
   GUI_MEMDEV_CopyToLCD(hMem0);
   GUI_MEMDEV_Delete(hMem0);
   
   //sysInit();
   //MNT_initSetting();
   
   GUI_Delay(1000);
    GUI_Clear();
   //创建字体
   GUI_UC_SetEncodeUTF8();	
   //字体设置	//GUI_SetDefaultFont (&SIF_Font);
   GUI_SetDefaultFont (&GUI_Font30);	
   TEXT_SetDefaultFont(&GUI_Font30);
   BUTTON_SetDefaultFont (&GUI_Font30);
   HEADER_SetDefaultFont(&GUI_Font30);
			MENU_SetDefaultFont (&GUI_Font30);
   HEADER_SetDefaultBkColor(GUI_BLUE);
   //EDIT_SetDefaultFont(&GUI_Font30);
			WIDGET_SetDefaultEffect(&WIDGET_Effect_None);
			MENU_SetDefaultEffect(&WIDGET_Effect_3D);
			MENU_SetDefaultBkColor(MENU_CI_ENABLED,GUI_WHITE);
			MENU_SetDefaultBkColor(MENU_CI_SELECTED,GUI_BLACK);
		//MENU_SetDefaultTextColor()
   //创建窗口 
//   sldWinCreate();
//     _sldWinCreate();
//     WM_SetFocus(_sldWinCreate());
//    confirmWin  = confirmWinCreate();
// 	 WM_ShowWindow (confirmWin);
//    mntSettingWin  = mntSettingWinCreate(); 
// //  _mntSettingWin  = _mntSettingWinCreate();
//    subWins[0]  = sub0WinCreate(); 
//    subWins[1]  = sub1WinCreate();
//    subWins[2]  = sub2WinCreate();
//    subWins[3]  = _sub3WinCreate();
//    menuWin  = menuWinCreate();
//    mapWin = mapWinCreate();

//  Window Creat
    PrintWin = PrintWinCreate();
    ToolTip = ToolTipCreate();
  	 Menuwin = MenuWinCreate();
  		CheckWin = CheckWinCreate();
    InfoText = InfoTextCreate();
   	mainwin = mainWinCreate();
	   WM_SetFocus (WM_GetDialogItem (mainwin,ID_BUTTON_0));
	//
   while(1)
   {
      GUI_Delay(200);
   }
}

/*************************** End of file ****************************/
