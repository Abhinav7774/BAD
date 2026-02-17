#pragma once

#ifdef BAD_PLATFORM_WINDOWS
	#ifdef BAD_BUILD_DLL
		#define BAD_API _declspec(dllexport)
	#else
		#define BAD_API _declspec(dllimport)
	#endif
#else
	#error BAD only supports Windows
#endif