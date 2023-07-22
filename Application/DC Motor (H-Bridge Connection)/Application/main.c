/*
 * main.c
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Application
 *      Simple Calculator
 */
#include "util/delay.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/DC_Motor/DCMotor_interface.h"

void main(void)
{
	u8DCMotor_Init(DIO_PORTD,DIO_PORTD,DIO_PIN0,DIO_PIN1);
	while(1)
	{
		u8DCMotor_RotateCW(DIO_PORTD,DIO_PORTD,DIO_PIN0,DIO_PIN1);
		_delay_ms(1500);
		u8DCMotor_RotateCCW(DIO_PORTD,DIO_PORTD,DIO_PIN0,DIO_PIN1);
		_delay_ms(1500);

	}
}
