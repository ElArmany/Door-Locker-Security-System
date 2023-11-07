 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: eeprom.h
 *
 * Description: Header file for the External EEPROM driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_WriteByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_ReadByte(uint16 u16addr,uint8 *u8data);


#endif /* EEPROM_H_ */
