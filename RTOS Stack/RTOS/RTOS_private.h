/*
 * RTOS_private.h
 *
 *  	Name: Mohamed Hussein
 *	    Layer: RTOS stack
 * 		Version: V1.0 - 23/10/2021
 */

#ifndef _RTOS_PRIVATE_H
#define _RTOS_PRIVATE_H

typedef struct
{
	uint16_t Periodicity;
	uint16_t FirstDelay;
	uint8_t State;
	void (*pvTaskFunction) (void);
}ST_Task_t;

#define TASK_resumed          0
#define TASK_suspended        1

static void voidScheduler (void);

#endif /* RTOS_STACK_RTOS_RTOS_PRIVATE_H_ */
