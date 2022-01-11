#include "delay.h"


void delay_us(uint32_t us)
{
    // 晶振是8MHz==> 1/8us
    while (us--)
    {
        // 需要计算
        uint16_t i = 8;
        while (i--);
    }
    
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}


