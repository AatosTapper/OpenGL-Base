add_executable(main 
    config.h 
    main.cpp 
    glad/glad.c
)

target_compile_options(main PRIVATE 
    -Wall
    -pedantic
)

add_subdirectory(Rendering)
add_subdirectory(Input)
add_subdirectory(Engine)

target_include_directories(main PRIVATE ../dep)
target_link_libraries(main 
    glfw 
    OpenGL::GL
    WindowManager
    Renderer
    Shader
    VertexBuffer
    VertexArray
    IndexBuffer
    Texture
    ObjParser
    Mesh
    Camera
    CameraController
    Scene
)