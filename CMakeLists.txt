cmake_minimum_required(VERSION 3.25.1)

project(sirocco)

add_definitions("-std=c++2b")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#3 This is the Conan configuartion.
conan_basic_setup(NO_OUTPUT_DIRS)

add_executable(sirocco src/server/app/main.cpp)

target_include_directories(sirocco PRIVATE src/server/include)

target_link_libraries(sirocco ${CONAN_LIBS})
