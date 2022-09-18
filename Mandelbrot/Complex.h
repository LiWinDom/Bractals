#pragma once
#include <cmath>

class Complex
{
public:
	Complex(const double& real = 0, const double& imaginable = 0);

	double getReal();

	void setReal(const double& real);

	double getImaginable();

	void setImaginable(const double& imaginable);

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

