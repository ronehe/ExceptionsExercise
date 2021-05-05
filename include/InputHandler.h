#include<fstream>
#include<stack>
typedef std::istream streamObj;
class InputHandler {
public:

	InputHandler(streamObj& istr);
	
	//addStream(streamObj& istr);
	template<typename T>
	friend void operator>>(const InputHandler &, T &);
private:
	std::stack<streamObj*>m_streams;

};
/// global operator >>  for handling the top of the stack which is the current stream  
template<typename T>
void operator>>(const InputHandler&cur, T &into ){
	*(cur.m_streams.top()) >> into;
}

