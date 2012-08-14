/**
 * @file relay.c
 * @author kubanec
 * @date 14.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "relays.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define REL1_VOL (GPIOC,14)
#define REL2_VOL (GPIOC,13)
#define REL3_VOL (GPIOB,8)

#define REL1_GAIN (GPIOB,7)
#define REL2_GAIN (GPIOB,5)
#define REL3_GAIN (GPIOB,4)

#define REL_MUTE  (GPIOC,15)
#define REL_INPUT (GPIOB,3)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void relays_init(void)
{
	palSetGroupMode(GPIOC, 0b111, 13, PAL_MODE_OUTPUT_PUSHPULL);
	palSetGroupMode(GPIOB, 0b110111, 3, PAL_MODE_OUTPUT_PUSHPULL);
}

void _set_channel(bool_t channel, uint8_t pot)
{
	if (channel = TRUE)
	{
		switch (pot)
		{
		case 1:
			palClearPad REL1_VOL;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
	else
	{

	}
}
