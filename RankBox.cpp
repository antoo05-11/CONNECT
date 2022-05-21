#include "RankBox.h"
RankBox :: RankBox(SDL_Renderer*& renderer) : renderer(renderer)
{
    std::ifstream ReadRank("assets/rank/rank.txt");
    if (!ReadRank.is_open()) logSDLError("std::ifstream", true);
    for (int i = 0; i < 11; i++)
    {
        leader_board.push_back({ 0, "" });
        std::string s;
        getline(ReadRank, s);
        leader_board[i].second = s;
        getline(ReadRank, s);
        leader_board[i].first = std::stoi(s);
    }
    ReadRank.close();

    game_text = new BaseObject[22];
    std::sort(leader_board.begin(), leader_board.end());
    for (int i = 0; i < 11; i++)
    {
        game_text[i].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 20);
        game_text[i + 11].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 20);
        game_text[i].LoadText(leader_board[i].second, WHITE_COLOR, renderer);
        game_text[i + 11].LoadText("ROUND " + std::to_string(leader_board[i].first), WHITE_COLOR, renderer);
    }

    rank_frame.loadImage("assets/start_image/1.png", renderer);
}

RankBox ::~RankBox()
{
    rank_frame.free();
    leader_board.clear();
    delete[] game_text;
}

void RankBox::Load(SDL_Renderer*& renderer)
{
    this->renderer = renderer;
    std::ifstream ReadRank("assets/rank/rank.txt");
    if (!ReadRank.is_open()) logSDLError("std::ifstream", true);
    for (int i = 0; i < 11; i++)
    {
        leader_board.push_back({ 0, "" });
        std::string s;
        getline(ReadRank, s);
        leader_board[i].second = s;
        getline(ReadRank, s);
        leader_board[i].first = std::stoi(s);
    }
    ReadRank.close();

    game_text = new BaseObject[22];
    std::sort(leader_board.begin(), leader_board.end());
    for (int i = 0; i < 11; i++)
    {
        game_text[i].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 20);
        game_text[i + 11].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 20);
        game_text[i].LoadText(leader_board[i].second, WHITE_COLOR, renderer);
        game_text[i + 11].LoadText("ROUND " + std::to_string(leader_board[i].first), WHITE_COLOR, renderer);
    }

    rank_frame.loadImage("assets/start_image/1.png", renderer);
}


void RankBox::Render(int& GAME_STATUS)
{
   

    if (ZOOM_STATUS == NONE || ZOOM_STATUS == ZOOM_IN)
    {
        cur_height += 10;
        if (cur_height <= 450)
        {
            ZOOM_STATUS = ZOOM_IN;
        }

        if (cur_height > 450)
        {
            ZOOM_STATUS = FULL;
            cur_height = 450;
        }
    }
    if (ZOOM_STATUS == ZOOM_OUT)
    {
        cur_height -= 10;
        if (cur_height < 0)
        {
            ZOOM_STATUS = NONE;
            cur_height = 0;
            GAME_STATUS = MENU;
        }
    }

    draw_circle(renderer, 0, 0, 100, { 200, 0, 10, 255 });
    draw_circle(renderer, 250, 50, 80, { 50, 50, 150, 255 });

    SDL_Rect dst_rect;
    dst_rect.h = cur_height;
    dst_rect.w = double(rank_frame.getWidth()) / double(rank_frame.getHeight()) * cur_height;
    dst_rect.x = SCREEN_WIDTH / 2 - dst_rect.w / 2;
    dst_rect.y = SCREEN_HEIGHT / 2 - dst_rect.h / 2;

    rank_frame.render(renderer, nullptr, &dst_rect);

    if (ZOOM_STATUS == FULL)
    {
        for (int i = 0; i < 11; i++)
        {
            dst_rect = { 90, 145 + (10 - i) * 33, game_text[i].getWidth(), game_text[i].getHeight() };
            game_text[i].render(renderer, nullptr, &dst_rect);
            dst_rect = { 217, 145 + (10 - i) * 33, game_text[11 + i].getWidth(), game_text[11 + i].getHeight() };
            game_text[11 + i].render(renderer, nullptr, &dst_rect);
        }
    }

}

void RankBox::HandleEvent(SDL_Event& e, SDL_Point& mouse_button_pos)
{
    
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&mouse_button_pos.x, &mouse_button_pos.y);
    }
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (CheckInsideRect(x, y, quit_rank_rect) 
            && CheckInsideRect(mouse_button_pos.x, mouse_button_pos.y,
            quit_rank_rect))
        {
            ZOOM_STATUS = ZOOM_OUT;
        }
    }
}

bool RankBox::Update(const int& ROUND, const std::string& user_name)
{
    std::sort(leader_board.begin(), leader_board.end());
    if (ROUND >= leader_board[0].first)
    {

        leader_board[0].first = ROUND;
        leader_board[0].second = user_name;
        std::sort(leader_board.begin(), leader_board.end());

        for (int i = 0; i < 11; i++)
        {
            game_text[i].free();
            game_text[i + 11].free();
            game_text[i].LoadText(leader_board[i].second, WHITE_COLOR, renderer);
            game_text[i + 11].LoadText("ROUND " + std::to_string(leader_board[i].first), WHITE_COLOR, renderer);
        }
    }
    if (ROUND >= leader_board[leader_board.size() - 1].first)
    {
        return true;
    }
    return false;
}

void RankBox::SaveLeaderBoard()
{
    std::sort(leader_board.begin(), leader_board.end());
    std::ofstream SaveRank("assets/rank/rank.txt");
    for (int i = 0; i < 11; i++)
    {
        SaveRank << leader_board[i].second << '\n';
        SaveRank << leader_board[i].first << '\n';
    }
    SaveRank.close();
}