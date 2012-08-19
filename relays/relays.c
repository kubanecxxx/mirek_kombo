/**
 * @file relay.c
 * @author kubanec
 * @date 14.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/

#include "relays.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @todo dodělat podporu pro relé na přepinání smyčky + ledky na kanály
 */

void rel_init(void)
{
	//turn off jtag, just swd will works
	AFIO ->MAPR |= 0b010 << 24;

	palSetGroupMode(GPIOC, 0b111, 13, PAL_MODE_OUTPUT_PUSHPULL);
	palSetGroupMode(GPIOB, 0b110111, 3, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 11, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL);

	rel_unmute();
	rel_set_gain(1);
	rel_set_volume(1);
	rel_inputHigh();
	rel_loopOn();
}

void _rel_set_channel(bool_t channel, uint8_t pot)
{
	bool_t prev = rel_getMute();

	if (prev == FALSE)
	{
		rel_mute();
		chThdSleepMilliseconds(2);
	}

	if (channel == TRUE)
	{
		switch (pot)
		{
		case 3:
			_rel_vol1_clear;
			_rel_vol3_clear;
			_rel_vol2_clear;
			break;
		case 2:
			_rel_vol1_clear;
			_rel_vol3_set;
			_rel_vol2_set;
			break;
		case 4:
			_rel_vol1_set;
			_rel_vol2_clear;
			_rel_vol3_clear;
			break;
		case 1:
			_rel_vol1_set;
			_rel_vol2_set;
			_rel_vol3_set;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (pot)
		{
		case 3:
			_rel_gain1_clear;
			_rel_gain3_clear;
			_rel_gain2_clear;
			break;
		case 2:
			_rel_gain1_clear;
			_rel_gain3_set;
			_rel_gain2_set;
			break;
		case 4:
			_rel_gain1_set;
			_rel_gain2_clear;
			_rel_gain3_clear;
			break;
		case 1:
			_rel_gain1_set;
			_rel_gain2_set;
			_rel_gain3_set;
			break;
		default:
			break;
		}
	}

	if (prev == FALSE)
	{
		chThdSleepMilliseconds(2);
		rel_unmute();
	}

}

#ifdef RELAY_TESTING
#define TIME 1000

void rel_test(void)
{
	uint8_t i;

	rel_unmute();
	rel_inputHigh();
	_rel_vol1_clear;
	_rel_vol2_clear;
	_rel_vol3_clear;
	_rel_gain1_clear;
	_rel_gain2_clear;
	_rel_gain3_clear;

	chThdSleepMilliseconds(TIME);
	chThdSleepMilliseconds(TIME);

	rel_mute();
	chThdSleepMilliseconds(TIME);
	rel_unmute();
	chThdSleepMilliseconds(TIME);

	rel_inputHigh();
	chThdSleepMilliseconds(TIME);
	rel_inputLow();
	chThdSleepMilliseconds(TIME);

	_rel_vol1_set;
	_rel_vol2_set;
	_rel_vol3_set;
	chThdSleepMilliseconds(TIME);
	_rel_vol1_clear;
	_rel_vol2_clear;
	_rel_vol3_clear;
	chThdSleepMilliseconds(TIME);

	for (i = 1; i < 5; i++)
	{
		rel_set_channel(TRUE, i);
		chThdSleepMilliseconds(TIME);

		_rel_vol1_clear;
		_rel_vol2_clear;
		_rel_vol3_clear;
		chThdSleepMilliseconds(TIME);

		rel_set_channel(TRUE, i);
		chThdSleepMilliseconds(TIME);

		_rel_vol1_set;
		_rel_vol2_set;
		_rel_vol3_set;
		chThdSleepMilliseconds(TIME);
	}

	_rel_gain1_set;
	_rel_gain2_set;
	_rel_gain3_set;
	chThdSleepMilliseconds(TIME);
	_rel_gain1_clear;
	_rel_gain2_clear;
	_rel_gain3_clear;
	chThdSleepMilliseconds(TIME);

	for (i = 1; i < 5; i++)
	{

		rel_set_channel(FALSE, i);
		chThdSleepMilliseconds(TIME);

		_rel_gain1_set;
		_rel_gain2_set;
		_rel_gain3_set;
		chThdSleepMilliseconds(TIME);

		rel_set_channel(FALSE, i);
		chThdSleepMilliseconds(TIME);

		_rel_gain1_clear;
		_rel_gain2_clear;
		_rel_gain3_clear;
		chThdSleepMilliseconds(TIME);
	}
}
#endif
