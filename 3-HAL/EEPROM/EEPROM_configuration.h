/*
 * EEPROM_configuration.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: HAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: EEPROM - ATMEL 24C08
 */

#ifndef _EEPROM_CONFIGURATION_H
#define _EEPROM_CONFIGURATION_H

/******************************************************************************
 * !comment : Select A2A1A0 connection for AT24C01 option:  		 	            *
 *           1: 1      if connected to VCC                                      *
 *           2: 0      if connected to GND                                      *
 *         8 EEPROMs on the Bus
 ******************************************************************************/
#define C01_A2PIN            1
#define C01_A1PIN            1
#define C01_A0PIN            1

/******************************************************************************
 * !comment : Select A2A1A0 connection for AT24C02 option:  		 	            *
 *           1: 1      if connected to VCC                                      *
 *           2: 0      if connected to GND                                      *
 *          8 EEPROMs on the Bus
 ******************************************************************************/
#define C02_A2PIN            1
#define C02_A1PIN            1
#define C02_A0PIN            1

/******************************************************************************
 * !comment : Select A2A1 connection for AT24C04 option:  		 	            *
 *           1: 1      if connected to VCC                                      *
 *           2: 0      if connected to GND                                      *
 *          4 EEPROMs on the Bus
 *          A0 not connected (it doesn't matter if you connect to VCC or GND)
 ******************************************************************************/
#define C04_A2PIN            1
#define C04_A1PIN            1

/******************************************************************************
 * !comment : Select A2 connection for AT24C08 option:  		 	            *
 *           1: 1      if connected to VCC                                      *
 *           2: 0      if connected to GND                                      *
 *           2 EEPROMs on the Bus
 *           A1 & A0 not connected (it doesn't matter if you connect to VCC or GND)
 ******************************************************************************/
#define C08_A2PIN            1

/******************************************************************************
 * !comment :  AT24C16 :  		 	            *
 *           1 EEPROMs on the Bus
 *           A2 & A1 & A0 not connected (it doesn't matter if you connect to VCC or GND)
 ******************************************************************************/

/******************************************************************************
 * !comment : Select your EEPROM option:  		 	            *
 *           1: AT24C01                                      *
 *           2: AT24C02                                      *
 *           3: AT24C04
 *           4: AT24C08
 *           5: AT24C16
 ******************************************************************************/
#define EEPROM_type               AT24C08

#endif /* HAL_EEPROM_EEPROM_CONFIGURATION_H_ */
