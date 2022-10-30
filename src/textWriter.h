#ifndef SRC_TEXTWRITER_H_
#define SRC_TEXTWRITER_H_

#include <allegro5/allegro_font.h>
#include <string>
#include "basic_allegro.h"

class TextWriter {
public:
	TextWriter(const Display& display, ALLEGRO_FONT* font);
	void writeCenter(const std::string& text);
	void writeCenterAtLine(int lineIndex, const std::string& text);

private:
	void write(int x, int y, const std::string& text);

	const Display& display;
	ALLEGRO_FONT* font;
};

#endif /* SRC_TEXTWRITER_H_ */
