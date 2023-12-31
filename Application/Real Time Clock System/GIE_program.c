/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: Global Interrput
 */
 
/* Files Inclusion */

/* 1. User Defined Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* 3. MCAL Files */
#include "GIE_registers.h"
#include "GIE_interface.h"

/* Functions Definitions */
/*Enable Global Interrupt
 * Input: void
 * return: void
 */
void vGlobalInterrupt_Enable(void)
{
	SET_BIT(SREG,7);
}
void vGlobalInterrupt_Disable(void)
{
	CLR_BIT(SREG,7);
}
