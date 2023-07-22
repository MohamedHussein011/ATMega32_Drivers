/*
 * Name: Mohamed Hussein
 * Layer: MCAL
 * Version: V1.0 - 23/10/2021
 *
 */
 
#ifndef _TIMER_INTERFACE_H
#define _TIMER_INTERFACE_H

/***** Timer Modes *********/
/*for Timer0 & Timer2*/
typedef enum {
	NormalTimermode,
	PWM_phasecorrectmode,
	CTCmode,
	Fast_PWMmode,
}EN_TimerMode_t;

/*for Timer1*/
typedef enum {
	NormalTimer1mode,
	CTC_OCR1A_TOPmode,
	CTC_ICR1_TOPmode,
	Fast_PWM_ICR1mode,
	Fast_PWM_OCR1Amode
}EN_Timer1Mode_t;

/************** Timer Prescalers *************/
/*for Timer0 & Timer1*/
typedef enum {
	Timer_Stop,
	Timer_Noprescaler,
	Timer_prescaler8,
	Timer_prescaler64,
	Timer_prescaler256,
	Timer_prescaler1024
}EN_TimerPrescaler_t;

/*for Timer2*/
typedef enum {
	Timer2_Stop,
	Timer2_Noprescaler,
	Timer2_prescaler8,
	Timer2_prescaler32,
	Timer2_prescaler64,
	Timer2_prescaler128,
	Timer2_prescaler256,
	Timer2_prescaler1024,
}EN_Timer2Prescaler_t;

/*Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.*/
#define SET_DownCounting_CLEAR_UpCounting			1       /*Non Inverted mode --> duty cycle = comp value / 2^n*/
#define SET_AT_TOP_CLEAR_AT_COMPARE			2       		/*Non Inverted mode --> duty cycle = comp value / 2^n*/

/*Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting*/
#define CLEAR_DownCounting_SET_UpCounting			3       /*Inverted mode --> duty cycle = 1 - (comp value / 2^n)*/
#define CLEAR_AT_TOP_SET_AT_COMPARE			4       /*Inverted mode --> duty cycle = 1 - (comp value / 2^n)*/
#define NORMAL_OPERATION                    5
#define TOGGLE                              6   //OC0 in normal mode

#define CHANNEL_A              0
#define CHANNEL_B              1

#define ICU_RISING_EDGE            0
#define ICU_FALLING_EDGE           1

/*Timer interrupts source*/
#define Timer0_Overflow             	0
#define Timer0_CompareMatch         	1
#define Timer1_Overflow             	2
#define Timer1_CompareMatchA        	3
#define Timer1_CompareMatchB        	4
#define Timer1_CaptureEvent         	5
#define Timer2_Overflow             	6
#define Timer2_CompareMatch         	7

/****************************************Timer initialize**************************************************/
void vTimer0_Initprebuild (void);           /*prebuild function*/
u8 vTimer0_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler);        /*postbuild function*/

void vTimer1_Initprebuild (void);
u8 vTimer1_Initpostbuild (EN_Timer1Mode_t ENcopy_mode, EN_TimerPrescaler_t ENcopy_prescaler);

void vTimer2_Initprebuild (void);
void vTimer2_Initpostbuild (EN_TimerMode_t ENcopy_mode, EN_Timer2Prescaler_t ENcopy_prescaler);

/******************************* callback function for all Timers interrupts source *****************************/
u8 u8Timer_SetCallbackFunction (void (*pvCopy_CallbackFunction) (void), u8 u8Copy_InterruptSource);

/****************************************Timer0 Post Configurations****************************************/
u8 u8Timer0_SetOverFlowPreload(u8 u8copy_Value);
void vTimer0_SetCompMatchValue(u8 u8copy_Value);
void vTimer0_DisableOverFlowInterrupt(void);
void vTimer0_EnableOverFlowInterrupt(void);
void vTimer0_DisableCompareMatchInterrupt(void);
void vTimer0_EnableCompareMatchInterrupt(void);
u8  u8Timer0_SetCompareMatchMode(u8 u8Copy_Mode);
void vTimer0_Stop(void);
u8  u8Timer0_GetTimerValue(u8 *u8Copy_Value);
void vTimer0_ResetTimer(void);
/**********************************************************************************************************/

/****************************************Timer1 Post Configurations****************************************/
u8  u8Timer1_SetCompareMatchMode(u8 u8copy_ChannelID, u8 u8Copy_Mode);
u8 u8Timer1_SetCompValue(u8 u8Copy_Channel, u16 u16Copy_Value);
void vTimer1_DisableCompareMatchInterrupt(u8 u8copy_ChannelID);
void vTimer1_EnableCompareMatchInterrupt (u8 u8copy_ChannelID);
void vTimer1_DisableOverFlowInterrupt(void);
void vTimer1_EnableOverFlowInterrupt(void);
u8 u8Timer1_SetOverFlowPreload(u16 u16Copy_TCNT1);
void vTimer1_SetICRValue(u16 u16Copy_ICR);
void vTimer1_ICUInit(void);
u16  u16Timer1_ICUGetTimerRead(void);
void vTimer1_ICUSetEdge(u8 u8copy_EdgeId);
void vTimer1_ICUDeInit(void);
void vTimer1_DisableICUInterrupt(void);
void vTimer1_EnableICUInterrupt(void);
void vTimer1_Stop(void);
u8  u8Timer1_GetTimerValue(u16 *u16Copy_Value);
void vTimer1_ResetTimer(void);
/**********************************************************************************************************/

/****************************************Timer2 Post Configurations****************************************/
void vTimer2_SetOverFlowPreload(u8 u8copy_Value);
void vTimer2_SetCompMatchValue(u8 u8copy_Value);
void vTimer2_DisableOverFlowInterrupt(void);
void vTimer2_EnableOverFlowInterrupt(void);
void vTimer2_DisableCompareMatchInterrupt(void);
void vTimer2_EnableCompareMatchInterrupt(void);
u8  u8Timer2_SetCompareMatchMode(u8 u8Copy_Mode);
void vTimer2_Stop(void);
u8  u8Timer2_GetTimerValue(u8 *u8Copy_Value);
void vTimer2_ResetTimer(void);
/**********************************************************************************************************/

#endif 
