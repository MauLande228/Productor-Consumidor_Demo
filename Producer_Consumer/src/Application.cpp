#include "Application.h"
#include "Random.h"

void Application::Run() noexcept
{
	Random::Init();

	SharedResources sharedResources = SharedResources();

	Producer producer(sharedResources);
	Consumer consumer(sharedResources);

	while (true)
	{
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(1s);
	}
}
