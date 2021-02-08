cmake_minimum_required(VERSION 3.19.4)
project(login)

include(CTest)
enable_testing()

find_package (SQLite3)
find_package(OpenSSL REQUIRED)


include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(login src/main.cpp src/auth.cpp src/auth.h)

target_link_libraries(login ${SQLite3_LIBRARIES})
target_link_libraries(login OpenSSL::SSL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)