#include "Fractal.h"

Fractal::Fractal(const std::function<Complex(const Complex& c, const Complex& coord)>& getZ0,
	const std::function<Complex(const Complex& z, const Complex& c, const Complex& coord)>& function,
	const Complex& c, const sf::Vector2i& size, const double& zoom, const sf::Vector2<double>& startPos):
	getZ0_(getZ0),
	function_(function),
	c_(c),
	size_(size),
	zoom_(zoom),
	pos_(startPos) {
	frame_ = std::vector<std::vector<std::vector<uint8_t>>>(size_.y, std::vector<std::vector<uint8_t>>(size_.x, std::vector<uint8_t>(3, 0)));
	return;
}

void Fractal::recalc(const uint16_t& iterationsLimit, const std::function<void()>& callback, const uint16_t& callbackPerLines) {
	for (uint16_t i = 0; i < size_.y; ++i) {
		for (uint16_t j = 0; j < size_.x; ++j) {
			uint16_t iterations = countIterations(convertPixel(j, i), iterationsLimit);
			if (iterations >= iterationsLimit) {
				frame::setPixel(frame_, j, i, 0);
			}
			else {
				frame::setPixel(frame_, j, i, frame::HSVtoRGB(iterations, 75, 75));
			}
		}
		if (callbackPerLines > 0 && i % callbackPerLines == 0) {
			callback();
		}
	}
	return;
}


Complex Fractal::convertPixel(const uint16_t& x, const uint16_t& y) {
	return Complex((x - size_.x / 2.0) / zoom_ - pos_.x, (y - size_.y / 2.0) / zoom_ - pos_.y);
}

uint16_t Fractal::countIterations(const Complex& coord, const uint16_t& iterationsLimit) {
	Complex z = getZ0_(c_, coord);
	uint16_t counter = 0;

	for (counter; counter < iterationsLimit; ++counter) {
		if (z.getReal() * z.getReal() + z.getImaginable() * z.getImaginable() > 4) {
			break;
		}
		z = function_(z, c_, coord);
	}
	return counter;
}
