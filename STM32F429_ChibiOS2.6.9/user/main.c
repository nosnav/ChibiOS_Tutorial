#include "ch.h"
#include "hal.h"
#include "test.h"

#include "chprintf.h"

static WORKING_AREA(waThreadLED_RED, 128);
static msg_t ThreadLED_RED(void *arg) 
{
	(void)arg;
	chRegSetThreadName("blinker1");
	while (TRUE) 
	{
		palClearPad(GPIOG, GPIOG_LED4_RED);
		chThdSleepMilliseconds(500);
		palSetPad(GPIOG, GPIOG_LED4_RED);
		chThdSleepMilliseconds(500);
	}
}

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThreadLED_GREEN, 128);
static msg_t ThreadLED_GREEN(void *arg) 
{
	(void)arg;
	chRegSetThreadName("blinker2");
	while (TRUE) 
	{
		palClearPad(GPIOG, GPIOG_LED3_GREEN);
		chThdSleepMilliseconds(1000);
		palSetPad(GPIOG, GPIOG_LED3_GREEN);
		chThdSleepMilliseconds(1000);
	}
}


int main(void) 
{
	uint8_t i = 0;
	halInit();
	chSysInit();
	
	sdStart(&SD1, NULL);
	palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));
	
	chprintf((BaseSequentialStream *)&SD1, "ChibiOS STM32F429\r\n");
	
	chThdCreateStatic(waThreadLED_RED, sizeof(waThreadLED_RED),NORMALPRIO + 10, ThreadLED_RED, NULL);
	chThdCreateStatic(waThreadLED_GREEN, sizeof(waThreadLED_GREEN),NORMALPRIO + 10, ThreadLED_GREEN, NULL);
	
	while (TRUE) 
	{
		chprintf((BaseSequentialStream *)&SD1, "Example: %d\r\n", i++);
		chThdSleepMilliseconds(250);
	}
}
