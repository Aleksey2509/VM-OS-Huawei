#include "Complex.hh"
#include <iostream>
#include <cmath>
using namespace math;

const Complex z1 (1.3, 1.6);
const Complex z2 (2.4, 2.5);

bool equalTest()
{
    Complex a{1.0, 1.0};
    Complex b{1.0, 1.0};

    if (!(a == b))
    {
        std::cout << "equality test failed" << std::endl;
        return false;
    }

    return true;
}

bool assignTest()
{
    Complex a = z1;
    if (!(a == z1))
    {
        std::cout << "assign test failed" << std::endl;
        return false;
    }

    return true;
}

bool unaryMinusTest()
{
    Complex a = -z1;

    if ((a.re_ != -z1.re_) || (a.im_ != -z1.im_))
    {
        std::cout << "unary minus test failed" << std::endl;
        return false;
    }

    return true;
}

bool absTest()
{
    double z1Abs = z1.abs();
    double z2Abs = z2.abs();
    double expectedFirstAbs = 2.061553;
    double expectedSecondAbs = 3.465545;

    if ((fabs(z1Abs - expectedFirstAbs) > FIT_TOLERANCE) || (fabs(z2Abs - expectedSecondAbs) > FIT_TOLERANCE))
    {
        std::cout << "abs test failed: got " << z1.abs() << " " << z2.abs()
        << "instead of " << expectedFirstAbs << " " << expectedSecondAbs << std::endl;
        return false;
    }

    return true;
}

bool addTest()
{
    Complex expectedResult (3.7, 4.1);

    Complex result = z1 + z2;
    if (result != expectedResult)
    {
        std::cout << "add test failed: expected: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
}

bool subTest()
{
    Complex expectedResult (1.1, 0.9);
    Complex result = z2 - z1;

    if (result != expectedResult)
    {
        std::cout << "sub test failed: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
} 

bool mulTest()
{
    Complex expectedResult (-0.88, 7.09);
    Complex result = z2 * z1;

    if (result != expectedResult)
    {
        std::cout << "mul test failed: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
} 

bool divTest()
{
    Complex expectedResult (0.592839, 0.0491257);
    Complex result = z1 / z2;
    if (result != expectedResult)
    {
        std::cout << "div test failed: expected: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
}

bool addEqTest()
{
    Complex expectedResult (3.7, 4.1);
    Complex result = z1;
    result += z2;
    if (result != expectedResult)
    {
        std::cout << "+= test failed: expected: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
}

bool subEqTest()
{
    Complex expectedResult (1.1, 0.9);
    Complex result = z2;
    result -= z1;

    if (result != expectedResult)
    {
        std::cout << "-= test failed: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
} 

bool mulEqTest()
{
    Complex expectedResult (-0.88, 7.09);
    Complex result = z2;
    result *= z1;

    if (result != expectedResult)
    {
        std::cout << "*= test failed: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
} 

bool divEqTest()
{
    Complex expectedResult (0.592839, 0.0491257);
    Complex result = z1;
    result /= z2;

    if (result != expectedResult)
    {
        std::cout << "/= test failed: expected: " << expectedResult
        << " got " << result << std::endl;
        return false;
    }

    return true;
}

int main()
{
    equalTest();
    assignTest();
    unaryMinusTest();
    absTest();
    addTest();
    subTest();
    mulTest();
    divTest();
    addEqTest();
    subEqTest();
    mulEqTest();
    divEqTest();
}