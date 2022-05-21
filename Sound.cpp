#include "Sound.h"

Music::Music(const std::string& path)
{
    this->path = path;
    is_playing = false;
    is_started = false;
    muted_by_user = false;
}

void Music::LoadMusic()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
        logSDLError("Mix_OpenAudio", true);
    mus = Mix_LoadMUS(path.c_str());
    if (mus == nullptr)
        logSDLError("Mix_LoadMUS", true);
}

void Music::PlayMusic(const int &loops)
{
    if (!is_started && !muted_by_user)
    {
        Mix_PlayMusic(mus, loops);
        is_playing = true;
        is_started = true;
    }
}

void Music::PauseMusic()
{
    if (is_playing && is_started)
    {
        Mix_PauseMusic();
        is_playing = false;
    }
}

void Music::UnpauseMusic()
{
    if (!is_playing && is_started && !muted_by_user)
    {
        Mix_ResumeMusic();
        is_playing = true;
    }
}

void Music::HaltMusic()
{
    if (is_started)
    {
        Mix_HaltMusic();
        is_playing = false;
        is_started = false;
    }
}
