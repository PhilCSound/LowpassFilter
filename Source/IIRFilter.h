/*
  ==============================================================================

    IIRFilter.h
    Created: 14 May 2022 9:59:20pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
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
	float m_prevIn;
	float m_prevIn1;
	float m_prevOut;
	float m_prevOut1;
};

//Template Definitions
template <class FloatType>
IIRFilter<FloatType>::IIRFilter()
	: m_prevIn(0.0f), m_prevIn1(0.0f), m_prevOut(0.0f), m_prevOut1(0.0f)
{
}

template <class FloatType>
IIRFilter<FloatType>::IIRFilter(FilterCoef _coef)
	: m_prevIn(0.0f), m_prevIn1(0.0f), m_prevOut(0.0f), m_prevOut1(0.0f), coef(_coef)
{
}


template <class FloatType>
FloatType IIRFilter<FloatType>::calculate(FloatType input)
{
	FloatType output = 0.0;
	
	//Process the sample
	output = coef.b0 * input + coef.b1 * m_prevIn + coef.b2 * m_prevIn1
		 - coef.a1 * m_prevOut - coef.a2 * m_prevOut1;

	//Update prev Vars
	m_prevIn1 = m_prevIn;
	m_prevIn = input;
	m_prevOut1 = m_prevOut;
	m_prevOut = output;

	return output;
}
