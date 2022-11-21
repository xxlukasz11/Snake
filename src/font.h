#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <memory>
#include <string>
#include <allegro5/allegro_font.h>

class Font {
public:
	ALLEGRO_FONT* getAllegroFontPtr() const;
	static std::unique_ptr<Font> loadFromFile(const char* filename, int fontSize);

private:
	using AllegroFontDeleter = void(*)(ALLEGRO_FONT*);
	using AllegroFontPtr = std::unique_ptr<ALLEGRO_FONT, AllegroFontDeleter>;

	Font(AllegroFontPtr fontPtr);
	static void destroyFont(ALLEGRO_FONT* font);

	AllegroFontPtr allegroFont;
};

#endif // SRC_FONT_H_
