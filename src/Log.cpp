#include "Log.h"
#include <iostream>
#include <cmath>

Log::Log(int base, const std::shared_ptr<Function>& func)
    : m_base(base), m_func(func)
{
}

double Log::operator()(double x) const
{
    if (x <= 0)
        throw std::invalid_argument::exception("invalid input for log");
    return std::log((*m_func)(x)) / std::log(m_base);
}

std::string Log::to_string(const std::string& arg) const
{
    return "log_" + std::to_string(m_base) + "(" + m_func->to_string(arg) + ")";
}
