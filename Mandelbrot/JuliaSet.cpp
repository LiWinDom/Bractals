#include "JuliaSet.h"

JuliaSet::JuliaSet(const Complex& c) {
	this->setC(c);
	return;
}

void JuliaSet::setC(const Complex& c) {
	this->c = c;
	return;
}

Complex JuliaSet::getC() {
	return this->c;
}

uint16_t JuliaSet::countIterations(const Complex& coord, const uint16_t& iterationsLimit) {
    Complex z = coord;
    uint16_t counter = 0;

    
    for (uint16_t n = 1; n <= iterationsLimit; ++n) {
        z = (z * z) + this->c;
        if (z.abs() > 2) {
            return n;
        }
        if (n == iterationsLimit) {
            return n;
        }
    }

    /*while (z.abs() <= 2 && counter < iterationsLimit) {
        z = (z * z) + this->c;
        ++counter;
    }*/
	return counter;
}