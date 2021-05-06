#include<fstream>
#include<stack>
#include <sstream>
#include <iostream>

typedef std::istream streamObj;

class InputHandler {
public:
	InputHandler(streamObj& istr);
	~InputHandler();
	void addStream(streamObj& istr);
	void removeStream() const;
	void readNewLine() const;
	void handleEOF();
	template<typename T>
	friend void operator>>(const InputHandler&, T&);
private:
	std::stack<streamObj*>* m_streams;
	std::stringstream* m_curLineRead;
};

/*
global operator >>  for handling the top of the stack which is the current stream
 doesnt care which object wants the data from the operator
*/
// "curHandler"  :current handler object  </param>
// "into" :object for which the data will go into </param>
/* <after effects>  will remove empty top stream  from stack(empty streams are the once of which recognize eof method)
in line reading func <after effects>*/
template<typename T>
void operator>>(const InputHandler&curHandlar, T &into ){
	*(cur.m_line) >> into;
	if (!(*curHandlar.m_line)) {
		curHandlar.m_line->clear();
		curHandlar.readNewLine();
		*(curHandlar.m_line) >> into;
	}
}
