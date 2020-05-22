#include <iostream>
#include"playerPower.h"


PlayerPower::PlayerPower()
{
	number_ = 0;
	lives_left = 0;
}
PlayerPower::~PlayerPower()
{

}

void PlayerPower::Addpos(const int& pos)
{
	post_list_.push_back(pos);
}


void PlayerPower::init(SDL_Renderer* screen) 
{
	bool rett = LoadImg("hinh//player_pw.png", screen);
	number_ = 3;
	if (post_list_.size())
	{
		post_list_.clear();
	}
	Addpos(20);
	Addpos(60);
	Addpos(100);
}

void PlayerPower::show(SDL_Renderer* screen)
{
	for (int i = 0; i < post_list_.size(); i++)
	{
		rect_.x = post_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void PlayerPower::decrease()
{
	if (number_ > lives_left)
	{
		number_--;
		post_list_.pop_back();
	}
	
}
void PlayerPower::initcreas()
{
	if (lives_left < number_)
	{
		number_++;
		int last_pos = post_list_.back();
		last_pos += 40;
		post_list_.push_back(last_pos);
	}
	
}

PlayerMoney::PlayerMoney()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
PlayerMoney::~PlayerMoney()
{

}

void PlayerMoney::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("hinh//money_img.png", screen);
}


void PlayerMoney::show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}