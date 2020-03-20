#include "main.h"

int main(){
  u8 str[] = "STM32F103xC Template by Peidzzz";
  // Add init here
  delay_init();
  LED_Init();
  LCD_Init();
  // Init end
  
  LCD_Clear(WHITE);
	while(1){
    /*** Add you own code here ***/
    LCD_ShowString(50, 0, 12*sizeof(str), 24, 24, str,  BLACK, WHITE);
    /*** Code end ***/
  }
}
