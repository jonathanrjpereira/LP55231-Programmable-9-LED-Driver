/*
 * lp55231.h
 *
 *  Created on: Nov 23, 2020
 *      Author: Jonathan
 */

#ifndef INC_LP55231_H_
#define INC_LP55231_H_

#include "stm32l4xx_hal.h"
#include "stm32l476xx.h"


/* 7-bit I2C device address */
#define LP55231_ADDR		0x32

/* 8-bit Register Access Macros	*/
//#define HWREG8(x)			(*((volatile uint8_t *)(x)))
#define HWREG8(x)			((uint8_t)(x)) // This works lol
#define BIT(n)              (1<<(n))


/****************************************/
/*	LP55231 Register Definition Macros	*/
/****************************************/
#define ENGINE_CNTRL_1		(HWREG8(0x00))
#define D1_PWM				(HWREG8(0x16))
#define MISC				(HWREG8(0x36))
#define RESET				(HWREG8(0x3D))
//
///****************************************/
///*	LP55231 Register Definition Macros	*/
///****************************************/
//#define CHIP_EN				(BITDEF(0x40))
////#define D9_ON				(BITDEF(0x01))
//#define INT_CLK_EN			(BITDEF(0x01))
//#define CLK_DET_EN			(BITDEF(0x02))
//#define CP_MODE_1			(BITDEF(0x10))
//#define EN_AUTO_INCR		(BITDEF(0x40))


#define CHIP_EN				(BIT(6))
#define INT_CLK_EN			(BIT(0))
#define CLK_DET_EN			(BIT(1))
#define CP_MODE_1			(BIT(4))
#define EN_AUTO_INCR		(BIT(6))

//HAL_StatusTypeDef LP55231_Chip_Reset(void);
//HAL_StatusTypeDef LP55231_Chip_Enable(void);
//HAL_StatusTypeDef LP55231_Init(void);
//HAL_StatusTypeDef OP_Ctrl(void);
//HAL_StatusTypeDef Dx_PWM(void);

///* 7-bit I2C Chip Address */
////static const uint8_t address = 0x32;

//static const uint8_t REG_CNTRL1 = 0x00;
static const uint8_t REG_OUTPUT_ONOFF_MSB = 0x04;
static const uint8_t REG_OUTPUT_ONOFF_LSB = 0x05;
// Direct PWM control registers
static const uint8_t REG_D1_PWM  = 0x16;
static const uint8_t REG_D2_PWM  = 0x17;
static const uint8_t REG_D3_PWM  = 0x18;
static const uint8_t REG_D4_PWM  = 0x19;
static const uint8_t REG_D5_PWM  = 0x1a;
static const uint8_t REG_D6_PWM  = 0x1b;
static const uint8_t REG_D7_PWM  = 0x1c;
static const uint8_t REG_D8_PWM  = 0x1d;
static const uint8_t REG_D9_PWM  = 0x1e;
//static const uint8_t REG_MISC    = 0x36;
//static const uint8_t REG_RESET   = 0x3D;

static const uint8_t NumChannels = 9;


typedef enum lp_err_code
{
  LP_ERR_NONE = 0,
  LP_ERR_INVALID_CHANNEL,
  LP_ERR_INVALID_FADER,
  LP_ERR_INVALID_ENGINE,
  LP_ERR_PROGRAM_LENGTH,
  LP_ERR_PROGRAM_VALIDATION,
  LP_ERR_PROGRAM_PC,
  LP_ERR_GPIO_OFF
};

void WriteReg(uint8_t reg, uint8_t val);
void Reset(void);
void Enable(void);
void LP55231_Init(void);
enum lp_err_code SetChannelPWM(uint8_t channel, uint8_t value);





#endif /* INC_LP55231_H_ */
