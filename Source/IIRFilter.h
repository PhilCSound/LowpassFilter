/*
  ==============================================================================

    IIRFilter.h
    Created: 14 May 2022 9:59:20pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "RingBuffer.h"
#include "FilterCoef.h"

template <class FloatType>
class IIRFilter
{
public:
	//Functions
	IIRFilter();
	IIRFilter(FilterCoef _coef);
	FloatType calculate(FloatType input);
	
	//Varibles
	FilterCoef coef;
	int side;
	

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
IIRFilter<FloatType>::IIRFilter(FilterCoef _coef)
	: m_inputBuffer(3), m_outputBuffer(3)
{
	coef = _coef;
}


template <class FloatType>
FloatType IIRFilter<FloatType>::calculate(FloatType input)
{
	m_inputBuffer.insert(input);
	FloatType output = 0.0;
	
	//This was the old process, I like it cause it can support multiple orders. Keeping for if we change design

	//for (int i = 0; i < m_inputBuffer.getSize(); i++)
	//	output += AFilterCoeffecients[i] * m_inputBuffer.at(i) + BFilterCoeffecients[i] * m_outputBuffer.at(i);

	//Slightly Faster than above, at the cost of flexibility, this filter can only be a 2nd degree filter now.
	output = coef.b0 * m_inputBuffer.at(0) + coef.b1 * m_inputBuffer.at(1) + coef.b2 * m_inputBuffer.at(2)
		 - coef.a1 * m_outputBuffer.at(0) - coef.a2 * m_outputBuffer.at(1);

	m_outputBuffer.insert(output);
	//y[n] = ax[n] + (1-a) y[n-1],   0<a<1
	//Cutoff freq =	a / 1 - (1-a) * z^(-1)
	//A should equal apprx: 1-e^ (-freq)
	//Exact A is:
	// A = -y + sqrt(y^(2) + 2y)    where y =  1-cos(wc)  wc is cutoff in radians?
	return output;
}
