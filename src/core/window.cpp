#include "window.h"

#include <iostream>
#include <glad/glad.h>

namespace Engine {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

Window::Window(const WindowProps& props) {
    Init(props);
}

Window::~Window() {
    Shutdown();
}

void Window::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    std::cout << "Creating window " << props.Title << " (" << props.Width << ", " << props.Height << ")" << std::endl;

    if (!s_GLFWInitialized) {
        // Initialize GLFW
        int success = glfwInit();
        if (!success) {
            std::cerr << "Could not initialize GLFW!" << std::endl;
            return;
        }

        glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }

    // Set GLFW window hints for macOS compatibility
    #ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif

    // Create window
    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(m_Window);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    std::cout << "OpenGL Info:" << std::endl;
    std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

    // Set GLFW callbacks
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
        
        // Future: Dispatch resize event
        // data.EventCallback(WindowResizeEvent(width, height));
        
        glViewport(0, 0, width, height);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
        
        // Future: Dispatch close event
        // data.EventCallback(WindowCloseEvent());
    });
}

void Window::Shutdown() {
    glfwDestroyWindow(m_Window);
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

bool Window::IsVSync() const {
    return m_Data.VSync;
}

} // namespace Engine