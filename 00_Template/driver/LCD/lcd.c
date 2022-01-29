

#include "FONT.H"
#include "ST7789.h"
#include "lcd.h"

uint16_t POINT_COLOR = WHITE;	//画笔颜色
uint16_t BACK_COLOR  = 0xFFFF;   //背景色 
uint16_t m_x_start = 120;        // 动态显示框左边坐标
uint16_t m_x_end   = 275;        // 动态显示框右边坐标
uint16_t m_thick_rect_width = 3;    // 动态显示边框宽度

/**
 * @brief  设置光标坐标
 * 
 * @param[i] Xpos  光标x坐标
 * @param[i] Ypos  光标y坐标
 * 
 * @retval no return
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    _lcd_dev lcddev = GetLCDDev();
    WriteComm(lcddev.setxcmd);
    WriteData(Xpos >> 8);
    WriteData(Xpos & 0xff);
    WriteComm(lcddev.setycmd);
    WriteData(Ypos >> 8);
    WriteData(Ypos & 0xff);
}


/**
 * @brief  写命令到GRAM，使能更改画笔颜色，每次只改一个像素
 *          若更改多个像素颜色，只需要发送一次命令，不能发送多次，因为没发送一次，都会重新定位到光标位置
 * 
 * @param[i] argv[i]  void
 * 
 * @retval void
 */
void LCD_WriteRAM_Prepare(void)
{
    _lcd_dev lcddev = GetLCDDev();
    WriteComm(lcddev.wramcmd);
}

/**
 * @brief  更改画笔颜色，紧随LCD_WriteRAM_Prepare使用
 * 
 * @param[i] color  对应的画笔颜色
 * 
 * @retval no return
 */
void LCD_WriteRAM(uint16_t color)
{
    WriteData(color >> 8);
    WriteData(color & 0xff);
}

/**
 * @brief  画点函数
 * 
 * @param[i] x      目标点x坐标
 * @param[i] y      目标点y坐标
 * @param[i] color  目标点颜色
 * 
 * @retval no reutrn
 */
void LCD_DrawPoint(uint16_t x,uint16_t y, uint16_t color)
{
	LCD_SetCursor(x,y);		        //设置光标位置 
	LCD_WriteRAM_Prepare();	        //开始写入GRAM
    LCD_WriteRAM(color);
}

/**
 * @brief  LCD屏幕初始化
 * 
 * @param[i] void
 * 
 * @retval no return 
 */
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
    delay_ms(1);
    WriteComm(0x29);    // Display On

    LCD_Param_Setting();
    LCD_Clear(BLACK);
}

/**
 * @brief  清屏
 * 
 * @param[i] color  清屏颜色
 * 
 * @retval no return
 */
void LCD_Clear(uint16_t color)
{
    _lcd_dev lcddev = GetLCDDev();
    uint16_t width = lcddev.width * 2;
    // TODO: 数组大小不能用变量替代，可使用malloc开辟内存空间的方法避免
    uint8_t buf[640]; 

    LCD_SetCursor(0x00,0x00);	
    LCD_WriteRAM_Prepare();	 

    for (uint16_t y = 0; y < lcddev.height; y++)
    {
        for (uint16_t x = 0; x < lcddev.width*2; x += 2)
        // for (uint16_t x = 0; x < lcddev.width; x++)
        {
            buf[x] = (color >> 8);
            buf[x+1] = color & 0xff;
            // LCD_WriteRAM(color);
        }
        WriteBurstData(buf, lcddev.width*2);
    }
} 

/**
 * @brief  
 * 
 * @param[i] x      字符起始x坐标
 * @param[i] y      字符起始y坐标
 * @param[i] num    待显示字符
 * @param[i] size   字体大小，暂只支持12/16/24
 * @param[i] mode   是否叠加(1:是， 0:否)
 * 
 * @retval no return
 */
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{  							  
    uint8_t temp, t1, t;
	uint16_t y0 = y;

    //得到字体一个字符对应点阵集所占的字节数	
	uint8_t csize = (size/8 + ((size % 8) ? 1:0))*(size / 2);	
    _lcd_dev lcddev = GetLCDDev();
    
    //得到偏移后的值(ASCII字库是从空格开始取模，所以-' '就是对应字符的字库)
    num = num - ' ';       
    
	for (t = 0; t < csize; t++)
	{   
		if (size == 12)
        {
            temp = asc2_1206[num][t]; 	 	//调用1206字体
        }
		else if (size == 16)
        {
            temp = asc2_1608[num][t];	        //调用1608字体
        }
		else if (size == 24)
        {
            temp = asc2_2412[num][t];	        //调用2412字体
        }
		else 
        {
            return ;                            //没有的字库
        }

		for (t1 = 0; t1 < 8; t1++)
		{			    
			if (temp & 0x80)
            {
                LCD_DrawPoint(x, y, POINT_COLOR);
            }
			else if (mode == 0)
            {
                LCD_DrawPoint(x, y, BACK_COLOR);
            }

			temp <<= 1;
			y++;
			if (y >= lcddev.height)
            {
                return ;		//超区域了
            }

			if ((y - y0) == size)
			{
				y = y0;
				x++;
				if (x >= lcddev.width)
                {
                    return ;	//超区域了
                }
				break;
			}
		}  	 
	}  	    	   	 	  
}  


/**
 * @brief  显示字符串底层函数
 * 
 * @param[i] x          字符串起始x坐标
 * @param[i] y          字符串起始x坐标
 * @param[i] width      屏幕宽度，超宽度须换行
 * @param[i] height     字体高度，超高度须另作处理
 * @param[i] size       字体大小
 * @param[i] *p         字符串起始地址
 * 
 * @retval no return
 */  
void LCD_WriteString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{         
	uint8_t x0 = x;
	width += x;
	height += y;
    while ((*p <= '~') && (*p>=' '))    //判断是不是非法字符!
    {       
        if (x >= width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
        {
            break;                      //退出
        }
        LCD_ShowChar(x, y, *p, size, 1);
        x += size / 2;
        p++;
    }  
}

/**
 * @brief  
 * 
 * @param[i] (x, y)     字符串起始坐标
 * @param[i] size       字体大小
 * @param[i] p          字符串起始地址
 * 
 * @retval [description] 
 */
void LCD_ShowString(uint32_t x, uint32_t y, uint8_t size, uint8_t *p)
{
    _lcd_dev lcddev = GetLCDDev();
    LCD_WriteString(x, y, lcddev.width, size, size, p);
}

/**
 * @brief  m^n
 * 
 * @param[i] m  底数
 * @param[i] n  指数
 * 
 * @retval result
 */
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result = 1;	 
	while (n--)
    {
        result*=m; 
    }   
	return result;
}	

/**
 * @brief  显示数组
 * 
 * @param[i] x      待显示数字x坐标
 * @param[i] y      待显示数字y坐标
 * @param[i] num    待显数字
 * @param[i] len    数字位数
 * @param[i] size   数值
 * 
 * @retval no return
 */
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow = 0;						   
	for (t = 0; t < len; t++)
	{
		temp = (num / LCD_Pow(10, len-t-1)) % 10;
		if ((enshow == 0) && (t < (len - 1)))
		{
			if (temp == 0)
			{
				LCD_ShowChar((x + (size / 2) * t), y, ' ', size, 0);
				continue;
			}
            else 
            {
                enshow=1; 
            }
		}
        LCD_ShowChar((x + (size/2) * t), y, (temp + '0'), size, 0); 
	}
} 


/**
 * @brief  显示数字,高位为0,也会显示
 * 
 * @param[i] x,y  起点坐标
 * @param[i] num  数值
 * @param[i] len  长度
 * @param[i] size 长度
 * @param[i] mode 状态标志
 *                  [7]:0,不填充;1,填充0.
 *                  [6:1]:保留
 *                  [0]:0,非叠加显示;1,叠加显示.
 *  
 * @retval [description] 
 */
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for (t = 0; t < len; t++)
	{
		temp = (num / LCD_Pow(10, len-t-1)) % 10;
		if ((enshow == 0) && (t < (len-1)))
		{
			if (temp == 0)
			{
				if (mode & 0X80)
                {
                    LCD_ShowChar((x + (size/2) * t), y, '0', size, (mode&0X01)); 
                } 
				else 
                {
                    LCD_ShowChar((x + (size/2) * t), y, ' ', size, (mode & 0X01)); 
                } 
                continue;
			}else 
            {
                enshow=1; 
            }
		}
        LCD_ShowChar((x + (size/2) * t), y, (temp + '0'), size, (mode & 0X01)); 
	}
} 


/**
 * @brief  填充指定区域指定颜色
 * 
 * @param[i] (sx,sy)  矩形坐标1
 * @param[i] (ex,ey)  矩形坐标2
 * @param[i] color    颜色
 * 
 * @retval no return
 */
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;

    xlen = ex - sx + 1;	 
    for (i = sy; i <= ey; i++)
    {
        LCD_SetCursor(sx, i);      				//设置光标位置 
        LCD_WriteRAM_Prepare();     			//开始写入GRAM	  
        for(j=0; j < xlen; j++)
        {
            LCD_WriteRAM(color);	            //显示颜色 
        }	    
    }	 
} 

/**
 * @brief  画线
 * 
 * @param[i] (x1, y1)  起点坐标
 * @param[i] (x2, y2)  终点坐标
 * @param[i] color     颜色
 * 
 * @retval no return
 */
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1;                          //计算坐标增量 
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 

	if (delta_x > 0)
    {
        incx=1;                                 //设置单步方向 
    }
	else if (delta_x == 0)
    {
        incx = 0;//垂直线 
    }
	else 
    {
        incx = -1;
        delta_x = -delta_x;
    } 

	if(delta_y > 0)
    {
        incy = 1; 
    }
	else if (delta_y == 0)
    {
        incy = 0;                     //水平线 
    }
	else
    {
        incy = -1;
        delta_y = -delta_y;
    } 

	if (delta_x > delta_y)
    {
        distance = delta_x;             //选取基本增量坐标轴 
    }
	else 
    {
        distance = delta_y; 
    }

	for (t = 0; t <= distance + 1; t++)             //画线输出 
	{  
		LCD_DrawPoint(uRow, uCol, color);//画点 
		xerr += delta_x; 
		yerr += delta_y; 

		if (xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if (yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
} 

/**
 * @brief  画粗线
 * 
 * @param[i] argv[i]  [description]
 * @param[i] argv[i]  [description]
 * @param[i] argv[i]  [description]
 * 
 * @retval [description] 
 */
void LCD_DrawThickLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t width)
{
    uint16_t delta_x = x2-x1;
    uint16_t delta_y = y2-y1;

    // 水平/垂直增粗
    for (uint8_t i = 0; i < width; i++)
    {
        if (delta_y == 0)
        {
            LCD_DrawLine(x1, y1+i, x2, y2+i, color);
        }
        else if (delta_x == 0)
        {
            LCD_DrawLine(x1+i, y1, x2+i, y2, color);
        }
    }
}

/**
 * @brief  画矩形
 * 
 * @param[i] (x1,y1)  矩形坐标1
 * @param[i] (x2,y2)  矩形对角坐标2
 * @param[i] color    边框颜色
 * 
 * @retval no return
 */
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}


/**
 * @brief  画粗矩形
 * 
 * @param[i] (x1,y1)  矩形坐标1
 * @param[i] (x2,y2)  矩形对角坐标2
 * @param[i] color    边框颜色
 * 
 * @retval no return
 */
void LCD_DrawThickRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t width)
{
    uint8_t i = 0;
    for (i = 0; i < width; i++)
    {
        LCD_DrawRectangle((x1+i), (y1+i), (x2-i), (y2-i), color);
    }
}

void LCD_FillRectanglePercent(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t rate)
{
    // 保留上次的
    static uint16_t x_end_old = 0;
    uint16_t x_end = x1 + (x2-x1)*rate/100;

    if (x_end == m_x_start)
    {
        x_end += m_thick_rect_width;
    }

    if (x_end == m_x_end)
    {
        x_end -= m_thick_rect_width;
    }

    if (rate >= 100)
    {
        rate = 100;
    }

    // 对框清屏
    if (x_end < x_end_old)
    {
        LCD_Fill(x_end, y1+m_thick_rect_width, x_end_old, y2-m_thick_rect_width, BLACK);
    }

    LCD_Fill(x1, y1, x_end, y2, color);
    x_end_old = x_end;
}

/**
 * @brief  xxx UI
 * 
 * @param[i] void
 * 
 * @retval no return
 */
void UI_Display(void)
{
	// 320*240
	LCD_DrawLine(160, 0, 160, 240, 0xFFFF);
	
	LCD_ShowString(28, 20, 16, "RF");
	LCD_ShowString(132, 20, 16, "AF");
	LCD_Fill(26, 50, 41, 215, 0x001F);
    LCD_Fill(130, 50, 145, 215, 0x07E0);
	
	LCD_ShowString(184, 20, 16, "AF");
	LCD_ShowString(284, 20, 16, "RF");
	LCD_Fill(180, 50, 195, 215, 0x07E0);
    LCD_Fill(284, 50, 299, 215, 0x001F);
	
	LCD_ShowString(70, 145, 24, "MHz");
	LCD_ShowString(220, 145, 24, "MHz");

	LCD_ShowString(60, 120, 24, "632.0");
	LCD_ShowString(210, 120, 24, "660.0");

    LCD_ShowString(75, 50, 16, "CH");
    LCD_ShowString(235, 50, 16, "CH");

    LCD_ShowString(78, 70, 24, "1");
    LCD_ShowString(225, 70, 24, "101");
}

/**
 * @brief  xxx UI
 * 
 * @param[i] void
 * 
 * @retval no return
 */
void UI_Display1(void)
{
    // 320*240
    // AC VOLTAGE  INPUT MODE
    POINT_COLOR = YELLOW;
    LCD_ShowString(60, 10, 16, "AC VOLTAGE   INPUT MODE");
    // 200V~240V
    POINT_COLOR = RED;
	LCD_ShowString(65, 35, 16, "200V~240V");
	// PARALLEL
    POINT_COLOR = GBLUE;
	LCD_ShowString(170, 35, 16, "PARALLEL");
	
	// CH1
    POINT_COLOR = GREEN;
    LCD_ShowString(15, 80, 16, "ANG1");
    LCD_DrawThickRectangle(10, 75, 50, 105, GREEN, m_thick_rect_width);
	//画线
    LCD_DrawThickLine(50, 88, 68, 88, GREEN, 3);
    LCD_DrawThickLine(75, 88, 82, 88, GREEN, 3);
    // 68dB
    LCD_ShowString(85, 80, 16, "68dB");
    // 动态框(120, 75), (275, 105)
    LCD_DrawThickRectangle(m_x_start, 75, m_x_end, 105, GREEN, m_thick_rect_width);

    LCD_DrawThickRectangle(280, 75, 315, 105, GREEN, m_thick_rect_width);
    LCD_ShowString(288, 80, 16, "CH1");

    // CH2
    POINT_COLOR = BLUE;
    LCD_DrawThickLine(60, 91, 60, 140, BLUE, 3);
    LCD_DrawThickLine(60, 140, 68, 140, BLUE, 3);
    LCD_DrawThickLine(75, 140, 82, 140, BLUE, 3);
    // 65dB
    LCD_ShowString(85, 133, 16, "65dB");
    // 动态框(120, 125), (275, 155)
    LCD_DrawThickRectangle(m_x_start, 125, m_x_end, 155, BLUE, m_thick_rect_width);

    LCD_DrawThickRectangle(280, 125, 315, 155, BLUE, m_thick_rect_width);
    LCD_ShowString(288, 133, 16, "CH2");

    // 温度显示
    POINT_COLOR = WHITE;
    LCD_ShowString(60, 220, 16, "TEMP:");
    POINT_COLOR = GREEN;
    LCD_ShowString(130, 220, 16, "28");
    LCD_ShowString(150, 220, 16, "C");

    // 风扇标志

    // 温度标记条
}
