add_library(CameraController CameraController.cpp CameraController.h)
target_include_directories(CameraController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(CameraController PRIVATE ../../dep)