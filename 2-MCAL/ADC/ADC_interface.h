/*
 * ADC_interface.h
 *
 * 		Name: Mohamed Hussein
 * 		Layer: MCAL
 * 		Version: V1.0 - 09/12/2021
 * 		Driver: ADC - Analog to Digital Converter
 */

#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H

/*ADC Channels for PORTA*/
#define ADC_SingleEndedChannel0       0
#define ADC_SingleEndedChannel1       1
#define ADC_SingleEndedChannel2       2
#define ADC_SingleEndedChannel3       3
#define ADC_SingleEndedChannel4       4
#define ADC_SingleEndedChannel5       5
#define ADC_SingleEndedChannel6       6
#define ADC_SingleEndedChannel7       7

/*if i want to do more than 1 conversion ---> Synch function is valid but will take long time to do more than 1 consecutively
 * Asynch is invalid as every conversion will re-write the previous one so we will read the last operation
 * so, we make a function that allows us to do that without any problems ---> Chain Function
 * */
typedef struct
{
	u8 ADC_NumberOfConversions;
	u8 *ADC_Channels;
	u16 *ADC_Results;
	void (*pvNotificationFunc)(void);
}ST_ChainAsynch_t;

typedef struct
{
	u8 ADC_NumberOfConversions;
	u8 *ADC_Channels;
	u16 *ADC_Results;
}ST_ChainSynch_t;

void vADC_Init(void);
u8 u8ADC_StartSingleConversionSynch(u8 u8Copy_Channel, u16* u16Copy_Value);
u8 u8ADC_StartSingleConversionAsynch(u8 u8Copy_Channel, u16* pu16Copy_Value, void (*pvCopy_NotificationFunction) (void));

u8 u8ADC_StartChainConversionSynch(ST_ChainSynch_t *stCopy_Element);
u8 u8ADC_StartChainConversionAsynch(ST_ChainAsynch_t *stCopy_Element);

u16 u16ADC_ConvertDigitalToAnalog (u16 u16Copy_Value);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
