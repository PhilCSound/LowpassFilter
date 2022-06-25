/*
  ==============================================================================

    FilterParameters.cpp
    Created: 26 May 2022 12:17:20am
    Author:  Phip

  ==============================================================================
*/

#include "FilterParameters.h"

FilterParameters::FilterParameters()
	:	m_Type(ALLPASS),			m_Cutoff(1000),				m_Q_Resonance(.7071),
		m_GainFactor(0.0),			m_SampleRate(44100),
		m_Slope(TWELVE_DB),			m_Equation(BUTTERWORTH)
{
}

FilterParameters::FilterParameters(FilterTypeEnum filtType, double Cutoff, double qResonance,
	double gainFactor, double SampleRate, FilterSlopeEnum slopeType, FilterEquationEnum equation)
	:	m_Type(filtType),			m_Cutoff(Cutoff),			m_Q_Resonance(qResonance),
		m_GainFactor(gainFactor),	m_SampleRate(SampleRate),	
		m_Slope(slopeType),			m_Equation(equation)
{
}

const FilterEquationEnum FilterParameters::getEquation()
{
	return m_Equation;
}

const double FilterParameters::getGainFactor()
{
	return m_GainFactor;
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

bool FilterParameters::isFlatFilter() const
{
	return (m_Type == FLAT_HIGHPASS || m_Type == FLAT_LOWPASS);
}

void FilterParameters::setEquation(FilterEquationEnum equation)
{
	m_Equation = equation;
}

//gainFactor should already be in the form: 10^(db/40)
//if not in this form set Gainfactor with:
//setGainFactorInDecibels(double decibels);
void FilterParameters::setGainFactor(double gainFactor)
{
	m_GainFactor = gainFactor;
}

void FilterParameters::setGainFactorInDecibels(double decibels)
{
	m_GainFactor = std::pow(10, (decibels / 40));
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
