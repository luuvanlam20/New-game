#include <iostream>
#include "Hamchung.h"
#include "TextObject.h"
#include "Hamcoso.h"


bool SDLCommonFuc::checkFocus(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

int SDLCommonFuc::ShowMenu(SDL_Renderer* screen, TTF_Font* font)
{
    Hamcoso g_menu;
    bool ret = g_menu.LoadImg("hinh//menu1.png", screen);
    if (ret == false)
    {
        return 2;
    }

    g_menu.Render(screen, NULL);
    
    

    const int kMenuItemNum = 3;
    SDL_Rect selec[3];
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 300;
    pos_arr[0].y = 300;
    

    pos_arr[1].x = 300;
    pos_arr[1].y = 350;

    pos_arr[2].x = 300;
    pos_arr[2].y = 400;
    

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("PLAY GAME");
    text_menu[0].SetColor(TextObject::RED_TEXT);
    text_menu[0].LoadFromRenderText(font, screen);

    text_menu[1].SetText("HELP");
    text_menu[1].SetColor(TextObject::RED_TEXT);
    text_menu[1].LoadFromRenderText(font, screen);

    text_menu[2].SetText("EXIT");
    text_menu[2].SetColor(TextObject::RED_TEXT);
    text_menu[2].LoadFromRenderText(font, screen);

    selec[0] = { pos_arr[0].x ,pos_arr[0].y,text_menu[0].Getwidth(),text_menu[0].Getheight() };
    selec[1] = { pos_arr[1].x ,pos_arr[1].y,text_menu[1].Getwidth(),text_menu[1].Getheight() };
    selec[2] = { pos_arr[2].x ,pos_arr[2].y,text_menu[2].Getwidth(),text_menu[2].Getheight() };

    
    int xm = 0, ym = 0;
    bool selected[3];
    for (int i = 0; i < 3; i++)
    {
        selected[i] = false;
    }
    SDL_Event m_evevt;

    while (true)
    {
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].RenderText(screen, selec[i].x, selec[i].y);
            
        }
        while (SDL_PollEvent(&m_evevt))
        {
            switch (m_evevt.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
            {
                xm = m_evevt.motion.x;
                ym = m_evevt.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (checkFocus(xm, ym, selec[i]))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = true;
                            text_menu[i].SetColor(TextObject::YELLOW_TEXT);
                            text_menu[i].LoadFromRenderText(font, screen);
                        }
                    }
                    else
                    {
                        //if (checkFocus(xm, ym, selec[i]))
                        //{
                            if (selected[i] == true)
                            {
                                selected[i] = false;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                                text_menu[i].LoadFromRenderText(font, screen);
                            }
                        //}
                    }

                    SDL_RenderPresent(screen);
                }
                

            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_evevt.button.x;
                ym = m_evevt.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (checkFocus(xm, ym, selec[i]))
                    {
                            g_menu.Free();
                            for (int i = 0; i < kMenuItemNum; i++)
                            {
                                text_menu[i].Free();
                            }
                            return i;
                    }
                }

            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_evevt.key.keysym.sym == SDLK_ESCAPE)
                    return 2;
            }
            break;
            default:
                break;
            }
        }
    }
    
    return 2;
}

int SDLCommonFuc::doHelp(SDL_Renderer* screen, TTF_Font* font)
{
    Hamcoso g_help;
    bool ret = g_help.LoadImg("hinh//help.png", screen);
    if (ret == false)
    {
        return ShowMenu(screen, font);
    }

    g_help.Render(screen, NULL);

    SDL_Rect help_poss;

    TextObject help_text;

    help_text.SetText("EXIT");
    help_text.SetColor(TextObject::RED_TEXT);
    help_text.LoadFromRenderText(font, screen);

    help_poss = { (SCREEN_WIDTH - help_text.Getwidth()) / 2,SCREEN_HEIGHT - help_text.Getheight(),help_text.Getwidth(),help_text.Getheight() };

    int xm = 0, ym = 0;
    bool selected_help;
   // for (int i = 0; i < 3; i++)
    //{
    selected_help = false;
   // }
    SDL_Event help_evevt;

    while (true)
    {
        help_text.RenderText(screen, help_poss.x, help_poss.y);

        while (SDL_PollEvent(&help_evevt))
        {
            switch (help_evevt.type)
            {
            case SDL_QUIT:
                return ShowMenu(screen, font);
            case SDL_MOUSEMOTION:
            {
                xm = help_evevt.motion.x;
                ym = help_evevt.motion.y;

               
                    if (checkFocus(xm, ym, help_poss))
                    {
                        if (selected_help == false)
                        {
                            selected_help = true;
                            help_text.SetColor(TextObject::YELLOW_TEXT);
                            help_text.LoadFromRenderText(font, screen);
                        }
                    }
                    else
                    {                    
                        if (selected_help == true)
                        {
                            selected_help = false;
                            help_text.SetColor(TextObject::RED_TEXT);
                            help_text.LoadFromRenderText(font, screen);
                        }
                    }

                    SDL_RenderPresent(screen);
            


            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = help_evevt.button.x;
                ym = help_evevt.button.y;
                
                    if (checkFocus(xm, ym, help_poss))
                    {

                            g_help.Free();
                            help_text.Free();
                            return ShowMenu(screen,font);
                    }
               

            }
            break;
            case SDL_KEYDOWN:
            {
                if (help_evevt.key.keysym.sym == SDLK_ESCAPE)
                    return ShowMenu(screen, font);
            }
            break;
            default:
                break;
            }
        }
    }

    return ShowMenu(screen, font);

}

bool SDLCommonFuc::END(SDL_Renderer* screen, TTF_Font* font, const UINT& mar)
{
    Hamcoso g_end;
    bool ret = g_end.LoadImg("hinh//menu2.png", screen);
    if (ret == false)
    {
        return ret;
    }

    g_end.Render(screen, NULL);

    SDL_Rect end_poss[2];

    TextObject END_text[2];


    std::string val_mark = std::to_string(mar);
    std::string str_mark = "Mark: ";
    str_mark += val_mark;
    END_text[0].SetText(str_mark);
    END_text[0].SetColor(TextObject::RED_TEXT);
    END_text[0].LoadFromRenderText(font, screen);

    END_text[1].SetText("EXIT");
    END_text[1].SetColor(TextObject::RED_TEXT);
    END_text[1].LoadFromRenderText(font, screen);

    end_poss[0] = { (SCREEN_WIDTH - END_text[0].Getwidth()) / 2,(SCREEN_HEIGHT - END_text[0].Getheight())/2,END_text[0].Getwidth(),END_text[0].Getheight() };
    end_poss[1] = { (SCREEN_WIDTH - END_text[1].Getwidth()) / 2,SCREEN_HEIGHT - END_text[1].Getheight(),END_text[1].Getwidth(),END_text[1].Getheight() };


    int xm = 0, ym = 0;
    bool selected_help;
    // for (int i = 0; i < 3; i++)
     //{
    selected_help = false;
    // }
    SDL_Event end_evevt;

    while (true)
    {
        for (int i = 0; i < 2; i++)
        {
            END_text[i].RenderText(screen, end_poss[i].x, end_poss[i].y);

        }

        while (SDL_PollEvent(&end_evevt))
        {
            switch (end_evevt.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = end_evevt.motion.x;
                ym = end_evevt.motion.y;


                if (checkFocus(xm, ym, end_poss[1]))
                {
                    if (selected_help == false)
                    {
                        selected_help = true;
                        END_text[1].SetColor(TextObject::YELLOW_TEXT);
                        END_text[1].LoadFromRenderText(font, screen);
                    }
                }
                else
                {
                    //if (checkFocus(xm, ym, selec[i]))
                    //{
                    if (selected_help == true)
                    {
                        selected_help = false;
                        END_text[1].SetColor(TextObject::RED_TEXT);
                        END_text[1].LoadFromRenderText(font, screen);
                    }
                    //}
                }

                SDL_RenderPresent(screen);



            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = end_evevt.button.x;
                ym = end_evevt.button.y;

                if (checkFocus(xm, ym, end_poss[1]))
                {

                    g_end.Free();
                    for (int i = 0; i < 2; i++)
                    {
                        END_text[i].Free();
                    }
                    
                    return true;
                }


            }
            break;
            case SDL_KEYDOWN:
            {
                if (end_evevt.key.keysym.sym == SDLK_ESCAPE)
                    return true;
            }
            break;
            default:
                break;
            }
        }
    }

    return true;
}

bool SDLCommonFuc::IS_WIN(SDL_Renderer* screen, TTF_Font* font, const UINT& mar)
{
    Hamcoso g_win;
    bool ret = g_win.LoadImg("hinh//menu3.png", screen);
    if (ret == false)
    {
        return ret;
    }

    g_win.Render(screen, NULL);

    SDL_Rect win_poss[2];

    TextObject WIN_text[2];


    std::string val_mark = std::to_string(mar);
    std::string str_mark = "Mark: ";
    str_mark += val_mark;
    WIN_text[0].SetText(str_mark);
    WIN_text[0].SetColor(TextObject::YELLOW_TEXT);
    WIN_text[0].LoadFromRenderText(font, screen);

    WIN_text[1].SetText("EXIT");
    WIN_text[1].SetColor(TextObject::RED_TEXT);
    WIN_text[1].LoadFromRenderText(font, screen);

    win_poss[0] = { (SCREEN_WIDTH - WIN_text[0].Getwidth()) / 2,(SCREEN_HEIGHT - WIN_text[0].Getheight()) / 2,WIN_text[0].Getwidth(),WIN_text[0].Getheight() };
    win_poss[1] = { (SCREEN_WIDTH - WIN_text[1].Getwidth()) / 2,SCREEN_HEIGHT - WIN_text[1].Getheight(),WIN_text[1].Getwidth(),WIN_text[1].Getheight() };


    int xm = 0, ym = 0;
    bool selected_win;
    selected_win = false;
    SDL_Event win_evevt;

    while (true)
    {
        for (int i = 0; i < 2; i++)
        {
            WIN_text[i].RenderText(screen, win_poss[i].x, win_poss[i].y);

        }

        while (SDL_PollEvent(&win_evevt))
        {
            switch (win_evevt.type)
            {
            case SDL_QUIT:
                return true;
            case SDL_MOUSEMOTION:
            {
                xm = win_evevt.motion.x;
                ym = win_evevt.motion.y;


                if (checkFocus(xm, ym, win_poss[1]))
                {
                    if (selected_win == false)
                    {
                        selected_win = true;
                        WIN_text[1].SetColor(TextObject::YELLOW_TEXT);
                        WIN_text[1].LoadFromRenderText(font, screen);
                    }
                }
                else
                {                   
                    if (selected_win == true)
                    {
                        selected_win = false;
                        WIN_text[1].SetColor(TextObject::RED_TEXT);
                        WIN_text[1].LoadFromRenderText(font, screen);
                    }
                }

                SDL_RenderPresent(screen);



            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = win_evevt.button.x;
                ym = win_evevt.button.y;

                if (checkFocus(xm, ym, win_poss[1]))
                {

                    g_win.Free();
                    for (int i = 0; i < 2; i++)
                    {
                        WIN_text[i].Free();
                    }
                    return true;

                }


            }
            break;
            case SDL_KEYDOWN:
            {
                if (win_evevt.key.keysym.sym == SDLK_ESCAPE)
                    return true;
            }
            break;
            default:
                break;
            }
        }
    }

    return true;
}
//muon tu wed phattrienphanmem123az
bool SDLCommonFuc::checkColisision(const SDL_Rect& obj1, const SDL_Rect& obj2)
{
    int left_a = obj1.x;
    int right_a = obj1.x + obj1.w;
    int top_a = obj1.y;
    int bottom_a = obj1.y + obj1.h;

    int left_b = obj2.x;
    int right_b = obj2.x + obj2.w;
    int top_b = obj2.y;
    int bottom_b = obj2.y + obj2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}