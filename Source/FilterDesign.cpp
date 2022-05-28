#include "FilterDesign.h"

///////// THIS WHOLE SHIT SHOULD BE REWRITTEN


FilterCoef GetButterworthCoef(FilterTypeEnum filtType, FilterSlopeEnum slope, double SampleRate, double Cutoff, double qResonance, unsigned int order = 1);
//FilterCoef GetButterworthLowpass(FilterTypeEnum filtType, double SampleRate, double Cutoff, double qResonance);
//FilterCoef GetButterworthHighpass(FilterTypeEnum filtType, double SampleRate, double Cutoff, double qResonance);


FilterCoef FilterDesign::GetCoef(FilterEquationEnum equation, FilterTypeEnum filtType, 
	FilterSlopeEnum slope, double SampleRate, double Cutoff, double qResonance, unsigned int order)
{
	switch (equation)
	{

	case FilterEquationEnum::BUTTERWORTH:
		return GetButterworthCoef(filtType, slope, SampleRate, Cutoff, qResonance);
		break;

	default:
		return GetButterworthCoef(filtType, slope, SampleRate, Cutoff, qResonance);
		break;
	}
}

FilterCoef FilterDesign::GetCoef(FilterParameters params, unsigned int order)
{
	switch (params.getEquation())
	{

	case FilterEquationEnum::BUTTERWORTH:
		return GetButterworthCoef(params.getFilterType(), params.getSlope(), params.getSampleRate(), params.getCutoff(), params.getResonance());
		break;

	default:
		return GetButterworthCoef(params.getFilterType(), params.getSlope(), params.getSampleRate(), params.getCutoff(), params.getResonance());
		break;
	}
}

FilterCoef GetButterworthCoef(FilterTypeEnum filtType, FilterSlopeEnum slope, double SampleRate, double Cutoff, double qResonance, unsigned int order)
{
	double w0 = 2 * M_PI * Cutoff / SampleRate;
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	//double A = std::pow(10, db / 40);
	double alpha;
	//CASCADE FILTER
	if (filtType == FLAT_LOWPASS || filtType == FLAT_HIGHPASS)
		alpha = sinW0 / (2 * std::cos((1 + (order * 2)) *  M_PI / (4 * (int)slope)));
	//RESONANT FILTER
	else
		alpha = sinW0 / (2 * qResonance);

	//double beta = std::pow(A, 0.5) / qResonance;
	double a0, a1, a2, b0, b1, b2;
	a0 = 1 / (1 + alpha); //Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	if (filtType == FLAT_LOWPASS || filtType == RESONANT_LOWPASS)
	{
		b0 = (a0 - a0 * cosW0) * 0.5;
		b1 = (a0 - a0 * cosW0);
	}
	else
	{
		b0 = (a0 + a0 * cosW0) * 0.5;
		b1 = -(a0 + a0 * cosW0);
	}
	b2 = b0;
	//Nomalized coef so that a0 = 1
	return FilterCoef(1, a1, a2, b0, b1, b2);
}