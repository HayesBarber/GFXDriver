#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>

#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 18
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 480
#define DEBOUNCE_DELAY 300

class GFXDriver {
public:
  GFXDriver();
  void init(void (*onTouch)());
  void writeText(String text);

private:
  void (*_onTouch)();
  Arduino_DataBus *_bus;
  Arduino_ESP32RGBPanel *_rgbpanel;
  Arduino_RGB_Display *_gfx;
};
