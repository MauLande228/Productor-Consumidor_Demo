#pragma once

#include <thread>

#include "SharedResources.h"

class Consumer
{
public:
	Consumer(SharedResources& sharedResources);
	~Consumer();

	void Consume();
	void ConsumerProc();

	bool IsWorking() const noexcept;

private:
	std::thread m_ConsumerTh;
	SharedResources& g_SharedResources;
};

