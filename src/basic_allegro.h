#ifndef _basic_allegro_hpp_
#define _basic_allegro_hpp_

#include <map>
#include <string>
#include <allegro5/allegro_font.h>

class Display {
public:
	ALLEGRO_DISPLAY* ptr{ nullptr };
	int width{ 0 };
	int height{ 0 };
	int widthRasters;
	int heightRasters;
	int rasterSize;
	~Display();
	bool init(int widthRasters, int heightRasters, int rasterSize, const char* _name = "Unnamed display");
	void destroy();
};

class Font {
public:
	std::map<std::string, ALLEGRO_FONT*> font_array;
	~Font();
	bool add(const char* _name, int _size, const char* _filename);
	ALLEGRO_FONT* operator[](const std::string& _name) const;
};

class Queue {
public:
	ALLEGRO_EVENT_QUEUE* ptr;
	Queue();
	~Queue();
	void register_source(ALLEGRO_DISPLAY* _display);
	void register_source(ALLEGRO_TIMER* _timer);
	void register_keyboard();
	void register_mouse();
};

void wait_for_any_key();

#endif
