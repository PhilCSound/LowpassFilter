#include "FilterDesign.h"

FilterCoef FilterDesign::GetFirstOrderHighpass(FilterParameters& params)
{
	double w0 = M_PI * params.getCutoff() / params.getSampleRate();
	double a1, b0;
	double K = std::tan(w0);
	b0 = 1 / (1 + K);	//alpha is 1+K b0 = 1/alpha. 
	a1 = -(1 - K) * b0; //since b0 = 1/alpha instead of divide by alpha we multiply
	return FilterCoef(1, a1, 0.0f, b0, -b0, 0.0f);
}

FilterCoef FilterDesign::GetFirstOrderLowpass(FilterParameters& params)
{
	double w0 = M_PI * params.getCutoff() / params.getSampleRate();
	double a1, b0;
	double K = std::tan(w0);
	b0 = 1 / (1 + K);	//alpha is 1+K b0 = 1/alpha. 
	a1 = -(1 - K) * b0; //since b0 = 1/alpha instead of divide by alpha we multiply
	return FilterCoef(1, a1, 0.0f, b0, b0, 0.0f);
}

FilterCoef FilterDesign::GetSecondOrderHighpass(FilterParameters& params)
{
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 + a0 * cosW0) * 0.5;
	b1 = -(a0 + a0 * cosW0);	//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::GetSecondOrderLowpass(FilterParameters& params)
{
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 - a0 * cosW0) * 0.5;
	b1 = (a0 - a0 * cosW0);		//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::GetSecondOrderPeaking(FilterParameters & params)
{
	//params.getGainFactor() is in form A = 10^(db/40)
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double A = params.getGainFactor();
	double a0, a2, b0, b1, b2;
	a0 = 1 / (1 + alpha / A);

	b0 = (1 + alpha * A) * a0;
	b1 = -2 * cosW0 * a0;
	b2 = (1 - alpha * A) * a0;
	a2 = (1 - alpha / A) * a0;
	return FilterCoef(1, b1, a2, b0, b1, b2); // a1 = b1
}

FilterCoef FilterDesign::GetSecondOrderAllpass(FilterParameters & params)
{
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double a0, a1, a2;	//b2 and a0 = 1, a1 = b1, b0 = a2
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = -2 * cosW0 * a0;
	a2 = (1 - alpha) * a0;
	return FilterCoef(1, a1, a2, a2, a1, 1); 
}

FilterCoef FilterDesign::GetLowShelf(FilterParameters & params)
{
	//params.getGainFactor() is in form A = 10^(db/40)
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double A = params.getGainFactor();
	double B = sqrt(A) / params.getResonance();

	double a0, a1, a2, b0, b1, b2;
	a0 = 1 / ((A + 1) + ((A - 1) * cosW0) + (B * sinW0));
	a1 = -2 * ((A - 1) + ((A + 1) * cosW0)) * a0;
	a2 = ((A + 1) + ((A - 1) * cosW0) - (B * sinW0)) * a0;
	b0 = A * ((A + 1) - ((A - 1) * cosW0) + (B * sinW0)) * a0;
	b1 = 2 * A * ((A - 1) - ((A + 1) * cosW0)) * a0;
	b2 = A * ((A + 1) - ((A - 1) * cosW0) - (B * sinW0)) * a0;

	return FilterCoef(1, a1, a2, b0, b1, b2);
}

FilterCoef FilterDesign::GetHighShelf(FilterParameters & params)
{
	//params.getGainFactor() is in form A = 10^(db/40)
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * params.getResonance());
	double A = params.getGainFactor();
	double B = sqrt(A) / params.getResonance();

	double a0, a1, a2, b0, b1, b2;
	a0 = 1 / ((A + 1) - ((A - 1) * cosW0) + (B * sinW0));
	a1 = 2 * ((A - 1) - ((A + 1) * cosW0)) * a0;
	a2 = ((A + 1) - ((A - 1) * cosW0) - (B * sinW0)) * a0;
	b0 = A * ((A + 1) + ((A - 1) * cosW0) + (B * sinW0)) * a0;
	b1 = -2 * A * ((A - 1) + ((A + 1) * cosW0)) * a0;
	b2 = A * ((A + 1) + ((A - 1) * cosW0) - (B * sinW0)) * a0;

	return FilterCoef(1, a1, a2, b0, b1, b2);
}

//Returns coefs for 12/24/36/48db flat filters
//Cascaded num = index of filter, num2ndOrder is max num biquads cascading ex: 48db is 4 biquads
FilterCoef FilterDesign::CascadeSecondOrderHighpass(FilterParameters& params, int cascadedNum, unsigned int num2ndOrdFilter)
{
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * std::cos((1 + (cascadedNum * 2)) *  M_PI / (4 * num2ndOrdFilter)));
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 + a0 * cosW0) * 0.5;
	b1 = -(a0 + a0 * cosW0);	//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::CascadeSecondOrderLowpass(FilterParameters& params, int cascadedNum, unsigned int num2ndOrdFilter)
{
	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alphaTheta = (1 + (cascadedNum * 2)) *  M_PI / (4 * num2ndOrdFilter);
	double alpha = sinW0 / (2 * std::cos(alphaTheta));
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 - a0 * cosW0) * 0.5;
	b1 = (a0 - a0 * cosW0);		//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::Cascade1stAnd2ndOrderHighpass(FilterParameters& params, int cascadedNum, unsigned int numBiquads)
{
	if (!cascadedNum)	//The first filter in a 18/30/42 filter is a first order filter
		return GetFirstOrderHighpass(params);

	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alphaTheta = cascadedNum * M_PI / (2 * numBiquads - 1);
	double alpha = sinW0 / (2 * std::cos(alphaTheta));
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 + a0 * cosW0) * 0.5;
	b1 = -(a0 + a0 * cosW0);	//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::Cascade1stAnd2ndOrderLowpass(FilterParameters& params, int cascadedNum, unsigned int numBiquads)
{
	if (!cascadedNum)	//The first filter in a 18/30/42 filter is a first order filter
		return GetFirstOrderHighpass(params);

	double w0 = 2 * M_PI * params.getCutoff() / params.getSampleRate();
	double sinW0 = std::sin(w0);
	double cosW0 = std::cos(w0);
	double alpha = sinW0 / (2 * std::cos(cascadedNum *  M_PI / (2 * numBiquads - 1)));
	double a0, a1, a2, b0, b1;	//B2 = b0, so
	a0 = 1 / (1 + alpha);		//Did reciprical so I can multiply instead of divide
	a1 = (-2 * cosW0) * a0;
	a2 = (1 - alpha) * a0;
	b0 = (a0 - a0 * cosW0) * 0.5;
	b1 = (a0 - a0 * cosW0);		//b2 = b0 below.
	return FilterCoef(1, a1, a2, b0, b1, b0);
}

FilterCoef FilterDesign::GetCoefs(FilterParameters& params)
{
	switch (params.getFilterType())
	{
	case RESONANT_LOWPASS:
		return GetSecondOrderLowpass(params);

	case RESONANT_HIGHPASS:
		return GetSecondOrderHighpass(params);

	case ALLPASS:
		return GetSecondOrderAllpass(params);

	case PEAKING:
		return GetSecondOrderPeaking(params);

	case HIGHSHELF:
		return GetHighShelf(params);
	
	case LOWSHELF:
		return GetLowShelf(params);

	default:
		return GetSecondOrderLowpass(params);
	}
}