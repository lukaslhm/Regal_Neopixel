#define WIFI_SSID "HexaPot"
#define WIFI_PWD "RASPberry"
#define WIFI_TIMEOUT 50000

#define OUTPOST_IP "192.168.4.1"
#define MQTT_TIMEOUT 50000

#define MQTT_TOPIC_FOLDER "regalLedControl/#"

#define MQTT_TOPIC_MODE "regalLedControl/selectedMode"

#define MQTT_TOPIC_STATIC_COLOR_HUE "regalLedControl/mode/staticColor/hue"
#define MQTT_TOPIC_STATIC_COLOR_SAT "regalLedControl/mode/staticColor/sat"
#define MQTT_TOPIC_STATIC_COLOR_VAL "regalLedControl/mode/staticColor/val"

#define MQTT_TOPIC_UNIFORM_RAINBOW_PERIOD "regalLedControl/mode/uniformRainbow/period"
#define MQTT_TOPIC_UNIFORM_RAINBOW_SAT "regalLedControl/mode/uniformRainbow/sat"
#define MQTT_TOPIC_UNIFORM_RAINBOW_VAL "regalLedControl/mode/uniformRainbow/val"

#define MQTT_TOPIC_WAVE_RAINBOW_PERIOD "regalLedControl/mode/waveRainbow/period"
#define MQTT_TOPIC_WAVE_RAINBOW_LAMBDA "regalLedControl/mode/waveRainbow/lambda"
#define MQTT_TOPIC_WAVE_RAINBOW_SAT "regalLedControl/mode/waveRainbow/sat"
#define MQTT_TOPIC_WAVE_RAINBOW_VAL "regalLedControl/mode/waveRainbow/val"

#define MQTT_TOPIC_LOG "Regal_LED_Strip/Log"
#define MQTT_TOPIC_INTENSITY "Regal_LED_Strip/Intensity"
#define MQTT_TOPIC_COLOR_PICKER "Regal_LED_Strip/Color_Picker"

#define LED_DATA_PIN 13
#define NUM_LEDS 260

#include <logger.hpp>

#define LOG_LEVEL_MQTT_MSG_CALLBACK eLogLevel::DEBUG
#define LOG_LEVEL_MAIN_LOOP eLogLevel::INFO
#define LOG_LEVEL_SETUP eLogLevel::INFO
#define LOG_LEVEL_WIFI_SETUP eLogLevel::INFO
#define LOG_LEVEL_MQTT_SETUP eLogLevel::INFO
#define LOG_LEVEL_LED_MODE eLogLevel::DEBUG

#include <FastLED.h>

extern CRGB leds[NUM_LEDS];
