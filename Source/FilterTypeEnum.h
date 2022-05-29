/*
  ==============================================================================

    FilterTypeEnum.h
    Created: 18 May 2022 1:08:10am
    Author:  Phip

  ==============================================================================
*/

#pragma once

////
//	Flat Low/Highpass are filters at which Q is locked to .7071 but can be cascaded for multiple slopes.
//	Resonant low/highpass are only 2nd order filters (12db/oct) but have a variable Q which can be changed.
//	Allpass is a filter that does nothing, this is equal to default coef (0, 0, 0, 1, 0, 0)
////
enum FilterTypeEnum
{
	FLAT_LOWPASS, FLAT_HIGHPASS, RESONANT_LOWPASS, RESONANT_HIGHPASS, ALLPASS
};