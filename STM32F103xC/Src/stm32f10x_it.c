/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
//  CAN_Receive(CAN1, CAN_FIFO0, &CAN_RECE_DATE);
//	if (CAN_RECE_DATE.Data[0] == 0x50) {
//		if (CheckData(CAN_RECE_DATE.Data)) {
//      switch (CAN_RECE_DATE.Data[1]) {
//        case 0x54: 
//          discharge1->DischargeId = CAN_RECE_DATE.Data[5] * 181;
//          StoreDischargeData(discharge1);
//          delay_ms(100);
//          __set_FAULTMASK(1);   //STM32程序软件复位  
//          NVIC_SystemReset(); 
//        case 0x53: 
//          CAN_RECE_FLAG = 1;
//          break;
//      }
//      if (CAN_RECE_DATE.Data[1] == 0x54) {
//        discharge1->DischargeId = CAN_RECE_DATE.Data[5] * 181;
//        StoreDischargeData(discharge1);
//        delay_ms(100);
//        __set_FAULTMASK(1);   //STM32程序软件复位  
//        NVIC_SystemReset(); 
//      } else if (CAN_RECE_DATE.Data[1] == 0x53) CAN_RECE_FLAG = 1;
//		}
//	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
