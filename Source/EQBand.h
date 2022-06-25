/*
  ==============================================================================

    EQBand.h
    Created: 25 May 2022 11:06:39pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "IIRFilter.h"
#include "FilterDesign.h"
#include <vector>

class EQBand
{

public:
	EQBand();
	EQBand(FilterTypeEnum filtType, double Cutoff, double qResonance,
		double gainFactor = 0.0, double SampleRate = 44100,
		FilterSlopeEnum slopeType = TWELVE_DB, FilterEquationEnum equation = BUTTERWORTH,
		bool enabled = true);
	
	EQBand(FilterParameters params, bool enabled = true);


	const FilterParameters getFilterParams();
	const bool isEnabled();
	void setCutoff(double cutoff);
	void setEnabled(bool enabled);
	void setParams(FilterParameters params, bool enabled = true);
	void setResonance(double resonance);
	void setSlope(FilterSlopeEnum slope);
	void setType(FilterTypeEnum type);
	float process(float input);

private:
	//Member Functions
	void updateCoefs();
	void createCascadedSlope(bool isLowpass = true);
	void createResonantSlope();

	//Member Variables
	bool m_IsEnabled = true;
	unsigned int m_numOfBiquads = 1;
	FilterParameters m_Parameters;
	std::vector<IIRFilter<float>> m_CascadedFilters;

};