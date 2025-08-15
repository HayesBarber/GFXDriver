#include "GFXDriver.h"

GFXDriver::GFXDriver() : _onTouch(nullptr) {
  _bus = new Arduino_SWSPI(GFX_NOT_DEFINED /* DC */, 39 /* CS */, 48 /* SCK */,
                           47 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

  _rgbpanel = new Arduino_ESP32RGBPanel(
      18 /* DE */, 17 /* VSYNC */, 16 /* HSYNC */, 21 /* PCLK */, 11 /* R0 */,
      12 /* R1 */, 13 /* R2 */, 14 /* R3 */, 0 /* R4 */, 8 /* G0 */,
      20 /* G1 */, 3 /* G2 */, 46 /* G3 */, 9 /* G4 */, 10 /* G5 */, 4 /* B0 */,
      5 /* B1 */, 6 /* B2 */, 7 /* B3 */, 15 /* B4 */, 1 /* hsync_polarity */,
      10 /* hsync_front_porch */, 8 /* hsync_pulse_width */,
      50 /* hsync_back_porch */, 1 /* vsync_polarity */,
      10 /* vsync_front_porch */, 8 /* vsync_pulse_width */,
      20 /* vsync_back_porch */, 0 /* pclk_active_neg */,
      12000000 /* prefer_speed */, false /* useBigEndian */,
      0 /* de_idle_high */, 0 /* pclk_idle_high */,
      0 /* bounce_buffer_size_px */);

  _gfx = new Arduino_RGB_Display(
      480 /* width */, 480 /* height */, _rgbpanel, 1 /* rotation */,
      true /* auto_flush */, _bus, GFX_NOT_DEFINED /* RST */,
      st7701_type9_init_operations, sizeof(st7701_type9_init_operations));
}

void GFXDriver::init(void (*onTouch)()) {}
