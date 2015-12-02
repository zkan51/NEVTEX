#include "LANGUAGE.H"

//char chsbutton[][13] =
//{
//	"全部信息",
//	"重要信息",
//	"搜救信息",
//	"新信息"
//};
//
//char enlbutton[][10] = 
//{
//  "ALL INFO",
//  "IMP INFO",
//  "SAR INFO",
//  "NEW INFO"
//};

const MAINWIN Lgumainwin[2] =
{
	{"所有信息","重要信息","新信息","搜救信息","高电压警告!","序号","信息编码","yyy/mm/dd","hh:mm","频道","信息类型","信息状态","当前页"},
	{"ALL MSG","IMPORTANT MSG","NEW MSG","SAR MSG","High Voltage!!","NO.","FORMAT","YYY/MM/DD","HH:MM","CHANNEL","TYPE","STATE","PAGE"}
};

const INFOTEXT Lguinfotext[2] = 
{
	{"信息","误字符率:00%","距离:458海里"},
	{"MSG","ERROR RATE:00%","DISTANCE:458 nm"}
};

const MENUWIN Lgumenuwin[2] = 
{
	{"主菜单","站点选择","信息选择","端口设置","系统设置",
	 "四频道同步选择","国际频道","本地频道I","本地频道II","中文频道",
	 "四频道同步选择","国际频道","本地频道I","本地频道II","中文频道",
	 "站点选择","信息选择",
	 "显示设置","报警音设置","按键音设置","时间设定","语言设置","天线设置","软件更新","恢复出厂设置","开启自检",
	 "A 接收","B 接收","C 接收","D 接收","E 接收",
	 "A 输出","B 输出","C输出","D输出","E输出",
	 "反色显示 关闭","反色显示 开启","睡眠设置 关闭","睡眠设置 开启",
	 "无操作15分钟进入睡眠模式",
	 "A类信息 开启","B类信息 开启","C类信息 开启","D类信息 开启",
	 "开启","关闭",
	 "UTC +0 2015 年 11 月 26 日 18:30",
	 "简体中文",
	 "有源天线","无源天线"
	 },

	{"MENU","RX STATION","MSG TYPE","OUTPUT SETTING","SYSTEM SETTING",
	 "SYNCHRONIZE ALL CHANNELS","INT CHANNEL(518KHz)","LOC I CHANNEL(490KHz)","LOC II CHANNEL(4209.5KHz)","CHINESE CHANNEL(486KHz)",
	 "SYNCHRONIZE ALL CHANNELS","INT CHANNEL(518KHz)","LOC I CHANNEL(490KHz)","LOC II CHANNEL(4209.5KHz)","CHINESE CHANNEL(486KHz)",
	 "RX STATION","MSG TYPE",
	 "DISPALY","ALARM","KEYPRESS BEEP","TIME","LANGUAGE","ANTENNA","SOFTWARE UPDATE","RESET TO FACTORY DEFAULTS","SELF-DIAGNOSTIC TESTS",
	 "A SEL","B SEL","C SEL","D SEL","E SEL",
	 "A SEL","B SEL","C SEL","D SEL","E SEL",
	 "REVERSE COLOR OFF","REVERSE COLOR ON","SLEEP MOOD OFF","SLEEP MOOD ON",
	 "SLEEP AFTER 15 MIN WITH NO OPERATION",
	 "MSG TYPE A ON","MSG TYPE B ON","MSG TYPE C ON","MSG TYPE D ON",
	 "ON","OFF",
	 "UTC +0 26/11/2015 18:30",
	 "ENGLISH",
	 "ACTIVE ANTENNA","POSSIVE ANTENNA"
	}
};

const PRINTWIN Lguprintwin[2] = 
{
	{"打印选项","所有储存的信息","正在显示的信息","按频率分类打印","按站点分类打印","按信息分类打印",
	 "国际频道","本地频道I","本地频道II","中文频道",
	 "打印","站点设置",
	 "打印","信息设置",
	 "A打印","B打印","C打印","D打印","E打印"
	},

	{"PRINT OPTIONS","ALL MSG STORED","MSG DISPALYED","PRINT BY FREQUENCY","PRINT BY RX STATION","PRINT BY MSG TYPE",
	 "INT CHANNEL(518KHz)","LOC I CHANNEL(490KHz)","LOC II CHANNEL(4209.5KHz)","CHINESE CHANNEL(486KHz)",
	 "PRINT","RX STATION",
	 "PRINT","MSG TYPE",
	 "A SEL","B SEL","C SEL","D SEL","E SEL"
	}
};

const TOOLTIP Lgutooltip[2] = 
{
	  {"未检测到系统更新文件。","按ESC键退出!",
				"请确定是否恢复出厂设置？",
				"请确认是否开始自检？",
				"正在打印......",
				"打印完成!",
				"否","是"
			},
			{
				"NO UPDATE FILE DETECTED,","PRESS ESC TO EXIT!",
				"RESTORE TO FACTORY\nDEFAULTS ARE YOU SURE？",
				"START SELF-DIAGNOSTIC\nTESTS ARE YOU SURE？",
				"PRINTING......",
				"FINISHED",
				"NO","YES"
			}
};

const CHECKWIN Lgucheckwin[2] = 
{
			{"国际频道 . . . . . . . . . . . . . . . . . . . . . 通过",
				"本地频道I. . . . . . . . . . . . . . . . . . . . . 通过",
				"本地频道II . . . . . . . . . . . . . . . . . . . . 通过",
				"中文频道 . . . . . . . . . . . . . . . . . . . . . 通过",
				"数据内存 . . . . . . . . . . . . . . . . . . . . . 通过",
				"天线单元 . . . . . . . . . . . . . . . . . . . . . 通过",
				"打印端口 . . . . . . . . . . . . . . . . . . . . . 通过",
				"报警铃声 . . . . . . . . . . . . . . . . . . . .  已执行"
			},
			{"INT CHANNEL   . . . . . . . . . . . . . . . . . . . . OK",
				"LOCI CHANNEL . . . . . . . . . . . . . . . . . . . . OK",
				"LOCII CHANNEL. . . . . . . . . . . . . . . . . . . .  OK",
				"CHINESE CHANNEL. . . . . . . . . . . . . . . . .  OK",
				"ROM                 . . . . . . . . . . . . . . . . . . . . OK",
				"ANTENNA         . . . . . . . . . . . . . . . . . . . . OK",
				"PRINT PORT       . . . . . . . . . . . . . . . . . . . . OK",
				"ALARM              . . . . . . . . . . . . . . . . . . . . COMPELTED"
			}
};
