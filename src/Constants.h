#define WIFI_SSID "HexaPot"
#define WIFI_PWD "RASPberry"
#define WIFI_TIMEOUT 50000

#define OUTPOST_IP "192.168.4.1"
#define MQTT_TIMEOUT 50000

#define MQTT_TOPIC_MODE "Regal_LED_Strip/Mode"
#define MQTT_TOPIC_LOG "Regal_LED_Strip/Log"
#define MQTT_TOPIC_INTENSITY "Regal_LED_Strip/Intensity"
#define MQTT_TOPIC_COLOR_PICKER "Regal_LED_Strip/Color_Picker"

enum class LED_Mode_Nr{
    off = 0,
    static_Color = 1
};

#define LED_DATA_PIN 13
#define NUM_LEDS 260


