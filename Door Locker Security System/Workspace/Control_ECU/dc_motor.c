 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "gpio.h" /* To use the GPIO Functions */
#include "pwm.h" /* To use the PWM Function */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)
{
	/*
	 * The Function responsible for setup the direction for the two
	 * motor pins through the GPIO driver.
	 */
	GPIO_SetPinDirection(MOTOR_PORT_ID,MOTOR_PIN1_ID,PIN_OUTPUT);
	GPIO_SetPinDirection(MOTOR_PORT_ID,MOTOR_PIN2_ID,PIN_OUTPUT);

	/*Stop at the DC-Motor at the beginning*/
	DcMotor_Rotate(STOP,0);
}


void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* Calculating the speed of motor through the PWM function */
	PWM_Timer0_Start(speed);

	switch(state){
	case STOP:
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_LOW);
		break;
	case CW:
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_HIGH);
		break;
	case CCW:
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_HIGH);
		GPIO_WritePin(MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_LOW);
		break;
	}

}
