#pragma once

#ifdef RT_PLATFORM_WINDOWS
	#ifdef RT_BUILD_DLL
		#define RAT_API __declspec(dllexport)
	#else
		#define RAT_API __declspec(dllimport)
	#endif
#else
	#error Rat only supports Windows!
#endif

#define BIT(x) (1 << x)