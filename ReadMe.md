# 项目介绍
## 此src_dma分支介绍

参考csdn博客：https://blog.csdn.net/weixin_45682654/article/details/136244101
已经下载归档在目录（参考/）

## 修改内容

- 新建my_mpu6050.c和my_mpu6050.h文件，实现MPU初始化和数据获取。
- 参考motion_driver_test.c文件流程，修改main.c代码，同时main.h引入相关代码

## 板子验证阶段修改内容
不修改直接返回-9错误即自检失败
改成了csdn_dmp中的my_mpu6050.c/.c还有inv_mpu.c/.h成功下载成功了
就很神奇，所以选择另一个分支csdn_dmp代码成功
## 当前成果
DMP的初步移植工作已完成，能够编译通过。
板子下载成功
## TODO:
1. 在STM32F103C8T6开发板下载验证程序，似乎还需要把inv_mpu.c中的MPU6050设备地址修改为0xD0，否则会找不到设备。
   
