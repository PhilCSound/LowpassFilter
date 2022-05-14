/*
  ==============================================================================

    FIRFilter.h
    Created: 13 May 2022 1:59:03pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "RingBuffer.h"

template <class FloatType>
class FIRFilter
{
public:
	FIRFilter();

	FloatType calculate(FloatType input);
	const double FilterCoeffecients[10] = { 0.5, 0.0, 0.25, 0.0, 0.125, 0.0, 0.0625, 0.0, 0.0625, 0.0 };

private:
	RingBuffer<FloatType> m_buffer;
};

//Template Definitions
template <class FloatType>
FIRFilter<FloatType>::FIRFilter()
	: m_buffer(10)
{
}

template <class FloatType>
FloatType FIRFilter<FloatType>::calculate(FloatType input)
{
	m_buffer.insert(input);
	FloatType output = 0.0f;
	for (int i = 0; i < m_buffer.getSize(); i++)
	{
		output += m_buffer.at(i) * FilterCoeffecients[i];
	}
	return output;
}
