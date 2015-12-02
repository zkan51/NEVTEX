#include <ucos_ii.h>
#include "stdio.h"
#include "uart.h"
#include "app.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_uart.h"
#include "lpc177x_8x_timer.h"
#include "Config.h"
#include "DMA.h"
#include "uart.h"
#include "SPI1.h"


//#ifndef test_test
//	#define test_test
//#endif


/*-------------------- Macro defines ---------------------*/
/* �����������ȼ� */
#define UI_Task_PRIO             11
#define Insert_Task_PRIO         8
#define Refresh_Task_PRIO        9
#define Task_Stack_Use_PRIO      10  
/* ���������ջ��С */
#define USER_TASK_STACK_SIZE 4096
#define TOUCH_TASK_STACK_SIZE 256
#define KEY_TASK_STACK_SIZE 128
#define Task_Stack_Use_STACK_SIZE 128

/*------------------- static ----------------------------*/
/* ���������ջ */
static	OS_STK	UI_Task_Stack[USER_TASK_STACK_SIZE];


static	OS_STK	Insert_Task_Stack[TOUCH_TASK_STACK_SIZE];

static	OS_STK	Refresh_Task_Stack[KEY_TASK_STACK_SIZE];
static  OS_STK  Task_Stack_Use_Stack[Task_Stack_Use_STACK_SIZE];

static  OS_STK_DATA UI_Task_Stack_Use;
static  OS_STK_DATA Insert_Task_Stack_Use;
static  OS_STK_DATA Refresh_Task_Stack_Use;



/*----------------- external function -------------------*/
void mntSetting_init(void);

/*----------------- Global   variables --------------------*/
///Insert , Refresh�����ź���
int isKeyTrigged  = 0;



int ReleasedDectSwitch  = 0;

OS_EVENT * Refresher;
OS_EVENT * Updater;

///--��Ϣ���еĶ��岿��---
OS_EVENT *QSem;//������Ϣ����ָ��
void *MsgQeueTb[MSG_QUEUE_TABNUM];//������Ϣָ�����飬���г���Ϊ10
OS_MEM   *PartitionPt;//�����ڴ����ָ��
// #pragma arm section rwdata = "SD_RAM2", zidata = "SD_RAM2"
uint8_t  Partition[MSG_QUEUE_TABNUM][100];
// #pragma arm section rwdata
// uint8_t  Partition[20][300]__attribute__((at(0xA1FF0000)));
uint8_t myErr;
uint8_t myErr_2;
int list_endIndex  = -1;

///* ADDRESS: 0xAC000000  SIZE: 0x400000  */
#pragma arm section rwdata = "SD_RAM1", zidata = "SD_RAM1"


#pragma arm section rwdata


/*----------------- External functions -----------------------*/


/*----------------- External variables -----------------------*/
extern volatile int xlCnt;


struct message_18 msg_18;

int N_boat = 0;
static int LPC_recCnt  = 0;
/*----------------- local   function  --------------------*/


void SysTick_Init(void);






///* ADDRESS: 0xAC000000  SIZE: 0x400000  */




void UI_Task(void *p_arg)/*����(Description):	����UI_Task*/
{
	
//	while(1)
//	{ 
//		OSTimeDly(200);	
		MainTask();
//	}
}
/*����(Description):	����Insert_Task*/
void Insert_Task(void *p_arg)  //�ȴ����ղɼ���������
{ 
	int tmp  = 0;

	uint8_t *s; 
	INT8U err;
//	static int a=0;
	message_18 text_out;
	message_24_partA text_out_24A;
	type_of_ship text_out_type_of_ship; 
// USER_Init();
	while(1)
	{	

		s = OSQPend(QSem,0,&err);
  
  LPC_recCnt++; 
 
    tmp  = translate_(s,&text_out,&text_out_24A,&text_out_type_of_ship); 
    OSMutexPend(Refresher, 0, &myErr);        
    switch(tmp)
    {
       case 18:
            break;
        case 240:
            break;
        case 241:             
            break;
        default:
         break;
    }
OSMutexPost(Refresher);    
//		OSMemPut(PartitionPt,s);


		OSTimeDly(20); 

	}
}
void Refresh_Task(void *p_arg)//����Refresh_Task
{

	while(1)
	{
  OSMutexPend(Refresher, 0, &myErr);
//  OSMutexPend(Updater, 0, &myErr_2);
  OSMutexPost(Refresher); 
//  UART_SendByte(2, 'k');
#ifdef CODE_CHECK 
       
#endif 

//  CurMntBoatIndex++;
//  CurMntBoatIndex  = CurMntBoatIndex%N_monitedBoat;
  
  
		OSTimeDlyHMSM(0,0,5,0);
	}
}
void Task_Stack_Use(void *p_arg)
{
	OS_MEM_DATA MemInfo;
	
	while(1)
	{
		OSMemQuery(PartitionPt,&MemInfo);
// 		printf("\r\n**********%d----------\n\r",MemInfo.OSNUsed);
// 		printf("\r\n**********%d**********\n\r",MemInfo.OSNFree);
		OSTimeDly(1000); 		/* ��ʱ8000ms */
	}
}
void App_TaskStart(void)//��ʼ��UCOS����ʼ��SysTick���ģ���������������
{
	INT8U err;
  

  
//   SPI1_DMA_Init();
//   SPI1_Int();
  
	OSInit();  
	SysTick_Init();/* ��ʼ��SysTick��ʱ�� */
  Refresher  = OSMutexCreate(6,&myErr);
  Updater    = OSMutexCreate(6,&myErr_2);
	QSem = OSQCreate(&MsgQeueTb[0],MSG_QUEUE_TABNUM); //������Ϣ���У�10����Ϣ
	PartitionPt=OSMemCreate(Partition,MSG_QUEUE_TABNUM,100,&err);
	
	OSTaskCreateExt(UI_Task, (void *)0,(OS_STK *)&UI_Task_Stack[USER_TASK_STACK_SIZE-1],  UI_Task_PRIO, UI_Task_PRIO, (OS_STK *)&UI_Task_Stack[0], USER_TASK_STACK_SIZE,(void*)0, OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR );/* �������� UI_Task */
// 	OSTaskCreateExt(Insert_Task,(void *)0,(OS_STK *)&Insert_Task_Stack[TOUCH_TASK_STACK_SIZE-1],Insert_Task_PRIO,Insert_Task_PRIO,(OS_STK *)&Insert_Task_Stack[0],TOUCH_TASK_STACK_SIZE,(void*)0,OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR );/* �������� Insert_Task */
// 	OSTaskCreateExt(Refresh_Task,  (void *)0,(OS_STK *)&Refresh_Task_Stack[KEY_TASK_STACK_SIZE-1],    Refresh_Task_PRIO,  Refresh_Task_PRIO  ,(OS_STK *)&Refresh_Task_Stack[0],  KEY_TASK_STACK_SIZE,(void*)0,  OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR);/* �������� Refresh_Task */
	OSTaskCreate(Task_Stack_Use,(void *)0,(OS_STK *)&Task_Stack_Use_Stack[Task_Stack_Use_STACK_SIZE-1],  Task_Stack_Use_PRIO);/* �������� Refresh_Task */
//lpc1788_DMA_Init();  
//	DMA_Config(1);

	OSStart();
}

//		switch(translate_(s,&text_out,&text_out_24A,&text_out_type_of_ship))
int translate_(unsigned char *text,message_18 *text_out,message_24_partA *text_out_24A,type_of_ship *text_out_type_of_ship)
{
  int i=0,comma=0;
  int tmp  = 0;

  long shiftReg  = 0;
  
  if((text[0]!='!')&&(text[0]!='$'))
    return 0;
  if((text[1]=='A')&&(text[2]=='I')&&(text[3]=='V')&&(text[4]=='D')&&(text[5]=='M'))
  { 
     for(i=6; i<20; i++)
     {
        if(text[i] == ',')
        {
           comma++;
           if(comma == 5)
              break;
        }
     }    
     if(i<20)
     {     
          i++;     
          tmp  = change_table(text[i]);
           
          switch(tmp)
          {
            case 18:           
                 (*text_out)=translate_m18(text,i);
                 return 18;

            case 24:            
                if(change_table(text[i+6])&12)
                {
                   *text_out_type_of_ship = translate_m24B(text,i);
                   return 241;
                }
                else
                {               
                   *text_out_24A = translate_m24A(text,i); 
                   return 240;
                }
                            
           default:
                return tmp;
           
         }
      }
      else
      {
         return 0;
      }
  }

	else if((text[1]=='G')&&(text[2]=='P')&&(text[3]=='R')&&(text[4]=='M')&&(text[5]=='C')) //GPS GPRMC
	{
//    tempgprmc = text[6]; mothership.latitude = tempgprmc << 24;
//    tempgprmc = text[7]; mothership.latitude = mothership.latitude + (tempgprmc << 16);
//    tempgprmc = text[8]; mothership.latitude = mothership.latitude + (tempgprmc << 8);
//    mothership.latitude = mothership.latitude + text[9];
//    mothership.latitude = mothership.latitude/10;    
    shiftReg   = text[6];
    shiftReg   = (shiftReg << 8) | text[7];
    shiftReg   = (shiftReg << 8) | text[8];
    shiftReg   = (shiftReg << 8) | text[9];
    if(shiftReg )
    
    
//    tempgprmc = text[10]; mothership.longitude = tempgprmc << 24;
//    tempgprmc = text[11]; mothership.longitude = mothership.longitude + (tempgprmc << 16);
//    tempgprmc = text[12]; mothership.longitude = mothership.longitude + (tempgprmc << 8);
//    mothership.longitude = mothership.longitude + text[13];
//    mothership.longitude = mothership.longitude/10;
      
    shiftReg   = text[10];
    shiftReg   = (shiftReg << 8) | text[11];
    shiftReg   = (shiftReg << 8) | text[12];
    shiftReg   = (shiftReg << 8) | text[13];
    if(shiftReg)
    
//    tempgprmc = text[14]; mothership.SOG = mothership.SOG + (tempgprmc << 8);
//    mothership.SOG = mothership.SOG + text[15];

      shiftReg   = text[14];
      shiftReg   = (shiftReg << 8) | text[15];
   
//    tempgprmc = text[16]; mothership.COG = mothership.COG + (tempgprmc << 8);
//    mothership.COG = mothership.COG + text[17];

      shiftReg   = text[16];
      shiftReg   = (shiftReg << 8) | text[17];

//    tempgprmc = text[18]; SYS_Date = tempgprmc << 24;
//    tempgprmc = text[19]; SYS_Date = SYS_Date + (tempgprmc << 16);
//    tempgprmc = text[20]; SYS_Date = SYS_Date + (tempgprmc << 8);
//    SYS_Date = SYS_Date + text[21];

      shiftReg   = text[18];
      shiftReg   = (shiftReg << 8) | text[19];
      shiftReg   = (shiftReg << 8) | text[20];
      shiftReg   = (shiftReg << 8) | text[21];
    
   
//    tempgprmc = text[22]; SYS_Time = tempgprmc << 24;
//    tempgprmc = text[23]; SYS_Time = SYS_Time + (tempgprmc << 16);
//    tempgprmc = text[24]; SYS_Time = SYS_Time + (tempgprmc << 8);
//    SYS_Time = SYS_Time + text[25];	

      shiftReg   = text[22];
      shiftReg   = (shiftReg << 8) | text[23];
      shiftReg   = (shiftReg << 8) | text[24];
      shiftReg   = (shiftReg << 8) | text[25];
	}

return 0;
}

/************************************* End *************************************/






