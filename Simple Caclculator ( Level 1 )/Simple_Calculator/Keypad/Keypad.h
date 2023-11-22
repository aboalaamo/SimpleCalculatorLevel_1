/*************************************************************************************
* Module: Keypad Driver																 *
* File Name: Keypad.h															 	 *
* Description: Header file for the Keypad driver									 *
* Author: Mohamed Alaa																 *
**************************************************************************************/

#ifndef DRIVERS_KEYPAD_KEYPAD_H_
#define DRIVERS_KEYPAD_KEYPAD_H_


#define HALF_INPUT_OUTPUT	0xF0
#define HALF_OUTPUT_INPUT	0x0F
#define KEYPAD_ROWS    		4
#define KEYPAD_COLS    		4
#define KEY_BUTTON_PRESSED	LOGIC_LOW /* Because We use Internal Pull Up */
#define DEBOUNCING_TIME		20

/* Functions Prototypes */

void KEYPAD_KeypadInit( uint8 Port_id , uint8 PortMode );

uint8 KEYPAD_GetPressedKeyValue(uint8 Port_id );


#endif /* DRIVERS_KEYPAD_KEYPAD_H_ */
