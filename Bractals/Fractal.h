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

	void setC(const Complex& c) { c_ = c; }

	Complex getC() { return c_; }

	void setSize(const sf::Vector2i& size) { size_ = size; }

	sf::Vector2i getSize() { return size_; }

	void setPos(const sf::Vector2<double>& pos) { pos_ = pos; }

	sf::Vector2<double> getPos() { return pos_; }

	void setZoom(const double& zoom) { zoom_ = zoom; }

	double getZoom() { return zoom_; }

	void setFrame(const std::vector<std::vector<std::vector<uint8_t>>>& frame) { frame_ = frame; }

	std::vector<std::vector<std::vector<uint8_t>>> getFrame() { return frame_; }

	void recalc(const uint16_t& iterationsLimit, const std::function<void()>& callback = []() -> void {}, const uint16_t& callbackPerLines = 0);

private:
	Complex convertPixel(const uint16_t& x, const uint16_t& y);

	uint16_t countIterations(const Complex& coord, const uint16_t& iterationsLimit);

	std::function<Complex(const Complex& c, const Complex& coord)> getZ0_;
	std::function<Complex(const Complex& z, const Complex& c, const Complex& coord)> function_;
	Complex c_;

	sf::Vector2i size_;
	sf::Vector2<double> pos_;
	double zoom_;

	std::vector<std::vector<std::vector<uint8_t>>> frame_;
};

