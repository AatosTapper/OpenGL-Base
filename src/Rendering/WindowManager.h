#pragma once

#include "../config.h"

// Manages and own the glfw context

class WindowManager
{
public:
    WindowManager(int width, int height, const char* name);
    ~WindowManager();

    inline GLFWwindow *get_window() const { return m_window; }
    float get_aspect_ratio() const;
    void terminate_context();

private:
    GLFWwindow *m_window;
    bool m_terminated;
};
