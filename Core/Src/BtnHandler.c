/*
 * BtnHandler.c
 *
 *  Created on: 2021/06/26
 *      Author: ekqxa
 */


#include "BtnHandler.h"



static struct KEYSTATUS stKeyCur;
static struct KEYSTATUS stKeyOld;
static struct KEYSTATUS stKeySts; // 0:OFF, 1:ON, 2:OFF(EDGE), 3:ON(EDGE)

static void SaveKeyStatus();

/////////////////////////////////////////////////
// Constructor�I��
void BtnHandler()
{
	memset(&stKeyCur, 0, sizeof(stKeyCur));
	memset(&stKeyOld, 0, sizeof(stKeyOld));
	memset(&stKeySts, 0, sizeof(stKeySts));
}

///////////////////////////////////////////////
// �{�^���̉����󋵂��`�F�b�N����
void btn_ReadKeyStatus()
{
	SaveKeyStatus();

  uint8_t *pBtnSts = (uint8_t*)&stKeyCur;

  pBtnSts[0] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOA, BTN_AX_UP_Pin))?0:1;
  pBtnSts[1] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOA, BTN_AX_DOWN_Pin))?0:1;
  pBtnSts[2] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, BTN_MAG_UP_Pin))?0:1;
  pBtnSts[3] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, BTN_MAG_DOWN_Pin))?0:1;
  pBtnSts[4] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, BTN_CS_Pin))?0:1;
  pBtnSts[5] = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, BTN_FH_Pin))?0:1;

}

///////////////////////////////////////////////////////////////////
// ON, OFF�̃g���K��ۑ�
void btn_SetKeyStatus(struct KEYSTATUS *pStsFlag)
{
	uint8_t *pBtnSts = (uint8_t*)&stKeyCur;
	uint8_t *pBtnOld = (uint8_t*)&stKeyOld;
	uint8_t *pKeySts = (uint8_t*)&stKeySts;
  int nNumOfKeyDown = 0;
  for ( int i = 0; i < 6; i++)
  {
    if ( pBtnSts[i] != pBtnOld[i] )   // �ω�����
    {
      pKeySts[i] = (pBtnSts[i]) ? ON_EDGE : OFF_EDGE;
    }
    else    // �ω������B�{�v���O�����ł͎g�p���Ȃ��X�e�[�^�X�B
    {
      pKeySts[i] = (pBtnSts[i]) ? ON_STS : OFF_STS;
    }
  }
  if( pStsFlag )
  {
	  memcpy(pStsFlag, pKeySts, sizeof(stKeySts) );
  }
}

///////////////////////////////////////////////
// �{�^���̉����󋵂�ۑ�����
void SaveKeyStatus()
{
	memcpy(&stKeyOld, &stKeyCur, sizeof(stKeyOld));
}

///////////////////////////////////////////////////////////////////
// ���{�^��
int8_t btn_Axis()
{
	int8_t return_val = 0;
	 if ( OFF_EDGE == stKeySts.btn1 )  // AXIS UP KEY
	 {
		 return_val = 1;
	 }
	 else if( OFF_EDGE == stKeySts.btn2 )  // AXIS Down KEY
	 {
		 return_val = -1;
	 }
	 return return_val;
}

///////////////////////////////////////////////////////////////////
// �{���{�^��
int8_t btn_MAG()
{
	int8_t return_val = 0;
	 if ( OFF_EDGE == stKeySts.btn3 )  // MAG UP KEY
	 {
		 return_val = 1;
	 }
	 else if( OFF_EDGE == stKeySts.btn4 )  // MAG Down KEY
	 {
		 return_val = -1;
	 }
	 return return_val;
}

///////////////////////////////////////////////////////////////////
// CS�{�^��
int8_t btn_CS()
{
	int8_t return_val = 0;
	if ( OFF_EDGE == stKeySts.btn5 )  // CS
	{
		 return_val = 1;
	}

	return return_val;
}

///////////////////////////////////////////////////////////////////
// FH�{�^��
int8_t btn_FH()
{
	int8_t return_val = 0;
	if ( ON_EDGE == stKeySts.btn6 )  // FH �͉������u�Ԃ�
	{
		 return_val = 1;
	}
	return return_val;
}


