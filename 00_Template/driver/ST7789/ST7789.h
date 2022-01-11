#ifndef __LCD_H
#define __LCD_H

#include "FT32f0xx.h"
#include "delay.h"

#define DIR_INPUT    0
#define DIR_OUTPUT   1

#define PORTRAIT     0      // 竖屏
#define LANDSCAPE    1      // 横屏

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

// CS--PC0, RESET--PC1, RS--PC2, WR--PC3, RD--PC4
#define CHIPSELECT_ENABLE   GPIO_ResetBits(GPIOC, GPIO_Pin_0)
#define CHIPSELECT_DISABLE  GPIO_SetBits(GPIOC, GPIO_Pin_0)

#define RESET_ENABLE        GPIO_ResetBits(GPIOC, GPIO_Pin_1)
#define RESET_DISABLE       GPIO_SetBits(GPIOC, GPIO_Pin_1)

#define RS_L_CMD            GPIO_ResetBits(GPIOC, GPIO_Pin_2)
#define RS_H_DAT            GPIO_SetBits(GPIOC, GPIO_Pin_2)

#define WRITE_LOW           GPIO_ResetBits(GPIOC, GPIO_Pin_3)
#define WRITE_HIGH          GPIO_SetBits(GPIOC, GPIO_Pin_3)

#define READ_ENABLE         GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define READ_DISABLE        GPIO_SetBits(GPIOC, GPIO_Pin_4)


typedef struct  
{										    
	uint16_t width;			//LCD 宽度
	uint16_t height;			//LCD 高度
	uint16_t id;				//LCD ID
	uint8_t  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t wramcmd;		//开始写gram指令
	uint16_t setxcmd;		//设置x坐标指令
	uint16_t setycmd;		//设置y坐标指令 
}_lcd_dev; 	

void LCD_IOInit(uint8_t dir);
void LCD_Init(void);
void LCD_Clear(uint16_t color);



#endif


