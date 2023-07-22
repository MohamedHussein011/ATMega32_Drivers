/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */


#ifndef _TIMER0_REGISTERS_H
#define _TIMER0_REGISTERS_H

/******************************************************************************
 * !comment : TIMER0 Registers  		    	                 			   *
 ******************************************************************************/

/* Timer/Counter Control Register */
#define TCCR0    *((volatile uint8_t *)0x53)
#define FOC0     7                              //Force Output Compare
#define WGM00    6                              //Waveform Generation Mode
#define COM01    5                              //Compare Match Output Mode
#define COM00    4                              //Compare Match Output Mode
#define WGM01    3                              //Waveform Generation Mode
#define CS02     2                              //Clock Select
#define CS01     1                              //Clock Select
#define CS00     0                              //Clock Select

/* Timer/Counter Register */
#define TCNT0    *((volatile uint8_t *)0x52)

/* Output Compare Register */
#define OCR0     *((volatile uint8_t *)0x5C)

/* Timer/Counter Interrupt Mask Register */
#define TIMSK    *((volatile uint8_t *)0x59)
#define OCIE0    1                              //Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE0    0                              //Timer/Counter0 Overflow Interrupt Enable

/* Timer/Counter Interrupt Flag Register */
#define TIFR     *((volatile uint8_t *)0x58)
#define OCF0     1                              //Output Compare Flag 0
#define TOV0     0                              //Timer/Counter0 Overflow Flag


#endif
