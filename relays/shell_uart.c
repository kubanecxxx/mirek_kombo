/**
 * @file shell_uart.c
 * @author kubanec
 * @date 18.8.2012
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "string.h"
#include "stdlib.h"
#include "relays.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const SerialConfig cfg =
{ 9600, 0, 0, 0 };

static WORKING_AREA(shell_wa, 1024);

/* Private function prototypes -----------------------------------------------*/
static void cmd_gain(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_volume(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_mute(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_channel(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_loop(BaseSequentialStream *chp, int argc, char *argv[]);
/* Private functions ---------------------------------------------------------*/

static ShellCommand comms[] =
{
{ "gain", cmd_gain },
{ "volume", cmd_volume },
{ "mute", cmd_mute },
{ "channel", cmd_channel },
{ "loop", cmd_loop },
{ NULL, NULL } };

static ShellConfig shell_cfg =
{ (BaseSequentialStream *) &SD2, comms };

void shell_init(void)
{
#ifdef SHELL_TESTING
	palSetPadMode(GPIOA, 2, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#else
	//turn off txd
	palSetPadMode(GPIOA, 2, PAL_MODE_INPUT);
#endif
	palSetPadMode(GPIOA, 3, PAL_MODE_INPUT);

	sdStart(&SD2, &cfg);
	shellCreateStatic(&shell_cfg, &shell_wa, sizeof(shell_wa), NORMALPRIO);
}

static void cmd_gain(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	(void) argc;

	uint8_t number = atoi(argv[0]);

	if (number > 0 && number < 5)
		rel_set_gain(number);
}

static void cmd_volume(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	(void) argc;

	uint8_t number = atoi(argv[0]);

	if (number > 0 && number < 5)
		rel_set_volume(number);
}

static void cmd_mute(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	(void) argc;

	if (strcmp("on", argv[0]) == 0)
		rel_mute();
	else if (strcmp("off", argv[0]) == 0)
		rel_unmute();
}

static void cmd_channel(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	(void) argc;

	if (strcmp("high", argv[0]) == 0)
		rel_inputHigh();
	else if (strcmp("low", argv[0]) == 0)
		rel_inputLow();
}

static void cmd_loop(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	(void) argc;

	if (strcmp("on", argv[0]) == 0)
		rel_loopOn();
	else if (strcmp("off", argv[0]) == 0)
		rel_loopOff();
}
