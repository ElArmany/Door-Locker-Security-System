 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "gpio.h"
#include "keypad.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLUMNS == 3)

static uint8 KEYPAD_4x3_AdjustKeyNumber(uint8 button_number);

#elif (KEYPAD_NUM_COLUMNS == 4)

static uint8 KEYPAD_4x4_AdjustKeyNumber(uint8 button_number);

#endif

#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 KEYPAD_GetPressedKey(void)
{
	uint8 col,row;
	GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID ,PIN_INPUT);
	GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+1 ,PIN_INPUT);
	GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+2 ,PIN_INPUT);
	GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+3 ,PIN_INPUT);

	GPIO_SetPinDirection(KEYPAD_COLUMN_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID ,PIN_INPUT);
	GPIO_SetPinDirection(KEYPAD_COLUMN_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID+1 ,PIN_INPUT);
	GPIO_SetPinDirection(KEYPAD_COLUMN_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID+2 ,PIN_INPUT);

#if (KEYPAD_NUM_COLUMNS == 4)
	GPIO_SetPinDirection(KEYPAD_COLUMN_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID+3 ,PIN_INPUT);
#endif

	while(1)
	{
		for (row = 0 ; row < KEYPAD_NUM_ROWS ; row ++)
		{
			GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+row ,PIN_OUTPUT);
			GPIO_WritePin(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+row , KEYPAD_BUTTON_PRESSED);

			for (col = 0 ; col < KEYPAD_NUM_COLUMNS ; col++)
			{
				if (GPIO_ReadPin(KEYPAD_COLUMN_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+col) == KEYPAD_BUTTON_PRESSED )
				{

					#if (KEYPAD_NUM_COLUMNS ==3)
						#ifdef STANDARD_KEYPAD
					return ((row*KEYPAD_NUM_COLUMNS)+col+1);
						#else
					return KEYPAD_4x3_AdjustKeyNumber((row*KEYPAD_NUM_COLUMNS)+col+1);
#endif
					#elif (KEYPAD_NUM_COLUMNS == 4)
						#ifdef STANDARD_KEYPAD
					return ((row*KEYPAD_NUM_COLUMNS)+col+1);
						#else
					return KEYPAD_4x4_AdjustKeyNumber((row*KEYPAD_NUM_COLUMNS)+col+1);
					#endif
				#endif
				}

			}
			GPIO_SetPinDirection(KEYPAD_ROW_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+row ,PIN_INPUT);
			_delay_ms(5);
		}

	}

}


#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLUMNS == 3)

static uint8 KEYPAD_4x3_AdjustKeyNumber(uint8 button_number)
{
	uint8 correct_num = 0;
	switch (button_number){
	case 10 :
		correct_num = '*';
		break;
	case 11 :
		correct_num = 0;
		break;
	case 12 :
		correct_num = '#';
		break;
	}
	return correct_num;
}

#elif (KEYPAD_NUM_COLUMNS ==4)

static uint8 KEYPAD_4x4_AdjustKeyNumber(uint8 button_number)
{
	uint8 correct_num =0;
	switch(button_number){
	case 1 : correct_num = 7;
	break;
	case 2 : correct_num = 8;
	break;
	case 3 : correct_num = 9;
	break;
	case 4 : correct_num = '/';
	break;
	case 5 : correct_num = 4;
	break;
	case 6 : correct_num = 5;
	break;
	case 7 : correct_num = 6;
	break;
	case 8 : correct_num = '*';
	break;
	case 9 : correct_num = 1;
	break;
	case 10 : correct_num = 2;
	break;
	case 11 : correct_num = 3;
	break;
	case 12 : correct_num = '-';
	break;
	case 13 : correct_num = 13;
	break;
	case 14 : correct_num = 0;
	break;
	case 15 : correct_num = '=';
	break;
	case 16 : correct_num = '+';
	break;
	default : correct_num = button_number;
	break;
	}
	return correct_num;
}

#endif

#endif
