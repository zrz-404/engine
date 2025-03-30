#pragma once //keyword similar to ifndef, def combo

#include <string>
#include <functional>
#include "/opt/homebrew/Cellar/glfw/3.4/include/GLFW/glfw3.h"
namespace Engine {

struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "My Game Engine",
                unsigned int width = 1280,
                unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

// Window class providing a cross-platform window abstraction
class Window {
public:
    // Define WindowData struct early for reference in callbacks
    struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        std::function<void(/*Event& event*/)> EventCallback;
    };

    using EventCallbackFn = std::function<void(/*Event& event*/)>;

    Window(const WindowProps& props);
    ~Window();

    void OnUpdate();

    unsigned int GetWidth() const { return m_Data.Width; }
    unsigned int GetHeight() const { return m_Data.Height; }

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled);
    bool IsVSync() const;

    void* GetNativeWindow() const { return m_Window; }

private:
    void Init(const WindowProps& props);
    void Shutdown();

private:
    GLFWwindow* m_Window;
    WindowData m_Data;
};

} // namespace Engine