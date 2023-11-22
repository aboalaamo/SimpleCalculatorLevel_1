/*************************************************************************************
* Module: GPIO Driver																 *
* File Name: GPIO.h																 	 *
* Description: Header file for the AVR GPIO driver									 *
* Author: Mohamed Alaa																 *
**************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/* Directions */

#define PIN_INPUT			   0
#define PIN_OUTPUT			   1
#define PORT_INPUT			   0
#define PORT_OUTPUT			   255

/* Ports */

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

/* Pins */

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/* Functions Prototypes */

void GPIO_SetPinDirction( uint8 Port_Id , uint8 Pin_Id , uint8 Direction );

void GPIO_WritePinValue( uint8 Port_Id , uint8 Pin_Id , uint8 Value );

uint8 GPIO_ReadPinValue( uint8 Port_Id , uint8 Pin_Id );

void GPIO_TogglePinValue( uint8 Port_Id , uint8 Pin_Id );

void GPIO_SetPortDirction( uint8 Port_Id , uint8 Direction );

void GPIO_WritePortValue( uint8 Port_Id , uint8 Value );

uint8 GPIO_ReadPortValue( uint8 Port_Id );




#endif /* GPIO_H_ */
