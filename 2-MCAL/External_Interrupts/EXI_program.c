/*
 * Name: Mohamed Hussein 
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: External Interrupts
 */


/* Files Inclusion */

/* 1. User Defined Libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Interrupts.h"

/* 3. MCAL Files */
#include "EXI_configuration.h"
#include "EXI_interface.h"
#include "EXI_private.h"
#include "EXI_registers.h"

/*array of 3 pointers to functions for all interrupt sources*/
static void (*pvCallbackFunction[3]) (void) = {NULL};

/* Functions Definitions */
/*initialize External Interrupt 0 with configuration you choose
 * Input: void
 * return: void
 */
void vEXI_InitINT0(void)     /* PD2 */
{
	/* Set Configuration to generate interrput */
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01);
#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01);
#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01);
#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01);
#else
#error "wrong INT0_SENSE configuration option"
#endif

	/* Set External Interrput 0 Enable */
	SET_BIT(GICR, INT0);

}

void vEXI_InitINT1 (void)     /* PD3 */
{
	/* Set Configuration to generate interrput */
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11);
#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11);
#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11);
#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11);
#else
#error "wrong INT1_SENSE configuration option"
#endif

	/* Set External Interrput 1 Enable */
	SET_BIT(GICR, INT1);

}

void vEXI_InitINT2(void)    /* PB2 */
{
	/* Set Configuration to generate interrput */
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,ISC2);
#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,ISC2);
#else
#error "wrong INT2_SENSE configuration option"
#endif

	/* Set External Interrput 2 Enable */
	SET_BIT(GICR, INT2);
}

u8 u8EXI_INT0SetSenseControl (u8 u8Copy_SenseControl)
{
	u8 u8Local_ErrorState = OK;
	switch(u8Copy_SenseControl)
	{
	case LOW_LEVEL: CLR_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01); break;
	case ON_CHANGE: SET_BIT(MCUCR, ISC00);
	CLR_BIT(MCUCR, ISC01); break;
	case FALLING_EDGE: CLR_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01); break;
	case RISING_EDGE: SET_BIT(MCUCR, ISC00);
	SET_BIT(MCUCR, ISC01); break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}
u8 u8EXI_INT1SetSenseControl (u8 u8Copy_SenseControl)
{
	u8 u8Local_ErrorState = OK;
	switch(u8Copy_SenseControl)
	{
	case LOW_LEVEL: CLR_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11); break;
	case ON_CHANGE: SET_BIT(MCUCR, ISC10);
	CLR_BIT(MCUCR, ISC11); break;
	case FALLING_EDGE: CLR_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11); break;
	case RISING_EDGE: SET_BIT(MCUCR, ISC10);
	SET_BIT(MCUCR, ISC11); break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}
u8 u8EXI_INT2SetSenseControl (u8 u8Copy_SenseControl)
{
	u8 u8Local_ErrorState = OK;
	switch(u8Copy_SenseControl)
	{
	case FALLING_EDGE: CLR_BIT(MCUCSR,ISC2); break;
	case RISING_EDGE: SET_BIT(MCUCSR,ISC2); break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}

u8 u8EXI_EnableInterrupt (u8 u8Copy_InterruptID)
{
	u8 u8Local_ErrorState = OK;
	switch(u8Copy_InterruptID)
	{
	case External_INT0: SET_BIT(GICR, INT0); break;
	case External_INT1: SET_BIT(GICR, INT1); break;
	case External_INT2: SET_BIT(GICR, INT2); break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}
u8 u8EXI_DisableInterrupt (u8 u8Copy_InterruptID)
{
	u8 u8Local_ErrorState = OK;
	switch(u8Copy_InterruptID)
	{
	case External_INT0: CLR_BIT(GICR, INT0); break;
	case External_INT1: CLR_BIT(GICR, INT1); break;
	case External_INT2: CLR_BIT(GICR, INT2); break;
	default: u8Local_ErrorState = NOK;
	}

	return u8Local_ErrorState;
}

/* Set Callback Function for all  interrupt sources*/
u8 u8EXI_SetCallback (void (*pvCopy_Function) (void), u8 u8Copy_InerruptSource)
{
	u8 u8Local_Error = OK;

	if(pvCopy_Function != NULL)
	{
		pvCallbackFunction[u8Copy_InerruptSource] = pvCopy_Function;
	}else
		u8Local_Error = NOK;

	return u8Local_Error;
}

/******************************************************************************
 * !comment  :  ISR Function EXI.  							 			      *
 ******************************************************************************/
/*INT0*/
ISR(EXT_INT0)
{
	if(pvCallbackFunction[External_Interrupt0] != NULL)
	{
		pvCallbackFunction[External_Interrupt0]();
	}
	else
	{

	}
}

/*INT1*/
ISR(EXT_INT1)
{
	if(pvCallbackFunction[External_Interrupt1] != NULL)
	{
		pvCallbackFunction[External_Interrupt1]();
	}
	else
	{

	}
}

/*INT2*/
ISR(EXT_INT2)
{
	if(pvCallbackFunction[External_Interrupt2] != NULL)
	{
		pvCallbackFunction[External_Interrupt2]();
	}
	else
	{

	}
}
