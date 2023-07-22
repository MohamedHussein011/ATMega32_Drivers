/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

/* Files Inclusion */

/* 1. User Defined Libraries */
#include "../../Library/STD_TYPE.h"
#include "../../Library/BIT_MATH.h"

/* 3. MCAL Files */
#include "../../MCAL/DIO/DIO_interface.h"

/* 4. HAL Files */
#include "Sevensegment_interface.h"

/* Numbers to be printed on SSD */
static uint8_t u8sev_seg[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void vSevensegment_Init(EN_PORT_t PortId)
{
	u8DIO_PortDir(PortId, DIO_OUTPUT);
}

void vSevensegment_Setnumber(EN_PORT_t PortId, EN_segment_t type, uint8_t u8Copy_number)
{
	switch (type){
	case cathode: u8DIO_PortVal(PortId, u8sev_seg[u8Copy_number]);   break;
	case anode:   u8DIO_PortVal(PortId, ~u8sev_seg[u8Copy_number]);  break;
	default:   break;
	}
}

void vSevensegment_OFF(EN_PORT_t PortId, EN_segment_t type)
{
	switch (type){
	case cathode: u8DIO_PortVal(PortId, DIO_LOW);   break;
	case anode:   u8DIO_PortVal(PortId, DIO_HIGH);  break;
	default:   break;
	}
}
