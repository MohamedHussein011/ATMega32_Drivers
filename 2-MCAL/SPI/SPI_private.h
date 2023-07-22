/*
 * SPI_private.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: SPI
 */

#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H

/******************************************************************************
 * !comment : Select SPI Data Order option:  			         	               *
 *           1: LSB                                                              *
 *           2: MSB                                                              *
 ******************************************************************************/

#define LSB             1
#define MSB             2


/******************************************************************************
 * !comment : Select SPI Clock Polarity Option (Leading_Trailing) Edge:  	      *
 *            1: IDLE_HIGH                                                   *
 *            2: IDLE_LOW                                                   *
 ******************************************************************************/
#define IDLE_HIGH         1
#define IDLE_LOW          2

/******************************************************************************
 * !comment : Select SPI Clock Phase Option (Leading_Trailing) Edge:  	      *
 *            1: Sample_Setup                                                   *
 *            2: Setup_Sample                                                  *
 ******************************************************************************/
#define Sample_Setup            1
#define Setup_Sample            2

/******************************************************************************
 * !comment : Select SPI Clock Rate Option :  	      *
 *            1: Normal_DivBy_4                               *
 *            2: Normal_DivBy_16                              *
 *		   3: Normal_DivBy_64                              *
 *		   4: Normal_DivBy_128                             *
 *		   5: Double_DivBy_2                               *
 *		   6: Double_DivBy_8                               *
 *		   7: Double_DivBy_32                              *
 *		   8: Double_DivBy_64                              *
 ******************************************************************************/

#define Normal_DivBy_4              1
#define Normal_DivBy_16             2
#define Normal_DivBy_64             3
#define Normal_DivBy_128            4
#define Double_DivBy_2              5
#define Double_DivBy_8              6
#define Double_DivBy_32             7
#define Double_DivBy_64             8


#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
