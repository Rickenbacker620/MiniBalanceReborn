#include "timer.h"

void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	//使能或者失能指定的TIM中断  //使能
	TIM_ITConfig( TIM6, TIM_IT_Update ,ENABLE );
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设
							 
}

/**************************************************************************
函数功能：定时器4通道输入捕获初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void TIM4_Cap_Init(u16 arr,u16 psc)	
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能GPIO时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA  输入  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//初始化定时器4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM4输入捕获参数
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择输入端 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
		//初始化TIM4输入捕获参数
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择输入端 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 	
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许捕获中断	
  TIM_Cmd(TIM4,ENABLE ); 	//使能定时器
}

/**************************************************************************
函数功能：定时器5通道输入捕获初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void TIM5_Cap_Init(u16 arr,u16 psc)	
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);  //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA  输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_4;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//初始化定时器5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择输入端 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
		//初始化TIM5输入捕获参数
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择输入端 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许捕获中断	
  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器
}
u16 TIM5CH1_CAPTURE_STA,TIM5CH1_CAPTURE_VAL,TIM5CH2_CAPTURE_STA,TIM5CH2_CAPTURE_VAL;
u16 TIM4CH1_CAPTURE_STA,TIM4CH1_CAPTURE_VAL,TIM4CH2_CAPTURE_STA,TIM4CH2_CAPTURE_VAL;




