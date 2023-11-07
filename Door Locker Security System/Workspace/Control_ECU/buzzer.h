 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT PORTD_ID
#define BUZZER_PIN  PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Buzzer_init(void);

void Buzzer_ON(void);

void Buzzer_OFF(void);



#endif /* BUZZER_H_ */
