//a class for handling cin stream in the calculator
#pragma once
#include "BaseStreamHandler.h"

class CinHandler : public BaseStreamHandler {
private:
public:
	CinHandler(std::istream*, FunctionCalculator*);
	bool getline(std::string&) override;
	bool endReadingFromStream(std::ostream&, const std::string&) const override;
};