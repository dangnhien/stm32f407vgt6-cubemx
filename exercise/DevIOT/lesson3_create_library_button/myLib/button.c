

#include "button.h"
	
	__weak void btn_pressing_callback()
	{
		
	}

	__weak void btn_release_callback()
	{
		
	}

	__weak void btl_press_short_callback()
	{
		
	}

	__weak void btl_press_slow_callback()
	{
		
	}
	
	void btn_handle(Button_Typdef *ButtonX)
	{
		// -----------------Loc nhieu----------------------
		uint8_t status_btn = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
		
		if(status_btn != ButtonX->btn_filter)
		{
			ButtonX->btn_filter = status_btn;
			ButtonX->is_debouncing = 1;
			ButtonX->time_debounce = HAL_GetTick();
		}
		
		// ----------------- Trang thai xac lap-----------------
		if( (ButtonX->is_debouncing == 1) && (HAL_GetTick() - ButtonX->time_debounce >= 15) )
		{
			ButtonX->is_debouncing = 0;
			ButtonX->btn_current = ButtonX->btn_filter;
		}
		
		// ---------------------- Xu ly nhan nha--------------------------
		if(ButtonX->btn_current != ButtonX->btn_last)
		{
			if(ButtonX->btn_current == Button_Pressed)
			{
				btn_pressing_callback();
				ButtonX->time_start_press = HAL_GetTick();
				ButtonX->press_slow=1;
			}else{
				if(HAL_GetTick() - ButtonX->time_start_press <= 1000)
					btl_press_short_callback();
				btn_release_callback();
				ButtonX->press_slow = 0;
			}
			
			ButtonX->btn_last = ButtonX->btn_current;
		}
		// ---------------------- Xu ly nhan giu-------------------------------
		if(ButtonX->press_slow == 1  && HAL_GetTick() - ButtonX->time_start_press >= 3000)
		{
			ButtonX->press_slow = 0;	// do for function btl_press_slow_callback(); only run once
			btl_press_slow_callback();
		}
	}
	
	void button_init(Button_Typdef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
	{
		ButtonX->GPIOx = GPIOx;
		ButtonX->GPIO_Pin = GPIO_Pin;
	}
		












	