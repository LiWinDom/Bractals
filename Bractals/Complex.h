#pragma once
#include <cmath>

class Complex
{
public:
	Complex(const double& real = 0, const double& imaginable = 0);

	void setReal(const double& real) { this->real_ = real; }

	double getReal() const { return this->real_; }

	void setImaginable(const double& imaginable) { this->imaginable_ = imaginable; }

	double getImaginable() const { return this->imaginable_; }

	double abs() const;


	bool operator== (const Complex& obj) const;

	bool operator!= (const Complex& obj) const;

	bool operator< (const Complex& obj) const;

	bool operator> (const Complex& obj) const;

	bool operator<= (const Complex& obj) const;

	bool operator>= (const Complex& obj) const;


	Complex operator+ (const Complex& obj) const;

	Complex operator- (const Complex& obj) const;

	Complex operator* (const Complex& obj) const;

	Complex operator/ (const Complex& obj) const;


	Complex operator+= (const Complex& obj);

	Complex operator-= (const Complex& obj);

	Complex operator*= (const Complex& obj);

	Complex operator/= (const Complex& obj);

private:
	double real_, imaginable_;
};

