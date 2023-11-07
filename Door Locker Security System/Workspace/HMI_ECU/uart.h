 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_BitData;

typedef enum{
	NO_PARITY,RESERVED,EVEN_PARITY,ODD_PARITY
}UART_Parity;

typedef enum{
	ONE_STOP_BIT,TWO_STOP_BITS
}UART_StopBit;

typedef uint32 UART_BaudRate;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_SendByte(uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_ReceiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_SendString(uint8 *string);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_ReceiveString (uint8 *string);


#endif /* UART_H_ */
