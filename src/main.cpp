/************************************************************************************
 * 
 * This is an example code used to test R61529 based LCD with FT6236 touch controller
 * connected to an ESP32 MCU through parallel(8080) interface. This code uses eSPI 
 * library
 * 
 * 
 * Note: Although you will find some files that contains R61581 in it, but be aware 
 * that those are modified files from original eSPI library to support R61529 ICs
 * (Some or all code was changed in those header files).
 * 
 * LCD Connection to the ESP32:
 * 
 * D0 -> GPIO 16
 * D1 -> GPIO 17
 * D2 -> GPIO 18
 * D3 -> GPIO 19
 * D4 -> GPIO 21
 * D5 -> GPIO 22
 * D6 -> GPIO 23
 * D7 -> GPIO 25
 * 
 * CSX -> GPIO 33
 * DCX -> GPIO 26
 * RSX -> GPIO 32
 * WRX -> GPIO 27
 * 
 * TOUCH IC connection to the ESP32:
 * 
 * SDA -> GPIO 15
 * SCL -> GPIO 14
 * INT -> GPIO 35
 * RST -> GPIO 32 (connected together with the LCD reset pin) 
 *
 *************************************************************************************/


#include <Arduino.h>

#include "../lib/TFT_eSPI/TFT_eSPI.h"
#include "Wire.h"

#define TOUCH_I2C_ADD 0x38
#define TOUCH_REG_XL 0x04
#define TOUCH_REG_XH 0x03
#define TOUCH_REG_YL 0x06
#define TOUCH_REG_YH 0x05

#define TOUCH_INT_PIN 35

#define COLOR_BACKGROUND 0x1084
#define COLOR_TOUCH_POINT TFT_BLUE

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

int touchX = 0;
int touchY = 0;
int oldTouchX = 0;
int oldTouchY = 0;

void drawTouchPlace(int x, int y, uint32_t col)
{
  int rectX = x - 10;
  int rectY = y - 10;
  if (rectX < 0)
    rectX = 0;
  if (rectY < 0)
    rectY = 0;
  if (rectX > 299)
    rectX = 299;
  if (rectY > 459)
    rectY = 459;

  tft.fillRect(rectX, rectY, 20, 20, col);
}

int getTouchInterruptPinValue()
{
  return digitalRead(TOUCH_INT_PIN);
}

int readTouchReg(int reg)
{
  int data = 0;
  Wire.beginTransmission(TOUCH_I2C_ADD);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(TOUCH_I2C_ADD, 1);
  if (Wire.available())
  {
    data = Wire.read();
  }
  return data;
}

int getTouchPointX()
{
  int XL = 0;
  int XH = 0;

  XH = readTouchReg(TOUCH_REG_XH);
  XL = readTouchReg(TOUCH_REG_XL);

  return ((XH & 0x0F) << 8) | XL;
}

int getTouchPointY()
{
  int YL = 0;
  int YH = 0;

  YH = readTouchReg(TOUCH_REG_YH);
  YL = readTouchReg(TOUCH_REG_YL);

  return ((YH & 0x0F) << 8) | YL;
}

void touchInit()
{
  Wire.begin(15, 14);
  Wire.setClock(40000);
  pinMode(35, INPUT);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("started");

  touchInit();

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(COLOR_BACKGROUND);

  Wire.beginTransmission(0x38);
  Wire.write(0xA4);
  Wire.write(0x00); //turn on interrupt
  Wire.endTransmission();

  tft.setTextSize(1);
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);

}

void loop()
{
  if (!getTouchInterruptPinValue())
  {
    touchX = getTouchPointX();
    touchY = getTouchPointY();

    if ((touchX != oldTouchX) || (touchY != oldTouchY))
    {
      tft.fillRect(0, 0, 65, 35, COLOR_BACKGROUND);
      drawTouchPlace(oldTouchX, oldTouchY, COLOR_BACKGROUND);
      drawTouchPlace(touchX, touchY, COLOR_TOUCH_POINT);
      oldTouchY = touchY;
      oldTouchX = touchX;

      tft.setCursor(0, 0);
      tft.println("X: " + String(touchX));
      tft.println("Y: " + String(touchY));
    }
    delay(400);
  }

  delay(5);
}