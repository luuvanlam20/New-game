#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include <iostream>
#include "Hamchung.h"
#include "Hamcoso.h"



class PlayerPower : public Hamcoso

{
public:
	PlayerPower();
	~PlayerPower();


	void Setnum(const int& num) { number_ = num; }
	void SetLives(const int& lives) { lives_left = lives; }
	void Addpos(const int& pos);
	void show(SDL_Renderer* screen);
	void init(SDL_Renderer* screen);


	void initcreas();
	void decrease();


private:
	int number_;
	int lives_left;
	std::vector<int> post_list_;
};

class PlayerMoney :public Hamcoso
{
public:
	PlayerMoney();
	~PlayerMoney();

	void Init(SDL_Renderer* screen);
	void show(SDL_Renderer* screen);
	void SetPos(const int& xp, const int& yp) { x_pos_ = xp; y_pos_ = yp; }

private:
	int x_pos_;
	int y_pos_;
};



#endif // !PLAYER_POWER_H_

