/*
 * RTC_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mhmd
 */

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

void Set_Time (u8 SECOND, u8 MINUTE, u8 HOUR);
void Set_Date (u8 DAY, u8 MONTH, u8 YEAR);

void Get_Time (u8* SECOND, u8* MINUTE, u8* HOUR);
void Get_Date (u8* DAY, u8* MONTH, u8* YEAR);

u8 decToBCD (u32 num);
u32 BCDtoDEC (u8 num);

#endif /* RTC_INTERFACE_H_ */
