#ifndef __ST7789_H
#define __ST7789_H

#include "FT32f0xx.h"
#include "delay.h"


#define PORTRAIT     0      // 竖屏
#define LANDSCAPE    1      // 横屏



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
	uint16_t height;		//LCD 高度
	uint16_t id;			//LCD ID
	uint8_t  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t wramcmd;		//开始写gram指令
	uint16_t setxcmd;		//设置x坐标指令
	uint16_t setycmd;		//设置y坐标指令 
} _lcd_dev; 	


void LCD_IOInit(uint8_t dir);
void WriteComm(uint8_t cmd);
void WriteData(uint8_t data);
void WriteBurstData(unsigned char *buff, uint16_t count);
void LCD_Param_Setting(void);
_lcd_dev GetLCDDev(void);

#endif


