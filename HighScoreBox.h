#pragma once
#include "Animation.h"
class HighScoreBox
{
    Animation* high_score_sticker;
    SDL_Renderer* renderer;
public:
    HighScoreBox(SDL_Renderer*&renderer)
    {
        this->renderer = renderer;
        high_score_sticker = new Animation[1];
        high_score_sticker[0].Load(renderer, {30,100}, "assets/high_score_sticker/", 16);
    }
    ~HighScoreBox()
    {

    }
    void Render()
    {
        high_score_sticker[0].Render();
    }
};

