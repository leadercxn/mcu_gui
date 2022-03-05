# mid_tftlcd

## 1. 说明
1. mid_tftlcd抽象了对TFT LCD屏的通用操作，如清屏、画图形、显示字符串等
2. 对LCD的通用操作中都需要给底层芯片发送命令，而这些命令则抽象到结构体`driver_info_t`中


## 1. 数据结构设计
1. `driver_info_t`结构体设计
   1. 发送命令操作: write_cmd, write_data, write_burst_data
   2. lcd参数结构体: lcd_dev_t --> 清屏操作需要用到屏幕参数
   3. 驱动芯片参数: 读写操作需要用到驱动参数结构体
   4. 笔画颜色参数
2. `driver_info_t`的初始化
   1. mid_tftlcd.h由底层驱动函数包含
   2. `driver_info_t`的实例化由app通过底层函数，传递到最底层的`tftlcd`中


