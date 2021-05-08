#include <FileHandler.h>
#include <YesNoValidator.h>
FileHandler::FileHandler(std::istream* istr, FunctionCalculator* calc, std::string& filename)
	: BaseStreamHandler(istr, calc), m_fileName(filename) {}

bool FileHandler::endReadingFromStream(std::ostream& ostr, const std::string& line) const{
	ostr <<" in file - " << m_fileName <<": "<<line<<"\n";
	return (!Validator::validate("would you like to continue reading? y/n"));
}