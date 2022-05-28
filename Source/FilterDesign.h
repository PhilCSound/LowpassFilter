/*
  ==============================================================================

    FilterDesign.h
    Created: 18 May 2022 1:12:00am
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "FilterParameters.h"
#include "FilterCoef.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

namespace FilterDesign
{

	//Gets coef order = cascaded filter order.
	FilterCoef GetCoef(FilterEquationEnum equation, FilterTypeEnum filtType, FilterSlopeEnum slope,
		double SampleRate, double Cutoff, double qResonance, unsigned int order = 1);
	FilterCoef GetCoef(FilterParameters params, unsigned int order = 1);
}