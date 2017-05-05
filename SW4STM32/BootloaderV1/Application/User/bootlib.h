#ifndef _BOOTLIB_H
#define _BOOTLIB_H
#include <stdint.h>
#include <string.h>
#include "stm32f1xx_hal.h"
void Bootloader_SplitFlash(uint16_t size, uint16_t *splitted_part);
void Bootloader_CalculateSectorForStorage(uint16_t size,uint32_t* erase_address);
void Bootloader_CalculateSectorForApp(uint16_t size,uint32_t* app_address);
void Bootloader_JumpToApplication(void);
char* Bootloader_Waiting_For_Key(void);
#endif // _BOOTLIB_H
