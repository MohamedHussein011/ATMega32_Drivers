/*
 * TWI_registers.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: TWI - Two-wire Serial Interface (I2C)
 */

#ifndef _TWI_REGISTERS_H
#define _TWI_REGISTERS_H

/******************************************************************************
 * !comment : TWI Bit Rate Register (TWBR) & Bits Definition.                     *
 ******************************************************************************/
#define TWBR    *((volatile u8 *)0x20)

/******************************************************************************
 * !comment : TWI Control Register (TWCR) & Bits Definition.                     *
 ******************************************************************************/
#define TWCR    *((volatile u8 *)0x56)
#define TWINT    7          //TWI Interrupt Flag
#define TWEA     6          //TWI Enable Acknowledge Bit
#define TWSTA    5          //TWI START Condition Bit
#define TWSTO    4          //TWI STOP Condition Bit
#define TWWC     3          //TWI Write Collision Flag
#define TWEN     2          //TWI Enable Bit
/* Bit 1 - Reserved for future use */
#define TWIE     0          //TWI Interrupt Enable

/******************************************************************************
 * !comment : TWI Status Register (TWSR) & Bits Definition.                     *
 ******************************************************************************/
#define TWSR    *((volatile u8 *)0x21)
#define TWS7    7          //TWI Status
#define TWS6    6          //TWI Status
#define TWS5    5          //TWI Status
#define TWS4    4          //TWI Status
#define TWS3    3          //TWI Status
/* Bit 2 - Reserved for future use */
#define TWPS1   1          //TWI Prescaler Bits
#define TWPS0   0          //TWI Prescaler Bits

/******************************************************************************
 * !comment : TWI Data Register (TWDR) Definition.                     *
 ******************************************************************************/
#define TWDR    *((volatile u8 *)0x23)

/******************************************************************************
 * !comment : TWI (Slave) Address Register (TWAR) Definition.                     *
 ******************************************************************************/
#define TWAR    *((volatile u8 *)0x22)
#define TWGCE    0    //TWI General Call Recognition Enable Bit


#endif /* MCAL_TWI_TWI_REGISTERS_H_ */
