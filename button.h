#pragma once
#include "BaseObject.h"

class button 
{
    SDL_Point button_address;
    BaseObject* button_texture;
public:
    button() : button_texture(new BaseObject[2])
    {
    }
    ~button()
    {
        delete[] button_texture;
    }
    void LoadButton(SDL_Renderer*& renderer, std::string path1, std::string path2);
    void render(SDL_Renderer* renderer, const SDL_Rect* src_rect, const SDL_Rect* dst_rect, bool zoom = true);
    bool IsInside(const SDL_Point& p);
};

enum
{
    QUIT_BUTTON,
    RETURN_BUTTON,
    YES_BUTTON,
    NO_BUTTON,
    MUSIC_BUTTON_2,
    PAUSE_BUTTON,
    MUSIC_BUTTON_1,
    RANK_BUTTON,
    START_BUTTON,
    UNPAUSE_BUTTON,
};

static button* game_button;
