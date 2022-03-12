# IR

## 麦克风IR对频协议
* 不采用标准的 NEC 协议

* 自定义帧
    帧头 + 命令码CMD 1B + 数据字节数长度LEN 1B + 数据DATA NB(目前N = 4) + CRC 1B + 结束符

    1. 帧头
        5ms 低电平 + 5ms 高电平

    2. bit '0':
            2ms 低电平 + 1ms 高电平
    3. bit '1':
            2ms 低电平 + 2ms 高电平

    4. 命令码对应数据含义
        | command | data |
        |---------|------|
        |   0x01  | freq |
        |   0x02  |  vol |
        |   0x03  | tx_p |

    5. 红外采用 LSB
    6. 结束符 5ms的低电平
    7. CRC = SUM(DATAs)

    8. 不同 command 的数据结构
        - freq: 0x01
            ```
                typedef struct
                {
                    uint8_t len;
                    uint8_t band_type;
                    uint8_t region_band;
                    uint8_t freq_ch;
                } __attribute__((__packed__ )) ir_command_freq_t;
            ```

