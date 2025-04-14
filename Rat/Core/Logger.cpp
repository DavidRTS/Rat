#include "RTHeader.h"

namespace
{
	std::string ColorWrap(const std::string& message, const std::string& colorCode)
	{
		return colorCode + message + "\033[0m"; // reset color after message
	}

	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string RED = "\033[31m";
	const std::string CYAN = "\033[36m";
	const std::string RESET = "\033[0m";
}

void Logger::Log(const std::string& category, const std::string& message)
{
	std::cout << "[" << category << "] " << message << std::endl;
}

void Logger::Info(const std::string& category, const std::string& message)
{
	Log(category, ColorWrap("INFO: " + message, GREEN));
}

void Logger::Warn(const std::string& category, const std::string& message)
{
	Log(category, ColorWrap("WARNING: " + message, YELLOW));
}

void Logger::Error(const std::string& category, const std::string& message)
{
	Log(category, ColorWrap("ERROR: " + message, RED));
}