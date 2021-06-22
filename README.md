# IPS LCD R61529 FT6236 Arduino eSPI Test
This is an example code used to test R61529 (bought from [Aliexpress](https://www.aliexpress.com/item/32940608152.html?spm=a2g0o.productlist.0.0.66e773f6vAhLCI&algo_pvid=f9214500-0ba3-4aff-b9a8-9fc9dc51cd2a&algo_expid=f9214500-0ba3-4aff-b9a8-9fc9dc51cd2a-16&btsid=25887317-95e8-4f7a-aabc-1913fdfeaadf&ws_ab_test=searchweb0_0,searchweb201602_6,searchweb201603_53)) based LCD with FT6236 touch controller connected to an ESP32 MCU through parallel(8080) interface. This code uses eSPI library.

You can find additional information at my blog: https://daumemo.com/ips-lcd-esp32-with-espi-library-and-touch-screen-diy-generator-part-9/

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

![Screen showns touch point](https://daumemo.com/wp-content/uploads/2020/03/ESP32-touch-test-code-with-eSPI-and-FT6236-controller.jpg)
