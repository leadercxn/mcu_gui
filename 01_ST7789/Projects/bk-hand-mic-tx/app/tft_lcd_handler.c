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
    .wramcmd    =   CMD_WRAM,
    .setxcmd    =   CMD_SETX,
    .setycmd    =   CMD_SETY,
};

static driver_info_t m_tftlcd_display_obj = 
{
    .dev                =   &m_st7789_obj,
    .lcd_param          =   &m_lcd_obj,
    .write_cmd          =   st7789_write_cmd,
    .write_data         =   st7789_write_data,
    .write_burst_data   =   st7789_write_burst_data,
    .point_color        =   RED,
    .background_color   =   WHITE,
};

void tft_lcd_init(void)
{
    st7789_init(&m_tftlcd_display_obj);
}

