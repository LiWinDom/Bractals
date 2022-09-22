#include "Fractal.h"

Fractal::Fractal(const std::function<Complex(const Complex& c, const Complex& coord)>& getZ0,
	const std::function<Complex(const Complex& z, const Complex& c, const Complex& coord)>& function,
	const Complex& c, const sf::Vector2i& size, const double& zoom, const sf::Vector2<double>& startPos) {
	this->getZ0 = getZ0;
	this->function = function;
	this->c = c;
	this->size = size;
	this->zoom = zoom;
	this->pos = startPos;
	this->frame = std::vector<std::vector<std::vector<uint8_t>>>(this->size.y, std::vector<std::vector<uint8_t>>(this->size.x, std::vector<uint8_t>(3, 0)));
	return;
}

void Fractal::recalc(const uint16_t& iterationsLimit, const std::function<void()>& callback, const uint16_t& callbackPerLines) {
	for (uint16_t i = 0; i < this->size.y; ++i) {
		for (uint16_t j = 0; j < this->size.x; ++j) {
			uint16_t iterations = this->countIterations(this->convertPixel(j, i), iterationsLimit);
			if (iterations >= iterationsLimit) {
				frame::setPixel(this->frame, j, i, 0);
			}
			else {
				frame::setPixel(this->frame, j, i, frame::HSVtoRGB(iterations, 75, 75));
			}
		}
		if (callbackPerLines > 0 && i % callbackPerLines == 0) {
			callback();
		}
	}
	return;
}


Complex Fractal::convertPixel(const uint16_t& x, const uint16_t& y) {
	return Complex((x - this->size.x / 2.0) / this->zoom - this->pos.x, (y - this->size.y / 2.0) / this->zoom - pos.y);
}

uint16_t Fractal::countIterations(const Complex& coord, const uint16_t& iterationsLimit) {
	Complex z = this->getZ0(this->c, coord);
	uint16_t counter = 0;

	for (counter; counter < iterationsLimit; ++counter) {
		if (z.getReal() * z.getReal() + z.getImaginable() * z.getImaginable() > 4) {
			break;
		}
		z = this->function(z, this->c, coord);
	}
	return counter;
}
