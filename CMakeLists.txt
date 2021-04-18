cmake_minimum_required(VERSION 3.0.0)
project(ModernCpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(Boost_INCLUDE_DIR /Users/ming-chunwu/boost_1_76_0)
set(Boost_LIBRARY_DIR /Users/ming-chunwu/boost_1_76_0/stage/lib)
find_package(Boost 1.76 REQUIRED COMPONENTS serialization)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

include_directories(src)
include_directories(header)

set(lib_101
header/lib_101.h
src/lib_101.cpp
)

set(lib_memory
header/lib_memory.h
src/lib_memory.cpp)

set(lib_primer
header/lib_primer.h
src/lib_primer.cpp)

set(Car
header/Car.h
src/Car.cpp)

set(Oop
header/Oop.h
src/Oop.cpp)

set(lambda_expressions
header/lambda_expressions.h
src/lambda_expressions.cpp)

add_executable(boost101 
main_boost101.cpp
)

add_executable(ModernCpp 
main.cpp
${lib_101}
${lib_primer}
${lib_memory}
${Car}
${Oop}
${lambda_expressions}
)

add_executable(Playground 
playground.cpp
${lib_101}
${lib_memory}
)

add_subdirectory(design_patterns)
add_executable(Design main_design_patterns.cpp)

target_link_libraries(Design PUBLIC design_patterns ${Boost_LIBRARIES})
target_include_directories(Design PUBLIC design_patterns/)