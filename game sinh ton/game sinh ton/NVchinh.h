#ifndef NV_CHINH_H_
#define NV_CHINH_H_

#include <vector>
#include "Hamchung.h"
#include "Hamcoso.h"
#include "bullet.h"


class NVchinh : public Hamcoso
{
public:
	NVchinh()
	{
		frame = 0;
		x_val = 0;
		y_val = 0;
		y_pos = 0;
		x_pos = 0;
		width_pic = 0;
		height_pic = 0;
		status = -1;
		input_type.left = 0;
		input_type.right = 0;
		input_type.up = 0;
		input_type.down = 0;
		input_type.jump = 0;
		on_groud = false;
		map_x_ = 0;
		map_y_ = 0;
		time_back = 0;
		money = 0;
		lives_left = 3;
		bullet_type = 1;
		is_win = false;
	}
	~NVchinh(){}
	enum WAKL_TYPE
	{
		JUMP = 2,
		RIGHT = 0,
		LEFT = 1,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);//load anh
	void show(SDL_Renderer* des);//show anh,ve anh ra man hinh
	void HandInputAction(SDL_Event event, SDL_Renderer* screen,Mix_Chunk* bullet_sound[2]);//nhap tu ngoai
	void SETNVchinh_clip();//clip nhan vat
	void dichuyen(map& map_data);//di chuyen
	void vacham(map& map_data);//va cham
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }//set toa do X,Y cua diem bat dau khi ve map
	void centerMap(map& map_data);//man hinh di chuyen
	void updateImg(SDL_Renderer* des);//cap nhat hinh anh

	SDL_Rect GetRectFrame(); //lay khung anh

	std::vector<Bullet*> get_bullet_list()const { return p_bullet_list_; }//lay dan
	void HandleBullet(SDL_Renderer* des,map& map_data);//xet dan
	void ThemTien();
	void set_time_back(const int& cb_time) { time_back = cb_time; }
	int GetMoney()const { return money; }
	void Lives_decre();
	int Get_lives_left()const { return lives_left; }
	bool WIN()const { return is_win; }

private:
	int money;
	std::vector<Bullet*> p_bullet_list_;
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_pic;
	int height_pic;

	SDL_Rect pic_clip[8];
	input input_type;

	int frame;
	int status;
	bool on_groud;
	bool is_win;
	int map_x_;
	int map_y_;

	int time_back;

	int lives_left;

	int bullet_type;

};

#endif // !NV_CHINH_H_


