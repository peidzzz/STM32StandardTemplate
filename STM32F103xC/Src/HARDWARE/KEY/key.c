#include "key.h"
#include "delay.h"

#if 1
void KEY_Init(void)
{
}

//按键处理函数
//返回按键值
//mode:
//		0,不支持连续按;
//		1,支持连续按;
//返回值：
//		0，没有任何按键按下
//		KEY0_PRES，KEY0按下
uint8_t KEY_Scan(void)
{
//    static uint8_t key_up = 0; //按键按松开标志
//    if (key_up && (KEY0 == 0)) {
//        delay_ms(10);          //去抖动
//        key_up = 0;
//        if (KEY0 == 0)
//            return KEY0_PRES;
//    } else if (KEY0 == 1)
//        key_up = 1;
//    return 0;                  // 无按键按下
  return 0;
}
#endif
