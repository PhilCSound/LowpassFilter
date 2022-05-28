/*
  ==============================================================================

    FilterParameters.cpp
    Created: 26 May 2022 12:17:20am
    Author:  Phip

  ==============================================================================
*/

#include "FilterParameters.h"

FilterParameters::FilterParameters()
	:	m_Equation(BUTTERWORTH), m_Type(RESONANT_LOWPASS), m_Slope(TWELVE_DB),
		m_SampleRate(44100), m_Cutoff(2000), m_Q_Resonance(.7071)
{
}

FilterParameters::FilterParameters(FilterEquationEnum equation, FilterTypeEnum filtType,
	FilterSlopeEnum slopeType, double SampleRate, double Cutoff, double qResonance)
	:	m_Equation(equation),		m_Type(filtType), m_Slope(slopeType), 
		m_SampleRate(SampleRate),	m_Cutoff(Cutoff), m_Q_Resonance(qResonance)
{
}

const FilterEquationEnum FilterParameters::getEquation()
{
	return m_Equation;
}

const FilterTypeEnum FilterParameters::getFilterType()
{
	return m_Type;
}

const FilterSlopeEnum FilterParameters::getSlope()
{
	return m_Slope;
}

const double FilterParameters::getSampleRate()
{
	return m_SampleRate;
}

const double FilterParameters::getCutoff()
{
	return m_Cutoff;
}

const double FilterParameters::getResonance()
{
	return m_Q_Resonance;
}

void FilterParameters::setEquation(FilterEquationEnum equation)
{
	m_Equation = equation;
}

void FilterParameters::setType(FilterTypeEnum type)
{
	m_Type = type;
}

void FilterParameters::setSlope(FilterSlopeEnum slope)
{
	m_Slope = slope;
}

void FilterParameters::setSampleRate(double sampleRate)
{
	m_SampleRate = sampleRate;
}

void FilterParameters::setCutoff(double cutoff)
{
	m_Cutoff = cutoff;
}

void FilterParameters::setResonance(double q)
{
	m_Q_Resonance = q;
}
