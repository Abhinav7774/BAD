#pragma once
#include "BAD/Window.h"
#include "../../../vendor/Glad/include/glad/glad.h"
#include "../../../vendor/GLFW/include/GLFW/glfw3.h"

struct GLFWwindow;

namespace BAD {

	class WindowsWindow : public Window {
		public:
			WindowsWindow(const WindowProps& props);
			virtual ~WindowsWindow();
			GLFWwindow* GetGLFWwindow() const { return m_window; }

			virtual void OnUpdate() const override;

			virtual unsigned int GetHeight() const override {return m_data.height; }
			virtual unsigned int GetWidth() const override { return m_data.width; }

			virtual void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };
			virtual void SetVSync(bool enbaled) override;
			virtual bool IsVSync() const override;
			
		private:
			virtual void Init(const WindowProps& props);
			virtual void Shutdown();

			GLFWwindow* m_window;

			struct WindowData 
			{
				std::string title;
				unsigned int height, width;
				bool vsync;

				EventCallbackFn EventCallback;
			};

			WindowData m_data;
	};
}
