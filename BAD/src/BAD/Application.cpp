#include "BAD/Event/ApplicationEvent.h"
#include "Application.h"
#include "Log.h"
#include <iostream>

namespace BAD {
	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::Run() {
			WindowResizeEvent e(1920,1080);
			BAD_TRACE("{}",e);
			while(true);
	}

}