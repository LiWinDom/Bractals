#include "Complex.h"

Complex::Complex(const double& real, const double& imaginable) {
	real_ = real;
	imaginable_ = imaginable;
	return;
}

double Complex::abs() const {
	return std::sqrt(real_ * real_ + imaginable_ * imaginable_);
}


bool Complex::operator== (const Complex& obj) const {
	return real_ == obj.real_ && imaginable_ == obj.imaginable_;
}

bool Complex::operator!= (const Complex& obj) const {
	return !operator==(obj);
}

bool Complex::operator< (const Complex& obj) const {
	return abs() < obj.abs();
}

bool Complex::operator> (const Complex& obj) const {
	return obj.operator<(*this);
}

bool Complex::operator<= (const Complex& obj) const {
	return !operator>(obj);
}

bool Complex::operator>= (const Complex& obj) const {
	return !operator<(obj);
}


Complex Complex::operator+ (const Complex& obj) const {
	return Complex(real_ + obj.real_, imaginable_ + obj.imaginable_);
}

Complex Complex::operator- (const Complex& obj) const {
	return Complex(real_ - obj.real_, imaginable_ - obj.imaginable_);
}

Complex Complex::operator* (const Complex& obj) const {
	return Complex(real_ * obj.real_ - imaginable_ * obj.imaginable_,
		real_ * obj.imaginable_ + imaginable_ * obj.real_);
}

Complex Complex::operator/ (const Complex& obj) const {
	Complex up = *this * Complex(obj.real_, -obj.imaginable_);
	Complex down = obj * Complex(obj.real_, -obj.imaginable_);
	return Complex(up.real_ / down.real_, up.imaginable_ / up.real_);
}


Complex Complex::operator+= (const Complex& obj) {
	return *this = Complex(real_ + obj.real_, imaginable_ + obj.imaginable_);
}

Complex Complex::operator-= (const Complex& obj) {
	return *this = Complex(real_ - obj.real_, imaginable_ - obj.imaginable_);
}

Complex Complex::operator*= (const Complex& obj) {
	return *this = Complex(real_ * obj.real_ - imaginable_ * obj.imaginable_,
		real_ * obj.imaginable_ + imaginable_ * obj.real_);
}

Complex Complex::operator/= (const Complex& obj) {
	Complex up = *this * Complex(obj.real_, -obj.imaginable_);
	Complex down = obj * Complex(obj.real_, -obj.imaginable_);
	return *this = Complex(up.real_ / down.real_, up.imaginable_ / up.real_);
}
