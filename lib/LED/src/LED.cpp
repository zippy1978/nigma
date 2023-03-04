#include "LED.h"

void LED::setup()
{
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);

    this->setRed(false);
    this->setGreen(false);
}

void LED::blinkOn(uint8_t pin)
{

    for (int i = 0; i < 4; i++)
    {
        digitalWrite(pin, 1);
        delay(100);
        digitalWrite(pin, 0);
        delay(100);
    }
}

void LED::setRed(bool state)
{
    if (state == true && this->redState == false)
    {
        this->blinkOn(LED_RED_PIN);
    }

    this->redState = state;
    digitalWrite(LED_RED_PIN, state);
}

void LED::setGreen(bool state)
{
    if (state == true && this->greenState == false)
    {
        this->blinkOn(LED_GREEN_PIN);
    }

    this->greenState = state;
    digitalWrite(LED_GREEN_PIN, state);
}