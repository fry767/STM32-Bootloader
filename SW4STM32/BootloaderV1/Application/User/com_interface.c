/*	###################################
 *				Boot	Menu
 *	###################################
 *
 **/
#include "com_interface.h"

#define BOOTLOADER_KEY	"TONYIDROPLASAUCE"
#define TIMEOUT_VALUE 10000 /* 1ms counter (SysTick)*/
#define IS_KEY_RECEIVED(a,b)	(a==b)?1:0

extern uint8_t usart1_rx_flag;


char Home_Menu[] = {
"#####################################\n\r\
           BOOT MENU \n\r\
#####################################\n\r\
1. Bootloader Version\n\r\
2. Send Firmware\n\r\
3. Check Current Firmware\n\r\
4. Press ~ for test\n\r"
};

void Send_Home_Menu(void)
{
	HAL_UART_Transmit(&huart1,Home_Menu,sizeof(Home_Menu),1000000);
}
void Send_Char(char* ch,uint8_t size)
{
	HAL_UART_Transmit(&huart1,ch,size,10000);
}
void Send_Buf8(uint8_t* buf,uint8_t size)
{
	HAL_UART_Transmit(&huart1,buf,size,10000);
}
void Receive_Char_In_Blocking_Mode(uint8_t* value,uint8_t size)
{
	HAL_UART_Receive(&huart1,value,size,TIMEOUT_VALUE);
}
uint8_t Receive_Char_In_IT_Mode(uint8_t* value,uint8_t size)
{
	uint32_t Starting_Time = HAL_GetTick();
	uint32_t Current_Time = 0;
	usart1_rx_flag = 0;
	HAL_UART_Receive_IT(&huart1,value, size);
	while(!usart1_rx_flag && Current_Time < TIMEOUT_VALUE)
	{
		Current_Time = HAL_GetTick() - Starting_Time;

	}
	if(Current_Time == TIMEOUT_VALUE)
		return 0;
	else
		return size;
}
uint8_t Comm_USART_Wait_For_Key(char* key)
{
	uint8_t value = 0;
	Receive_Char_In_IT_Mode(&value,1);
	return IS_KEY_RECEIVED(value,*key);
}
uint8_t Comm_USART_Poll_For_Key(char* key)
{

}
