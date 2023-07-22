/*
 * main.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Simple Smart Home
 *
 */
/*enter the ID & the password is ID but in opposite direction
 * ex: ID=1234         Pass=4321
 * you have 3 trials that appears on 7Segment
 * after that it will measure the temperature and if it's bigger than 30c, the motor starts to run
 * & stops if it's smaller than 30c
 * it will also measure the light intensity surrounding you & number of LEDs will be on based on that
 * */
#include "util/delay.h"
#include "../Library/Mapping_interface.h"

#include "../MCAL/Global Interrupt/GIE_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KeyPad/Keypad_interface.h"
#include "../HAL/Seven Segment/Sevensegment_interface.h"
#include "../HAL/TempSensor/TempSensor_interface.h"
#include "../HAL/DC_Motor/DCMotor_interface.h"

#define NOT_PRESSED           0x00
#define ID_size                 4
#define TRUE                    1
#define FALSE                   0

uint8_t u8Local_ID[5] = {NOT_PRESSED};
uint8_t u8Local_Pass[5] = {NOT_PRESSED};

void Temperature(void);
void LightIntensity(void);

uint16_t u16Temp = 0;
uint8_t  u8Temp = 0;
uint16_t u16Light = 0;
uint8_t  u8Light = 0;
uint8_t  u8Leds = 0;

void main(void)
{
	uint8_t u8Local_Counter = 0;
	uint8_t u8Local_Iterator = 0;
	uint8_t u8Local_Trials = 3;
	uint8_t u8Local_PassFlag = FALSE;
	uint8_t u8Local_IdFlag = TRUE;
	uint8_t u8Local_SensorFlag = FALSE;

	vLCD_Init();
	vKeypad_Init();
	vSevensegment_Init(DIO_PORTC);
	vDCMotor_Init();
	vADC_Init();
	vTempSensor_Init();
	vGlobalInterrupt_Enable();

	u8DIO_PinDir(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);
	vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
	vLCD_SendString("Welcome!");
	_delay_ms(3000);
	vLCD_ClearDisplay();

	while(1)
	{
		if(u8Local_IdFlag == TRUE)
		{
			u8Local_IdFlag = FALSE;
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Enter ID: ");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			while(1)
			{
				do
				{
					u8Local_ID[u8Local_Counter] = u8Keypad_GetPressedKey();
				}while(u8Local_ID[u8Local_Counter] == NOT_PRESSED);
				vLCD_SendCharacter(u8Local_ID[u8Local_Counter]);
				u8Local_Counter++;
				if(u8Local_Counter == 4)
					break;
			}

			u8Local_Counter = 0;
			u8Local_PassFlag = TRUE;
		}

		if(u8Local_PassFlag == TRUE)
		{
			while(u8Local_Trials != 0)
			{
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("Enter Password: ");
				vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
				u8DIO_PinVal(DIO_PORTA,DIO_PIN4,DIO_HIGH);
				vSevensegment_Setnumber(DIO_PORTC,anode,u8Local_Trials);

				while(1)
				{
					do
					{
						u8Local_Pass[u8Local_Counter] = u8Keypad_GetPressedKey();
					}while(u8Local_Pass[u8Local_Counter] == NOT_PRESSED);
					vLCD_SendCharacter(u8Local_Pass[u8Local_Counter]);
					u8Local_Counter++;
					if(u8Local_Counter == 4)
						break;
				}
				u8Local_Counter = 0;

				for(u8Local_Iterator=0; u8Local_Iterator<ID_size && u8Local_PassFlag == TRUE; u8Local_Iterator++)
				{
					if(u8Local_Pass[u8Local_Iterator] != u8Local_ID[ID_size-u8Local_Iterator-1])
					{
						u8Local_Trials--;
						vSevensegment_Setnumber(DIO_PORTC,anode,u8Local_Trials);
						u8Local_PassFlag = FALSE;
					}
				}
				if(u8Local_PassFlag == TRUE)
				{
					u8Local_PassFlag = FALSE;
					u8Local_SensorFlag = TRUE;
					break;
				}

				u8Local_PassFlag = TRUE;
				vLCD_ClearDisplay();
				vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
				vLCD_SendString("Try Again!");
				_delay_ms(1000);
			}
		}

		if(u8Local_Trials != 0 && u8Local_SensorFlag == TRUE)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Welcome, ");
			vLCD_SendString(u8Local_ID);
			_delay_ms(1500);
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Temp: ");
			vLCD_GoToRowCol(LCD_ROW1,LCD_COL0);
			vLCD_SendString("LEDs: ");
			u8DIO_PinVal(DIO_PORTA,DIO_PIN4,DIO_LOW);
			u8Local_SensorFlag = FALSE;
		}

		if(u8Local_Trials == 0)
		{
			vLCD_ClearDisplay();
			vLCD_GoToRowCol(LCD_ROW0,LCD_COL0);
			vLCD_SendString("Bye Bye!");
			_delay_ms(1000);
			vPORT_Init();
			break;
		}
		else
		{
			/*for Temperature*/
			u8ADC_StartConversionAsynch(ADC_SingleEndedChannel0,&u16Temp,Temperature);
			/*for Light Intensity*/
			u8ADC_StartConversionAsynch(ADC_SingleEndedChannel1,&u16Light,LightIntensity);
		}
	}
}

void Temperature(void)
{
	u8Temp = u8TempSensor_GetValue(u16Temp);
	vLCD_GoToRowCol(LCD_ROW0,LCD_COL6);
	vLCD_SendNumber(u8Temp);
	vLCD_SendCharacter('c');
	if(u8Temp > 30)
	{
		vLCD_SendString("     M");
		vDCMotor_RotateCW();
	}
	else
	{
		vLCD_SendString("      ");
		vDCMotor_Stop();
	}
}

void LightIntensity(void)
{
	u8Light = (uint8_t)s32Map(0,1023,1,8,u16Light);

	vLCD_GoToRowCol(LCD_ROW1,LCD_COL6);
	vLCD_SendNumber(u8Light);
	vLCD_SendString("LEDs");
	vLCD_SendString("      ");
	u8Leds = (uint8_t)s32Map(1,8,0,255,u8Light);
	u8DIO_PortVal(DIO_PORTC,u8Leds);
}
