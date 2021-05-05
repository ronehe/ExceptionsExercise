#include<fstream>
#include<stack>
#include <sstream>

typedef std::istream streamObj;

class InputHandler {
public:
	InputHandler(streamObj& istr);
	void addStream(streamObj& istr);
	void removeStream();
	void readNewLine();
	template<typename T>
	friend void operator>>(InputHandler &, T &);
private:
	std::stack<streamObj*> *m_streams;
	std::stringstream m_line;
};
/// global operator >>  for handling the top of the stack which is the current stream  
template<typename T>
void operator>>(InputHandler&cur, T &into ){
	if (cur.m_line.eof()) { //used to check if line read from file is over, eof does not trigger in std::cin
		cur.readNewLine();
	}
	cur.m_line >> into;
}
