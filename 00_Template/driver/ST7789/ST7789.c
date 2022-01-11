#include "ST7789.h"

_lcd_dev lcddev;
uint16_t POINT_COLOR = 0x0000;	//画笔颜色
uint16_t BACK_COLOR  = 0xFFFF;   //背景色 

/*
 *  IO分配:
 *  DB Lines: 
 *      DB0--PB12, DB1--PB13, DB2--PB14, DB3--PB15, DB4--PC6, DB5--PC7, DB6--PC8, DB7--PC9
 */
// TODO: 根据dir确定输出方向，以防需要读命令
void LCD_DBLineInit(uint8_t dir)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
}

/*
 *  IO分配:
 *  Functional Pins:
 *      CS--PC0, RESET--PC1, RS--PC2, WR--PC3, RD--PC4
 */
void LCD_IOInit(uint8_t dir)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);

    LCD_DBLineInit(dir);
    
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}


// DB0--PB12, DB1--PB13, DB2--PB14, DB3--PB15, DB4--PC6, DB5--PC7, DB6--PC8, DB7--PC9
void Send_RawData(uint8_t cmd)
{
    if (cmd & 0x80)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_9);
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_9);
    }

    if (cmd & 0x40)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_8);
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    }

    if (cmd & 0x20)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    }

    if (cmd & 0x10)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_6);
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_6);
    }

    if (cmd & 0x08)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_15);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_15);
    }

    if (cmd & 0x04)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_14);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);
    }

    if (cmd & 0x02)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_13);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    }

    if (cmd & 0x01)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    }
}

// 发送命令，实现时序
void WriteComm(uint8_t cmd)
{
    CHIPSELECT_ENABLE;
    RS_L_CMD;
    WRITE_LOW;
    Send_RawData(cmd);
    // delay_us(10);              
    WRITE_HIGH;
    // delay_us(10);

    CHIPSELECT_DISABLE;
}

// 发送数据，实现时序
void WriteData(uint8_t data)
{
    CHIPSELECT_ENABLE;
    RS_H_DAT;
    WRITE_LOW;
    Send_RawData(data);
    // delay_us(10);
    WRITE_HIGH;
    // delay_us(10);

    CHIPSELECT_DISABLE;
}

void WriteBurstData(unsigned char *buff, uint16_t count)
{
    CHIPSELECT_ENABLE;
    RS_H_DAT;

    for (uint16_t i = 0; i < count; i++)
    {
        WRITE_LOW;
        Send_RawData(buff[i]);
        WRITE_HIGH;
        delay_us(10);
    }
    CHIPSELECT_DISABLE;
}

// ST7789屏幕参数设置
void LCD_Param_Setting(void)
{
    lcddev.width    = 320;
    lcddev.height   = 240;
    lcddev.id       = 0;        // 该参数可读
    lcddev.dir      = LANDSCAPE;
    lcddev.wramcmd  = 0x2C;
    lcddev.setxcmd  = 0x2A;
    lcddev.setycmd  = 0x2B;

    WriteComm(lcddev.setxcmd);
    WriteData(0);
    WriteData(0);
    WriteData((lcddev.width-1) >> 8);
    WriteData((lcddev.width-1) & 0xff);

    WriteComm(lcddev.setycmd);
    WriteData(0);
    WriteData(0);
    WriteData((lcddev.height-1) >> 8);
    WriteData((lcddev.height-1) & 0xff);
}

// 设置坐标
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    WriteComm(lcddev.setxcmd);
    WriteData(Xpos >> 8);
    WriteData(Xpos & 0xff);
    WriteComm(lcddev.setycmd);
    WriteData(Ypos >> 8);
    WriteData(Ypos & 0xff);
}

// 更改画笔颜色
void LCD_WriteRAM_Prepare(void)
{
    WriteComm(lcddev.wramcmd);
}

void LCD_WriteRAM(uint16_t color)
{
    WriteData(color >> 8);
    WriteData(color & 0xff);
}

void LCD_DrawPoint(uint16_t x,uint16_t y, uint16_t color)
{
	LCD_SetCursor(x,y);		        //设置光标位置 
	LCD_WriteRAM_Prepare();	//开始写入GRAM
}

void LCD_Clear(uint16_t color)
{
    unsigned char buf[320*2];
    LCD_SetCursor(0x00,0x00);	
    LCD_WriteRAM_Prepare();	 

    for (uint16_t y = 0; y < lcddev.height; y++)
    {
        for (uint16_t x = 0; x < 320*2; x = x+2)
        {
            buf[x] = (color >> 8);
            buf[x+1] = color & 0xff;
        }
        WriteBurstData(buf, 320*2);
    }
} 

// LCD初始化
void LCD_Init(void)
{
    LCD_IOInit(DIR_OUTPUT);

    WriteComm(0x36);    // 显示扫描方向
    WriteData(0xA0);    // 00:从左到右，从上到下
                        // A0:从下到上，从左到右
                        // 60:从上到下，从右到左

    WriteComm(0x3A);    // color format
    WriteData(0x05);    // 16bit/pixel

    WriteComm(0xB2);    // Porch Setting  
    WriteData(0x0C);   
    WriteData(0x0C);   
    WriteData(0x00);   
    WriteData(0x33);   
    WriteData(0x33);   

    WriteComm(0xB7);    // Gate Control
    WriteData(0x35);   

    WriteComm(0xBB);    // VCOM  
    WriteData(0x1C);   

    WriteComm(0xC0);    // LCM control   
    WriteData(0x2C);   

    WriteComm(0xC2);    // VDV and VRH Command Enable 
    WriteData(0x01);   

    WriteComm(0xC3);    //  VRH Set  
    WriteData(0x0B);       

    WriteComm(0xC4);    // VDV Set
    WriteData(0x20);   

    WriteComm(0xC6);    // Frame Rate    
    WriteData(0x0F);   

    WriteComm(0xD0);    // Power Control 1
    WriteData(0xA4);   
    WriteData(0xA1);   

    WriteComm(0xE0);    // Positive Voltage     
    WriteData(0xD0);   
    WriteData(0x06);   
    WriteData(0x0B);   
    WriteData(0x0A);   
    WriteData(0x09);   
    WriteData(0x06);   
    WriteData(0x2F);   
    WriteData(0x44);   
    WriteData(0x45);   
    WriteData(0x18);   
    WriteData(0x14);   
    WriteData(0x14);   
    WriteData(0x27);   
    WriteData(0x2D);   

    WriteComm(0xE1);    // Negative Voltage    
    WriteData(0xD0);   
    WriteData(0x06);   
    WriteData(0x0B);   
    WriteData(0x0A);   
    WriteData(0x09);   
    WriteData(0x05);   
    WriteData(0x2E);   
    WriteData(0x43);   
    WriteData(0x45);   
    WriteData(0x18);   
    WriteData(0x14);   
    WriteData(0x14);   
    WriteData(0x27);   
    WriteData(0x2D);   

    WriteComm(0x21);    // Display Inversion On
    WriteComm(0x11);    // Sleep Out
    delay_ms(120);
    WriteComm(0x29);    // Display On

    LCD_Param_Setting();
    LCD_Clear(WHITE);
}





