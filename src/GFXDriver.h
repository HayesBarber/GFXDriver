#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>

class GFXDriver {
public:
  GFXDriver();
  void init(void (*onTouch)());

private:
  void (*_onTouch)();
  Arduino_DataBus *_bus;
  Arduino_ESP32RGBPanel *_rgbpanel;
  Arduino_RGB_Display *_gfx;
};
