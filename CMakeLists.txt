cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project (snake)

file(GLOB SOURCES "src/*.cpp")
add_executable(snake ${SOURCES})

set_property(TARGET snake PROPERTY CXX_STANDARD 17)

target_compile_options(snake PRIVATE -Wall -pedantic)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "snake")
target_link_libraries(snake allegro_ttf allegro_font allegro_primitives allegro_audio allegro_acodec allegro)
