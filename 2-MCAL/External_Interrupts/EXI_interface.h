/*
 * Name: Mohamed Hussein 
 * Layer: MCAL
 * Version: V1.0 - 15/10/2021
 * Driver: External Interrupts
 */
 
 
#ifndef _EXI_INTERFACE_H
#define _EXI_INTERFACE_H

/******************************************************************************
* !comment : Select Interrupt Sense Control option:  		 	               *
*           1: LOW_LEVEL                                                     *
*           2: ON_CHANGE                                                     *
            3: FALLING_EDGE                                                     *
            4: RISING_EDGE                                         			*
******************************************************************************/

#define LOW_LEVEL        1
#define ON_CHANGE        2
#define FALLING_EDGE     3
#define RISING_EDGE      4

/******************************************************************************
* !comment : Select Interrupt Sense Control option:  		 	               *
*           1: INT0                                                     *
*           2: INT1                                                     *
            3: INT2                                                     *
******************************************************************************/

#define External_INT0        1
#define External_INT1        2
#define External_INT2        3

/*External Interrupts sources*/
#define External_Interrupt0           0
#define External_Interrupt1           1
#define External_Interrupt2           2

/* Fucntions Prototype */
void vEXI_InitINT0(void);    /* Pin D2 */
void vEXI_InitINT1(void);    /* Pin D3 */
void vEXI_InitINT2(void);    /* Pin B2 */

u8 u8EXI_INT0SetSenseControl (u8 u8Copy_SenseControl);
u8 u8EXI_INT1SetSenseControl (u8 u8Copy_SenseControl);
u8 u8EXI_INT2SetSenseControl (u8 u8Copy_SenseControl);

u8 u8EXI_EnableInterrupt (u8 u8Copy_InterruptID);
u8 u8EXI_DisableInterrupt (u8 u8Copy_InterruptID);

/* Set Callback Function for all  interrupt sources*/
u8 u8EXI_SetCallback (void (*pvCopy_Function) (void), u8 u8Copy_InerruptSource);


#endif 
