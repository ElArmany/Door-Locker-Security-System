 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include <avr/io.h> /* To use the Timer0 Registers */

#include "pwm.h"

#include "gpio.h" /* To use the GPIO functions */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Set Timer Initial Value to 0 */
	TCNT0 = 0;

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	/*Set Compare value*/
	OCR0  = (uint8)(((float32)duty_cycle/100)*(TIMER_MAX_COUNT));

	GPIO_SetPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
}

