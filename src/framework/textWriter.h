#ifndef SRC_TEXTWRITER_H_
#define SRC_TEXTWRITER_H_

#include <string>

namespace framework {

class Display;
class Font;

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

} // namespace framework

#endif /* SRC_TEXTWRITER_H_ */
