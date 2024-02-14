add_library(Engine Engine.cpp Engine.h)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Scene Scene.cpp Scene.h)
target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Engine PRIVATE ../../dep)
target_include_directories(Scene PRIVATE ../../dep)