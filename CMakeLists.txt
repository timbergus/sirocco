cmake_minimum_required(VERSION 3.2)

project(sirocco)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

#3 This is the Conan configuartion.
conan_basic_setup(NO_OUTPUT_DIRS)

add_executable(sirocco src/server/app/main.cpp)

target_include_directories(sirocco PRIVATE src/server/include)

target_link_libraries(sirocco ${CONAN_LIBS})
