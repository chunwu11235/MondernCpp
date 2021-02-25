cmake_minimum_required(VERSION 3.0.0)
project(ModernCpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


include_directories(src)

set(my_lib
src/my_lib.h
src/my_lib.cpp
)

add_executable(ModernCpp 
main.cpp
${my_lib}
)

add_executable(Playground 
playground.cpp
${my_lib}
)