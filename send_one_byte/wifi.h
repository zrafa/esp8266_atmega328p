/*
 * wifi.h: wifi web server using esp8266 as blackbox
 * 
 * Rafael Ignacio Zurita (c) 2022 <rafa@fi.uncoma.edu.ar>
 */

#ifndef WIFI_H
#define WIFI_H

int wait_connection();
void cipsend_one_byte(int n, char c);
void wifi_init_server();

#endif /* WIFI_H */
