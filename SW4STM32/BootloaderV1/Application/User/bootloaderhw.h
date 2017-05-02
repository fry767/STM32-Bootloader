#ifndef _BOOTLOADERHW_H
#define _BOOTLOADERHW_H

#ifdef __cplusplus
 extern "C" {
#endif
/*#include <stm32f1xx_hal_flash.h>
#include <stm32f1xx_hal_flash_ex.h>*/
#include "stm32f1xx_hal.h"

uint32_t Bootloader_WriteStorage8(uint8_t value,uint32_t* Address);
uint32_t Bootloader_WriteStorage32(uint32_t value, uint32_t* Address);
uint8_t Bootloader_EraseApp(void);
uint8_t Bootloader_CopyStorageInAppspace(void);
uint8_t Bootloader_Init(void);

#ifdef __cplusplus
}
#endif
#endif // _BOOTLOADERHW_H
