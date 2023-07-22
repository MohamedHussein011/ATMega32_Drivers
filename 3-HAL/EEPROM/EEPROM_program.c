/*
 * EEPROM_program.c
 *
 *  	Name: Mohamed Hussein
 *		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: EEPROM - ATMEL 24C08
 */
#include "../../Library/STD_TYPE.h"

#include "../../MCAL/TWI/TWI_interface.h"

#include "EEPROM_private.h"
#include "EEPROM_configuration.h"
#include "EEPROM_interface.h"

void vEEPROM_SendDataByte (uint8_t u8Copy_Data, uint16_t u16Copy_Address)
{
	/* Send Start Condition for operation */
	enTWI_StartCondition();
	/* Send slave address with write */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithWrite(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithWrite(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithWrite(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithWrite(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithWrite(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif

	/* Send Address of memory location */
	enTWI_MatserWriteByte((uint8_t)u16Copy_Address);
	/* Send Data */
	enTWI_MatserWriteByte(u8Copy_Data);
	/* Stop condition */
	vTWI_StopCondition();
}
void vEEPROM_ReadDataByte (uint8_t *pu8Copy_Data, uint16_t u16Copy_Address)
{
	/* Send Start Condition for operation */
	enTWI_StartCondition();
	/* Send slave address with write */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithWrite(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithWrite(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithWrite(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithWrite(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithWrite(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif
	/* Send Address of memory location */
	enTWI_MatserWriteByte((uint8_t)u16Copy_Address);
	/* Send Repeated Start */
	enTWI_RepeatedStart();
	/* Send slave address with read */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithRead(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithRead(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithRead(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithRead(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithRead(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif
	/* Read Data */
	enTWI_MasterReadByteWithACK(pu8Copy_Data);
	/* Stop condition */
	vTWI_StopCondition();
}

void vEEPROM_SendString (char *pu8Copy_Data, uint16_t u16Copy_Address, uint8_t u8Copy_Size)
{
	uint8_t u8Local_Counter = 0;

	/* Send Start Condition for operation */
	enTWI_StartCondition();
	/* Send slave address with write */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithWrite(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithWrite(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithWrite(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithWrite(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithWrite(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif
	/* Send Address of memory location */
	enTWI_MatserWriteByte((uint8_t)u16Copy_Address);
	while(u8Local_Counter < u8Copy_Size)
	{
		/* Send Data */
		enTWI_MatserWriteByte(pu8Copy_Data[u8Local_Counter]);
		u8Local_Counter++;
	}
	/* Stop condition */
	vTWI_StopCondition();
}
void vEEPROM_ReadString (char *pu8Copy_Data, uint16_t u16Copy_Address, uint8_t u8Copy_Size)
{
	uint8_t u8Local_Counter = 0;

	/* Send Start Condition for operation */
	enTWI_StartCondition();
	/* Send slave address with write */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithWrite(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithWrite(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithWrite(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithWrite(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithWrite(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif
	/* Send Address of memory location */
	enTWI_MatserWriteByte((uint8_t)u16Copy_Address);
	/* Send Repeated Start */
	enTWI_RepeatedStart();
	/* Send slave address with read */
#if EEPROM_type == AT24C01
	enTWI_SendSlaveAddWithRead(0x50 | (C01_A2PIN << 2) | (C01_A1PIN << 1) | (C01_A0PIN));
#elif EEPROM_type == AT24C02
	enTWI_SendSlaveAddWithRead(0x50 | (C02_A2PIN << 2) | (C02_A1PIN << 1) | (C02_A0PIN));
#elif EEPROM_type == AT24C04
	enTWI_SendSlaveAddWithRead(0x50 | (C04_A2PIN << 2) | (C04_A1PIN << 1) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C08
	enTWI_SendSlaveAddWithRead(0x50 | (C08_A2PIN << 2) | (u16Copy_Address >> 8));
#elif EEPROM_type == AT24C16
	enTWI_SendSlaveAddWithRead(0x50 | (u16Copy_Address >> 8));
#else
#error "Wrong Option"
#endif
	while(u8Local_Counter < u8Copy_Size)
	{
		/* Read Data */
		enTWI_MasterReadByteWithACK(&pu8Copy_Data[u8Local_Counter]);
		u8Local_Counter++;
	}
	/* Stop condition */
	vTWI_StopCondition();
}
