/*
 * Name: Muhammad Hussein Muhammad Salem
 * Layer: MCAL
 * Version: V1.0 - 08/11/2021
 *
 */


#ifndef _TIMER0_CONFIGURATION_H
#define _TIMER0_CONFIGURATION_H

/************************************************* TIMER0 *******************************************/
/* Waveform Generation Mode Bit Description
   Options: 
		1: Normal   -  OverFlow
		2: PWM_Phase_Correct
		3: CTC    -    Clear Timer on Compare Match
		4: Fast_PWM
 */

#define Timer0Waveform_Mode     CTC

/* compare output mode Description
   Options:
		1: NormalOperation   -  , OC0 disconnected
		2: ToggleOC0		- Non PWM mode
		3: ClearOnCompare_SetAtTop    -    Clear OC0 on compare match, set OC0 at TOP (Non-Inverted mode)
		4: SetAtCompare_ClearOnTop			- Set OC0 on compare match, clear OC0 at TOP (Inverted mode)
		5: SET_UpCounting_CLEAR_DownCounting         - Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
		6: CLEAR_UpCounting_SET_DownCounting         - Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
 */

#define Timer0CompareOutput_Mode     ClearOnCompare_SetAtTop

/* Clock Select - Prescaler
   Options: 
		1: Timer_StopClock
		2: TimerNo_Prescalig       -   Clock Source
		3: TimerDiv_By_8           -   Division by 8
		4: TimerDiv_By_64          -   Division by 64
		5: TimerDiv_By_256         -   Division by 256
		6: TimerDiv_By_1024        -   Division by 1024
 */

#define Timer0Prescaler_Select    TimerDiv_By_64

/* Disable or Enable Overflow Interrupt
   Options:
		1: Timer0_OVEnableInterrupt
		2: Timer0_OVDisableInterrupt
 */
#define Timer0_OverflowInterrupt         Timer0_OVDisableInterrupt

/* Disable or Enable CTC Interrupt
   Options:
		1: Timer0_CTCEnableInterrupt
		2: Timer0_CTCDisableInterrupt
 */
#define Timer0_CTCInterrupt         Timer0_CTCEnableInterrupt

/*Set Preload Value on TCNT0*/
#define Timer0_PreloadValue                   0

/*Set Compare Value on OCR0*/
#define Timer0_CompareValue                    125

/****************************************************************************************************/
#endif
