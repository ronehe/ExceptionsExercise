#include <InputHandler.h>
InputHandler::InputHandler(streamObj& istr) {
	addStream(istr);
}
void InputHandler::addStream(streamObj& istr) {
	m_streams.push(&istr);

}

