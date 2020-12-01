/*
 * lp55231.h
 *
 *  Created on: Nov 20, 2020
 *      Author: Jonathan
 */

#ifndef INC_LP55231_H_
#define INC_LP55231_H_

#include "stm32l4xx_hal.h"
#include "stm32l476xx.h"
#include <stdbool.h>


/* 7-bit I2C device address */
#define LP55231_ADDR		0x32

/* 8-bit Register Access Macros	*/
//#define HWREG8(x)			(*((volatile uint8_t *)(x)))
#define HWREG8(x)			((uint8_t)(x)) // This works lol
#define BIT(n)              (1<<(n))


/****************************************/
/*	LP55231 Register Macros	*/
/****************************************/
#define ENGINE_CNTRL_1		(HWREG8(0x00))
#define D1_CNTRL			(HWREG8(0x06))
#define D1_PWM				(HWREG8(0x16))
#define D1_CURRENT_CNTRL	(HWREG8(0x26))
#define MISC				(HWREG8(0x36))
#define RESET				(HWREG8(0x3D))
#define TEMP_ADC_CNTRL		(HWREG8(0x3E))
#define TEMP_READ			(HWREG8(0x3F))
#define LED_TEST_CNTRL		(HWREG8(0x41))
#define LED_TEST_ADC		(HWREG8(0x42))
#define MASTER_FADER_1		(HWREG8(0x48))
/****************************************/
/*	LP55231 Register Bit Macros	*/
/****************************************/
/* ENGINE_CNTRL_1 */
#define CHIP_EN				(BIT(6))
/* D1_CNTRL */
#define LOG_EN				(BIT(5))
#define MAPPING_0			(BIT(6))
#define MAPPING_1			(BIT(7))
/* MISC */
#define INT_CLK_EN			(BIT(0))
#define CLK_DET_EN			(BIT(1))
#define CP_MODE_1			(BIT(4))
#define EN_AUTO_INCR		(BIT(6))
/* TEMP_ADC_CNTRL */
#define EN_TEMP_SENSOR		(BIT(2))
#define TEMP_MEAS_BUSY		(BIT(7))
/* LED_TEST_CNTRL */
#define EN_LEDTEST_ADC		(BIT(7))

static const uint8_t Total_Channels = 9;
static const uint8_t Total_Faders = 3;

typedef enum lp_err_code
{
  LP_OK = 0,
  LP_ERR_INVALID_CHANNEL,
  LP_ERR_INVALID_FADER,
  LP_ERR_RESET,
  LP_RESET_OK,
  LP_ERR_ENABLE,
  LP_ENABLE_OK,
  LP_I2C_ERROR,
  LP_I2C_OK
};

/* Initial Chip Configuration */
enum lp_err_code Reset(void);
enum lp_err_code  Enable(void);
void LP55231_Init(void);
/* Direct PWM Control */
enum lp_err_code Set_Channel_PWM(uint8_t channel, uint8_t value);
void RGB_LED(uint8_t LED_Group, uint8_t R_PWM, uint8_t G_PWM, uint8_t B_PWM);
void Google_Blue(uint8_t LED_Group);
void Google_Red(uint8_t LED_Group);
void Google_Yellow(uint8_t LED_Group);
void Google_Green(uint8_t LED_Group);
void White(uint8_t LED_Group);
/* Master Fader */
enum lp_err_code Log_Dimmer_CNTRL(uint8_t channel, bool control);
enum lp_err_code Master_Fader_Map(uint8_t channel, uint8_t fader_mode);
enum lp_err_code Set_Master_Fader_PWM(uint8_t fader, uint8_t value);
/* Diagnostics */
int8_t Read_Temp_Sensor(void);
float Read_LED_OP_Voltage(uint8_t channel);
float Read_ADC(void);
float Read_VDD(void);

#endif /* INC_LP55231_H_ */
