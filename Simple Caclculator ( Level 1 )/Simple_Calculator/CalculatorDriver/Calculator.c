/*************************************************************************************
* Module: Calculator Driver															 *
* File Name: Calculator.c														 	 *
* Description: Source file for Calculator driver									 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


/* Includes */


#include <util/delay.h>
#include "../Library/Std_Types.h"
#include "../GPIO/GPIO.h"
#include "Calculator.h"
#include "../LCD/LCD.h"
#include "../Keypad/Keypad.h"

static uint8 LCD_DataPort , LCD_ControlPort , Keypad_Port ,  LCD_Mode , Keypad_Mode ;


/*
 * Description: This function is used to initialize and run the Calculator .
 * Arguments:
	 * LCD_DataPort_id : LCD Data Port .
	 * LCD_ControlPort_id : LCD Control Port .
	 * Keypad_Port_id : Keypad Port .
	 * LCD_Mode_id : LCD Connection Mode .
	 * Keypad_Mode_id : Keypad Connection Mode .
 * Return Value: no return ( void ) .
 */
void Calculator_Run(uint8 LCD_DataPort_id, uint8 LCD_ControlPort_id, uint8 Keypad_Port_id, uint8 LCD_Mode_id, uint8 Keypad_Mode_id) {

    // Initialize global variables with provided values.
    LCD_DataPort = LCD_DataPort_id;
    LCD_ControlPort = LCD_ControlPort_id;
    Keypad_Port = Keypad_Port_id;
    LCD_Mode = LCD_Mode_id;
    Keypad_Mode = Keypad_Mode_id;

    // Initialize the LCD display and keypad.
    LCD_LcdInit(LCD_DataPort, LCD_ControlPort, MODE_8_BIT);
    KEYPAD_KeypadInit(Keypad_Port, HALF_INPUT_OUTPUT);

    // Display an introductory message and wait for a key press to start.
    Calculator_StartStatement();

    // Main operation loop.
    Operation:

    while (1) {
    	// OperationStatement will contain Whole Calculation Expression .
    	// StopIndex is index of last input ( = )
        uint8 OperationStatement[16], index = 0, StopIndex;
        uint8 KeyValue = 0xff;
        sint32 Number_1 = 0, Number_2 = 0;
        // To Handle Negative Values if Found .
        uint8 operator, Number_1Operator = '+', Number_2Operator = '+';
        uint8 Number_1Flag = 0, OperatorFlag = 0, Number_2Flag = 0;

        // Input loop to get the user's input.
        while (1) {
            KeyValue = KEYPAD_GetPressedKeyValue(Keypad_Port);

            if (KeyValue == 0xff) {
                continue;
            } else if (KeyValue == 'c') {
                // Clear the LCD and start over if 'c' is pressed.
                LCD_ClearLCD();
                goto Operation;
            } else if (KeyValue == '=') {
                // End the input if '=' is pressed.
                StopIndex = index;
                break;
            } else {
                OperationStatement[index] = KeyValue;
                ++index;
            }

            // Display the pressed key on the LCD.
            LCD_SendData(KeyValue);
        }

        // Parse the input and perform the calculation.
        uint8 counter;
        for (counter = 0; counter < StopIndex; ++counter) {
            if ((OperationStatement[counter] == '-') && (Number_1Flag == 0)) {
                Number_1Operator = OperationStatement[counter];
            } else if ((OperationStatement[counter] >= '0' && OperationStatement[counter] <= '9') &&
                       (OperatorFlag == 0) && (Number_2Flag == 0)) {
                Number_1Flag = 1;
                Number_1 += (OperationStatement[counter] - '0');
                Number_1 *= 10;
            } else if ((OperationStatement[counter] == '+' || OperationStatement[counter] == '-' ||
                        OperationStatement[counter] == '*' || OperationStatement[counter] == '/') &&
                       (Number_1Flag == 1) && (OperatorFlag == 0)) {
                OperatorFlag = 1;
                operator = OperationStatement[counter];
            } else if ((OperationStatement[counter] == '-') && (Number_1Flag == 1) && (OperatorFlag == 1)) {
                Number_2Operator = OperationStatement[counter];
            } else if ((OperationStatement[counter] >= '0' && OperationStatement[counter] <= '9') &&
                       (Number_1Flag == 1) && (OperatorFlag == 1)) {
                Number_2Flag = 1;
                Number_2 += (OperationStatement[counter] - '0');
                Number_2 *= 10;
            } else {
                // Display an error message if an invalid character is encountered.
                LCD_MoveCursor(2, 9);
                LCD_DisplayString("Error !");
            }
        }

        // Handle negative numbers.
        if (Number_1Operator == '-') {
            Number_1 *= -1;
        }
        if (Number_2Operator == '-') {
            Number_2 *= -1;
        }

        // Remove the extra factor of 10 from parsing.
        Number_1 /= 10;
        Number_2 /= 10;

        // Calculate the result .
        sint32 Result;
        Result = Calculator_ResultCalc(Number_1, Number_2, operator);

        // Display the result on the LCD or an error message if an error occurred.
        LCD_MoveCursor(2, 0);
        if (Result == "Error") {
            LCD_MoveCursor(2, 9);
            LCD_DisplayString("Error !");
        } else {
            LCD_DisplayNumber(Result);
        }
    }
}

/*************************************************************************************/

/*
 * Description: This function is used to print a start on LCD .
 * Arguments:
	 * No Arguments .
 * Return Value: no return ( void ) .
 */
static void Calculator_StartStatement(void) {
    // Display "Simple" on the first line at column 5 of an LCD screen.
    LCD_MoveCursor(1, 5);
    LCD_DisplayString("Simple");

    // Display "Calculator" on the second line at column 3 of the same LCD screen.
    LCD_MoveCursor(2, 3);
    LCD_DisplayString("Calculator");

    // Delay for 2 seconds to show the "Simple Calculator" message.
    _delay_ms(2000);

    // Clear the LCD screen.
    LCD_ClearLCD();

    // Display "By :" on the first line at column 6 of the LCD screen.
    LCD_MoveCursor(1, 6);
    LCD_DisplayString("By :");

    // Display "Abo Alaa" on the second line at column 2 of the same LCD screen.
    LCD_MoveCursor(2, 4);
    LCD_DisplayString("Abo Alaa");

    // Delay for 2 seconds to show the "By: Mohamed Alaa" message.
    _delay_ms(2000);

    // Clear the LCD screen.
    LCD_ClearLCD();

    // Display "Press any" on the first line at column 3 of the LCD screen.
    LCD_MoveCursor(1, 3);
    LCD_DisplayString("Press any");

    // Display "key to Start..." on the second line at column 1 of the same LCD screen.
    LCD_MoveCursor(2, 1);
    LCD_DisplayString("key to Start...");

    // Wait indefinitely for any key press to clear the screen.
    while (1) {
        if (KEYPAD_GetPressedKeyValue(Keypad_Port) != 255) {
            LCD_ClearLCD();
            break;
        }
    }
}

/*************************************************************************************/

/*
 * Description: This function is used to calculate the operation .
 * Arguments:
	 * Operand_1 : First Number .
	 * Operand_2 : Second Number .
	 * Operator : Operator .
 * Return Value: Returns The Result .
 */
static sint32 Calculator_ResultCalc(sint32 Operand_1, sint32 Operand_2, uint8 Operator) {
    // Declare a variable to store the result.
    sint32 Result;

    // Use a switch statement to perform different operations based on the operator.
    switch (Operator) {
        case '+':
            // If the operator is '+', add Operand_1 and Operand_2.
            Result = Operand_1 + Operand_2;
            break;
        case '-':
            // If the operator is '-', subtract Operand_2 from Operand_1.
            Result = Operand_1 - Operand_2;
            break;
        case '*':
            // If the operator is '*', multiply Operand_1 and Operand_2.
            Result = Operand_1 * Operand_2;
            break;
        case '/':
            // If the operator is '/', check for division by zero.
            if (Operand_2 == 0) {
                // Display an error message on an LCD screen .
                LCD_MoveCursor(2, 9);
                LCD_DisplayString("Error !");
                // Set the Result to "Error" to indicate an error condition.
                Result = "Error";
            } else {
                // If Operand_2 is not zero, perform division and store the result.
                Result = Operand_1 / Operand_2;
            }
            break;
    }

    // Return the computed result.
    return Result;
}

