#include "Ln.h"
#include<iostream>
#include <cmath>

double Ln::operator()(double x) const
{
    if (x <= 0)
        throw std::invalid_argument::exception(("none, " + std::to_string(x)+" is invalid input for ln").data());
    return std::log(x);
}

std::string Ln::to_string(const std::string& arg) const
{
    return "ln(" + arg + ")";
}
