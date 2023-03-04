#include "Display.h"

#include <Wire.h>

void Display::setup()
{
    while (lcd.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT, LCD_5x8DOTS) != 1) // Colums, rows, characters size
    {
        Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
        delay(5000);
    }
    this->setLine(0, " ");
    this->setLine(1, " ");
    this->setLine(2, " ");
    this->setLine(3, " ");
}

void Display::setLine(int index, String value)
{
    if (value.length() <= DISPLAY_WIDTH)
    {
        value.toCharArray(buffer[index], value.length() + 1);
        for (int i = value.length(); i < DISPLAY_WIDTH; i++)
        {
            buffer[index][i] = ' ';
        }
        buffer[index][DISPLAY_WIDTH] = '\0';
        this->shouldUpdate = true;
    }
    else
    {
        this->setLine(index, "#DISP_OVERFLOW");
    }
}

void Display::update()
{
    if (!this->shouldUpdate)
    {
        return;
    }

    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        lcd.setCursor(0, i);
        lcd.print(buffer[i]);
    }

    this->shouldUpdate = false;
}
