#include <InputHandler.h>
InputHandler::InputHandler(streamObj& istr) {
	m_streams = new std::stack<streamObj*>;
	m_line = new std::stringstream();
	addStream(istr);
	//readNewLine();
}
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
	m_line->str(temp);
}

void InputHandler::handleEOF() {
	removeStream();
	auto temp = std::string();
	std::getline(*(m_streams->top()), temp);
	(*m_line) << temp;
}

InputHandler::~InputHandler() {
	delete m_line;
	delete m_streams;
}
