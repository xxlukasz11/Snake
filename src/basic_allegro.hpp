#ifndef _basic_allegro_hpp_
#define _basic_allegro_hpp_

#include <map>

class Display {
public:
	ALLEGRO_DISPLAY * ptr{ nullptr };
	int width{ 0 };
	int height{ 0 };
	~Display();
	bool init(int _width, int _height, const char* _name = "Unnamed display");
	void destroy();
};

class Font {
public:
	std::map<const char*, ALLEGRO_FONT*> font_array;
	~Font();
	bool add(const char* _name, int _size, const char* _filename);
	ALLEGRO_FONT* operator[](const char* _name);
};

class Queue {
public:
	ALLEGRO_EVENT_QUEUE * ptr;
	Queue();
	~Queue();
	void register_source(ALLEGRO_DISPLAY* _display);
	void register_source(ALLEGRO_TIMER* _timer);
	void register_keyboard();
	void register_mouse();
};

class Timer {
public:
	ALLEGRO_TIMER * ptr{ nullptr };
	double interval{ 0 };
	~Timer();
	bool init(double _seconds);
};

void wait_for_any_key();

#endif