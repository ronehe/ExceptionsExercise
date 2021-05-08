#include <FileHandler.h>
FileHandler::FileHandler(std::istream* istr, FunctionCalculator* calc, std::string& filename)
	: BaseStreamHandler(istr, calc), m_fileName(filename) {}

bool FileHandler::endReadingFromStream(std::ostream& ostr, const std::string& line) const{
	ostr <<" in file - " << m_fileName <<": "<<line<<"\n";
	return (!m_functionCalculator->getYesNo("would you like to continue reading? y/n"));
}

unsigned int FileHandler::getValidListLength() const {
	throw std::invalid_argument::exception("Invalid size");
}

bool FileHandler::handleOverloadFunctionList() const {
	throw std::invalid_argument::exception("ERROR: Wanted maximum is less than current capacity");
}