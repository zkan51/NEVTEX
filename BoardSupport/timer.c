#include "lpc177x_8x_timer.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_gpdma.h"
#include "lpc177x_8x_uart.h"
#include "timer.h"

void lpc1788_TIMER_Init(void)//TIMER��ʱ����ʼ������
{
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type MatchConfigStruct;

	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL; 	/* ��ʼ��timer2, Ԥ��Ƶ����ʱ��Ϊ1000000uS = 1S */
	TIM_ConfigStruct.PrescaleValue	=400; //���ü���ʱ�ӷ�Ƶ��0.4�������һ��
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &TIM_ConfigStruct);

	MatchConfigStruct.MatchChannel = 0; //ʹ��ͨ��0
	MatchConfigStruct.IntOnMatch = ENABLE; //MR0��TCֵƥ��ʱ�����ж�
	MatchConfigStruct.ResetOnMatch = ENABLE; //MR0��TCֵ��ƥ��ʱTC��λ
	MatchConfigStruct.StopOnMatch = DISABLE;
	MatchConfigStruct.ExtMatchOutputType = 0;
	MatchConfigStruct.MatchValue =1; //0.4����ƥ���ж�
	TIM_ConfigMatch(LPC_TIM2, &MatchConfigStruct);

	TIM_ResetCounter(LPC_TIM2);	/* ��ʱ��������λ */

	NVIC_SetPriority(TIMER2_IRQn, ((0x01<<3)|0x01));/* ������ռ���ȼ�preemptionΪ1, �����ȼ�sub-priorityΪ1 */
	NVIC_EnableIRQ(TIMER2_IRQn);	/* ʹ��TIMER2�ж� */
	TIM_Cmd(LPC_TIM2, ENABLE);/* ������ʱ�� */
}

