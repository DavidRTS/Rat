#pragma once

class Engine
{
public:
	static bool Init();
	static bool IsRunning();
	static void Run();
	static void Shutdown();

private:
	static bool running;
};
