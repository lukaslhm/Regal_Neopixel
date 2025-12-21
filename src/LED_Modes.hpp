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
        uniformRainbow() = default;
        void update(uint16_t dt) override;

        void setPeriod(float t);
        void setSat(uint8_t sat);
        void setVal(uint8_t val);
    
    private:
        float period = 1;
        uint8_t sat = 0;
        uint8_t val = 255;

        float time = 0;
        CHSV color;
    };

    class waveRainbow : public generic
    {
    public:
        waveRainbow() = default;
        void update(uint16_t dt) override;

        void setPeriod(float t);
        void setSat(uint8_t s);
        void setVal(uint8_t v);
        void setWaveLength(float lambda);
    private:
        float period = 1;
        uint8_t sat = 0;
        uint8_t val = 0;
        float lambdaStrip = 1;

        float time = 0;
    };

    extern off modeOff;
    extern staticColor modeStaticColor;
    extern uniformRainbow modeUniformRainbow;
    extern waveRainbow modeWaveRainbow;
}

    