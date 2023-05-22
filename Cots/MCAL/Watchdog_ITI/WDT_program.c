#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"


void WDT_voidEnable(void)
{
	SET_BIT(WDCTR, WDE);
}

void WDT_SetSleepTime(u8 Copy_u8SleepTime)
{
	WDCTR &= 0b11111000;
	WDCTR |= Copy_u8SleepTime;
}

void WDT_voidDisable(void)
{
	/*writing 1 at bit 3 and 4 at the same operation*/
	WDCTR |= 0b00011000;

	/*writing 1 at bit number 3*/
	WDCTR = 0;


}
