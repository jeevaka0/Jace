project(Chess CXX)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

add_library(Chess STATIC ${SOURCE_FILES})
