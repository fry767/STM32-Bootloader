/*	###################################
 *				Boot	Menu
 *	###################################
 *
 **/
#include "com_interface.h"

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
