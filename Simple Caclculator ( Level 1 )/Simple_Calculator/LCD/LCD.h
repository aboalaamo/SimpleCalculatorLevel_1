/*************************************************************************************
* Module: LCD Driver																 *
* File Name: LCD.h																 	 *
* Description: Header file for the LCD driver										 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


#ifndef DRIVERS_LCD_LCD_H_
#define DRIVERS_LCD_LCD_H_


#define MODE_4_BIT			LOGIC_LOW
#define MODE_8_BIT			LOGIC_HIGH
#define RS					PIN0_ID
#define RW					PIN1_ID
#define E					PIN2_ID

#define DB0					PIN0_ID
#define DB1					PIN1_ID
#define DB2					PIN2_ID
#define DB3					PIN3_ID
#define DB4					PIN4_ID
#define DB5					PIN5_ID
#define DB6					PIN6_ID
#define DB7					PIN7_ID

#define INSTRUCTION_CODE	LOGIC_LOW
#define DATA_CODE			LOGIC_HIGH
#define WRITE_DATA			LOGIC_LOW
#define READ_DATA			LOGIC_HIGH

#define LCD_GO_TO_HOME   	   (0x02)
#define LCD_FIRST_ROW  	       (0x80)
#define LCD_SECOND_ROW	       (0xC0)
#define LCD_ROW_1  		       (1u)
#define LCD_ROW_2		       (2u)
#define SET_CGRAM_ADDRESS      (0x40)
#define SET_DDRAM_ADDRESS      (0x80)

#define MODE_4_BIT_FUNCTION_SET_PART_1	(0x20)
#define MODE_4_BIT_FUNCTION_SET_PART_2	(0x80)
#define MODE_4_BIT_DISPLAY_PART_1		(0x00)
#define MODE_4_BIT_DISPLAY_PART_2		(0xF0)
#define MODE_4_BIT_CLEAR_PART_1			(0x00)
#define MODE_4_BIT_CLEAR_PART_2			(0x10)
#define MODE_4_BIT_ENTRY_MODE_PART_1	(0x00)
#define MODE_4_BIT_ENTRY_MODE_PART_2	(0x60)

#define MODE_8_BIT_FUNCTION_SET			(0x38)
#define MODE_8_BIT_DISPLAY				(0x0F)
#define MODE_8_BIT_CLEAR				(0x01)
#define MODE_8_BIT_ENTRY_MODE			(0x06)

#define BASE_TEN	(10u)


/* Functions Prototypes */

void LCD_LcdInit( uint8 Data_Port , uint8 Control_Port , uint8 Bit_Mode );

void LCD_SendCommand( uint8 Command );

void LCD_SendData( uint8 Data );

void LCD_DisplayString( sint8 *Str );

void LCD_DisplayNumber( sint32 Number );

void LCD_MoveCursor( uint8 RowIndex , uint8 ColIndex );

void LCD_ClearLCD( void );

void LCD_SaveCustomChar( uint8 Index , uint8 CustomChar[] );

void LCD_DisplayCustomChar( uint8 Index );


#endif /* DRIVERS_LCD_LCD_H_ */
