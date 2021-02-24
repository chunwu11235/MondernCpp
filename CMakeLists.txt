cmake_minimum_required(VERSION 3.0.0)
project(ModernCpp VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


include_directories(src)

set(SOURCES 
main.cpp 
src/my_lib.h
src/my_lib.cpp
)

add_executable(ModernCpp ${SOURCES})


