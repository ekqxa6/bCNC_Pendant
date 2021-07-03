/*
 * Encoder.c
 *
 *  Created on: 2020/10/03
 *      Author: ekqxa
 */

/*
 * handling function for Encoder
 */

#include "Encoder.h"

static TIM_HandleTypeDef* p_htim = NULL;

//static int16_t volume_val=0;			// Current volume value
//static int16_t volume_val_old=0;		// Previous volume value
static int16_t rotate_val=0;			// Current rotation angle value
static int16_t rotate_val_old=0;		// Previous rotation angle value

static uint32_t encoder_val=0;		// Current encoder read
static uint32_t	encoder_val_old=0;	// previous encoder read

static uint32_t encoderRead(void);	// Read Encoder value
static int16_t encoderReadDiff(void);	// Read how much rotated from previous read


/////////////////////////////////////////////////
// Constructor�I��
void Encoder(TIM_HandleTypeDef* htim)
{
	p_htim = htim;
//	volume_val = 0;
//	volume_val_old = 0;
}

///////////////////////////////////////////////////////////////
// TIMER INTERRUPT
//�I�[�o�[�t���[�A���_�[�t���[����Ǝ����I�ɌĂ΂��֐�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if( p_htim == NULL )
		return;

	//���̊֐����̂�TIM3�Ŗ����Ă��Ă΂�Ă��܂��\��������̂ŁCTIM4�̊��荞�݂ł��邱�Ƃ��m�F����
	if(htim->Instance == p_htim->Instance){
		//���荞�݃t���O�N���A�C��������Ȃ��Ƃ��̊֐���������Ăяo�����
		__HAL_TIM_CLEAR_FLAG(p_htim, TIM_IT_UPDATE);
		HAL_GPIO_TogglePin( LED_PIN_GPIO_Port, LED_PIN_Pin);
	}
}




///////////////////////////////////////////////////////////////
// �p���X������肷��ۂɌĂт���
// +val : +�����ւ̈ړ��w�߃p���X
// -val : -�����ւ̈ړ��w�߃p���X
int16_t enc_GetPulse(void)
{
	rotate_val_old = rotate_val;	// �Â��l��ۑ�
	rotate_val += (int32_t)encoderReadDiff();	// ������ǉ�

	return rotate_val / 2;
}

///////////////////////////////////////////////////////////////
// ���M�����R�}���h����񍐂���
// +�����Ɉړ������ꍇ��+�l�œn���B
int16_t enc_SentPulse(int16_t cnt)	// report how many command has been sent
{
	rotate_val -= (cnt*2);
	return rotate_val;
}

///////////////////////////////////////////////////////////////
// �p���X�������Z�b�g����B���I����{���I��������ɌĂт���
void enc_ResetPulse(void)
{
	rotate_val = 0;
	rotate_val_old = 0;
}

int16_t encoderReadDiff(void)
{
	int32_t temp;
	temp = (int32_t)encoderRead();
	return (int16_t)(temp - (int32_t)encoder_val_old);
}
uint32_t encoderRead(void)
{
	encoder_val_old = encoder_val;	// save old value
	return encoder_val = p_htim->Instance->CNT;	// TIM4->CNT
}


void enc_Start(void)
{
    HAL_TIM_Encoder_Start(p_htim, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(p_htim);  // Enable interrupt
}

void enc_Stop(void)
{
    HAL_TIM_Encoder_Stop(p_htim, TIM_CHANNEL_ALL);
}

