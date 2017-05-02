#ifndef _COMM_INTERFACE_H
#define _COMM_INTERFACE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "usart.h"

void Send_Home_Menu(void);
void Send_Char(char* ch,uint8_t size);
void Receive_Char_In_Blocking_Mode(uint8_t* value,uint8_t size);
uint8_t Receive_Char_In_IT_Mode(uint8_t* value,uint8_t size);
uint8_t Comm_USART_Wait_For_Key(char* key);

#ifdef __cplusplus
}
#endif
#endif
