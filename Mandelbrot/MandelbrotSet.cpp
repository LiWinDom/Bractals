#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet() {
    return;
}

uint16_t MandelbrotSet::countIterations(const Complex& coord, const uint16_t& iterationsLimit) {
    Complex z = Complex(0, 0);
    uint16_t counter = 0;

    for (uint16_t n = 1; n <= iterationsLimit; ++n) {
        z = (z * z) + coord;
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