#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "stm32f10x.h"

#define PASS_ID ((uint32_t)0x1105)
#define CENTER_ID ((uint32_t)0x0001)

//CAN消息定义
#define HEAD_MESSAGE    0x50
#define ASK_MESSAGE     0x53
#define CAN_DATA_LEN    8

//CAN端口定义
#define CAN_TX_GPIO_PORT   GPIOB
#define CAN_TX_GPIO_PIN    GPIO_Pin_9
#define CAN_RX_GPIO_PORT   GPIOB
#define CAN_RX_GPIO_PIN    GPIO_Pin_8
#define CAN_GPIO_CLK       RCC_APB2Periph_GPIOB

void CAN_Config(void);
void CANMessage(uint8_t *message, uint8_t *data, uint8_t len);
void CAN_SENDMESSAGE(uint32_t STDID, uint32_t PASSID, uint8_t CAN_RTR, uint8_t CAN_ID, uint8_t CAN_DLC, uint8_t *Message);

#endif /* __BSP_CAN_H */
