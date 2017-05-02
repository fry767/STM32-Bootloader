#include "test_comm.h"
#include "usart.h"
#include "com_interface.h"
#include "bootloaderHW.h"
#include "bootlib.h"
#include "Bootloader_Settings.h"

#define TIMEOUT_VALUE	10000 /* 1ms counter (Systick)*/
static uint32_t Address;
extern uint8_t usart1_rx_flag;

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
		char ch[] = "*";
		Send_Char(ch,sizeof(ch));
		Starting_Time = HAL_GetTick();
	}
	char ch[] = "\n\r";
	Send_Char(ch,sizeof(ch));
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

	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	char ch[] = "Bootloader initialized, send some CHAR\n\r";
	Send_Char(ch,sizeof(ch));
	HAL_UART_Receive_IT(&huart1,&Received_Value, 1);
	while(Current_Time < TIMEOUT_VALUE && Received_Value == 0)
	{
		Current_Time = HAL_GetTick() - Starting_Time;
	}
	if(Current_Time == TIMEOUT_VALUE)
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed TIMEOUT VALUE\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	Value_Read_In_Flash = Bootloader_WriteStorage8(Received_Value);
	if(Value_Read_In_Flash == Received_Value)
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
uint8_t test_MultipleWriteReceivedDataInFlash(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;

	uint8_t Number_Of_Write = 10;
	uint32_t Value_Read_In_Flash[Number_Of_Write];
	uint8_t Received_Value[Number_Of_Write] ;
	uint8_t flag_Wrong_RCV = 0;
	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

	char ch[] = "Bootloader initialized, send some CHAR\n\r";
	Send_Char(ch,sizeof(ch));
	memset(Received_Value,0,Number_Of_Write);
	HAL_UART_Receive_IT(&huart1,(uint8_t*)Received_Value, Number_Of_Write);
	for(uint8_t i=0;i<Number_Of_Write;i++)
	{
		while(Current_Time < TIMEOUT_VALUE && Received_Value[i] == 0)
		{
			Current_Time = HAL_GetTick() - Starting_Time;
		}
		if(Current_Time == TIMEOUT_VALUE)
		{
			char ch[] = "test_WriteReceivedDataInFlash Failed TIMEOUT VALUE\n\r";
			Send_Char(ch,sizeof(ch));
			return 0;
		}
		Value_Read_In_Flash[i] = Bootloader_WriteStorage8(Received_Value[i]);
	}
	for(uint8_t i=0;i<Number_Of_Write;i++)
	{
		if(Value_Read_In_Flash[i] != Received_Value[i])
			flag_Wrong_RCV = 1;
	}
	if(!flag_Wrong_RCV)
	{
		char ch[] = "test_MultipleWriteReceivedDataInFlash PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_MultipleWriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_WriteLargerThanAvailableFiles(void)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;

	uint32_t Number_Of_Write = 55000;/* Only 54k available in Storage*/
	uint8_t Received_Value = 0;
	uint32_t Value_Read_In_Flash = 0;
	uint16_t i = 0;
	uint8_t flag_Wrong_RCV = 0;
	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

	char ch[] = "Bootloader initialized, send some CHAR\n\r";
	Send_Char(ch,sizeof(ch));

	HAL_UART_Receive_IT(&huart1,&Received_Value, 1);
	for( i = 0;i<Number_Of_Write;i++)
	{
		while(!usart1_rx_flag && Current_Time < TIMEOUT_VALUE)
		{
			Current_Time = HAL_GetTick() - Starting_Time;
		}
		if(Current_Time == TIMEOUT_VALUE)
		{
			return 0;
		}
		Value_Read_In_Flash = Bootloader_WriteStorage8(Received_Value);
		Starting_Time = HAL_GetTick();
		usart1_rx_flag = 0;
		HAL_UART_Receive_IT(&huart1,&Received_Value, 1);
	}
	if(i == Number_Of_Write)
	{
		char ch[] = "test_WriteLargerThanAvailableFiles Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
}
	else
	{
		char ch[] = "test_WriteLargerThanAvailableFiles Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}


}
void runAllCommTest(void)
{
	char ch[] = "Starting Com Test\n\r";
	Send_Char(ch,sizeof(ch));
	/*test_ReceptionInBlockingMode();
	test_ReceptionInNonBlockingMode();
	test_MultipleNonBlockingModeReception();
	test_SendHomeMenu();
	test_WriteReceivedDataInFlash();*/
	//test_MultipleWriteReceivedDataInFlash();
	test_WriteLargerThanAvailableFiles();
}
