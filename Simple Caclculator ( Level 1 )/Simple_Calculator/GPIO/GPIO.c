/*************************************************************************************
* Module: GPIO Driver																 *
* File Name: GPIO.c																 	 *
* Description: Source file for the AVR GPIO driver									 *
* Author: Mohamed Alaa																 *
**************************************************************************************/

/* Includes */

#include <avr/io.h>
#include <util/delay.h>
#include "../Library/Std_Types.h"
#include "../Library/Macros.h"
#include "GPIO.h"

/* Functions Implementation */


/*
 * Description: This function is used to set the direction pin on a GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
	 * Pin_Id: pin on the port .
	 * Direction: direction of pin ( Input or Output ) .
 * Return Value: no return ( void ) .
 */
void GPIO_SetPinDirction( uint8 Port_Id , uint8 Pin_Id , uint8 Direction ){
	switch( Port_Id ){
		case PORTA_ID :
			if( Direction == PIN_INPUT ){
				CLR_BIT( DDRA , Pin_Id );
			}
			else{
				SET_BIT( DDRA , Pin_Id );
			}
			break ;

		case PORTB_ID :
			if( Direction == PIN_INPUT ){
				CLR_BIT( DDRB , Pin_Id );
			}
			else{
				SET_BIT( DDRB , Pin_Id );
			}
			break ;

		case PORTC_ID :
			if( Direction == PIN_INPUT ){
				CLR_BIT( DDRC , Pin_Id );
			}
			else{
				SET_BIT( DDRC , Pin_Id );
			}
			break ;

		case PORTD_ID :
			if( Direction == PIN_INPUT ){
				CLR_BIT( DDRD , Pin_Id );
			}
			else{
				SET_BIT( DDRD , Pin_Id );
			}
			break ;
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to write the value of pin on a GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
	 * Pin_Id: pin on the port .
	 * Value: value of pin ( High or Low ) .
 * Return Value: no return ( void ) .
 */
void GPIO_WritePinValue( uint8 Port_Id , uint8 Pin_Id , uint8 Value ){
	switch( Port_Id ){
		case PORTA_ID :
			if( Value == LOGIC_LOW ){
				CLR_BIT( PORTA , Pin_Id );
			}
			else{
				SET_BIT( PORTA , Pin_Id );
			}
			break ;

		case PORTB_ID :
			if( Value == LOGIC_LOW ){
				CLR_BIT( PORTB , Pin_Id );
			}
			else{
				SET_BIT( PORTB , Pin_Id );
			}
			break ;

		case PORTC_ID :
			if( Value == LOGIC_LOW ){
				CLR_BIT( PORTC , Pin_Id );
			}
			else{
				SET_BIT( PORTC , Pin_Id );
			}
			break ;

		case PORTD_ID :
			if( Value == LOGIC_LOW ){
				CLR_BIT( PORTD , Pin_Id );
			}
			else{
				SET_BIT( PORTD , Pin_Id );
			}
			break ;
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to read the value of pin on a GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
	 * Pin_Id: pin on the port .
 * Return Value: return pin value ( High or Low ) .
 */
uint8 GPIO_ReadPinValue( uint8 Port_Id , uint8 Pin_Id ){
	uint8 PinValue ;
	switch( Port_Id ){
		case PORTA_ID :
			if( RED_BIT( PINA , Pin_Id ) ){
				PinValue = LOGIC_HIGH ;
			}
			else{
				PinValue = LOGIC_LOW ;
			}
			break ;

		case PORTB_ID :
			if( RED_BIT( PINB , Pin_Id ) ){
				PinValue = LOGIC_HIGH ;
			}
			else{
				PinValue = LOGIC_LOW ;
			}
			break ;

		case PORTC_ID :
			if( RED_BIT( PINC , Pin_Id ) ){
				PinValue = LOGIC_HIGH ;
			}
			else{
				PinValue = LOGIC_LOW ;
			}
			break ;

		case PORTD_ID :
			if( RED_BIT( PIND , Pin_Id ) ){
				PinValue = LOGIC_HIGH ;
			}
			else{
				PinValue = LOGIC_LOW ;
			}
			break ;
	}
	return PinValue ;
}

/*************************************************************************************/

void GPIO_TogglePinValue( uint8 Port_Id , uint8 Pin_Id ){
	switch( Port_Id ){
		case PORTA_ID :
			TOG_BIT( PORTA , Pin_Id );
			break ;

		case PORTB_ID :
			TOG_BIT( PORTB , Pin_Id );
			break ;

		case PORTC_ID :
			TOG_BIT( PORTC , Pin_Id );
			break ;

		case PORTD_ID :
			TOG_BIT( PORTD , Pin_Id );
			break ;
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to set the direction of GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
	 * Direction: direction of port .
 * Return Value: no return ( void ) .
 */
void GPIO_SetPortDirction( uint8 Port_Id , uint8 Direction ){
	switch( Port_Id ){
		case PORTA_ID :
			DDRA = Direction ;
			break ;

		case PORTB_ID :
			DDRB = Direction ;
			break ;

		case PORTC_ID :
			DDRC = Direction ;
			break ;

		case PORTD_ID :
			DDRD = Direction ;
			break ;
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to write the value of GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
	 * Value: value of port .
 * Return Value: no return ( void ) .
 */
void GPIO_WritePortValue( uint8 Port_Id , uint8 Value ){
	switch( Port_Id ){
		case PORTA_ID :
			PORTA = Value ;
			break ;

		case PORTB_ID :
			PORTB = Value ;
			break ;

		case PORTC_ID :
			PORTC = Value ;
			break ;

		case PORTD_ID :
			PORTD = Value ;
			break ;
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to read the value of GPIO port.
 * Arguments:
	 * Port_Id: GPIO port .
 * Return Value: return port value .
 */
uint8 GPIO_ReadPortValue( uint8 Port_Id ){
	uint8 PortValue ;
	switch( Port_Id ){
		case PORTA_ID :
			PortValue = PINA ;
			break ;

		case PORTB_ID :
			PortValue = PINB ;
			break ;

		case PORTC_ID :
			PortValue = PINC ;
			break ;

		case PORTD_ID :
			PortValue = PIND ;
			break ;
	}
	return PortValue ;
}
