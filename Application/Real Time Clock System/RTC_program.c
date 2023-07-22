/*
 * RTC_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mhmd
 */

#include "STD_TYPES.h"

#include "TWI_interface.h"

#include "LCD_interface.h"

#include "RTC_interface.h"
#include "RTC_config.h"

#define DS3232_ADDRESS			0xD0


u8 RTC_HOUR = RTC_HOUR_SET;
u8 RTC_MINUTE = RTC_MINUTE_SET;
u8 RTC_SECOND = RTC_SECOND_SET;
u8 RTC_YEAR = RTC_YEAR_SET;
u8 RTC_MONTH = RTC_MONTH_SET;
u8 RTC_DAY = RTC_DAY_SET;

u8 decToBCD (u32 num)
{
	return (u8)( (num/10*16) + (num%10) );
}

u32 BCDtoDEC (u8 num)
{
	return (u32)( (num/16*10) + (num%16) );
}

void Set_Time (u8 SECOND, u8 MINUTE, u8 HOUR)
{
	u8 sec = decToBCD(SECOND);
	u8 min = decToBCD(MINUTE);
	u8 hou = decToBCD(HOUR);

	enTWI_StartCondition();
	enTWI_SendSlaveAddWithWrite(DS3232_ADDRESS);
	enTWI_MatserWriteByte(0x00);

	enTWI_MatserWriteByte(sec);

	enTWI_MatserWriteByte(min);

	enTWI_MatserWriteByte(hou);

	vTWI_StopCondition();
}

void Set_Date (u8 DAY, u8 MONTH, u8 YEAR)
{
	u8 day = decToBCD(DAY);
	u8 mon = decToBCD(MONTH);
	u8 year = decToBCD(YEAR);

	enTWI_StartCondition();
	enTWI_SendSlaveAddWithWrite(DS3232_ADDRESS);
	enTWI_MatserWriteByte(0x04);

	enTWI_MatserWriteByte(day);

	enTWI_MatserWriteByte(mon);

	enTWI_MatserWriteByte(year);

	vTWI_StopCondition();
}

void Get_Time (u8* SECOND, u8* MINUTE, u8* HOUR)
{
	u8 sec = 0, min = 0, hou = 0;

	enTWI_StartCondition();
	enTWI_SendSlaveAddWithWrite(DS3232_ADDRESS);
	enTWI_MatserWriteByte(0x00);
	enTWI_RepeatedStart();
	enTWI_SendSlaveAddWithRead(DS3232_ADDRESS);
	enTWI_MasterReadByteACK(&sec);
	enTWI_MasterReadByteACK(&min);
	enTWI_MasterReadByteNACK(&hou);
	vTWI_StopCondition();

	*SECOND = BCDtoDEC(sec);
	*MINUTE = BCDtoDEC(min);
	*HOUR = BCDtoDEC(hou);
}

void Get_Date (u8* DAY, u8* MONTH, u8* YEAR)
{
	u8 day = 0, mon = 0, year = 0;

	enTWI_StartCondition();
	enTWI_SendSlaveAddWithWrite(DS3232_ADDRESS);
	enTWI_MatserWriteByte(0x04);
	enTWI_RepeatedStart();
	enTWI_SendSlaveAddWithRead(DS3232_ADDRESS);
	enTWI_MasterReadByteACK(&day);
	enTWI_MasterReadByteACK(&mon);
	enTWI_MasterReadByteNACK(&year);
	vTWI_StopCondition();

	*DAY = BCDtoDEC(day);
	*MONTH = BCDtoDEC(mon);
	*YEAR = BCDtoDEC(year);
}

