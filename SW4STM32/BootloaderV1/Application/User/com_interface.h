#ifndef _COMM_INTERFACE_H
#define _COMM_INTERFACE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "usart.h"

void Send_Home_Menu(void);
void Send_Char(char* ch,uint8_t size);


#ifdef __cplusplus
}
#endif
#endif
