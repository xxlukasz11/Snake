#ifndef SRC_FRAMEWORK_ALLEGRO_INIT_H_
#define SRC_FRAMEWORK_ALLEGRO_INIT_H_

#include <string>

namespace framework {

enum class AllegroInitStatus {
	SUCCESS, FAILURE
};

struct AllegroInitResult {
	AllegroInitStatus status;
	std::string errorMesage;
};

AllegroInitResult init_allegro();

}
// namespace framework

#endif /* SRC_FRAMEWORK_ALLEGRO_INIT_H_ */
