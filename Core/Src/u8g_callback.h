
#ifndef	___SSD_1306_HANDLER___
#define	___SSD_1306_HANDLER___

#define I2C_ADDRESS_1 0x3C
#define I2C_ADDRESS_2 0x3D

//#define I2C_ADDRESS_1 0x3D
//#define I2C_ADDRESS_2 0x3C


#include "u8glib\\u8g2.h"
#include "stm32f4xx_hal.h"

uint8_t psoc_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

uint8_t u8x8_byte_stm32hal_hw_i2c_1(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_stm32hal_hw_i2c_2(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;

#endif	// ___SSD_1306_HANDLER___
