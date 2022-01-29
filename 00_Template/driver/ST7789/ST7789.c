#include "ST7789.h"

_lcd_dev lcddev;


/**
 * @brief  获取lcd设备信息
 * 
 * @param[i] void
 * 
 * @retval no return
 */
_lcd_dev GetLCDDev(void)
{
    return lcddev;
}


/**
 * @brief  FT32对ST7789 DB line的IO初始化
 *          DB0--PB12, DB1--PB13, DB2--PB14, DB3--PB15, DB4--PC6, DB5--PC7, DB6--PC8, DB7--PC9
 * 
 * @param[i] dir
 * 
 * @retval no return
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


/**
 * @brief  所有GPIO初始化
 *          CS--PC0, RESET--PC1, RS--PC2, WR--PC3, RD--PC4
 * 
 * @param[i] dir
 * 
 * @retval no return
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


/**
 * @brief  发送原始数据
 *          DB0--PB12, DB1--PB13, DB2--PB14, DB3--PB15, DB4--PC6, DB5--PC7, DB6--PC8, DB7--PC9
 * 
 * @param[i] cmd    原始数据
 * 
 * @retval no return
 */
void Send_RawData(uint8_t cmd)
{
    GPIOB->BSRR &= ~(0x0f << 12);
    GPIOB->BRR  &= ~(0x0f << 12);
    GPIOC->BSRR &= ~(0x0f << 6);
    GPIOC->BRR  &= ~(0x0f << 6);

    uint8_t tmp1  = (cmd & 0x0f);
    uint8_t tmp2  = (~(cmd & 0x0f) & 0x0f);
    GPIOB->BSRR  |= ((tmp1) << 12);
    GPIOB->BRR   |= ((tmp2) << 12);

    tmp1 = ((cmd & 0xf0) >> 4);
    tmp2 = ((~(cmd & 0xf0) & 0xf0) >> 4);
    GPIOC->BSRR  |= ((tmp1) << 6);
    GPIOC->BRR   |= ((tmp2) << 6);
}


/**
 * @brief  发送命令
 * 
 * @param[i] cmd    命令
 * 
 * @retval no return
 */
void WriteComm(uint8_t cmd)
{
    CHIPSELECT_ENABLE;
    RS_L_CMD;
    WRITE_LOW;
    Send_RawData(cmd);             
    WRITE_HIGH;
    CHIPSELECT_DISABLE;
}

// 发送数据，实现时序
/**
 * @brief  发送数据
 * 
 * @param[i] data   数据
 * 
 * @retval [description] 
 */
void WriteData(uint8_t data)
{
    CHIPSELECT_ENABLE;
    RS_H_DAT;
    WRITE_LOW;
    Send_RawData(data);
    WRITE_HIGH;
    CHIPSELECT_DISABLE;
}

/**
 * @brief  一次性发送多次数据
 * 
 * @param[i] buff       数据首地址
 * @param[i] count      数据长度
 * 
 * @retval [description] 
 */
void WriteBurstData(unsigned char *buff, uint16_t count)
{
    CHIPSELECT_ENABLE;
    RS_H_DAT;

    for (uint16_t i = 0; i < count; i++)
    {
        WRITE_LOW;
        Send_RawData(buff[i]);
        WRITE_HIGH;
    }
    CHIPSELECT_DISABLE;
}

/**
 * @brief  ST7789屏幕参数设置
 * 
 * @param[i] void
 * 
 * @retval no return
 */
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


