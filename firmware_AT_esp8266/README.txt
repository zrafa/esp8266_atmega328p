
- GPIO1 to GND to get into flashing mode

- esptool  write_flash  0x0 Cytron_ESP-01S_AT_Firmware_V2.2.0.bin

- remove GPIO1 so MCU boots normally

- check with AT commands to MCU. DONT FORGET \n\r after every AT command!!!
