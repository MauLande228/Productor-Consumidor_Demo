#pragma once

#include <iostream>
#include <Windows.h>

#define GREEN 10
#define BLUE 11

template<class _type, int SIZE = 1024>
class Buffer
{
public:
	Buffer();
	virtual ~Buffer() noexcept;

	void Write(_type item, uint32_t randint);
	void Read(uint32_t randint);

	void Print() noexcept;
	bool empty() const noexcept;
	bool full() const noexcept;
	uint32_t Beginning() const noexcept;
	int End() const noexcept;
	uint32_t Room() const noexcept;

private:
	_type m_Buffer[SIZE];

	uint32_t m_Beginning = 0;
	int m_End = -1;
	uint32_t m_Room;
	uint32_t m_ProductCounter = 0;
	
	bool m_bEmpty = true;
	bool m_bFull = false;

};

template<class _type, int SIZE>
inline Buffer<_type, SIZE>::Buffer()
{
	for (int i = 0; i < SIZE; i++)
	{
		m_Buffer[i] = '-';
	}
}

template<class _type, int SIZE>
inline Buffer<_type, SIZE>::~Buffer() noexcept
{
}

template<class _type, int SIZE>
inline void Buffer<_type, SIZE>::Write(_type item, uint32_t randint)
{
	auto beginWrite = m_End + 1;
	auto endWrite = m_End + randint;

	if (m_ProductCounter > SIZE) m_ProductCounter = SIZE;

	for (int i = beginWrite; i <= endWrite; i++)
	{
		int index = i % SIZE;
		m_Buffer[index] = item;
		m_ProductCounter++;
	}

	m_End = endWrite % SIZE;
}

template<class _type, int SIZE>
inline void Buffer<_type, SIZE>::Read(uint32_t randint)
{
	auto beginRead = m_Beginning;
	auto endRead = m_Beginning + randint - 1;
	int index;

	for (int i = beginRead; i <= endRead; i++)
	{
		index = i % SIZE;
		m_Buffer[index] = '-'; //This program is a demonstration of how consuming would look like. This is actually incorrect!
		m_ProductCounter--;
	}

	m_Beginning = index + 1;
}

template<class _type, int SIZE>
inline void Buffer<_type, SIZE>::Print() noexcept
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < SIZE; i++)
	{
		SetConsoleTextAttribute(hConsole, GREEN);
		std::cout << m_Buffer[i] << " ";
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, BLUE);
}

template<class _type, int SIZE>
inline bool Buffer<_type, SIZE>::empty() const noexcept
{
	return m_ProductCounter == 0;
}

template<class _type, int SIZE>
inline bool Buffer<_type, SIZE>::full() const noexcept
{
	return m_ProductCounter >= SIZE;
}

template<class _type, int SIZE>
inline uint32_t Buffer<_type, SIZE>::Beginning() const noexcept
{
	return m_Beginning;
}

template<class _type, int SIZE>
inline int Buffer<_type, SIZE>::End() const noexcept
{
	return m_End;
}

template<class _type, int SIZE>
inline uint32_t Buffer<_type, SIZE>::Room() const noexcept
{
	m_Room = SIZE - m_ProductCounter;
	return m_Room;
}
