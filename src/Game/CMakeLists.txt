add_library(Scenes Scenes.cpp Scenes.h)
target_include_directories(Scenes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Scenes PRIVATE ../../dep)