#ifndef _MENUWIN_H
#define _MENUWIN_H

#include "WM.h"
#include "WIDGET.h"
#include "MENU.H"
#include "TEXT.H"
#include "DIALOG_Intern.h" 
#include "28.h"

extern WM_HWIN MenuHint;
extern char Language;
//
// 设置MENU内容
//
	static void _SetMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_SetItem(hMenu,Item.Id,&Item);
}

//
//添加MENU菜单项
//
static void _AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) {
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  MENU_AddItem(hMenu, &Item);
}

//
//更改提示信息
//
static void _SetHintText(WM_HWIN hText,int MenuId,int Flag)
{
	  if(Flag == 0)   //Menuwin
			{
				if(Language == 0)
				{
					 TEXT_SetFont(hText,&GUI_Font24);
						if (MenuId >= 0x801 && MenuId <= 0x804)    //站点选择，信息选择，端口选择，系统设置
						{
									TEXT_SetText(MenuHint,"按上下选择选项，ENT键进入下一级菜单，ESC键返回上一级菜单，MENU键退出菜单");
						}
						else if (MenuId >= 0x805 && 	MenuId <= 0x809) //四频道同步，国际频道，本地频道I，II，中文频道
						{
									TEXT_SetText(MenuHint,"按上下选择选项，左右键选择接收与不接收，ESC键返回上一级菜单，MENU键退出菜单");
						}
						else if (MenuId ==0x80a || MenuId == 0x80b)// 站点选择，信息选择
						{
									TEXT_SetText(MenuHint,"按上下选择选项，左右键选择输出与不输出，ESC键返回上一级菜单，MENU键退出菜单");
						}
						else if (MenuId == 0x810 || MenuId == 0x811 || MenuId == 0x812) //显示设置，报警音设置
						{
									TEXT_SetText(MenuHint,"按上下选择选项，左右键选择开启与关闭，ESC键返回上一级菜单，MENU键退出菜单");
						}
						else if (MenuId == 0x813) // 时间设定
						{
									TEXT_SetText(MenuHint,"按左右键切换时间模式，ESC键返回上一级菜单，MENU键退出菜单");
						}
						else if (MenuId == 0x814) //语言设定
						{
									TEXT_SetText(MenuHint,"按左右键切换语言，ESC键返回上一级菜单，MENU键退出菜单");
						}
					}
					else 
					{
						TEXT_SetFont(hText,&GUI_Font16_1);
						TEXT_SetText(MenuHint,"PRESS UP/DOWN TO SELECT THE ITEM，ENTER TO THE NEXT MENU, ESC TO THE PREVIOUS MENU, MENU TO EXIT");
					}
// 						else
// 						{
// 									TEXT_SetText(MenuHint,"");
// 						}
			}
			else if (Flag == 1) //PrintWint
			{
				if (Language == 0)
				{
					 TEXT_SetFont(hText,&GUI_Font24);
						TEXT_SetText(hText,"按上下选择选项，按ENT键打印，ESC键返回上一级菜单，PRINT键退出打印");
				}
				else
				{
					 TEXT_SetFont(hText,&GUI_Font16_1);
					 TEXT_SetText(hText,"PRESS UP/DOWN TO SELECT THE ITEM, ENT TO THE PRINT, ESC TO THE PREVIOUS MENU, PRINT TO EXIT");
				}
			}
}

#endif