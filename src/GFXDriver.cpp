#include "GFXDriver.h"

GFXDriver::GFXDriver() : _onTouch(nullptr) {
  _bus = new Arduino_SWSPI(GFX_NOT_DEFINED /* DC */, 1 /* CS */, 46 /* SCK */,
                           0 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

  _rgbpanel = new Arduino_ESP32RGBPanel(
      2 /* DE */, 42 /* VSYNC */, 3 /* HSYNC */, 45 /* PCLK */, 11 /* R0 */,
      15 /* R1 */, 12 /* R2 */, 16 /* R3 */, 21 /* R4 */, 39 /* G0/P22 */,
      7 /* G1/P23 */, 47 /* G2/P24 */, 8 /* G3/P25 */, 48 /* G4/P26 */,
      9 /* G5 */, 4 /* B0 */, 41 /* B1 */, 5 /* B2 */, 40 /* B3 */, 6 /* B4 */,
      1 /* hsync_polarity */, 10 /* hsync_front_porch */,
      8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
      1 /* vsync_polarity */, 10 /* vsync_front_porch */,
      8 /* vsync_pulse_width */, 20 /* vsync_back_porch */,
      0 /* pclk_active_neg */, 12000000 /* prefer_speed */,
      false /* useBigEndian */, 0 /* de_idle_high */, 0 /* pclk_idle_high */,
      0 /* bounce_buffer_size_px */);

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
  int16_t y = DISPLAY_HEIGHT / 2;

  _gfx->setCursor(x, y);
  _gfx->println(text);
}
