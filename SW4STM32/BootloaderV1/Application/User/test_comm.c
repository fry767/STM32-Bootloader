#include "test_comm.h"
#include "usart.h"
#include "com_interface.h"
#include "bootloaderHW.h"
#include "bootlib.h"
#include "Bootloader_Settings.h"

#define TIMEOUT_VALUE	10000 /* 1ms counter (Systick)*/
static uint32_t Address;
uint8_t test_ReceptionInBlockingMode(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	uint8_t value = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
	while(value!=0x7E && Current_Time < TIMEOUT_VALUE)
	{
		value = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
		Current_Time = HAL_GetTick() - Starting_Time;
	}

	if(value == 0x7E)
	{
		char ch[] = "ReceptionInBlockingMode PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "ReceptionInBlockingMode Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_ReceptionInNonBlockingMode(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	uint8_t value = 0;
	HAL_UART_Receive_IT(&huart1,&value, 1);
	while(value!=0x7E && Current_Time < TIMEOUT_VALUE)
	{
		Current_Time = HAL_GetTick() - Starting_Time;
	}

	if(value == 0x7E)
	{
		char ch[] = "test_ReceptionInNonBlockingMode PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_ReceptionInNonBlockingMode Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_MultipleNonBlockingModeReception(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	uint8_t Number_Of_Reception  = 10;
	uint8_t value[Number_Of_Reception];
	uint8_t flag_rcv_error = 0;
	HAL_UART_Receive_IT(&huart1,(uint8_t*)value, Number_Of_Reception);
	for(uint8_t i = 0;i < Number_Of_Reception; i++)
	{
		while(value[i]!=0x7E && Current_Time < TIMEOUT_VALUE)
		{
			Current_Time = HAL_GetTick() - Starting_Time;
		}
		if(Current_Time == TIMEOUT_VALUE)
		{
			flag_rcv_error = 1;
			break;
		}
		Starting_Time = HAL_GetTick();
	}
	if(!flag_rcv_error)
	{
		char ch[] = "test_MultipleNonBlockingModeReception PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_MultipleNonBlockingModeReception Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_SendHomeMenu(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	uint8_t value = 0;
	HAL_UART_Receive_IT(&huart1,&value, 1);
	Send_Home_Menu();
	while(value!=0x7E && Current_Time < TIMEOUT_VALUE)
	{
		Current_Time = HAL_GetTick() - Starting_Time;
	}

	if(value == 0x7E)
	{
		char ch[] = "test_SendHomeMenu PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_SendHomeMenu Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}


}
uint8_t test_WriteReceivedDataInFlash(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	uint32_t Value_Read_In_Flash = 0;
	uint8_t Received_Value = 0;

	Address = START_FLASH_ADDRESS;
	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	HAL_UART_Receive_IT(&huart1,&Received_Value, 1);
	while(Current_Time < TIMEOUT_VALUE)
	{
		Current_Time = HAL_GetTick() - Starting_Time;
	}
	if(Current_Time == TIMEOUT_VALUE)
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	Value_Read_In_Flash = Bootloader_WriteStorage8(Received_Value,&Address);
	if(Value_Read_In_Flash != Received_Value)
	{
		char ch[] = "test_WriteReceivedDataInFlash PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
void runAllCommTest(void)
{
	test_ReceptionInBlockingMode();
	test_ReceptionInNonBlockingMode();
	test_MultipleNonBlockingModeReception();
	test_SendHomeMenu();
	test_WriteReceivedDataInFlash();
}
