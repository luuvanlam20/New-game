#include "NVchinh.h"
#define tocdoroi 1
#define tocdomax 10
#define tocdochay 10
#define lucnhay 19

bool NVchinh::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = Hamcoso::LoadImg(path, screen);
	if (ret == true)
	{
		width_pic = rect_.w / 8;
		height_pic = rect_.h;

	}
	return ret;
}

SDL_Rect NVchinh::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_pic;
	rect.h = height_pic;

	return rect;
}

void NVchinh::SETNVchinh_clip()
{
	if (width_pic > 0 && height_pic > 0)
	{
		pic_clip[0].x = 0;
		pic_clip[0].y = 0;
		pic_clip[0].w = width_pic;
		pic_clip[0].h = height_pic;

		pic_clip[1].x = width_pic;
		pic_clip[1].y = 0;
		pic_clip[1].w = width_pic;
		pic_clip[1].h = height_pic;

		pic_clip[2].x = 2 * width_pic;
		pic_clip[2].y = 0;
		pic_clip[2].w = width_pic;
		pic_clip[2].h = height_pic;

		pic_clip[3].x = 3 * width_pic;
		pic_clip[3].y = 0;
		pic_clip[3].w = width_pic;
		pic_clip[3].h = height_pic;

		pic_clip[4].x = 4 * width_pic;
		pic_clip[4].y = 0;
		pic_clip[4].w = width_pic;
		pic_clip[4].h = height_pic;

		pic_clip[5].x = 5 * width_pic;
		pic_clip[5].y = 0;
		pic_clip[5].w = width_pic;
		pic_clip[5].h = height_pic;

		pic_clip[6].x = 6 * width_pic;
		pic_clip[6].y = 0;
		pic_clip[6].w = width_pic;
		pic_clip[6].h = height_pic;

		pic_clip[7].x = 7 * width_pic;
		pic_clip[7].y = 0;
		pic_clip[7].w = width_pic;
		pic_clip[7].h = height_pic;
	}
}
void NVchinh::show(SDL_Renderer* des)
{
	updateImg(des);
	
	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else frame = 0;
	if (frame == 8)
	{
		frame = 0;
	}
	if (time_back == 0) 
	{
		rect_.x = x_pos - map_x_;
		rect_.y = y_pos - map_y_;
		SDL_Rect* clipHT = &pic_clip[frame];
		SDL_Rect rederquad = { rect_.x,rect_.y,width_pic,height_pic };
		SDL_RenderCopy(des, p_object_, clipHT, &rederquad);//render 1 phan hinh anh cua p_obj theo vi tris da cho
	}
}
void NVchinh::HandInputAction(SDL_Event event, SDL_Renderer* screen,Mix_Chunk* bullet_sound[2])
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case(SDLK_RIGHT):
		{
			status = RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			updateImg(screen);
		}
		break;
		case(SDLK_LEFT):
		{
			status = LEFT;
			input_type.left = 1;
			input_type.right = 0;
			updateImg(screen);
		}
		break;
		
		case(SDLK_UP):
		{
			input_type.up = 1;
		}
		break;
		case(SDLK_DOWN):
		{
			input_type.down = 1;
		}
		break;
		case(SDLK_1):
		{
			
			if (bullet_type == 1)
			{
				bullet_type = 2;
			}
			
		}
		break;
		case(SDLK_2):
		{
			if (bullet_type == 2)
			{
				bullet_type = 1;
			}
			
		}
		break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case(SDLK_RIGHT):
		{
			input_type.right = 0;
			

		}
		break;
		case(SDLK_LEFT):
		{
			input_type.left = 0;
			

		}
		break;
		case(SDLK_UP):
		{
			input_type.up = 0;
		}
		break;
		case(SDLK_DOWN):
		{
			input_type.down = 0;
		}
		break;
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			Bullet* p_bullet = new Bullet();
			if (bullet_type == 1) 
			{
				p_bullet->set_bullet_type(Bullet::lazer_bullet);
			}
			if (bullet_type == 2)
			{
				p_bullet->set_bullet_type(Bullet::bigger_bullet);
			}
			p_bullet->loadImgBullet(screen);

			if (status == LEFT)
			{
				if (input_type.up == 0 && input_type.down == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_left);
					p_bullet->SetRect(this->rect_.x, rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 1 && input_type.down == 0 && input_type.left == 1)
				{
					p_bullet->set_bullet_dir(Bullet::dir_up_left);
					p_bullet->SetRect(this->rect_.x, rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 0 && input_type.down == 1 && input_type.left == 1)
				{
					p_bullet->set_bullet_dir(Bullet::dir_down_left);
					p_bullet->SetRect(this->rect_.x, rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 1 && input_type.down == 0 && input_type.left == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_up);
					p_bullet->SetRect(this->rect_.x, rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 0 && input_type.down == 1 && input_type.left == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_down);
					p_bullet->SetRect(this->rect_.x, rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				
			}
			else
			{
				if (input_type.up == 0 && input_type.down == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_right);
					p_bullet->SetRect(this->rect_.x  + width_pic - 20, this->rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 1 && input_type.down == 0 && input_type.right == 1)
				{
					p_bullet->set_bullet_dir(Bullet::dir_up_right);
					p_bullet->SetRect(this->rect_.x + width_pic - 20, this->rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 0 && input_type.down == 1 && input_type.right == 1)
				{
					p_bullet->set_bullet_dir(Bullet::dir_down_right);
					p_bullet->SetRect(this->rect_.x + width_pic - 20, this->rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 1 && input_type.down == 0 && input_type.right == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_up);
					p_bullet->SetRect(this->rect_.x + width_pic - 20, this->rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
				else if (input_type.up == 0 && input_type.down == 1 && input_type.right == 0)
				{
					p_bullet->set_bullet_dir(Bullet::dir_down);
					p_bullet->SetRect(this->rect_.x + width_pic - 20, this->rect_.y + (height_pic) * 0.25);
					Mix_PlayChannel(-1, bullet_sound[0], 0);
				}
			}

			

			p_bullet->set_x_val(30);
			p_bullet->set_y_val(30);
			p_bullet->set_is_move(true);

			p_bullet_list_.push_back(p_bullet);
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			input_type.jump = 1;
		}
	}
}

void NVchinh::HandleBullet(SDL_Renderer* des,map& map_data)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		Bullet* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->hand_Move(SCREEN_WIDTH, SCREEN_HEIGHT,map_data,map_x_,map_y_);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if (p_bullet != NULL) 
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}

	}
}

void NVchinh::dichuyen(map& map_data)
{
	if(time_back == 0){
		x_val = 0;
		y_val += tocdoroi;
		if (y_val >= tocdomax)
		{
			y_val = tocdomax;
		}
		if (input_type.left == 1)
		{
			x_val -= tocdochay;
		}
		if (input_type.right == 1)
		{
			x_val += tocdochay;
		}
		if (input_type.jump == 1)
		{
			if (on_groud==true)
			{
				y_val = -lucnhay;
				on_groud = false;
			}
		
			input_type.jump = 0;
		}
		vacham(map_data);
		centerMap(map_data);
	}
	else
	{
		time_back--;
		if (time_back == 0)
		{
			x_pos = x_pos-400;	
			y_pos = 0;
			x_val = 0;
			y_val = 0;
		}
		
	}
}

void NVchinh::centerMap(map& map_data)
{
	map_data.stratX = x_pos - (SCREEN_WIDTH/ 2);
	if (map_data.stratX < 0)
	{
		map_data.stratX = 0;
	}
	else if (map_data.stratX + SCREEN_WIDTH >= map_data.max_X)
	{
		map_data.stratX = map_data.max_X - SCREEN_WIDTH;
	}
	map_data.stratY = y_pos - SCREEN_HEIGHT / 2;
	if (map_data.stratY < 0)
	{
		map_data.stratY = 0;
	}
	else if (map_data.stratY + SCREEN_HEIGHT >= map_data.max_Y)
	{
		map_data.stratY = map_data.max_Y - SCREEN_HEIGHT;
	}
}

void NVchinh::vacham(map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	
	//kt chieu cao
	int height_min = height_pic < TILE_SIZE ? height_pic : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_pic - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (x_val > 0)//di chuyen sang ngang
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == MONEY_TILE || val2 == MONEY_TILE)
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				ThemTien();
			}
			else
			{
				if (val1 != chotrong || val2 != chotrong)
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= (width_pic + 1);
					x_val = 0;
				}
				else if (map_data.tile[y1][x2] == chotrong && map_data.tile[y2][x2] == chotrong)
					on_groud = false;
			}
		}
		
		else if (x_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == MONEY_TILE || val2 == MONEY_TILE)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				ThemTien();
			}
			else
			{
				if (val1 != chotrong || val2 != chotrong)
				{
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val = 0;
				}
				else if (map_data.tile[y1][x1] == chotrong && map_data.tile[y2][x1] == chotrong)
					on_groud = false;
			}
			
		}
	}
	int width_min = width_pic < TILE_SIZE ? width_pic : TILE_SIZE;

	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min - 1) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_pic - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAPMAX_X && y1 >= 0 && y2 < MAPMAX_Y)
	{
		if (y_val > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == MONEY_TILE || val2 == MONEY_TILE) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				ThemTien();
			}
			else
			{
				if (val1 != chotrong || val2 != chotrong)
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= height_pic + 1;
					y_val = 0;
					on_groud = true;
				}
			}
			
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == MONEY_TILE || val2 == MONEY_TILE)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				ThemTien();
			}
			else
			{
				if (val1 != chotrong || val2 != chotrong)
				{
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val = 0;
				}
			}
			
		}
	}
	x_pos += x_val;
	y_pos += y_val;
	if (x_pos < 0)
	{
		x_pos = 0;
	}
	if (x_pos >= map_data.max_X - 400)
	{
		is_win = true;
	}
	if (y_pos < 0)
	{
		y_pos = 0;
	}
	else if (y_pos + height_pic > map_data.max_Y)
	{
		time_back = 10;
		on_groud = false;
		Lives_decre();
	}
}
void NVchinh::ThemTien()
{
	money++;
}
void NVchinh::Lives_decre()
{
	lives_left--;
}

void NVchinh::updateImg(SDL_Renderer* des)
{
	if (on_groud == true) 
	{
		if (status == LEFT)
		{
			LoadImg("hinh//player_left.png", des);
		}
		else
		{
			LoadImg("hinh//player_right.png", des);
		}
	}
	else
	{
		if (status == LEFT)
		{
			LoadImg("hinh//jum_left.png", des);
		}
		else
		{
			LoadImg("hinh//jum_right.png", des);
		}
	}
}