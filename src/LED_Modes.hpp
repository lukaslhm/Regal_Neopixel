#include <FastLED.h>

namespace LED_Mode
{
    class generic
    {
    public:
        virtual void update(uint16_t dt) = 0;
    };

    class off : public generic
    {
    public:
        void update(uint16_t dt) override;
    };

    class staticColor : public generic
    {
    public:
        void update(uint16_t dt) override;

        void setHue(uint16_t hue);
        void setSat(uint8_t sat);
        void setVal(uint8_t val);

    private:
        CRGB color;
    };

    class uniformRainbow : public generic
    {
    public:
        void update(uint16_t dt) override;

        void setPeriod(float t);
        void setSat(uint8_t sat);
        void setVal(uint8_t val);
    
    private:
        uint32_t huePerSec = 0;
        uint8_t sat = 0;
        uint8_t val = 255;

        CHSV color;
    };

    extern off modeOff;
    extern staticColor modeStaticColor;
    extern uniformRainbow modeUniformRainbow;
}

    