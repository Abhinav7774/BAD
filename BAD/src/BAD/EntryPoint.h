#pragma once
#include "badpch.h"
#include "Application.h"
#ifdef BAD_PLATFORM_WINDOWS
	
	extern BAD::Application* BAD::CreateApplication();
	int main(int argc, char** argv) {
		BAD::Log::Init();
		BAD_CORE_DBUG("Initialize Log!!");
		BAD_CORE_DBUG("Initialize Log for Engine!!");
		BAD_CORE_INFO("BAD ENGINE IS STARING!!");
		auto app = BAD::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error BAD only supports Windows for now
#endif