#include "HandleEvent.h"

void DrawConnection(SDL_Renderer*& renderer,
                    GameMap& map,
                    std::vector<std::vector<std::pair<int, int>>>& connection_from,
                    std::vector<std::vector<std::pair<int, int>>>& connection_to,
                    std::vector<std::vector<int>>& status_of_connection,
                    std::vector<int>& color_of_way,
                    BaseObject*& image,
                    const int& cur_i)
{
    double tile_size = 330.0 / map.GetSize();
    for (int i = 0; i < connection_from.size(); i++)
    {
        if (!connection_to[i].empty() && i != cur_i)
            for (int j = 0; j < status_of_connection[i].size(); j++)
            {
                //Check if some full way is gone over by current way when clicking and moving mouse
                bool check = true;
                if (cur_i >= 0)
                {
                    int k = 0;
                    for (k = 0; k < connection_to[cur_i].size(); k++)
                    {
                        if (connection_to[cur_i][k].first == connection_to[i][j].first &&
                            connection_to[cur_i][k].second == connection_to[i][j].second &&
                            map.map[connection_to[cur_i][k].first][connection_to[cur_i][k].second] != -2)
                        {
                            check = false;
                            break;
                        }

                        if (connection_to[cur_i][k].first == connection_from[i][j].first &&
                            connection_to[cur_i][k].second == connection_from[i][j].second &&
                            map.map[connection_to[cur_i][k].first][connection_to[cur_i][k].second] != -2)
                        {
                            check = false;
                            break;
                        }
                    }
                }

                if (check)
                {
                    if (map.map[connection_to[i][j].first][connection_to[i][j].second] != -2 && 
                        map.map[connection_from[i][j].first][connection_from[i][j].second] != -2)
                    {
                        if (status_of_connection[i][j] == RIGHT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10 - 3 * tile_size / 4),
                                static_cast<int>(connection_to[i][j].second * tile_size + tile_size / 4 + 135),
                                static_cast<int>(3 * tile_size / 2),
                                static_cast<int>(tile_size / 2)
                            };

                            image[color_of_way[i] + 400].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == LEFT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10 + tile_size / 4),
                                static_cast<int>(connection_to[i][j].second * tile_size + tile_size / 4 + 135),
                                static_cast<int>(3 * tile_size / 2),
                                static_cast<int>(tile_size / 2)
                            };
                            image[color_of_way[i] + 400].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == UP)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10 + tile_size / 4),
                                static_cast<int>(connection_to[i][j].second * tile_size + tile_size / 4 + 135),
                                static_cast<int>(tile_size / 2),
                                static_cast<int>(3 * tile_size / 2)
                            };
                            image[color_of_way[i] + 100].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == DOWN)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10 + tile_size / 4),
                                static_cast<int>(connection_to[i][j].second * tile_size - 3 * tile_size / 4 + 135),
                                static_cast<int>(tile_size / 2),
                                static_cast<int>(3 * tile_size / 2)
                            };
                            image[color_of_way[i] + 100].render(renderer, nullptr, &dst_rect);
                        }
                    }

                    else if (map.map[connection_to[i][j].first][connection_to[i][j].second] == -2 && 
                             map.map[connection_from[i][j].first][connection_from[i][j].second] != -2)
                    {
                        if (status_of_connection[i][j] == RIGHT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(tile_size / 3 + tile_size * (connection_to[i][j].first - 1)) + 10,
                                static_cast<int>(connection_to[i][j].second * tile_size) + 135,
                                static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                                static_cast<int>(tile_size)
                            };

                            image[color_of_way[i] + 80].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == LEFT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(tile_size / 2 + tile_size * (connection_to[i][j].first)) + 10,
                                static_cast<int>(connection_to[i][j].second * tile_size) + 135,
                                static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                                static_cast<int>(tile_size)
                            };
                            image[color_of_way[i] + 60].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == UP)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10),
                                static_cast<int>((connection_to[i][j].second) * tile_size + tile_size * 13 / 20 + 135),
                                static_cast<int>(tile_size),
                                static_cast<int>(1.1 * tile_size)
                            };
                            image[color_of_way[i] + 20].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == DOWN)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_to[i][j].first * tile_size + 10),
                                static_cast<int>((connection_to[i][j].second - 1) * tile_size + tile_size / 4 + 135),
                                static_cast<int>(tile_size),
                                static_cast<int>(0.9 * tile_size)
                            };
                            image[color_of_way[i] + 40].render(renderer, nullptr, &dst_rect);
                        }
                    }

                    else if (map.map[connection_from[i][j].first][connection_from[i][j].second] == -2 && 
                             map.map[connection_to[i][j].first][connection_to[i][j].second] != -2)
                    {
                        if (status_of_connection[i][j] == RIGHT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>((connection_from[i][j].first) * tile_size + 10 + tile_size / 2),
                                static_cast<int>(connection_from[i][j].second * tile_size) + 135,
                                static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                                static_cast<int>(tile_size)
                            };

                            image[color_of_way[i] + 60].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == LEFT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>((connection_from[i][j].first - 1) * tile_size + 10 + tile_size / 3),
                                static_cast<int>(connection_from[i][j].second * tile_size) + 135,
                                static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                                static_cast<int>(tile_size)
                            };
                            image[color_of_way[i] + 80].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == UP)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_from[i][j].first * tile_size + 10),
                                static_cast<int>((connection_from[i][j].second - 1) * tile_size + tile_size / 4 + 135),
                                static_cast<int>(tile_size),
                                static_cast<int>(0.9 * tile_size)
                            };
                            image[color_of_way[i] + 40].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == DOWN)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_from[i][j].first * tile_size + 10),
                                static_cast<int>((connection_from[i][j].second) * tile_size + tile_size * 13 / 20 +
                                    135),
                                static_cast<int>(tile_size),
                                static_cast<int>(1.1 * tile_size)
                            };
                            image[color_of_way[i] + 20].render(renderer, nullptr, &dst_rect);
                        }
                    }

                    else if (map.map[connection_from[i][j].first][connection_from[i][j].second] == -2 && map.map[
                        connection_to[i][j].first][connection_to[i][j].second] == -2)
                    {
                        if (status_of_connection[i][j] == RIGHT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>((connection_from[i][j].first) * tile_size + 10 + tile_size / 2),
                                static_cast<int>(connection_from[i][j].second * tile_size) + 135,
                                static_cast<int>(tile_size),
                                static_cast<int>(tile_size)
                            };

                            image[color_of_way[i] + 300].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == LEFT)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>((connection_from[i][j].first - 1) * tile_size + 10 + tile_size / 2),
                                static_cast<int>(connection_from[i][j].second * tile_size) + 135,
                                static_cast<int>(tile_size),
                                static_cast<int>(tile_size)
                            };
                            image[color_of_way[i] + 300].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == UP)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_from[i][j].first * tile_size + 10),
                                static_cast<int>((connection_from[i][j].second - 1) * tile_size + tile_size * 13 / 20 +
                                    135),
                                static_cast<int>(tile_size),
                                static_cast<int>(0.5 * tile_size)
                            };
                            image[color_of_way[i] + 200].render(renderer, nullptr, &dst_rect);
                        }
                        if (status_of_connection[i][j] == DOWN)
                        {
                            SDL_Rect dst_rect = {
                                static_cast<int>(connection_from[i][j].first * tile_size + 10),
                                static_cast<int>((connection_from[i][j].second) * tile_size + tile_size * 13 / 20 +
                                    135),
                                static_cast<int>(tile_size),
                                static_cast<int>(0.5 * tile_size)
                            };
                            image[color_of_way[i] + 200].render(renderer, nullptr, &dst_rect);
                        }
                    }
                }
            }
    }

    //Draw current way if clicking and move mouse
    if (cur_i >= 0)
    {
        for (int j = 0; j < connection_to[cur_i].size(); j++)
        {
            if (map.map[connection_to[cur_i][j].first][connection_to[cur_i][j].second] != -2 && 
                map.map[connection_from[cur_i][j].first][connection_from[cur_i][j].second] != -2)
            {
                if (status_of_connection[cur_i][j] == RIGHT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10 - 3 * tile_size / 4),
                        static_cast<int>(connection_to[cur_i][j].second * tile_size + tile_size / 4 + 135),
                        static_cast<int>(3 * tile_size / 2),
                        static_cast<int>(tile_size / 2)
                    };

                    image[color_of_way[cur_i] + 400].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == LEFT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10 + tile_size / 4),
                        static_cast<int>(connection_to[cur_i][j].second * tile_size + tile_size / 4 + 135),
                        static_cast<int>(3 * tile_size / 2),
                        static_cast<int>(tile_size / 2)
                    };
                    image[color_of_way[cur_i] + 400].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == UP)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10 + tile_size / 4),
                        static_cast<int>(connection_to[cur_i][j].second * tile_size + tile_size / 4 + 135),
                        static_cast<int>(tile_size / 2),
                        static_cast<int>(3 * tile_size / 2)
                    };
                    image[color_of_way[cur_i] + 100].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == DOWN)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10 + tile_size / 4),
                        static_cast<int>(connection_to[cur_i][j].second * tile_size - 3 * tile_size / 4 + 135),
                        static_cast<int>(tile_size / 2),
                        static_cast<int>(3 * tile_size / 2)
                    };
                    image[color_of_way[cur_i] + 100].render(renderer, nullptr, &dst_rect);
                }
            }

            else if (map.map[connection_to[cur_i][j].first][connection_to[cur_i][j].second] == -2 && 
                     map.map[connection_from[cur_i][j].first][connection_from[cur_i][j].second] != -2)
            {
                if (status_of_connection[cur_i][j] == RIGHT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(tile_size / 3 + tile_size * (connection_to[cur_i][j].first - 1)) + 10,
                        static_cast<int>(connection_to[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                        static_cast<int>(tile_size)
                    };

                    image[color_of_way[cur_i] + 80].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == LEFT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(tile_size / 2 + tile_size * (connection_to[cur_i][j].first)) + 10,
                        static_cast<int>(connection_to[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                        static_cast<int>(tile_size)
                    };
                    image[color_of_way[cur_i] + 60].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == UP)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_to[cur_i][j].second) * tile_size + tile_size * 13 / 20 + 135),
                        static_cast<int>(tile_size),
                        static_cast<int>(1.1 * tile_size)
                    };
                    image[color_of_way[cur_i] + 20].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == DOWN)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_to[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_to[cur_i][j].second - 1) * tile_size + tile_size / 4 + 135),
                        static_cast<int>(tile_size),
                        static_cast<int>(0.9 * tile_size)
                    };
                    image[color_of_way[cur_i] + 40].render(renderer, nullptr, &dst_rect);
                }
            }

            else if (map.map[connection_from[cur_i][j].first][connection_from[cur_i][j].second] == -2 && 
                     map.map[connection_to[cur_i][j].first][connection_to[cur_i][j].second] != -2)
            {
                if (status_of_connection[cur_i][j] == RIGHT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>((connection_from[cur_i][j].first) * tile_size + 10 + tile_size / 2),
                        static_cast<int>(connection_from[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                        static_cast<int>(tile_size)
                    };

                    image[color_of_way[cur_i] + 60].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == LEFT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>((connection_from[cur_i][j].first - 1) * tile_size + 10 + tile_size / 3),
                        static_cast<int>(connection_from[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(2.0 / 3.0 * tile_size + tile_size / 2.0),
                        static_cast<int>(tile_size)
                    };
                    image[color_of_way[cur_i] + 80].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == UP)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_from[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_from[cur_i][j].second - 1) * tile_size + tile_size / 4 + 135),
                        static_cast<int>(tile_size),
                        static_cast<int>(0.9 * tile_size)
                    };
                    image[color_of_way[cur_i] + 40].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == DOWN)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_from[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_from[cur_i][j].second) * tile_size + tile_size * 13 / 20 + 135),
                        static_cast<int>(tile_size),
                        static_cast<int>(1.1 * tile_size)
                    };
                    image[color_of_way[cur_i] + 20].render(renderer, nullptr, &dst_rect);
                }
            }

            else if (map.map[connection_from[cur_i][j].first][connection_from[cur_i][j].second] == -2 
            && map.map[connection_to[cur_i][j].first][connection_to[cur_i][j].second] == -2)
            {
                if (status_of_connection[cur_i][j] == RIGHT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>((connection_from[cur_i][j].first) * tile_size + 10 + tile_size / 2),
                        static_cast<int>(connection_from[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(tile_size),
                        static_cast<int>(tile_size)
                    };

                    image[color_of_way[cur_i] + 300].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == LEFT)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>((connection_from[cur_i][j].first - 1) * tile_size + 10 + tile_size / 2),
                        static_cast<int>(connection_from[cur_i][j].second * tile_size) + 135,
                        static_cast<int>(tile_size),
                        static_cast<int>(tile_size)
                    };
                    image[color_of_way[cur_i] + 300].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == UP)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_from[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_from[cur_i][j].second - 1) * tile_size + tile_size * 13 / 20 +
                            135),
                        static_cast<int>(tile_size),
                        static_cast<int>(0.5 * tile_size)
                    };
                    image[color_of_way[cur_i] + 200].render(renderer, nullptr, &dst_rect);
                }
                if (status_of_connection[cur_i][j] == DOWN)
                {
                    SDL_Rect dst_rect = {
                        static_cast<int>(connection_from[cur_i][j].first * tile_size + 10),
                        static_cast<int>((connection_from[cur_i][j].second) * tile_size + tile_size * 13 / 20 + 135),
                        static_cast<int>(tile_size),
                        static_cast<int>(0.5 * tile_size)
                    };
                    image[color_of_way[cur_i] + 200].render(renderer, nullptr, &dst_rect);
                }
            }
        }
    }
}


void HandleEvent(const SDL_Event& e, GameMap& map,
                 std::vector<std::vector<std::pair<int, int>>>& connection_from,
                 std::vector<std::vector<std::pair<int, int>>>& connection_to,
                 std::vector<std::vector<int>>& status_of_connection,
                 std::vector<int>& color_of_way,
                 std::vector<bool>& full_way,
                 int& PLAYING_STATUS,
                 bool& clicked,
                 int& cur_i,
                 button * game_button,
                 SDL_Point &mouse_button_pos,
                 int&GAME_STATUS,
                 Timer &playing_timer,
                 Music &playing_music)
{
    const int tile_size = map.GetMapTileSize();

    //Find the current coordinates an d then convert to the coordinates in the main table
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        mouse_button_pos = {x, y};
    }
    if(e.type == SDL_MOUSEBUTTONUP)
    {
        if (game_button[RETURN_BUTTON].IsInside(mouse_button_pos) && game_button[RETURN_BUTTON].IsInside({ x, y }))
        {
            GAME_STATUS = RETURN_PAUSE;
            playing_timer.Paused();
        }
        if (game_button[PAUSE_BUTTON].IsInside(mouse_button_pos) && game_button[PAUSE_BUTTON].IsInside({ x,y }))
        {
            GAME_STATUS = PAUSE;
            playing_timer.Paused();
        }
        if (game_button[MUSIC_BUTTON_2].IsInside({ mouse_button_pos }) && game_button[MUSIC_BUTTON_2].IsInside({ x,y }))
        {
            if (playing_music.IsPlaying())
            {
                playing_music.PauseMusic();
                playing_music.muted_by_user = true;
            }
            else
            {
                playing_music.UnpauseMusic();
                playing_music.muted_by_user = false;
            }
        }
    }

    x -= 10;
    y -= 135;
    const int m = x / tile_size;
    const int n = y / tile_size;

    if (x >= 0 && x <= 330 && y >= 0 && y <= 330)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            clicked = true;
          
            //Check if the mouse is clicked on the cell that belongs to one of the available ways
            is_repeated = false;
            for (int i = 0; i < connection_to.size(); i++)
            {
                for (int j = 0; j < connection_to[i].size(); j++)
                {
                    if (m == connection_to[i][j].first && n == connection_to[i][j].second)
                    {
                        cur_i = i;
                        is_repeated = true;
                        int delete_times = connection_to[i].size() - j - 1;
                        while (delete_times--)
                        {
                            connection_from[i].pop_back();
                            connection_to[i].pop_back();
                            status_of_connection[i].pop_back();
                        }
                        full_way[i] = false;
                        connection_from[cur_i].push_back({connection_to[cur_i][connection_to[cur_i].size() - 1]});
                        break;
                    }
                }

                if (m == connection_from[i][0].first && n == connection_from[i][0].second)
                {
                    cur_i = i;
                    is_repeated = true;
                    connection_from[i].clear();
                    connection_to[i].clear();
                    status_of_connection[i].clear();
                    full_way[i] = false;
                    connection_from[cur_i].emplace_back(m, n);
                }

                if (is_repeated) break;
            }

            //Clicking on a colored cell and do not belong to any available ways, create a new line.
            if (!is_repeated && map.map[m][n] > 0)
            {
                std::vector<std::pair<int, int>> new_connection;
                connection_from.push_back(new_connection);
                connection_to.push_back(new_connection);
                std::vector<int> new_status_connection;
                status_of_connection.push_back(new_status_connection);
                full_way.push_back(false);
                connection_from[connection_from.size() - 1].emplace_back(m, n);
                cur_i = connection_from.size() - 1;
                color_of_way.push_back(map.map[m][n]);
            }

            //Check if the ways (not the current way) are full, then delete them.
            for (int i = 0; i < connection_from.size(); i++)
            {
                if (i != cur_i)
                    if (!full_way[i])
                    {
                        connection_from.erase(connection_from.begin() + i);
                        connection_to.erase(connection_to.begin() + i);
                        full_way.erase(full_way.begin() + i);
                        status_of_connection.erase(status_of_connection.begin() + i);
                        color_of_way.erase(color_of_way.begin() + i);
                        if (cur_i > i) cur_i -= 1;
                        break;
                    }
            }

            //If clicking on an empty cell
            if (!is_repeated && map.map[m][n] <= 0)
            {
                clicked = false;
            }
        }

        

        if (e.type == SDL_MOUSEMOTION && clicked)
        {
            if (!full_way[cur_i])
                if (map.map[m][n] == 0 || (map.map[m][n] == color_of_way[cur_i]) || map.map[m][n] == -2)
                {
                    if (m == connection_from[cur_i][connection_from[cur_i].size() - 1].first &&
                        n == connection_from[cur_i][connection_from[cur_i].size() - 1].second + 1)
                    {
                        if ((map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                    cur_i][connection_from[cur_i].size() - 1].second] == -2
                                && status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != LEFT &&
                                status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != RIGHT)
                            || map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                cur_i][connection_from[cur_i].size() - 1].second] != -2)
                        {
                            status_of_connection[cur_i].push_back(DOWN);
                            connection_to[cur_i].emplace_back(m, n);
                            connection_from[cur_i].emplace_back(m, n);
                        }
                    }
                    if (m == connection_from[cur_i][connection_from[cur_i].size() - 1].first &&
                        n == connection_from[cur_i][connection_from[cur_i].size() - 1].second - 1)
                    {
                        if ((map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                    cur_i][connection_from[cur_i].size() - 1].second] == -2
                                && status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != LEFT &&
                                status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != RIGHT)
                            || map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                cur_i][connection_from[cur_i].size() - 1].second] != -2)
                        {
                            status_of_connection[cur_i].push_back(UP);
                            connection_to[cur_i].emplace_back(m, n);
                            connection_from[cur_i].emplace_back(m, n);
                        }
                    }
                    if (m == connection_from[cur_i][connection_from[cur_i].size() - 1].first - 1 &&
                        n == connection_from[cur_i][connection_from[cur_i].size() - 1].second)
                    {
                        if ((map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                    cur_i][connection_from[cur_i].size() - 1].second] == -2
                                && status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != UP &&
                                status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != DOWN)
                            || map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                cur_i][connection_from[cur_i].size() - 1].second] != -2)
                        {
                            status_of_connection[cur_i].push_back(LEFT);
                            connection_to[cur_i].emplace_back(m, n);
                            connection_from[cur_i].emplace_back(m, n);
                        }
                    }
                    if (m == connection_from[cur_i][connection_from[cur_i].size() - 1].first + 1 &&
                        n == connection_from[cur_i][connection_from[cur_i].size() - 1].second)
                    {
                        if ((map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                    cur_i][connection_from[cur_i].size() - 1].second] == -2
                                && status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != UP &&
                                status_of_connection[cur_i][status_of_connection[cur_i].size() - 1] != DOWN)
                            || map.map[connection_from[cur_i][connection_from[cur_i].size() - 1].first][connection_from[
                                cur_i][connection_from[cur_i].size() - 1].second] != -2)
                        {
                            status_of_connection[cur_i].push_back(RIGHT);
                            connection_to[cur_i].emplace_back(m, n);
                            connection_from[cur_i].emplace_back(m, n);
                        }
                    }
                }

            //Check if the cur_i way is full
            if (!connection_to[cur_i].empty())
            {
                if ((connection_from[cur_i][0].first != connection_to[cur_i][connection_to[cur_i].size() - 1].first ||
                        connection_from[cur_i][0].second != connection_to[cur_i][connection_to[cur_i].size() - 1].
                        second) &&
                    map.map[connection_to[cur_i][connection_to[cur_i].size() - 1].first][connection_to[cur_i][
                        connection_to[cur_i].size() - 1].second]
                    == color_of_way[cur_i])
                {
                    full_way[cur_i] = true;
                }
            }

            //Check if player go back
            for (int j = 0; j < connection_from[cur_i].size() - 1; j++)
            {
                if (m == connection_from[cur_i][j].first && n == connection_from[cur_i][j].second)
                {
                    for (int k = j; k < connection_from[cur_i].size(); k++)
                    {
                        connection_from[cur_i].pop_back();
                        connection_to[cur_i].pop_back();
                        status_of_connection[cur_i].pop_back();
                        full_way[cur_i] = false;
                    }
                    break;
                }
            }
        }

        if (e.type == SDL_MOUSEBUTTONUP && clicked)
        {
            if (!connection_to[cur_i].empty())
                if (connection_from[cur_i][0].first != connection_to[cur_i][connection_to[cur_i].size() - 1].first &&
                    connection_from[cur_i][0].second != connection_to[cur_i][connection_to[cur_i].size() - 1].second &&
                    map.map[connection_to[cur_i][connection_to[cur_i].size() - 1].first][connection_to[cur_i][
                        connection_to[cur_i].size() - 1].second] == color_of_way[cur_i])
                {
                    full_way[cur_i] = true;
                }

            //If moving mouse on the first cell, delete it
            if (connection_from[cur_i].size() == 1)
            {
                connection_from.erase(connection_from.begin() + cur_i);
                connection_to.erase(connection_to.begin() + cur_i);
                full_way.erase(full_way.begin() + cur_i);
                status_of_connection.erase(status_of_connection.begin() + cur_i);
                color_of_way.erase(color_of_way.begin() + cur_i);
            }
            else
            {
                //If size of current way > 1 then delete the last element of connection_from[cur_i]
                connection_from[cur_i].pop_back();

                //Check if current way go over other full way
                for (int i = connection_to.size() - 1; i >= 0; i--)
                {
                    if (i != cur_i)
                    {
                        for (int j = 0; j < connection_to[i].size(); j++)
                        {
                            is_repeated = false;
                            for (int k = 0; k < connection_to[cur_i].size(); k++)
                                if (connection_to[cur_i][k].first == connection_to[i][j].first &&
                                    connection_to[cur_i][k].second == connection_to[i][j].second &&
                                    map.map[connection_to[cur_i][k].first][connection_to[cur_i][k].second] != -2)
                                {
                                    is_repeated = true;
                                    connection_from.erase(connection_from.begin() + i);
                                    connection_to.erase(connection_to.begin() + i);
                                    full_way.erase(full_way.begin() + i);
                                    status_of_connection.erase(status_of_connection.begin() + i);
                                    color_of_way.erase(color_of_way.begin() + i);
                                    if (cur_i > i) cur_i -= 1;
                                    break;
                                }
                            if (is_repeated) break;
                        }
                    }
                }
            }


            cur_i = -1;

            //Check complete condition
            bool complete_checking = true;
            for (int i = 0; i < connection_to.size(); i++)
            {
                if (!full_way[i])
                {
                    complete_checking = false;
                    break;
                }
                for (int j = 0; j < connection_to[i].size() - 1; j++)
                {
                    map.map_with_status[connection_to[i][j].first][connection_to[i][j].second]
                        = status_of_connection[i][j];
                }
            }

            if (complete_checking)
                for (int i = 0; i < map.GetSize(); i++)
                {
                    for (int j = 0; j < map.GetSize(); j++)
                    {
                        if (map.map_with_status[i][j] == 0)
                        {
                            complete_checking = false;
                            break;
                        }
                    }
                }

            if (complete_checking)
            {
                PLAYING_STATUS = COMPLETE;
                cur_i = -1;
                clicked = false;
                connection_from.clear();
                connection_to.clear();
                status_of_connection.clear();
                full_way.clear();
                color_of_way.clear();
                is_repeated = false;
                SDL_Delay(500);
            }
            else
            {
                map.ResetStatusMap();
            }
        }

        else if (e.type == SDL_MOUSEBUTTONUP && !clicked)
        {
            for (int i = 0; i < connection_from.size() && i != cur_i; i++)
            {
                if (!full_way[i])
                {
                    connection_from.erase(connection_from.begin() + i);
                    connection_to.erase(connection_to.begin() + i);
                    full_way.erase(full_way.begin() + i);
                    status_of_connection.erase(status_of_connection.begin() + i);
                    color_of_way.erase(color_of_way.begin() + i);
                    cur_i = -1;
                }
            }
        }
        if (e.type == SDL_MOUSEBUTTONUP)
        {
            clicked = false;
        }
    }
    if (e.type == SDL_MOUSEBUTTONUP && (x < 0 || x > 330 || y < 0 || y > 330) && clicked)
    {
        clicked = false;
        if (connection_from[cur_i].size() > 1)
        {
            connection_from[cur_i].pop_back();
        }

        //Check if current way go over other full way
        for (int i = connection_to.size() - 1; i >= 0; i--)
        {
            if (i != cur_i)
            {
                for (int j = 0; j < connection_to[i].size(); j++)
                {
                    is_repeated = false;
                    for (int k = 0; k < connection_to[cur_i].size(); k++)
                        if (connection_to[cur_i][k].first == connection_to[i][j].first &&
                            connection_to[cur_i][k].second == connection_to[i][j].second &&
                            map.map[connection_to[cur_i][k].first][connection_to[cur_i][k].second] != -2)
                        {
                            is_repeated = true;
                            connection_from.erase(connection_from.begin() + i);
                            connection_to.erase(connection_to.begin() + i);
                            full_way.erase(full_way.begin() + i);
                            status_of_connection.erase(status_of_connection.begin() + i);
                            color_of_way.erase(color_of_way.begin() + i);
                            if (cur_i > i) cur_i -= 1;
                            break;
                        }
                    if (is_repeated) break;
                }
            }
        }

        cur_i = -1;

        //Check complete condition
        bool complete_checking = true;
        for (int i = 0; i < connection_to.size(); i++)
        {
            if (!full_way[i])
            {
                complete_checking = false;
                break;
            }
            for (int j = 0; j < connection_to[i].size() - 1; j++)
            {
                map.map_with_status[connection_to[i][j].first][connection_to[i][j].second]
                    = status_of_connection[i][j];
            }
        }

        if (complete_checking)
            for (int i = 0; i < map.GetSize(); i++)
            {
                for (int j = 0; j < map.GetSize(); j++)
                {
                    if (map.map_with_status[i][j] == 0)
                    {
                        complete_checking = false;
                        break;
                    }
                }
            }

        if (complete_checking)
        {
            PLAYING_STATUS = COMPLETE;
            clicked = false;
            connection_from.clear();
            connection_to.clear();
            status_of_connection.clear();
            full_way.clear();
            color_of_way.clear();
            is_repeated = false;
            SDL_Delay(500);
        }
        else
        {
            map.ResetStatusMap();
        }
    }
}
