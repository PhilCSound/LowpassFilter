#pragma once


//Problem with this design and the design in IIRFilter is that its locked in to 2nd order Coef
//Could remedy this by going back to the double array design for coeficents.
class FilterCoef
{
public:
	FilterCoef();
	FilterCoef(double _a0, double _a1, double _a2, double _b0, double _b1, double _b2);
	
	//Member functions
	static FilterCoef GetBlankCoef();

	//Member Variables
	double a0, a1, a2, b0, b1, b2;

private:
};