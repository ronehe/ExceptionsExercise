#include <CinHandler.h>
#include <FunctionCalculator.h>
CinHandler::CinHandler(std::istream* istr, FunctionCalculator* calc)
	: BaseStreamHandler(istr, calc) {}

bool CinHandler::getline(std::string& str) {
	m_functionCalculator->printFunctionList();
	return BaseStreamHandler::getline(str);
}

bool CinHandler::endReadingFromStream(std::ostream&, const std::string& str) const {
	return false;
}