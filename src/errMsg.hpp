#ifndef _errMsg_hpp_
#define _errMsg_hpp_

#include <string>

class errMsg {
public:
	std::string msg{ "" };
	errMsg(std::string _m);
	void print(const char* _filename);
};

#endif
