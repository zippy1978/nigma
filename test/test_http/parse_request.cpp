#include "unity.h"
#include "HTTP.h"
#include "Lock.h"
#include "Settings.h"
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

void test_parseRequest(void)
{
    Settings settings{"V1"};
    Lock lock;
    HTTP http(&settings, &lock);
    HTTPRequest parsed = http.parseRequest("GET /unlock/12 HTTP/1.1");
    TEST_ASSERT_EQUAL_STRING("GET", &parsed.method);
    TEST_ASSERT_EQUAL_STRING("/unlock/12", &parsed.path);
}


int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parseRequest);
    return UNITY_END();
}

void setup()
{
    delay(2000);
    runUnityTests();
}
void loop() {}
