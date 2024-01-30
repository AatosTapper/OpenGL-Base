#pragma once

struct GLFWwindow;
class Camera;

// provides a generic 3D camera controller with mouse and keyboard already setup

class CameraController
{
public:
    CameraController(GLFWwindow *window, float SW, float SH);
    
    void update(GLFWwindow *window, Camera &camera);
};