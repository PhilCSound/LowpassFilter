/*
  ==============================================================================

    FilterSlopeEnum.h
    Created: 25 May 2022 11:37:08pm
    Author:  Phip

  ==============================================================================
*/

#pragma once

//For now we are only supporting multiples of 12db/oct
//We can go back and redesign the FilterCoef/IIR filter class to support
//6/18/30/36 db slopes at another time. 
enum FilterSlopeEnum
{
	TWELVE_DB = 1, TWENTY_FOUR_DB, THIRTY_SIX_DB, FOURTY_EIGHT_DB   
};