/*
 * RTOS_interface.h
 *
 *  	Name: Mohamed Hussein
 *	    Layer: RTOS stack
 * 		Version: V1.0 - 23/10/2021
 */

#ifndef _RTOS_INTERFACE_H
#define _RTOS_INTERFACE_H

void vRTOS_Start (void);
uint8_t vRTOS_CreateTask (uint8_t u8Copy_Priority, uint16_t u16Copy_Periodicity, void (*pvCopy_Function) (void), uint16_t u16Copy_FirstDelay);

void vRTOS_SuspendTask (uint8_t u8Copy_Priority);
void vRTOS_ResumeTask (uint8_t u8Copy_Priority);
void vRTOS_DeleteTask (uint8_t u8Copy_Priority);

#endif /* RTOS_STACK_RTOS_RTOS_INTERFACE_H_ */
