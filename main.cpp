#include "button.h"
#include "GameMap.h"
#include "HandleEvent.h"
#include "HandleSmallEvents.h"
#include "HandleTime.h"
#include "HighScoreBox.h"
#include "MusicBox.h"
#include "RankBox.h"
#include "Sound.h"
#include "StartBox.h"
#include "TimeLine.h"
#include "UserName.h"

const int NUM_OF_MAPS = 23;

void LoadTexture(SDL_Renderer*& renderer, button*& game_button, BaseObject& quit_image, BaseObject*& game_text,
                 BaseObject*& image);

void DestroyEverything();

int GAME_STATUS = MENU;

int SMALL_STATUS = NONE; //Include Return status, Quit status, Pause status when GAME_STATUS == PLAYING

Timer fps_timer;
Timer playing_timer;

double ratio = 1; //Ratio = Time_pass / Max_time

TimeLine time_left;

int main(int argc, char* argv[]);

void LoadTexture(SDL_Renderer* &renderer, button* & game_button, BaseObject& quit_image, BaseObject* & game_text, 
                 BaseObject* & image)
{
    std::ifstream file("assets/tiles_and_way/infoColors.txt");
    if (!file.is_open()) logSDLError("std::ifstream", true);
    int num_of_colors;
    file >> num_of_colors;
    file.close();
    image = new BaseObject[500];
    for (int i = 1; i <= num_of_colors; i++)
    {
        image[100 + i].loadImage("assets/tiles_and_way/vertical_way/" + std::to_string(i) + ".png", renderer,
                                 &WHITE_COLOR);
        image[400 + i].loadImage("assets/tiles_and_way/horizontal_way/" + std::to_string(i) + ".png", renderer,
                                 &WHITE_COLOR);
        image[20 + i].loadImage("assets/tiles_and_way/bridge_way/up/" + std::to_string(20 + i) + ".png", renderer,
                                &WHITE_COLOR);
        image[40 + i].loadImage("assets/tiles_and_way/bridge_way/down/" + std::to_string(20 + i) + ".png", renderer,
                                &WHITE_COLOR);
        image[60 + i].loadImage("assets/tiles_and_way/bridge_way/left/" + std::to_string(20 + i) + ".png", renderer,
                                &WHITE_COLOR);
        image[80 + i].loadImage("assets/tiles_and_way/bridge_way/right/" + std::to_string(20 + i) + ".png", renderer,
                                &WHITE_COLOR);
        image[200 + i].loadImage("assets/tiles_and_way/bridge_way/middle_vertical/" + std::to_string(20 + i) + ".png",
                                 renderer, &WHITE_COLOR);
        image[300 + i].loadImage("assets/tiles_and_way/bridge_way/middle_horizontal/" + std::to_string(20 + i) + ".png",
                                 renderer, &WHITE_COLOR);
    }

    image[1].loadImage("assets/tiles_and_way/wall/1.png", renderer, &BLACK_COLOR);
    image[2].loadImage("assets/tiles_and_way/wall/2.png", renderer, &WHITE_COLOR);

    quit_image.loadImage("assets/quit_image/0.png", renderer, &GREEN_COLOR);

    game_button = new button[12];
    for (int i = 0; i < 12; i++)
    {
        game_button[i].LoadButton(renderer,
                                  "assets/button/" + std::to_string(i) + ".png",
                                  "assets/button/" + std::to_string(i + 20) + ".png");
    }

    game_text = new BaseObject[6];

    game_text[GET_NAME_REQUEST].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 24);
    game_text[RETURN_REQUEST].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 24);
    game_text[QUIT_REQUEST].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 24);
    game_text[PLAYER_NAME].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 24);
    game_text[GET_NAME_REQUEST].LoadText("ENTER YOUR NAME: ", BLACK_COLOR, renderer);
    game_text[RETURN_REQUEST].LoadText("DO YOU WANT TO RETURN?", BLACK_COLOR, renderer);
    game_text[QUIT_REQUEST].LoadText("DO YOU WANT TO QUIT?", BLACK_COLOR, renderer);
}

void DestroyEverything()
{
    delete[] game_button;
    delete[] image;
    delete[] game_text;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int SDL_main(int argc, char* argv[])
{
    init_SDL();
    LoadTexture(renderer, game_button, quit_image, game_text, image);

    time_left.Load(renderer);
    
    Music* playing_music = new Music[10];

    for(int i =0; i<10; i++)
    {
        playing_music[i].SetPath("assets/sound/" + std::to_string(i)+ ".mp3");
        playing_music[i].LoadMusic();
    }

    std::string name_song_string[10] = {
        "Default song",
        "Everytime",
        "Let her go",
        "We don't talk any more",
        "Pho da len den",
        "See you again",
        "Troi giau troi mang di",
        "Thang dien",
        "Angel Baby",
        "Payphone"
    };

    MusicBox music_frame(renderer, 10, name_song_string, playing_music);
    RankBox rank_frame(renderer);
    UserName name_frame(renderer);
    StartBox start_frame(renderer);
    HighScoreBox high_score_frame(renderer);
   
    SDL_Event e;

    GameMap* map;
    map = new GameMap[NUM_OF_MAPS];
    for (int i = 0; i < NUM_OF_MAPS; i++)
        map[i].LoadMap("assets/map/" + std::to_string(i + 1) + ".txt");
    int level = -1;

    while (GAME_STATUS != QUIT)
    {
        while (GAME_STATUS == MENU)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    GAME_STATUS = QUIT;
                    break;
                }
                start_frame.HandleEvent(e, GAME_STATUS, mouse_button_down_pos);
            }

            start_frame.Render();
            SDL_RenderPresent(renderer);

            level = 1;
        }

        while (GAME_STATUS == GET_USER_NAME)
        {
            SDL_SetRenderDrawColor(renderer, 218, 223, 225, 255);
            SDL_RenderClear(renderer);
            while (SDL_PollEvent(&e) != 0)
            {
                name_frame.HandleEvent(e, GAME_STATUS, playing_timer, mouse_button_down_pos);
            }

            name_frame.Render();
            SDL_RenderPresent(renderer);
        }

        while (GAME_STATUS == PRINT_RANK)
        {
            fps_timer.Start();

            SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, 255);
            SDL_RenderClear(renderer);
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    GAME_STATUS = QUIT;
                    break;
                }
                rank_frame.HandleEvent(e, mouse_button_down_pos);
            }
            rank_frame.Render(GAME_STATUS);
            SDL_RenderPresent(renderer);

            //Handle FPS
            if (fps_timer.GetTime() < 1000 / FPS) SDL_Delay(1000 / FPS - fps_timer.GetTime());
            fps_timer.Stop();
        }

        while (GAME_STATUS == PRINT_MUSIC)
        {
            fps_timer.Start();

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    GAME_STATUS = QUIT;
                    break;
                }
                music_frame.HandleEvent(e, mouse_button_down_pos, GAME_STATUS);
            }
            music_frame.Render();
            SDL_RenderPresent(renderer);

            //Handle FPS
            if (fps_timer.GetTime() < 1000.0 / FPS) SDL_Delay(1000.0 / FPS - fps_timer.GetTime());
            fps_timer.Stop();
        }

        while (GAME_STATUS == PLAYING ||
            GAME_STATUS == QUIT_PAUSE ||
            GAME_STATUS == RETURN_PAUSE ||
            GAME_STATUS == PAUSE)
        {
            
            playing_music[music_frame.GetSong()].PlayMusic(-1);
            playing_music[music_frame.GetSong()].UnpauseMusic();

            fps_timer.Start();

            if (PLAYING_STATUS == COMPLETE)
            {
                level++;
                PLAYING_STATUS = UNCOMPLETE;
                playing_timer.Stop();
                playing_timer.Start();
                ratio = 1;
            }

            ratio = 1 - playing_timer.GetTime() / static_cast<double>(map[level - 1].GetTime() * 1000);

            if (ratio < 0)
            {
                GAME_STATUS = LOSE;

                connection_from.clear();
                connection_to.clear();
                status_of_connection.clear();
                full_way.clear();
                color_of_way.clear();
                for (int i = 0; i < level; i++)
                {
                    map[i].ResetStatusMap();
                }
                cur_i = -1;
                clicked = false;
                if (rank_frame.Update(level,name_frame.GetUserName()))
                {
                    GAME_STATUS = HIGH_SCORE;
                    playing_timer.Stop();
                    playing_timer.Start();
                }
                break;
            }

            map[level - 1].RenderMap(renderer, image, game_button, playing_music[music_frame.GetSong()]);

            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    GAME_STATUS = QUIT_PAUSE;
                    playing_timer.Paused();
                }
                HandleEvent(e, map[level - 1], connection_from, connection_to, status_of_connection, color_of_way,
                            full_way,
                            PLAYING_STATUS, clicked, cur_i, game_button, mouse_button_down_pos, GAME_STATUS,
                            playing_timer, playing_music[music_frame.GetSong()]);
            }

            DrawConnection(renderer, map[level - 1], connection_from, connection_to, status_of_connection, color_of_way,
                           image, cur_i);

            time_left.Render(renderer, ratio, level);

            while (GAME_STATUS == QUIT_PAUSE)
            {
                playing_music[music_frame.GetSong()].PauseMusic();
                while (SDL_PollEvent(&e) != 0)
                {
                    HandleQuitGame(e, SMALL_STATUS);

                    if (SMALL_STATUS == ALLOWED_TO_DO)
                    {
                        GAME_STATUS = QUIT;
                    }
                    if (SMALL_STATUS == NOT_ALLOWED_TO_DO)
                    {
                        SMALL_STATUS = NONE;
                        GAME_STATUS = PLAYING;
                        playing_timer.Unpaused();
                    }
                }
                RenderQuitGame(renderer, quit_image, game_button, game_text);
                SDL_RenderPresent(renderer);
            }

            while (GAME_STATUS == RETURN_PAUSE)
            {
                playing_music[music_frame.GetSong()].PauseMusic();
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        GAME_STATUS = QUIT_PAUSE;
                        playing_timer.Paused();
                    }
                    else
                    {
                        HandleReturnEvent(e, SMALL_STATUS);

                        if (SMALL_STATUS == ALLOWED_TO_DO)
                        {
                            GAME_STATUS = PLAYING;

                            connection_from.clear();
                            connection_to.clear();
                            status_of_connection.clear();
                            full_way.clear();
                            color_of_way.clear();
                            for (int i = 0; i < level; i++)
                            {
                                map[i].ResetStatusMap();
                            }
                            cur_i = -1;
                            clicked = false;

                            level = 1;
                            SMALL_STATUS = NONE;

                            playing_timer.Stop();
                            playing_timer.Start();
                        }
                        if (SMALL_STATUS == NOT_ALLOWED_TO_DO)
                        {
                            SMALL_STATUS = NONE;
                            GAME_STATUS = PLAYING;
                            playing_timer.Unpaused();
                        }
                    }
                }
                RenderReturnEvent(renderer, quit_image, game_button, game_text);
                SDL_RenderPresent(renderer);
            }

            while (GAME_STATUS == PAUSE)
            {
                playing_music[music_frame.GetSong()].PauseMusic();
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        GAME_STATUS = QUIT_PAUSE;
                        playing_timer.Paused();
                    }
                    else
                    {
                        HandlePauseEvent(e, SMALL_STATUS, game_button, mouse_button_down_pos);
                        if (SMALL_STATUS == ALLOWED_TO_DO)
                        {
                            SMALL_STATUS = NONE;
                            playing_timer.Unpaused();
                            GAME_STATUS = PLAYING;
                        }
                    }
                }
                RenderPauseFrame(renderer, quit_image, game_button);
                SDL_RenderPresent(renderer);
            }

            SDL_RenderPresent(renderer);

            //Handle FPS
            if (fps_timer.GetTime() < 1000 / FPS) SDL_Delay(1000 / FPS - fps_timer.GetTime());
            fps_timer.Stop();
        }
        while (GAME_STATUS == HIGH_SCORE)
        {
            SDL_SetRenderDrawColor(renderer, 22, 26, 26, 255);
            SDL_RenderClear(renderer);

            high_score_frame.Render();

            SDL_RenderPresent(renderer);
           
            if(playing_timer.GetTime()>5000)
            {
                GAME_STATUS = LOSE;
            }
        }
        while (GAME_STATUS == LOSE)
        {
            playing_timer.Stop();
            playing_music[music_frame.GetSong()].HaltMusic();
            name_frame.ResetName();
            GAME_STATUS = MENU;
        }
    }

    if (GAME_STATUS == QUIT)
    {
        rank_frame.SaveLeaderBoard();
        DestroyEverything();
    }

    return 0;
}
