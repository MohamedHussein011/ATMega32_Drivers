/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */
 
#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H

/*Timer interrupts source*/
#define Timer0_Overflow             	0
#define Timer0_CompareMatch         	1

/****************************************Timer initialize**************************************************/
void vTimer0_Init(void);

/******************************* Set callback function for all Timers interrupts source *****************************/
unsigned char u8Timer_SetCallbackFunction (void (*pvCopy_CallbackFunction) (void), unsigned char u8Copy_InterruptSource);


#endif 
