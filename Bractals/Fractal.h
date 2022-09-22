#pragma once
#include <algorithm>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Complex.h"
#include "Frame.h"

class Fractal final
{
public:
	Fractal(const std::function<Complex(const Complex& c, const Complex& coord)>& getZ0,
		const std::function<Complex(const Complex& z, const Complex& c, const Complex& coord)>& function,
		const Complex& c, const sf::Vector2i& size, const double& zoom, const sf::Vector2<double>& startPos = sf::Vector2<double>(0, 0));

	void setC(const Complex& c) {
		this->c = c;
	}

	Complex getC() {
		return this->c;
	}

	void setSize(const sf::Vector2i& size) {
		this->size = size;
	}

	sf::Vector2i getSize() {
		return this->size;
	}

	void setPos(const sf::Vector2<double>& pos) {
		this->pos = pos;
	}

	sf::Vector2<double> getPos() {
		return this->pos;
	}

	void setZoom(const double& zoom) {
		this->zoom = zoom;
	}

	double getZoom() {
		return this->zoom;
	}

	std::vector<std::vector<std::vector<uint8_t>>> getFrame() {
		return this->frame;
	}

	void recalc(const uint16_t& iterationsLimit, const std::function<void()>& callback = []() -> void {}, const uint16_t& callbackPerLines = 0);

private:
	Complex convertPixel(const uint16_t& x, const uint16_t& y);

	uint16_t countIterations(const Complex& coord, const uint16_t& iterationsLimit);

	std::function<Complex(const Complex& c, const Complex& coord)> getZ0;
	std::function<Complex(const Complex& z, const Complex& c, const Complex& coord)> function;
	Complex c;

	sf::Vector2i size;
	sf::Vector2<double> pos;
	double zoom;

	std::vector<std::vector<std::vector<uint8_t>>> frame;
};

