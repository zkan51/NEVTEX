#include "lpc177x_8x_pwm.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_adc.h"
#include "lpc177x_8x_pinsel.h"
#include "pwm.h"

#define _BACK_LIGHT_BASE_CLK (1000/4)
	uint32_t pclk;
void lpc1788_PWM_Init(void)//PWM��ʼ������
{
//	uint32_t pclk;
  PWM_TIMERCFG_Type PWMCfgDat;
  PWM_MATCHCFG_Type PWMMatchCfgDat;
	
  PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;/* ֱ��ʹ�÷�Ƶֵ(���⻹����ʹ��΢��ֵ) */
  PWMCfgDat.PrescaleValue = 1;  //Ƶ��=fpclk
  PWM_Init(1, PWM_MODE_TIMER, (void *) &PWMCfgDat);/* PWM1��ʹ�ö�ʱģʽ�����⻹����ʹ�ü���ģʽ�� */		
	PINSEL_ConfigPin(1,18,2);/*����PWM���� P1.18: PWM1_1*/
	PWM_ChannelConfig(1, 1, PWM_CHANNEL_SINGLE_EDGE);	/* ����PWM1ͨ��1����������ؿ���ģʽ */

  pclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);	/* ����PWM1ͨ��1���������� */
  PWM_MatchUpdate(1, 0, pclk/_BACK_LIGHT_BASE_CLK, PWM_MATCH_UPDATE_NOW);
  PWMMatchCfgDat.IntOnMatch = DISABLE;
  PWMMatchCfgDat.MatchChannel = 0;
  PWMMatchCfgDat.ResetOnMatch = ENABLE;
  PWMMatchCfgDat.StopOnMatch = DISABLE;
  PWM_ConfigMatch(1, &PWMMatchCfgDat);

  PWM_MatchUpdate(1, 1, (pclk/_BACK_LIGHT_BASE_CLK)/2, PWM_MATCH_UPDATE_NOW);	/* ����PWM1ͨ��2������ռ�ձ�, ������Ϊ50% */
  PWMMatchCfgDat.IntOnMatch = DISABLE;
  PWMMatchCfgDat.MatchChannel = 1;
  PWMMatchCfgDat.ResetOnMatch = DISABLE;
  PWMMatchCfgDat.StopOnMatch = DISABLE;
  PWM_ConfigMatch(1, &PWMMatchCfgDat);

  PWM_ChannelCmd(1, 1, ENABLE);  /* ʹ��PWM1ͨ��2��� */
  PWM_ResetCounter(1);/* ��λPWM1������ */
  PWM_CounterCmd(1, ENABLE);/* PWM1����ʹ�� */
  PWM_Cmd(1, ENABLE);  /* PWMģʽʹ�� */
}
void SetBackLight(uint32_t level)//����PWMռ�ձȣ�����LCD��������
{ 
  PWM_MATCHCFG_Type PWMMatchCfgDat;
  PWM_MatchUpdate(1, 1, level, PWM_MATCH_UPDATE_NOW);	/* ����PWM1ͨ��2������ռ�ձ� */
  PWMMatchCfgDat.IntOnMatch = DISABLE;
  PWMMatchCfgDat.MatchChannel = 1;
  PWMMatchCfgDat.ResetOnMatch = DISABLE;
  PWMMatchCfgDat.StopOnMatch = DISABLE;
  PWM_ConfigMatch(1, &PWMMatchCfgDat);
}

void PWM_SET(uint8_t PWM)//PWM_test
{
	  uint32_t BACK_LIGHT;
	  BACK_LIGHT=pclk/_BACK_LIGHT_BASE_CLK/10;
    printf("\r\nBACK_LIGHT:%d\n\r",PWM);
		SetBackLight(BACK_LIGHT*PWM);
}



/************************************* End *************************************/
