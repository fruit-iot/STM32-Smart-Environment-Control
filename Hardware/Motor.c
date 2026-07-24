#include "stm32f10x.h"
#include "PWM.h"

extern int temperature_threshold;

static uint8_t motor_speed = 50;

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	PWM_Init();
}

void Motor_SetSpeed(uint8_t speed)
{
	if (speed > 100) speed = 100;
	motor_speed = speed;
}

uint8_t Motor_GetSpeed(void)
{
	return motor_speed;
}

void Motor_Start(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void Motor_Stop(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
}

void Motor_Control(float temp)
{
	if (temp > temperature_threshold)
	{
		Motor_Start();
		PWM_SetCompare3(motor_speed);
	}
	else
	{
		Motor_Stop();
		PWM_SetCompare3(0);
	}
}
