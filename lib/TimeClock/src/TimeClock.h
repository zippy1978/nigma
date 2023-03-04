#ifndef TimeClock_h
#define TimeClock_h

#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeClock
{
private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    unsigned long startEpoch;
    unsigned long durationSecs;
    unsigned long unlockEpoch;

public:
    TimeClock(unsigned long startEpoch, unsigned long durationSecs) : timeClient(ntpUDP, "pool.ntp.org"), startEpoch(startEpoch), durationSecs(durationSecs){};
    void setup(int timeOffset);
    void update();
    unsigned long getTimeBeforeStart();
    unsigned long getTimeBeforeFinish();
    unsigned long getDuration();
    unsigned long getStartEpoch();
    void setUnlockEpoch();
    unsigned long getUnlockEpoch();
    bool isGameStarted();
    bool isGameFinished();
    String getFormattedTime();
    String getFormattedTime(unsigned long rawTime);
};

#endif