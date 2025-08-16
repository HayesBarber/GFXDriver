#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <vector>

#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 18
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 480
#define DEBOUNCE_DELAY_MS 300
#define THIRD_HEIGHT (DISPLAY_HEIGHT / 3)

enum Third { UPPER_THIRD, MIDDLE_THIRD, LOWER_THIRD };

struct ThirdCenter {
  uint16_t x;
  uint16_t y;
};

static const ThirdCenter THIRD_CENTERS[] = {
    {DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT / 6)},    // UPPER_THIRD
    {DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT / 2)},    // MIDDLE_THIRD
    {DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT * 5) / 6} // LOWER_THIRD
};

struct ThirdCorner {
  uint16_t x;
  uint16_t y;
};

static const ThirdCorner THIRD_TOPLEFTS[] = {
    {0, 0},               // UPPER_THIRD
    {0, THIRD_HEIGHT},    // MIDDLE_THIRD
    {0, THIRD_HEIGHT * 2} // LOWER_THIRD
};

class GFXDriver {
public:
  GFXDriver();
  void init(void (*onTouch)());
  void writeText(String text);
  void writeText(String text, Third third);
  void loop();
  void off();
  void clearThird(Third third);
  void drawColors(const std::vector<uint16_t> &colors);
  void drawColors(const std::vector<uint16_t> &colors, Third third);
  uint16_t hexToColor(const String &hexString);

private:
  void (*_onTouch)();
  Arduino_DataBus *_bus;
  Arduino_ESP32RGBPanel *_rgbpanel;
  Arduino_RGB_Display *_gfx;

  void i2cRead(uint16_t addr, uint8_t reg_addr, uint8_t *reg_data,
               uint32_t length);
};
