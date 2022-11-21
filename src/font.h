#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <map>
#include <string>
#include <allegro5/allegro_font.h>

class Font {
public:
	~Font();
	bool add(const char* _name, int _size, const char* _filename);
	ALLEGRO_FONT* operator[](const std::string& _name) const;

private:
	std::map<std::string, ALLEGRO_FONT*> fontArray;
};

#endif // SRC_FONT_H_
