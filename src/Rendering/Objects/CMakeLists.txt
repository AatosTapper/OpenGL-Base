add_library(VertexBuffer VertexBuffer.cpp VertexBuffer.h)
target_include_directories(VertexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(VertexArray VertexArray.cpp VertexArray.h)
target_include_directories(VertexArray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(IndexBuffer IndexBuffer.cpp IndexBuffer.h)
target_include_directories(IndexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(VertexBuffer PRIVATE ../../../dep)
target_include_directories(VertexArray PRIVATE ../../../dep)
target_include_directories(IndexBuffer PRIVATE ../../../dep)