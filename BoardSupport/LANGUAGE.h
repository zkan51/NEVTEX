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
	char *MenuTitle;  //����
	char *Menu[4];    //���˵�

	char *Rx_Station[5]; //վ��ѡ��
	char *Msg_Type[5];  //��Ϣѡ��
	char *Output_Set[2];//�˿�ѡ��
	char *System_Set[9];//ϵͳ����

	char *IsReceive[5]; //���ա�������
	char *IsOutput[5]; //����������
	char *DispSet[4]; //��ʾ����
	char *SleepSet;  //˯������
	char *Alarm[4];  //����������
	char *KeyBeep[2]; //����������
	char *Time;      //ʱ������
	char *Language;  //��������
	char *Antenna[2];//��������
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