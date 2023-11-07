 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Buzzer_init()
{
	GPIO_SetPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_WritePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

void Buzzer_ON(void)
{
	GPIO_WritePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void Buzzer_OFF(void)
{
	GPIO_WritePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
