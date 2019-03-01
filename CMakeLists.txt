cmake_minimum_required (VERSION 3.5)

project(my_test_avl)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(avl ${SRC_DIR}/avl.c ${INCLUDE_DIR}/avl.h)
target_include_directories(avl PUBLIC ${INCLUDE_DIR})
add_executable(test_avl ${SRC_DIR}/test_avl.c)
target_compile_options(test_avl PUBLIC -DEBUG -Wall -Wextra -Wpedantic -g) 
target_include_directories(test_avl PUBLIC ${INCLUDE_DIR})
target_link_libraries(test_avl avl)