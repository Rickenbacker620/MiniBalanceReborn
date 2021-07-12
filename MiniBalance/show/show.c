#include "show.h"

unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
						int accz;
void oled_show(void)
{
												
					//=============第3行显示左电机的状态=======================//	
						if( Target_Left<0)		  OLED_ShowString(00,20,"-"),
																OLED_ShowNumber(15,20,-Target_Left,5,12);
					else                 	OLED_ShowString(0,20,"+"),
																OLED_ShowNumber(15,20, Target_Left,5,12); 			
					if( Encoder_Left<0)		  OLED_ShowString(80,20,"-"),
																OLED_ShowNumber(95,20,-Encoder_Left,4,12);
					else                 	OLED_ShowString(80,20,"+"),
																OLED_ShowNumber(95,20, Encoder_Left,4,12);
					//=============第4行显示右电机的状态=======================//	
						if( Target_Right<0)		  OLED_ShowString(00,30,"-"),
																OLED_ShowNumber(15,30,-Target_Right,5,12);
					else                 	OLED_ShowString(0,30,"+"),
																OLED_ShowNumber(15,30, Target_Right,5,12); 					
					if( Encoder_Right<0)		  OLED_ShowString(80,30,"-"),
																OLED_ShowNumber(95,30,-Encoder_Right,4,12);
					else                 	OLED_ShowString(80,30,"+"),
																OLED_ShowNumber(95,30, Encoder_Right,4,12);	
					
					//=============第5行显示舵机的状态=======================//	
				 	OLED_ShowString(00,40,"Servo:"),	//舵机状态
					OLED_ShowNumber(60,40, Servo,4,12);	
					//=============第6行显示电压模式等=======================//	
                       //  电机使能/使能显示
											if(Flag_Stop==0)//根据Flag_Stop标志位显示电机的状态
											OLED_ShowString(103,50,"O-N");
											if(Flag_Stop==1)
											OLED_ShowString(103,50,"OFF");

                      OLED_ShowString(0,50,"PS2"); //遥控模式
											OLED_Refresh_Gram();	//刷新
}


