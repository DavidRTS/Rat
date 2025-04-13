#pragma once
#include "RTHeader.h"

class Logger
{
public :
	static void Log(const std::string& category, const std::string& message);
	static void Info(const std::string& category, const std::string& message);
	static void Warning(const std::string& category, const std::string& message);
	static void Error(const std::string& category, const std::string& message);
};

