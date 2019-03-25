/*
 * bees_my_music.h
 *
 * Created: 3/22/2019 6:34:09 AM
 *  Author: mohammadmusleh3
 */ 


#ifndef BEES_MY_MUSIC_H_
#define BEES_MY_MUSIC_H_

void delay_us(int us){
	for (int i = 0; i < us; i++){
		_delay_us(1);
	}
}

void beep_main(){
	for (int i = 100; i < 200; i+=5) {
		PORTC = 0x01;
		delay_us(i);
		PORTC = 0x00;
		delay_us(500);
	}
}

void beep_1(){
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(20);
		PORTC = 0x00;
		delay_us(980);
	}
}

void beep_2(){
	beep_main();
	_delay_ms(300);
	beep_main();
	_delay_ms(200);
	beep_main();
}

void beep_3(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(20);
		PORTC = 0x00;
		delay_us(980);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(67);
		PORTC = 0x00;
		delay_us(600);
	}
}

void beep_4(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(200);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(97);
		PORTC = 0x00;
		delay_us(300);
	}
}

void beep_5(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(i+30);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(200-i);
	}
}

void beep_6(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(i+40);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(100+i);
	}
}

void beep_7(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(300);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(200);
	}
}
void beep_8(){
	_delay_ms(150);
	for (int i = 0; i < 100; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(600);
	}
	
	_delay_ms(100);
	
	for (int i = 0; i < 200; i++) {
		PORTC = 0x01;
		delay_us(1);
		PORTC = 0x00;
		delay_us(30);
	}
}
#endif /* BEES_MY_MUSIC_H_ */