#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor_Start(void);
void Motor_Stop(void);
void Motor_Control(float temp);
void Motor_SetSpeed(uint8_t speed);
uint8_t Motor_GetSpeed(void);

#endif