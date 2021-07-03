/*
 * BtnHandler.h
 *
 *  Created on: 2021/06/26
 *      Author: ekqxa
 */

#ifndef SRC_BTNHANDLER_H_
#define SRC_BTNHANDLER_H_

#include "main.h"

struct KEYSTATUS
{
	uint8_t btn1;
	uint8_t btn2;
	uint8_t btn3;
	uint8_t btn4;
	uint8_t btn5;
	uint8_t btn6;
};

#define OFF_STS   (0)
#define ON_STS    (1)
#define OFF_EDGE  (2)
#define ON_EDGE  (3)


void BtnHandler();

void btn_ReadKeyStatus();
void btn_SetKeyStatus(struct KEYSTATUS *pStsFlag);


int8_t btn_Axis();
int8_t btn_MAG();
int8_t btn_CS();
int8_t btn_FH();

#endif /* SRC_BTNHANDLER_H_ */
