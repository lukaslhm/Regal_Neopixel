#include "LED_Modes.hpp"

#include "Constants.h"

#include <FastLED.h>

void LED_Mode::off(CRGB* leds, bool& modeChanged)
{
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (modeChanged) modeChanged = false;
}

void LED_Mode::staticColor(CRGB* leds, CRGB color, bool& modeChanged)
{
    fill_solid(leds, NUM_LEDS, color);

    if (modeChanged) modeChanged = false;
}
