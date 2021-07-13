#include "delay.h"

static u8 fac_us = 0;  // us延时倍乘数
static u16 fac_ms = 0; // ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //选择外部时钟  HCLK/8
    fac_us = SystemCoreClock / 8000000;                   //为系统时钟的1/8
    fac_ms = (u16)fac_us * 1000;                          //非OS下,代表每个ms需要的systick时钟数
}

void delay_us(u32 nus)
{
    SysTick->LOAD = nus * fac_us - 1;         //时间加载
    SysTick->VAL = 0x00;                      //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数

    while (!((SysTick->CTRL) & (1 << 16)))
        ;
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数器
    SysTick->VAL = 0X00;                       //清空计数器
}
void delay_ms(u16 nms)
{
    SysTick->LOAD = (u32)nms * fac_ms - 1;    //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;                      //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数

    while (!((SysTick->CTRL) & (1 << 16)))
        ;

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数器
    SysTick->VAL = 0X00;                       //清空计数器
}
