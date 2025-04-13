#include "Engine.h"
#include "RTHeader.h"
#include <iostream>

int main()
{
	Logger::Info("Engine", "Booting up...");

	if (!Engine::Init())
	{
		Logger::Error("Engine", "Failed to initialized!");
		return -1;
	}

	Engine::Run();
	Engine::Shutdown();

	Logger::Info("Engine", "Shutdown complete.");
	return 0;
}