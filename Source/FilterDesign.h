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
	FilterCoef GetFirstOrderHighpass(FilterParameters& params);
	FilterCoef GetFirstOrderLowpass(FilterParameters& params);
	FilterCoef GetSecondOrderHighpass(FilterParameters& params);
	FilterCoef GetSecondOrderLowpass(FilterParameters& params);
	FilterCoef CascadeSecondOrderHighpass(FilterParameters& params, int cascadedNum = 0, unsigned int num2ndOrdFilter = 1);
	FilterCoef CascadeSecondOrderLowpass(FilterParameters& params, int cascadedNum = 0, unsigned int num2ndOrdFilter = 1);
	FilterCoef Cascade1stAnd2ndOrderHighpass(FilterParameters& params, int cascadedNum = 0, unsigned int numBiquads = 1);
	FilterCoef Cascade1stAnd2ndOrderLowpass(FilterParameters& params, int cascadedNum = 0, unsigned int numBiquads = 1);


	FilterCoef GetCoefs(FilterParameters& params);
}