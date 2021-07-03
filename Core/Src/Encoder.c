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
// Constructor的な
void Encoder(TIM_HandleTypeDef* htim)
{
	p_htim = htim;
//	volume_val = 0;
//	volume_val_old = 0;
}

///////////////////////////////////////////////////////////////
// TIMER INTERRUPT
//オーバーフローアンダーフローすると自動的に呼ばれる関数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if( p_htim == NULL )
		return;

	//この関数自体はTIM3で無くても呼ばれてしまう可能性があるので，TIM4の割り込みであることを確認する
	if(htim->Instance == p_htim->Instance){
		//割り込みフラグクリア，これをしないとこの関数が複数回呼び出される
		__HAL_TIM_CLEAR_FLAG(p_htim, TIM_IT_UPDATE);
		HAL_GPIO_TogglePin( LED_PIN_GPIO_Port, LED_PIN_Pin);
	}
}




///////////////////////////////////////////////////////////////
// パルス数を入手する際に呼びだす
// +val : +方向への移動指令パルス
// -val : -方向への移動指令パルス
int16_t enc_GetPulse(void)
{
	rotate_val_old = rotate_val;	// 古い値を保存
	rotate_val += (int32_t)encoderReadDiff();	// 差分を追加

	return rotate_val / 2;
}

///////////////////////////////////////////////////////////////
// 送信したコマンド分を報告する
// +方向に移動した場合は+値で渡す。
int16_t enc_SentPulse(int16_t cnt)	// report how many command has been sent
{
	rotate_val -= (cnt*2);
	return rotate_val;
}

///////////////////////////////////////////////////////////////
// パルス数をリセットする。軸選択や倍率選択した後に呼びだす
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

