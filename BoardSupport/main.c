#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_lcd.h"
#include "uart.h"
#include "dma.h"
#include "timer.h"
#include "lcd43.h"
//#include "w25qxx.h"
#include "pwm.h"
#include <ucos_ii.h>
// #include "exfuns.h"
#include "lpc177x_8x_eeprom.h"
#include "lpc177x_8x_uart.h"

////////
///////
//////
////
///
//
//
extern volatile int TimeMS;  // Defined in GUI_X.c

void SysTick_Handler (void);
void Delay (int tick);
void App_TaskStart(void);

void SysTick_Handler (void)//	SysTick�жϷ�����
{
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */
	TimeMS++;
	OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}

void SysTick_Init(void)//SysTick_Init
{
	uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);	/* ��ȡϵͳʱ��Ƶ�� */
	SysTick_Config(cclk/OS_TICKS_PER_SEC - 1);	/* ����SysTickΪ10ms�ж�һ�� */
}

int main(void)
{	
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);/* ��GPIO�����Դ���ϵ��GPIO��ԴĬ���Ǵ򿪵ģ����п�ȥ�� */


//��ʼ��UART0 ��UART2����Timer2
	USER_Init();
	lpc1788_Lcd_Init();	  /* ��ʼ��LCD */	
 lpc1788_PWM_Init();
 EEPROM_Init();
 
//	LCD_test();
  //fs_test();
//  	exfuns_init();
//  	load_font(); //����flash�ֿ�  7E 02 01 EF

	App_TaskStart();

	while(1);
}

/************************************* End *************************************/
