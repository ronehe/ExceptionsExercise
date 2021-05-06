#include <InputHandler.h>
/*
constarctor, enters the first stream in the top of the stack
 */ 
//"istr" : 
InputHandler::InputHandler(streamObj& istr) {
	m_streams = new std::stack<streamObj*>;
	m_curLineRead = new std::stringstream();
	addStream(istr);
	//readNewLine();
}
//should probebly gets *
void InputHandler::addStream(streamObj& istr) {
	m_streams->push(&istr);
}

void InputHandler::removeStream() const {
	if (auto p = dynamic_cast<std::ifstream*>(m_streams->top())) {
		p->close();
	}
	delete m_streams->top();
	m_streams->pop();
}

void InputHandler::readNewLine() const{
	auto temp = std::string();
	std::getline(*(m_streams->top()), temp);
	if ((m_streams->top()->eof())) {
		removeStream();
		readNewLine();
		return;
	}
	m_curLineRead->str(temp);
}

void InputHandler::handleEOF() {
	removeStream();
	auto temp = std::string();
	std::getline(*(m_streams->top()), temp);
	(*m_curLineRead) << temp;
}

InputHandler::~InputHandler() {
	delete m_curLineRead;
	delete m_streams;
}
