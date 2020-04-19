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
    bool ret = g_menu.LoadImg("hinh//menu.png", screen);
    if (ret == false)
    {
        return 1;
    }

    g_menu.Render(screen, NULL);
    
    

    const int kMenuItemNum = 2;
    SDL_Rect selec[2];
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 300;
    selec[0] = { pos_arr[0].x ,pos_arr[0].y,150,30 };

    pos_arr[1].x = 200;
    pos_arr[1].y = 400;
    selec[1] = { pos_arr[1].x ,pos_arr[1].y,80,30 };

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::RED_TEXT);
    text_menu[0].LoadFromRenderText(font, screen);

    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject::RED_TEXT);
    text_menu[1].LoadFromRenderText(font, screen);

    
    int xm = 0, ym = 0;
    bool selected[2];
    for (int i = 0; i < 2; i++)
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
                return 1;
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
                            text_menu[i].SetColor(TextObject::BLACK_TEXT);
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
                        return i;
                    }
                }

            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_evevt.key.keysym.sym == SDLK_ESCAPE)
                    return 1;
            }
            break;
            default:
                break;
            }
        }
    }
    
    return 1;
}



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