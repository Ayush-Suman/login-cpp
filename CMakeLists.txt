cmake_minimum_required(VERSION 3.19.4)
project(login)

include(CTest)
enable_testing()

find_package (SQLite3)
find_package(OpenSSL REQUIRED)


include_directories(${SQLite3_INCLUDE_DIRS})

set(Auth src/auth)

add_executable(login src/main.cpp ${Auth}/auth.cpp ${Auth}/auth.h ${Auth}/auth_model.cpp ${Auth}/auth_model.h)

target_link_libraries(login ${SQLite3_LIBRARIES})
target_link_libraries(login OpenSSL::SSL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)