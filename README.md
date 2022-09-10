# esp8266_atmega328p

C example for controlling esp8266 via AT commands using arduino atmega328p avr - IOT stable connection

![avr_and_esp8266](/pic.jpg)

This repo aims to provide a stable wifi web server tiny C example code 
(simple IOT: internet of things), using an Arduino UNO (or similar)
and an esp8266 as a blackbox. The code is useful as starting point 
into other bigger projects.

I decided to put this code here after several days with unstable 
wifi / web server / html code from several sources. The esp8266 is great
(cheap, tiny, low power, wifi), but it is a "bit fragile" if you
do not use the proper setup. Moreover, I have not found 
an example like this (baremetal C code for avr), so I wanted 
to share it and lets it available for others (and for own projects coming :-)
(sometimes you found a solution, and after some weeks or days, you do not
remember it anymore :( , so better if we put it on some public place for easy
reuse).

Some important notes about esp8266
==================================

- The ultra cheap tiny esp8266 is it: https://www.sparkfun.com/products/17146

- For solid wifi functionality you MUST change the speed to 9600,8,1
Some chips come already with that speed as default, others not. If your chip
is by default at 115200, you can use the below command:

AT+UART_DEF=9600,8,1,0,0

That will change the configuration on flash (after off-on you will
have 9600bpp as speed).

- You need to send \r \n after every AT command sent to esp8266.

- The esp8266 just works on 3.3V!. BUT IMPORTANT AND USEFUL: the rx/tx
i/o pins are 5V tolerant!! (so you can connect them to arduino directly).
(the esp's company owner published this note).


Compiling and flashing
======================

make clean; 
make; 
make flash  

(If flash fails, then change the speed and/or the device for the avrdude 
command.)


Usage
=====

Join your laptop/phone to "AVR_wifi_ESP" wifi.

Then, you can point chrome or firefox (or whatever) to http://192.168.4.1
(192.168.4.1 is the IP address of esp8266). The request from chrome/firefox
will arrive to AVR atmega328p, and it will answer with a simple web page.

The setup is multiple connections (4 max.). This example will reply to
all of them. The web server listens on port 80.


Read the .c code for further details.
