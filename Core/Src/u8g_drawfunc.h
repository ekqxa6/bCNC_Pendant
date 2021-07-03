/*
 * u8g_drawfunc.h
 *
 *  Created on: 2020/10/03
 *      Author: ekqxa
 */

#ifndef U8G_DRAWFUNC_H_
#define U8G_DRAWFUNC_H_

#include "u8glib\\u8g2.h"

void u8g_DrawFunc(u8g2_t *p_u8);
void u8g_Setup();
void u8g_drawSplashScreen();

void u8g_DrawFFT();
void u8g_DrawVUBar();
void u8g_DrawVUMeter();
void u8g_DrawWaveForm();

void u8g_Draw(int16_t pulse, int8_t axis, int8_t mag);


#endif /* U8G_DRAWFUNC_H_ */
