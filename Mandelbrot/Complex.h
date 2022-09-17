#pragma once
#include <cmath>

class Complex
{
public:
	Complex(const double& real, const double& imaginable);

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

