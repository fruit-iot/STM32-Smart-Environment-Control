#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "FMQ.h"
#include "Serial.h"
#include "Key.h"
#include "Motor.h"
#include "threshold.h"
#include "Encoder.h"


uint8_t KeyNum;
u8 temp,humi;
int16_t last_encoder;
int16_t fan_speed = 50;
extern int temperature_threshold;


int main(void)
{    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);//led写这了//




	 uint32_t bufe[5];
	 OLED_Init();
	 DHT11_Init();
	 mfq_Init();
	 Serial_Init();
	 Key_Init();
	 Motor_Init();
	 Encoder_Init();


	OLED_ShowChinese(0, 0, "温度：");
	OLED_ShowChinese(94, 0, "℃");
	OLED_ShowChinese(0, 16, "阈值：");
	OLED_ShowChinese(94,16, "℃");
	OLED_ShowChinese(0, 32, "转速：");
	OLED_ShowChinese(94, 32, "%");



	OLED_Update();

	while(1)
	{   if(temp>temperature_threshold )
		{
			 GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		     Delay_ms(50);
		     GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		     Delay_ms(50);
        }
		else
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}






		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			temperature_threshold += 5;
			if (temperature_threshold>50 )
			{
				temperature_threshold=0 ;
			}
		}

		// Rotary encoder speed control
		{
			int16_t enc_val = Encoder_GetCount();
			if (enc_val != last_encoder)
			{
				fan_speed += (enc_val - last_encoder) * 5;
				if (fan_speed > 100) fan_speed = 100;
				if (fan_speed < 0)   fan_speed = 0;
				Motor_SetSpeed((uint8_t)fan_speed);
				last_encoder = enc_val;
			}
		}

		// Encoder button cycles speed: 0 -> 50 -> 100 -> 0
		if (Encoder_GetButton())
		{
			if      (fan_speed == 0)   fan_speed = 50;
			else if (fan_speed == 50)  fan_speed = 100;
			else                        fan_speed = 0;
			Motor_SetSpeed((uint8_t)fan_speed);
			Encoder_ResetCount();
			last_encoder = 0;
		}

		Motor_Control(temp);



		DHT11_Read_Data(&temp,&humi);
	    bufe[0]=temp;
		bufe[1]=humi;



		OLED_ShowNum(47,0,bufe[0],2,OLED_8X16);
		OLED_ShowNum(47, 16, temperature_threshold, 2, OLED_8X16);
		OLED_ShowNum(47, 32, (uint8_t)fan_speed, 3, OLED_8X16);
		OLED_Update();
		fmq(temp,humi);

		 printf("temp=%d  , Threshold = %d  , Speed = %d%%\r\n",temp,temperature_threshold,(uint8_t)fan_speed);

	}
}
