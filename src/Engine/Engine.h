#pragma once

#include "../config.h"

#include <memory>

class Scene;
class WindowManager;
class Renderer;
class Camera;
class CameraController;
class Shader;
class Mesh;

class Engine
{
public:
    Engine(int argc, char** argv, uint16_t sw, uint16_t sh);
    ~Engine();

    void load_scene(Scene *active_scene);
    void run();

private:
    std::unique_ptr<WindowManager> m_window_manager;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<CameraController> m_camera_controller;
    Scene *m_active_scene;

    void m_update_logic();
    void m_update_render();
};