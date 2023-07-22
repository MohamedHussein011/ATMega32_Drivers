/*
 * main.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Simple Calculator
 */
#include "util/delay.h"
#include "../Library/Conversion_Function.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KeyPad/Keypad_interface.h"

#define NOT_PRESSED       0x00

void CalculateResult(char Copy_String1[], char Copy_String2[], char u8Copy_Operator, char* Copy_Result);

void main(void)
{
	char Local_Number1[10] = {NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED};
	char Local_Number2[10] = {NOT_PRESSED};
	uint8_t u8Local_Iterator = 0, u8Local_Operator = 0;
	char Local_Result[10];

	vLCD_Init();
	vKeypad_Init();

	vLCD_ClearDisplay();

	while(1)
	{
		/*getting first number*/
		do
		{
			Local_Number1[u8Local_Iterator] = u8Keypad_GetPressedKey();
			if(Local_Number1[u8Local_Iterator] == '/' || Local_Number1[u8Local_Iterator] == '*' || Local_Number1[u8Local_Iterator] == '+' || Local_Number1[u8Local_Iterator] == '=')
				Local_Number1[u8Local_Iterator] = NOT_PRESSED;
		}while(Local_Number1[u8Local_Iterator] == NOT_PRESSED);

		vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
		vLCD_SendCharacter(Local_Number1[u8Local_Iterator]);
		u8Local_Iterator++;

		while(1)
		{
			do{
				Local_Number1[u8Local_Iterator] = u8Keypad_GetPressedKey();
				if(Local_Number1[u8Local_Iterator] == '=')
					Local_Number1[u8Local_Iterator] = NOT_PRESSED;
			}while(Local_Number1[u8Local_Iterator] == NOT_PRESSED);

			if(Local_Number1[u8Local_Iterator] == '/')
			{
				if(Local_Number1[0] == '-' && u8Local_Iterator == 1)
				{
					Local_Number1[u8Local_Iterator] = NOT_PRESSED;
					continue;
				}
				else
				{
					u8Local_Operator = '/';
					Local_Number1[u8Local_Iterator] = '\0';
					vLCD_SendCharacter(u8Local_Operator);
					u8Local_Iterator = 0;
					break;
				}
			}
			else if(Local_Number1[u8Local_Iterator] == '*')
			{
				if(Local_Number1[0] == '-' && u8Local_Iterator == 1)
				{
					Local_Number1[u8Local_Iterator] = NOT_PRESSED;
					continue;
				}
				else
				{
					u8Local_Operator = '*';
					Local_Number1[u8Local_Iterator] = '\0';
					vLCD_SendCharacter(u8Local_Operator);
					u8Local_Iterator = 0;
					break;
				}

			}
			else if(Local_Number1[u8Local_Iterator] == '-')
			{
				if(Local_Number1[0] == '-' && u8Local_Iterator == 1)
				{
					Local_Number1[u8Local_Iterator] = NOT_PRESSED;
					continue;
				}
				else
				{
					u8Local_Operator = '-';
					Local_Number1[u8Local_Iterator] = '\0';
					vLCD_SendCharacter(u8Local_Operator);
					u8Local_Iterator = 0;
					break;
				}

			}
			else if(Local_Number1[u8Local_Iterator] == '+')
			{

				if(Local_Number1[0] == '-' && u8Local_Iterator == 1)
				{
					Local_Number1[u8Local_Iterator] = NOT_PRESSED;
					continue;
				}
				else
				{
					u8Local_Operator = '+';
					Local_Number1[u8Local_Iterator] = '\0';
					vLCD_SendCharacter(u8Local_Operator);
					u8Local_Iterator = 0;
					break;
				}

			}

			vLCD_SendCharacter(Local_Number1[u8Local_Iterator]);
			u8Local_Iterator++;
			_delay_ms(100);
		}

		/*getting second number*/
		do
		{
			Local_Number2[u8Local_Iterator] = u8Keypad_GetPressedKey();
			if(Local_Number2[u8Local_Iterator] == '/' || Local_Number2[u8Local_Iterator] == '*' || Local_Number2[u8Local_Iterator] == '+' || Local_Number2[u8Local_Iterator] == '=')
				Local_Number2[u8Local_Iterator] = NOT_PRESSED;
		}while(Local_Number2[u8Local_Iterator] == NOT_PRESSED);

		vLCD_SendCharacter(Local_Number2[u8Local_Iterator]);
		u8Local_Iterator++;

		while(1)
		{
			do{
				Local_Number2[u8Local_Iterator] = u8Keypad_GetPressedKey();
			}while(Local_Number2[u8Local_Iterator] == NOT_PRESSED);

			if(Local_Number2[u8Local_Iterator] == '=')
			{
				Local_Number2[u8Local_Iterator] = '\0';
				vLCD_SendCharacter('=');
				u8Local_Iterator = 0;
				break;

			}
			else if(Local_Number2[u8Local_Iterator] == '/' || Local_Number2[u8Local_Iterator] == '*' || Local_Number2[u8Local_Iterator] == '+' || Local_Number2[u8Local_Iterator] == '-')
			{
				Local_Number2[u8Local_Iterator] = NOT_PRESSED;
				continue;
			}

			vLCD_SendCharacter(Local_Number2[u8Local_Iterator]);
			u8Local_Iterator++;
			_delay_ms(100);
		}

		CalculateResult(Local_Number1,Local_Number2,u8Local_Operator, Local_Result);
		vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
		vLCD_SendString(Local_Result);

		/*Clear Display*/
		_delay_ms(2000);
		vLCD_ClearDisplay();
		_delay_ms(100);
	}
}

void CalculateResult(char Copy_String1[], char Copy_String2[], char u8Copy_Operator, char* Copy_Result)
{
	int32_t s32Local_Num1 = ConvertToint(Copy_String1);
	int32_t s32Local_Num2 = ConvertToint(Copy_String2);
	int32_t s32Local_Result = 0;

	switch(u8Copy_Operator)
	{
	case '/': s32Local_Result = s32Local_Num1 / s32Local_Num2;     break;
	case '*': s32Local_Result = s32Local_Num1 * s32Local_Num2;     break;
	case '-': s32Local_Result = s32Local_Num1 - s32Local_Num2;     break;
	case '+': s32Local_Result = s32Local_Num1 + s32Local_Num2;     break;
	}

	ConvertToString(Copy_Result, s32Local_Result);

}
