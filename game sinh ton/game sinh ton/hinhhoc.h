#ifndef HINH_HOC_H_
#define HINH_HOC_H_

#include <iostream>
#include "Hamchung.h"


typedef struct HINH_HOC_FORMAT
{
public:
	HINH_HOC_FORMAT(int left, int top, int width, int height)
	{
		left_ = left;
		top_ = top;
		width_ = width;
		height_ = height;
	};


	int left_;
	int top_;
	int width_;
	int height_;

};


typedef struct MAU_SAC
{
	MAU_SAC(Uint8 r, Uint8 g, Uint8 b) 
	{
		red_ = r;
		green_ = g;
		blue_ = b;
	}

public:
	Uint8 red_;
	Uint8 green_;
	Uint8 blue_;


};

class HINH
{
public:
	static void VE_HCN(const HINH_HOC_FORMAT& HCN_size, const MAU_SAC& mau, SDL_Renderer* screen);
	static void VIEN(const HINH_HOC_FORMAT& HCN_size, const MAU_SAC& mau, SDL_Renderer* screen);
};


#endif // !HINH_HOC_H_

