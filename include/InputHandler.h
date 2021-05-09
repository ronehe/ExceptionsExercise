#pragma once
#include<fstream>
#include<stack>
#include <sstream>
#include <iostream>

class BaseStreamHandler;
class FunctionCalculator;
typedef std::istream streamObj;

class InputHandler {
public:
	InputHandler(BaseStreamHandler*);
	~InputHandler();
	void addStream(BaseStreamHandler*);
	void removeStream() const;
	void readNewLine() const;
	void handleInvalidArgument(std::ostream&);
	void handleOutOfRange(unsigned int& num);
	bool handleOverloadFunctionList();
	void clear();
	bool lineIsEmpty()const;
	void startRunning();

	template<typename T>
	friend void operator>>(const InputHandler&, T&);
	std::string getLineRead() const;
private:
	std::stack<BaseStreamHandler*>* m_streams;
	std::stringstream* m_curLineRead;
};

/*
global operator >>  for handling the top of the stack which is the current stream,
 doesnt matter which object wants the data from the operator
*/
// "curHandler"  :current handler object  </param>
// "into" :object for which the data will go into </param>
/* <after effects>  will remove empty top stream  from stack(empty streams are the once of which recognize the - "eof" method)
in newLineRead fun <after effects>*/
template<typename T>
void operator>>(const InputHandler&curHandlar, T &into ){
	if(curHandlar.lineIsEmpty())
		curHandlar.readNewLine();
	*(curHandlar.m_curLineRead) >> into;

	if ((*curHandlar.m_curLineRead).fail()) {
	throw std::invalid_argument::exception("invalid type has entered");
		}
	//if file has ended, set the input stream the previous stack
}

