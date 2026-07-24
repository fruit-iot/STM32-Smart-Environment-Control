#include "stm32f10x.h"
#include "Delay.h"

/*
 *  Rotary encoder pin mapping:
 *    PB12 - CLK (A phase) - external interrupt, falling edge
 *    PB13 - DT  (B phase) - read in ISR to determine direction
 *    PB14 - SW  (button)  - polled
 */

static volatile int16_t encoder_count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line    = EXTI_Line12;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);
}

int16_t Encoder_GetCount(void)
{
	return encoder_count;
}

void Encoder_ResetCount(void)
{
	encoder_count = 0;
}

uint8_t Encoder_GetButton(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0);
			Delay_ms(20);
			return 1;
		}
	}
	return 0;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
				encoder_count--;
			else
				encoder_count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}
