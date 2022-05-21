#pragma once
#include "BaseObject.h"
#include "button.h"
#include "HandleTime.h"

class UserName
{
    BaseObject name_frame;
    SDL_Renderer* renderer;
    std::string name_string;
    BaseObject* game_text;
    BaseObject* image;
    button game_button;

    int time = 0;
public:
    enum
    {
        GET_NAME_REQUEST, //"PLEASE ENTER YOUR NAME"
        INTRO_GET_NAME //"PRESS ENTER TO CONTINUE"
    };

    UserName(SDL_Renderer*& renderer);

    ~UserName();

    void HandleEvent(const SDL_Event& e, int& GAME_STATUS, Timer& playing_timer,SDL_Point& mouse_button_pos);
    void Render();
    std::string GetUserName();
    void ResetName();
};
