/******************************************************************************
 *
 * Module: Exernal EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: Source file for the External EEPROM driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "eeprom.h"
#include "i2c.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 EEPROM_WriteByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
	TWI_Start();
	if (TWI_GetStatus() != TWI_START){
		return ERROR;
	}

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	* memory location address and R/W=0 (write) */
	TWI_WriteByte((uint8)((0xA0) | ((u16addr & 0x0700) >> 7)));
	if (TWI_GetStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}

	/* Send the required memory location address */
	TWI_WriteByte((uint8)(u16addr));
	if (TWI_GetStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	/* write byte to EEPROM */
	TWI_WriteByte(u8data);
	if (TWI_GetStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	/* Send the Stop Bit */
	TWI_Stop();

	return SUCCESS;
}

uint8 EEPROM_ReadByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
	TWI_Start();
	if (TWI_GetStatus() != TWI_START){
		return ERROR;
	}

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
	TWI_WriteByte((uint8)((0xA0) | ((u16addr & 0x0700) >> 7)));
	if (TWI_GetStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}

	/* Send the required memory location address */
	TWI_WriteByte((uint8)(u16addr));
	if (TWI_GetStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	/* Send the Repeated Start Bit */
	TWI_Start();
	if (TWI_GetStatus() != TWI_REP_START){
		return ERROR;
	}

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
	TWI_WriteByte((uint8)((0xA0) | ((u16addr & 0x0700) >> 7) | 1));
	if (TWI_GetStatus() != TWI_MT_SLA_R_ACK){
		return ERROR;
	}

	/* Read Byte from Memory without send ACK */
	*u8data = TWI_ReadByteWithNACK();
    if (TWI_GetStatus() != TWI_MR_DATA_NACK){
        return ERROR;
    }

    /* Send the Stop Bit */
    TWI_Stop();

    return SUCCESS;
}
