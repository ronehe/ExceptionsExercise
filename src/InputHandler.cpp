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
	
}

void InputHandler::ignoreLine() const {
	m_curLineRead->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* 
reads another line from the current first stream in the stack, doesnt matter if it is
a file or any istrem inherited class.

<after effects> :removes the stream if ended inserts in the new line - from getline.
*/

void InputHandler::readNewLine() const{
	auto temp = std::string();
	//as long as it is possible to get lines
	while(!m_streams->top()->getline(temp)){
		removeStream();
	}
	m_curLineRead->str(temp);
	m_curLineRead->clear();
}

//for indication if calculator is running
void InputHandler::startRunning() {
	m_streams->top()->startRunning();
}

//clearing handler
void InputHandler::clear() {
	m_curLineRead->clear();
}

InputHandler::~InputHandler() {
	delete m_curLineRead;
	while (m_streams->size() )
	{
		delete m_streams->top();
		m_streams->pop();
	}
}

//for getting the entire line in case of an error
std::string InputHandler::getLineRead() const {
	return (m_curLineRead->str());
}

//for checking if currently the line is empty, >> operator will behave differently in that case
bool InputHandler::lineIsEmpty()const {
	return(!m_curLineRead->rdbuf()->in_avail());
}
