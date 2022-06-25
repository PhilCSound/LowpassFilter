/*
  ==============================================================================

    FilterParameters.h
    Created: 26 May 2022 12:17:20am
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "FilterEquationEnum.h"
#include "FilterSlopeEnum.h"
#include "FilterTypeEnum.h"
#define _USE_MATH_DEFINES
#include <cmath>

class FilterParameters
{

public:
	FilterParameters();
	FilterParameters(FilterTypeEnum filtType, double Cutoff, double qResonance, 
		double gainFactor = 0.0, double SampleRate = 44100,
		FilterSlopeEnum slopeType = TWELVE_DB, FilterEquationEnum equation = BUTTERWORTH);

	const FilterEquationEnum getEquation();
	const double getGainFactor();
	const FilterTypeEnum getFilterType();
	const FilterSlopeEnum getSlope();
	const double getSampleRate();
	const double getCutoff();
	const double getResonance();
	bool isFlatFilter() const;
	void setEquation(FilterEquationEnum equation);
	void setGainFactor(double gainFactor);
	void setGainFactorInDecibels(double decibels);
	void setType(FilterTypeEnum type);
	void setSlope(FilterSlopeEnum slope);
	void setSampleRate(double sampleRate);
	void setCutoff(double cutoff);
	void setResonance(double q);

private:
	FilterTypeEnum m_Type;
	double m_Cutoff;
	double m_Q_Resonance;
	double m_GainFactor;
	double m_SampleRate;
	FilterSlopeEnum m_Slope;
	FilterEquationEnum m_Equation;
	
};