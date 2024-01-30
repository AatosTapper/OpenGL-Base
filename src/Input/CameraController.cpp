#include "CameraController.h"

#include "../config.h"

#include "../Rendering/Objects/Camera.h"

float mouse_last_x, mouse_last_y = 0.0f;
float mouse_x_offset = 0.0f;
float mouse_y_offset = 0.0f;
bool mouse_status = false;
bool esc_pressed_last_frame = false;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    mouse_x_offset = (mouse_last_x - xpos) * 0.14f;
    mouse_y_offset = (mouse_last_y - ypos) * 0.1f;
    mouse_last_x = xpos;
    mouse_last_y = ypos;
}

CameraController::CameraController(GLFWwindow *window, float SW, float SH)
{
    mouse_last_x = SW / 2.0f;
    mouse_last_y = SH / 2.0f;

    glfwSetCursorPosCallback(window, mouse_callback);
}

void CameraController::update(GLFWwindow *window, Camera &camera)
{
    const float cam_speed = 0.1f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.forward(cam_speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.back(cam_speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.left(cam_speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.right(cam_speed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.up(cam_speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.down(cam_speed);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !esc_pressed_last_frame)
    {
        if (mouse_status)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouse_status = !mouse_status;
        esc_pressed_last_frame = true;
    }   
    if (!mouse_status)
    {
        camera.yaw -= mouse_x_offset;
        camera.pitch += mouse_y_offset;

        if (camera.pitch > 88.0f)
            camera.pitch = 88.0f;
        else if (camera.pitch < -88.0f)
            camera.pitch = -88.0f;

        mouse_x_offset = 0.0f;
        mouse_y_offset = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
        esc_pressed_last_frame = false;
}