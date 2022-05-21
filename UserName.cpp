#include "UserName.h"
UserName :: UserName(SDL_Renderer*& renderer)
{
    this->renderer = renderer;
    name_frame.LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 25);
    name_string = "";

    game_text = new BaseObject[2];
    game_text[GET_NAME_REQUEST].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 25);
    game_text[INTRO_GET_NAME].LoadFont("assets/font/URW Geometric Cond W03 Heavy.ttf", 25);
    game_text[GET_NAME_REQUEST].LoadText("PLEASE ENTER YOUR NAME", BLACK_COLOR, renderer);
    game_text[INTRO_GET_NAME].LoadText("PRESS ENTER TO CONTINUE", BLACK_COLOR, renderer);

    image = new BaseObject[1];
    image[0].loadImage("assets/start_image/2.png", renderer);

    game_button.LoadButton(renderer, "assets/button/1.png", "assets/button/21.png"); //Return button
}

UserName :: ~UserName()
{
    name_frame.FreeFont();
}


void UserName::HandleEvent(const SDL_Event& e, int& GAME_STATUS, Timer& playing_timer, SDL_Point &mouse_button_pos)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (name_string.length() > 0)
        {
            if (e.key.keysym.sym == SDLK_RETURN)
            {
                GAME_STATUS = PLAYING;
                playing_timer.Start();
            }
        }
        if (name_string.length() <= 10)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_SPACE:
                name_string = name_string + " ";
                break;
            case SDLK_a:
                name_string = name_string + "a";
                break;
            case SDLK_b:
                name_string = name_string + "b";
                break;
            case SDLK_c:
                name_string = name_string + "c";
                break;
            case SDLK_d:
                name_string = name_string + "d";
                break;
            case SDLK_e:
                name_string = name_string + "e";
                break;
            case SDLK_f:
                name_string = name_string + "f";
                break;
            case SDLK_g:
                name_string = name_string + "g";
                break;
            case SDLK_h:
                name_string = name_string + "h";
                break;
            case SDLK_k:
                name_string = name_string + "k";
                break;
            case SDLK_i:
                name_string = name_string + "i";
                break;
            case SDLK_j:
                name_string = name_string + "j";
                break;
            case SDLK_l:
                name_string = name_string + "l";
                break;
            case SDLK_m:
                name_string = name_string + "m";
                break;
            case SDLK_n:
                name_string = name_string + "n";
                break;
            case SDLK_o:
                name_string = name_string + "o";
                break;
            case SDLK_p:
                name_string = name_string + "p";
                break;
            case SDLK_q:
                name_string = name_string + "q";
                break;
            case SDLK_r:
                name_string = name_string + "r";
                break;
            case SDLK_s:
                name_string = name_string + "s";
                break;
            case SDLK_t:
                name_string = name_string + "t";
                break;
            case SDLK_u:
                name_string = name_string + "u";
                break;
            case SDLK_v:
                name_string = name_string + "v";
                break;
            case SDLK_w:
                name_string = name_string + "w";
                break;
            case SDLK_x:
                name_string = name_string + "x";
                break;
            case SDLK_y:
                name_string = name_string + "y";
                break;
            case SDLK_z:
                name_string = name_string + "z";
                break;
            case SDLK_1:
                name_string = name_string + "1";
                break;
            case SDLK_2:
                name_string = name_string + "2";
                break;
            case SDLK_3:
                name_string = name_string + "3";
                break;
            case SDLK_4:
                name_string = name_string + "4";
                break;
            case SDLK_5:
                name_string = name_string + "5";
                break;
            case SDLK_6:
                name_string = name_string + "6";
                break;
            case SDLK_7:
                name_string = name_string + "7";
                break;
            case SDLK_8:
                name_string = name_string + "8";
                break;
            case SDLK_9:
                name_string = name_string + "9";
                break;
            case SDLK_0:
                name_string = name_string + "0";
                break;
            }
        }
        if (e.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (name_string.length() > 0)
                name_string = name_string.erase(name_string.length() - 1, 1);
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&mouse_button_pos.x, &mouse_button_pos.y);
    }
    if(e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (game_button.IsInside({ x,y }) && game_button.IsInside(mouse_button_pos))
        {
            GAME_STATUS = MENU;
        }
    }
}

void UserName::Render()
{
    SDL_Rect dst_rect = {
        SCREEN_WIDTH / 2 - game_text[GET_NAME_REQUEST].getWidth() / 2, 150, game_text[GET_NAME_REQUEST].getWidth(),
        game_text[GET_NAME_REQUEST].getHeight()
    };
    game_text[GET_NAME_REQUEST].render(renderer, nullptr, &dst_rect);


    dst_rect = {
        SCREEN_WIDTH / 2 - game_text[INTRO_GET_NAME].getWidth() / 2, 300,
        game_text[INTRO_GET_NAME].getWidth(),
        game_text[INTRO_GET_NAME].getHeight()
    };
    game_text[INTRO_GET_NAME].render(renderer, nullptr, &dst_rect);


    dst_rect = { 150, 30, 50, 50 };
    game_button.render(renderer, nullptr, &dst_rect);

    dst_rect = {
        SCREEN_WIDTH / 2 - image[0].getWidth() / 2, 200, image[0].getWidth(),
        image[0].getHeight()
    };

    image[0].render(renderer, nullptr, &dst_rect);

    if (name_string.length() > 0)
    {
        name_frame.LoadText(name_string, WHITE_COLOR, renderer);
        dst_rect = {
            SCREEN_WIDTH / 2 - name_frame.getWidth() / 2, 215, name_frame.getWidth(), name_frame.getHeight()
        };
        name_frame.render(renderer, nullptr, &dst_rect);
        name_frame.free();
    }
}
std::string UserName::GetUserName() { return name_string; }
void UserName::ResetName() { name_string = ""; }