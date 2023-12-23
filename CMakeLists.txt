cmake_minimum_required(VERSION 3.27)
project(sirocco VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/server/apps/*.cpp)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/server/main.cpp ${CPP_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# TESTS

# add_executable(split_test ${CMAKE_SOURCE_DIR}/src/tests/split_test.cpp ${CPP_FILES})
# target_include_directories(split_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

# add_test(
#   NAME split_test
#   COMMAND $<TARGET_FILE:split_test>
# )

# add_executable(read_env_file_test ${CMAKE_SOURCE_DIR}/src/tests/read_env_file_test.cpp ${CPP_FILES})
# target_include_directories(read_env_file_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

# add_test(
#   NAME read_env_file_test
#   COMMAND $<TARGET_FILE:read_env_file_test>
# )

# add_executable(read_file_test ${CMAKE_SOURCE_DIR}/src/tests/read_file_test.cpp ${CPP_FILES})
# target_include_directories(read_file_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

# add_test(
#   NAME read_file_test
#   COMMAND $<TARGET_FILE:read_file_test>
# )

# add_executable(stringify_vector_test ${CMAKE_SOURCE_DIR}/src/tests/stringify_vector_test.cpp ${CPP_FILES})
# target_include_directories(stringify_vector_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

# add_test(
#   NAME stringify_vector_test
#   COMMAND $<TARGET_FILE:stringify_vector_test>
# )

# add_executable(stringify_map_test ${CMAKE_SOURCE_DIR}/src/tests/stringify_map_test.cpp ${CPP_FILES})
# target_include_directories(stringify_map_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

# add_test(
#   NAME stringify_map_test
#   COMMAND $<TARGET_FILE:stringify_map_test>
# )
