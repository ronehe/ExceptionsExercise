//a base class for handling stream, used for distingiuishing cin and files

#pragma once
#include <iostream>

class FunctionCalculator;

class BaseStreamHandler {
private:
	std::istream* m_stream; //cin or files
protected:
	FunctionCalculator* m_functionCalculator; //for accessing necessary public functions
	bool m_isRunning = false;
public:
	BaseStreamHandler(std::istream*, FunctionCalculator*);
	virtual bool getline(std::string&);

	//vritual functions that will handle errors when occur
	virtual bool endReadingFromStream(std::ostream&, const std::string&) const = 0;
	virtual unsigned int getValidListLength() const = 0;
	virtual bool handleOverloadFunctionList() const = 0;
	void startRunning();
};