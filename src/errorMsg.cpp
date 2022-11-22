#include <fstream>
#include <string>
#include "errorMsg.h"

ErrorMsg::ErrorMsg(const std::string& message) :
		msg(message) {
}

void ErrorMsg::print(const std::string& filename) {
	std::ofstream file(filename, std::ios::app);
	file << msg << std::endl;
	file.close();
}
