add_library(ObjParser ObjParser.cpp ObjParser.h)
target_include_directories(ObjParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ObjParser PRIVATE ../../../dep)