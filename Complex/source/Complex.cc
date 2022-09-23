#include "Complex.hh"
#include <cmath>
#include <cstdlib>


namespace math
{

Complex::Complex(double re, double im) :
    re_(re), im_(im)
    {}

Complex::Complex(const Complex& another) :
    re_(another.re_), im_(another.im_)
    {}

double Complex::abs() const
{
    return sqrt(re_ * re_ + im_ * im_);
}

double Complex::arg() const
{
    if (abs() == 0)
        return 0.0;

    if (re_ == 0)
        return M_PI_2;

    return atan(im_/re_);
}

bool Complex::operator==(const Complex& rhs) const
{
    return (fabs(re_ - rhs.re_) <= COMPARE_ERROR) && (fabs(im_ - rhs.im_) <= COMPARE_ERROR);
}

bool Complex::operator!=(const Complex& rhs) const
{
    return !((*this) == rhs);
}

Complex& Complex::operator=(const Complex rhs)
{
    re_ = rhs.re_;
    im_ = rhs.im_;

    return *this;
}

Complex& Complex::operator+=(const Complex& rhs)
{
    re_ += rhs.re_;
    im_ += rhs.im_;

    return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
    re_ -= rhs.re_;
    im_ -= rhs.im_;

    return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
    Complex tmp{*this};
    re_ = tmp.re_ * rhs.re_ - tmp.im_ * rhs.im_;
    im_ = tmp.re_ * rhs.im_ + tmp.im_ * rhs.re_;

    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    Complex tmp{*this};
    re_ = (tmp.re_ * rhs.re_ + tmp.im_ * rhs.im_) / (rhs.abs() * rhs.abs());
    im_ = (tmp.im_ * rhs.re_ - tmp.re_ * rhs.im_) / (rhs.abs() * rhs.abs());

    return *this;
}

Complex& Complex::operator+=(double rhs)
{
    re_ += rhs;
    return *this;
}
Complex& Complex::operator-=(double rhs)
{
    re_ -= rhs;
    return *this;
}

Complex& Complex::operator*=(double rhs)
{
    re_ *= rhs;
    im_ *= rhs;

    return *this;
}

Complex& Complex::operator/=(double rhs)
{
    re_ /= rhs;
    im_ /= rhs;

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

Complex operator*(const Complex& lhs, double rhs)
{
    Complex tmp{lhs};
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

Complex operator/(const Complex& lhs, double rhs)
{
    Complex tmp{lhs};
    tmp /= rhs;
    return tmp;
}

} // namespace math

std::ostream& operator<<(std::ostream& ostream, const math::Complex& z)
{
    if (fabs(z.re_) >= math::Complex::COMPARE_ERROR)
        ostream << z.re_;

    ostream << " ";
    if (z.im_ >= math::Complex::COMPARE_ERROR)
        ostream << "+ ";

    if (fabs(z.im_) >= math::Complex::COMPARE_ERROR)
        ostream << z.im_ << "i";
    return ostream;
}