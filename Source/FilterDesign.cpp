#include "FilterDesign.h"

//This is a empty namespace, think of it as a private functions only this namespace can access
namespace
{
	FilterCoef GetBQDCoef(FilterTypeEnum filtType, double SampleRate, double Cutoff, double qResonance)
	{
		double w0 = 2 * M_PI * (Cutoff / SampleRate);
		double sinW0 = std::sin(w0);
		double cosW0 = std::cos(w0);
		//double A = std::pow(10, db / 40);
		double alpha = sinW0 / (2 * qResonance);
		//double beta = std::pow(A, 0.5) / qResonance;
		double a0, a1, a2, b0, b1, b2;
		a0 = 1 / (1 + alpha); //Did reciprical so I can multiply instead of divide
		a1 = (-2 * cosW0) * a0;
		a2 = (1 - alpha) * a0;
		if (filtType == FilterTypeEnum::LOWPASS)
		{
			b0 = (a0 - a0 * cosW0) * 0.5;
			b1 = (a0 - a0 * cosW0);
		}
		else
		{
			b0 = (1 + cosW0) * 0.5 * a0;
			b1 = -(1 + cosW0) * a0;
		}
		b2 = b0;
		//Nomalized coef so that a0 = 1
		return FilterCoef(1, a1, a2, b0, b1, b2);
	}
}


FilterCoef FilterDesign::GetCoef(FilterEquationEnum equation, FilterTypeEnum filtType, double SampleRate, double Cutoff, double qResonance)
{
	switch (equation)
	{
	case FilterEquationEnum::BQD_FILTER:
		return GetBQDCoef(filtType, SampleRate, Cutoff, qResonance);
		break;

	case FilterEquationEnum::BUTTERWORTH:
		//Return your equation here
		break;

	default:
		return GetBQDCoef(filtType, SampleRate, Cutoff, qResonance);
		break;
	}
}

