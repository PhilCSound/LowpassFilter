/*
  ==============================================================================

    FilterCoef.cpp
    Created: 17 May 2022 9:30:16pm
    Author:  Phip

  ==============================================================================
*/

#include "FilterCoef.h"

//Changed to an initialization list, what this does is construct the doubles with a value of 0.0
FilterCoef::FilterCoef()
	: a0(0.0), a1(0.0), a2(0.0), b0(0.0), b1(0.0), b2(0.0)
{
}

//Changed to an initialization list
FilterCoef::FilterCoef(double _a0, double _a1, double _a2, double _b0, double _b1, double _b2)
	: a0(_a0), a1(_a1), a2(_a2), b0(_b0), b1(_b1), b2(_b2)
{
}
