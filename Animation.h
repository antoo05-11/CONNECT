#pragma once
#include "BaseObject.h"
class Animation
{
    BaseObject* image;
    SDL_Renderer* renderer;
    SDL_Point start_point;
    int num_of_images;
    int k = 0;
    int cur_frame = 0;
public:
    Animation()
    {
        
    }
    ~Animation()
    {
        delete[] image;
    }
    void Load(SDL_Renderer*& renderer, const SDL_Point& start_point, const std::string& animation_path, const int& num_of_images) 
    {
        this->renderer = renderer;
        this->start_point = start_point;
        this->num_of_images = num_of_images;
        image = new BaseObject[num_of_images];
        for (int i = 0; i < num_of_images; i++)
        {
            image[i].loadImage(animation_path + std::to_string(i) + ".png", renderer);
        }
    }
    void Render()
    {
        SDL_Rect dst_rect = { start_point.x, start_point.y, image[cur_frame].getWidth(), image[cur_frame].getHeight() };
        image[cur_frame].render(renderer, nullptr, &dst_rect);
        k++;
        if (k % 20 == 0) cur_frame++;
        if (cur_frame >= num_of_images) cur_frame = 0;
    }
};

