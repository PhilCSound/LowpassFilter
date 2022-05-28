/*
  ==============================================================================

    Equalizer.cpp
    Created: 25 May 2022 11:08:35pm
    Author:  Phip

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer()
	: band1(FilterParameters(BUTTERWORTH, FLAT_LOWPASS, FOURTY_EIGHT_DB, 44100, 15000, .7071))
{
}

float Equalizer::process(float input)
{
	return band1.process(input);
}

void Equalizer::setCutoff(double cutoff)
{
	band1.setCutoff(cutoff);
}
