#include <fstream>
#include <string>
#include "errMsg.hpp"

errMsg::errMsg(std::string _m) {
	msg = _m;
}

void errMsg::print(const char* _filename) {
	std::ofstream err(_filename, std::ios::app);
	err << msg << std::endl;
	err.close();
}