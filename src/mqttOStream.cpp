#include "mqttOStream.hpp"

#include <Arduino.h>
#include <PubSubClient.h>
#include <string>
#include <sstream>

#include "Constants.h"

extern PubSubClient mqttClient;

class mqttStreamBuf : public std::streambuf
{
public:
    int_type overflow(int_type c) override
    {
        lineBuffer << (char) c;

        return c;
    }

    int_type sync() override
    {
        mqttClient.publish(MQTT_TOPIC_LOG, lineBuffer.str().c_str());
        lineBuffer.clear();
        lineBuffer.str("");

        return 0;
    }

private:
    std::stringstream lineBuffer;
};

mqttStreamBuf mqttBuf;
std::ostream MQTT::mqttLog(&mqttBuf);
