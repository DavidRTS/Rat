#include <RTHeader.h>
#include "Core/Engine.h"

int main()
{
	RTE_LOG_INFO("Booting up...");
	RTE_LOG_WARN("Logging test");
	RTE_LOG_ERROR("Logging test");

	if (!Engine::Init())
	{
		RTE_LOG_ERROR("Failed to initialized!");
		return -1;
	}

	RTI_LOG_INFO("Booting up...");
	RTI_LOG_WARN("Logging test");
	RTI_LOG_ERROR("Logging test");

	Engine::Run();
	Engine::Shutdown();

	RTE_LOG_INFO("Shutdown complete.");
	return 0;
}