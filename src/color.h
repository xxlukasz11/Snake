#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

class Color {
public:
	Color();
	int r() const;
	int g() const;
	int b() const;
	static Color rgb(int r, int g, int b);

private:
	Color(int r, int g, int b);

	int rValue;
	int gValue;
	int bValue;
};

#endif /* SRC_COLOR_H_ */
