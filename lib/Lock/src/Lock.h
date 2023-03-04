#ifndef Lock_h
#define Lock_h

#include <Arduino.h>

// Parameters
#define LOCK_DIGITS 4

class Lock
{
private:
    String unlockCode;
    bool locked;
public:
    void setup();
    bool unlock(String code);
    bool isLocked();
};

#endif