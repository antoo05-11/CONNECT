#pragma once
#include "BaseObject.h"

class RankBox
{
    SDL_Renderer* renderer;
    std::vector<std::pair<int, std::string>> leader_board;
    BaseObject* game_text;

    BaseObject rank_frame;
    int cur_height = 0;
    int ZOOM_STATUS = NONE;

    const SDL_Rect quit_rank_rect = { 282, 90, 51, 51 };


public:
    enum zoom_status_
    {
        NONE,
        ZOOM_IN,
        ZOOM_OUT,
        FULL
    };

    RankBox(SDL_Renderer*& renderer);

    ~RankBox();

    RankBox()
    {
        
    }
    void Load(SDL_Renderer*& renderer);
    void Render(int& GAME_STATUS);

    void HandleEvent(SDL_Event& e, SDL_Point& mouse_button_pos);

    bool Update(const int& ROUND, const std::string& user_name);

    void SaveLeaderBoard();
};
