#include "Complex.h"

Complex::Complex(const double& real, const double& imaginable) {
	this->setReal(real);
	this->setImaginable(imaginable);
	return;
}

double Complex::abs() const {
	return std::sqrt(this->getReal() * this->getReal() + this->getImaginable() + this->getImaginable());
}


bool Complex::operator== (const Complex& obj) const {
	return this->getReal() == obj.getReal() && this->getImaginable() == obj.getImaginable();
}

bool Complex::operator!= (const Complex& obj) const {
	return this->getReal() != obj.getReal() || this->getImaginable() != obj.getImaginable();
}

bool Complex::operator> (const Complex& obj) const {
	return this->abs() > obj.abs();
}

bool Complex::operator< (const Complex& obj) const {
	return this->abs() < obj.abs();
}

bool Complex::operator>= (const Complex& obj) const {
	return this->abs() >= obj.abs();
}

bool Complex::operator<= (const Complex& obj) const {
	return this->abs() <= obj.abs();
}


Complex Complex::operator+ (const Complex& obj) const {
	return Complex(this->getReal() + obj.getReal(), this->getImaginable() + obj.getImaginable());
}

Complex Complex::operator- (const Complex& obj) const {
	return Complex(this->getReal() - obj.getReal(), this->getImaginable() - obj.getImaginable());
}

Complex Complex::operator* (const Complex& obj) const {
	return Complex(this->getReal() * obj.getReal() - this->getImaginable() * obj.getImaginable(),
		this->getReal() * obj.getImaginable() + this->getImaginable() * obj.getReal());
}

Complex Complex::operator/ (const Complex& obj) const {
	Complex up = *this * Complex(obj.getReal(), -obj.getImaginable());
	Complex down = obj * Complex(obj.getReal(), -obj.getImaginable());
	return Complex(up.getReal() / down.getReal(), up.getImaginable() / up.getReal());
}


Complex Complex::operator+= (const Complex& obj) {
	return *this = Complex(this->getReal() + obj.getReal(), this->getImaginable() + obj.getImaginable());
}

Complex Complex::operator-= (const Complex& obj) {
	return *this = Complex(this->getReal() - obj.getReal(), this->getImaginable() - obj.getImaginable());
}

Complex Complex::operator*= (const Complex& obj) {
	return *this = Complex(this->getReal() * obj.getReal() - this->getImaginable() * obj.getImaginable(),
		this->getReal() * obj.getImaginable() + this->getImaginable() * obj.getReal());
}

Complex Complex::operator/= (const Complex& obj) {
	Complex up = *this * Complex(obj.getReal(), -obj.getImaginable());
	Complex down = obj * Complex(obj.getReal(), -obj.getImaginable());
	return *this = Complex(up.getReal() / down.getReal(), up.getImaginable() / up.getReal());
}
