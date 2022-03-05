#ifndef __BK9532_H
#define __BK9532_H

typedef struct
{
    uint8_t  reg;
    uint32_t value;
} bk953x_reg_value_t;

/**
 * BK953X GPIO4 作为静音输出IO
 */
#define  BK953X_GPIO4_MUTE_FUN

typedef enum
{
    BK953X_SAMPLE_RATE_48K,
    BK953X_SAMPLE_RATE_32K,
    BK953X_SAMPLE_RATE_24K,
    BK953X_SAMPLE_RATE_12K,
} bk953x_sample_rate_e;

typedef enum
{
    BK953X_BAND_V,  //V段
    BK953X_BAND_U   //U段
} bk953x_band_type_e;

typedef enum
{
    SA_ANT1_PIN6 = 0,                   //使用PIN6作为天线输入口    2020-05-26
    SA_ANT2_PIN5,                       //使用PIN5作为天线输入口    2020-05-26
    DA_AUTO,                            //自动天线模式
} antenna_type_e;

typedef enum
{
    ADPCM_NORMAL = 0,                   //PLC常规处理
    ADPCM_ZERO,                         //PLC补0处理 
} adpcm_mode_e;

typedef struct
{
    bk953x_band_type_e  band_type;
    uint16_t            chan_index;
    uint32_t            freq;
    uint32_t            reg_value;
} freq_chan_object_t;


/**
 * I2S 相关配置
 */
typedef enum
{
    PCM_SLAVE = 0,
    PCM_MASTER,
} bk953x_pcm_mode_e;

typedef enum
{
    PCM_SDA_O = 0,
    PCM_SDA_I = 4,
} bk953x_pcm_data_cfg_e;

typedef enum
{
    PCM_SCK_O = 0,
    PCM_SCK_I = 4,
} bk953x_pcm_bclk_cfg_e;

typedef enum
{
    PCM_LRCK_O = 0,
    PCM_LRCK_I = 4,
} bk953x_pcm_lrclk_cfg_e;

typedef enum
{
    PCM_LEFT = 0,       //左声道（LRCK=0时输出音频数据）
    PCM_RIGHT,          //右声道（LRCK=1时输出音频数据）
    PCM_MONO,           //单声道（在LRCK高电平和低电平期间均输出音频数据）
} bk953x_pcm_channel_cfg_e;

typedef struct
{
    bk953x_pcm_mode_e           mode;
    bk953x_pcm_data_cfg_e       data;
    bk953x_pcm_bclk_cfg_e       bclk;
    bk953x_pcm_lrclk_cfg_e      lrclk;
    bk953x_pcm_channel_cfg_e    channel;
} bk953x_pcm_config_t;


typedef void (*bk953x_hw_reset_handler) (void);

typedef struct 
{
    uint16_t                    chip_id;
    uint8_t                     device_id;
    bk953x_band_type_e          band_type;
    antenna_type_e              antenna_type;
    uint16_t                    freq_chan_index;
    mid_bk953x_t                mid_bk953x_object;
    bk953x_hw_reset_handler     hw_reset_handler;
} bk953x_object_t;


#define BK9532_CHID_ID      0x9532

#define REG_CHIP_ID 0x70

#endif
