#include "GameMap.h"

GameMap::GameMap()
{
    int size = 0;

    int TILE_SIZE = 0;
    int max_time = 0;
}
GameMap::~GameMap()
{
    
}

void GameMap::LoadMap(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open()) logSDLError("std::ifstream", true);
    file >> size;
    TILE_SIZE = 330 / size;

    for(int i = 0; i<size;i++)
    {
        xpos[i] = 10 + i * TILE_SIZE;
        ypos[i] = 135 + i * TILE_SIZE;
    }

    file >> num_of_color;
    file >> max_time;

    for(int j = 0; j < size; j++)
    {
        for(int i = 0; i<size; i++)
        {
            file >> map[i][j];
        }
    }
    file.close();

    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            map_with_status[i][j] = map[i][j] ;
        }
    }
}
void GameMap::RenderMap(SDL_Renderer* &renderer, BaseObject* image, button* game_button, Music& playing_music)
{
    RenderBackground(renderer, GetSize(), game_button, playing_music);
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            SDL_Rect dst_rect{ xpos[i], ypos[j], TILE_SIZE, TILE_SIZE };
            if(map[i][j] > 0)
            {
                draw_circle(renderer, 10 + i * GetMapTileSize() + GetMapTileSize() / 2, 135 + j*GetMapTileSize() + GetMapTileSize() / 2, 5*GetMapTileSize() / 12, CIRCLE_COLOR[map[i][j] - 1]);
            }
            if (map[i][j] == -1) image[1].render(renderer, nullptr, &dst_rect);
            if (map[i][j] == -2) image[2].render(renderer, nullptr, &dst_rect);
        }
    }
}
void GameMap::ResetStatusMap()
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            map_with_status[i][j] = map[i][j];
        }
    }
}
