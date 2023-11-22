/*************************************************************************************
* Module: Keypad Driver																 *
* File Name: Keypad.c															 	 *
* Description: Source file for Keypad driver										 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


/* Includes */

#include <util/delay.h>
#include "../Library/Std_Types.h"
#include "../GPIO/GPIO.h"
#include "Keypad.h"


static const uint8 KEYPAD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = { {'7', '8', '9', '/'} ,
															{'4', '5', '6', '*'} ,
															{'1', '2', '3', '-'} ,
															{'c', '0', '=', '+'}
														};

static uint8 KeyPadConnectionMode ;

/* Functions Implementation */


/*
 * Description: This function is used to initialize the Keypad Port .
 * Arguments:
	 * Port_Id: port .
	 * PortMode: Mode of Connection of the port .
 * Return Value: no return ( void ) .
 */
void KEYPAD_KeypadInit( uint8 Port_id , uint8 PortMode ){
	/* Check For Mode */
	if( PortMode == HALF_INPUT_OUTPUT || PortMode == HALF_OUTPUT_INPUT ){
		KeyPadConnectionMode = PortMode ;
		GPIO_SetPortDirction(Port_id,PortMode);
		/* Enable Internal Pull Up */
		GPIO_WritePortValue(Port_id,0xff);
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to get pressed key value .
 * Arguments:
	 * Port_Id: port .
	 * PortMode: Mode of Connection of the port .
 * Return Value: return pressed key value .
 */
uint8 KEYPAD_GetPressedKeyValue( uint8 Port_id ) {
	uint8 PortMode = KeyPadConnectionMode;
    uint8 KeyVal = 0xff, flag = 0;

    // Check if PortMode is HALF_INPUT_OUTPUT or HALF_OUTPUT_INPUT
    if(PortMode == HALF_INPUT_OUTPUT || PortMode == HALF_OUTPUT_INPUT){
    	// HALF_INPUT_OUTPUT Mode
        if( PortMode == HALF_INPUT_OUTPUT ){
        	uint8 Col = 0, Row = 0;
            // Loop through the columns
            for( Col = 0 ; Col < KEYPAD_COLS ; ++Col ){
                // Set the current column to low
                GPIO_WritePinValue(Port_id, Col + KEYPAD_COLS, LOGIC_LOW);
                // Loop through the rows
                for( Row = 0 ; Row < KEYPAD_ROWS ; ++Row ){
                    if(GPIO_ReadPinValue(Port_id, Row) == KEY_BUTTON_PRESSED){
                        _delay_ms(DEBOUNCING_TIME);
                        // Check if the button is still pressed after debounce
                        if( GPIO_ReadPinValue(Port_id, Row) == KEY_BUTTON_PRESSED ){
                            KeyVal = KEYPAD_MAP[Row][Col];
                            // Wait until the button is released
                            while( GPIO_ReadPinValue(Port_id, Row) == KEY_BUTTON_PRESSED );
                            flag = 1;
                            break;
                        }
                    }
                }
                // Set the current column back to high
                GPIO_WritePinValue(Port_id, Col + KEYPAD_COLS, LOGIC_HIGH);
                if( flag == LOGIC_HIGH ) {
                    break;
                }
            }
        }
        // HALF_OUTPUT_INPUT Mode
        else{
            uint8 Row = 0, Col = 0;
            // Loop through the rows
            for( Row = 0 ; Row < KEYPAD_ROWS ; ++Row ){
                // Set the current row to low
                GPIO_WritePinValue( Port_id , Row , LOGIC_LOW );
                // Loop through the columns
                for( Col = 0 ; Col < KEYPAD_COLS ; ++Col ){
                    if( GPIO_ReadPinValue(Port_id, Col + KEYPAD_COLS) == KEY_BUTTON_PRESSED){
                        _delay_ms(20);
                        // Check if the button is still pressed after debounce
                        if( GPIO_ReadPinValue(Port_id, Col + KEYPAD_COLS) == KEY_BUTTON_PRESSED ){
                            KeyVal = KEYPAD_MAP[Row][Col];
                            // Wait until the button is released
                            while( GPIO_ReadPinValue(Port_id, Col + KEYPAD_COLS) == KEY_BUTTON_PRESSED );
                            flag = 1;
                            break;
                        }
                    }
                }
                // Set the current row back to high
                GPIO_WritePinValue(Port_id, Row, LOGIC_HIGH);
                if (flag == LOGIC_HIGH) {
                    break;
                }
            }
        }
    }
    else{
        // PortMode is neither HALF_INPUT_OUTPUT nor HALF_OUTPUT_INPUT
        // Nothing happened, return 0xff
        KeyVal = 0xff;
    }
    return KeyVal;
}





