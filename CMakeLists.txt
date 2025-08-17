cmake_minimum_required(VERSION 4.1.0)
project(sirocco
  VERSION 0.1.0
  DESCRIPTION "Sirocco Project"
  LANGUAGES C CXX
)

set(PROJECT_AUTHOR "Gustavo Muñoz")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Werror -Wpedantic)

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/server/apps/*.cpp)

include(FetchContent)

# >>> fmt library download
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.2.0
)
FetchContent_MakeAvailable(fmt)
# <<< fmt library download

# >>> nlohmann_json library download
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)
# <<< nlohmann_json library download

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/server/main.cpp ${CPP_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
  fmt::fmt
  nlohmann_json::nlohmann_json
  sqlite3
)

# >>> CPack
include(InstallRequiredSystemLibraries)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR ${PROJECT_AUTHOR})
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
include(CPack)
# <<< CPack

# >>> Testing
include(CTest)
enable_testing()

# SPLIT_TEST

add_executable(split_test ${CMAKE_SOURCE_DIR}/src/tests/split_test.cpp ${CPP_FILES})
target_include_directories(split_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(split_test fmt::fmt)
target_link_libraries(split_test sqlite3)

add_test(
  NAME split_test
  COMMAND $<TARGET_FILE:split_test>
)

# READ_ENV_FILE_TEST

add_executable(read_env_file_test ${CMAKE_SOURCE_DIR}/src/tests/read_env_file_test.cpp ${CPP_FILES})
target_include_directories(read_env_file_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(read_env_file_test fmt::fmt)
target_link_libraries(read_env_file_test sqlite3)

add_test(
  NAME read_env_file_test
  COMMAND $<TARGET_FILE:read_env_file_test>
)

# READ_FILE_TEST

add_executable(read_file_test ${CMAKE_SOURCE_DIR}/src/tests/read_file_test.cpp ${CPP_FILES})
target_include_directories(read_file_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(read_file_test fmt::fmt)
target_link_libraries(read_file_test sqlite3)

add_test(
  NAME read_file_test
  COMMAND $<TARGET_FILE:read_file_test>
)

# STRINGIFY_VECTOR_TEST

add_executable(stringify_vector_test ${CMAKE_SOURCE_DIR}/src/tests/stringify_vector_test.cpp ${CPP_FILES})
target_include_directories(stringify_vector_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(stringify_vector_test fmt::fmt)
target_link_libraries(stringify_vector_test sqlite3)

add_test(
  NAME stringify_vector_test
  COMMAND $<TARGET_FILE:stringify_vector_test>
)

# STRINGIFY_MAP_TEST

add_executable(stringify_map_test ${CMAKE_SOURCE_DIR}/src/tests/stringify_map_test.cpp ${CPP_FILES})
target_include_directories(stringify_map_test PRIVATE ${CMAKE_SOURCE_DIR}/src/server/include)

target_link_libraries(stringify_map_test fmt::fmt)
target_link_libraries(stringify_map_test sqlite3)

add_test(
  NAME stringify_map_test
  COMMAND $<TARGET_FILE:stringify_map_test>
)
# <<< Testing
