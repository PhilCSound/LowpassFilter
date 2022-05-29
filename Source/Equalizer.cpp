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

	m_EqBands[0].setParams(FilterParameters(BUTTERWORTH, RESONANT_HIGHPASS, TWELVE_DB, 44100, 30, .7071));
	m_EqBands[1].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 200, .7071), false);
	m_EqBands[2].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 500, .7071), false);
	m_EqBands[3].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 1000, .7071), false);
	m_EqBands[4].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 5000, .7071), false);
	m_EqBands[5].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 8000, .7071), false);
	m_EqBands[6].setParams(FilterParameters(BUTTERWORTH, ALLPASS, TWELVE_DB, 44100, 10000, .7071), false);
	m_EqBands[7].setParams(FilterParameters(BUTTERWORTH, FLAT_LOWPASS, FOURTY_EIGHT_DB, 44100, 20000, .7071));
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

bool Equalizer::IsBandNumberValid(unsigned int bandNum)
{
	if (bandNum < m_EqBands.size())
		return true;
	return false;
}
