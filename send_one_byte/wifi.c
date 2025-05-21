/*
 * wifi.c: wifi web server using esp8266 as blackbox
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <string.h>
#include <util/delay.h>
#include "avr_serial.h"

int 	sprintf (char *__s, const char *__fmt,...);


int wait_connection() {
	int found = 0;
	char m[3];
	char c;

	m[0] = serial_get_char();
	m[1] = serial_get_char();

	while (!found) {
		m[2] = serial_get_char();
		if ((m[0] == 'I') && (m[1] == 'P') && (m[2] == 'D')) 
			found = 1;
		else {
			m[0]=m[1]; m[1]=m[2]; 
		}

	}
	c = serial_get_char();
	c = serial_get_char();

	return (c-48);
}

void cipsend_one_byte(int n, char c)
{
	int i;
	char dest[80];
	char at_un_byte[] = "AT+CIPSEND=%i,1";  /* en conexion n enviaremos 1 byte */
	char un_byte[2];

	un_byte[0] = c;
	un_byte[1] = '\0';

	sprintf(dest, at_un_byte, n);
	serial_put_str(dest);
	_delay_ms(40);
	serial_put_str(un_byte);
	_delay_ms(40);
}

void wifi_init_server()
{
	// AT y reset
	serial_put_str("AT");
	_delay_ms(400);
	serial_put_str("AT+RST");
	_delay_ms(400);

	// access point
	serial_put_str("AT+CWMODE=3");
	_delay_ms(400);

	// canal 1, access point ESP, sin clave (el cero) 
	serial_put_str("AT+CWSAP=\"AVR_wifi_ESP\",,1,0");
	_delay_ms(400);

	// mult conexiones
	serial_put_str("AT+CIPMUX=1");	/* 0: 1 conexion; 1: max 4 conexiones */
	_delay_ms(400);

	// servidor web
	serial_put_str("AT+CIPSERVER=1,80");
	_delay_ms(400);
}

void wifi_control() 
{
	int n, i;
	char c;

	wifi_init_server();

	n = wait_connection();
	while(1) {

		cipsend_one_byte(n, 'A');
		cipsend_one_byte(n, 'B');


	}
			      
}

