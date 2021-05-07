#include <FunctionCalculator.h>
/*
constarctor, enters the first stream in the top of the stack
 */ 
//"istr" : 
InputHandler::InputHandler(std::pair <streamObj* , const std::string& > strP , FunctionCalculator* calc)
	: m_functionsCalculator(calc)
{
	m_streams = new std::stack<std::pair <streamObj*,  std::string>>;
	//creates new because the functions in the calculator are consts, 
		//and we tried as little as we can to change your code
	m_curLineRead = new std::stringstream();
	addStream(strP);
	//readNewLine();
}

//defalut constractor for standared input
InputHandler::InputHandler(streamObj* istr, FunctionCalculator* calc) 
: m_functionsCalculator(calc)
{
	std::pair<streamObj*, const std::string&> strP(istr,"standred input");
	m_streams = new std::stack<std::pair <streamObj*,  std::string >>;
	m_curLineRead = new std::stringstream();
	addStream(strP);

}



//inputs new stream in the stack
void InputHandler::addStream(std::pair <streamObj*, const std::string & > strP) {
	m_streams->push(strP);
}
//removes the recent stream from the stack
void InputHandler::removeStream() const {
	delete m_streams->top().first;//deleting the stream
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
	while (!std::getline(*(m_streams->top().first), temp)) {
		removeStream();
	}
	m_curLineRead->str(temp);
	m_curLineRead->clear();
	m_curLineRead->seekg(0, std::ios::beg);
}

bool InputHandler::isCin() const {
	return m_streams->top().first == &std::cin;
}

void InputHandler::clear() {
	m_curLineRead->clear();
}

InputHandler::~InputHandler() {
	delete m_curLineRead;
	while (m_streams->size() )
	{
		if(!isCin())
			delete(m_streams->top().first);
		m_streams->pop();
	}
}
std::string InputHandler::getLineRead() const {
	return (m_curLineRead->str());
}
//returns the file name of the current stream
const std::string InputHandler:: fileName() {
	return m_streams->top().second;
}
bool InputHandler::lineIsEmpty()const {
	return(!m_curLineRead->rdbuf()->in_avail());
}
//removes the currrent line read from the top steram
void InputHandler:: removeLine() const{
	std::stringstream().swap(*m_curLineRead);
	
}
