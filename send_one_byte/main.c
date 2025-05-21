/*
 * main.c: little example program for controlling esp8266 using atmega328
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "avr_serial.h"

extern void wifi_control();

void main() {

	serial_init(9600);
	_delay_ms(2000);

	wifi_control();
	
	/* the execution continues in wifi.c, not here */
	for(;;);
}
