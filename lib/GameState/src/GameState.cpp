#include "GameState.h"

GameState computeState(TimeClock *timeClock, Lock *lock) {
    if (lock->isLocked())
  {
    if (timeClock->isGameStarted())
    {
      return GameState::Started;
    }
    else if (timeClock->isGameFinished())
    {
      return GameState::Lost;
    }
  }
  else
  {
    return GameState::Won;
  }

  return GameState::NoStarted;
}
