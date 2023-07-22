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
	uint8_t ADC_NumberOfConversions;
	uint16_t *ADC_Results;
	uint8_t *ADC_Channels;
	void (*pvNotificationFunc)(void);
}ST_Chain_t;

void vADC_Init(void);
uint8_t u8ADC_StartConversionSynch(uint8_t u8Copy_Channel, uint16_t* u16Copy_Value);
uint8_t u8ADC_StartConversionAsynch(uint8_t u8Copy_Channel, uint16_t* pu16Copy_Value, void (*pvCopy_NotificationFunction) (void));

uint8_t u8ADC_StartChainConversionAsynch(ST_Chain_t *stCopy_Element);

uint16_t u16ADC_ConvertDigitalToAnalog (uint16_t u16Copy_Value);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
