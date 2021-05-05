#include <InputHandler.h>
InputHandler::InputHandler(streamObj& istr) {
	addStream(istr);
	//readNewLine();
}
void InputHandler::addStream(streamObj& istr) {
	istr.exceptions(std::ios::eofbit);
	m_streams.push(&istr);
}

void InputHandler::removeStream() {
	delete m_streams.top();
	m_streams.pop();
}

void InputHandler::readNewLine() {
	auto temp = std::string();
	if (m_streams.top()->eof()) {
		removeStream();
	}
	std::getline(*(m_streams.top()), temp);
	*m_line << temp;
}

void InputHandler::handleEOF() {
	removeStream();
	auto temp = std::string();
	std::getline(*m_streams.top(), temp);
	*m_line << temp;
}
