#include "MusicBox.h"

MusicBox :: MusicBox(SDL_Renderer*& renderer, int num_of_songs, std::string* name_string, Music*& music) : renderer(renderer)
{
    this->num_of_songs = num_of_songs;
    this->music = music;

    box_frame = new BaseObject[3];
    box_frame[0].loadImage("assets/start_image/3.png", renderer);
    box_frame[1].loadImage("assets/start_image/4.png", renderer);
    box_frame[2].loadImage("assets/start_image/5.png", renderer);

    game_button = new button[3];
    game_button[QUIT_BUTTON].LoadButton(renderer, "assets/button/0.png", "assets/button/20.png");
    game_button[PLAY_MUSIC_BUTTON].LoadButton(renderer, "assets/button/10.png", "assets/button/30.png");
    game_button[STOP_MUSIC_BUTTON].LoadButton(renderer, "assets/button/11.png", "assets/button/31.png");

    name_song = new BaseObject[num_of_songs];
    for (int i = 0; i < num_of_songs; i++)
    {
        name_song[i].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 20);
        name_song[i].LoadText(name_string[i], BLACK_COLOR, renderer);
    }

    music_frame = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    350, num_of_songs * 120);
    if (music_frame == nullptr) logSDLError("SDL_CreateTexture", true);


    clicked_at_bar_line = false;

    bar_line = { 330, 100, 10, int(400 * 400.0 / 120.0 / num_of_songs) };

    listen_sticker = new Animation[1];
    listen_sticker[0].Load(renderer, { 100, 490 },
                           "assets/listen_sticker/",
                           20);

}
MusicBox ::~MusicBox()
{
    delete[] box_frame;
    delete[] name_song;
    delete[] game_button;
}

void MusicBox::Render()
{
    listen_sticker[0].Render();

    SDL_Rect src_rect = { 0,int((bar_line.y - full_bar_line.y) / 400.0 * 120 * num_of_songs), 350, 400 };

    this->Update();
    SDL_RenderCopy(renderer, music_frame, &src_rect, &dst_music_frame_rect);

    SDL_SetRenderDrawColor(renderer, 241, 241, 241, 255);
    SDL_RenderFillRect(renderer, &full_bar_line);

    SDL_SetRenderDrawColor(renderer, color_of_bar_line.r, color_of_bar_line.g, color_of_bar_line.b, 255);
    SDL_RenderFillRect(renderer, &bar_line);

    SDL_Rect dst_rect = { 300, 10, 40, 40 };
    game_button[QUIT_BUTTON].render(renderer, nullptr, &dst_rect);

    dst_rect = { SCREEN_WIDTH / 2 - box_frame[2].getWidth() / 2, 0 , box_frame[2].getWidth(), box_frame[2].getHeight() };
    box_frame[2].render(renderer, nullptr, &dst_rect);


}

void MusicBox :: HandleEvent(SDL_Event& e, SDL_Point& mouse_button_pos, int& GAME_STATUS)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (CheckInsideRect(x, y, bar_line))
    {
        color_of_bar_line = { 120,120,120, 255 };
    }

    else if (!clicked_at_bar_line)
    {
        color_of_bar_line = { 193,193,193 , 255 };
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&mouse_button_pos.x, &mouse_button_pos.y);
        if (CheckInsideRect(mouse_button_pos.x, mouse_button_pos.y, bar_line))
        {
            clicked_at_bar_line = true;
            color_of_bar_line = { 120,120,120, 255 };
        }

        for (int i = 0; i < num_of_songs; i++)
        {
            SDL_Rect dst_rect = { 50, i * 120 + 35, 30, 30 };
            if (CheckInsideRect(mouse_button_pos.x, mouse_button_pos.y - 100 + int((bar_line.y - full_bar_line.y) / 400.0 * 120 * num_of_songs), dst_rect))
            {
                if (cur_song == i)
                {
                    cur_song = -1;
                    music[i].HaltMusic();
                }
                else
                {
                    if (cur_song >= 0)
                        if (music[cur_song].IsPlaying()) music[cur_song].HaltMusic();
                    cur_song = i;
                    music[cur_song].PlayMusic(-1);
                }
                song_chosen = cur_song;
            }

        }

    }
    if (e.type == SDL_MOUSEMOTION && clicked_at_bar_line)
    {
        SDL_GetMouseState(&x, &y);
        bar_line.y = bar_line.y + y - mouse_button_pos.y;
        mouse_button_pos = { x,y };

        if (bar_line.y + bar_line.h > full_bar_line.y + full_bar_line.h)
        {
            bar_line.y = full_bar_line.y + full_bar_line.h - bar_line.h;
        }
        if (bar_line.y < full_bar_line.y)
        {
            bar_line.y = full_bar_line.y;
        }
    }
    if (e.type == SDL_MOUSEWHEEL)
    {
        if (e.wheel.y > 0)
        {
            bar_line.y -= 5;

            if (bar_line.y + bar_line.h > full_bar_line.y + full_bar_line.h)
            {
                bar_line.y = full_bar_line.y + full_bar_line.h - bar_line.h;
            }
            if (bar_line.y < full_bar_line.y)
            {
                bar_line.y = full_bar_line.y;
            }
        }
        if (e.wheel.y < 0)
        {
            bar_line.y += 5;

            if (bar_line.y + bar_line.h > full_bar_line.y + full_bar_line.h)
            {
                bar_line.y = full_bar_line.y + full_bar_line.h - bar_line.h;
            }
            if (bar_line.y < full_bar_line.y)
            {
                bar_line.y = full_bar_line.y;
            }
        }
    }
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        if (clicked_at_bar_line)
        {
            clicked_at_bar_line = false;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (game_button[QUIT_BUTTON].IsInside(mouse_button_pos) && game_button[QUIT_BUTTON].IsInside({ x,y }))
        {
            GAME_STATUS = MENU;
            if (cur_song >= 0)
                music[cur_song].HaltMusic();
            cur_song = -1;
        }

    }
}
void MusicBox::Update() const
{
    SDL_SetRenderTarget(renderer, music_frame);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < num_of_songs; i++)
    {
        SDL_Rect dst_rect = { 10, i * 120, 300,100 };
        if (i % 2 == 0) box_frame[0].render(renderer, nullptr, &dst_rect);
        else box_frame[1].render(renderer, nullptr, &dst_rect);
    }
    for (int i = 0; i < num_of_songs; i++)
    {
        SDL_Rect dst_rect = { 110, i * 120 + 50, name_song[i].getWidth(),name_song[i].getHeight() };
        name_song[i].render(renderer, nullptr, &dst_rect);

        dst_rect = { 45, i * 120 + 40, 30, 30 };
        if (i != cur_song)
        {
            game_button[PLAY_MUSIC_BUTTON].render(renderer, nullptr, &dst_rect, false);
        }
        else
        {
            game_button[STOP_MUSIC_BUTTON].render(renderer, nullptr, &dst_rect, false);
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
}
int MusicBox::GetSong() { return (song_chosen == -1) ? 0 : song_chosen; }