#ifndef HAM_CHUNG_H_
#define HAM_CHUNG_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_main_sound;

//Screen
const int FRAME_PER_SECOND = 40;
const int SCREEN_WIDTH = 1280;//chieu rong windown
const int SCREEN_HEIGHT = 640;//chieu cao windown
const int SCREEN_BPP = 32;

//Collor

const int COLOR_KEY_R = 167;//ma mau nen nhan vat
const int COLOR_KEY_G = 175;//ma mau nen nhan vat
const int COLOR_KEY_B = 180;//ma mau nen nhan vat


const int RENDER_DRAW_COLOR = 0xff;//mau trang

#define MONEY_TILE 4
#define chotrong 0
#define TILE_SIZE 64//co mat xich ban do
#define MAPMAX_X 400//so mat xich theo X
#define MAPMAX_Y 10//so mat xich theo Y

struct map
{
	int stratX;
	int stratY;

	int max_X;
	int max_Y;
	int tile[MAPMAX_Y][MAPMAX_X];
	const char* file_name;//ten duong dan
};

struct input
{
	int left;
	int right;
	int up;
	int down;
	int jump;
};

namespace SDLCommonFuc
{
	bool checkColisision(const SDL_Rect& obj1, const SDL_Rect& obj2);

	int ShowMenu(SDL_Renderer* screen, TTF_Font* font);

	bool checkFocus(const int& x,const int& y,const SDL_Rect& rect);

	int doHelp(SDL_Renderer* screen, TTF_Font* font);
	bool END(SDL_Renderer* screen, TTF_Font* font,const UINT & mar);
	bool IS_WIN(SDL_Renderer* screen, TTF_Font* font, const UINT& mar);

}



#endif
