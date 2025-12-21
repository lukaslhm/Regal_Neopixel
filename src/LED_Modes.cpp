#include "LED_Modes.hpp"

#include "logger.hpp"

#include "Constants.h"

#include <FastLED.h>

Logger modeLogger(LOG_LEVEL_LED_MODE, "[LED MODE]");

LED_Mode::off LED_Mode::modeOff;
LED_Mode::staticColor LED_Mode::modeStaticColor;
LED_Mode::uniformRainbow LED_Mode::modeUniformRainbow;
LED_Mode::waveRainbow LED_Mode::modeWaveRainbow;

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

    modeLogger.DEBUG << "Set Hue to: " << std::to_string(h) << " from: " << std::to_string(hue) << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setSat(uint8_t sat)
{
    uint8_t s = (sat / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.s = s;

    modeLogger.DEBUG << "Set Sat to: " << std::to_string(s) << " from: " << std::to_string(sat) << std::endl;

    color = temp;
}

void LED_Mode::staticColor::setVal(uint8_t val)
{
    uint8_t v = (val / 100.0) * 255 + 0.5;
    CHSV temp = rgb2hsv_approximate(color);
    temp.v = v;

    modeLogger.DEBUG << "Set Val to: " << std::to_string(v) << " from: " << std::to_string(val) << std::endl;

    color = temp;
}

void LED_Mode::uniformRainbow::update(uint16_t dt)
{
    time += (dt / 1000.0);
    if (time > period) time -= period;
    color.h = ((uint8_t) (time / period * 255 + 0.5)) % 256;
    fill_solid(leds, NUM_LEDS, color);
}

void LED_Mode::uniformRainbow::setPeriod(float t)
{
    period = t;

    modeLogger.DEBUG << "Set period: " << std::to_string(period) << std::endl;
}

void LED_Mode::uniformRainbow::setSat(uint8_t sat)
{
    uint8_t s = (sat / 100.0) * 255 + 0.5;

    modeLogger.DEBUG << "Set Sat: " << std::to_string(s) << std::endl;

    color.s = s;
}

void LED_Mode::uniformRainbow::setVal(uint8_t val)
{
    uint8_t v = (val / 100.0) * 255 + 0.5;

    modeLogger.DEBUG << "Set Val: " << std::to_string(v) << std::endl;

    color.v = v;
}

void LED_Mode::waveRainbow::setPeriod(float t)
{
    period = t;

    modeLogger.DEBUG << "Set Period: " << std::to_string(t) << std::endl;
}

void LED_Mode::waveRainbow::setSat(uint8_t s)
{
    sat = (uint8_t) (s / 100.0) * 255 + 0.5;

    modeLogger.DEBUG << "Set Sat: " << std::to_string(sat) << std::endl;
}

void LED_Mode::waveRainbow::setVal(uint8_t v)
{
    val = (uint8_t) (v / 100.0 * 255) + 0.5;
    
    modeLogger.DEBUG << "Set Val: " << std::to_string(val) << std::endl;
}

void LED_Mode::waveRainbow::setWaveLength(float lambda)
{
    lambdaStrip = lambda;

    modeLogger.DEBUG << "Set Wave Length: " << std::to_string(lambdaStrip) << std::endl;
}

void LED_Mode::waveRainbow::update(uint16_t dt)
{
    time += dt;
    if (time > period) time -= period;
    Serial.println("update");
    for (int i = 0; i > NUM_LEDS; i++)
    {
        leds[i] = CHSV((uint8_t) 255/period * time - 255 / (lambdaStrip * NUM_LEDS) * i + 0.5, sat, val);
        Serial.print("LED: "); Serial.print(i); Serial.print(", Val: r "); Serial.print(leds[i].r); Serial.print(" g "); Serial.print(leds[i].g); Serial.print(" b "); Serial.println(leds[i].b);
    }
}

