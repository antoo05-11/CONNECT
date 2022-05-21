#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 127, 39};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {34, 177, 76};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

const SDL_Color CIRCLE_COLOR[] = {
    {28, 179, 75},
    {0, 163, 233},
    {255, 242, 0},
    {164, 71, 165},
    {186, 123, 86},
    {240, 136, 133},
    {255, 176, 202},
    {255, 202, 6},
    {154, 218, 235},
    {182, 231, 23},
    {201, 192, 232},
    {61, 70, 205},
    {239, 229, 178},
    {236, 48, 31},
    {162, 251, 143},
    {127, 133, 247}
};

const SDL_Color BG_COLOR = { 74,142,220 };

const SDL_Color COLOR_KEY = WHITE_COLOR;

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

const std::string WINDOW_TITLE = "CONNECT";
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 350;


inline void logSDLError(std::string error, bool fatal)
{
    std::cout << error << "Error: " << SDL_GetError() <<'\n';
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

inline void init_SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError("SDL_INIT", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError("SDL_CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) logSDLError("SDL_CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "software");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Surface* icon = IMG_Load("assets/image/icon.png");
    if (icon == nullptr) logSDLError("IMG_Load", true);
    SDL_SetColorKey(icon, SDL_TRUE,
                    SDL_MapRGB(icon->format, COLOR_KEY.r, COLOR_KEY.g, COLOR_KEY.b));
    SDL_SetWindowIcon(window, icon);
}


const int FPS = 144;

inline bool CheckInsideRect(const int &x, const int &y, const SDL_Rect container)
{
    if (x < container.x || x > container.x + container.w ||
        y < container.y || y > container.y + container.h)
    {
        return false;
    }
    return true;
}


enum game_status_
{
    PLAYING,
    PAUSE,
    QUIT_PAUSE,
    QUIT,
    RETURN_PAUSE,
    MENU,
    GET_USER_NAME,
    INTRODUCTION,
    PRINT_RANK,
    LOSE,
    HIGH_SCORE,
    PRINT_MUSIC
};

static SDL_Point mouse_button_down_pos;

inline void draw_circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; 
            int dy = radius - h; 
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
