/*
 * main.c
 *
 *  	Created on: 29/3/2023
 *      Author: Mohamed Hussein
 *      Real Time Clock System Project
 *		note: press 'A' (ON/C button on keypad) while you're in home screen to enter adjust menu
 *		& after typing any number press 'A'
 */
#include "STD_TYPES.h"
#include "User_Functions.h"

#include "GIE_interface.h"
#include "Timer_interface.h"
#include "TWI_interface.h"

#include "LCD_interface.h"
#include "Keypad_interface.h"
#include "RTC_interface.h"

#include "util/delay.h"

#define NOT_PRESSED				0x00
#define HOME_screen 			0
#define ADJUST_screen 			1
#define HOUR_adj 				2
#define MINUTE_adj				3
#define SECOND_adj 				4
#define YEAR_adj 				5
#define MONTH_adj 				6
#define DAY_adj 				7

void Show_Time(void);
void Show_Date(void);

extern u8 RTC_HOUR, RTC_MINUTE, RTC_SECOND, RTC_YEAR, RTC_MONTH, RTC_DAY;


void main(void)
{
	u8 u8Local_PressedKey = NOT_PRESSED, u8Local_Number[3] = {NOT_PRESSED}, u8Local_Iterator = 0;
	u8 u8Local_Temp = 0, u8Local_Flag = HOME_screen, u8Local_DayFlag = FALSE;
	u8 Hour = 0, Min = 0, Sec = 0;
	u8 Year = 0, Mon = 0, Day = 0;

	vTWI_MasterInit();
	vKeypad_Init();
	vLCD_Init();
	vTimer0_Initprebuild();
	vTimer2_Initprebuild();

	u8Timer_SetCallbackFunction(&Show_Date,Timer0_Overflow);
	u8Timer_SetCallbackFunction(&Show_Time,Timer2_Overflow);

	vGlobalInterrupt_Enable();

	vLCD_ClearDisplay();
	Set_Time(RTC_SECOND,RTC_MINUTE,RTC_HOUR);
	Set_Date(RTC_DAY,RTC_MONTH,RTC_YEAR);

	vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
	vLCD_SendString("Real Time ");
	vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
	vLCD_SendString("Clock Project");
	_delay_ms(1000);

	while(1)
	{

		if(u8Local_Flag == HOME_screen)
		{
			vLCD_ClearDisplay();
			_delay_ms(10);
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Time: ");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
			vLCD_SendString("Date:");

			vTimer2_EnableOverFlowInterrupt();
			vTimer0_EnableOverFlowInterrupt();

			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
				if(u8Local_PressedKey != 'A')
				{
					u8Local_PressedKey = NOT_PRESSED;
				}
			}while(u8Local_PressedKey == NOT_PRESSED);

			vTimer2_DisableOverFlowInterrupt();
			vTimer0_DisableOverFlowInterrupt();

			u8Local_Flag = ADJUST_screen;

		}

		if(u8Local_Flag == ADJUST_screen)
		{
			vLCD_ClearDisplay();
			_delay_ms(10);

			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("1: Adj Time");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
			vLCD_SendString("2: Adj Date");
			vLCD_SendString(" 3:ret");

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();
				if(u8Local_PressedKey == '1' || u8Local_PressedKey == '2' || u8Local_PressedKey == '3')
				{
					/* Do nothing*/
				}
				else
					u8Local_PressedKey = NOT_PRESSED;

			}while(u8Local_PressedKey == NOT_PRESSED);

			switch(u8Local_PressedKey)
			{
			case '1':		u8Local_Flag = HOUR_adj;		break;

			case '2':		u8Local_Flag = YEAR_adj;		break;

			case '3':	    u8Local_Flag = HOME_screen;  	break;
			}
		}

		/************************************* Change Hour ***********************************************/
		if(u8Local_Flag == HOUR_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Hour (00 - 23):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 23)
				{
					Hour = u8Local_Temp;
					_delay_ms(10);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;

					u8Local_Flag = MINUTE_adj;
				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of HOUR_adj

		/************************************* Change Minute ***********************************************/
		if(u8Local_Flag == MINUTE_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Minute (00 - 59):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 59)
				{
					Min = u8Local_Temp;
					_delay_ms(10);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;

					u8Local_Flag = SECOND_adj;
				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of MINUTE_adj

		/************************************* Change Second ***********************************************/
		if(u8Local_Flag == SECOND_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Second (00 - 59):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 59)
				{
					Sec = u8Local_Temp;
					_delay_ms(10);
					vLCD_ClearDisplay();
					Set_Time(Sec,Min,Hour);
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Time Updated!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;

					u8Local_Flag = ADJUST_screen;
				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of SECOND_adj

		/************************************* Change Year ***********************************************/
		if(u8Local_Flag == YEAR_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Year (00 - 99):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 99)
				{
					Year = u8Local_Temp;
					_delay_ms(10);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;

					u8Local_Flag = MONTH_adj;
				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of YEAR_adj

		/************************************* Change Month ***********************************************/
		if(u8Local_Flag == MONTH_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Month (00 - 12):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 12)
				{
					Mon = u8Local_Temp;
					_delay_ms(10);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;

					u8Local_Flag = DAY_adj;
				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of MONTH_adj

		/************************************* Change Day ***********************************************/
		if(u8Local_Flag == DAY_adj)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
			vLCD_SendString("Day (00 - 31):");
			vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);

			u8Local_PressedKey = NOT_PRESSED;
			do
			{
				u8Local_PressedKey = u8Keypad_GetPressedKey();

				if(u8Local_PressedKey >= '0' && u8Local_PressedKey <= '9' && u8Local_Iterator <= 1)
				{
					vLCD_SendCharacter(u8Local_PressedKey);
					u8Local_Number[u8Local_Iterator] = u8Local_PressedKey;
					u8Local_Iterator++;
				}
				else if (u8Local_PressedKey == 'A')
				{	break;	}

			}while(u8Local_PressedKey != 'A');

			if(u8Local_Iterator != 0)
			{
				u8Local_Temp = (u8) ConvertToint((const char*)u8Local_Number);
				if(u8Local_Temp <= 31)
				{
					Day = u8Local_Temp;

					if(Mon == 4 || Mon == 6 || Mon == 9 || Mon == 11)
					{
						if(Day == 31)
							u8Local_DayFlag = FALSE;
						else
							u8Local_DayFlag = TRUE;
					}
					else if (Mon == 2)
					{
						u8Local_Temp = 2000 + Year;
						if(u8Local_Temp % 4 == 0)	//if it's a leap year
						{
							if(Day > 29)
								u8Local_DayFlag = FALSE;
							else
								u8Local_DayFlag = TRUE;
						}
						else
						{
							if(Day > 28)
								u8Local_DayFlag = FALSE;
							else
								u8Local_DayFlag = TRUE;
						}
					}
					else
						u8Local_DayFlag = TRUE;


					if (u8Local_DayFlag == TRUE)
					{
						_delay_ms(10);
						vLCD_ClearDisplay();
						Set_Date(Day,Mon,Year);
						vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
						vLCD_SendString("Date Updated!");
						_delay_ms(1000);
						u8Local_Number[0] = NOT_PRESSED;
						u8Local_Number[1] = NOT_PRESSED;
						u8Local_Iterator = 0;

						u8Local_Flag = ADJUST_screen;
					}
					else
					{
						vLCD_ClearDisplay();
						_delay_ms(10);
						vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
						if(Mon == 2)
						{
							if(u8Local_Temp % 4 == 0)	//if it's a leap year
							{
								vLCD_SendString("Leap Year does");
								vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
								vLCD_SendString("not exceed 29");
							}
							else
							{
								vLCD_SendString("February does");
								vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
								vLCD_SendString("not exceed 28");
							}
						}
						else
						{
							vLCD_SendString("This Month does");
							vLCD_GoToRowCol(LCD_ROW1, LCD_COL0);
							vLCD_SendString("not exceed 30");
						}
						_delay_ms(1000);
						u8Local_Number[0] = NOT_PRESSED;
						u8Local_Number[1] = NOT_PRESSED;
						u8Local_Iterator = 0;
					}


				}
				else
				{
					vLCD_ClearDisplay();
					vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
					vLCD_SendString("Invalid Input!");
					_delay_ms(1000);
					u8Local_Number[0] = NOT_PRESSED;
					u8Local_Number[1] = NOT_PRESSED;
					u8Local_Iterator = 0;
				}
			}
			else
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0, LCD_COL0);
				vLCD_SendString("Invalid Input!");
				_delay_ms(1000);
			}

		}	//end of DAY_adj


	}
}

void Show_Time(void)
{
	u8 x = 0, y = 0, z = 0;

	static u8 counter = 0;
	counter++;

	if(counter == 3)
	{
		Get_Time(&x,&y,&z);

		vLCD_GoToRowCol(LCD_ROW0, LCD_COL7);
		if(z < 10)
		{
			vLCD_SendCharacter(' ');
			vLCD_SendNumber(z);
		}
		else
			vLCD_SendNumber(z);

		vLCD_SendCharacter(':');

		if(y < 10)
		{
			vLCD_SendNumber(0);
			vLCD_SendNumber(y);
		}
		else
			vLCD_SendNumber(y);

		vLCD_SendCharacter(':');

		if(x < 10)
		{
			vLCD_SendNumber(0);
			vLCD_SendNumber(x);
		}
		else
			vLCD_SendNumber(x);

		counter = 0;
	}
}

void Show_Date(void)
{
	u8 d = 0, m = 0, ye = 0;

	static u8 counter = 0;
	counter++;

	if(counter == 7)
	{
		Get_Date(&d,&m,&ye);

		vLCD_GoToRowCol(LCD_ROW1, LCD_COL5);
		if(d < 10)
		{
			vLCD_SendNumber(0);
			vLCD_SendNumber(d);
		}
		else
			vLCD_SendNumber(d);

		vLCD_SendCharacter('-');

		if(m < 10)
		{
			vLCD_SendNumber(0);
			vLCD_SendNumber(m);
		}
		else
			vLCD_SendNumber(m);

		vLCD_SendCharacter('-');

		if(ye < 10)
		{
			vLCD_SendNumber(200);
			vLCD_SendNumber(ye);
		}
		else
		{
			vLCD_SendNumber(20);
			vLCD_SendNumber(ye);
		}

		counter = 0;

	}

}

