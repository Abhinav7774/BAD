#pragma once
#include "badpch.h"
#include "Application.h"
#ifdef BAD_PLATFORM_WINDOWS
	
	extern BAD::Application* BAD::CreateApplication();
	int main(int argc, char** argv) {
		BAD::Log::Init();
		BAD_CORE_ERROR("Wohoo Atlast an Error!! with number1:{0} and numer2:{1}",10,3);
		BAD_WARN("Initialize Log!!");
		BAD_CORE_ERROR("Initialize Log for Engine!!");
		std::cout << "BAD ENGINE IS STARING!!" << "\n";
		auto app = BAD::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error BAD only supports Windows for now
#endif