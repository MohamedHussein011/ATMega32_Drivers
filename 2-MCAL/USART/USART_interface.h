/*
 * USART_interface.h
 *
 *  		Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: USART
 */

#ifndef _USART_INTERFACE_H
#define _USART_INTERFACE_H

void vUSART_Init(void);

u8 vUSART_SendByte(u8 u8Copy_Byte);
u8 vUSART_RecieveByte(u8* pu8Copy_Byte);

u8 u8USART_SendStringSynchronous(const char * pu8Copy_string);
u8 u8USART_SendStringAsynchronous(const char * pu8Copy_string, void(*Copy_pvNotificationFunction)(void));

u8 u8USART_ReceiveBufferSynchronous(char * pu8Copy_Data, u8 u8Copy_BufferSize);
u8 u8USART_ReceiveBufferAsynchronous(char * pu8Copy_Data, u8 u8Copy_BufferSize, void(*Copy_pvNotificationFunction)(void));

/*enter horizontal tab to exit the function*/
u8 u8USART_ReceiveStringSynchronous(char * pu8Copy_string);

void vUSART_SendNumberSynchronous(s32 s32Copy_Number);

#endif /* MCAL_USART_USART_INTERFACE_H_ */
