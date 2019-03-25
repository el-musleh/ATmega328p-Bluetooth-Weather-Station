
#ifndef _HAL_USART_H_
#define _HAL_USART_H_

#include <avr/io.h>
#include "common.h"

void USART_Begin(void);
void USART_SendByte(unsigned char x);	//USART_Transmit
void Transmit_string(const char *s);
void USART_SendData(const char *data, unsigned int leng);
void USART_Print(int data);
void USART_SendLine(void);
unsigned char USART_Receive(void);	//USART_Receive

#endif
