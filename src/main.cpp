#include <Arduino.h>
#include <ArduinoOTA.h>

#include <iomanip>

#include <WiFi.h>
#include <PubSubClient.h>
#include <logger.hpp>
#include <string>
#include <cstring>

#include <FastLED.h>

#include "mqttOStream.hpp"
#include "uartOStream.hpp"
#include "Constants.h"

#include "setup.hpp"
#include "LED_Modes.hpp"

std::string LED_Active_Mode = "ledOff";
float LED_Brightness = 0;
CRGB colorPicker_Color = CRGB::Red;

unsigned long lastMillis = millis();

CRGB leds[NUM_LEDS];

void mqttMsgArrivedCallback(char* initTopic, byte* initMsg, unsigned int initLength)
{
  std::string topic(initTopic);
  unsigned int length = initLength;
  std::string msg((char*) initMsg, length);

  Logger logger(eLogLevel::INFO, "[MQTT]");

  logger.DEBUG << "Topic: " << topic << " , Msg: " << msg << std::endl;

  if (topic == MQTT_TOPIC_MODE)
  {
    LED_Active_Mode = msg;
  }
  else if (topic == MQTT_TOPIC_STATIC_COLOR_HUE)
  {
    LED_Mode::modeStaticColor.setHue(std::stoi(msg));
  }
  else if (topic == MQTT_TOPIC_STATIC_COLOR_SAT)
  {
    LED_Mode::modeStaticColor.setSat(std::stoi(msg));
  }
  else if (topic == MQTT_TOPIC_STATIC_COLOR_VAL)
  {
    LED_Mode::modeStaticColor.setVal(std::stoi(msg));
  }
  else if (topic == MQTT_TOPIC_UNIFORM_RAINBOW_PERIOD)
  {
    LED_Mode::modeUniformRainbow.setPeriod(std::stof(msg));
  }
  else if (topic == MQTT_TOPIC_UNIFORM_RAINBOW_SAT)
  {
    LED_Mode::modeUniformRainbow.setSat(std::stoi(msg));
  }
  else if (topic == MQTT_TOPIC_UNIFORM_RAINBOW_VAL)
  {
    LED_Mode::modeUniformRainbow.setVal(std::stoi(msg));
  }
  else
  {
    logger.WARN << "Unknown Topic Received: " << topic << " Msg: " << msg << std::endl;
  }

}

WiFiClient espClient;
PubSubClient mqttClient(OUTPOST_IP, 1883, mqttMsgArrivedCallback, espClient);

void setup() {
  Logger logger(eLogLevel::DEBUG, "[SETUP]");
  Logger::addOutStream(&UART0::uartOut);
  
  logger.INFO << "Booting..." << std::endl;

  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

  wifi_setup();

  logger.DEBUG << "Wifi Setup finished" << std::endl;

  mqtt_setup();

  logger.DEBUG << "MQTT Setup finished" << std::endl;

  
}

void loop() {
  ArduinoOTA.handle();
  mqttClient.loop();

  unsigned int dt = millis() - lastMillis;
  lastMillis += dt;

  if (LED_Active_Mode == "ledOff")
  {
    LED_Mode::modeOff.update(dt);
  }
  else if (LED_Active_Mode == "staticColor")
  {
    LED_Mode::modeStaticColor.update(dt);
  }
  else if (LED_Active_Mode == "uniformRainbow")
  {
    LED_Mode::modeUniformRainbow.update(dt);
  }

  FastLED.show();
  delay(30);
}

