#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "errMsg.hpp"
#include "gra.hpp"



Snake::Snake(float _part_size, short _window_width, short _window_height,
	float _dt, short _border, ALLEGRO_COLOR _head_color, ALLEGRO_COLOR _snake_color,
	ALLEGRO_COLOR _border_color, ALLEGRO_COLOR _background_color) :
	part_size(_part_size),
	window_width(_window_width),
	window_height(_window_height),
	dt(_dt),
	border(_border*_part_size),
	head_color(_head_color),
	snake_color(_snake_color),
	border_color(_border_color),
	background_color(_background_color),
	width(_window_width / _part_size),
	height(_window_height / _part_size) {
	std::srand(std::time(NULL));
	try {
		if (!al_reserve_samples(1))
			throw errMsg("Failed to reserve sample");
		sample = al_load_sample("sample.wav");
		if (!sample)
			throw errMsg("Failed to load sample.wav");
	}
	catch (errMsg r) {
		r.print("error.log");
	}
}

Snake::~Snake() {
	if (sample)
		al_destroy_sample(sample);
}

void Snake::intro(ALLEGRO_FONT* font) {
	draw_all();
	al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4, ALLEGRO_ALIGN_CENTRE, "NACISNIJ DOWOLNY KLAWISZ");
	al_flip_display();
}

void Snake::outro(ALLEGRO_FONT* font) {
	std::fstream file("snake_results.dat", std::ios::in);
	short max_value = 0;
	short result;
	while (file >> result) {
		if (result > max_value)
			max_value = result;
	}
	file.close();
	file.open("snake_results.dat", std::ios::app);
	file << " " << snake_size;;
	file.close();
	if (snake_size == max_value)
		al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4, ALLEGRO_ALIGN_CENTRE, "BRAWO! WYRÓWNANY REKORD!");
	else if (snake_size > max_value)
		al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4, ALLEGRO_ALIGN_CENTRE, "BRAWO! REKORD!");
	else
		al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4, ALLEGRO_ALIGN_CENTRE, "KONIEC GRY");
	al_draw_textf(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4 + 50, ALLEGRO_ALIGN_CENTRE, "Dlugosc weza: %hd", snake_size);
	if (snake_size < max_value)
		al_draw_textf(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4 + 85, ALLEGRO_ALIGN_CENTRE, "Aktualny rekord: %hd", max_value);
	else if (snake_size > max_value)
		al_draw_textf(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4 + 85, ALLEGRO_ALIGN_CENTRE, "Poprzedni rekord: %hd", max_value);
	al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height / 4 + 120, ALLEGRO_ALIGN_CENTRE, "Jeszcze raz? [t/n]");
	al_flip_display();
}

void Snake::set_food() {
	bool zle;
	do {
		zle = false;
		jx = border + (rand() % (width - 2))*part_size;
		jy = border + (rand() % (height - 2))*part_size;
		for (int i = 0; i < snake_size; i++) {
			if (jx == x[i] && jy == y[i]) {
				zle = true;
				break;
			}
		}
	} while (zle);
}

void Snake::set_start_variables(float _x, float _y, short _vx, short _vy) {
	x.push_back(static_cast<int>(_x / part_size)*part_size);
	y.push_back(static_cast<int>(_y / part_size)*part_size);
	snake_size++;
	vx = _vx;
	vy = _vy;
	set_food();
}

int Snake::change_dir(int _keycode, int _old_dir) {
	switch (_keycode) {
	case ALLEGRO_KEY_DOWN:
		if (_old_dir != ALLEGRO_KEY_UP) { vx = 0; vy = 1; return ALLEGRO_KEY_DOWN; } break;
	case ALLEGRO_KEY_UP:
		if (_old_dir != ALLEGRO_KEY_DOWN) { vx = 0; vy = -1; return ALLEGRO_KEY_UP; } break;
	case ALLEGRO_KEY_LEFT:
		if (_old_dir != ALLEGRO_KEY_RIGHT) { vx = -1; vy = 0; return ALLEGRO_KEY_LEFT; } break;
	case ALLEGRO_KEY_RIGHT:
		if (_old_dir != ALLEGRO_KEY_LEFT) { vx = 1; vy = 0; return ALLEGRO_KEY_RIGHT; } break;
	}
	return _old_dir;
}

bool Snake::calc() {
	x.push_front(x[0] + vx * part_size);
	y.push_front(y[0] + vy * part_size);
	short zderzenie = 0;
	for (int i = 4; i < snake_size; i++) {
		if (x[0] == x[i] && y[0] == y[i]) {
			zderzenie = i - 1;
			break;
		}
	}
	if (zderzenie) {
		al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		for (int i = snake_size; i > zderzenie; i--) {
			al_draw_filled_rectangle(x[i], y[i], x[i] + part_size, y[i] + part_size, background_color);
			x.pop_back();
			y.pop_back();
		}
		snake_size = zderzenie + 1;
	}
	else if (x[0] != jx || y[0] != jy) {
		al_draw_filled_rectangle(x[snake_size], y[snake_size], x[snake_size] + part_size, y[snake_size] + part_size, background_color);
		x.pop_back();
		y.pop_back();
	}
	else {
		snake_size++;
		set_food();
	}
	if (x[0] > window_width - part_size - border
		|| x[0] < border
		|| y[0] > window_height - part_size - border
		|| y[0] < border)
		return false;
	return true;
}

void Snake::draw_all() {
	al_clear_to_color(border_color);
	al_draw_filled_rectangle(border, border, window_width - border, window_height - border, background_color);
	al_draw_filled_circle(jx + part_size / 2, jy + part_size / 2, part_size / 2.2, al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(x[0], y[0], x[0] + part_size, y[0] + part_size, head_color);
	for (int i = 1; i < snake_size; i++)
		al_draw_filled_rectangle(x[i], y[i], x[i] + part_size, y[i] + part_size, snake_color);
}

void Snake::draw() {
	al_draw_filled_circle(jx + part_size / 2, jy + part_size / 2, part_size / 2.2, al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(x[0], y[0], x[0] + part_size, y[0] + part_size, head_color);
	if (snake_size > 1)
		al_draw_filled_rectangle(x[1], y[1], x[1] + part_size, y[1] + part_size, snake_color);
}

bool install_modules() {
	try {
		if (!al_init())
			throw errMsg("Failed to initialize allegro");
		if (!al_install_audio())
			throw errMsg("Failed to install audio");
		if (!al_init_acodec_addon())
			throw errMsg("Failed to initialize acodec addon");
		if (!al_init_primitives_addon())
			throw errMsg("Failed to initialize primitives addon");
		if (!al_init_font_addon())
			throw errMsg("Failed to initialize font addon");
		if (!al_init_ttf_addon())
			throw errMsg("Failed to initialize ttf addon");
	}
	catch (errMsg r) {
		r.print("error.log");
		return false;
	}
	return true;
}
