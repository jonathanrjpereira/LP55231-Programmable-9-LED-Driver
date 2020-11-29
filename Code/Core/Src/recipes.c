/*
 * recipes.c
 *
 *  Created on: Nov 27, 2020
 *      Author: Jonathan
 */

#include "recipes.h"



void LED_PWM_Test(void){
	for(int i=0; i<NumChannels; i++){
		for(int j=0; j<255; j=j+5){
			SetChannelPWM(i, j);
			HAL_Delay(10);
		}
		SetChannelPWM(i, 0);
	}
}

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


