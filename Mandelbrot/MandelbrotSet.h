#pragma once
#include <algorithm>

#include "Complex.h"

class MandelbrotSet
{
public:
	MandelbrotSet();

	uint16_t countIterations(const Complex& coord, const uint16_t& iterationsLimit);

private:
};

