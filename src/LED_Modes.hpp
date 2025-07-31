#include <FastLED.h>

namespace LED_Mode
{
    void off(CRGB* leds, bool& modeChanged);
    void staticColor(CRGB* leds, CRGB color, bool& modeChanged);
}
