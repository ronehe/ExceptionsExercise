#pragma once
#include <exception>

class MaximumFunctionsException : public std::exception {
public:
	MaximumFunctionsException() 
		: std::exception("You have reached maximum vector size") {}
};