 /******************************************************************************
 *
 * Module: Control ECU
 *
 * File Name: Control_ECU.h
 *
 * Description: Header file for the Control application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_


#include "uart.h"
#include "buzzer.h"
#include "eeprom.h"
#include "dc_motor.h"
#include "i2c.h"
#include "timer.h"
#include <util/delay.h>
#include <avr/io.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_SIZE 5

#define FIRST_TIME_PASSWORD 10
#define CHANGE_PASSWORD 20
#define PASSWORD_CHECK 30
#define OPEN_DOOR 40
#define WRONG_PASS 50

#define MATCHED 1
#define NOT_MATCHED 0

#define SLAVE_ADDRESS 0x0004

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description:
 * The callback function called by the timer driver
 */
void Timer1_Tick();

/* Description:
 * Receives the two passwords entered from the user and check if they are
 * similar, if they are matched set this password as the system's password
 * and save it in the EEPROM
 */
void SetNewPassword();

/* Description:
 * Compares the entered password with the password saved in the EEPROM
 */
void VerifyPassword();

/* Description:
 * Saves the system's password in the EEPROM
 */
void Save_Password(uint8* password);

/* Description:
 * Get the password saved in the EEPROM to compare
 */
void Check_Saved_Password(uint8* password);

/* Description:
 * Function to manage the door operations
 */
void Door_Opening();

/* Description:
 * Function the enables the buzzer in case password has been entered
 * wrong for 3 consecutive times
 */
void Wrong_Password();

#endif /* CONTROL_ECU_H_ */
