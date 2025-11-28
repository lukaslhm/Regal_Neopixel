#include "LED_Modes.hpp"

#include "logger.hpp"

#include "Constants.h"

#include <FastLED.h>

Logger logger(eLogLevel::DEBUG, "[LED MODE]");

LED_Mode::off LED_Mode::modeOff;
LED_Mode::staticColor LED_Mode::modeStaticColor;
LED_Mode::uniformRainbow LED_Mode::modeUniformRainbow;

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

    logger.DEBUG << "Set Hue to: " << std::to_string(h) << " from: " << std::to_string(hue) << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setSat(uint8_t sat)
{
    uint8_t s = (sat / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.s = s;

    logger.DEBUG << "Set Sat to: " << std::to_string(s) << " from: " << std::to_string(sat) << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setVal(uint8_t val)
{
    uint8_t v = (val / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.v = v;

    logger.DEBUG << "Set Val to: " << std::to_string(v) << " from: " << std::to_string(val) << std::endl;

    color = temp;
}

void LED_Mode::uniformRainbow::update(uint16_t dt)
{
    color.h = (color.h + (uint8_t) (huePerSec * dt / 1000 + 0.5)) % 256;
    fill_solid(leds, NUM_LEDS, color);
}

void LED_Mode::uniformRainbow::setPeriod(float t)
{
    huePerSec = 255/t + 0.5;

    logger.DEBUG << "Set Hue per Sec: " << std::to_string(huePerSec) << std::endl;
}

void LED_Mode::uniformRainbow::setSat(uint8_t sat)
{
    uint8_t s = (sat / 100.0) * 255 + 0.5;

    logger.DEBUG << "Set Sat: " << std::to_string(s) << std::endl;

    color.s = s;
}

void LED_Mode::uniformRainbow::setVal(uint8_t val)
{
    uint8_t v = (val / 100.0) * 255 + 0.5;

    logger.DEBUG << "Set Val: " << std::to_string(v) << std::endl;

    color.v = v;
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
