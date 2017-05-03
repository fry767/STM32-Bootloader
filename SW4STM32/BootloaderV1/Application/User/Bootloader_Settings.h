#include "com_interface.h"

#define START_FLASH_ADDRESS 0x08000000

#define BOOTLOADER_SIZE 20

#define COMMUNICATION_RECEIVE_FUNCTION(value,size)  Receive_Char_In_IT_Mode(value,size)
