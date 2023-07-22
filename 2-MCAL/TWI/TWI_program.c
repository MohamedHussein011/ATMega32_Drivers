/*
 * TWI_program.c
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: TWI - Two-wire Serial Interface (I2C)
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Interrupts.h"

#include "TWI_private.h"
#include "TWI_configuration.h"
#include "TWI_registers.h"
#include "TWI_interface.h"


void vTWI_MasterInit(void)
{
	/* Set SCL to 400 Kbps
	 * Set TWBR to 2
	 */
	TWBR = 2;

	/*set prescaler to 1*/
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);

	/* Enable Bit for TWI &  Acknowledge Bit*/
#if ACK_Bit == ACK_Disable
	TWCR = (1 << TWEN);
#elif ACK_Bit == ACK_Enable
	TWCR = (1<<TWEA) | (1<<TWEN);
#else
#error "Wrong Option, choose another"
#endif

}
//initialize the slave address for master if it wants to be addressed by other masters
void vTWI_SlaveInit(u8 u8Copy_SlaveAddress)
{
	//initialize the node address
	TWAR = u8Copy_SlaveAddress;

	//Enable TWI
	TWCR = (1<<TWEA) | (1 << TWEN) | (1 << TWINT);
}

EN_ErrorStatus_t enTWI_StartCondition (void)
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;

	/*send start condition & clear the interrupt flag to start the operation then enable TWI*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the START condition has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	/* Check if Start Condition is sent */
	if(u8TWI_GetStatus() != Start_Condition)
	{
		enLocal_ErrorStatus = StartConditionError;
	}
	else
	{
		/*Do Nothing*/
	}

	return enLocal_ErrorStatus;
}
EN_ErrorStatus_t enTWI_RepeatedStart (void)
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;

	/*send start condition & clear the interrupt flag to start the operation then enable TWI*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the Repeated START condition has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	/* Check if Start Condition is sent */
	if(u8TWI_GetStatus() != Repeated_Start_Condition)
	{
		enLocal_ErrorStatus = RepeatedStartError;
	}
	else
	{
		/*Do Nothing*/
	}

	return enLocal_ErrorStatus;
}

EN_ErrorStatus_t enTWI_SendSlaveAddWithWrite(u8 u8Copy_SlaveAddress)
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;
	/* Load address in data register to be sent and clear 1st bit in TWDR for Write operation */
	TWDR = u8Copy_SlaveAddress | WRITE_mode;

	/* Start operation*/
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the Slave address with write has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	/* Check if Start Condition is sent */
	if(u8TWI_GetStatus() != SLA_W_ACK_Rec || u8TWI_GetStatus() != SLA_W_NACK_Rec)
	{
		enLocal_ErrorStatus = SlaveAddWithWriteError;
	}
	else
	{
		/*Do Nothing*/
	}

	return enLocal_ErrorStatus;
}
EN_ErrorStatus_t enTWI_SendSlaveAddWithRead(u8 u8Copy_SlaveAddress)
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;
	/* Load address in data register to be sent and clear 1st bit in TWDR for Write operation */
	TWDR = u8Copy_SlaveAddress | READ_mode;

	/* Start operation*/
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the Slave address with read has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	/* Check if Start Condition is sent */
	if(u8TWI_GetStatus() != SLA_R_ACK_Rec || u8TWI_GetStatus() != SLA_R_NACK_Rec)
	{
		enLocal_ErrorStatus = SlaveAddWithReadError;
	}
	else
	{
		/*Do Nothing*/
	}

	return enLocal_ErrorStatus;
}

EN_ErrorStatus_t enTWI_MatserWriteByte (u8 u8copy_Data)
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;

	/* Load Data in Data register to be sent (Written) */
	TWDR = u8copy_Data;

	/* Start operation*/
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the write byte has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	/* Check if Start Condition is sent */
	if(u8TWI_GetStatus() != Data_Trans_ACK_Rec || u8TWI_GetStatus() != Data_Trans_NACK_Rec)
	{
		enLocal_ErrorStatus = MasterWriteError;
	}
	else
	{
		/*Do Nothing*/
	}

	return enLocal_ErrorStatus;
}
EN_ErrorStatus_t enTWI_MasterReadByteACK (u8 *pu8copy_Data)     //read with send ACK
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;

	/* Start operation*/
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the raed byte has been
	 * received
	 */
	while(!(TWCR & (1 << TWINT)));

	if(u8TWI_GetStatus() != Data_Rec_ACK_Ret)
	{
		enLocal_ErrorStatus = MasterReadError;
	}
	else
	{
		*pu8copy_Data = TWDR;
	}

	return enLocal_ErrorStatus;
}

EN_ErrorStatus_t enTWI_MasterReadByteNACK (u8 *pu8copy_Data)     //read with send NACK
{
	EN_ErrorStatus_t enLocal_ErrorStatus = NoError;

	/* Start operation*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT Flag set. This indicates
	 * that the raed byte has been
	 * received
	 */
	while(!(TWCR & (1 << TWINT)));

	if(u8TWI_GetStatus() != Data_Rec_NACK_Ret)
	{
		enLocal_ErrorStatus = MasterReadError;
	}
	else
	{
		*pu8copy_Data = TWDR;
	}

	return enLocal_ErrorStatus;
}


u8 enTWI_SlaveListen (void)
{

	while (1)
	{
		/*wait until the flag is raised, meaning that i'm being addressed */
		while(!(TWCR & (1 << TWINT)));

		/*check if addressed or not*/
		if(u8TWI_GetStatus() == SLA_Rec_W_Req_ACK_Ret || u8TWI_GetStatus() == SLA_Rec_W_Req_ACK_Ret_ArbLOST) //SLA+W & ACK
		{
			return 0;
		}
		else if(u8TWI_GetStatus() == SLA_Rec_R_Req_ACK_Ret || u8TWI_GetStatus() == SLA_Rec_R_Req_ACK_Ret_ArbLOST) //SLA+R & ACK
		{
			return 1;
		}
		else if(u8TWI_GetStatus() == SLA_Rec_W_Req_ACK_Ret_GenCALL || u8TWI_GetStatus() == SLA_Rec_W_Req_ACK_Ret_ArbLOST_GenCALL) //General call
		{
			return 2;
		}
		else
		{
			continue;
		}
	}

}

u8 enTWI_SlaveWriteByte (u8 u8copy_Data)
{

	/* Load Data in Data register to be sent (Written) */
	TWDR = u8copy_Data;

	/* Start operation*/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1 << TWEA);

	/* Wait for TWINT Flag set. This indicates
	 * that the write byte has been
	 * transmitted
	 */
	while(!(TWCR & (1 << TWINT)));

	if (u8TWI_GetStatus() == STOP_REPEATED_CONDITION)
	{
		TWCR |= (1 << TWINT);		//clear the flag
		return -1;
	}

	if(u8TWI_GetStatus() == SLA_Data_Trans_ACK_Ret)
		return 0;

	if(u8TWI_GetStatus() == SLA_Data_Trans_NACK_Ret)
	{
		TWCR |= (1 << TWINT);		//clear the flag
		return -2;
	}

	if(u8TWI_GetStatus() == SLA_Last_Byte_Trans_ACK_Ret)
		return -3;
	else
		return -4;

}

u8 enTWI_SlaveReadByte (u8 *pu8copy_Data)     //read with send ACK
{
	/* Start operation*/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1 << TWEA);

	/* Wait for TWINT Flag set. This indicates
	 * that the raed byte has been
	 * received
	 */
	while(!(TWCR & (1 << TWINT)));

	if(u8TWI_GetStatus() == SLA_Data_Rec_ACK_Ret || u8TWI_GetStatus() == SLA_Data_Rec_ACK_Ret_GenCALL)
	{
		*pu8copy_Data = TWDR;
		return 0;
	}

	if(u8TWI_GetStatus() == SLA_Data_Rec_NACK_Ret || u8TWI_GetStatus() == SLA_Data_Rec_NACK_Ret_GenCALL)
	{
		*pu8copy_Data = TWDR;
		return 0;
	}

	if (u8TWI_GetStatus() == STOP_REPEATED_CONDITION)
	{
		TWCR |= (1 << TWINT);		//clear the flag
		return -1;
	}
	else
		return -2;


}

u8 u8TWI_GetStatus (void)
{
	u8 u8Local_Status = TWSR & Prescaler_Mask;
	return u8Local_Status;
}

void vTWI_StopCondition (void)
{
	/* Transmit STOP condition */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

	/*wait until stop condition is executed*/
	while (TWCR & (1 << TWSTO));
}

/******************************************************************************
 * !comment  :  ISR Function TWI.  							       *
 ******************************************************************************/
ISR(TWI)
{

}
