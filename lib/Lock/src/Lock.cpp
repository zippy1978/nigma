#include "Lock.h"

void Lock::setup()
{
    this->locked = true;

    String code = "";
    for (int i = 0; i < LOCK_DIGITS; i++)
    {
        int digit = random(0, 9);
        code += digit;
    }
    this->unlockCode = code;
}

bool Lock::unlock(String code)
{
    Serial.println("Attempting unlock with code: " + code);
    bool unlocked = this->unlockCode.equals(code);
    this->locked = !unlocked;
    return unlocked;
}

bool Lock::isLocked()
{
    return this->locked;
}