#ifndef SRC_BORDER_H_
#define SRC_BORDER_H_

#include "utils.h"

class Border {
public:
	Border(const Area& area);
	bool isPartOfTheBorder(const Position& position) const;
	const Area& getArea() const;

private:
	Area area;
};

#endif /* SRC_BORDER_H_ */
