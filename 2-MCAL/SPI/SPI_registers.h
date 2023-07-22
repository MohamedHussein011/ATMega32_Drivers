/*
 * SPI_registers.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: SPI
 */

#ifndef _SPI_REGISTERS_H
#define _SPI_REGISTERS_H

/******************************************************************************
 * !comment : SPI Control Register (SPCR) & Bits Definition.                     *
 ******************************************************************************/
#define SPCR    *((volatile u8 *)0x2D)
#define SPIE    7          //SPI Interrupt Enable
#define SPE     6          //SPI Enable
#define DORD    5          //Data Order
#define MSTR    4          //Master/Slave Select
#define CPOL    3          //Clock Polarity
#define CPHA    2          //Clock Phase
#define SPR1    1          //SPI Clock Rate Select 1
#define SPR0    0          //SPI Clock Rate Select 0

/******************************************************************************
 * !comment : SPI Status Register (SPSR) & Bits Definition.                     *
 ******************************************************************************/
#define SPSR    *((volatile u8 *)0x2E)
#define SPIF            7         //SPI Interrupt Flag
#define WCOL            6         //Write COLlision Flag
/* Bit 5 .. 1 reserved */
#define SPI2X           0         //Double SPI Speed Bit

/******************************************************************************
 * !comment : SPI Data Register (SPDR) Definition.                     *
 ******************************************************************************/
#define SPDR    *((volatile u8 *)0x2F)



#endif /* MCAL_SPI_SPI_REGISTERS_H_ */
