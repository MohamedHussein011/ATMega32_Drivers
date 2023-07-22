/*
 * SPI_configuration.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: SPI
 */

#ifndef _SPI_CONFIGURATION_H
#define _SPI_CONFIGURATION_H

/******************************************************************************
 * !comment : Select SPI Data Order option:  			         	               *
 *           1: LSB                                                              *
 *           2: MSB                                                              *
 ******************************************************************************/

#define Data_Order             MSB

/******************************************************************************
 * !comment : Select SPI Clock Polarity Option (Leading_Trailing) Edge:  	      *
 *            1: IDLE_HIGH                                                   *
 *            2: IDLE_LOW                                                   *
 ******************************************************************************/
#define Clock_polarity        IDLE_HIGH

/******************************************************************************
 * !comment : Select SPI Clock Phase Option (Leading_Trailing) Edge:  	      *
 *            1: Sample_Setup                                                   *
 *            2: Setup_Sample                                                  *
 ******************************************************************************/
#define Clock_Phase            Sample_Setup

/******************************************************************************
 * !comment : Select SPI Clock Rate Option :  	      *
 *          1: Normal_DivBy_4                               *
 *          2: Normal_DivBy_16                              *
 *		   3: Normal_DivBy_64                              *
 *		   4: Normal_DivBy_128                             *
 *		   5: Double_DivBy_2                               *
 *		   6: Double_DivBy_8                               *
 *		   7: Double_DivBy_32                              *
 *		   8: Double_DivBy_64                              *
 ******************************************************************************/

#define Clock_Rate          Normal_DivBy_4



#endif /* MCAL_SPI_SPI_CONFIGURATION_H_ */
