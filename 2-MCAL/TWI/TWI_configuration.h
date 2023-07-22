/*
 * TWI_configuration.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: TWI - Two-wire Serial Interface (I2C)
 */

#ifndef _TWI_CONFIGURATION_H
#define _TWI_CONFIGURATION_H

/*MC clock frequency*/
#define MC_ClockFreq                  8000000UL

/*SCL Frequency you need*/
#define SCL_Freq                      400000UL      //400Kbps

/******************************************************************************
 * !comment : Select TWI Bit Rate Prescaler option:  		 	               *
 *           1: Prescaler_1                                                      *
 *           2: Prescaler_4                                                      *
            3: Prescaler_16                                                     *
            4: Prescaler_64                                         			*
 ******************************************************************************/

#define TWI_PrescalerSelect             Prescaler_1

/******************************************************************************
 * !comment : Select Enable or Disable ACK option:  		 	               *
 *           1: ACK_Enable                                                      *
 *           2: ACK_Disable                                                      *
 ******************************************************************************/
#define ACK_Bit       ACK_Disable

#endif /* MCAL_TWI_TWI_CONFIGURATION_H_ */
