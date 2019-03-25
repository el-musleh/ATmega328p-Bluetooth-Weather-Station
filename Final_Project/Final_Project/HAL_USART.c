#include "HAL_USART.h"

void USART_Begin(void)
{
	/*Set baud rate */
	UBRR0H = (BAUDRATE>>8);	// shift the register right by 8 bits to get the upper 8 bits
	UBRR0L = BAUDRATE;		// set baud rate
	/*Double transmission speed */
	UCSR0A |= (1 << U2X0);
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data stop bit */
	UCSR0C = (3<<UCSZ00);
}

unsigned char USART_Receive( void ){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_SendByte(unsigned char x)	
{
	while(!((UCSR0A)&(1<<UDRE0)));
	UDR0=x;
}

void Transmit_string(const char *s){
	char c;
	while ( (c = *s++) ){
		USART_SendByte(c);
		_delay_ms(2);
	}
}

void USART_SendData(const char *data, unsigned int leng)
{
	while(leng)
	{
		while(!((UCSR0A)&(1<<UDRE0)));
		UDR0=*data;
		data++;
		leng--;
	}
}

void USART_Print(int data)
{
	if(data<0)
	{
		data=~data+1;
		USART_SendByte('-');	
	}
	USART_SendByte(data/10000+48);
	USART_SendByte(data%10000/1000+48);	
	USART_SendByte(data%1000/100+48);	
	USART_SendByte(data%100/10+48);	
	USART_SendByte(data%10+48);	
}

void USART_SendLine(void)
{
	USART_SendByte(0X0D);
	USART_SendByte(0X0A);
}


