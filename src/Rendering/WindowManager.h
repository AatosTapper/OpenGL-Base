#pragma once

#include "../config.h"

// Manages and own the glfw context

class WindowManager
{
public:
    WindowManager(int width, int height, const char* name);
    ~WindowManager();

    inline GLFWwindow *get_window() const { return m_window; }
    void terminate_context();

private:
    GLFWwindow *m_window;
    bool m_terminated;
};
