#pragma once
#include "CommonFunc.h"

class Timer
{
public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Paused();
    void Unpaused();

    int GetTime();

    bool IsStarted();
    bool IsPaused();

private:
    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;

    int pause_time;
};

