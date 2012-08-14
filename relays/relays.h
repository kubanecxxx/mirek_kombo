/**
 * @file relays.h
 * @author kubanec
 * @date 14.8.2012
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RELAYS_H_
#define RELAYS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define REL1_GAIN (GPIOB,7)
#define REL2_GAIN (GPIOB,5)
#define REL3_GAIN (GPIOB,4)

#define REL_MUTE  (GPIOC,15)
#define REL_INPUT (GPIOB,3)
/* Exported functions --------------------------------------------------------*/

#define _rel_vol1_set palSetPad(GPIOC,14)
#define _rel_vol2_set palSetPad(GPIOC,13)
#define _rel_vol3_set palSetPad(GPIOB,8)
#define _rel_vol1_clear palClearPad(GPIOC,14)
#define _rel_vol2_clear palClearPad(GPIOC,13)
#define _rel_vol3_clear palClearPad(GPIOB,8)

#define _rel_gain1_set palSetPad(GPIOB,7)
#define _rel_gain2_set palSetPad(GPIOB,5)
#define _rel_gain3_set palSetPad(GPIOB,4)
#define _rel_gain1_clear palClearPad(GPIOB,7)
#define _rel_gain2_clear palClearPad(GPIOB,5)
#define _rel_gain3_clear palClearPad(GPIOB,4)

#define rel_mute() palSetPad(GPIOC,15)
#define rel_unmute() palClearPad(GPIOC,15)
#define rel_inputHigh() palSetPad (GPIOB,3)
#define rel_inputLow() palClearPad (GPIOB,3)

void rel_set_channel(bool_t channel, uint8_t pot);
void rel_init(void);

#ifdef RELAY_TESTING
void rel_test(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* RELAYS_H_ */
