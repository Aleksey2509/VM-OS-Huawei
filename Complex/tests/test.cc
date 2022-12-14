#include "Complex.hh"
#include <iostream>
#include <cmath>
using namespace complex_math;

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
    const Complex z1 (1.3, 1.6);
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
    const Complex z1 (1.3, 1.6);
    Complex a = -z1;

    if ((a.re != -z1.re) || (a.im != -z1.im))
    {
        std::cout << "unary minus test failed" << std::endl;
        return false;
    }

    return true;
}

bool unaryPlusTest()
{
    const Complex z1 (1.3, 1.6);
    Complex a = +z1;
    if (a != z1)
    {
        std::cout << "unary minus test failed" << std::endl;
        return false;
    }

    return true;
}

bool absTest()
{
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

    double expectedFirstAbs = 2.061553;
    double expectedSecondAbs = 3.465545;

    if ((fabs(z1.abs() - expectedFirstAbs) > Complex::COMPARE_ERROR) ||
        (fabs(z2.abs() - expectedSecondAbs) > Complex::COMPARE_ERROR))
    {
        std::cout << "abs test failed: got " << z1.abs() << " " << z2.abs()
        << "instead of " << expectedFirstAbs << " " << expectedSecondAbs << std::endl;
        return false;
    }

    return true;
}

bool argTest()
{
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

    double expectedFirstArg = 0.88848;
    double expectedSecondArg = 0.805803;

    if ((fabs(z1.arg() - expectedFirstArg) > Complex::COMPARE_ERROR) ||
        (fabs(z2.arg() - expectedSecondArg) > Complex::COMPARE_ERROR))
    {
        std::cout << "arg test failed: got " << z1.arg() << " " << z2.arg()
        << "instead of " << expectedFirstArg << " " << expectedSecondArg << std::endl;
        return false;
    }

    return true;
}

bool addTest()
{
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);
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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    const Complex z1 (1.3, 1.6);
    const Complex z2 (2.4, 2.5);

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
    return  equalTest() &&
            assignTest() &&
            unaryMinusTest() &&
            unaryPlusTest() &&
            absTest() &&
            argTest() &&
            addTest() &&
            subTest() &&
            mulTest() &&
            divTest() &&
            addEqTest() &&
            subEqTest() &&
            mulEqTest() &&
            divEqTest();
}