#ifndef _basic_allegro_hpp_
#define _basic_allegro_hpp_

#include <map>
#include <string>
#include <allegro5/allegro_font.h>

class Font {
public:
	std::map<std::string, ALLEGRO_FONT*> font_array;
	~Font();
	bool add(const char* _name, int _size, const char* _filename);
	ALLEGRO_FONT* operator[](const std::string& _name) const;
};

void wait_for_any_key();

#endif
