cmake_minimum_required(VERSION 3.16)
project(21f_pa03_kyle_ariyan)

set(CMAKE_CXX_STANDARD 14)


find_package(Boost 1.40 COMPONENTS graph REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(input01 "football.graphml")
set(input02 "input.graphml")

foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(21f_pa03_kyle_ariyan main.cpp Girvan-Newman.cpp Girvan-Newman.h AVLTree1.h AVLtree.h)

target_link_libraries(21f_pa03_kyle_ariyan Boost::graph)