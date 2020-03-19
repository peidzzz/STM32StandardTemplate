#include "bsp_can.h"


/** 支持时间戳，可以过滤特定ID报文  实际应用中常使用CAN_OPEN
 	* 
	* 
	* 
  */
void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	RCC_APB2PeriphClockCmd(CAN_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = CAN_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = CAN_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
}

void CAN_Mode_Config(void)
{
	CAN_InitTypeDef CAN_InitTypeStruct;
	
	CAN_InitTypeStruct.CAN_ABOM = ENABLE;           //自动离线管理
	CAN_InitTypeStruct.CAN_AWUM = ENABLE;           //自动唤醒（比较节能）
	CAN_InitTypeStruct.CAN_Mode = CAN_Mode_Normal;  //工作模式
	CAN_InitTypeStruct.CAN_NART = ENABLE;           //自动重传
	CAN_InitTypeStruct.CAN_RFLM = ENABLE;           //锁定模式，锁定后当消息溢出后新报文将会被丢弃
	CAN_InitTypeStruct.CAN_TTCM = DISABLE;          //时间戳功能
	CAN_InitTypeStruct.CAN_TXFP = ENABLE;           //报文优先级判定
	
	CAN_InitTypeStruct.CAN_BS1 = CAN_BS1_3tq;
	CAN_InitTypeStruct.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitTypeStruct.CAN_SJW = CAN_SJW_1tq;
	CAN_InitTypeStruct.CAN_Prescaler = 12;
	
	CAN_Init(CAN1, &CAN_InitTypeStruct);
}

void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	CAN_FilterInitStruct.CAN_FilterActivation     = ENABLE;
//  CAN_FilterInitStruct.CAN_FilterActivation     = DISABLE;

	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitStruct.CAN_FilterNumber         = 0;
	CAN_FilterInitStruct.CAN_FilterScale          = CAN_FilterScale_32bit;
//	CAN_FilterInitStruct.CAN_FilterMode           = CAN_FilterMode_IdMask;     //过滤器工作模式设置为掩码模式
	CAN_FilterInitStruct.CAN_FilterMode           = CAN_FilterMode_IdList;      //过滤器工作模式设置为列表模式（白名单）
	CAN_FilterInitStruct.CAN_FilterIdHigh         = ((CENTER_ID<<3 | CAN_Id_Extended | CAN_RTR_Data)&0xFFFF0000)>>16;
	CAN_FilterInitStruct.CAN_FilterIdLow          = ((CENTER_ID<<3 | CAN_Id_Extended | CAN_RTR_Data)&0XFFFF);
	
//	CAN_FilterInitStruct.CAN_FilterMaskIdHigh     = 0xFFFF;
//	CAN_FilterInitStruct.CAN_FilterMaskIdLow      = 0xFFFF;
	
	CAN_FilterInit(&CAN_FilterInitStruct);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

void CAN_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_Initstructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_Initstructure.NVIC_IRQChannel                    = USB_LP_CAN1_RX0_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority  = 1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority         = 1;
	NVIC_Initstructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_Initstructure);
}

void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_Mode_Config();
	CAN_Filter_Config();
	CAN_NVIC_Config();
}

void CANMessage(uint8_t *message, uint8_t *data, uint8_t len){
	uint8_t i;
	for(i = 0;i < len;i++){
		data[i] = message[i];
	}
}

void CAN_SENDMESSAGE(uint32_t STDID, uint32_t PASSID, uint8_t CAN_RTR, uint8_t CAN_ID, uint8_t CAN_DLC, uint8_t *Message){
	CanTxMsg CAN_TRAN_DATE;
	uint8_t mail;
	CAN_TRAN_DATE.StdId = STDID;
	CAN_TRAN_DATE.ExtId = PASSID;
	CAN_TRAN_DATE.RTR   = CAN_RTR;
	CAN_TRAN_DATE.IDE   = CAN_ID;
	CAN_TRAN_DATE.DLC   = CAN_DLC;
	CANMessage(Message, CAN_TRAN_DATE.Data, CAN_TRAN_DATE.DLC);
	mail = CAN_Transmit(CAN1, &CAN_TRAN_DATE);
	while(CAN_TransmitStatus(CAN1, mail) == CAN_TxStatus_Failed);
}
