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

bool LED_Mode_Changed = true;
int LED_Active_Mode = 0;
float LED_Brightness = 0;
CRGB colorPicker_Color = CRGB::Red;

CRGB leds[NUM_LEDS];

void mqttMsgArrivedCallback(char* initTopic, byte* initMsg, unsigned int initLength)
{
  std::string topic(initTopic);
  unsigned int length = initLength;
  std::string msg((char*) initMsg, length);

  Logger logger(eLogLevel::DEBUG, "[MQTT]");

  if (topic == MQTT_TOPIC_MODE)
  {
    try
    {
      LED_Active_Mode = std::stoi(msg);
      LED_Mode_Changed = true;
      logger.INFO << "LED Mode changed to " << LED_Active_Mode << std::endl;
    }
    catch(const std::exception& e)
    {
      logger.ERROR << e.what() << std::endl;
    }
  } else if (topic == MQTT_TOPIC_COLOR_PICKER)
  {
    colorPicker_Color.r = strtoul(msg.substr(1, 2).c_str(), nullptr, 16);
    colorPicker_Color.g = strtoul(msg.substr(3, 2).c_str(), nullptr, 16);
    colorPicker_Color.b = strtoul(msg.substr(5, 2).c_str(), nullptr, 16);

    logger.DEBUG << "MQTT Input: " << msg << " r: " << msg.substr(1, 2).c_str() << " g: " << msg.substr(3, 2).c_str() << " b: " << msg.substr(5, 2).c_str() << std::endl;
    logger.DEBUG << "Color Picker Color changed to: " << colorPicker_Color.toString().c_str() << std::endl;
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

  switch(LED_Active_Mode)
  {
    case 0:
      LED_Mode::off(leds, LED_Mode_Changed);
      break;
    case 1:
      LED_Mode::staticColor(leds, colorPicker_Color, LED_Mode_Changed);
      break;

  }

  FastLED.show();
  delay(30);
}

