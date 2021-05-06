#include <InputHandler.h>
/*
constarctor, enters the first stream in the top of the stack
 */ 
//"istr" : 
InputHandler::InputHandler(streamObj* istr) {
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
}
/* 
reads anouther line from the current higest stream in the stack doesnt matter if it is
a file or any istrem inherited class.

<after effects> :removes the stream if ended inserts in the new line - from getline.
*/
void InputHandler::readNewLine() const{
	auto temp = std::string();
	//checkes if the read failed
	if (!(std::getline(*(m_streams->top()), temp))){
		removeStream();
		readNewLine();
		return;
	}
	m_curLineRead->str(temp);
}



InputHandler::~InputHandler() {
	delete m_curLineRead;
	while (m_streams->size() )
	{
		delete(m_streams->top());
		m_streams->pop();
	}
		
}
