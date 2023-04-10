cmake_minimum_required(VERSION 3.9)

file(GLOB snake_SRC CONFIGURE_DEPENDS "*.cpp" "*.cc")
add_executable(snake ${snake_SRC})
set_target_properties(snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(snake PROPERTIES OUTPUT_NAME "snake")

set_target_properties(snake PROPERTIES CXX_STANDARD 17)
target_compile_options(snake PRIVATE -Wall)
target_link_libraries(snake PRIVATE allegrocpp)