#ifndef Display_h
#define Display_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Settings.h"
#include "TimeClock.h"

// Parameters
#define DISPLAY_WIDTH 16
#define DISPLAY_HEIGHT 4

class Display
{
private:
    LiquidCrystal_I2C lcd;
    Settings *settings;
    char buffer[DISPLAY_HEIGHT][DISPLAY_WIDTH + 1]; // +1 is for String terminator
    bool shouldUpdate;

public:
    Display(Settings *settings) : lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE), settings(settings){};
    void setup();
    void setLine(int index, String value);
    void update();
};

#endif