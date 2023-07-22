/*
 * User_Functions.h
 *
 *  	Created on: 24/08/2022
 *      Author: Mohamed Hussein
 *      Layer: Library
 */

#ifndef _USER_FUNCTIONS_H
#define _USER_FUNCTIONS_H

void ConvertToString(char* Copy_String, s32 s32Copy_Number);
s32 ConvertToint(const char* Copy_String);

u8 StringCompare(const char* pu8Copy_String1, const char* pu8Copy_String2);
u8 StringLength(const char* pu8Copy_String);
void StringReset(char* pu8Copy_String);

#endif /* LIBRARY_CONVERSION_FUNCTION_H_ */
