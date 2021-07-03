/*
 * SendKey.h
 *
 *  Created on: 2021/06/24
 *      Author: ekqxa
 */

#ifndef SRC_SENDKEY_H_
#define SRC_SENDKEY_H_

#include "main.h"

// HID Keyboard
struct keyboardConfig_t {
	uint8_t id;
	uint8_t modifiers;
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
};
/*
 * modifiers
 *
 * 0 : L Ctrl
 * 1 : L Shift
 * 2 : L Alt
 * 3 : L GUI
 * 4 : R Ctrl
 * 5 : R Shift
 * 6 : R Alt
 * 7 : R GUI
 *
 * key : http://www2d.biglobe.ne.jp/~msyk/keyboard/layout/usbkeycode.html
 */

void key_Setup();


void key_sendFH();
void key_sendCS();
void key_sendMag(uint8_t mag);
void key_sendPulse(uint8_t ax, int8_t dir);

#endif /* SRC_SENDKEY_H_ */
