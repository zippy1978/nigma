#ifndef LED_h
#define LED_h

#include <Arduino.h>

// Parameters
#define LED_RED_PIN D6
#define LED_GREEN_PIN D5

class LED
{
private:
    bool redState;
    bool greenState;
    void blinkOn(uint8_t pin);
public:
    void setup();
    void setRed(bool state);
    void setGreen(bool state);
};

#endif