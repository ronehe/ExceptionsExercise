//a base class for handling stream, used for distingiuishing cin and files

#pragma once
#include <iostream>

class FunctionCalculator;

class BaseStreamHandler {
private:
	std::istream* m_stream;
protected:
	FunctionCalculator* m_functionCalculator;
public:
	BaseStreamHandler(std::istream*, FunctionCalculator*);
	virtual bool getline(std::string&);
	virtual bool endReadingFromStream(std::ostream&, const std::string&) const = 0;
};