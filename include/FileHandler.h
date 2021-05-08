//a class for handling files
#pragma once
#include <BaseStreamHandler.h>

class FileHandler : public BaseStreamHandler {
private:
	std::string m_fileName;
public:
	FileHandler(std::istream*, FunctionCalculator*, std::string&);
	bool endReadingFromStream(std::ostream&, const std::string&) const override;
};