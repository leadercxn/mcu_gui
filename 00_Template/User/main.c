/*
 * @Description: 
 * @Author: cxt
 * @Date: 2022-01-12 00:22:50
 * @LastEditTime: 2022-02-03 10:40:46
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
	uint16_t coord_x1 = 0;
	uint16_t coord_x2 = 0;
	uint8_t rate2[] = {30, 34, 38, 42, 50, 46, 42, 38, 42, 46, 50, 42, 36, 30};
	
	LCD_Init();
	UI_Display1();
	
	while (1)
	{
		LCD_FillRectanglePercent(120, 75, 275, 105, GREEN, rate2[i], &coord_x1);
		LCD_FillRectanglePercent(120, 125, 275, 155, BLUE, rate2[i], &coord_x2);

		i++;
		if (i >= (sizeof(rate2)/sizeof(rate2[0])))
		{
			i = 0;
		}
		delay_ms(50);
	}
	
	return 0;
}
