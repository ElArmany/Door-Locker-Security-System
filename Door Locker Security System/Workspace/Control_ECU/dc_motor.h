 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Motor's HW Ports and Pins ID'S */
#define MOTOR_PORT_ID   	PORTA_ID
#define MOTOR_PIN1_ID   	PIN0_ID
#define MOTOR_PIN2_ID   	PIN1_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
	CW,CCW,STOP
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * Function responsible for initialize the DC Motor driver. */
void DcMotor_Init(void);

/* Description :
 * Function responsible for determining the state of the motor
 * either to stop or rotate clockwise or anti-clockwise
 * and the required percentage speed of the motor */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
