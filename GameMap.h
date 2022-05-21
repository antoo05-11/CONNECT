#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "button.h"
#include "HandleTime.h"
#include "Sound.h"


class GameMap
{
    int size;
    
    int xpos[100];
    int ypos[100];
    int TILE_SIZE;
    int max_time;
public:
    GameMap();
    ~GameMap();

    int map[100][100];
    int map_with_status[100][100];
    int num_of_color;

    void ResetStatusMap();

    void LoadMap(std::string path);
    void RenderMap(SDL_Renderer*& renderer, BaseObject* image, button* game_button, Music& playing_music);

    void HandleInputAction(SDL_Event e);

    int GetMapTileSize() const { return TILE_SIZE; }
    int GetSize() const { return size; }
    int GetTime() const { return max_time; }
};


inline void RenderBackground(SDL_Renderer*& renderer, int size_map, button* game_button, Music &playing_music)
{
    SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, 255);
    SDL_RenderClear(renderer);

    SDL_Rect dst_rect = { 290,10, 50, 50 };
    game_button[RETURN_BUTTON].render(renderer, nullptr, &dst_rect);

    dst_rect = { 225,10, 50,50 };
    game_button[PAUSE_BUTTON].render(renderer, nullptr, &dst_rect);

    dst_rect = { 160,10 ,50,50 };
    game_button[MUSIC_BUTTON_2].render(renderer, nullptr, &dst_rect);

    SDL_SetRenderDrawColor(renderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, 255);
    if (playing_music.muted_by_user)
    {
        SDL_RenderDrawLine(renderer, 171, 15, 201, 50);
    }

    dst_rect  = { 0, 100, 350, 400 };
    SDL_SetRenderDrawColor(renderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, 255);
    SDL_RenderFillRect(renderer, &dst_rect);

    dst_rect = { 10, 135, 330, 330 };
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, 255);
    SDL_RenderFillRect(renderer, &dst_rect);

    SDL_SetRenderDrawColor(renderer, 191, 191, 191 , 255);
    for (int i = 1; i < size_map; i++)
    {
        SDL_RenderDrawLine(renderer, dst_rect.x + dst_rect.w / size_map * i, dst_rect.y,
                           dst_rect.x + dst_rect.w / size_map * i, dst_rect.y + dst_rect.h);
        SDL_RenderDrawLine(renderer, dst_rect.x, dst_rect.y + dst_rect.h / size_map * i,
                           dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h / size_map * i);
    }

   
}