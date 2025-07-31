#include <Arduino.h>
#include <ArduinoOTA.h>

#include <iomanip>

#include <WiFi.h>
#include <PubSubClient.h>
#include <logger.hpp>
#include <string>
#include <cstring>

#include "mqttOStream.hpp"
#include "uartOStream.hpp"
#include "Constants.h"

void mqttMsgArrivedCallback(char* initTopic, byte* initMsg, unsigned int initLength)
{
  std::string topic(initTopic);
  unsigned int length = initLength;
  byte msg[length];
  std::memcpy(msg, initMsg, length);

  Logger logger(eLogLevel::DEBUG, "[MQTT]");
  logger.INFO << "Message Received!" << std::endl;
  logger.INFO << "Topic: " << topic << std::endl;
  logger.INFO << "Msg: ";
  for (int i = 0; i<length; i++)
  {
    logger.INFO << (char) msg[i];
  }
  logger.INFO << std::endl;
}


WiFiClient espClient;
PubSubClient mqttClient(OUTPOST_IP, 1883, mqttMsgArrivedCallback, espClient);

int logMqttState(Logger& logger, int state)
{
  switch(state)
  {
    case -4:
      logger.ERROR << "Code -4: Connection Timeout - Server didn\'t respont within the keepalive time" << std::endl;
      break;
    case -3:
      logger.ERROR << "MQTT Status -3: Connection Lost - Network connection was broken" << std::endl;
      break;
    case -2:
      logger.ERROR << "MQTT Status -2: Connection Failed - Network connection failed" << std::endl;
      break;
    case -1:
      logger.WARN << "MQTT Status -1: Connection Disconnected Cleanly" << std::endl;
      break;
    case 0:
      logger.INFO << "MQTT Status 0: Connection successful" << std::endl;
      break;
    case 1:
      logger.ERROR << "MQTT Status 1: BAD Protocol - Server doesn\'t support the requested version of MQTT" << std::endl;
      break;
    case 2:
      logger.ERROR << "MQTT Status 2: BAD Client ID" << std::endl;
      break;
    case 3:
      logger.ERROR << "MQTT Status 3: Server Unavailable" << std::endl;
      break;
    case 4:
      logger.ERROR << "MQTT Status 4: Bad Credentials" << std::endl;
      break;
    case 5:
      logger.ERROR << "MQTT Status 5: Client Unauthorized" << std::endl;
      break;
  }

  return state;
}

int logUniqueMqttState(Logger& logger, int state, int lastState)
{
  if (state != lastState) logMqttState(logger, state);

  return state;
}

void wifi_Setup()
{
  Logger logger(eLogLevel::DEBUG, "[WIFI]");
  logger.DEBUG << "Wifi Setup" << std::endl;

  IPAddress local_IP(192, 168, 4, 10);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.config(local_IP, gateway, subnet);

  logger.INFO << "Connecting to WiFi \"" << WIFI_SSID << "\"" << std::flush;
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  unsigned long start_millis = millis();
  while(WiFi.status() != WL_CONNECTED)
  {
    if (millis() - start_millis > WIFI_TIMEOUT) break;
    if (micros() % 500000UL == 0)
    {
      logger.INFO << "." << std::flush;
    }
  }

  logger.INFO << std::endl;

  if (WiFi.status() != WL_CONNECTED)
  {
    logger.WARN << "Timeout" << std::endl;

  }
  else {
    logger.INFO << "connected!" << std::endl;
    logger.INFO << "IP: " <<  (int) WiFi.localIP()[0] << '.' << (int) WiFi.localIP()[1] << '.' << (int) WiFi.localIP()[2] << '.' << (int) WiFi.localIP()[3] << std::endl;
  }

  ArduinoOTA.begin();
}

void mqtt_setup()
{
  Logger logger(eLogLevel::DEBUG, "[MQTT]");

  logger.INFO << "Connection to Broker: " << std::endl << '.' << std::flush;

  unsigned long start = millis();

  while (!mqttClient.connect("Regal_LED_Strip"))
  {
    if (micros() % 1000000) logger.INFO << '.' << std::flush;
    if ((millis() - start) > MQTT_TIMEOUT)
    {
      logger.ERROR << "Connection Attempt Timeout";
      break;
    } 
  }

  logger.INFO << std::endl;

  logMqttState(logger, mqttClient.state());

  if (mqttClient.subscribe(MQTT_TOPIC_MODE))
  {
    logger.DEBUG << "Subscription to: " << MQTT_TOPIC_MODE << " Succeeded" << std::endl;
  } else
  {
    logger.ERROR << "Subscription to: " << MQTT_TOPIC_MODE << " Failed" << std::endl;
  }
  
  if (mqttClient.subscribe(MQTT_TOPIC_INTENSITY))
  {
    logger.DEBUG << "Subscription to: " << MQTT_TOPIC_INTENSITY << " Succeeded" << std::endl;
  } else
  {
    logger.ERROR << "Subscription to: " << MQTT_TOPIC_INTENSITY << " Failed" << std::endl;
  }

  
  Logger::addOutStream(&MQTT::mqttLog);

}

void setup() {
  Logger logger(eLogLevel::DEBUG, "[SETUP]");
  Logger::addOutStream(&UART0::uartOut);
  
  logger.INFO << "Booting..." << std::endl;
  logger.DEBUG << "Start Setup" << std::endl;

  wifi_Setup();

  logger.DEBUG << "Wifi Setup finished" << std::endl;

  mqtt_setup();

  logger.DEBUG << "MQTT Setup finished" << std::endl;

  
}

void loop() {
  ArduinoOTA.handle();
  mqttClient.loop();
  delay(10);
}

