#ifndef _gra_hpp_
#define _gra_hpp_

#include <deque>

bool install_modules();

class Snake {
	std::deque<float> x;
	std::deque<float> y;
	float part_size;
	short window_width, window_height;
	float dt;
	float border;
	ALLEGRO_COLOR head_color;
	ALLEGRO_COLOR snake_color;
	ALLEGRO_COLOR border_color;
	ALLEGRO_COLOR background_color;
	int width, height;
	short vx{ 0 }, vy{ 0 };
	float jx, jy;
	short snake_size{ 0 };
	ALLEGRO_SAMPLE* sample{ nullptr };
public:
	Snake(float _part_size, short _window_width, short _window_height,
		float _dt, short _border, ALLEGRO_COLOR _head_color, ALLEGRO_COLOR _snake_color,
		ALLEGRO_COLOR _border_color, ALLEGRO_COLOR _background_color);
	~Snake();
	void intro(ALLEGRO_FONT* font);
	void outro(ALLEGRO_FONT* font);
	void set_start_variables(float _x, float _y, short _vx, short _vy);
	int change_dir(int _keycode, int _old_dir);
	bool calc();
	void draw_all();
	void draw();
	void set_food();
};

#endif
