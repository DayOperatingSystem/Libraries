#include "math.h"

#define EULER 2.718281828459045235360287471352662497

double floor(double x)
{
	/// FIXME: Real implementation!
	return ((long) x);
}

double pow(double b, double e)
{
	return exp(log(b) * e);
}

double logn(double x, double b)
{
	return log(x) / log(b);
}

double log10(double x)
{
	return log(x) / 2.302585092994045684017991454684364207601101488628772976033; // log(x) / log(10)
}

double exp(double x)
{
	if(x == 0.0) return 1.0;
	if(x == 1.0) return EULER;

	const unsigned int iterations = 100;
	double sum = 1.0f;
	for(int i = iterations; i > 0; i--)
		sum = 1.0 + x * sum / (double) i;

	return sum;}



double ldexp(double x, int exp)
{
	return __builtin_ldexp(x, exp);
}

double ceil(double x)
{
	return __builtin_ceil(x);
}

double frexp(double x, int* exp)
{
	return __builtin_frexp(x, exp);
}

double atan(double x)
{
	return __builtin_atan(x);
}

double cosh(double x)
{
	return __builtin_cosh(x);
}

double fabs(double x)
{
	return __builtin_fabs(x);
}

double modf(double x, double* intpart)
{
	return __builtin_modf(x, intpart);
}

double sinh(double x)
{
	return __builtin_sinh(x);
}

double tanh(double x)
{
	return __builtin_tanh(x);
}

double trunc(double x)
{
	return __builtin_trunc(x);
}

float truncf(float x)
{
	return __builtin_truncf(x);
}

double fmod(double x, double y)
{
	return __builtin_fmod(x,y);
}

double tan(double x)
{
	return __builtin_tan(x);
}

double asin(double x)
{
	return __builtin_asin(x);
}
double acos(double x)
{
	return __builtin_acos(x);
}

double atan2(double x, double y)
{
	return __builtin_atan2(x, y);
}