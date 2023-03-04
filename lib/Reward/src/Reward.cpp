#include "Reward.h"

#include <math.h>

int Reward::getWonAmount() {
    unsigned long remaining = (this->timeClock->getStartEpoch() + this->timeClock->getDuration()) - this->timeClock->getUnlockEpoch();
    double current = (double)this->initialAmount / (double)this->timeClock->getDuration() * remaining;
    return round(current);
}

int Reward::getCurrentAmount()
{
    double current = (double)this->initialAmount / (double)this->timeClock->getDuration() * (double)this->timeClock->getTimeBeforeFinish();
    return round(current);
}