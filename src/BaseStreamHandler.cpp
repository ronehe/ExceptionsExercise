#include <BaseStreamHandler.h>
#include <FunctionCalculator.h>
#include <string>

BaseStreamHandler::BaseStreamHandler(std::istream* istr, FunctionCalculator* calc) 
	: m_stream(istr), m_functionCalculator(calc) {}

bool BaseStreamHandler::getline(std::string& str) {
	if (std::getline(*m_stream, str)) return true;
	return false;
}

