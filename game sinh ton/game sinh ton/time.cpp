#include "time.h"


impTime::impTime()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	time_pause = 0;
	rumse_time = 0;
	is_paused_ = false;
	is_started_ = false;

}
impTime::~impTime()
{


}

void impTime::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();

}
void impTime::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void impTime::pause(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case(SDLK_p):
		{
			//time_pause = SDL_GetTicks() - time_pause;
			if (is_started_ == true && is_paused_ == false)
			{
				is_paused_ = true;
				pause_tick_ = SDL_GetTicks() - start_tick_;
			}
		}
		break;
		}
	}
}
void impTime::un_pausel(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case(SDLK_r):
		{
			//rumse_time = SDL_GetTicks();
			if (is_paused_ == true)
			{
				is_paused_ = false;
				start_tick_ = SDL_GetTicks() - pause_tick_;
				time_pause = pause_tick_;
				pause_tick_ = 0;
			}
		}
		break;
		}
	}
	
}
int impTime::get_tick()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return pause_tick_;
		}
		else
			return SDL_GetTicks() - start_tick_;
	}
	return 0;
}
bool impTime::is_started()
{
	return is_started_;
}
bool impTime::is_paused()
{
	return is_paused_;
}
int impTime::TimePass(const int & time_be_for_start)
{	
	int TIMEPASS = 0;
	TIMEPASS = SDL_GetTicks() - time_be_for_start-pause_tick_;
	return TIMEPASS/1000;

}