/*
 * SPI_interface.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: SPI
 */

#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

void vSPI_MasterInit(void);
void vSPI_SlaveInit(void);

void vSPI_SendChar   (u8 u8Copy_Char);
u8 u8SPI_ReceiveChar (u8* pu8Copy_Char);
u8 u8SPI_TransReceiveChar (u8 u8Copy_Char);

void vSPI_EnableInterrput (void);
void vSPI_DisableInterrput (void);

void vSPI_STCSetCallBack (void (*pvCopy_ptr) (void));


#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
