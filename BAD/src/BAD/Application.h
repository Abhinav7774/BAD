#pragma once
#include "Core.h"
#include "BAD/Event/Event.h"
#include "BAD/Event/ApplicationEvent.h"
#include "PLatform/Windows/WindowsWindow.h"
#include "LayerStack.h"
namespace BAD {
	class BAD_API Application
	{
		public:
			Application();
			virtual ~Application();
			void Run();
			void OnEvent(Event& event);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			bool OnWindowClose(Event& e);


		private:
			std::unique_ptr<Window> m_window;
			bool m_running = true;
			LayerStack m_LayerStack;

	};

	Application* CreateApplication();
}


