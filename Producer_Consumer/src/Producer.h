#pragma once

#include <thread>

#include "SharedResources.h"

class Producer
{
public:
	Producer(SharedResources& resources);
	~Producer();

	void Produce();
	void ProducerProc();

	bool IsWorking() const noexcept;

private:
	std::thread m_ProducerTh;
	SharedResources& g_SharedResources;
};

