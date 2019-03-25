/*
 * common.h
 *
 * Created: 3/22/2019 3:02:05 AM
 *  Author: mohammadmusleh3
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>	//bool

/* Declaration for Bluetooth*/
#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*8UL)-1) // set baud rate value for UBRR
#define MYUBRR FOSC/16/BAUD-1



#endif /* COMMON_H_ */