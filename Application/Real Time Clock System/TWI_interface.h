/*
 * TWI_interface.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: TWI - Two-wire Serial Interface (I2C)
 */

#ifndef _TWI_INTERFACE_H
#define _TWI_INTERFACE_H

typedef enum {
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddWithWriteError,
	SlaveAddWithReadError,
	MasterWriteError,
	MasterReadError,
	SlaveReadError,
	SlaveWriteError,
	SlaveReceivedError,
	SlaveTransmittedError,
}EN_ErrorStatus_t;

#define WRITE_mode            0x00
#define READ_mode             0x01


void vTWI_MasterInit(void);

EN_ErrorStatus_t enTWI_StartCondition (void);
EN_ErrorStatus_t enTWI_RepeatedStart (void);

EN_ErrorStatus_t enTWI_SendSlaveAddWithWrite(u8 u8Copy_SlaveAddress);
EN_ErrorStatus_t enTWI_SendSlaveAddWithRead(u8 u8Copy_SlaveAddress);

EN_ErrorStatus_t enTWI_MatserWriteByte (u8 u8copy_Data);
EN_ErrorStatus_t enTWI_MasterReadByteACK (u8 *pu8copy_Data);
EN_ErrorStatus_t enTWI_MasterReadByteNACK (u8 *pu8copy_Data);


/*************************** Slave Transmitter & Receiver *********************/

//initialize the slave address for master if it wants to be addressed by other masters
void vTWI_SlaveInit(u8 u8Copy_SlaveAddress);

u8 enTWI_SlaveListen (void);		//listen to the bus in case of being addressed

u8 enTWI_SlaveWriteByte (u8 u8copy_Data);

u8 enTWI_SlaveReadByte (u8 *pu8copy_Data);


u8 u8TWI_GetStatus (void);

void vTWI_StopCondition (void);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
