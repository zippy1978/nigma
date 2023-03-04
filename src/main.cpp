#include "config.h"
#include "secrets.h"
#include "GameState.h"
#include "TimeClock.h"
#include "Reward.h"
#include "Settings.h"
#include "Display.h"
#include "LED.h"
#include "Lock.h"
#include "HTTP.h"

Settings settings{NIGMA_VERSION};
TimeClock timeClock(NIGMA_START_EPOCH, NIGMA_DURATION_SECS);
Reward reward(NIGMA_INITIAL_REWARD, &timeClock);
Lock lock;
LED led;
Display display(&settings);
HTTP http(&settings, &lock);
GameState state = GameState::NoStarted;

// TODO
// Led.h
// Python cli and tests

void notStartedState()
{
  //http.listen();
  led.setRed(lock.isLocked());
  led.setGreen(!lock.isLocked());
  display.setLine(0, "Starts in ");
  display.setLine(1, timeClock.getFormattedTime(timeClock.getTimeBeforeStart()));
}

void startedState()
{
  http.listen();
  led.setRed(lock.isLocked());
  led.setGreen(!lock.isLocked());
  String prefix = "Reward ";
  String suffix = " eur";
  display.setLine(0, prefix + reward.getCurrentAmount() + suffix);
  display.setLine(1, "Rem. " + timeClock.getFormattedTime(timeClock.getTimeBeforeFinish()));
}

void wonState()
{
  //http.listen();
  led.setRed(lock.isLocked());
  led.setGreen(!lock.isLocked());
  String prefix = "You won ";
  String suffix = " eur";
  display.setLine(0, "Congrats :)");
  display.setLine(1, prefix + reward.getWonAmount() + suffix);
}

void lostState()
{
  //http.listen();
  led.setRed(lock.isLocked());
  led.setGreen(!lock.isLocked());
  display.setLine(0, "Sorry :(");
  display.setLine(1, "You lost");
}

void setup()
{
  Serial.begin(9600);
  delay(200);
  timeClock.setup(NIGMA_TIME_CLOCK_OFFSET);
  lock.setup();
  led.setup();
  display.setup();
  display.setLine(0, "NigMa " + settings.version);
  display.setLine(1, "Connecting...");
  display.update();
  http.setup(WIFI_SSID, WIFI_PASSWORD);
  display.setLine(1, http.getAddress());
  display.update();
  // Give time to read IP address
  delay(3000);
}

void loop()
{
  // Update clock
  timeClock.update();

  // Read state
  GameState newState = computeState(&timeClock, &lock);

  // Win detection
  if (newState == GameState::Won && state != GameState::Won)
  {
    timeClock.setUnlockEpoch();
  }

  // Update state
  state = newState;

  // Process
  switch (state)
  {
  case NoStarted:
    notStartedState();
    break;
  case Started:
    startedState();
    break;
  case Won:
    wonState();
    break;
  case Lost:
    lostState();
    break;
  default:
    break;
  }

  display.update();

  delay(100);
}
