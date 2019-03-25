/*
ATmega328|P
 
 Reset	PC6|1   28|PC5
 B.RX	PD0|2   27|PC4
 B.TX	PD1|3   26|PC3
		PD2|4   25|PC2
		PD3|5   24|PC1
		PD4|6   23|PC0		Buzzer
VCC		Vcc|7   22|Gnd		GND
GND		Gnd|8   21|Aref
		PB6|9   20|AVcc		VCC
		PB7|10  19|PB5		SCK
		PD5|11  18|PB4		MISO
DHT11	PD6|12  17|PB3		MOSI
		PD7|13  16|PB2		LED
LED		PB0|14  15|PB1		LED
*/

#include "common.h"
#include "HAL_USART.h"
#include "bees_my_music.h"

// DHT11 global variable
#define DHT11_PIN PIND6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

char start_wel[]= "Hello, Welcome :)";
char error[]= "ERROR";
char Hum_pt[]= "Humidity = ";
char Temp_pt[]= "Temperature = ";
char Hum_siu[]= " %";
char Temp_c_siu[]= " C";	//Celsius
char Temp_f_siu[]= " F";	//Fahrenheit

bool pressed_f1 = false, pressed_f2 = false, pressed_f3 = false;

/*----------DHT11/Begin----------*/
void Request(){				//send start pulse/request 
	DDRD |= (1<<DHT11_PIN);
	PORTD |= (1<<DHT11_PIN);	/* set to on pin */
	_delay_ms(1000);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);				/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);	/* set to high pin */
}

void Response(){			//receive response from DHT11
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data(){		//receive data 
	for (int q=0; q<8; q++){
		while((PIND & (1<<DHT11_PIN)) == 0);	/* check received bit 0 or 1 */
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))				/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);						/* then its logic HIGH */
		else									/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}
void DTH11_final_code(int Temp_or_hum){
	char data[5];
	Request();				/* send start pulse */
	Response();				/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		Transmit_string(error);
		USART_SendLine();
	}
	
	else
	{
		//1 mean humidity in %
		if(Temp_or_hum == 1){
			itoa(I_RH,data,10);	/* Integer to string conversion */
			Transmit_string(Hum_pt);
			Transmit_string(data);
			Transmit_string(".");
			itoa(D_RH,data,10);
			Transmit_string(data);
			Transmit_string(Hum_siu);
			USART_SendLine();
		}
		//2 mean temp. in C and F
		else if(Temp_or_hum == 2){
			itoa(I_Temp,data,10);
			Transmit_string(Temp_pt);
			Transmit_string(data);
			Transmit_string(".");
			itoa(D_Temp,data,10);
			Transmit_string(data);
			Transmit_string(Temp_c_siu);
			USART_SendLine();
			
			Transmit_string(Temp_pt);
			itoa(CheckSum,data,10);
			Transmit_string(data);
			Transmit_string(Temp_f_siu);
			USART_SendLine();
		}
	}
	_delay_ms(500);
}
/*----------DHT11/End----------*/

/*----------Buzzer/Begin----------*/
void mid_state(){
	beep_2();	//lazer fire
	beep_7();	//mme 2ou22
	beep_2();	//lazer fire
	beep_8();	//IT exit
	//beep_8();	//IT exit
	beep_1();	//ou2 e22
	beep_2();	//lazer fire
	beep_7();	//mme 2ou22
	beep_3();	//ou2 e22
	/*beep_4();	//ou2 e22*/
	beep_5();	//muzz muzz
	beep_6();	//mou2 mouw
	beep_1();	//ou2 e22
	beep_2();	//lazer fire
	beep_7();	//mme 2ou22
	beep_3();	//ou2 e22
	/*beep_4();	//ou2 e22*/
	beep_5();	//muzz muzz
	beep_6();	//mou2 mouw
	beep_2();	//lazer fire
	//beep_2();	//lazer fire
	beep_7();	//mme 2ou22
	beep_2();	//lazer fire
	beep_8();	//IT exit
}
void inc_state(){
	beep_1();	//ou2 e22
	beep_2();	//ou2 e22
	beep_3();	//ou2 e22
	beep_4();	//ou2 e22
}
void speaker_info(){
	DDRC |= (1 << PINC0);
	PORTC |= (1 << PINC0);
	_delay_ms(100);
	PORTC &= ~(1 << PINC0);
	inc_state();
}
/*----------Buzzer/End----------*/

int main(void){
	DDRB |= 1 << PINB0;         // pin 0 of PORTB as output
	DDRB |= 1 << PINB1;         // pin 1 of PORTB as output
	DDRB |= 1 << PINB2;         // pin 2 of PORTB as output
	USART_Begin();
	int Data_in;
	Transmit_string(start_wel);
	USART_SendLine();
	speaker_info();
	_delay_ms(100);
	while(1){
		Data_in= USART_Receive();
		_delay_ms(100);
		//USART_SendByte(Data_in);
		if(Data_in == '1'){
			if(pressed_f1 == false){		//if false not On
				Transmit_string("Green LED -> ON");
				PORTB |= 1 << PINB0;		// switch PB0 to 1
				pressed_f1 = true;
			}
			else {
				Transmit_string("Green LED -> OFF");
				PORTB &= ~(1 << PINB0);		// switch PB0 to 0FF
				pressed_f1 = false;
			}
			USART_SendLine();
		}
		else if(Data_in == '2'){
			if(pressed_f2 == false){			//if false not On
				Transmit_string("Blue LED -> ON");
				PORTB |= 1 << PINB1;		// switch PB1 to 1
				pressed_f2 = true;
			}
			else {
				Transmit_string("Blue LED -> OFF");
				PORTB &= ~(1 << PINB1);		// switch PB1 to 0FF
				pressed_f2 = false;
			}
			USART_SendLine();
		}
		else if(Data_in == '3'){
			if(pressed_f3 == false){		//if false not On
				Transmit_string("Red LED -> ON");
				PORTB |= 1 << PINB2;	// switch PB2 to 1
				pressed_f3 = true;
			}
			else {
				Transmit_string("Red LED -> OFF");
				PORTB &= ~(1 << PINB2);		// switch PB2 to 0FF
				pressed_f3 = false;
			}
			USART_SendLine();
		}
		else if(Data_in == '4'){
			Transmit_string("|---- [Humidity] ----|");
			USART_SendLine();
			DTH11_final_code(1);
			_delay_ms(500);
		}
		else if(Data_in == '5'){
			Transmit_string("|---- [Temperature] ----|");
			USART_SendLine();
			DTH11_final_code(2);
			_delay_ms(500);
		}
		else if(Data_in == '6'){
			Transmit_string("|---- [Buzzer] ----|");
			USART_SendLine();
			Transmit_string("Enjoy!!!");
			mid_state();
			USART_SendLine();
			Transmit_string("Unfortunately, it's over now! play again!!");
		}
		_delay_ms(100);
	}
}