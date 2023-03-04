#include "unity.h"
#include "TimeClock.h"
#include <Arduino.h>
#include <Wire.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_getFormattedTime(void)
{
    TimeClock timeClock(0, 1000);
    // 1 minute
    String time1 = timeClock.getFormattedTime(60);
    TEST_ASSERT_EQUAL_STRING("00:01:00", &time1);
    // 100 hours 1 min and 1 secs
    String time2 = timeClock.getFormattedTime(60 * 60 * 100 + 61);
    TEST_ASSERT_EQUAL_STRING("100:01:01", &time2);
}


int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getFormattedTime);
    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}
