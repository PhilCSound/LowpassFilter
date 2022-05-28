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

class FilterParameters
{

public:
	FilterParameters();
	FilterParameters(FilterEquationEnum equation, FilterTypeEnum filtType,
		FilterSlopeEnum slopeType, double SampleRate, double Cutoff, double qResonance);

	const FilterEquationEnum getEquation();
	const FilterTypeEnum getFilterType();
	const FilterSlopeEnum getSlope();
	const double getSampleRate();
	const double getCutoff();
	const double getResonance();

	void setEquation(FilterEquationEnum equation);
	void setType(FilterTypeEnum type);
	void setSlope(FilterSlopeEnum slope);
	void setSampleRate(double sampleRate);
	void setCutoff(double cutoff);
	void setResonance(double q);

private:
	FilterEquationEnum m_Equation;
	FilterTypeEnum m_Type;
	FilterSlopeEnum m_Slope;
	double m_SampleRate;
	double m_Cutoff;
	double m_Q_Resonance;
	
};