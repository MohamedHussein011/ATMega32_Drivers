/*
 * EEPROM_interface.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: EEPROM - ATMEL 24C08
 */

#ifndef _EEPROM_INTERFACE_H
#define _EEPROM_INTERFACE_H

/*this driver for ATMEL AT24C01 / AT24C02 / AT24C04 / AT24C08 / AT24C16 EEPROM*/
//Addressed range for AT24C01: 0 to 127  (128 Bytes)
//Addressed range for AT24C02: 0 to 255  (256 Bytes)
//Addressed range for AT24C04: 0 to 511  (512 Bytes)
//Addressed range for AT24C08: 0 to 1023  (1024 Bytes)
//Addressed range for AT24C16: 0 to 2047  (2048 Bytes)

void vEEPROM_SendDataByte (uint8_t u8Copy_Data, uint16_t u16Copy_Address);
void vEEPROM_ReadDataByte (uint8_t *pu8Copy_Data, uint16_t u16Copy_Address);

void vEEPROM_SendString (char *pu8Copy_Data, uint16_t u16Copy_Address, uint8_t u8Copy_Size);
void vEEPROM_ReadString (char *pu8Copy_Data, uint16_t u16Copy_Address, uint8_t u8Copy_Size);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
