#pragma once //keyword similar to ifndef, def combo

#include <string>
#include <functional>
#include "/opt/homebrew/Cellar/glfw/3.4/include/GLFW/glfw3.h"

namespace Engine {

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "zrz",
                unsigned int width = 1280,
                unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

//window class providing a cross-platform window abstraction
class Window {
    public:
        using EventCallbackFn = std::function<void(/*Event& event*/)>;

        Window(const WindowProps& props);
        ~Window();

        void OnUpdate();

        unsigned int GetWidth() const { return m_Data.Width; }
        unsigned int GetHeight() const { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) {m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        void IsVsync() const;

        void* GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
};

} // namespace engine
