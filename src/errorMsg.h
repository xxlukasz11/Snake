#ifndef _errMsg_hpp_
#define _errMsg_hpp_

#include <string>

class ErrorMsg {
public:
	ErrorMsg(const std::string& message);
	void print(const std::string& filename);

private:
	std::string msg{ "" };
};

#endif
