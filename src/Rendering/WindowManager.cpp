#include "WindowManager.h"

#include "../util.h"

static float aspect_ratio = 0.0f;

static float calc_aspect_ratio(int width, int height)
{
    return (float)width / (float)height;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    aspect_ratio = calc_aspect_ratio(width, height);
}

WindowManager::WindowManager(int width, int height, const char* name) : m_terminated(false)
{
    aspect_ratio = calc_aspect_ratio(width, height);
    if (!glfwInit())
    {
        ASSERT(false, "GLFW couldn't init");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

    m_window = glfwCreateWindow(width, height, name, NULL, NULL);
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        ASSERT(false, "glad couldn't init");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    int fb_width, fb_height;
    glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
    framebuffer_size_callback(m_window, fb_width, fb_height);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

WindowManager::~WindowManager()
{
    if (!m_terminated)
        glfwTerminate();
}

void WindowManager::terminate_context()
{
    glfwTerminate();
    m_terminated = true;
}

float WindowManager::get_aspect_ratio() const
{
    return aspect_ratio;
}