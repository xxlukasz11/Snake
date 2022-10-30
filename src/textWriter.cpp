#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include "textWriter.h"

constexpr int LINE_HEIGHT = 30;
static const ALLEGRO_COLOR COLOR_BLACK = al_map_rgb(0, 0, 0);

TextWriter::TextWriter(const Display& display, ALLEGRO_FONT* font) :
		display(display),
		font(font) {
}

void TextWriter::writeCenter(const std::string& text) {
	write(display.width / 2, display.height / 2, text);
}

void TextWriter::writeCenterAtLine(int lineIndex, const std::string& text) {
	auto offset = LINE_HEIGHT * lineIndex;
	write(display.width / 2, display.height / 2 + offset, text);
}

void TextWriter::write(int x, int y, const std::string& text) {
	al_draw_text(font, COLOR_BLACK, x, y, ALLEGRO_ALIGN_CENTRE, text.c_str());
}
