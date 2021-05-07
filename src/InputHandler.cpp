#include <FunctionCalculator.h>
/*
constarctor, enters the first stream in the top of the stack
 */ 
//"istr" : 
InputHandler::InputHandler(streamObj* istr, FunctionCalculator* calc) 
	: m_functionsCalculator(calc)
{
	m_streams = new std::stack<streamObj*>;
	//creates new because the functions in the calculator are consts, 
		//and we tried as little as we can to change your code
	m_curLineRead = new std::stringstream();
	addStream(istr);
	//readNewLine();
}
//inputs new stream in the stack
void InputHandler::addStream(streamObj* istr) {
	m_streams->push(istr);
}
//removes the recent stream from the stack
void InputHandler::removeStream() const {
	delete m_streams->top();
	m_streams->pop();
	
	//after removing stream, print function list if reached std::cin
	if (isCin())
		m_functionsCalculator->printFunctionList();
}
/* 
reads anouther line from the current higest stream in the stack doesnt matter if it is
a file or any istrem inherited class.

<after effects> :removes the stream if ended inserts in the new line - from getline.
*/
void InputHandler::readNewLine() const{
	auto temp = std::string();
	//as long as it is possible to get lines
	while (!std::getline(*(m_streams->top()), temp)) {
		removeStream();
	}
	m_curLineRead->str(temp);
}

bool InputHandler::isCin() const {
	return m_streams->top() == &std::cin;
}

void InputHandler::clear() {
	m_curLineRead->clear();
}

InputHandler::~InputHandler() {
	delete m_curLineRead;
	while (m_streams->size() )
	{
		if(!isCin())
			delete(m_streams->top());
		m_streams->pop();
	}
}
std::string InputHandler::getLineRead() const {
	return (m_curLineRead->str());
}

