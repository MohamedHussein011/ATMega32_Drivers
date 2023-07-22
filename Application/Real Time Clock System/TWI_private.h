/*
 * TWI_private.h
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: TWI - Two-wire Serial Interface (I2C)
 */

#ifndef _TWI_PRIVATE_H
#define _TWI_PRIVATE_H

/* Macros to define Status Codes for Master Transmitter & Receiver Mode */
/* Transmitter Mode */
#define Start_Condition                     0x08             //A START condition has been transmitted
#define Repeated_Start_Condition            0x10             //A repeated START condition has been transmitted
#define SLA_W_ACK_Rec                       0x18             //SLA+W has been transmitted & ACK has been received
#define SLA_W_NACK_Rec                      0x20             //SLA+W has been transmitted & NOT ACK has been received
#define Data_Trans_ACK_Rec                  0x28             //Data byte has been transmitted & ACK has been received
#define Data_Trans_NACK_Rec                 0x30             //Data byte has been transmitted & NOT ACK has been received

/* Receiver Mode */
#define SLA_R_ACK_Rec                       0x40             //SLA+R has been transmitted & ACK has been received
#define SLA_R_NACK_Rec                      0x48             //SLA+R has been transmitted & NOT ACK has been received
#define Data_Rec_ACK_Ret                    0x50             //Data byte has been received & ACK has been returned
#define Data_Rec_NACK_Ret                   0x58             //Data byte has been received & NOT ACK has been returned

/*Slave receiver mode*/
#define SLA_Rec_W_Req_ACK_Ret               0x60             //Own SLA+W has been received with write request & ACK has been returned
#define SLA_Rec_W_Req_ACK_Ret_ArbLOST       0x68             //Own SLA+W has been received with write request & ACK has been returned, arbitration lost as master
#define SLA_Rec_W_Req_ACK_Ret_GenCALL       0x70             //Own SLA+W has been received with write request & ACK has been returned, general call
#define SLA_Rec_W_Req_ACK_Ret_ArbLOST_GenCALL   0x78             //Own SLA+W has been received with write request & ACK has been returned, arbitration lost as master, general call
#define SLA_Data_Rec_ACK_Ret                0x80             //data has been received & ACK has been returned
#define SLA_Data_Rec_NACK_Ret               0x88             //data has been received & NACK has been returned
#define SLA_Data_Rec_ACK_Ret_GenCALL        0x90             //data has been received & ACK has been returned
#define SLA_Data_Rec_NACK_Ret_GenCALL       0x98             //data has been received & NACK has been returned
#define STOP_REPEATED_CONDITION 			0xA0

/*Slave Transmitter mode*/
#define SLA_Rec_R_Req_ACK_Ret               0xA8             //Own SLA+R has been received with read request & ACK has been returned
#define SLA_Rec_R_Req_ACK_Ret_ArbLOST       0xB0             //Own SLA+R has been received with read request & ACK has been returned, arbitration lost as master
#define SLA_Data_Trans_ACK_Ret              0xB8             //data has been transmitted & ACK has been received
#define SLA_Data_Trans_NACK_Ret             0xC0             //data has been transmitted & NACK has been received
#define SLA_Last_Byte_Trans_ACK_Ret         0xC8             //Last byte has been transmitted & ACK has been received

/******************************************************************************
 * !comment : Select TWI Bit Rate Prescaler option:  		 	               *
 *           1: Prescaler_1                                                      *
 *           2: Prescaler_4                                                      *
            3: Prescaler_16                                                     *
            4: Prescaler_64                                         			*
 ******************************************************************************/
#define Prescaler_Mask              0xF8
#define Prescaler_1                 0
#define Prescaler_4                 1
#define Prescaler_16                2
#define Prescaler_64                3

/******************************************************************************
 * !comment : Select Enable or Disable ACK option:  		 	               *
 *           1: ACK_Enable                                                      *
 *           2: ACK_Disable                                                      *
 ******************************************************************************/
#define ACK_Enable       1
#define ACK_Disable      2

#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
