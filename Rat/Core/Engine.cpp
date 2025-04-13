#include "Engine.h"
#include "RTHeader.h"
#include <iostream>

bool Engine::running = true; // Properly defined static member

bool Engine::Init()
{
	Logger::Info("Engine", "Initialized!");
	return true;
}

void Engine::Run()
{
	while (running)
	{
		Logger::Info("Engine", "Running game loop...");
		running = false;
	}
}

void Engine::Shutdown()
{
	Logger::Info("Engine", "Shutting down.");
}

bool Engine::IsRunning()
{
	return running;
}
