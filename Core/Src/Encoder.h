/*
 * Encoder.h
 *
 *  Created on: 2020/10/03
 *      Author: ekqxa
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"


void Encoder(TIM_HandleTypeDef* htim);	// Constructor

int16_t enc_GetPulse(void);		// use this to get number of pulse for sending
int16_t enc_SentPulse(int16_t cnt);	// report how many command has been sent
void enc_ResetPulse(void);		// reset encoder pos when axis selection changed

void enc_Start(void);
void enc_Stop(void);

#endif /* ENCODER_H_ */
