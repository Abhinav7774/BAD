#include "badpch.h"
#include "WindowsWindow.h"

namespace BAD {
	
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) 
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::OnUpdate() const {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_data.title = props.m_title;
		m_data.height = props.m_height;
		m_data.width = props.m_width;
		
		BAD_CORE_DBUG("Creating Window of {0} Height and {1} Width With Title: {2}",m_data.height,m_data.width, m_data.title);

		if (!s_GLFWInitialized) {
			int success  = glfwInit();

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int) m_data.width, (int) m_data.height, (const char*) m_data.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_window);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else 
		{
			glfwSwapInterval(0);
		}
		m_data.vsync = true;
	}

	bool WindowsWindow::IsVSync() const {
		return m_data.vsync;
	}
}