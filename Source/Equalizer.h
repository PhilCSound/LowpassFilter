/*
  ==============================================================================

    Equalizer.h
    Created: 25 May 2022 11:08:35pm
    Author:  Phip

  ==============================================================================
*/

#pragma once
#include "EQBand.h"

class Equalizer
{
public:
	Equalizer();

	float process(float input);
	void setCutoff(double cutoff);

private:
	EQBand band1;
};