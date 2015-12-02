#include "SPI1.h"
#include "lpc177x_8x_ssp.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"
#include "DMA.h"
#define SSP_TX_SRC_DMA_CONN		(GPDMA_CONN_SSP1_Tx)
#define SSP_RX_SRC_DMA_CONN		(GPDMA_CONN_SSP1_Rx)

SSP_CFG_Type SSP_ConfigStruct;// SSP Configuration structure variable

void  SPI1_Int(void)
{
  PINSEL_ConfigPin(0, 7, 2);//p0.7��SSP0_SCK
  PINSEL_ConfigPin(0, 6, 2);//p0.6: CS //SSP0_SSEL
  PINSEL_ConfigPin(0, 8, 2);//p0.8: SSP0_MISO
  PINSEL_ConfigPin(0, 9, 2);//p0.9: SSP0_MOSI
	
	SSP_ConfigStruct.CPHA = SSP_CPHA_FIRST;//SSP���ƼĴ�����֡����ĵ�һ��ʱ�������ز���������
	SSP_ConfigStruct.CPOL = SSP_CPOL_HI;//SSP������ʹ����ʱ����ÿ֡���ݴ���֮�䱣�ָߵ�ƽ
	SSP_ConfigStruct.ClockRate = 1000000;//
	SSP_ConfigStruct.Databit = SSP_DATABIT_8;//ÿ֡8λ����
	SSP_ConfigStruct.Mode = SSP_SLAVE_MODE;//ѡ��SSPΪ�ӻ�
	SSP_ConfigStruct.FrameFormat = SSP_FRAME_SPI;//SPI ģʽ
	
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);// Initialize SSP peripheral with parameter given in structure above
	
	LPC_SSP1->CR1 |= SSP_CR1_SSP_EN;//SSP_Cmd(0, ENABLE);// Enable SSP peripheral	
 printf("\n\rSPI_INIT\n\r");
}























































































































