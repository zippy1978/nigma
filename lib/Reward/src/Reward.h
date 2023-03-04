#ifndef Reward_h
#define Reward_h

#include "TimeClock.h"

#include <Arduino.h>

class Reward
{
private:
    int initialAmount;
    TimeClock *timeClock;

public:
    Reward(int initialAmount, TimeClock *timeClock) : initialAmount(initialAmount), timeClock(timeClock) {};
    int getWonAmount();
    int getCurrentAmount();
};

#endif