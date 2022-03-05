#include "tft_lcd_handler.h"
#include "board_config.h"
#include "picture.h"


static lcd_drv_t    m_st7789_obj = 
{
    // CS--PC0, RESET--PC1, RS--PC2, WR--PC3, RD--PC4
    .cs_pin.gpio_port_periph_clk    = ST7789_CS_PORT_PERIPH_CLK,
    .cs_pin.p_gpio_port             = ST7789_CS_PORT,
    .cs_pin.gpio_dir                = GPIO_DIR_OUTPUR,
    .cs_pin.gpio_pin                = ST7789_CS_PIN,

    .rst_pin.gpio_port_periph_clk   = ST7789_RST_PORT_PERIPH_CLK,
    .rst_pin.p_gpio_port            = ST7789_RST_PORT,
    .rst_pin.gpio_dir               = GPIO_DIR_OUTPUR,
    .rst_pin.gpio_pin               = ST7789_RST_PIN,

    .rs_pin.gpio_port_periph_clk    = ST7789_RS_PORT_PERIPH_CLK,
    .rs_pin.p_gpio_port             = ST7789_RS_PORT,
    .rs_pin.gpio_dir                = GPIO_DIR_OUTPUR,
    .rs_pin.gpio_pin                = ST7789_RS_PIN,

    .wr_pin.gpio_port_periph_clk    = ST7789_WR_PORT_PERIPH_CLK,
    .wr_pin.p_gpio_port             = ST7789_WR_PORT,
    .wr_pin.gpio_dir                = GPIO_DIR_OUTPUR,
    .wr_pin.gpio_pin                = ST7789_WR_PIN,

    .rd_pin.gpio_port_periph_clk    = ST7789_RD_PORT_PERIPH_CLK,
    .rd_pin.p_gpio_port             = ST7789_RD_PORT,
    .rd_pin.gpio_dir                = GPIO_DIR_OUTPUR,
    .rd_pin.gpio_pin                = ST7789_RD_PIN,

    // DB0--PB12, DB1--PB13, DB2--PB14, DB3--PB15, DB4--PC6, DB5--PC7, DB6--PC8, DB7--PC9
    .db0.gpio_port_periph_clk    = ST7789_DB0_PORT_PERIPH_CLK,
    .db0.p_gpio_port             = ST7789_DB0_PORT,
    .db0.gpio_dir                = GPIO_DIR_OUTPUR,
    .db0.gpio_pin                = ST7789_DB0_PIN,

    .db1.gpio_port_periph_clk    = ST7789_DB1_PORT_PERIPH_CLK,
    .db1.p_gpio_port             = ST7789_DB1_PORT,
    .db1.gpio_dir                = GPIO_DIR_OUTPUR,
    .db1.gpio_pin                = ST7789_DB1_PIN,

    .db2.gpio_port_periph_clk    = ST7789_DB2_PORT_PERIPH_CLK,
    .db2.p_gpio_port             = ST7789_DB2_PORT,
    .db2.gpio_dir                = GPIO_DIR_OUTPUR,
    .db2.gpio_pin                = ST7789_DB2_PIN,

    .db3.gpio_port_periph_clk    = ST7789_DB3_PORT_PERIPH_CLK,
    .db3.p_gpio_port             = ST7789_DB3_PORT,
    .db3.gpio_dir                = GPIO_DIR_OUTPUR,
    .db3.gpio_pin                = ST7789_DB3_PIN,

    .db4.gpio_port_periph_clk    = ST7789_DB4_PORT_PERIPH_CLK,
    .db4.p_gpio_port             = ST7789_DB4_PORT,
    .db4.gpio_dir                = GPIO_DIR_OUTPUR,
    .db4.gpio_pin                = ST7789_DB4_PIN,

    .db5.gpio_port_periph_clk    = ST7789_DB5_PORT_PERIPH_CLK,
    .db5.p_gpio_port             = ST7789_DB5_PORT,
    .db5.gpio_dir                = GPIO_DIR_OUTPUR,
    .db5.gpio_pin                = ST7789_DB5_PIN,

    .db6.gpio_port_periph_clk    = ST7789_DB6_PORT_PERIPH_CLK,
    .db6.p_gpio_port             = ST7789_DB6_PORT,
    .db6.gpio_dir                = GPIO_DIR_OUTPUR,
    .db6.gpio_pin                = ST7789_DB6_PIN,

    .db7.gpio_port_periph_clk    = ST7789_DB7_PORT_PERIPH_CLK,
    .db7.p_gpio_port             = ST7789_DB7_PORT,
    .db7.gpio_dir                = GPIO_DIR_OUTPUR,
    .db7.gpio_pin                = ST7789_DB7_PIN,
};  

// lcd屏幕参数
static lcd_dev_t    m_lcd_obj = 
{
    .width      =   320,
    .height     =   240,
    .id         =   0,
    .dir        =   0,
    .wramcmd    =   0x2C,
    .setxcmd    =   0x2A,
    .setycmd    =   0x2B,
};

static driver_info_t m_tftlcd_display_obj = 
{
    .dev                =   &m_st7789_obj,
    .lcd_param          =   &m_lcd_obj,
    .write_cmd          =   st7789_write_cmd,
    .write_data         =   st7789_write_data,
    .write_burst_data   =   st7789_write_burst_data,
    .point_color        =   RED,
    .background_color   =   BLACK,
};

void tft_lcd_init(void)
{
    st7789_init(&m_tftlcd_display_obj);
}

void Display_UI1(void)
{
    // 320*240
    // AC VOLTAGE  INPUT MODE
    m_tftlcd_display_obj.point_color = YELLOW;
    LCD_ShowString(&m_tftlcd_display_obj, 60, 10, 320, 16, 16, "AC VOLTAGE   INPUT MODE");
    // 200V~240V
    m_tftlcd_display_obj.point_color = RED;
	LCD_ShowString(&m_tftlcd_display_obj, 65, 35, 320, 16, 16, "200V~240V");
	// PARALLEL
    m_tftlcd_display_obj.point_color = GBLUE;
	LCD_ShowString(&m_tftlcd_display_obj, 170, 35, 320, 16, 16, "PARALLEL");

	// CH1
    m_tftlcd_display_obj.point_color = GREEN;
    LCD_ShowString(&m_tftlcd_display_obj, 15, 82, 320, 16, 16, "ANG1");
    LCD_DrawRectangle(&m_tftlcd_display_obj, 10, 75, 50, 105, 3, GREEN);

	//画线
    LCD_DrawLine(&m_tftlcd_display_obj, 50, 88, 68, 88, 3, GREEN);
    LCD_DrawLine(&m_tftlcd_display_obj, 75, 88, 82, 88, 3, GREEN);
    // 68dB
    LCD_ShowString(&m_tftlcd_display_obj, 85, 82, 320, 16, 16, "68dB");
    LCD_DrawRectangle(&m_tftlcd_display_obj, RECT_X_START, 75, RECT_X_END, 105, RECT_LINE_WIDTH, GREEN);
    LCD_DrawRectangle(&m_tftlcd_display_obj, 280, 75, 315, 105, RECT_LINE_WIDTH, GREEN);
    LCD_ShowString(&m_tftlcd_display_obj, 288, 82, 320, 16, 16, "CH1");    

    // CH2
    m_tftlcd_display_obj.point_color = BLUE;
    LCD_DrawLine(&m_tftlcd_display_obj, 60, 91, 60, 140, 3, BLUE);
    LCD_DrawLine(&m_tftlcd_display_obj, 60, 140, 68, 140, 3, BLUE);
    LCD_DrawLine(&m_tftlcd_display_obj, 75, 140, 82, 140, 3, BLUE);
    // 65dB
    LCD_ShowString(&m_tftlcd_display_obj, 85, 133, 320, 16, 16, "65dB");
    LCD_DrawRectangle(&m_tftlcd_display_obj, RECT_X_START, 125, RECT_X_END, 155, RECT_LINE_WIDTH, BLUE);
    LCD_DrawRectangle(&m_tftlcd_display_obj, 280, 125, 315, 155, RECT_LINE_WIDTH, BLUE);
    LCD_ShowString(&m_tftlcd_display_obj, 288, 133, 320, 16, 16, "CH2");

    // 温度显示
    m_tftlcd_display_obj.point_color = WHITE;
    LCD_ShowString(&m_tftlcd_display_obj, 60, 218, 320, 16, 16, "TEMP:");
    m_tftlcd_display_obj.point_color = GREEN;
    LCD_ShowString(&m_tftlcd_display_obj, 120, 218, 320, 16, 16, "28");
    LCD_ShowBMP(&m_tftlcd_display_obj, 138, 218, (sizeof(gImage_dot)/sizeof(gImage_dot[0])), 20, gImage_dot, GREEN);
    LCD_ShowString(&m_tftlcd_display_obj, 160, 218, 320, 16, 16, "C");

    // 风扇标志
    LCD_ShowBMP(&m_tftlcd_display_obj, 180, 210, (sizeof(gImage_fan)/sizeof(gImage_fan[0])), 30, gImage_fan, GREEN);

    // 温度标记条
    LCD_DrawTriangle(&m_tftlcd_display_obj, 220, 230, 60, 25, 3, GREEN);
    LCD_FillTriangle(&m_tftlcd_display_obj, 220, 230, 60, 25, 0, GREEN);
}



void Display_Dynamic(void)
{
    uint8_t rate[] = {30, 34, 38, 42, 50, 46, 42, 38, 42, 46, 50, 42, 36, 30};
    uint16_t coord_x1 = 0;
	uint16_t coord_x2 = 0;
    uint8_t i = 0;

    while (1)
    {
        LCD_FillRectanglePercent(&m_tftlcd_display_obj, 120, 75, 275, 105, GREEN, rate[i], &coord_x1);
		i++;
		if (i >= (sizeof(rate)/sizeof(rate[0])))
		{
			i = 0;
		}
		delay_ms(50);
    }
}
