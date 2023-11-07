 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS 				4
#define NUM_OF_PINS_PER_PORT 		8

#define PORTA_ID 					0
#define PORTB_ID 					1
#define PORTC_ID 					2
#define PORTD_ID 					3

#define PIN0_ID 					0
#define PIN1_ID 					1
#define PIN2_ID 					2
#define PIN3_ID 					3
#define PIN4_ID 					4
#define PIN5_ID						5
#define PIN6_I 						6
#define PIN7_D 						7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_SetPinDirection (uint8 port_num , uint8 pin_num , GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_WritePin (uint8 port_num , uint8 pin_num , uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_ReadPin(uint8 port_num , uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_SetupPortDirection(uint8 port_num , GPIO_PortDirectionType direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_WritePort(uint8 port_num , uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_ReadPort(uint8 port_num);


#endif /* GPIO_H_ */
