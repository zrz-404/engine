#pragma once

#include "window.h"
#include <memory>

namespace Engine {

class Application {
public:
	Application();
	virtual ~Application();

	void Run();

	Window& GetWindow() { return *m_Window; }

	static Application& Get() { return *s_Instance; }

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;

private:
	static Application* s_Instance;
};

// To be defined by CLIENT
Application* CreateApplication();

} // namespace Engine