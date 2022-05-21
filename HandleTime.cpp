#include "HandleTime.h"

Timer::Timer()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
    pause_time = 0;
}

Timer::~Timer()
{
    
}

void Timer::Start()
{
    if(!is_started)
    {
        is_started = true;
        is_paused = false;
        start_tick = SDL_GetTicks();
    }
   
}

void Timer::Stop()
{
    is_paused = false;
    is_started = false;
    pause_time = 0;
}

void Timer::Paused()
{
    if(is_started && !is_paused)
    {
        is_paused = true;
        pause_tick = SDL_GetTicks(); //thời điểm ngưng
    }
}
void Timer::Unpaused()
{
    if(is_paused)
    {
        is_paused = false;
        pause_time += (SDL_GetTicks() - pause_tick);
        std::cout << pause_time << '\n';
    }
}


bool Timer::IsStarted()
{
    return is_started;
}

bool Timer::IsPaused()
{
    return is_paused;
}

int Timer::GetTime()
{
    return SDL_GetTicks() - start_tick - pause_time;
}





