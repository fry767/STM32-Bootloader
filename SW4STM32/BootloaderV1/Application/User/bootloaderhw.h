#ifndef _BOOTLOADERHW_H
#define _BOOTLOADERHW_H

#ifdef __cplusplus
 extern "C" {
#endif
/*#include <stm32f1xx_hal_flash.h>
#include <stm32f1xx_hal_flash_ex.h>*/
#include "stm32f1xx_hal.h"
uint32_t Bootloader_Read(uint32_t Address);
uint32_t Bootloader_WriteStorage8(uint8_t value);
uint32_t Bootloader_WriteStorage32(uint32_t value);
uint32_t Bootloader_WriteApp32(uint32_t value);
uint8_t Bootloader_EraseApp(void);
uint8_t Bootloader_EraseUserSpace(void);
uint8_t Bootloader_CopyStorageInAppspace(void);
uint8_t Bootloader_ManualWrite(uint32_t value,uint32_t* Address);
uint8_t Bootloader_Init(void);
uint8_t Bootloader_WriteDeviceID(uint8_t DeviceID);
uint8_t Bootloader_GetDeviceID(void);
uint8_t Bootloader_WriteDeviceName(uint8_t* ch, uint16_t nameSize);
void Bootloader_ReadDeviceName(uint8_t* DeviceName);
uint32_t* Bootloader_GetStorageAddress(void);
uint32_t* Bootloader_GetAppAddress(void);
uint16_t Bootloader_GetFlashSize(void);
#ifdef __cplusplus
}
#endif
#endif // _BOOTLOADERHW_H
