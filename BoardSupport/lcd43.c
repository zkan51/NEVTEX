/*******************************************************************************
 * ��Ϊ�������޹�˾ 		Copyright(C) 2013, baiweijishu 
 * ��Ŀ����(Project):			
 * �ļ���(File):				lcd.c
 *
 * ����(Author):				������ (xi_iang)
 * ����(Email):					zhang.xiliang@163.com
 * ����֧����̳(Forum)��www.stm32bbs.com
 * �Ա��ٷ�����(Shop):  http://baiweijishu.taobao.com
 * �޸�����(Date): 			2013-11-29		
 *******************************************************************************/
#include "lpc177x_8x_lcd.h"
#include "lpc177x_8x_pinsel.h"
#include "lcd43.h"
#include "sdram.h"


/*******************************************************************************
 * ������(Function):	lpc1788_Lcd_Init
 * ����(Param):				�� 							
 * ����ֵ(Return):		��
 * ����(Description):	LCD��ʼ������
 *******************************************************************************/
void lpc1788_Lcd_Init(void)
{
	LCD_Config_Type lcd_config;

	/* ژҕLCD࠘׆ */
	LCD_Enable (FALSE);
 
	/* ��ʼ��SDRAM */
	lpc1788_SDRAM_Init();
 lpc1788_SDRAM_Clean();


 	/* ����LCD���� */
  lcd_config.big_endian_byte = 0;
  lcd_config.big_endian_pixel = 0;
  lcd_config.hConfig.hbp = LCD_H_BACK_PORCH;
  lcd_config.hConfig.hfp = LCD_H_FRONT_PORCH;
  lcd_config.hConfig.hsw = LCD_H_PULSE;
  lcd_config.hConfig.ppl = LCD_H_SIZE;
  lcd_config.vConfig.lpp = LCD_V_SIZE;
  lcd_config.vConfig.vbp = LCD_V_BACK_PORCH;
  lcd_config.vConfig.vfp = LCD_V_FRONT_PORCH;
  lcd_config.vConfig.vsw = LCD_V_PULSE;
  lcd_config.panel_clk   = LCD_PIX_CLK;
  lcd_config.polarity.active_high = 1;
  lcd_config.polarity.cpl = LCD_H_SIZE;
  lcd_config.polarity.invert_hsync = 1;
  lcd_config.polarity.invert_vsync = 1;
  lcd_config.polarity.invert_panel_clock = 0;
  lcd_config.lcd_panel_upper =  LCD_VRAM_BASE_ADDR_UPPER;
  lcd_config.lcd_panel_lower =  LCD_VRAM_BASE_ADDR_LOWER;
  lcd_config.lcd_bpp = LCD_BPP_16_565Mode;
  lcd_config.lcd_type = LCD_TFT;
	lcd_config.lcd_palette = NULL;
  lcd_config.lcd_bgr = FALSE;
	LCD_Initialize (&lcd_config);

//  LCD_SetImage(LCD_PANEL_UPPER, NULL);
//  LCD_SetImage(LCD_PANEL_LOWER, NULL);

	/* LCDʹ�� */
	LCD_Enable (TRUE);


}

/*******************************************************************************
 * ������(Function):	LCD_Clear
 * ����(Param):				panel
 *                    Color							
 * ����ֵ(Return):		��
 * ����(Description):	LCD����
 *******************************************************************************/
void LCD_Clear(LCD_PANEL panel, int Color)
{
	int i,j;
	uint16_t * pBuffer;
	if(panel == LCD_PANEL_UPPER)
		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_UPPER;
// 	else 
// 		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_LOWER;	 
	for(i = 0; i < LCD_H_SIZE; i++)
	{
		for(j = 0;j < LCD_V_SIZE; j++)
		{
			pBuffer[j*LCD_H_SIZE + i] = Color; 
		}
	}
}

/*******************************************************************************
 * ������(Function):	LCD_SetPixel
 * ����(Param):				panel
 *                    x
 *                    y	
 *                    Color							
 * ����ֵ(Return):		��
 * ����(Description):	LCD���㺯��
 *******************************************************************************/
void LCD_SetPixel(LCD_PANEL panel, int x, int y, int Color)
{
	uint16_t * pBuffer;
	if(panel == LCD_PANEL_UPPER)
		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_UPPER;
// 	else 
// 		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_LOWER;	 

	pBuffer[y*LCD_H_SIZE + x] = Color; 

}

/*******************************************************************************
 * ������(Function):	LCD_GetPixel
 * ����(Param):				panel
 *                    x
 *                    y	
 *                    Color							
 * ����ֵ(Return):		���ص�����ֵ
 * ����(Description):	LCD���㺯��
 *******************************************************************************/
uint16_t LCD_GetPixel(LCD_PANEL panel, int x, int y)
{
	uint16_t * pBuffer;
	if(panel == LCD_PANEL_UPPER)
		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_UPPER;
// 	else 
// 		pBuffer = (uint16_t *)LCD_VRAM_BASE_ADDR_LOWER;	 

	return pBuffer[y*LCD_H_SIZE + x]; 

}


/*******************************************************************************
 * ������(Function):	LCD_test
 * ����(Param):				�� 							
 * ����ֵ(Return):		��
 * ����(Description):	LCD����
 *******************************************************************************/
void LCD_test(void)
{
	int x, y;
	/* ��ʼ��LCD */
	lpc1788_Lcd_Init();

//	/* LCD���� */
//	LCD_Clear(LCD_PANEL_UPPER, WHITE);
//	LCD_Clear(LCD_PANEL_LOWER, WHITE);

//	/* ������ */
//	LCD_FillRectangle (LCD_PANEL_UPPER, 10, 100, 10, 100, GREEN);
//	LCD_FillRectangle (LCD_PANEL_UPPER, 100, 200, 100, 200, RED);
//	LCD_FillRectangle (LCD_PANEL_UPPER, 200, 300, 100, 200, BLUE);

//	for(x=350;x<400;x++)
//		for(y=100;y<200;y++)
//			LCD_PutPixel(LCD_PANEL_UPPER,x,y,RED);
}

/************************************* End *************************************/
