 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* The maximum number the timer can count
 * It should be 255 in case of 8-bit timer and 65535 in case of 16-bit timer */

#define TIMER_MAX_COUNT 		255

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*The function responsible for trigger the Timer0 with the PWM Mode.*/
void PWM_Timer0_Start(uint8 set_duty_cycle);

#endif /* PWM_H_ */
