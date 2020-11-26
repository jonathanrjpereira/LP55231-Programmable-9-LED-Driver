/*
 * lp55231.h
 *
 *  Created on: Nov 19, 2020
 *      Author: Jonathan
 */

#ifndef INC_LP55231_H_
#define INC_LP55231_H_

#include "stm32l4xx_hal.h"
#include "stm32l476xx.h"

/* 7-bit I2C Chip Address */
#define LP55231_ADDR 		0x32

///* 8-bit Register Access Macros */
#define HWREG8(x)			(*((volatile uint8_t*)(x)))

/***************************************/
/* LP55231 Register Definition Macros */
/***************************************/
#define ENGINE_CNTRL1 		(HWREG8(0x00))
#define OP_CTRL_MSB			(HWREG8(0x04))
#define OP_CTRL_LSB			(HWREG8(0x05))
#define D1_PWM				(HWREG8(0x16))
#define D2_PWM				(HWREG8(0x17))
#define D3_PWM				(HWREG8(0x18))
#define D4_PWM				(HWREG8(0x19))
#define D5_PWM				(HWREG8(0x1A))
#define D6_PWM				(HWREG8(0x1B))
#define D7_PWM				(HWREG8(0x1C))
#define D8_PWM				(HWREG8(0x1D))
#define D9_PWM				(HWREG8(0x1E))
#define MISC 				(HWREG8(0x36))

/*********************************/
/* LP55231 Bit Definition Macros */
/*********************************/
/*	ENGINE_CNTRL1	*/
#define CHIP_EN 			(HWREG8(0x40))
/*	OP_CTRL_MSB / LSB	*/
#define D9_ON 				(HWREG8(0x01))
#define D8_ON				(HWREG8(0x80))
#define D7_ON				(HWREG8(0x40))
#define D6_ON				(HWREG8(0x20))
#define D5_ON				(HWREG8(0x10))
#define D4_ON				(HWREG8(0x08))
#define D3_ON				(HWREG8(0x04))
#define D2_ON				(HWREG8(0x02))
#define D1_ON				(HWREG8(0x01))
/*	MISC	*/
#define INT_CLK_EN			(HWREG8(0x01))
#define CLK_DET_EN			(HWREG8(0x02))
#define PWM_PS_EN			(HWREG8(0x04))
#define CP_MODE_0			(HWREG8(0x08))
#define CP_MODE_1			(HWREG8(0x10))
#define POWERSAVE_EN		(HWREG8(0x20))
#define EN_AUTO_INCR		(HWREG8(0x40))
#define VARIABLE_D_SEL		(HWREG8(0x80))

///***************************************/
///* LP55231 Register Definition Macros */
///***************************************/
//#define ENGINE_CNTRL1 		((0x00))
//#define OP_CTRL_MSB			((0x04))
//#define OP_CTRL_LSB			((0x05))
//#define D1_PWM				((0x16))
//#define D2_PWM				((0x17))
//#define D3_PWM				((0x18))
//#define D4_PWM				((0x19))
//#define D5_PWM				((0x1A))
//#define D6_PWM				((0x1B))
//#define D7_PWM				((0x1C))
//#define D8_PWM				((0x1D))
//#define D9_PWM				((0x1E))
//#define MISC 				((0x36))

///*********************************/
///* LP55231 Bit Definition Macros */
///*********************************/
///*	ENGINE_CNTRL1	*/
//#define CHIP_EN 			((0x40))
///*	OP_CTRL_MSB / LSB	*/
//#define D9_ON 				((0x01))
//#define D8_ON				((0x80))
//#define D7_ON				((0x40))
//#define D6_ON				((0x20))
//#define D5_ON				((0x10))
//#define D4_ON				((0x08))
//#define D3_ON				((0x04))
//#define D2_ON				((0x02))
//#define D1_ON				((0x01))
///*	MISC	*/
//#define INT_CLK_EN			((0x01))
//#define CLK_DET_EN			((0x02))
//#define PWM_PS_EN			((0x04))
//#define CP_MODE_0			((0x08))
//#define CP_MODE_1			((0x10))
//#define POWERSAVE_EN		((0x20))
//#define EN_AUTO_INCR		((0x40))
//#define VARIABLE_D_SEL		((0x80))


/***********/
HAL_StatusTypeDef LP55231_Chip_Enable(void);
HAL_StatusTypeDef LP55231_Init(void);
HAL_StatusTypeDef OP_Ctrl(void);
HAL_StatusTypeDef Dx_PWM(void);
//uint8_t Read_MISC(void);


#endif /* INC_LP55231_H_ */
