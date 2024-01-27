add_library(Renderer Renderer.cpp Renderer.h)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(WindowManager WindowManager.cpp WindowManager.h)
target_include_directories(WindowManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Renderer PRIVATE ../../dep)
target_include_directories(WindowManager PRIVATE ../../dep)

add_subdirectory(Shader)
add_subdirectory(Objects)
add_subdirectory(Parsing)