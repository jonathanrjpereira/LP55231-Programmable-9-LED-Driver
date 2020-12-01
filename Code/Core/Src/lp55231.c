/*
 * lp55231.c
 *
 *  Created on: Nov 20, 2020
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

/*
 * @brief Resets all device registers
 * @param None
 * @retval Status
*/
enum lp_err_code Reset(void){
  uint8_t config = 0xFF;
  HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), RESET, 1, &config, 1, 50);
  if(ret != HAL_OK){
	return LP_ERR_RESET;
  }
  return LP_RESET_OK;
}

/*
 * @brief LP55231 Enable. Mode of Operation changes from Standby to Normal
 * @param None
 * @retval Status
*/
enum lp_err_code Enable(void){
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  uint8_t config = CHIP_EN;
  HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), ENGINE_CNTRL_1, 1, &config, 1, 50);
  if(ret != HAL_OK){
	return LP_ERR_ENABLE;
  }
  HAL_Delay(500);
  return LP_ENABLE_OK;
}

/*
 * @brief Configures Clock Selection and Charge Pump operation mode
 * @param None
 * @retval None
*/
void LP55231_Init(void){
  uint8_t misc_config = CP_MODE_1 | CLK_DET_EN | INT_CLK_EN;
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), MISC, 1, &misc_config, 1, 50);
}

/*
 * @brief Direct PWM Control - Used to set brightness of individual LED channel.
 * @param channel: LED channel number (0-8)
 * @param value: 8-bit PWM value
 * @retval Status
*/
enum lp_err_code Set_Channel_PWM(uint8_t channel, uint8_t value){
  if(channel >= Total_Channels){
    return LP_ERR_INVALID_CHANNEL;
  }
  uint8_t reg = (D1_PWM) + channel;
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), reg, 1, &value, 1, 50);
  return LP_OK;
}

/*
 * @brief Groups 3 individual LEDs into their respective RGB group.
 * Used to set the color of a RGB LED.
 * @param LED_Group: Selects the RGB LED (1-3)
 * @param R/G/B_PWM: 8-bit PWM value to set the R,G & B LEDs brightness
 * @retval None
*/
void RGB_LED(uint8_t LED_Group, uint8_t R_PWM, uint8_t G_PWM, uint8_t B_PWM){
	int r_channel  = (7 + (1 * (LED_Group - 1))) - 1;
	int g_channel  = (1 + (2 * (LED_Group - 1))) - 1;
	int b_channel  = (2 + (2 * (LED_Group - 1))) - 1;
	Set_Channel_PWM(r_channel, R_PWM);
	Set_Channel_PWM(g_channel, G_PWM);
	Set_Channel_PWM(b_channel, B_PWM);
}

/*
 * @brief Standard Colors used in Demos
 * @param LED_Group: Selects the RGB LED (1-3)
 * @retval None
*/
void Google_Blue(uint8_t LED_Group){
	RGB_LED(LED_Group, 10, 15, 244);
}
void Google_Red(uint8_t LED_Group){
	RGB_LED(LED_Group, 254, 15, 10);
}
void Google_Yellow(uint8_t LED_Group){
	RGB_LED(LED_Group, 244, 160, 0);
}
void Google_Green(uint8_t LED_Group){
	RGB_LED(LED_Group, 15, 244, 30);
}
void White(uint8_t LED_Group){
	RGB_LED(LED_Group, 254, 254, 254);
}

/*
 * @brief Selects dimming mode i.e. Log/Linear scale
 * @param channel: LED channel number (0-8)
 * @param control: 0: Linear, 1: Log
 * @retval Status
*/
enum lp_err_code Log_Dimmer_CNTRL(uint8_t channel, bool control){
	if(channel >= Total_Channels){
		return LP_ERR_INVALID_CHANNEL;
	}
	uint8_t reg;
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) |0x01, (D1_CNTRL) + channel, 1, reg, 1, 50);
	uint8_t config = control ? LOG_EN : 0x00;
	reg &= ~(0x20);
	reg |= config;
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), (D1_CNTRL) + channel, 1, &reg, 1, 50);
	return LP_OK;
}

/*
 * @brief Assigns a channel to a specific Master Fader
 * @param channel: LED channel number (0-8)
 * @param fader_mode: 0: No Mapping, 1: Master Fader 1, , 2: Master Fader 2, 3: Master Fader 3
 * @retval Status
*/
enum lp_err_code Master_Fader_Map(uint8_t channel, uint8_t fader_mode){
	if(channel >= Total_Channels){
		return LP_ERR_INVALID_CHANNEL;
	}
	uint8_t reg, config;
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) |0x01, (D1_CNTRL) + channel, 1, reg, 1, 50);
	config = fader_mode;
	config <<= 6;
	reg &= ~(0xC0);
	reg |= config;
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), (D1_CNTRL) + channel, 1, &reg, 1, 50);
	return LP_OK;
}

/*
 * @brief Sets the dimming value for a specific Master Fader.
 * @param fader: Selects the Master Fader (1-3)
 * @param value: 8-bit value
 * @retval Status
*/
enum lp_err_code Set_Master_Fader_PWM(uint8_t fader, uint8_t value){
  if(fader >= Total_Faders){
    return LP_ERR_INVALID_FADER;
  }
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), MASTER_FADER_1 + fader, 1, &value, 1, 50);
  return LP_OK;
}

/*
 * @brief Read the internal temperature sensor.
 * @param None
 * @retval temperature: Temperature in C.
*/
int8_t Read_Temp_Sensor(void){
	uint8_t config = EN_TEMP_SENSOR;
	uint8_t cntrl_reg, temp_reg;
	int8_t temperature;

	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), TEMP_ADC_CNTRL, 1, &config, 1, 50);
	do{
		HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) |0x01, TEMP_ADC_CNTRL, 1, cntrl_reg, 1, 50);
	}while(cntrl_reg & TEMP_MEAS_BUSY);

	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) |0x01, TEMP_READ, 1, temp_reg, 1, 50);
	temperature = (int8_t)temp_reg;
	return temperature;
}

/*
 * @brief Read the LED Driver Output voltage.
 * @param channel: Channel Selection (0-8)
 * @retval voltage: Voltage in volts.
*/
float Read_LED_OP_Voltage(uint8_t channel){
	uint8_t config;
	config = EN_LEDTEST_ADC | channel;
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), LED_TEST_CNTRL, 1, &config, 1, 50);
	HAL_Delay(3);
	float voltage = Read_ADC();
	return voltage;
}

/*
 * @brief Read the Supply voltage VDD.
 * @param None
 * @retval voltage: Voltage in volts.
*/
float Read_VDD(void){
	uint8_t config;
	uint8_t vdd = 0x10;
	config = EN_LEDTEST_ADC | vdd;
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(LP55231_ADDR<<1), LED_TEST_CNTRL, 1, &config, 1, 50);
	HAL_Delay(3);
	float voltage = Read_ADC();
	return voltage;
}

/*
 * @brief Read the ADC register voltage.
 * @param None
 * @retval voltage: Voltage in volts.
*/
float Read_ADC(void){
	uint8_t adc_reg;
	float voltage;
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(LP55231_ADDR<<1) |0x01, LED_TEST_ADC, 1, adc_reg, 1, 50);
	voltage = (adc_reg * 0.03) - 1.478;
	return voltage;
}
