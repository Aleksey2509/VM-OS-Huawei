#include "Complex.hh"
#include <cmath>
#include <cstdlib>


namespace complex_math
{

Complex::Complex(double real, double imag) :
    re(real), im(imag)
    {}

Complex::Complex(const Complex& another) :
    re(another.re), im(another.im)
    {}

double Complex::abs() const
{
    return sqrt(re * re + im * im);
}

double Complex::arg() const
{
    if (abs() == 0)
        return 0.0;

    if (re == 0)
        return M_PI_2;

    return atan(im/re);
}

bool Complex::operator==(const Complex& rhs) const
{
    return (fabs(re - rhs.re) <= COMPARE_ERROR) && (fabs(im - rhs.im) <= COMPARE_ERROR);
}

bool Complex::operator!=(const Complex& rhs) const
{
    return !((*this) == rhs);
}

Complex& Complex::operator=(const Complex rhs)
{
    re = rhs.re;
    im = rhs.im;

    return *this;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    re += rhs.re;
    im += rhs.im;

    return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
    re -= rhs.re;
    im -= rhs.im;

    return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
    Complex tmp{*this};
    re = tmp.re * rhs.re - tmp.im * rhs.im;
    im = tmp.re * rhs.im + tmp.im * rhs.re;

    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    Complex tmp{*this};
    re = (tmp.re * rhs.re + tmp.im * rhs.im) / (rhs.abs() * rhs.abs());
    im = (tmp.im * rhs.re - tmp.re * rhs.im) / (rhs.abs() * rhs.abs());

    return *this;
}

Complex& Complex::operator+=(double rhs)
{
    re += rhs;
    return *this;
}
Complex& Complex::operator-=(double rhs)
{
    re -= rhs;
    return *this;
}

Complex& Complex::operator*=(double rhs)
{
    re *= rhs;
    im *= rhs;

    return *this;
}

Complex& Complex::operator/=(double rhs)
{
    re /= rhs;
    im /= rhs;

    return *this;
}

Complex Complex::operator-() const
{
    return -1.0 * (*this);
}

Complex Complex::operator+(const Complex& rhs) const
{
    Complex tmp{*this};
    tmp += rhs;
    return tmp;
}

Complex Complex::operator+() const
{
    return *this;
}

Complex Complex::operator-(const Complex& rhs) const
{
    Complex tmp{*this};
    tmp -= rhs;
    return tmp;
}

Complex Complex::operator*(const Complex& rhs) const
{
    Complex tmp{*this};
    tmp *= rhs;
    return tmp;
}

Complex Complex::operator/(const Complex& rhs) const
{
    Complex tmp{*this};
    tmp /= rhs;
    return tmp;
}

Complex Complex::operator*(double rhs)
{
    Complex tmp{*this};
    tmp *= rhs;
    return tmp;
}

Complex operator*(double lhs, const Complex& rhs)
{
    Complex tmp{rhs};
    tmp *= lhs;
    return tmp;
}

Complex operator/(double lhs, const Complex& rhs)
{
    Complex tmp{rhs};
    tmp /= lhs;
    return tmp;
}

Complex Complex::operator/(double rhs)
{
    Complex tmp{*this};
    tmp /= rhs;
    return tmp;
}

} // namespace complex_math

std::ostream& operator<<(std::ostream& ostream, const complex_math::Complex& z)
{
    if (fabs(z.re) >= complex_math::Complex::COMPARE_ERROR)
        ostream << z.re;

    ostream << " ";
    if (z.im >= complex_math::Complex::COMPARE_ERROR)
        ostream << "+ ";

    if (fabs(z.im) >= complex_math::Complex::COMPARE_ERROR)
        ostream << z.im << "i";
    return ostream;
}