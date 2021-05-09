#include <InputHandler.h>
#include <FunctionCalculator.h>
#include <BaseStreamHandler.h>
/*
constarctor, enters the first stream in the top of the stack
 */ 
//"istr" : 
InputHandler::InputHandler(BaseStreamHandler* stream)
{
	m_streams = new std::stack<BaseStreamHandler*>;
	//creates new because the functions in the calculator are consts, 
		//and we tried as little as we can to change your code
	m_curLineRead = new std::stringstream();
	addStream(stream);
	//readNewLine();
}

void InputHandler::handleOutOfRange(unsigned int& size) {
	size = m_streams->top()->getValidListLength();
}

bool InputHandler::handleOverloadFunctionList() {
	return m_streams->top()->handleOverloadFunctionList();
}

void InputHandler::handleInvalidArgument(std::ostream& ostr) {
	if (m_streams->top()->endReadingFromStream(ostr, m_curLineRead->str())) {
		removeStream();
	}
	readNewLine();
}

//inputs new stream in the stack
void InputHandler::addStream(BaseStreamHandler* stream) {
	m_streams->push(stream);
}
//removes the recent stream from the stack
void InputHandler::removeStream() const {
	delete m_streams->top();//deleting the stream
	m_streams->pop();
	
	//after removing stream, print function list if reached std::cin
	//if (isCin())
		//m_functionsCalculator->printFunctionList();
}
/* 
reads anouther line from the current higest stream in the stack doesnt matter if it is
a file or any istrem inherited class.

<after effects> :removes the stream if ended inserts in the new line - from getline.
*/

void InputHandler::startRunning() {
	m_streams->top()->startRunning();
}
void InputHandler::readNewLine() const{
	auto temp = std::string();
	//as long as it is possible to get lines
	while(!m_streams->top()->getline(temp)){
		removeStream();
	}
	m_curLineRead->str(temp);
	m_curLineRead->clear();
}

//bool InputHandler::isCin() const {
	//return m_streams->top().first == &std::cin;
//}

void InputHandler::clear() {
	m_curLineRead->clear();
}

InputHandler::~InputHandler() {
	delete m_curLineRead;
	while (m_streams->size() )
	{
		delete(m_streams->top());
		m_streams->pop();
	}
}
std::string InputHandler::getLineRead() const {
	return (m_curLineRead->str());
}
//returns the file name of the current stream
//const std::string InputHandler:: fileName() {
	//return m_streams->top().second;
//}
bool InputHandler::lineIsEmpty()const {
	return(!m_curLineRead->rdbuf()->in_avail());
}
//removes the currrent line read from the top steram
//void InputHandler:: removeLine() const{
	//std::stringstream().swap(*m_curLineRead);
//}
