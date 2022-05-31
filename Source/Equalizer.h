/*
  ==============================================================================

    Equalizer.h
    Created: 25 May 2022 11:08:35pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "EQBand.h"
#include <vector>

class Equalizer
{
public:
	Equalizer();

	//Member Functions
	const bool isBandEnabled(unsigned int bandNumber);
	const FilterParameters getFilterParameters(unsigned int bandNumber);
	float process(float input);
	void setCutoff(unsigned int bandNumber, double cutoff);
	void setResonance(unsigned int bandNumber, double resonance);
	void setSlope(unsigned int bandNumber, FilterSlopeEnum slope);

private:
	//Member functions
	bool IsBandNumberValid(unsigned int);

	//Member Variables
	std::vector<EQBand> m_EqBands;
};