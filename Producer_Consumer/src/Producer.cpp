#include "Producer.h"
#include "Random.h"

#include <chrono>

Producer::Producer(SharedResources& resources) :
	g_SharedResources(resources)
{
	m_ProducerTh = std::thread(&Producer::ProducerProc, this);
}

Producer::~Producer()
{
	if (m_ProducerTh.joinable())
		m_ProducerTh.join();
}

void Producer::Produce()
{
	g_SharedResources.PCMutex.lock();

	auto rcount = Random::RandInt(1, 5);
	g_SharedResources.BufferPC.Write('*', rcount);

	g_SharedResources.PCMutex.unlock();
}

void Producer::ProducerProc()
{
	while (true)
	{
		if (g_SharedResources.ConsumerState == State::IDLE && !g_SharedResources.BufferPC.full())
		{
			Produce();
			g_SharedResources.ProducerState = State::WORKING;

			g_SharedResources.CoutMutex.lock();
			g_SharedResources.BufferPC.Print();
			std::cout << "Producer: working" << "\t\t\t\tConsumer: idle" << std::endl;
			g_SharedResources.CoutMutex.unlock();

			auto rtime = Random::RandInt(1, 4);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));
			
			g_SharedResources.ProducerState = State::IDLE;

			rtime = Random::RandInt(2, 4);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));
		}
		else
		{
			g_SharedResources.CoutMutex.lock();
			std::cout << "Producer attempted to produce but was rejected" << std::endl;
			g_SharedResources.CoutMutex.unlock();

			auto rtime = Random::RandInt(3, 5);
			std::this_thread::sleep_for(std::chrono::seconds(rtime));
		}
	}
}

bool Producer::IsWorking() const noexcept
{
	return g_SharedResources.ProducerState == State::WORKING;
}
