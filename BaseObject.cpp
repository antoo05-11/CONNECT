#include "BaseObject.h"


BaseObject::BaseObject() : object(nullptr)
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject()
{
    free();
}

void BaseObject::loadImage(const std::string& path, SDL_Renderer* & renderer, const SDL_Color* color)
{
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface == nullptr) logSDLError("IMG_LOAD(" + path + ")", true);

    if (color != nullptr)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE,
                        SDL_MapRGB(load_surface->format, color->r, color->g, color->b));
    }

    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    if (new_texture == nullptr) logSDLError("Create texture(" + path + ")", false);

    rect.w = load_surface->w;
    rect.h = load_surface->h;

    SDL_FreeSurface(load_surface);
    object = new_texture;
}

void BaseObject::render(SDL_Renderer* renderer, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
    SDL_RenderCopy(renderer, object, srcrect, dstrect);
}

void BaseObject::free()
{
    if (object != nullptr)
    {
        SDL_DestroyTexture(object);
        rect.w = 0;
        rect.h = 0;
    }
}

void BaseObject::LoadText(std::string text, SDL_Color color, SDL_Renderer*& renderer, int length_wrapped)
{
    SDL_Surface* surface;
    if (length_wrapped == 0)
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    else surface = TTF_RenderText_Solid_Wrapped(font, text.c_str(), color, length_wrapped);
    if (surface == nullptr) logSDLError("TTF_RenderText_Solid", true);
    rect.h = surface->h;
    rect.w = surface->w;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) logSDLError("SDL_CreateTextureFromSurface", true);
    object = texture;
    SDL_FreeSurface(surface);
}
