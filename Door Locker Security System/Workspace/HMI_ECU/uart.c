 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "uart.h"
#include "common_macros.h"
#include "avr/io.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value=0;

	/* U2X = 1 for double transmission speed */
	UCSRA |= (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * Configurable bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRB = (UCSRB & 0xFB) | ((Config_Ptr->bit_data) & 4);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = - Configurable parity bit
	 * USBS    = - Configurable number of stop bits
	 * UCSZ1:0 = - Configurable bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL);
	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->parity)   << UPM0 );
	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->stop_bit) << USBS  );
	UCSRC = (UCSRC & 0xF9) | (((Config_Ptr->bit_data) & 3) << UCSZ0 );

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (8UL * Config_Ptr->baud_rate)))-1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = (ubrr_value>>8);
	UBRRL = ubrr_value;
}

void UART_SendByte(uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while (BIT_IS_CLEAR(UCSRA,UDRE));

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}

uint8 UART_ReceiveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA,RXC));

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

void UART_SendString(uint8 *string)
{
	uint8 i=0;

	/* Send the whole string */
	while(string[i] != '\0'){
		UART_SendByte(string[i]);
		i++;
	}
}

void UART_ReceiveString (uint8 *string)
{
	uint8 i=0;

	/* Receive the first byte */
	string[i] = UART_ReceiveByte();

	/* Receive the whole string until the '#' */
	while (string[i] != '#'){
		i++;
		string[i]= UART_ReceiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	string[i] = '\0';
}
