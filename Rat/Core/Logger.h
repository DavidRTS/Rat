#pragma once

class Logger
{
public :
	static void Log(const std::string& category, const std::string& message);
	static void Info(const std::string& category, const std::string& message);
	static void Warn(const std::string& category, const std::string& message);
	static void Error(const std::string& category, const std::string& message);
};

#define RT_LOG_INFO(category, message)    Logger::Info(category, message)
#define RT_LOG_WARN(category, message)    Logger::Warn(category, message)
#define RT_LOG_ERROR(category, message)   Logger::Error(category, message)

#define RTE_LOG_INFO(message)    Logger::Info("Engine", message)
#define RTE_LOG_WARN(message)    Logger::Warn("Engine", message)
#define RTE_LOG_ERROR(message)   Logger::Error("Engine", message)

#define RTI_LOG_INFO(message)    Logger::Info("Interactor", message)
#define RTI_LOG_WARN(message)    Logger::Warn("Interactor", message)
#define RTI_LOG_ERROR(message)   Logger::Error("Interactor", message)