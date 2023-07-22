/*
 * Mapping_program.c
 *
 *  	Name: Mohamed Hussein
 * 		Version: V1.0 - 01/10/2021
 */

#include "STD_TYPES.h"
#include "Mapping_interface.h"

s32 s32Map (s32 InputMin, s32 InputMax, s32 OutputMin, s32 OutputMax, s32 InputValue)
{
	/*y is output, x is input
	 * (y-y1)/(x-x1) = (y2-y1)/(x2-x1)
	 * */
	s32 s32Local_OutputDiference = OutputMax - OutputMin;
	s32 s32Local_InputDiference = InputMax - InputMin;
	s32 s32Local_InputCalculation = InputValue - InputMin;

	s32 s32Local_Output = (s32) ((s32Local_OutputDiference * s32Local_InputCalculation) / s32Local_InputDiference);
	s32Local_Output += OutputMin;

	if(s32Local_Output <= OutputMin)
		return OutputMin;
	else if(s32Local_Output >= OutputMax)
		return OutputMax;
	else
		return s32Local_Output;

}
