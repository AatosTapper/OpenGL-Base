add_library(VertexBuffer VertexBuffer.cpp VertexBuffer.h)
target_include_directories(VertexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(VertexArray VertexArray.cpp VertexArray.h)
target_include_directories(VertexArray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(IndexBuffer IndexBuffer.cpp IndexBuffer.h)
target_include_directories(IndexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Texture Texture.cpp Texture.h)
target_include_directories(Texture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Mesh Mesh.cpp Mesh.h)
target_include_directories(Mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Camera Camera.cpp Camera.h)
target_include_directories(Camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Lights Lights.cpp Lights.h)
target_include_directories(Lights PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(VertexBuffer PRIVATE ../../../dep)
target_include_directories(VertexArray PRIVATE ../../../dep)
target_include_directories(IndexBuffer PRIVATE ../../../dep)
target_include_directories(Texture PRIVATE ../../../dep)
target_include_directories(Mesh PRIVATE ../../../dep)
target_include_directories(Camera PRIVATE ../../../dep)
target_include_directories(Lights PRIVATE ../../../dep)