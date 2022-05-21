#pragma once
#include <algorithm>
#include"BaseObject.h"
#include "CommonFunc.h"
#include "button.h"

//Handle QUIT_PAUSE event
enum quit_game_image
{
    QUIT_BG_texture
};

enum quit_status
{
    NOT_ALLOWED_TO_DO,
    ALLOWED_TO_DO,
    NONE
};

static SDL_Rect BOX_rect = {22, 183, 304, 166};
static SDL_Rect QUIT_rect = {270, 200, 40, 40};
static SDL_Rect YES_rect = {70, 285, 93, 35};
static SDL_Rect NO_rect = {190, 285, 94, 35};

inline void HandleQuitGame(SDL_Event& e, int& QUIT_STATUS)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        if (CheckInsideRect(x, y, YES_rect))
        {
            QUIT_STATUS = ALLOWED_TO_DO;
        }
        if (CheckInsideRect(x, y, NO_rect) || CheckInsideRect(x, y, QUIT_rect))
        {
            QUIT_STATUS = NOT_ALLOWED_TO_DO;
        }
    }
}

inline void RenderQuitGame(SDL_Renderer*& renderer, BaseObject &quit_image, button* &game_button, BaseObject* &game_text)
{
    quit_image.render(renderer, nullptr, &BOX_rect);
    game_button[QUIT_BUTTON].render(renderer, nullptr, &QUIT_rect);

    static SDL_Rect quit_request_rect = {63, 235, game_text[QUIT_REQUEST].getWidth(), game_text[QUIT_REQUEST].getHeight()};
    game_text[QUIT_REQUEST].render(renderer, nullptr, &quit_request_rect);

    game_button[YES_BUTTON].render(renderer, nullptr, &YES_rect);
    game_button[NO_BUTTON].render(renderer, nullptr, &NO_rect);
}

//Handle RETURN_PAUSE event
inline void HandleReturnEvent(SDL_Event& e, int& RETURN_STATUS)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        if (CheckInsideRect(x, y, YES_rect))
        {
            RETURN_STATUS = ALLOWED_TO_DO;
        }
        if (CheckInsideRect(x, y, NO_rect) || CheckInsideRect(x, y, QUIT_rect))
        {
            RETURN_STATUS = NOT_ALLOWED_TO_DO;
        }
    }
}


inline void RenderReturnEvent(SDL_Renderer*& renderer, BaseObject& quit_image, button* game_button, BaseObject* game_text)
{
    quit_image.render(renderer, nullptr, &BOX_rect);
    game_button[QUIT_BUTTON].render(renderer, nullptr, &QUIT_rect);
    static SDL_Rect quit_request_rect = {63, 235, game_text[QUIT_REQUEST].getWidth(), game_text[QUIT_REQUEST].getHeight()};
    game_text[RETURN_REQUEST].render(renderer, nullptr, &quit_request_rect);

    game_button[YES_BUTTON].render(renderer, nullptr, &YES_rect);
    game_button[NO_BUTTON].render(renderer, nullptr, &NO_rect);
}

//Handle PAUSE Event
static SDL_Rect unpause_button_rect = {126, 216, 100, 100};

inline void HandlePauseEvent(SDL_Event& e, int& PAUSE_STATUS, button* game_button, SDL_Point& mouse_button_pos)
{
    static int x;
    static int y;
    SDL_GetMouseState(&x, &y);
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        mouse_button_pos = {x, y};
    }
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        if (game_button[UNPAUSE_BUTTON].IsInside({x, y}) && game_button[UNPAUSE_BUTTON].IsInside(mouse_button_pos))
        {
            PAUSE_STATUS = ALLOWED_TO_DO;
        }
    }
}

inline void RenderPauseFrame(SDL_Renderer*& renderer, BaseObject& quit_image, button* game_button)
{
    quit_image.render(renderer, nullptr, &BOX_rect);
    game_button[UNPAUSE_BUTTON].render(renderer, nullptr, &unpause_button_rect);
}

