#pragma once
#include <algorithm>

#include "Complex.h"

class JuliaSet
{
public:
	JuliaSet(const Complex& c);

	void setC(const Complex& c);

	Complex getC();

	uint16_t countIterations(const Complex& coord, const uint16_t& iterationsLimit);

private:
	Complex c;
};

