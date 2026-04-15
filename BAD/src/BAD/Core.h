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

#ifdef BAD_DEBUG
#define BAD_ENABLE_ASSERTS
#endif

#ifdef BAD_ENABLE_ASSERTS
#define BAD_ASSERT(x, ...) { if(!(x)) { BAD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define BAD_CORE_ASSERT(x, ...) { if(!(x)) { BAD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define BAD_ASSERT(x, ...)
#define BAD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) 1 << x