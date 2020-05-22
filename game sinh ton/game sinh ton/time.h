#ifndef TIME_H_
#define TIME_H_

#include "Hamchung.h"

class impTime
{
public:
	impTime() ;
	~impTime() ;
	void start();
	void stop();
	void pause(SDL_Event event);
	void un_pausel(SDL_Event event);
	int get_tick();
	bool is_started();
	bool is_paused();
	int TimePass(const int & time_be_for_start);

private:
	int start_tick_;
	int pause_tick_;
	int time_pause;
	int rumse_time;

	bool is_paused_;
	bool is_started_;
};



#endif
