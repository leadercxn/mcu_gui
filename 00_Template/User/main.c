/*
 * @Description: 
 * @Author: cxt
 * @Date: 2022-01-12 00:22:50
 * @LastEditTime: 2022-01-29 14:27:43
 * @LastEditors: cxt
 * @Reference: 
 */
#include "FT32f0xx.h"
#include "led.h"
#include "lcd.h"
#include "delay.h"

int main()
{
	uint8_t i = 0;
	uint8_t order = 0;		// 0-->µİÔö£¬1-->µİ¼õ
	LCD_Init();
	UI_Display1();
	
	while (1)
	{
		LCD_FillRectanglePercent(120, 75, 275, 105, GREEN, i*10);
		LCD_FillRectanglePercent(120, 125, 275, 155, BLUE, i*10);
		if (i >= 10)
		{
			order = 1;
		}
		else if (i == 0)
		{
			order = 0;
		}
		if (order == 1)
		{
			i--;
		}
		else 
		{
			i++;
		}
		delay_ms(300);
	}
	
	return 0;
}
