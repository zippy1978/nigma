#ifndef GameState_h
#define GameState_h

#include "Lock.h"
#include "TimeClock.h"

enum GameState
{
    NoStarted,
    Started,
    Won,
    Lost
};

GameState computeState(TimeClock *timeClock, Lock *lock);

#endif