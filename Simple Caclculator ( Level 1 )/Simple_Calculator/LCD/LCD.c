/*************************************************************************************
* Module: LCD Driver																 *
* File Name: LCD.c																 	 *
* Description: Source file for LCD driver											 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


/* Includes */

#include <util/delay.h>
#include "../Library/Std_Types.h"
#include "../Library/Macros.h"
#include "../GPIO/GPIO.h"
#include "LCD.h"


static uint8 LCD_DataPort ;
static uint8 LCD_ControlPort ;
static uint8 LCD_Bit_Mode ;


/* Functions Implementation */


/*
 * Description: This function is used to Send Command to LCD .
 * Arguments:
	 * Command : Command Send .
 * Return Value: no return ( void ) .
 */
void LCD_SendCommand( uint8 Command ){
	if( LCD_Bit_Mode == MODE_4_BIT || LCD_Bit_Mode == MODE_8_BIT ){
		GPIO_WritePinValue(LCD_ControlPort,RS,INSTRUCTION_CODE);
		GPIO_WritePinValue(LCD_ControlPort,RW,INSTRUCTION_CODE);
		if( LCD_Bit_Mode == MODE_4_BIT ){
			GPIO_WritePinValue(LCD_DataPort,DB4,RED_BIT(Command,PIN4_ID));
			GPIO_WritePinValue(LCD_DataPort,DB5,RED_BIT(Command,PIN5_ID));
			GPIO_WritePinValue(LCD_DataPort,DB6,RED_BIT(Command,PIN6_ID));
			GPIO_WritePinValue(LCD_DataPort,DB7,RED_BIT(Command,PIN7_ID));
		}
		else if( LCD_Bit_Mode == MODE_8_BIT ){
			GPIO_WritePortValue(LCD_DataPort,Command);
		}
		GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_HIGH);
		_delay_ms(1);
		GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_LOW);
		_delay_ms(1);
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Send Data to LCD .
 * Arguments:
	 * Data : Data Send .
 * Return Value: no return ( void ) .
 */
void LCD_SendData( uint8 Data ){
	if( LCD_Bit_Mode == MODE_4_BIT || LCD_Bit_Mode == MODE_8_BIT ){
		GPIO_WritePinValue(LCD_ControlPort,RS,DATA_CODE);
		GPIO_WritePinValue(LCD_ControlPort,RW,WRITE_DATA);
		if( LCD_Bit_Mode == MODE_4_BIT ){
			GPIO_WritePinValue(LCD_DataPort,DB4,RED_BIT(Data,PIN4_ID));
			GPIO_WritePinValue(LCD_DataPort,DB5,RED_BIT(Data,PIN5_ID));
			GPIO_WritePinValue(LCD_DataPort,DB6,RED_BIT(Data,PIN6_ID));
			GPIO_WritePinValue(LCD_DataPort,DB7,RED_BIT(Data,PIN7_ID));
			GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_HIGH);
			_delay_ms(1);
			GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_LOW);
			_delay_ms(1);
			GPIO_WritePinValue(LCD_DataPort,DB4,RED_BIT(Data,PIN0_ID));
			GPIO_WritePinValue(LCD_DataPort,DB5,RED_BIT(Data,PIN1_ID));
			GPIO_WritePinValue(LCD_DataPort,DB6,RED_BIT(Data,PIN2_ID));
			GPIO_WritePinValue(LCD_DataPort,DB7,RED_BIT(Data,PIN3_ID));
		}
		else{
			GPIO_WritePortValue(LCD_DataPort,Data);
		}
		GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_HIGH);
		_delay_ms(1);
		GPIO_WritePinValue(LCD_ControlPort,E,LOGIC_LOW);
		_delay_ms(1);
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to initialize LCD .
 * Arguments:
	 * Data_Port : Data Port in MCU .
	 * Control_Port : Control Port in MCU .
	 * Bit_Mode : Mode of Connection .
 * Return Value: no return ( void ) .
 */
void LCD_LcdInit( uint8 Data_Port , uint8 Control_Port , uint8 Bit_Mode ){
		LCD_DataPort = Data_Port ;
		LCD_ControlPort = Control_Port ;
		LCD_Bit_Mode = Bit_Mode ;
	if( LCD_Bit_Mode == MODE_4_BIT || LCD_Bit_Mode == MODE_8_BIT ){
		GPIO_SetPinDirction(LCD_ControlPort,RS,PIN_OUTPUT);
		GPIO_SetPinDirction(LCD_ControlPort,RW,PIN_OUTPUT);
		GPIO_SetPinDirction(LCD_ControlPort,E,PIN_OUTPUT);
		GPIO_SetPortDirction(LCD_DataPort,PORT_OUTPUT);
		if( LCD_Bit_Mode == MODE_4_BIT ){
			_delay_ms(50);
			/* Function Set */
			LCD_SendCommand(MODE_4_BIT_FUNCTION_SET_PART_1);
			LCD_SendCommand(MODE_4_BIT_FUNCTION_SET_PART_1);
			LCD_SendCommand(MODE_4_BIT_FUNCTION_SET_PART_2);
			_delay_ms(50);
			/* Display ON/OFF */
			LCD_SendCommand(MODE_4_BIT_DISPLAY_PART_1);
			LCD_SendCommand(MODE_4_BIT_DISPLAY_PART_2);
			_delay_ms(50);
			/* Display Clear */
			LCD_SendCommand(MODE_4_BIT_CLEAR_PART_1);
			LCD_SendCommand(MODE_4_BIT_CLEAR_PART_2);
			_delay_ms(2);
			/* Entry Mode Set */
			LCD_SendCommand(MODE_4_BIT_ENTRY_MODE_PART_1);
			LCD_SendCommand(MODE_4_BIT_ENTRY_MODE_PART_2);
		}
		else{
			_delay_ms(50);
			/* Function Set */
			LCD_SendCommand(MODE_8_BIT_FUNCTION_SET);
			_delay_ms(50);
			/* Display ON/OFF */
			LCD_SendCommand(MODE_8_BIT_DISPLAY);
			_delay_ms(50);
			/* Display Clear */
			LCD_SendCommand(MODE_8_BIT_CLEAR);
			_delay_ms(2);
			/* Entry Mode Set */
			LCD_SendCommand(MODE_8_BIT_ENTRY_MODE);
		}
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Display String on LCD .
 * Arguments:
	 * *Str : Pointer to Array of Characters ( String ) .
 * Return Value: no return ( void ) .
 */
void LCD_DisplayString( sint8 *Str ){
	sint8 CharcterIndex ;
	for ( CharcterIndex = 0 ; Str[CharcterIndex] != NULL_CHAR ; ++CharcterIndex ){
		LCD_SendData(Str[CharcterIndex]);
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Display Number on LCD .
 * Arguments:
	 * Number : Number Send .
 * Return Value: no return ( void ) .
 */
void LCD_DisplayNumber( sint32 Number ){

	if( Number < 0 ){
		LCD_SendData('-');
		Number *= -1 ;
	}
	if( Number != 0 ){
		LCD_DisplayNumber(Number/10);
		LCD_SendData('0'+(Number%10));
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Move Cursor on LCD .
 * Arguments:
	 * RowIndex : Index of Row .
	 * ColIndex : Index of Column .
 * Return Value: no return ( void ) .
 */
void LCD_MoveCursor( uint8 RowIndex , uint8 ColIndex ){
	if( (RowIndex == LCD_ROW_1 || RowIndex == LCD_ROW_2 ) && ( ColIndex >= 0 && ColIndex <= 15 ) ){
		if( RowIndex == LCD_ROW_1 ){
			LCD_SendCommand( LCD_FIRST_ROW + ColIndex );
		}
		else{
			LCD_SendCommand( LCD_SECOND_ROW + ColIndex );
		}
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Clear LCD .
 * Arguments:
	 * No Arguments .
 * Return Value: no return ( void ) .
 */
void LCD_ClearLCD( void ){
	if( LCD_Bit_Mode == MODE_4_BIT || LCD_Bit_Mode == MODE_8_BIT ){
		if( LCD_Bit_Mode == MODE_4_BIT ){
			LCD_SendCommand(MODE_4_BIT_CLEAR_PART_1);
			LCD_SendCommand(MODE_4_BIT_CLEAR_PART_2);
		}
		else{
			LCD_SendCommand(MODE_8_BIT_CLEAR);
		}
	}
	else{
		/* Nothing Happened */
	}
}

/*************************************************************************************/

/*
 * Description: This function is used to Save Custom Characters in LCD .
 * Arguments:
	 * Index : Index of Storing in CGRAM .
	 * CustomChar[] : Array of 8 Elements , Each element is 5 digit binary ( 5*8 dots ) .
 * Return Value: no return ( void ) .
 */
void LCD_SaveCustomChar( uint8 Index , uint8 CustomChar[] ){
	if( Index < 8 ){
		uint8 counter ;
		LCD_SendCommand( SET_CGRAM_ADDRESS + Index * 8 );
		for( counter = 0 ; counter < 8 ; ++counter ){
			LCD_SendData(CustomChar[counter]);
		}
		LCD_SendCommand(SET_DDRAM_ADDRESS);
	}
	else{
		/* Nothing Happened */
	}
}
/*************************************************************************************/

/*
 * Description: This function is used to Display Custom Character on LCD .
 * Arguments:
	 * Index : Index of Storing in CGRAM .
 * Return Value: no return ( void ) .
 */
void LCD_DisplayCustomChar( uint8 Index ){
	if( Index < 8 ){
		LCD_SendData(Index);
	}
	else{
		/* Nothing Happened */
	}
}












