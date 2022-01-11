#include "FT32f0xx.h"
#include "led.h"
#include "ST7789.h"

int main()
{
	uint32_t COLOR_ARRAY[] = {WHITE, BLACK, RED, GREEN, CYAN, YELLOW};
	uint8_t i = 0, j = 0;
	LED_Init();
	LCD_Init();

	
	while (1)
	{
		i++;
		if (j >= (sizeof(COLOR_ARRAY)/sizeof(COLOR_ARRAY[0])))
			j = 0;
			
		if (i % 2 == 1)
		{
			LED_On();
		}
		else
		{
			LED_Off();
		}
		delay_ms(1000);
		LCD_Clear(COLOR_ARRAY[j]);
		j++;
	}
	
	return 0;
}
