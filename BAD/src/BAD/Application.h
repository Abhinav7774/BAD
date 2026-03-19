#pragma once
#include "Core.h"
#include "PLatform/Windows/WindowsWindow.h"
namespace BAD {
	class BAD_API Application
	{
		public:
			Application();
			virtual ~Application();
			void Run();
		private:
			std::unique_ptr<Window> m_window;
			bool m_running = true;
	};
	Application* CreateApplication();
}


