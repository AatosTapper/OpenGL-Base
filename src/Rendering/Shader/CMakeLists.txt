add_library(Shader Shader.cpp Shader.h)
target_include_directories(Shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Shader PRIVATE ../../../dep)