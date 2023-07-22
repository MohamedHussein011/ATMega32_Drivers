/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/Interrupts.h"

/* 3. MCAL Files */
#include "Timer0_configuration.h"
#include "Timer0_interface.h"
#include "Timer0_private.h"
#include "Timer0_registers.h"

/********************* Array of 8 pointers to functions for callback for all Timers interrupts *******************/
static void (*pvTimer_CallbackFunction[2]) (void) = {NULL};

/****************************************Timer initialize**************************************************/
/*Initialize Timer0 with configuration you choose
 * Input: void
 * return: void
 */
void vTimer0_Init(void)
{
	/* Timer/Counter Waveform Generation Mode of Operation */
#if Timer0Waveform_Mode == Normal
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == PWM_Phase_Correct
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == CTC
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#elif Timer0Waveform_Mode == Fast_PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*choose compare output mode*/
#if Timer0CompareOutput_Mode == NormalOperation
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == ToggleOC0
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == ClearOnCompare_SetAtTop
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == CLEAR_UpCounting_SET_DownCounting
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == SetAtCompare_ClearOnTop
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif Timer0CompareOutput_Mode == SET_UpCounting_CLEAR_DownCounting
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable Overflow Interrupt*/
#if Timer0_OverflowInterrupt == Timer0_OVEnableInterrupt
	SET_BIT(TIMSK,TOIE0);
#elif Timer0_OverflowInterrupt == Timer0_OVDisableInterrupt
	CLR_BIT(TIMSK,TOIE0);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Disable or Enable CTC Interrupt*/
#if Timer0_CTCInterrupt == Timer0_CTCEnableInterrupt
	SET_BIT(TIMSK,OCIE0);
#elif Timer0_CTCInterrupt == Timer0_CTCDisableInterrupt
	CLR_BIT(TIMSK,OCIE0);
#else
#error "Wrong choice, please choose correctly"
#endif

	/*Set Preload Value on TCNT0*/
	TCNT0 = Timer0_PreloadValue;

	/*Set Compare Value on OCR0*/
	OCR0 = Timer0_CompareValue;

	/* Clock Select Bit Description ---> Prescaler */
	TCCR0 &= TimerPrescaler_Mask;
	TCCR0 |= Timer0Prescaler_Select;
}

/*******************************************************************************************************************/
/******************************* Set callback function for all Timers interrupts source *****************************/
uint8_t u8Timer_SetCallbackFunction (void (*pvCopy_CallbackFunction) (void), uint8_t u8Copy_InterruptSource)
{
	uint8_t u8Local_ErrorState = OK;

	if(pvCopy_CallbackFunction != NULL)
	{
		pvTimer_CallbackFunction[u8Copy_InterruptSource] = pvCopy_CallbackFunction;
	}else{
		u8Local_ErrorState = NULLPOINTER;
	}

	return u8Local_ErrorState;
}
/*******************************************************************************************************************/

/********************************************** ISR Body Definition ************************************************/
/************************************************* Timer0 *******************************************/

ISR(TIMER0_OVF)
{
	if (pvTimer_CallbackFunction[Timer0_Overflow] != NULL)
	{
		pvTimer_CallbackFunction[Timer0_Overflow]();
	}else{
		/*Do Nothing*/
	}
}

ISR(TIMER0_COMP)
{
	if (pvTimer_CallbackFunction[Timer0_CompareMatch] != NULL)
	{
		pvTimer_CallbackFunction[Timer0_CompareMatch]();
	}else{
		/*Do Nothing*/
	}
}
