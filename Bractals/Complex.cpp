#include "Complex.h"

Complex::Complex(const double& real, const double& imaginable) {
	this->setReal(real);
	this->setImaginable(imaginable);
	return;
}

double Complex::abs() {
	return std::sqrt(this->getReal() * this->getReal() + this->getImaginable() + this->getImaginable());
}


bool Complex::operator== (const Complex& obj) {
	return this->getReal() == static_cast<Complex>(obj).getReal() && this->getImaginable() == static_cast<Complex>(obj).getImaginable();
}

bool Complex::operator> (const Complex& obj) {
	return this->abs() > static_cast<Complex>(obj).abs();
}

bool Complex::operator< (const Complex& obj) {
	return this->abs() < static_cast<Complex>(obj).abs();
}

bool Complex::operator>= (const Complex& obj) {
	return this->abs() >= static_cast<Complex>(obj).abs();
}

bool Complex::operator<= (const Complex& obj) {
	return this->abs() <= static_cast<Complex>(obj).abs();
}


Complex Complex::operator+ (const Complex& obj) {
	return Complex(this->getReal() + static_cast<Complex>(obj).getReal(), this->getImaginable() + static_cast<Complex>(obj).getImaginable());
}

Complex Complex::operator- (const Complex& obj) {
	return Complex(this->getReal() - static_cast<Complex>(obj).getReal(), this->getImaginable() - static_cast<Complex>(obj).getImaginable());
}

Complex Complex::operator* (const Complex& obj) {
	return Complex(this->getReal() * static_cast<Complex>(obj).getReal() - this->getImaginable() * static_cast<Complex>(obj).getImaginable(),
		this->getReal() * static_cast<Complex>(obj).getImaginable() + this->getImaginable() * static_cast<Complex>(obj).getReal());
}

Complex Complex::operator/ (const Complex& obj) {
	Complex up = *this * Complex(static_cast<Complex>(obj).getReal(), -static_cast<Complex>(obj).getImaginable());
	Complex down = static_cast<Complex>(obj) * Complex(static_cast<Complex>(obj).getReal(), -static_cast<Complex>(obj).getImaginable());
	return Complex(up.getReal() / down.getReal(), up.getImaginable() / up.getReal());
}


Complex Complex::operator+= (const Complex& obj) {
	return *this = Complex(this->getReal() + static_cast<Complex>(obj).getReal(), this->getImaginable() + static_cast<Complex>(obj).getImaginable());
}

Complex Complex::operator-= (const Complex& obj) {
	return *this = Complex(this->getReal() - static_cast<Complex>(obj).getReal(), this->getImaginable() - static_cast<Complex>(obj).getImaginable());
}

Complex Complex::operator*= (const Complex& obj) {
	return *this = Complex(this->getReal() * static_cast<Complex>(obj).getReal() - this->getImaginable() * static_cast<Complex>(obj).getImaginable(),
		this->getReal() * static_cast<Complex>(obj).getImaginable() + this->getImaginable() * static_cast<Complex>(obj).getReal());
}

Complex Complex::operator/= (const Complex& obj) {
	Complex up = *this * Complex(static_cast<Complex>(obj).getReal(), -static_cast<Complex>(obj).getImaginable());
	Complex down = static_cast<Complex>(obj) * Complex(static_cast<Complex>(obj).getReal(), -static_cast<Complex>(obj).getImaginable());
	return *this = Complex(up.getReal() / down.getReal(), up.getImaginable() / up.getReal());
}
