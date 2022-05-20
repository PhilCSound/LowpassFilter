/*
  ==============================================================================

    RingBuffer.h
    Created: 12 May 2022 7:42:11pm
    Author:  Phip

  ==============================================================================
*/


//NASTY BUGS if size 0 or 1, but at that point its not a ring buffer now is it?
#pragma once
#include <vector>

template <class Type>
class RingBuffer
{
public:
	RingBuffer();
	RingBuffer(unsigned int size = 128);
	const unsigned int getSize();
	Type at(unsigned int index);
	void insert(Type input);

private:
	unsigned int m_bufferSize = 128;
	unsigned int m_currentIndex = 0;
	unsigned int m_firstIndex = m_bufferSize - 1;
	std::vector<Type> m_buffer;

	//Private Function
	void IncrementIndex();

};

//Template Definitions

template <class Type>
RingBuffer<Type>::RingBuffer()
{
	m_buffer.reserve(m_bufferSize);
	m_buffer.resize(m_bufferSize);
}

template <class Type>
RingBuffer<Type>::RingBuffer(unsigned int size)
	: m_bufferSize(size), m_firstIndex(size - 1)
{
	m_buffer.reserve(m_bufferSize);
	m_buffer.resize(m_bufferSize);
}

template <class Type>
const unsigned int RingBuffer<Type>::getSize()
{
	return m_bufferSize;
}

template <class Type>
Type RingBuffer<Type>::at(unsigned int index)
{
	unsigned int accessIndex;
	if (index > m_firstIndex)
		accessIndex = (m_bufferSize - (index - m_firstIndex));
	else
		accessIndex = m_firstIndex - index;
	//This will return an exception when over m_bufferSize.
	return m_buffer.at(accessIndex);
}

template <class Type>
void RingBuffer<Type>::insert(Type input)
{
	m_buffer[m_currentIndex] = input;
	IncrementIndex();
}

template <class Type>
void RingBuffer<Type>::IncrementIndex()
{
	m_currentIndex++;
	m_firstIndex++;
	if (m_currentIndex >= m_bufferSize)
		m_currentIndex = 0;
	if (m_firstIndex >= m_bufferSize)
		m_firstIndex = 0;
}
