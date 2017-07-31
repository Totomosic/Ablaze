#pragma once
#include <Windows.h>
#include <iostream>

namespace Ablaze
{
#define AB_LOG_LEVEL_FATAL 0
#define AB_LOG_LEVEL_ERROR 1
#define AB_LOG_LEVEL_WARN 2
#define AB_LOG_LEVEL_INFO 3

	static void reset_console()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int background = 0;
		int foreground = 15;
		SetConsoleTextAttribute(hConsole, foreground + background * 16);
	}

	static void setup_console(int level)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int background;
		int foreground;
			
		switch (level)
		{
		case (AB_LOG_LEVEL_FATAL):
			foreground = 15;
			background = 12;
			SetConsoleTextAttribute(hConsole, foreground + background * 16);
			break;
		case (AB_LOG_LEVEL_ERROR):
			foreground = 12;
			background = 0;
			SetConsoleTextAttribute(hConsole, foreground + background * 16);
			break;
		case (AB_LOG_LEVEL_WARN):
			foreground = 14;
			background = 0;
			SetConsoleTextAttribute(hConsole, foreground + background * 16);
			break;
		case (AB_LOG_LEVEL_INFO):
			break;
		}
	}

#define AB_FATAL(x) do { setup_console(AB_LOG_LEVEL_FATAL); std::cout << "ABLAZE:     " << x << "    " << std::endl; reset_console(); } while(0)
#define AB_ERROR(x) do { setup_console(AB_LOG_LEVEL_ERROR); std::cout << "ABLAZE:     " << x << "    " << std::endl; reset_console(); } while(0)
#define AB_WARN(x) do { setup_console(AB_LOG_LEVEL_WARN); std::cout << "ABLAZE:     " << x << "    " << std::endl; reset_console(); } while(0)
#define AB_INFO(x) do { setup_console(AB_LOG_LEVEL_INFO); std::cout << "ABLAZE:     " << x << "    " << std::endl; reset_console(); } while(0)

#define AB_ASSERT(x, m) \
		if (!(x)) { \
			AB_FATAL("*************************"); \
			AB_FATAL("    ASSERTION FAILED!    "); \
			AB_FATAL("*************************"); \
			AB_FATAL(m); \
		}

}

