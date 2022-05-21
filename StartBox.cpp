#include "StartBox.h"
StartBox :: StartBox(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    game_button = new button[3];
    game_button[START_BUTTON].LoadButton(renderer, "assets/button/8.png", "assets/button/28.png");
    game_button[RANK_BUTTON].LoadButton(renderer, "assets/button/7.png", "assets/button/27.png");
    game_button[MUSIC_BUTTON].LoadButton(renderer, "assets/button/6.png", "assets/button/26.png");
    name_image.loadImage("assets/start_image/0.png", renderer, &BLACK_COLOR);
}

StartBox ::~StartBox()
{
    delete[] game_button;
}

void StartBox::Render()
{
    static SDL_Rect start_button_rect = { 100, 225, 150, 150 };
    static SDL_Rect rank_button_rect = { 50, 400, 100, 100 };
    static SDL_Rect name_rect = { 25, 100, 300, 51 };
    static SDL_Rect music_button_rect = { 200, 400, 100, 100 };

    draw_circle(renderer, 0, 0, 100, { 200, 0, 10, 255 });
    draw_circle(renderer, 250, 50, 80, { 50, 50, 150, 255 });
    game_button[START_BUTTON].render(renderer, nullptr, &start_button_rect);
    game_button[RANK_BUTTON].render(renderer, nullptr, &rank_button_rect);
    game_button[MUSIC_BUTTON].render(renderer, nullptr, &music_button_rect);
    name_image.render(renderer, nullptr, &name_rect);
}
void StartBox::HandleEvent(SDL_Event& e, int& GAME_STATUS, SDL_Point& mouse_button_down_pos)
{
    int x = 0, y = 0;
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&x, &y);
        mouse_button_down_pos.x = x;
        mouse_button_down_pos.y = y;
    }
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        SDL_GetMouseState(&x, &y);
        if (game_button[START_BUTTON].IsInside({ x, y }) && game_button[START_BUTTON].IsInside({ mouse_button_down_pos }))
        {
            GAME_STATUS = GET_USER_NAME;
        }
        if (game_button[RANK_BUTTON].IsInside({ x, y }) && game_button[RANK_BUTTON].IsInside({ mouse_button_down_pos }))
        {
            GAME_STATUS = PRINT_RANK;
        }
        if (game_button[MUSIC_BUTTON].IsInside({ x,y }) && game_button[MUSIC_BUTTON].IsInside({ mouse_button_down_pos }))
        {
            GAME_STATUS = PRINT_MUSIC;
        }
    }
}