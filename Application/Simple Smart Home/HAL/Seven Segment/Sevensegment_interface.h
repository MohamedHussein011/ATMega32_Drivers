/*
 * Name: Mohamed Hussein
 * Layer: HAL
 * Version: V1.0 - 15/10/2021
 *
 */

#ifndef _SEVENSEGMENT_INTERFACE_H
#define _SEVENSEGMENT_INTERFACE_H


typedef enum {
	cathode,
	anode
}EN_segment_t;

/* Fucntions Prototype */
void vSevensegment_Init(EN_PORT_t PortId);

void vSevensegment_Setnumber(EN_PORT_t PortId, EN_segment_t type, uint8_t u8Copy_number);

void vSevensegment_OFF(EN_PORT_t PortId, EN_segment_t type);

#endif
