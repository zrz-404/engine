#include "application.h"

#include <iostream>

namespace Engine {

Application* Application::s_Instance = nullptr;

Application::Application() {
    if (s_Instance) {
        std::cerr << "Application already exists!" << std::endl;
        return;
    }
    s_Instance = this;

    m_Window = std::make_unique<Window>(WindowProps());
}

Application::~Application() {
    s_Instance = nullptr;
}

void Application::Run() {
    std::cout << "Application running..." << std::endl;

    // Basic game loop
    while (m_Running) {
        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update window
        m_Window->OnUpdate();

        // Check if window should close
        if (glfwWindowShouldClose((GLFWwindow*)m_Window->GetNativeWindow())) {
            m_Running = false;
        }
    }
}

} // namespace Engine