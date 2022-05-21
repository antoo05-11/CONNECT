#include "button.h"

void button :: LoadButton(SDL_Renderer*& renderer, std::string path1, std::string path2)
{
    button_texture[0].loadImage(path1, renderer);
    button_texture[1].loadImage(path2, renderer);
}
void button::render(SDL_Renderer* renderer, const SDL_Rect* src_rect, const SDL_Rect* dst_rect, bool zoom)
{
    SDL_Point mouse_pos;
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    button_address.x = dst_rect->x;
    button_address.y = dst_rect->y;
    if (zoom)
    {
        if (this->IsInside(mouse_pos))
        {
            SDL_Rect new_dst_rect;
            new_dst_rect.h = dst_rect->h + 10;
            new_dst_rect.w = int(new_dst_rect.h * double(dst_rect->w) / dst_rect->h);
            new_dst_rect.x = dst_rect->x - (new_dst_rect.w - dst_rect->w) / 2;
            new_dst_rect.y = dst_rect->y - 5;
            SDL_RenderCopy(renderer, button_texture[1].getTexture(), src_rect, &new_dst_rect);
        }
        else SDL_RenderCopy(renderer, button_texture[0].getTexture(), src_rect, dst_rect);
    }
    else SDL_RenderCopy(renderer, button_texture[0].getTexture(), src_rect, dst_rect);
}
bool button::IsInside(const SDL_Point& p)
{
    return !(p.x < button_address.x || p.x > button_address.x + button_texture[0].getWidth() ||
             p.y < button_address.y || p.y > button_address.y + button_texture[0].getHeight());
}