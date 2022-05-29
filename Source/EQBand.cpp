/*
  ==============================================================================

    EQBand.cpp
    Created: 25 May 2022 11:06:39pm
    Author:  Phip

  ==============================================================================
*/

#include "EQBand.h"

EQBand::EQBand(FilterEquationEnum equation, FilterTypeEnum filtType, FilterSlopeEnum slope,
	double SampleRate, double Cutoff, double qResonance, bool enabled)
	:	m_Parameters(equation, filtType, slope, SampleRate, Cutoff, qResonance),
		m_IsEnabled(enabled)
{
	m_CascadedFilters.reserve(4);
	m_CascadedFilters.resize(4);
	updateCoefs();
}

EQBand::EQBand(FilterParameters params, bool enabled)
	: m_Parameters(params),
	m_IsEnabled(enabled)
{
	m_CascadedFilters.reserve(4);
	m_CascadedFilters.resize(4);
	updateCoefs();
}

const FilterParameters EQBand::getFilterParams()
{
	return m_Parameters;
}

const bool EQBand::isEnabled()
{
	return m_IsEnabled;
}

void EQBand::setCutoff(double cutoff)
{
	m_Parameters.setCutoff(cutoff);
	updateCoefs();
}

void EQBand::setEnabled(bool enabled)
{
	m_IsEnabled = enabled;
}

void EQBand::setParams(FilterParameters params, bool enabled)
{
	m_Parameters = params;
	m_IsEnabled = enabled;
	updateCoefs();
}

void EQBand::setResonance(double resonance)
{
	m_Parameters.setResonance(resonance);
	//If its a flat filter then we dont have to calculate resonance
	FilterTypeEnum type = m_Parameters.getFilterType();
	if (type == FLAT_LOWPASS || type == FLAT_HIGHPASS)
		return;
	createResonantSlope();
}

void EQBand::setSlope(FilterSlopeEnum slope)
{
	m_Parameters.setSlope(slope);
	//We should check to see if this is a flat filter if so then we need to
	//Recalculate the coef's
	FilterTypeEnum type = m_Parameters.getFilterType();
	if (type == FLAT_LOWPASS || type == FLAT_HIGHPASS)
		createFlatSlope();
}

void EQBand::setType(FilterTypeEnum type)
{
	if (m_Parameters.getFilterType() == type)
		return;
	m_Parameters.setType(type);
	updateCoefs();
}

float EQBand::process(float input)
{
	if (!m_IsEnabled)
		return input;

	float output = input;
	
	for (int i = 0; i < m_Parameters.getSlope(); i++)
		output = m_CascadedFilters[i].calculate(output);
	
	return output;
}

void EQBand::updateCoefs()
{
	FilterTypeEnum type = m_Parameters.getFilterType();
	//Flat lowpass is only the first filter
	if (type == FLAT_LOWPASS || type == FLAT_HIGHPASS)
		createFlatSlope();
	else
		createResonantSlope();
}

void EQBand::createResonantSlope()
{
	//Flat filters are only one biquad so we set all to blank aside from the first
	m_CascadedFilters.at(0).coef = FilterDesign::GetCoef(m_Parameters);
	for (int i = 1; i < m_CascadedFilters.size(); i++)
		m_CascadedFilters.at(i).coef = FilterCoef::GetBlankCoef();
}

void EQBand::createFlatSlope()
{
	for (int i = 0; i < m_CascadedFilters.size(); i++)
	{
		if (i < (int)m_Parameters.getSlope())
			m_CascadedFilters.at(i).coef = FilterDesign::GetCoef(m_Parameters, i);
		else
			m_CascadedFilters.at(i).coef = FilterCoef::GetBlankCoef();
	}

}
