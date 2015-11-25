/***************************************************

  This sketch implements a simple XY display

  It is based heavily on prior work from:

    Adafruit:         http://www.adafruit.com/products/1480
    Guy van den Berg: http://www.microsmart.co.za/technical/2014/03/01/advanced-arduino-adc/

  You can get this file from:
    https://github.com/mjoldfield/xy-arduino-toy
  or read more at:
    http://mjoldfield.com/atelier/2015/11/cheap-xy-display.html

  A lightly modified version of the code is used in:
    https://www.geocaching.com/seek/cache_details.aspx?wp=GC5WKF3

  **********************************************************************

  What follows below is the header from the Adafruit example.

  **********************************************************************

  This is an example sketch for the Adafruit 2.2" SPI display.
  This library works with the Adafruit 2.2" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/1480
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

// These are the pins used for the UNO
// We use hardware SPI, so the values for _sclk, _miso, and _mosi are
// fixed.
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 8
#define _dc 10
#define _rst 9

// Crank up ADC speed as per
// http://www.microsmart.co.za/technical/2014/03/01/advanced-arduino-adc/	
const unsigned char PS_16  = (1 << ADPS2);					
const unsigned char PS_32  = (1 << ADPS2) | (1 << ADPS0);			
const unsigned char PS_64  = (1 << ADPS2) | (1 << ADPS1);			
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

void setup()
{
  // ADC prescaler to 16 => 1MHz clock with 16MHz part => ~20us per sample	
   ADCSRA &= ~PS_128;								
   ADCSRA |=  PS_16 ;					
  
  tft.begin();
  
  tft.fillScreen(ILI9340_BLACK);
  tft.setRotation(1);
  
  tft.setTextColor(ILI9340_WHITE);
  tft.setTextSize(2);
  tft.println("        XY display");

  delay(1000);
  
  tft.fillScreen(ILI9340_BLACK);
}

void loop(void) 
{
  int x = analogRead(0);
  int y = analogRead(1);
  
  tft.drawPixel(x >> 2, 240 - (y >> 2), ILI9340_GREEN);
}
