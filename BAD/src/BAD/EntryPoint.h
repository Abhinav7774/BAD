#pragma once
#include "Application.h"
#include <cstdio>
#ifdef BAD_PLATFORM_WINDOWS
	
	extern BAD::Application* BAD::CreateApplication();
	int main(int argc, char** argv) {
	printf("BAD ENGINE IS STARING!!");
		auto app = BAD::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error BAD only supports Windows
#endif