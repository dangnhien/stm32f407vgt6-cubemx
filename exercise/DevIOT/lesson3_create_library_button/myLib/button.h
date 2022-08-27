#ifndef BUTTON_H
#define BUTTON_H

	#include "main.h"
	
	enum StatusLed{
		LED_OFF,
		LED_ON
	};

	enum StatusButton
	{
		Button_Released,
		Button_Pressed
	};

	
	
	typedef struct{
		uint8_t btn_current, btn_last ;
		uint8_t btn_filter ;
		uint32_t time_debounce;
		uint8_t is_debouncing;
		uint32_t time_start_press;

		uint8_t press_slow;

		uint8_t test;
		
		GPIO_TypeDef *GPIOx;
		uint16_t GPIO_Pin;
		
		uint8_t ids;
		
	}Button_Typdef;
	
	
	
	void button_init(Button_Typdef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
	void btn_handle(Button_Typdef *ButtonX);
		

#endif
