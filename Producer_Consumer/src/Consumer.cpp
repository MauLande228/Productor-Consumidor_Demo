#include "Consumer.h"
#include "Random.h"

#include <chrono>

Consumer::Consumer(SharedResources& sharedResources) :
	g_SharedResources(sharedResources)
{
	m_ConsumerTh = std::thread(&Consumer::ConsumerProc, this);
}

Consumer::~Consumer()
{
	if (m_ConsumerTh.joinable())
		m_ConsumerTh.join();
}

void Consumer::Consume()
{
	g_SharedResources.PCMutex.lock();

	auto rcount = Random::RandInt(1, 4);
	g_SharedResources.BufferPC.Read(rcount);

	g_SharedResources.PCMutex.unlock();
}

void Consumer::ConsumerProc()
{
	while (true)
	{
		if (g_SharedResources.ProducerState == State::IDLE && !g_SharedResources.BufferPC.empty())
		{
			Consume();
			g_SharedResources.ConsumerState = State::WORKING;

			g_SharedResources.CoutMutex.lock();
			g_SharedResources.BufferPC.Print();
			std::cout << "Producer: idle" << "\t\t\t\tConsumer: working" << std::endl;
			g_SharedResources.CoutMutex.unlock();

			auto rtime = Random::RandInt(1, 4);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));

			g_SharedResources.ConsumerState = State::IDLE;

			rtime = Random::RandInt(2, 4);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));
		}
		else
		{
			g_SharedResources.CoutMutex.lock();
			std::cout << "Consumer attempted to produce but was rejected" << std::endl;
			g_SharedResources.CoutMutex.unlock();

			auto rtime = Random::RandInt(3, 5);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));
		}
	}
}

bool Consumer::IsWorking() const noexcept
{
	return false;
}
