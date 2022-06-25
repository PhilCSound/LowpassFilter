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
#include <algorithm>

namespace FilterDesign
{
	FilterCoef GetFirstOrderHighpass(FilterParameters& params);
	FilterCoef GetFirstOrderLowpass(FilterParameters& params);
	FilterCoef GetSecondOrderHighpass(FilterParameters& params);
	FilterCoef GetSecondOrderLowpass(FilterParameters& params);
	FilterCoef GetSecondOrderPeaking(FilterParameters& params);
	FilterCoef GetSecondOrderAllpass(FilterParameters& params);
	FilterCoef GetLowShelf(FilterParameters& params);
	FilterCoef GetHighShelf(FilterParameters& params);
	FilterCoef CascadeSecondOrderHighpass(FilterParameters& params, int cascadedNum = 0, unsigned int num2ndOrdFilter = 1);
	FilterCoef CascadeSecondOrderLowpass(FilterParameters& params, int cascadedNum = 0, unsigned int num2ndOrdFilter = 1);
	FilterCoef Cascade1stAnd2ndOrderHighpass(FilterParameters& params, int cascadedNum = 0, unsigned int numBiquads = 1);
	FilterCoef Cascade1stAnd2ndOrderLowpass(FilterParameters& params, int cascadedNum = 0, unsigned int numBiquads = 1);


	FilterCoef GetCoefs(FilterParameters& params);
}