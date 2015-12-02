/*******************************************************************************
 * ��Ϊ�������޹�˾ 		Copyright(C) 2013, baiweijishu 
 * ��Ŀ����(Project):			
 * �ļ���(File):				sdram.c
 *
 * ����(Author):				������ (xi_iang)
 * ����(Email):					zhang.xiliang@163.com
 * ����֧����̳(Forum)��www.stm32bbs.com
 * �Ա��ٷ�����(Shop):  http://baiweijishu.taobao.com
 * �޸�����(Date): 			2013-11-29		
 *******************************************************************************/

#include "lpc177x_8x_libcfg_default.h"

#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_timer.h"

/************************************* End *************************************/
#include "sdram.h"
/************************************************************************************
*�ļ���  ��sdram.c																	                                *
*�ļ����ã�SDRAM����																	                              *
*����    ��ũ����																	                                  *
*����QQ  ��382421307															                                	*
*�ļ�����ʱ�䣺2012/05/11															                              *
*************************************************************************************/
#define EMC_NS2CLK(ns, nsPerClk)	((ns + nsPerClk - 1) / nsPerClk)
/*******************************************************************************************
* @��������SDRAM_GPIO_Config()
* @����  ��void
* @����ֵ��void
* @����  ��SDRAM�ܽ����ú������ڲ�����
*********************************************************************************************/
static void  SDRAM_GPIO_Config(void)
{ 
	
	/*����EMC��A0-A14*/
  LPC_IOCON->P4_0=0x01;
	LPC_IOCON->P4_1=0x01;
	LPC_IOCON->P4_2=0x01;
	LPC_IOCON->P4_3=0x01;
	LPC_IOCON->P4_4=0x01;
	LPC_IOCON->P4_5=0x01;
	LPC_IOCON->P4_6=0x01;
	LPC_IOCON->P4_7=0x01;
	LPC_IOCON->P4_8=0x01;
	LPC_IOCON->P4_9=0x01;
	LPC_IOCON->P4_10=0x01;
	LPC_IOCON->P4_11=0x01;
	LPC_IOCON->P4_12=0x01;
	LPC_IOCON->P4_13=0x01;
	LPC_IOCON->P4_14=0x01;
  /*����EMC��D0-D31*/
  LPC_IOCON->P3_0=0x01;
	LPC_IOCON->P3_1=0x01;
	LPC_IOCON->P3_2=0x01;
	LPC_IOCON->P3_3=0x01;
	LPC_IOCON->P3_4=0x01;
	LPC_IOCON->P3_5=0x01;
	LPC_IOCON->P3_6=0x01;
	LPC_IOCON->P3_7=0x01;
	LPC_IOCON->P3_8=0x01;
	LPC_IOCON->P3_9=0x01;
	LPC_IOCON->P3_10=0x01;
	LPC_IOCON->P3_11=0x01;
	LPC_IOCON->P3_12=0x01;
	LPC_IOCON->P3_13=0x01;
	LPC_IOCON->P3_14=0x01;
	LPC_IOCON->P3_15=0x01;
	#if SDRAM_TYPE==SDRAM_32BIT
	LPC_IOCON->P3_16=0x01;
	LPC_IOCON->P3_17=0x01;
	LPC_IOCON->P3_18=0x01;
	LPC_IOCON->P3_19=0x01;
	LPC_IOCON->P3_20=0x01;
	LPC_IOCON->P3_21=0x01;
	LPC_IOCON->P3_22=0x01;
	LPC_IOCON->P3_23=0x01;
	LPC_IOCON->P3_24=0x01;
	LPC_IOCON->P3_25=0x01;
	LPC_IOCON->P3_26=0x01;
	LPC_IOCON->P3_27=0x01;
	LPC_IOCON->P3_28=0x01;
	LPC_IOCON->P3_29=0x01;
	LPC_IOCON->P3_30=0x01;
	LPC_IOCON->P3_31=0x01;
	#endif
	 /* Pin configuration:
   * P2.16 - /EMC_CAS
   * P2.17 - /EMC_RAS  */
	LPC_IOCON->P2_16=0x01;
	LPC_IOCON->P2_17=0x01;
	/*
   * P2.18 - EMC_CLK[0]
   *
   * P2.20 - EMC_DYCS0
   *
   * P2.24 - EMC_CKE0
	*/
  LPC_IOCON->P2_18=0x01;
	LPC_IOCON->P2_20=0x01;
	LPC_IOCON->P2_24=0x01;
   /*
   * P2.28 - EMC_DQM0
   * P2.29 - EMC_DQM1
   * P2.30 - EMC_DQM2
   * P2.31 - EMC_DQM3*/
  LPC_IOCON->P2_28=0x01;
	LPC_IOCON->P2_29=0x01;
	/*���ʹ�õ���32BIT��SDRAM*/
#if SDRAM_TYPE==SDRAM_32BIT
	LPC_IOCON->P2_30=0x01;  
	LPC_IOCON->P2_31=0x01;
 #endif	
	/* P4.25 - /EMC_WE
   */
   LPC_IOCON->P4_25=0x01;
	
}
/*******************************************************************************************
* @��������SDRAM_Init()
* @����  ��void
* @����ֵ��void
* @����  ��SDRAM�ܽ����ú�������ʹ��SDRAMǰ�ȵ���
*********************************************************************************************/
void lpc1788_SDRAM_Init( void )
{
	volatile uint32_t i;
	volatile unsigned long Dummy;
	
	SDRAM_GPIO_Config();
	LPC_SC->PCONP   	|= 0x00000800;
	/*Init SDRAM controller*/
	LPC_SC->EMCDLYCTL |= (8<<0);
	/*Set data read delay*/
	LPC_SC->EMCDLYCTL |=(8<<8);
	LPC_SC->EMCDLYCTL |= (0x08 <<16);

	LPC_EMC->Control =1;
	LPC_EMC->DynamicReadConfig = 1;
	LPC_EMC->DynamicRasCas0 = 0;
	LPC_EMC->DynamicRasCas0 |=(3<<8);
	LPC_EMC->DynamicRasCas0 |= (3<<0);
	LPC_EMC->DynamicRP = P2C(SDRAM_TRP);
	LPC_EMC->DynamicRAS = P2C(SDRAM_TRAS);
	LPC_EMC->DynamicSREX = P2C(SDRAM_TXSR);
	LPC_EMC->DynamicAPR = SDRAM_TAPR;
	LPC_EMC->DynamicDAL = SDRAM_TDAL+P2C(SDRAM_TRP);
	LPC_EMC->DynamicWR = SDRAM_TWR;
	LPC_EMC->DynamicRC = P2C(SDRAM_TRC);
	LPC_EMC->DynamicRFC = P2C(SDRAM_TRFC);
	LPC_EMC->DynamicXSR = P2C(SDRAM_TXSR);
	LPC_EMC->DynamicRRD = P2C(SDRAM_TRRD);
	LPC_EMC->DynamicMRD = SDRAM_TMRD;
   
	 #if SDRAM_TYPE==SDRAM_32BIT
	// 13 row, 9 - col, SDRAM
	LPC_EMC->DynamicConfig0 = 0x0004680;
	// JEDEC General SDRAM Initialization Sequence
	// DELAY to allow power and clocks to stabilize ~100 us
	// NOP
	#else
	LPC_EMC->DynamicConfig0 = 0x000680;
	#endif
	LPC_EMC->DynamicControl = 0x0183;
	for(i= 200*30; i;i--);
	// PALL
	LPC_EMC->DynamicControl = 0x0103;
	LPC_EMC->DynamicRefresh = 2;
	for(i= 256; i; --i); // > 128 clk
	LPC_EMC->DynamicRefresh = P2C(SDRAM_REFRESH) >> 4;
	// COMM

    LPC_EMC->DynamicControl    = 0x00000083; /* Issue MODE command */
	#if SDRAM_TYPE==SDRAM_32BIT
	Dummy = *((volatile uint32_t *)(SDRAM_BASE| (0x32<<13)));
	#else
	Dummy = *((volatile uint32_t *)(SDRAM_BASE| (0x33<<12)));
	#endif
	// NORM
	LPC_EMC->DynamicControl = 0x0000;
	LPC_EMC->DynamicConfig0 |=(1<<19);
	for(i = 100000; i;i--);
}


void lpc1788_SDRAM_Clean()
{
  uint16_t * wr_ptr;
  int  i  = 0;
  
  wr_ptr  = (uint16_t*)SDRAM_BASE_ADDR;
  for(i=0;i<SDRAM_SIZE;i++)
  {
    *wr_ptr++  = 0x00;
  }
}
