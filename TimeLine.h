#pragma once
#include "BaseObject.h"
#include "CommonFunc.h"

class TimeLine
{
    BaseObject time_box;
    BaseObject time_line;
    BaseObject round;

public:
    TimeLine();

    ~TimeLine();

    void Load(SDL_Renderer*& renderer);

    void Render(SDL_Renderer*& renderer, const double& ratio, const int& round);
};
