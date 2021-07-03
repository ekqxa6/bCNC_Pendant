/*
 * SendKey.c
 *
 *  Created on: 2021/06/24
 *      Author: ekqxa
 */
#include "usb_device.h"
#include "SendKey.h"
#include "defines.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

static struct keyboardConfig_t keyData;
static void sendKey();

static uint8_t mag_old = 0;
///////////////////////////////////////////////////////
// setup keyboard interface
void key_Setup()
{
	keyData.id = 1;
	keyData.modifiers = 0;
	keyData.key1 = 0;
	keyData.key2 = 0;
	keyData.key3 = 0;
}

void key_sendFH()
{
	key_Setup();

	keyData.modifiers = 2;	// SHIFT
	keyData.key1 = 0x1E;	// !
	sendKey();
}
void key_sendCS()
{
	key_Setup();

	keyData.modifiers = 2;	// SHIFT
	keyData.key1 = 0x35;	// ~
	sendKey();
}

void key_sendMag(uint8_t mag)
{
	key_Setup();

	if(MAG_0010 == mag )
	{
		if( MAG_0001 == mag_old )
		{
			keyData.modifiers = 2;	// SHIFT
			keyData.key1 = 0x25;	// * (SHIFT+8)
		}
		else if( MAG_0100 == mag_old)
		{
			keyData.key1 = 0x54;	// / (P)
		}
	}
	else if(MAG_0001 == mag)
	{
		if( MAG_0010 == mag_old )
		{
			keyData.key1 =0x54;	// / (P)
		}
	}
	else if(MAG_0100 == mag )
		keyData.key1 = 0x1E;	// 1
	else if(MAG_1000 == mag )
		keyData.key1 = 0x1F;	// 2

	sendKey();

	mag_old = mag;

}

//#define	PULSE_PLUS	(1)
//#define	PULSE_MINUS	(-1)

void key_sendPulse(uint8_t ax, int8_t dir)
{
	if( AXIS_OFF >= ax || ax > MAX_AXIS )
		return;

	key_Setup();

	if( AXIS_X == ax )
	{
		keyData.key1 = (PULSE_PLUS == dir)? 0x4F: 0x50;
	}
	else if( AXIS_Y == ax )
	{
		keyData.key1 = (PULSE_PLUS == dir)? 0x52: 0x51;
	}
	else if( AXIS_Z == ax )
	{
		keyData.key1 = (PULSE_PLUS == dir)? 0x4B: 0x4E;
	}

	sendKey();
}

void sendKey()
{
	USBD_HID_SendReport(&hUsbDeviceFS, &keyData, sizeof(keyData));
	HAL_Delay(30);
	keyData.modifiers = 0;
	keyData.key1 = 0;
	USBD_HID_SendReport(&hUsbDeviceFS, &keyData, sizeof(keyData));
}



