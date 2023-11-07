 /******************************************************************************
 *
 * Module: I2C (TWI)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C(TWI) driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef uint8 TWI_Address;

typedef uint32 TWI_BaudRate;

typedef struct{
 TWI_Address address;
 TWI_BaudRate bit_rate;
}TWI_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void TWI_init(const TWI_ConfigType * Config_Ptr);

void TWI_Start(void);

void TWI_Stop(void);

void TWI_WriteByte(uint8 data);

uint8 TWI_ReadByteWithACK(void);

uint8 TWI_ReadByteWithNACK(void);

uint8 TWI_GetStatus(void);

#endif /* I2C_H_ */
