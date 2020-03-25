# IPS LCD R61529 FT6236 Arduino eSPI Test
This is an example code used to test R61529 based LCD with FT6236 touch controller connected to an ESP32 MCU through parallel(8080) interface. This code uses eSPI library

Note: Although you will find some files that contains R61581 in it, but be aware that those are modified files from original eSPI library to support R61529 ICs (Some or all code was changed in those header files).

LCD Connection to the ESP32:
 
D0 -> GPIO 16
D1 -> GPIO 17
D2 -> GPIO 18
D3 -> GPIO 19
D4 -> GPIO 21
D5 -> GPIO 22
D6 -> GPIO 23
D7 -> GPIO 25

CSX -> GPIO 33
DCX -> GPIO 26
RSX -> GPIO 32
WRX -> GPIO 27
 
TOUCH IC connection to the ESP32:
 
SDA -> GPIO 15
SCL -> GPIO 14
INT -> GPIO 35
RST -> GPIO 32 (connected together with the LCD reset pin) 
