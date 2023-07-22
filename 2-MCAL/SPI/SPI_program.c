/*
 * SPI_program.c
 *
 *  	Name: Mohamed Hussein
 *		Layer: MCAL
 * 		Version: V1.0 - 15/10/2021
 * 		Driver: SPI
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_private.h"
#include "SPI_configuration.h"
#include "SPI_registers.h"
#include "SPI_interface.h"

/* Global Pointer to function */
void (*SPI_STCCallBack)(void);     //Serial Transfer Complete Interrput


void vSPI_MasterInit(void)
{
	/* Data order to be transmitted */
#if Data_Order == LSB           // The LSB of the data word is transmitted first
	SET_BIT(SPCR,DORD);
#elif Data_Order == MSB         // The MSB of the data word is transmitted first
	CLR_BIT(SPCR,DORD);
#else
#error "wrong option for data order"
#endif

	/* SPI Clock Polarity Option */
#if Clock_polarity == IDLE_LOW       //leading Edge is Rising Edge & trailing Edge is Falling as IDLE state is LOW
	CLR_BIT(SPCR,CPOL);
#elif Clock_polarity == IDLE_HIGH	   //leading Edge is Falling Edge & trailing Edge is Rising as IDLE state is HIGH
	SET_BIT(SPCR,CPOL);
#else
#error "wrong option for Clock Polarity"
#endif

	/* SPI Clock Phase */
#if Clock_Phase == Sample_Setup        //leading Edge is Sample(receive) & trailing Edge is Setup(Send)
	CLR_BIT(SPCR,CPHA);
#elif Clock_Phase == Setup_Sample      //leading Edge is Setup(Send) & trailing Edge is Sample(receive)
	SET_BIT(SPCR,CPHA);
#else
#error "wrong option for Clock Phase"
#endif

	/* SPI Clock Rate */
#if Clock_Rate == Normal_DivBy_4
	CLR_BIT(SPCR,SPR1);
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPSR,SPI2X);
#elif Clock_Rate == Normal_DivBy_16
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPSR,SPI2X);
#elif Clock_Rate == Normal_DivBy_64
	SET_BIT(SPCR,SPR1);
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPSR,SPI2X);
#elif Clock_Rate == Normal_DivBy_128
	SET_BIT(SPCR,SPR1);
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPSR,SPI2X);
#elif Clock_Rate == Double_DivBy_2
	CLR_BIT(SPCR,SPR1);
	CLR_BIT(SPCR,SPR0);
	SET_BIT(SPSR,SPI2X);
#elif Clock_Rate == Double_DivBy_8
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPSR,SPI2X);
#elif Clock_Rate == Double_DivBy_32
	SET_BIT(SPCR,SPR1);
	CLR_BIT(SPCR,SPR0);
	SET_BIT(SPSR,SPI2X);
#elif Clock_Rate == Double_DivBy_64
	SET_BIT(SPCR,SPR1);
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPSR,SPI2X);
#else
#error "wrong option for Clock Rate"
#endif

	/* Select Master */
	SET_BIT(SPCR,MSTR);

	/* SPI Enable */
	SET_BIT(SPCR,SPE);
}

void vSPI_SlaveInit(void)
{
	/* Data order to be transmitted */
#if Data_Order == LSB           // The LSB of the data word is transmitted first
	SET_BIT(SPCR,DORD);
#elif Data_Order == MSB         // The MSB of the data word is transmitted first
	CLR_BIT(SPCR,DORD);
#else
#error "wrong option for data order"
#endif

	/* SPI Clock Polarity Option */
#if Clock_polarity == IDLE_LOW       //leading Edge is Rising Edge & trailing Edge is Falling as IDLE state is LOW
	CLR_BIT(SPCR,CPOL);
#elif Clock_polarity == IDLE_HIGH	   //leading Edge is Falling Edge & trailing Edge is Rising as IDLE state is HIGH
	SET_BIT(SPCR,CPOL);
#else
#error "wrong option for Clock Polarity"
#endif

	/* SPI Clock Phase */
#if Clock_Phase == Sample_Setup        //leading Edge is Sample(receive) & trailing Edge is Setup(Send)
	CLR_BIT(SPCR,CPHA);
#elif Clock_Phase == Setup_Sample      //leading Edge is Setup(Send) & trailing Edge is Sample(receive)
	SET_BIT(SPCR,CPHA);
#else
#error "wrong option for Clock Phase"
#endif
	/* Select Slave */
	CLR_BIT(SPCR,MSTR);

	/* SPI Enable */
	SET_BIT(SPCR,SPE);
}

uint8_t u8SPI_TransReceiveChar (uint8_t u8Copy_Char)
{
	/* load data in data register to be sent */
	SPDR = u8Copy_Char;

	/* Busy Wait polling till sending operation complete */
	while (GET_BIT(SPSR, SPIF) != 1 );

	/* Clear interrput flag */
	SET_BIT(SPSR,SPIF);

	return SPDR;
}

void vSPI_SendChar   (uint8_t u8Copy_Char)
{
	/*variable to hold data received*/
	uint8_t u8Local_Buffer = 0;

	/* Load data in Data Register to be sent */
	SPDR = u8Copy_Char;

	/* Busy Wait polling till sending operation complete */
	while (GET_BIT(SPSR, SPIF) != 1 );

	/* Clear interrput flag */
	SET_BIT(SPSR,SPIF);

	u8Local_Buffer = SPDR;
}

uint8_t u8SPI_ReceiveChar (uint8_t* pu8Copy_Char)
{
	uint8_t u8Local_ErrorState = OK;
	if(pu8Copy_Char == NULL)
		u8Local_ErrorState = NULLPOINTER;
	else
	{
		/*initialize the SPDR register with garbage value*/
		SPDR = 0xFF;

		/* Bust Wait polling till receive complete */
		while (GET_BIT(SPSR, SPIF) != 1 );

		/* Clear interrput flag */
		SET_BIT(SPSR,SPIF);

		*pu8Copy_Char = SPDR;
	}

	return u8Local_ErrorState;
}

/* Function To Enable SPI Interrput */
void vSPI_EnableInterrput (void)
{
	SET_BIT(SPCR,SPIE);
}
/* Function To Disable SPI Interrput */
void vSPI_DisableInterrput (void)
{
	CLR_BIT(SPCR,SPIE);
}
/* Function To Call SPI ISR */
void vSPI_STCSetCallBack (void (*pvCopy_ptr) (void))
{
	/* Assign the address to global to extend its lifetime */
	SPI_STCCallBack = pvCopy_ptr;
}

/******************************************************************************
 * !comment  :  ISR Function SPI.  							 			      *
 ******************************************************************************/
ISR(SPI_STC)
{
	if(SPI_STCCallBack != NULL)
		SPI_STCCallBack();

}
