#include <iostream>
#include "hinhhoc.h"



void HINH::VE_HCN(const HINH_HOC_FORMAT& HCN_size, const MAU_SAC& mau, SDL_Renderer* screen)
{
	SDL_Rect fill_rect = { HCN_size.left_,HCN_size.top_,HCN_size.width_,HCN_size.height_ };
	SDL_SetRenderDrawColor(screen, mau.red_, mau.green_, mau.blue_, 0xFF);
	SDL_RenderFillRect(screen, &fill_rect);
}

void HINH::VIEN(const HINH_HOC_FORMAT& HCN_size, const MAU_SAC& mau, SDL_Renderer* screen)
{
	SDL_Rect outline = { HCN_size.left_,HCN_size.top_,HCN_size.width_,HCN_size.height_ };
	SDL_SetRenderDrawColor(screen, mau.red_, mau.green_, mau.blue_, 0xFF);
	SDL_RenderDrawRect(screen, &outline);
}