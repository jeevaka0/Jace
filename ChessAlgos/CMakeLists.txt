project(ChessAlgos CXX)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

add_library(ChessAlgos STATIC ${SOURCE_FILES})
