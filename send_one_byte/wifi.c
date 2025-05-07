/*
 * wifi.c: wifi web server using esp8266 as blackbox
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "avr_serial.h"

int 	sprintf (char *__s, const char *__fmt,...);

/* Commands in PROGMEM Flash */
const __flash char mm1[] = "AT";
const __flash char mm2[] = "AT+RST";
const __flash char mm3[] = "AT+CWMODE=3";
const __flash char mm4[] = "AT+CWSAP=\"AVR_wifi_ESP\",,1,0";
const __flash char mm5[] = "AT+CIPMUX=1";		/* 0 : una conexion;    1 : hasta 4 conexiones */ 
const __flash char mm6[] = "AT+CIPSERVER=1,80";
/*
const __flash char mm7[] = "AT+CIPSEND=%i,1";  /* en conexion 0 enviaremos 25 bytes */
/*
const __flash char mm8[] = "<html><head></head><body>";
const __flash char mm9[] = "AT+CIPSEND=%i,19";
const __flash char mm10[] = "<h1>Web demo  </h1>";
const __flash char mm11[] = "AT+CIPSEND=%i,45";
const __flash char mm12[] = "AT+CIPSEND=%i,14";
const __flash char mm13[] = "</body></html>";
const __flash char mm14[] = "AT+CIPCLOSE=%i";
*/

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
	_delay_ms(400);
	serial_put_str(un_byte);
	_delay_ms(400);
}

void wifi_web_server() {

	char msg[46], msg2[20];
	int n, i;

	// AT y reset
	serial_put_str2(mm1);
	_delay_ms(400);
	serial_put_str2(mm2);
	_delay_ms(400);

	// access point
	serial_put_str2(mm3);
	_delay_ms(400);

	// canal 1, access point ESP, sin clave (el cero) 
	serial_put_str2(mm4);
	_delay_ms(400);

	// mult conexiones
	serial_put_str2(mm5);
	_delay_ms(400);

	// servidor web
	serial_put_str2(mm6);
	_delay_ms(400);

	n = wait_connection();
	while(1) {

		cipsend_one_byte(n, 'A');
		_delay_ms(400);
		cipsend_one_byte(n, 'B');
		_delay_ms(400);
	}

			      
}

