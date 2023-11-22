/*************************************************************************************
* Module: Application Program														 *
* File Name: main.c																 	 *
* Description: Runner For Calculator												 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


/* Includes */

#include <avr/io.h>
#include <util/delay.h>
#include "../Library/Std_Types.h"
#include "../Library/Macros.h"
#include "../GPIO/GPIO.h"
#include "../Keypad/Keypad.h"
#include "../LCD/LCD.h"
#include "../CalculatorDriver/Calculator.h"

int main(void){

	GPIO_SetPortDirction(PORTA_ID,PORT_OUTPUT);
	GPIO_SetPortDirction(PORTB_ID,PORT_OUTPUT);
	GPIO_SetPortDirction(PORTC_ID,HALF_INPUT_OUTPUT);
	while(1){
		Calculator_Run(PORTA_ID,PORTB_ID,PORTC_ID,MODE_8_BIT,HALF_INPUT_OUTPUT);
	}
	return 0 ;
}
