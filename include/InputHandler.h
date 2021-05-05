#include<fstream>
#include<stack>
#include <sstream>
#include <iostream>

typedef std::istream streamObj;

class InputHandler {
public:
	InputHandler(streamObj& istr);
	void addStream(streamObj& istr);
	void removeStream();
	void readNewLine();
	void handleEOF();
	template<typename T>
	friend void operator>>(const InputHandler&, T&);
private:
	std::stack<streamObj*> m_streams;
	std::stringstream *m_line;
};
/// global operator >>  for handling the top of the stack which is the current stream  
template<typename T>
void operator>>(const InputHandler&cur, T &into ){
	*(cur.m_line) >> into;
}
