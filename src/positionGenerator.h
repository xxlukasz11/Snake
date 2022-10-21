#ifndef SRC_POSITIONGENERATOR_H_
#define SRC_POSITIONGENERATOR_H_

#include <random>
#include "utils.h"

class PositionGenerator {
public:
	PositionGenerator(const Area& area);
	int ramdomX();
	int randomY();

private:
	std::mt19937 generator;
	std::uniform_int_distribution<> xDistrib;
	std::uniform_int_distribution<> yDistrib;
};

#endif /* SRC_POSITIONGENERATOR_H_ */
