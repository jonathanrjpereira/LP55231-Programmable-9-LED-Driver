/*
 * lp55231.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Jonathan
 */


#include "lp55231.h"

extern I2C_HandleTypeDef hi2c1;

//HAL_I2C_Master_Transmit();
//HAL_I2C_Master_Receive();
//HAL_I2C_Mem_Write();
//HAL_I2C_Mem_Read();

HAL_StatusTypeDef LP55231_Chip_Enable(void){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), ENGINE_CNTRL1, 1, &CHIP_EN, 1, 50);
	HAL_Delay(500);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

HAL_StatusTypeDef LP55231_Init(void){
	HAL_StatusTypeDef ret;
	uint8_t config = EN_AUTO_INCR | CP_MODE_1 | CLK_DET_EN | INT_CLK_EN;
	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), MISC, 1, &config, 1, 50);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

HAL_StatusTypeDef OP_Ctrl(void){
	HAL_StatusTypeDef ret;
	uint8_t config = D9_ON;
	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)LP55231_ADDR<<1, OP_CTRL_MSB, 1, &config, 1, 50);

	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

HAL_StatusTypeDef Dx_PWM(void){
	HAL_StatusTypeDef ret;
	uint8_t config = 0xFF;
	ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)LP55231_ADDR<<1, D9_PWM, 1, &config, 1, 50);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

//uint8_t Read_MISC(void){
//	HAL_StatusTypeDef ret;
//	uint8_t tempData[1];
//	ret = HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) | 0x01, MISC, 1, tempData, 1, 50);
//	if (ret != HAL_OK){
//		return ret;
//	}
//	return *tempData;
//}
