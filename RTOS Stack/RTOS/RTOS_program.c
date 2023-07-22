/*
 * RTOS_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mhmd
 */


#include "../../Library/STD_TYPE.h"

#include "../Timer0/Timer0_interface.h"
#include "../GIE/GIE_interface.h"

#include "RTOS_private.h"
#include "RTOS_configuration.h"
#include "RTOS_interface.h"

ST_Task_t SystemTasks[Number_Of_Tasks] = {{NULL}};

void vRTOS_Start (void)
{
	/*trigger compare match interrupt every 1 ms*/
	u8Timer_SetCallbackFunction(voidScheduler, Timer0_CompareMatch);
	vGlobalInterrupt_Enable();
	vTimer0_Init();
}

/*here we consider the highest priority is the lowest index
 * the Periodicity is in terms of system tick we choose in Timer0 configuration
 *
 * */
uint8_t vRTOS_CreateTask (uint8_t u8Copy_Priority, uint16_t u16Copy_Periodicity, void (*pvCopy_Function) (void), uint16_t u16Copy_FirstDelay)
{
	uint8_t u8Local_ErrorState = OK;

	/*Check first if the task priority is used before creating another task*/
	if(SystemTasks[u8Copy_Priority].pvTaskFunction == NULL)
	{
		SystemTasks[u8Copy_Priority].Periodicity = u16Copy_Periodicity;
		SystemTasks[u8Copy_Priority].pvTaskFunction = pvCopy_Function;
		SystemTasks[u8Copy_Priority].State = TASK_resumed;
		SystemTasks[u8Copy_Priority].FirstDelay = u16Copy_FirstDelay;
	}else
	{
		/*priority is reserved before and can't used*/
		u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}

static void voidScheduler (void)
{
	uint8_t u8Local_TaskCounter;

	for(u8Local_TaskCounter = 0; u8Local_TaskCounter < Number_Of_Tasks; u8Local_TaskCounter++)
	{
		/*check if the task is suspended or not*/
		if(SystemTasks[u8Local_TaskCounter].State == TASK_resumed)
		{
			if(SystemTasks[u8Local_TaskCounter].FirstDelay == 0)
			{
				/*Invoke the Task function*/
				if(SystemTasks[u8Local_TaskCounter].pvTaskFunction != NULL)
				{
					SystemTasks[u8Local_TaskCounter].pvTaskFunction();
					/*Assign first delay parameter to periodicity mince 1*/
					SystemTasks[u8Local_TaskCounter].FirstDelay = SystemTasks[u8Local_TaskCounter].Periodicity - 1;
				}
			}
			else
			{
				/*Decrement first delay*/
				SystemTasks[u8Local_TaskCounter].FirstDelay--;
			}
		}

	}
}

void vRTOS_SuspendTask (uint8_t u8Copy_Priority)
{
	SystemTasks[u8Copy_Priority].State = TASK_suspended;
}

void vRTOS_ResumeTask (uint8_t u8Copy_Priority)
{
	SystemTasks[u8Copy_Priority].State = TASK_resumed;
}

void vRTOS_DeleteTask (uint8_t u8Copy_Priority)
{
	SystemTasks[u8Copy_Priority].pvTaskFunction = NULL;
}
