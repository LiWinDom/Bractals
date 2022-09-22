#pragma once
#include <cmath>

class Complex
{
public:
	Complex(const double& real = 0, const double& imaginable = 0);

	void setReal(const double& real) {
		this->real = real;
	}

	double getReal() {
		return this->real;
	}

	void setImaginable(const double& imaginable) {
		this->imaginable = imaginable;
	}

	double getImaginable() {
		return this->imaginable;
	}

	double abs();


	bool operator== (const Complex& obj);

	bool operator> (const Complex& obj);

	bool operator< (const Complex& obj);

	bool operator>= (const Complex& obj);

	bool operator<= (const Complex& obj);


	Complex operator+ (const Complex& obj);

	Complex operator- (const Complex& obj);

	Complex operator* (const Complex& obj);

	Complex operator/ (const Complex& obj);


	Complex operator+= (const Complex& obj);

	Complex operator-= (const Complex& obj);

	Complex operator*= (const Complex& obj);

	Complex operator/= (const Complex& obj);

private:
	double real, imaginable;
};

