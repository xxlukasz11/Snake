#ifndef SRC_TEXTWRITER_H_
#define SRC_TEXTWRITER_H_

#include <string>
#include "display.h"
#include "font.h"

class TextWriter {
public:
	TextWriter(const Display& display, const Font& font);
	void writeCenter(const std::string& text);
	void writeCenterAtLine(int lineIndex, const std::string& text);

private:
	void write(int x, int y, const std::string& text);

	const Display& display;
	const Font& font;
};

#endif /* SRC_TEXTWRITER_H_ */
