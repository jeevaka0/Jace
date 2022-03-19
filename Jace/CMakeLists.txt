cmake_minimum_required(VERSION 3.5)

project(Jace CXX)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

add_executable(jace ${SOURCE_FILES})
target_link_libraries(jace ChessAlgos Chess StdPlus)
