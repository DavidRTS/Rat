#include "RTHeader.h"
#include "Core/Engine.h"

bool Engine::running = true; // Properly defined static member

bool Engine::Init()
{
	RTE_LOG_INFO("Initialized");
	return true;
}

void Engine::Run()
{
	while (running)
	{
		RTE_LOG_INFO("Running game loop...");
		running = false;
	}
}

void Engine::Shutdown()
{
	RTE_LOG_INFO("Shutting down.");
}

bool Engine::IsRunning()
{
	return running;
}
