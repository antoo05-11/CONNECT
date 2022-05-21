#include "TimeLine.h"

TimeLine::TimeLine()
{
    round = BaseObject("assets/font/URW Geometric Cond W03 Heavy.ttf", 19);
}

TimeLine::~TimeLine()
{
    
}


void TimeLine :: Load(SDL_Renderer*& renderer)
{
    time_box.loadImage("assets/play_image/time_box.png", renderer, &BLUE_COLOR);
    time_line.loadImage("assets/play_image/time_line.png", renderer);
}

void TimeLine::Render(SDL_Renderer*& renderer, const double& ratio, const int& round)
{
    SDL_Rect dst_rect = { 10, 510, time_box.getWidth(), time_box.getHeight() };
    time_box.render(renderer, nullptr, &dst_rect);
    SDL_Rect src_rect = { 0, 0, int(time_line.getWidth() * ratio), time_line.getHeight() };
    dst_rect = { 57, 535, src_rect.w, src_rect.h };
    time_line.render(renderer, &src_rect, &dst_rect);
    this->round.LoadText("Round " + std::to_string(round), BLACK_COLOR, renderer);
    dst_rect = {250, 532, 68, 24};
    this->round.render(renderer, nullptr, &dst_rect);
}