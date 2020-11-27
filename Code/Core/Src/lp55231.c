/*
 * lp55231.c
 *
 *  Created on: Nov 23, 2020
 *      Author: Jonathan
 */
#include "lp55231.h"

extern I2C_HandleTypeDef hi2c1;

/*
 * 3 RGB LEDs connected to the LP55231's channels
 * RGB LED 1: R=7; G=1; B=2;
 * RGB LED 2: R=8; G=3; B=4;
 * RGB LED 3: R=9; G=5; B=6;
 */

//HAL_StatusTypeDef LP55231_Chip_Reset(void){
////	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
//	HAL_StatusTypeDef ret;
//	uint8_t config = 0xFF;
//	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), RESET, 1, &config, 1, 50);
//	if(ret != HAL_OK){
//		return ret;
//	}
//	return HAL_OK;
//}

//HAL_StatusTypeDef LP55231_Chip_Enable(void){
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
//	HAL_StatusTypeDef ret;
//	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), ENGINE_CNTRL_1, 1, &CHIP_EN, 1, 50);
//	if(ret != HAL_OK){
//		return ret;
//	}
//	return HAL_OK;
//}


void WriteReg(uint8_t reg, uint8_t val){
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), reg, 1, &val, 1, 50);
}

void Reset(void){
  uint8_t config = 0xFF;
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), RESET, 1, &config, 1, 50);
}

void Enable(void){
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  uint8_t config = CHIP_EN;
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), ENGINE_CNTRL_1, 1, &config, 1, 50);
  HAL_Delay(500);
}

void LP55231_Init(void){
  // enable internal clock & charge pump & write auto increment
  uint8_t misc_config = EN_AUTO_INCR | CP_MODE_1 | CLK_DET_EN | INT_CLK_EN;
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), MISC, 1, &misc_config, 1, 50);
}

enum lp_err_code SetChannelPWM(uint8_t channel, uint8_t value){
  if(channel >= NumChannels)
  {
    return LP_ERR_INVALID_CHANNEL;
  }

  uint8_t reg = (D1_PWM) + channel;

//  WriteReg(REG_D1_PWM + channel, value);
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), reg, 1, &value, 1, 50);
  return LP_ERR_NONE;
}
