/*
 * u8g_drawfunc.c
 *
 *  Created on: 2020/10/03
 *      Author: ekqxa
 */
#include <stdio.h>
#include "u8g_drawfunc.h"
#include "u8g_callback.h"
#include "icon_pics.h"	// icon
#include "defines.h"

#define	___SCR_HIGHT	(64-1)
#define	___SCR_WIDTH	(128-1)
#define	___DELAY_TIMES	(10)		// Delay timer for icon magnification when swich
#define ___VOL_HIGHT	(15)
#define	___VOL_WIDTH	(126)
//#define ___MIN_VOLUME_VAL	(-223)	// defined in defines.h

#define I2C_ADDRESS 0x3C

extern u8x8_t u8x8;                    // u8x8 object
extern u8g2_t u8g2;

static u8g2_t *p_u8g2 = NULL;

static int16_t delayCount4Icon;
static uint8_t currentOutput = 255;

static void DrawFrame(int style);


void u8g_DrawFunc(u8g2_t *p_u8)
{
	p_u8g2 = p_u8;
}

/**
  * @brief  : Initialize for u8g2
  * @param	: NIL
  * @retval : NIL
  *
  * ** ALIのOLEDは"f"にすること (u8g2_Setup_ssd1306_128x64_noname_f)
  */
void u8g_Setup()
{
	// I2C
	  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2,	// Mdf. here
			  U8G2_R0,
			  u8x8_byte_stm32hal_hw_i2c_1,	// here
			  psoc_gpio_and_delay_cb);
	  u8g2_SetI2CAddress(&u8g2, I2C_ADDRESS*2);
	  u8g2_InitDisplay(&u8g2);
	  u8g2_SetPowerSave(&u8g2, 0);
	  u8g2_ClearDisplay(&u8g2);

	  u8g2_SetDrawColor(&u8g2, 1);
	  u8g2_SetFontDirection(&u8g2, 0);
	  u8g2_SetFont(p_u8g2,u8g_font_helvB08);		// XOR
	  u8g2_SetFontMode(p_u8g2, 1);	// Transparent
}


// Splash screen (3 sec) = using for delay on timer for relay output
void u8g_drawSplashScreen()
{
	// 描画に20msec程必要な様子
	// 秒数はプログレスバーのステップ数で調整すること
	for(int i = 0; i < ___SCR_WIDTH; i+=4)
	{
		u8g2_FirstPage(p_u8g2);
		do
		{
			//u8g2_DrawXBM(p_u8g2, 0,0,MUSES_20ICON_width ,MUSES_20ICON_height ,MUSES_20ICON_bits);
			//u8g2_DrawLine(p_u8g2,0, ___SCR_HIGHT, i, ___SCR_HIGHT);	// progress bar
		} while ( u8g2_NextPage(p_u8g2) );

		//HAL_Delay(time_ms/___SCR_WIDGH);	// (3000/128)
	}
}


/**
  * @brief  : Draw main
  * @param	: pulse, axis, mag
  * @retval : NIL
  */
void u8g_Draw(int16_t pulse, int8_t axis, int8_t mag)
{

    u8g2_ClearBuffer(p_u8g2);

    u8g2_SetFontMode(p_u8g2, 1); // Transparent
    u8g2_SetFontDirection(p_u8g2, 0);
    u8g2_SetFont(p_u8g2, u8g2_font_inb16_mf);

    char buffer[32];
/*    if(pulse)
    	sprintf(buffer, "%+d", pulse);
    else
    	sprintf(buffer, " 0");
    u8g2_DrawStr(p_u8g2, 1, 24, buffer);
*/

    int16_t power[] = {1, 10, 100,1000};
    int16_t disp = pulse * power[mag];
    if( disp < 0 )
    	sprintf(buffer, "-%3d.%03d",-disp/1000, -disp%1000);
    else
    	sprintf(buffer, "+%3d.%03d",disp/1000, disp%1000);
    u8g2_DrawStr(p_u8g2, 16, 24, buffer);


    /*sprintf(counter, "%d%d%d%d%d%d", sts.btn1,sts.btn2,sts.btn3,sts.btn4,sts.btn5,sts.btn6 );
    u8g2_DrawStr(&u8g2, 48, 32, counter);
     */

    const char *mg[]={
    		{"*___1"},
    		{"*__10"},
			{"*_100"},
			{"*1000"},
    };
    u8g2_SetFont(p_u8g2, u8g2_font_inb16_mf);
    sprintf(buffer, "%s", mg[mag]);
    u8g2_DrawStr(p_u8g2, 0, 62, buffer);


    const char AxisChar[]="0XYZ4";
    if( AXIS_OFF == axis )
    	sprintf(buffer, "%s", "OFF");
    else
    	sprintf(buffer, "-%c-", AxisChar[axis]);
    u8g2_DrawStr(p_u8g2, 80, 62, buffer);


    u8g2_SendBuffer(p_u8g2);

}


/**
  * @brief  : Draw Rectangle Frame
  * @param	: int style 0: horizontal, 1 : Vertical separation.
  * @retval : NIL
  */
void DrawFrame(int style)
{

	u8g2_DrawLine(p_u8g2, 0, 0, ___SCR_WIDTH, 0);
	u8g2_DrawLine(p_u8g2, 0, ___SCR_HIGHT, 0, 0);
	u8g2_DrawLine(p_u8g2, ___SCR_WIDTH, ___SCR_HIGHT, ___SCR_WIDTH, 0);
	u8g2_DrawLine(p_u8g2, 0, ___SCR_HIGHT, ___SCR_WIDTH, ___SCR_HIGHT);
	if( 0 == style )
	{
		u8g2_DrawLine(p_u8g2, 64, 1, 64, 63 ); // Center line
	}
	else
	{
		u8g2_DrawLine(p_u8g2, 1, 40, 127, 40 );    // Center line
	}


}

