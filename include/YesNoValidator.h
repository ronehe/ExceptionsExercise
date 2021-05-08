#pragma once
#include <exception>
#include <functional>
#include <iostream>
#include <string>

//class of static validators
class Validator {
public:
	static bool validate(const std::string&);
};
