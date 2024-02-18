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

CameraController::CameraController(GLFWwindow *window, float SW, float SH) :
    movement_speed(0.08f), 
    mouse_sensitivity(0.8f)
{
    mouse_last_x = SW / 2.0f;
    mouse_last_y = SH / 2.0f;

    glfwSetCursorPosCallback(window, mouse_callback);
}

void CameraController::update(GLFWwindow *window, Camera &camera)
{
    glm::vec3 delta_pos = glm::vec3(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        delta_pos.z += movement_speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        delta_pos.z -= movement_speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        delta_pos.x -= movement_speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        delta_pos.x += movement_speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        delta_pos.y -= movement_speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        delta_pos.y += movement_speed;
    
    float multiplier = 1.0f;
    if (glm::length(delta_pos) > movement_speed)
        multiplier = movement_speed / glm::length(delta_pos);
    delta_pos *= multiplier;

    camera.forward(delta_pos.z);
    camera.right(delta_pos.x);
    camera.down(delta_pos.y);

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
        camera.yaw -= mouse_x_offset * mouse_sensitivity;
        camera.pitch += mouse_y_offset * mouse_sensitivity;

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

/*
void CameraController::m_clamp_delta_pos()
{
    if (glm::length(m_delta_pos) < 0.00001f) return;
    
    const float max_len = 0.1f;
    float multiplier = 1.0f;
    
    if (glm::length(m_delta_pos) > max_len)
        multiplier = max_len / glm::length(m_delta_pos);

    m_delta_pos *= multiplier;
}
*/