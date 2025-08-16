# GFXDriver

GFXDriver is a specialized library built specifically for the Makerfabs MaTouch ESP32-S3 Rotary IPS Display with Touch 2.1" ST7701. It is designed to manage both the display and touch input of this particular hardware, and is not intended to be a generic solution for arbitrary displays.

The library provides simple and efficient APIs for common operations such as writing text, clearing sections of the screen, drawing colors, displaying a power symbol, and handling touch input events. This makes it easy to integrate and control the display and touch features in your ESP32-S3 projects.

## Quick Start

```cpp
#include <GFXDriver.h>

GFXDriver display;

void onTouch() {
  // Do something...
}

void setup() {
  driver.init(onTouch);
  driver.writeText("4:19 PM", XL);
  driver.drawColors({driver.hexToColor("FF0000"), driver.hexToColor("00FF00")}, UPPER_THIRD);
}

void loop() {
  driver.loop();
}
```
