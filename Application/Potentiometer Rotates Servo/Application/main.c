/*
 * main.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Simple Smart Home
 *
 */

#include "util/delay.h"

#include "../Library/Mapping_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"

#include "../HAL/ServoMotor/ServoMotor_interface.h"

void main(void)
{
	uint16_t u16Local_ADCresult = 0;
	uint8_t u8Local_Angle = 0;

	u8DIO_PinDir(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
	u8DIO_PinDir(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	vADC_Init();

	while(1)
	{
		u8ADC_StartSingleConversionSynch(ADC_SingleEndedChannel0 ,&u16Local_ADCresult);
		u8Local_Angle = (uint8_t)s32Map(0,1023,0,180,u16Local_ADCresult);
		u8ServoMotor_SetAngle(A_CHANNEL,u8Local_Angle);
		_delay_ms(10);

	}
}
