#ifndef COMPLEX_HH
#define COMPLEX_HH

#include <iostream>

namespace math
{


struct Complex
{
    constexpr static double COMPARE_ERROR = 0.000001;

    double re_ = 0.0;
    double im_ = 0.0;

    Complex();
    Complex(double re, double im);
    Complex(const Complex& another);

    double abs() const;
    double arg() const;

    bool operator==(const Complex& rhs) const;
    bool operator!=(const Complex& rhs) const;

    Complex& operator=(Complex rhs);
    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);

    Complex& operator+=(double rhs);
    Complex& operator-=(double rhs);
    Complex& operator*=(double rhs);
    Complex& operator/=(double rhs);

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    Complex operator-() const;

};


Complex operator*(const Complex& lhs, double rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, double rhs);

} // namespace math

std::ostream& operator<<(std::ostream& ostream, const math::Complex& z);

#endif