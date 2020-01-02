cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(NISTC)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Threads)

add_subdirectory(../AlignmentRepaC ../AlignmentRepaC_build)

include_directories(../rapidjson/include ../AlignmentC ../AlignmentRepaC)

add_executable(NISTC main.cpp NISTDev.cpp )

target_link_libraries(NISTC PUBLIC AlignmentRepaC AlignmentC Threads::Threads)

target_include_directories(NISTC PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )

install(TARGETS NISTC DESTINATION bin)
