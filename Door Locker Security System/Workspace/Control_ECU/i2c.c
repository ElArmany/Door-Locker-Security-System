 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C/TWI driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "i2c.h"
#include <avr/io.h>
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	uint32 twbr_value;

	TWCR = (1 << TWEN); /* enable TWI */

	TWSR = 0; // Prescaler = 1

	twbr_value = ((F_CPU/(2*Config_Ptr->bit_rate)))-8; // The value '8' changes if prescaler is changed

	TWBR = twbr_value;

	TWAR = ((Config_Ptr->address) << TWA0 ); // Slave address of the TWI unit
}

void TWI_Start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_Stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_WriteByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data;

    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_ReadByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR;
}

uint8 TWI_ReadByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	return TWDR;
}

uint8 TWI_GetStatus(void)
{
	uint8 status;

	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;

	return status;
}
