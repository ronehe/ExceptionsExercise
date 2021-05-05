#include <InputHandler.h>
InputHandler::InputHandler(streamObj& istr) {
	m_streams.push(&istr);
}

