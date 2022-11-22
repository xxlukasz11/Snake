#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "font.h"

Font::Font(AllegroFontPtr fontPtr) :
		allegroFont(std::move(fontPtr)) {
}

void Font::destroyFont(ALLEGRO_FONT* font) {
	al_destroy_font(font);
}

std::unique_ptr<Font> Font::loadFromTtfFile(const char* filename, int fontSize) {
	AllegroFontPtr fontPtr{ al_load_ttf_font(filename, fontSize, 0), destroyFont };
	if (!fontPtr) {
		return nullptr;
	}
	return std::unique_ptr<Font>(new Font(std::move(fontPtr)));
}

ALLEGRO_FONT* Font::getAllegroFontPtr() const {
	return allegroFont.get();
}
