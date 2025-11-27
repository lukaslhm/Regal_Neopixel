#include "LED_Modes.hpp"

#include "logger.hpp"

#include "Constants.h"

#include <FastLED.h>

extern CRGB* leds;

Logger logger(eLogLevel::DEBUG, "[LED MODE]");

void LED_Mode::off::update(uint16_t dt)
{
    fill_solid(leds, NUM_LEDS, CRGB::Black);
}

void LED_Mode::staticColor::update(uint16_t dt)
{
    fill_solid(leds, NUM_LEDS, color);
}

void LED_Mode::staticColor::setHue(uint16_t hue)
{
    uint8_t h = (hue / 360.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.h = h;

    logger.DEBUG << "Set Hue to: " << h << " from: " << hue << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setSat(uint8_t sat)
{
    uint8_t s = (sat / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.s = s;

    logger.DEBUG << "Set Hue to: " << s << " from: " << sat << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setVal(uint8_t val)
{
    uint8_t v = (val / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.v = v;

    logger.DEBUG << "Set Hue to: " << v << " from: " << val << std::endl;

    color = temp;
}

/*
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

void rainbow(CRGB* leds, float freq, bool& modeChanged)
{
    uint64_t huePerMicro = 256 * freq * 1e-6 + 0.5;
    unsigned long lastTime = micros();
    uint8_t hue = 0;
    while (!modeChanged)
    {
        unsigned long dt = micros() - lastTime;
        lastTime += dt;

        hue = (hue + huePerMicro * dt) % 256;

        fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));

        FastLED.show();
        delay(30);
    }
}*/
