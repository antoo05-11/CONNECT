#pragma once
#include "BaseObject.h"
#include "button.h"
#include "Sound.h"
#include "Animation.h"

class MusicBox
{
    BaseObject* box_frame;
    BaseObject* name_song;
    button* game_button;
    int num_of_songs;
    SDL_Renderer* renderer;
    SDL_Texture* music_frame;

    bool clicked_at_bar_line;
    SDL_Rect bar_line;
    const SDL_Rect full_bar_line = { 327, 100, 16, 400 };

    SDL_Color color_of_bar_line = { 193,193,193,255};

    Music* music;
    int cur_song = -1;
    int song_chosen = -1;

    const SDL_Rect dst_music_frame_rect = { 0, 100,350, 400 };

    Animation* listen_sticker;

public:
    enum
    {
        QUIT_BUTTON,
        PLAY_MUSIC_BUTTON,
        STOP_MUSIC_BUTTON
    };
    MusicBox(SDL_Renderer*& renderer, int num_of_songs, std::string* name_string, Music*& music);
    ~MusicBox();
    void Render();
    void HandleEvent(SDL_Event& e, SDL_Point& mouse_button_pos, int& GAME_STATUS);
    void Update() const;
    int GetSong();
};

