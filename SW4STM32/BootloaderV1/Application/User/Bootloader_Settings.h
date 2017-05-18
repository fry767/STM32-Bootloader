#include "com_interface.h"
#include "bootloaderhw.h"
#define START_FLASH_ADDRESS 0x08000000
#define BOOTLOADER_SIZE 30


#define COMMUNICATION_RECEIVE_FUNCTION(value,size)  Receive_Char_In_IT_Mode(value,size)
#define COMMUNICATION_SEND_FUNCTION(ptr,size)    Send_Buf8(ptr,size)


#define STORE_IN_EEPROM_FUNCTION(rcv_value)		    Bootloader_WriteStorage32(rcv_value);
#define READ_IN_MEMORY(Address)					    Bootloader_Read(Address)
#define GET_STORAGE_ADDRESS()						Bootloader_GetStorageAddress();
