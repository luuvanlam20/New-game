#include "bullet.h"

Bullet::Bullet()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	bullet_dir = 0;
	bullet_type = 0;

}

Bullet::~Bullet()
{

}
bool Bullet::loadImgBullet(SDL_Renderer* des)
{
	bool rec = false;
	if(bullet_type==bigger_bullet)
	{
		rec=LoadImg("hinh//bigger_bullet.png", des);
	}
	else if(bullet_type == lazer_bullet)
	{
		rec=LoadImg("hinh//lazer_bullet.png", des);
	}
	else if(bullet_type == bomb_bullet)
	{
		rec=LoadImg("hinh//bomb_bullet.png", des);
	}
	
	return rec;
}
void Bullet::hand_Move(const int& x_bor,const int & y_bor,map& map_data, const int& map_x, const int& map_y)
{
	if (bullet_dir == dir_right)
	{
		vacham(map_data,map_x,map_y);
		if (rect_.x > x_bor)
		{
			is_move = false;
		}


	}
	else if (bullet_dir == dir_left)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.x < 0)
		{
			is_move = false;
		}


	}
	else if (bullet_dir == dir_up)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.y < 0)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == dir_down)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.y > y_bor)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == dir_up_left)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.x < 0)
		{
			is_move = false;
		}

		if (rect_.y < 0)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == dir_up_right)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.x > x_bor)
		{
			is_move = false;
		}
		if (rect_.y < 0)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == dir_down_left)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.x < 0)
		{
			is_move = false;
		}
		if (rect_.y > y_bor)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == dir_down_right)
	{
		vacham(map_data, map_x, map_y);
		if (rect_.x > x_bor)
		{
			is_move = false;
		}
		if (rect_.y > y_bor)
		{
			is_move = false;
		}

	}
}

void Bullet::vacham( map& map_data,const int& map_x,const int& map_y)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int m=0,n=0;

	if (bullet_dir == dir_left || bullet_dir == dir_down_left || bullet_dir == dir_up_left)
	{
		m = -x_val_;
	}
	if (bullet_dir == dir_right || bullet_dir == dir_down_right || bullet_dir == dir_up_right)
	{
		m = x_val_;
	}
	if (bullet_dir == dir_up || bullet_dir == dir_up_left || bullet_dir == dir_up_right)
	{
		n = -y_val_;
	}
	if (bullet_dir == dir_down || bullet_dir == dir_down_left || bullet_dir == dir_down_right)
	{
		n = y_val_;
	}

	int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;

	x1 = (rect_.x + map_x + m) / TILE_SIZE;
	x2 = (rect_.x + map_x + m + rect_.w - 1) / TILE_SIZE;

	y1 = (rect_.y+map_y) / TILE_SIZE;
	y2 = (rect_.y+map_y + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (m > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];


			if (val1 != chotrong && val1 != MONEY_TILE || val2 != chotrong && val2 != MONEY_TILE)
			{
				is_move = false;
			}

		}

		else if (m < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 != chotrong && val1 != MONEY_TILE || val2 != chotrong && val2 != MONEY_TILE)
			{
				is_move = false;
			}


		}
	}
	int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;

	x1 = (rect_.x + map_x) / TILE_SIZE;
	x2 = (rect_.x + map_x + width_min - 1) / TILE_SIZE;

	y1 = (rect_.y + map_y + n) / TILE_SIZE;
	y2 = (rect_.y + map_y + n + rect_.h - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (n > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			
				if (val1 != chotrong && val1 != MONEY_TILE || val2 != chotrong && val2 != MONEY_TILE)
				{
					is_move = false;
				}
			

		}
		else if (n < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 != chotrong && val1 != MONEY_TILE || val2 != chotrong && val2 != MONEY_TILE)
			{
				is_move = false;
			}


		}
	}
	rect_.x += m;
	rect_.y += n;

	
}