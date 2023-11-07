 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the Timer driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	NO_CLOCK,NO_PRESCALER,PRESCALER_8,PRESCALER_64,PRESCALER_256,PRESCALER_1024,EXT_CLOCK_FALLING,EXT_CLOCK_RISING
}Timer1_Prescaler;

typedef enum{
	NORMAL_MODE,COMPARE_MODE
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;       // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/* Description:
 * Function to disable the Timer
 */
void Timer1_deInit(void);

/* Description:
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
