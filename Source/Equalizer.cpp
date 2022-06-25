/*
  ==============================================================================

    Equalizer.cpp
    Created: 25 May 2022 11:08:35pm
    Author:  Phip

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer()
{
	m_EqBands.reserve(8);
	m_EqBands.resize(8);

	m_EqBands[0].setParams(FilterParameters(RESONANT_HIGHPASS, 30, .707, 1.0));
	m_EqBands[1].setParams(FilterParameters(PEAKING, 200, .707, 2.818)); //+6db
	m_EqBands[2].setParams(FilterParameters(ALLPASS, 500, .707, 1.0), false);
	m_EqBands[3].setParams(FilterParameters(ALLPASS, 1000, .707, 1.0), false);
	m_EqBands[4].setParams(FilterParameters(ALLPASS, 2500, .707, 1.0), false);
	m_EqBands[5].setParams(FilterParameters(ALLPASS, 5000, .707, 1.0), false);
	m_EqBands[6].setParams(FilterParameters(ALLPASS, 10000, .707, 1.0), false);
	m_EqBands[7].setParams(FilterParameters(FLAT_LOWPASS, 20000, .707, 1.0, 44100, FOURTY_EIGHT_DB));
}

const bool Equalizer::isBandEnabled(unsigned int bandNumber)
{
	if (IsBandNumberValid(bandNumber))
		return m_EqBands[bandNumber].isEnabled();
	return false;
}

//Make sure you call this with a valid bandNumber this will crash if not
const FilterParameters Equalizer::getFilterParameters(unsigned int bandNumber)
{
	//Not going to check for out of bounds here, as if I return dummy Params
	//People might be confused when something goes wrong, therefore if I crash via exceptions
	// We will better know something is wrong.
	return m_EqBands.at(bandNumber).getFilterParams();
}

float Equalizer::process(float input)
{
	float output = input;
	for (auto& band : m_EqBands)
		output = band.process(output);
	return output;
}

void Equalizer::setCutoff(unsigned int bandNumber, double cutoff)
{
	if (IsBandNumberValid(bandNumber))
		m_EqBands[bandNumber].setCutoff(cutoff);
}

void Equalizer::setResonance(unsigned int bandNumber, double resonance)
{
	if (IsBandNumberValid(bandNumber))
		m_EqBands[bandNumber].setResonance(resonance);
}

void Equalizer::setSlope(unsigned int bandNumber, FilterSlopeEnum slope)
{
	if (IsBandNumberValid(bandNumber))
		m_EqBands[bandNumber].setSlope(slope);
}

bool Equalizer::IsBandNumberValid(unsigned int bandNum)
{
	if (bandNum < m_EqBands.size())
		return true;
	return false;
}
