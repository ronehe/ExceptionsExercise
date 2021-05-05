#include <InputHandler.h>
InputHandler::InputHandler(std::istream& istr) {
	m_streams.push(&istr);
}


