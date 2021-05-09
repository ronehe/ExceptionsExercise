#include "FunctionCalculator.h"

#include <iostream>

int main()
{
	try {
		FunctionCalculator(std::cin, std::cout).run();
	}
	catch (std::invalid_argument::exception& e) {
		std::cout << "wrong size entered please try again: \n";
		main();
	}
}
