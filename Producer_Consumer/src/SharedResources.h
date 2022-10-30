#pragma once

#include <semaphore>
#include <mutex>

#include "Buffer.h"

enum class State
{
	IDLE,
	WORKING
};

struct SharedResources
{
	Buffer<char, 25> BufferPC;
	State ProducerState = State::IDLE;
	State ConsumerState = State::IDLE;
	std::mutex PCMutex;
	std::mutex CoutMutex;
};