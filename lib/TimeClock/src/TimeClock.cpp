#include "TimeClock.h"

void TimeClock::setup(int timeOffset)
{
    this->timeClient.begin();
    this->timeClient.setTimeOffset(timeOffset);
}

void TimeClock::update()
{
    this->timeClient.update();
}

String TimeClock::getFormattedTime()
{
    return this->timeClient.getFormattedTime();
}

String TimeClock::getFormattedTime(unsigned long rawTime)
{
    unsigned long hours = rawTime / 3600;
    String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

    unsigned long minutes = (rawTime % 3600) / 60;
    String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

    unsigned long seconds = rawTime % 60;
    String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

    return hoursStr + ":" + minuteStr + ":" + secondStr;
}

unsigned long TimeClock::getTimeBeforeStart()
{
    return this->startEpoch - this->timeClient.getEpochTime();
}
unsigned long TimeClock::getTimeBeforeFinish()
{
    return (this->startEpoch + this->durationSecs) - this->timeClient.getEpochTime();
}

bool TimeClock::isGameStarted()
{
    return this->timeClient.getEpochTime() >= this->startEpoch && !this->isGameFinished();
}

bool TimeClock::isGameFinished()
{
    return this->timeClient.getEpochTime() > (this->startEpoch + this->durationSecs);
}

unsigned long TimeClock::getDuration()
{
    return this->durationSecs;
}

void TimeClock::setUnlockEpoch()
{
    this->unlockEpoch = this->timeClient.getEpochTime();
}

unsigned long TimeClock::getUnlockEpoch()
{
    return this->unlockEpoch;
}

unsigned long TimeClock::getStartEpoch()
{
    return this->startEpoch;
}