/*
  ==============================================================================

    IIRFilter.h
    Created: 14 May 2022 9:59:20pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "RingBuffer.h"

template <class FloatType>
class IIRFilter
{
public:
	IIRFilter();

	FloatType calculate(FloatType input);
	const double AFilterCoeffecients[3] = { 0.5, 0.0, 0.0 };
	const double BFilterCoeffecients[3] = { 0.5, 0.0, 0.0 };

private:
	RingBuffer<FloatType> m_inputBuffer;
	RingBuffer<FloatType> m_outputBuffer;
};

//Template Definitions
template <class FloatType>
IIRFilter<FloatType>::IIRFilter()
	: m_inputBuffer(3), m_outputBuffer(3)
{
}

template <class FloatType>
FloatType IIRFilter<FloatType>::calculate(FloatType input)
{
	m_inputBuffer.insert(input);
	FloatType output = 0.0;
	for (int i = 0; i < m_inputBuffer.getSize(); i++)
	{
		output += AFilterCoeffecients[i] * m_inputBuffer.at(i) + BFilterCoeffecients[i] * m_outputBuffer.at(i);
	}
	m_outputBuffer.insert(output);
	//y[n] = ax[n] + (1-a) y[n-1],   0<a<1
	//Cutoff freq =	a / 1 - (1-a) * z^(-1)
	//A should equal apprx: 1-e^ (-freq)
	//Exact A is:
	// A = -y + sqrt(y^(2) + 2y)    where y =  1-cos(wc)  wc is cutoff in radians?
	return output;
}
