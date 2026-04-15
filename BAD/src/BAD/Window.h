#pragma once
#include "badpch.h"
#include "Core.h"
#include "BAD/Event/Event.h"


namespace BAD {
	struct WindowProps 
	{
		std::string m_title;
		unsigned int m_height;
		unsigned int m_width;


		WindowProps(const std::string& p_title = "BAD",
					 unsigned int p_height = 720,
					 unsigned int p_width = 1280)
					 : m_title(p_title),
					   m_height(p_height),
					   m_width(p_width) {};
	};

	class BAD_API Window {
		public:
			using EventCallbackFn = std::function<void(Event& e)>;

			virtual ~Window() {}

			virtual void OnUpdate() const = 0;

			virtual unsigned int GetHeight() const = 0;
			virtual unsigned int GetWidth() const = 0;

			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
			virtual void SetVSync(bool enbaled) = 0;
			virtual bool IsVSync() const = 0;

			static Window* Create (const WindowProps& props = WindowProps());

	};
}

