#include "badpch.h"
#include "Application.h"
#include "BAD/Event/ApplicationEvent.h"
#include "BAD/Event/KeyEvent.h"

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
float s_PlayerVelocity = 0.0f;
namespace BAD {


	Application::Application() {
		m_window = (std::unique_ptr<Window>)Window::Create();
		m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		
		dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
			{
				if (e.GetKeyCode() == GLFW_KEY_SPACE)
				{
					BAD_TRACE("SPACE PRESSED");
					s_PlayerVelocity = 0.2f;
				}
				return false;
			});

		BAD_CORE_TRACE(event);
	}

	void Application::Run()
	{
		while (m_running)
		{
		
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

		
			m_window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(Event& e) {
		m_running = false;
		return true;
	}


}