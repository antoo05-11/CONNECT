#pragma once
#include "BaseObject.h"
#include "button.h"

class StartBox
{
    button* game_button;
    SDL_Renderer* renderer;
BaseObject name_image;
public:
    enum button_
    {
        START_BUTTON,
        RANK_BUTTON,
        MUSIC_BUTTON
    };
    StartBox(SDL_Renderer* renderer);
    ~StartBox();
    void Render();
    void HandleEvent(SDL_Event& e, int& GAME_STATUS, SDL_Point& mouse_button_down_pos);
};

