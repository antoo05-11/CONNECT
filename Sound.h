#pragma once

#include "CommonFunc.h"

class Music
{
    Mix_Music* mus{};
    std::string path;
    bool is_playing;
    bool is_started;

public:
    bool muted_by_user;
    Music(const std::string& path);

    Music()
    {
    }

    ~Music()
    {
        Mix_FreeMusic(mus);
    };

    void SetPath(const std::string& path)
    {
        this->path = path;
        is_playing = false;
        is_started = false;
        muted_by_user = false;
    }

    void LoadMusic();
    void PlayMusic(const int& loops);
    void PauseMusic();
    void UnpauseMusic();
    void HaltMusic();

    bool IsPlaying()
    {
        return is_playing;
    }

    bool IsStarted()
    {
        return is_started;
    }

    bool IsMuted()
    {
        return muted_by_user;
    }
};
