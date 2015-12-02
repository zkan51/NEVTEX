#ifndef _LANGUAGE_H
#define _LANGUAGE_H

typedef struct _MAINWIN MAINWIN;
struct _MAINWIN
{
   char *ButtonInfo[4];
   char *hpAlarm;
   char *ListHead[7];
   char *Page;
};

typedef struct _INFOTEXT INFOTEXT;
struct _INFOTEXT
{
	char *Button;
	char *ErrorRate;
	char *Distance;
};

typedef struct _MENUWIN MENUWIN;
struct _MENUWIN 
{
	char *MenuTitle;  //标题
	char *Menu[4];    //主菜单

	char *Rx_Station[5]; //站点选择
	char *Msg_Type[5];  //信息选择
	char *Output_Set[2];//端口选择
	char *System_Set[9];//系统设置

	char *IsReceive[5]; //接收、不接受
	char *IsOutput[5]; //输出、不输出
	char *DispSet[4]; //显示设置
	char *SleepSet;  //睡眠设置
	char *Alarm[4];  //报警音设置
	char *KeyBeep[2]; //按键音设置
	char *Time;      //时间设置
	char *Language;  //语言设置
	char *Antenna[2];//天线设置
	//char *HintText[];
};

typedef struct _PRINTWIN PRINTWIN;
struct _PRINTWIN
{
	char *PrintTitle;
	char *PrintMenu[5];
	char *Frequency[4];
	char *StaTion[2];
	char *InfoType[2];
	char *IsPrint[5];
	//char *HintText[];
};

typedef struct _TOOLTIP TOOLTIP;
struct _TOOLTIP
{
	char *Text1[6];
	char *Button[2];
};

typedef struct _CHECKWIN CHECKWIN;
struct _CHECKWIN
{
	char *CheckItem[8];
	//char *IsOK[3];
};

extern const MAINWIN Lgumainwin[2];
extern const INFOTEXT Lguinfotext[2];
extern const MENUWIN Lgumenuwin[2];
extern const PRINTWIN Lguprintwin[2];
extern const CHECKWIN Lgucheckwin[2];
extern const TOOLTIP Lgutooltip[2];
#endif