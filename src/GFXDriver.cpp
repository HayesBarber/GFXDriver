#include "GFXDriver.h"

GFXDriver::GFXDriver() : _onTouch(nullptr) {
  _bus = new Arduino_SWSPI(GFX_NOT_DEFINED /* DC */, 1 /* CS */, 46 /* SCK */,
                           0 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

  _rgbpanel = new Arduino_ESP32RGBPanel(
      2 /* DE */, 42 /* VSYNC */, 3 /* HSYNC */, 45 /* PCLK */, 4 /* R0 */,
      41 /* R1 */, 5 /* R2 */, 40 /* R3 */, 6 /* R4 */, 39 /* G0/P22 */,
      7 /* G1/P23 */, 47 /* G2/P24 */, 8 /* G3/P25 */, 48 /* G4/P26 */,
      9 /* G5 */, 11 /* B0 */, 15 /* B1 */, 12 /* B2 */, 16 /* B3 */,
      21 /* B4 */, 1 /* hsync_polarity */, 10 /* hsync_front_porch */,
      8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
      1 /* vsync_polarity */, 10 /* vsync_front_porch */,
      8 /* vsync_pulse_width */, 20 /* vsync_back_porch */);

  _gfx = new Arduino_RGB_Display(
      DISPLAY_WIDTH /* width */, DISPLAY_HEIGHT /* height */, _rgbpanel,
      0 /* rotation */, true /* auto_flush */, _bus, GFX_NOT_DEFINED /* RST */,
      st7701_type5_init_operations, sizeof(st7701_type5_init_operations));
}

void GFXDriver::init(void (*onTouch)()) {
  _onTouch = onTouch;
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  _gfx->begin();
  _gfx->fillScreen(BLACK);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(4);
}

void GFXDriver::writeText(String text) {
  _gfx->fillScreen(BLACK);
  if (text.length() == 0) {
    return;
  }

  int16_t x1, y1;
  uint16_t textWidth, textHeight;
  _gfx->getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);

  int16_t x = (DISPLAY_WIDTH - textWidth) / 2;
  int16_t y = (DISPLAY_HEIGHT / 2) + 15;

  _gfx->setCursor(x, y);
  _gfx->println(text);
}

void GFXDriver::loop() {
  static unsigned long lastTapTime = 0;

  byte data_raw[7];
  i2cRead(0x15, 0x02, data_raw, 7);

  int event = data_raw[1] >> 6;

  if (event != 2) {
    return;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastTapTime >= DEBOUNCE_DELAY_MS) {
    lastTapTime = currentTime;
    _onTouch();
  }
}

void GFXDriver::i2cRead(uint16_t addr, uint8_t reg_addr, uint8_t *reg_data,
                        uint32_t length) {
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  if (Wire.endTransmission(true))
    return;
  Wire.requestFrom(addr, length, true);
  for (int i = 0; i < length; i++) {
    *reg_data++ = Wire.read();
  }
}

void GFXDriver::off() { _gfx->fillScreen(BLACK); }

void GFXDriver::drawColors(const std::vector<uint16_t> &colors) {}
