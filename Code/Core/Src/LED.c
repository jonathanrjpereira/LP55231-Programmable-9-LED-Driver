#include "LED.h"


//******************************************************************************************
// User LEDs: 
//   LD4 Red = PB2    LD5 Green = PE8
// Note: The Green LED is yellow on my board.
//       PE8 is also the TIM1_CH1N for ADC Triggers.
//******************************************************************************************
void LED_Init(void){
	
	// Enable the peripheral clock of GPIO Port	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOEEN;
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// LD4 Red = PB2
	///////////////////////////////////////////////////////////////////////////////////////////////
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOB->MODER = ~(3U<<(2*2));  
	GPIOB->MODER |= 1U<<(2*2);      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOB->OSPEEDR &= ~(3U<<(2*2));
	GPIOB->OSPEEDR |=   3U<<(2*2);  // High speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOB->OTYPER &= ~(1U<<2);       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOB->PUPDR   &= ~(3U<<(2*2));  // No pull-up, no pull-down
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// LD5 Green = PE8
	///////////////////////////////////////////////////////////////////////////////////////////////
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOE->MODER = ~(3U<<(2*8));  
	GPIOE->MODER |= 1U<<(2*8);      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOE->OSPEEDR &= ~(3U<<(2*8));
	GPIOE->OSPEEDR |=   3U<<(2*8);  // High speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOE->OTYPER &= ~(1U<<8);       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOE->PUPDR   &= ~(3U<<(2*8));  // No pull-up, no pull-down
}

//******************************************************************************************
// Turn Red LED On
//******************************************************************************************
void Red_LED_On(void){
	GPIOB->ODR |= GPIO_ODR_ODR_2;
}

//******************************************************************************************
// Turn Red LED Off
//******************************************************************************************
void Red_LED_Off(void){
	GPIOB->ODR &= ~GPIO_ODR_ODR_2;
}

//******************************************************************************************
// Toggle Red LED 
//******************************************************************************************
void Red_LED_Toggle(void){
	GPIOB->ODR ^= GPIO_ODR_ODR_2;
}

//******************************************************************************************
// Turn Green LED On
//******************************************************************************************
void Green_LED_On(void){
	GPIOE->ODR |= GPIO_ODR_ODR_8;
}

//******************************************************************************************
// Turn Green LED Off
//******************************************************************************************
void Green_LED_Off(void){
	GPIOE->ODR &= ~GPIO_ODR_ODR_8;
}

//******************************************************************************************
// Toggle Green LED
//******************************************************************************************
void Green_LED_Toggle(void){
	GPIOE->ODR ^= GPIO_ODR_ODR_8;
}

//******************************************************************************************
// LED Configurations dependent on the State: Off, Green, Yellow, Red
//******************************************************************************************
void LED_Off_State(void){
	Green_LED_Off();
	Red_LED_Off();
}

void LED_Green_State(void){
	Green_LED_On();
	Red_LED_Off();
}

void LED_Yellow_State(void){
	Green_LED_On();
	Red_LED_On();
}

void LED_Red_State(void){
	Green_LED_Off();
	Red_LED_On();
}


