#pragma once
#include "Core.h"
namespace BAD {
	class BAD_API Application
	{
		public:
			Application();
			virtual ~Application();
			void Run();
	};
	Application* CreateApplication();
}


