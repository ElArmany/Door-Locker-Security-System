 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include "common_macros.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*CallBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect){
	if (CallBackPtr != NULL_PTR){
		/* Call the Call Back function in the application after the edge is detected */
		CallBackPtr();
	}
}

ISR(TIMER1_COMPB_vect){
	if (CallBackPtr != NULL_PTR){
		/* Call the Call Back function in the application after the edge is detected */
		CallBackPtr();
	}
}

ISR(TIMER1_OVF_vect){
	if (CallBackPtr != NULL_PTR){
		/* Call the Call Back function in the application after the edge is detected */
		CallBackPtr();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
 {
	TCNT1 = Config_Ptr -> initial_value ; /* Set timer1 initial value */

	/* FOC1A=1 FOC1B=1 These bits are only active in case non-pwm mode */
	TCCR1A = (1<< FOC1A) | (1<< FOC1B);

	/* Configurable Prescaler value */
	TCCR1B = (Config_Ptr->prescaler) ;

	if (Config_Ptr -> mode == NORMAL_MODE){
		/*In case of normal(overflow) mode , Enable the overflow interrupt*/
		TIMSK |= (1<<TOIE1);
	}
	else if (Config_Ptr -> mode == COMPARE_MODE){
		OCR1A   = Config_Ptr -> compare_value ; /* Set the compare value */
		TCCR1B |= (1<< WGM12); /*Enable CTC mode*/
		TIMSK  |= (1<<OCIE1A); /*Enable Compare A match interrupt*/
	}

 }

void Timer1_deInit(void)
 {
	/* Clear All Timer1 Registers */
	TCNT1  = 0;
	TCCR1A = 0;
	TCCR1B = 0;

	/* Disable the Input Capture interrupt */
	CLEAR_BIT( TIMSK , OCIE1A );
	CLEAR_BIT( TIMSK , TOIE1  );

 }

void Timer1_setCallBack(void(*a_ptr)(void))
 {
	/* Save the address of the Call back function in a global variable */
	CallBackPtr = a_ptr;
 }
