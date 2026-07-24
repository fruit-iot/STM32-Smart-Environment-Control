#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

void Encoder_Init(void);
int16_t Encoder_GetCount(void);
void Encoder_ResetCount(void);
uint8_t Encoder_GetButton(void);

#endif
