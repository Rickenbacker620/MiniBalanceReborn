#ifndef __SYS_H
#define __SYS_H
#include <stm32f10x.h>

// 0,不支持ucos
// 1,支持ucos
#define SYSTEM_SUPPORT_UCOS 0 //定义系统文件夹是否支持UCOS

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
// IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 12) // 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12) // 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12) // 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12) // 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12) // 0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8) // 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8) // 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8) // 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8) // 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8) // 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8) // 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8) // 0x40011E08

// IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  //输入

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) //输出
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  //输入

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) //输出
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  //输入

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) //输出
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  //输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) //输出
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) //输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) //输出
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  //输入
/////////////////////////////////////////////////////////////////
// Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6

#define FTIR 1 //下降沿触发
#define RTIR 2 //上升沿触发
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "timer.h"
#include "motor.h"
#include "encoder.h"
#include "show.h"
#include "exti.h"
#include "DataScope_DP.h"
#include "stmflash.h"
#include "spi.h"
#include "24l01.h"
#include "pstwo.h"
#include "usart.h"
// #include "bsp_SysTick.h"
// JTAG模式设置定义
#define JTAG_SWD_DISABLE 0X02
#define SWD_ENABLE 0X01
#define JTAG_SWD_ENABLE 0X00
#define SERVO_INIT 1600
extern u8 Flag_Left, Flag_Right, Flag_Direction, Flag_Way, Flag_Next, operationMode; //蓝牙遥控相关的变量
extern u8 Flag_Stop, Flag_Show;            //停止标志位和 显示标志位 默认停止 显示打开
extern int Encoder_Left, Encoder_Right;    //编码器的脉冲计数
extern long int Motor_Left, Motor_Right;   //电机PWM变量
extern long int Target_Left, Target_Right; //电机目标值
extern int Voltage;                        //电池电压采样相关的变量
extern u8 delay_50, delay_flag;            //延时相关变量
extern u8 Run_Flag;                        //速度或者位置模式指示变量
extern float Velocity, Angle, Servo;
extern u8 rxbuf[8], Urxbuf[8], CAN_ON_Flag, Usart_ON_Flag, Usart_Flag, PID_Send; // CAN和串口控制相关变量
extern u8 txbuf[8], txbuf2[8];                                                   // CAN发送相关变量
extern float Pitch, Roll, Yaw, Gryo_Z;                         //三轴角度 Z轴陀螺仪和XYZ轴目标速度
extern float Position_KP, Position_KI, Position_KD;            //位置控制PID参数
extern float Velocity_KP, Velocity_KI;                         //速度控制PID参数
extern int RC_Velocity;                                        //设置遥控的速度和位置值
extern int PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY, Accel_Key; // PS2相关变量
extern u16 CCD_Zhongzhi, CCD_Yuzhi, ADV[128];                  // CCD相关变量
extern int Sensor_Left, Sensor_Middle, Sensor_Right, Sensor;   //电磁巡线相关
extern int Remoter_Ch1, Remoter_Ch2, Remoter_Ch3, Remoter_Ch4;
extern int Distance_A, Distance_B, Distance_C, Distance_D; //超声波相关变量
extern short gyroX, gyroY, gyroZ;
extern short accelX, accelY, accelZ;
extern short magX, magY, magZ;
extern float Tand;
/////////////////////////////////////////////////////////////////
void Stm32_Clock_Init(u8 PLL);                                                                      //时钟初始化
void Sys_Soft_Reset(void);                                                                          //系统软复位
void Sys_Standby(void);                                                                             //待机模式
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);                                          //设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);                                                    //设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority, u8 NVIC_SubPriority, u8 NVIC_Channel, u8 NVIC_Group); //设置中断
void Ex_NVIC_Config(u8 GPIOx, u8 BITx, u8 TRIM); //外部中断配置函数(只对GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//以下为汇编函数
void WFI_SET(void);      //执行WFI指令
void INTX_DISABLE(void); //关闭所有中断
void INTX_ENABLE(void);  //开启所有中断
void MSR_MSP(u32 addr);  //设置堆栈地址
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
//#include "dmpKey.h"
//#include "dmpmap.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#endif
