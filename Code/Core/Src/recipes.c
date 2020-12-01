/*
 * recipes.c
 *
 *  Created on: Nov 20, 2020
 *      Author: Jonathan
 */

#include "recipes.h"


/*
 * @brief Power On Self Test - Consecutively varies each channels brightness
 * @param None
 * @retval None
*/
void POST(void){
	for(int i = 0; i < Total_Channels; i++){
		for(int j = 0; j < 255; j = j + 1){
			Set_Channel_PWM(i, j);
			HAL_Delay(5);
		}
		Set_Channel_PWM(i, 0);
	}
}

/*
 * @brief Lighting sequence animation that resembles Google Home Mini
 * @param None
 * @retval None
*/
void Google_Home_Mini_Search_Animation(void){
	int channel_sequence[4] = {1, 2, 3, 20};
	int temp, i, j;
	int N = 4;

	Google_Blue(channel_sequence[0]);
	Google_Red(channel_sequence[1]);
	Google_Yellow(channel_sequence[2]);
	Google_Green(channel_sequence[3]);
	HAL_Delay(250);

	for(j = 0; j < 3; j++){
		temp = channel_sequence[0];
		for(i = 0; i < N; i++){
			channel_sequence[i] = channel_sequence[i + 1];
		}
		channel_sequence[N - 1] = temp;

		Google_Blue(channel_sequence[0]);
		Google_Red(channel_sequence[1]);
		Google_Yellow(channel_sequence[2]);
		Google_Green(channel_sequence[3]);
		HAL_Delay(250);
	}
}

/*
 * @brief Master Fader Demo
 * Configures the R,G,B channels of LED1 to Master Fader 1.
 * Sets LED1 to White in the Log mode.
 * Varies the master fader value to change brightness of all assigned channels simultaneously
 * in a ratiometric manner.
 * @param None
 * @retval None
*/
void Master_Fader(void){
  Master_Fader_Map(7, 1);
  Master_Fader_Map(1, 1);
  Master_Fader_Map(2, 1);
  Log_Dimmer_CNTRL(7, true);
  Log_Dimmer_CNTRL(1, true);
  Log_Dimmer_CNTRL(2, true);
  White(1);
  for (int i = 0; i < 255; i++){
	 Set_Master_Fader_PWM(0, i);
	 HAL_Delay(25);
  }
}
