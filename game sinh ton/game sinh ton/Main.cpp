#include <iostream>
#include "Hamchung.h"
#include "Hamcoso.h"
#include "bando.h"
#include "NVchinh.h"
#include "Enemy.h"
#include "time.h"
#include "explo.h"
#include "TextObject.h"
#include "playerPower.h"
#include "hinhhoc.h"

Hamcoso g_background;

TTF_Font* font_time=NULL;
TTF_Font* menu_font = NULL;
// tao windown
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("GAME SINH TON", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int ImgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(ImgFlags) && ImgFlags))
        {
            success = false;
        }
        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        menu_font = TTF_OpenFont("font//dlxfont_.ttf", 25);
        if (font_time == NULL)
        {
            success = false;
        }
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
        g_sound_bullet[0] = Mix_LoadWAV("sound//Laser.wav");
        g_sound_bullet[1] = Mix_LoadWAV("sound//Fire1.wav");
        g_sound_exp[0] = Mix_LoadWAV("sound//Explosion+1.wav");
        g_sound_exp[1] = Mix_LoadWAV("sound//Bomb1.wav");
        g_main_sound = Mix_LoadWAV("sound//Heroes-Tonight-Janji_-Johnning-_128kbps_MP3_.wav");
        if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0]==NULL|| g_sound_exp[1]==NULL)
        {
            success = false;
        }
    }
    return success;
}
//load anh nen
bool LoadBackGround()
{
    bool ret = g_background.LoadImg("hinh//thac.png", g_screen);
    if (ret == false)
        return false;
    return true;
}
//dong ctrinhk
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}
std::vector<Enemy*> MakeEnemyList()
{
    std::vector<Enemy*> enemy_list;

    Enemy* enemy_obj_move = new Enemy[55];
    for (int i = 0; i < 55; i++)
    {
        Enemy* p_enemy = (enemy_obj_move + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("hinh//threat_left.png", g_screen);
            p_enemy->set_clip();
            p_enemy->set_type_move(Enemy::move_in_space);
            p_enemy->set_x_pos(500 + i * 350);
            p_enemy->set_y_pos(200);

            int pos1 = p_enemy->get_x_pos() - 60;
            int pos2 = p_enemy->get_x_pos() + 60;

            p_enemy->set_enemy_pos(pos1, pos2);

            p_enemy->set_input_left(1);
           
            enemy_list.push_back(p_enemy);

        }
    }

    Enemy* enemy_obj = new Enemy[55];
    for (int i = 0; i < 55; i++)
    {
        Enemy* p_enemy = (enemy_obj + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("hinh//threat_level.png", g_screen);
            p_enemy->set_clip();
            p_enemy->set_x_pos(750+i*500);
            p_enemy->set_y_pos(250);
            p_enemy->set_type_move(Enemy::static_enemy);

            
            Bullet* p_bullet = new Bullet();

            p_enemy->InitBullet(p_bullet, g_screen);
            
                                  
            enemy_list.push_back(p_enemy);

        }
    }
    return enemy_list;
}
int main(int argc, char* argv[])
{
    impTime fps_times;


    if (InitData() == false)
        return -1;
    if (LoadBackGround() == false)
        return -1;

    int ret_menu = SDLCommonFuc::ShowMenu(g_screen, menu_font);

    bool is_quit = false;
    while (ret_menu == 1)
    {
        if (ret_menu == 1)
        {
            ret_menu = SDLCommonFuc::doHelp(g_screen, menu_font);

        }
    }
    

    if (ret_menu == 2)
    {
        is_quit = true;

        close();
        return 0;
    }
    

    Mix_PlayChannel(-1, g_main_sound, 2);
    //map
    bando game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTile(g_screen);

    //nhan vat
    NVchinh player;

    player.LoadImg("hinh//player_right.png", g_screen);
    player.SETNVchinh_clip();

    PlayerPower player_power;
    player_power.init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(170, 8);

    std::vector<Enemy*> enemy_list = MakeEnemyList();

    EXPLO exp_enemy;
    bool tRet = exp_enemy.LoadImg("hinh//exp3.png", g_screen);
    if (!tRet) 
    {
        return -1;
    }
    exp_enemy.set_clip();
    EXPLO exp_main;
    bool mRet = exp_main.LoadImg("hinh//exp3.png", g_screen);
    if (!mRet)
    {
        return -1;
    }
    exp_main.set_clip();


    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mar_val = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    int time_be_for_start = SDL_GetTicks();

    while (!is_quit)
    {
        if (ret_menu == 0 && fps_times.is_paused() == false)
        {
            fps_times.start();
        }
        
        //nhan vao khi nhap
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            fps_times.un_pausel(g_event);
            fps_times.pause(g_event);
            player.HandInputAction(g_event, g_screen, g_sound_bullet);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        if (fps_times.is_paused() == false)
        {
            //anh nen
            g_background.Render(g_screen, NULL);

            //map
            map map_data = game_map.getMap();


            game_map.DrawMap(g_screen);
            //nhan vat

            player.SetMapXY(map_data.stratX, map_data.stratY);
            player.HandleBullet(g_screen, map_data);
            player.dichuyen(map_data);
            player.show(g_screen);

            //map
            game_map.SetMap(map_data);

            //ve khung
            HINH_HOC_FORMAT HCN(0, 0, SCREEN_WIDTH, 50);
            MAU_SAC mau(71, 44, 107);
            HINH::VE_HCN(HCN, mau, g_screen);

            HINH_HOC_FORMAT vien(1, 1, SCREEN_WIDTH - 1, 48);
            MAU_SAC mauvien(245, 245, 31);
            HINH::VIEN(vien, mauvien, g_screen);
            //show power

            player_power.show(g_screen);
            player_money.show(g_screen);


            for (int i = 0; i < enemy_list.size(); i++)
            {
                Enemy* p_enemy = enemy_list.at(i);
                if (p_enemy != NULL)
                {                 
                    if (p_enemy->GetisDead())
                    {
                        p_enemy->Free();
                        enemy_list.erase(enemy_list.begin() + i);
                    }
                    p_enemy->SetMapXY(map_data.stratX, map_data.stratY);
                    p_enemy->ImgMoveType(g_screen);
                    p_enemy->doEnemy(map_data);
                    p_enemy->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, map_data);
                    p_enemy->show(g_screen);

                    SDL_Rect rect_player = player.GetRectFrame();
                    bool bCol1 = false;
                    std::vector<Bullet*> tbullet = p_enemy->get_bullet_list();

                    for (int k = 0; k < tbullet.size(); k++)
                    {
                        Bullet* enemy_bullet = tbullet.at(k);

                        if (enemy_bullet)
                        {
                            bCol1 = SDLCommonFuc::checkColisision(enemy_bullet->GetRect(), rect_player);

                            if (bCol1)
                            {
                                enemy_bullet->set_is_move(false);                               
                                break;
                            }
                        }
                    }

                    SDL_Rect rect_enemy = p_enemy->GetRectFrame();
                    bool bCol2;
                    bCol2 = SDLCommonFuc::checkColisision(rect_player, rect_enemy);

                    if (bCol1 || bCol2)
                    {
                        for (int ex = 0; ex < Num_EX_frame; ex++)
                        {
                            int frame_exp_width = exp_main.get_frame_width();
                            int frame_exp_height = exp_main.get_frame_height();
                            int x_pos = (player.GetRect().x + player.GetRectFrame().w) - frame_exp_width * 0.5;
                            int y_pos = (player.GetRect().y + player.GetRectFrame().h) - frame_exp_height * 0.5;
                            Mix_PlayChannel(-1, g_sound_exp[1], 0);
                            exp_main.set_frame(ex);
                            exp_main.SetRect(x_pos, y_pos);
                            exp_main.show(g_screen);
                            SDL_RenderPresent(g_screen);

                        }

                        player.Lives_decre();
                        if (player.Get_lives_left() > 0)
                        {
                            player.SetRect(0, 0);
                            player.set_time_back(20);
                            SDL_Delay(1000);
                            player_power.SetLives(player.Get_lives_left());
                            player_power.decrease();                           
                            continue;
                        }
                        else
                        {
                            g_background.Free();
                            player.Free();
                            enemy_list.clear();
                            mark_game.Free();
                            time_game.Free();
                            player_power.Free();
                            player_money.Free();
                            exp_enemy.Free();
                            exp_main.Free();
                            bool end = SDLCommonFuc::END(g_screen, menu_font, mar_val);
                            if (end)
                            {
                                player.Free();
                                close();
                                SDL_Quit();
                                return 0;
                            }
                        }

                    }
                    player_power.SetLives(player.Get_lives_left());
                    player_power.decrease();
                    if (player.Get_lives_left() <= 0)
                    {
                        g_background.Free();
                        player.Free();
                        enemy_list.clear();
                        mark_game.Free();
                        time_game.Free();
                        player_power.Free();
                        player_money.Free();
                        exp_enemy.Free();
                        exp_main.Free();
                        bool end = SDLCommonFuc::END(g_screen, menu_font, mar_val);
                        if (end)
                        {
                            player.Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }


                }
            }

            int frame_exp_width = exp_enemy.get_frame_width();
            int frame_exp_height = exp_enemy.get_frame_height();

            std::vector<Bullet*> bullet_arr = player.get_bullet_list();
            for (int bl = 0; bl < bullet_arr.size(); bl++)
            {
                Bullet* p_bullet = bullet_arr.at(bl);
                if (p_bullet != NULL)
                {
                    for (int t = 0; t < enemy_list.size(); t++)
                    {
                        Enemy* obj_enemy = enemy_list.at(t);
                        if (obj_enemy != NULL)
                        {
                            SDL_Rect tRect = obj_enemy->GetRectFrame();
                            SDL_Rect bRect;
                            bRect = p_bullet->GetRect();

                            bool bCol = SDLCommonFuc::checkColisision(bRect, tRect);

                            if (bCol)
                            {
                                mar_val += 10;
                                for (int ex = 0; ex < Num_EX_frame; ex++)
                                {
                                    int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                    int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
                                    exp_enemy.set_frame(ex);
                                    exp_enemy.SetRect(x_pos, y_pos);
                                    exp_enemy.show(g_screen);

                                }
                                p_bullet->set_is_move(false);
                                Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                obj_enemy->Free();
                                enemy_list.erase(enemy_list.begin() + t);
                            }

                        }
                    }
                }
            }

            //show game time

            std::string str_time = "Time: ";
            Uint32 time_val_ = fps_times.TimePass(time_be_for_start);
            Uint32 val_time = 600 - time_val_;

            if (val_time <= 0)
            {
                g_background.Free();
                player.Free();
                enemy_list.clear();
                mark_game.Free();
                time_game.Free();
                player_power.Free();
                player_money.Free();
                exp_enemy.Free();
                exp_main.Free();
                bool end = SDLCommonFuc::END(g_screen, menu_font, mar_val);
                if (end)
                {
                    player.Free();
                    close();
                    SDL_Quit();
                    return 0;
                }
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);
                time_game.LoadFromRenderText(font_time, g_screen);
                time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
            }

            std::string val_mark = std::to_string(mar_val);
            std::string str_mark = "Mark: ";
            str_mark += val_mark;
            mark_game.SetText(str_mark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 100, 15);

            int money_count = player.GetMoney();
            std::string val_money = std::to_string(money_count);

            mark_game.SetText(val_money);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, 200, 15);

            if (player.WIN() == true)
            {
                g_background.Free();
                player.Free();
                enemy_list.clear();
                mark_game.Free();
                time_game.Free();
                player_power.Free();
                player_money.Free();
                exp_enemy.Free();
                exp_main.Free();
                bool win = SDLCommonFuc::IS_WIN(g_screen, menu_font, mar_val);
                if (win)
                {
                    player.Free();
                    close();
                    SDL_Quit();
                    return 0;
                }
            }
        
            SDL_RenderPresent(g_screen);
        }
        //delay
        int real_impTime = fps_times.get_tick();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_impTime < time_one_frame)
        {
            int delay_time = time_one_frame - real_impTime;
            if(delay_time>=0)
                SDL_Delay(delay_time);
                
        }
    }
    for (int i = 0; i < enemy_list.size(); i++)
    {
        Enemy* p_enemy = enemy_list.at(i);
        if (p_enemy)
        {
            p_enemy->Free();
            p_enemy = NULL;
        }
    }
    g_background.Free();
    player.Free();
    enemy_list.clear();
    mark_game.Free();
    time_game.Free();
    player_power.Free();
    player_money.Free();
    exp_enemy.Free();
    exp_main.Free();
    close();
    return 0;
}
