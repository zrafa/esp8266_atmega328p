/*
 * main.c: little example program for controlling esp8266 using atmega328
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "avr_serial.h"
#include "wifi.h"

void main() {

	int n;
	char c;

	serial_init(9600);
	_delay_ms(2000);

	wifi_init_server();

	n = wait_connection();
	cipsend_one_byte(n, 'A');
	while(1) {

		c = wait_byte();
		cipsend_one_byte(n, c);


	}
}

