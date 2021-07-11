#include "timer.h"

void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	//ʹ�ܻ���ʧ��ָ����TIM�ж�  //ʹ��
	TIM_ITConfig( TIM6, TIM_IT_Update ,ENABLE );
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����
							 
}

/**************************************************************************
�������ܣ���ʱ��4ͨ�����벶���ʼ��
��ڲ�������ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/
void TIM4_Cap_Init(u16 arr,u16 psc)	
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA  ����  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //��� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//��ʼ����ʱ��4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM4���벶�����
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //ѡ������� 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
		//��ʼ��TIM4���벶�����
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //ѡ������� 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 	
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2,ENABLE);//��������ж� ,�������ж�	
  TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��
}

/**************************************************************************
�������ܣ���ʱ��5ͨ�����벶���ʼ��
��ڲ�������ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/
void TIM5_Cap_Init(u16 arr,u16 psc)	
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);  //ʹ��GPIOʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA  ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_4;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //��� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//��ʼ����ʱ��5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //ѡ������� 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
		//��ʼ��TIM5���벶�����
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //ѡ������� 
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2,ENABLE);//��������ж� ,�������ж�	
  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��
}
u16 TIM5CH1_CAPTURE_STA,TIM5CH1_CAPTURE_VAL,TIM5CH2_CAPTURE_STA,TIM5CH2_CAPTURE_VAL;
u16 TIM4CH1_CAPTURE_STA,TIM4CH1_CAPTURE_VAL,TIM4CH2_CAPTURE_STA,TIM4CH2_CAPTURE_VAL;




