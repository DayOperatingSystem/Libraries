#include <math.h>

void test_sqrt()
{
	double val = 2.0;
	sqrt(val);
}

void run_math_test()
{
	RUN(test_sqrt);
}