/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init();
void serial_put_char(char);
int serial_new_data(void);
char serial_get_char(void);
void serial_put_str(char *);
void serial_put_str2(const __flash char m[]);

#endif /* _SERIAL_H */
