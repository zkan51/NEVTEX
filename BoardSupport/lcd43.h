/*******************************************************************************
 * ��Ϊ�������޹�˾ 		Copyright(C) 2013, baiweijishu 
 * ��Ŀ����(Project):			
 * �ļ���(File):				lcd43.h
 *
 * ����(Author):				������ (xi_iang)
 * ����(Email):					zhang.xiliang@163.com
 * ����֧����̳(Forum)��www.stm32bbs.com
 * �Ա��ٷ�����(Shop):  http://baiweijishu.taobao.com
 * �޸�����(Date): 			2013-11-29		
 *******************************************************************************/
#include "lpc177x_8x_lcd.h"

#define LCD_H_SIZE           800						 //Pixels per line  
#define LCD_H_PULSE          1               // HSYNC pulse width, 
#define LCD_H_FRONT_PORCH    80              // Horizontal front porch, 
#define LCD_H_BACK_PORCH     46              //Horizontal back porch,
#define LCD_V_SIZE           480             // Lines per panel
#define LCD_V_PULSE          2               // VSYNC pulse width, MSUT be 3
#define LCD_V_FRONT_PORCH    21               // Vertical front porch, 1,3�ǿ��Ե�
#define LCD_V_BACK_PORCH     21               // Vertical back porch, ����datasheet������32���������⣡1,3�ǿ��Ե�
#define LCD_PIX_CLK          (6.5*1000000l)  //

#define LCD_VRAM_BASE_ADDR_UPPER 	((uint32_t)SDRAM_BASE_ADDR + 0x1000000)
#define LCD_VRAM_BASE_ADDR_LOWER 	(LCD_VRAM_BASE_ADDR_UPPER + 1024*768*4)

//#define MAKE_COLOR(red,green,blue)  ((blue&0xF8) << 11 | (green&0xFC) << 5 | (red&0xF8))
#define MAKE_COLOR(red,green,blue)  (blue << 10 | green << 5 | red)

#define RED 		MAKE_COLOR(0xFF, 0, 0)
#define GREEN 	MAKE_COLOR(0, 0xFF, 0)
#define BLUE 		MAKE_COLOR(0, 0, 0xFF)
#define WHITE 	MAKE_COLOR(0xFF, 0xFF, 0xFF)
#define skyblue   MAKE_COLOR(0,0xBE,0xFF)
#define NavyBlue  MAKE_COLOR(0,0,0x28)

void lpc1788_Lcd_Init(void);
void LCD_test(void);

void LCD_Clear(LCD_PANEL panel, int Color);
void LCD_SetPixel(LCD_PANEL panel, int x, int y, int Color);
uint16_t LCD_GetPixel(LCD_PANEL panel, int x, int y);

/************************************* End *************************************/
