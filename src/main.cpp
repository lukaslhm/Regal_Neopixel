#include <Arduino.h>

#include <iomanip>

#include <WiFi.h>
#include <logger.hpp>

#include "uartOStream.hpp"
#include "Constants.h"

Logger logger(eLogLevel::DEBUG, "[MAIN]");

void setup() {
  logger.addOutStream(&UART0::uartOut);
  logger.INFO << "Initialisation" << std::endl;

  logger.INFO << "Connecting to WiFi \"" << WIFI_SSID << "\"" << std::flush;
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  unsigned long start_millis = millis();
  while(WiFi.status() != WL_CONNECTED)
  {
    if (millis() - start_millis > WIFI_TIMEOUT) break;
    if (millis() % 1000UL == 0)
    {
      logger.INFO << "." << std::flush;
    }
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    logger.WARN << "Wifi Timeout" << std::endl;
  }
  else {
    logger.INFO << "  connected!" << std::endl;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  logger.INFO << "Loop" << std::endl;
  sleep(1);
}

