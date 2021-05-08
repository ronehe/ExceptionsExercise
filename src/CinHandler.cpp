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
unsigned int CinHandler::getValidListLength() const{
	return m_functionCalculator->getValidListLength();
}

bool CinHandler::handleOverloadFunctionList() const{
	return m_functionCalculator->getYesNo("This operation might delete functions, would you like to continue? y/n: ");
}
