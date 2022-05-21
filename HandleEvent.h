#pragma once

#include "CommonFunc.h"
#include "GameMap.h"
#include "HandleTime.h"
#include "Sound.h"

static std::vector<std::vector<std::pair<int, int>>> connection_from;
static std::vector<std::vector<std::pair<int, int>>> connection_to;
static std::vector<std::vector<int>> status_of_connection;
static std::vector<int> color_of_way;
static std::vector<bool> full_way;

enum DIRECTION
{
    NOWAY = 1000,
    RIGHT = 2000,
    LEFT = 3000,
    UP = 4000,
    DOWN = 5000
};

void DrawConnection(SDL_Renderer*& renderer,
                    GameMap& map,
                    std::vector<std::vector<std::pair<int, int>>>& connection_from,
                    std::vector<std::vector<std::pair<int, int>>>& connection_to,
                    std::vector<std::vector<int>>& status_of_connection,
                    std::vector<int>& color_of_way,
                    BaseObject*& image,
                    const int& cur_i);

static bool clicked = false;
static bool is_repeated = false; //check xem điểm mới bấm chuột đã có mặt ở mảng connected from chưa
static int cur_i = -1; //chỉ số đường đi đang nối hiện thời

enum playing_status
{
    COMPLETE,
    UNCOMPLETE,
};

static int PLAYING_STATUS = UNCOMPLETE;

void HandleEvent(const SDL_Event& e, GameMap& map,
                 std::vector<std::vector<std::pair<int, int>>>& connection_from,
                 std::vector<std::vector<std::pair<int, int>>>& connection_to,
                 std::vector<std::vector<int>>& status_of_connection,
                 std::vector<int>& color_of_way,
                 std::vector<bool>& full_way,
                 int& PLAYING_STATUS,
                 bool& clicked,
                 int& cur_i,
                 button* game_button,
                 SDL_Point &mouse_button_pos,
                 int& GAME_STATUS, 
                 Timer& playing_timer,
                 Music& playing_music);

