#include "main.h"

int main(){
  u8 i = 0;
  u8 str[] = "HangZhou Silver Bullet Technology";
  delay_init();
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  LED_Init();
  LCD_Init();
  LCD_Clear(WHITE);
	while(1){
    delay_ms(200);
    LCD_ShowNum(0, 0, i, 3, 24, BLACK, WHITE);
//    DrawHLine(100, 100, 200, BLACK);
//    DrawRLine(100, 100, 200, BLACK);
//    i++;
    LCD_ShowString(50, 0, sizeof(str)*12, 24, 24, str, BLACK, WHITE);
//    LCD_DrawCircle(100, 100, 60, BLACK, 0);
    LCD_DrawRectangle(150, 150, 230, 160, BLACK, 1);
  }
}
