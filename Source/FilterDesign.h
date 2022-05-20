/*
  ==============================================================================

    FilterDesign.h
    Created: 18 May 2022 1:12:00am
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "FilterCoef.h"
#include "FilterEquationEnum.h"
#include "FilterTypeEnum.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

namespace FilterDesign
{
	FilterCoef GetCoef(FilterEquationEnum equation, FilterTypeEnum filtType, 
		double SampleRate, double Cutoff, double qResonance);
	
}