cmake_minimum_required(VERSION 3.26.3)
project(sirocco VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 26)
add_compile_options(-Wall -Wextra)

file(GLOB SOURCES src/server/include/*.h src/server/include/*.cpp)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(sirocco src/server/app/main.cpp ${SOURCES})

target_include_directories(sirocco PRIVATE src/server/include)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
