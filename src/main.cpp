#include <Arduino.h>

#include <WiFi.h>
#include <logger.hpp>

#include "uartOStream.hpp"
#include "Constants.h"

Logger logger(eLogLevel::DEBUG, "[MAIN]");

void setup() {
  logger.addOutStream(&UART0::uartOut);

  logger.INFO << "Connecting to WiFi \"" << WIFI_SSID << "\"" << std::endl;
  while(WiFi.begin(WIFI_SSID, WIFI_PWD) != WL_CONNECTED)
  {
    if (millis() % 1000 == 0)
    {
      logger.INFO << "." << std::endl;
    }
  }
  logger.INFO << std::endl << "connected!" << std::endl;
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

