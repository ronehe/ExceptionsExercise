#include<fstream>
#include<stack>
#include <sstream>
#include <iostream>

class FunctionCalculator;
typedef std::istream streamObj;

class InputHandler {
public:
	InputHandler(std::pair <streamObj*, const std::string&  >strOb, FunctionCalculator*);
	InputHandler(streamObj* istr, FunctionCalculator*);
	~InputHandler();
	void addStream(std::pair <streamObj*,const  std::string & > strP);
	void removeStream() const;
	void readNewLine() const;
	bool isCin() const;
	void clear();
	const std::string fileName();
	bool lineIsEmpty()const;
	//removes the currrent line read from the top stream
	void removeLine()const;
	template<typename T>
	friend void operator>>(const InputHandler&, T&);
	std::string getLineRead() const;
private:
	std::stack<std::pair <streamObj*, std::string  >>* m_streams;
	std::stringstream* m_curLineRead;
	FunctionCalculator* m_functionsCalculator;
};

/*
global operator >>  for handling the top of the stack which is the current stream,
 doesnt matter which object wants the data from the operator
*/
// "curHandler"  :current handler object  </param>
// "into" :object for which the data will go into </param>
/* <after effects>  will remove empty top stream  from stack(empty streams are the once of which recognize the - "eof" method)
in newLineRead fun <after effects>*/
template<typename T>
void operator>>(const InputHandler&curHandlar, T &into ){
	if(curHandlar.lineIsEmpty())
		curHandlar.readNewLine();
	*(curHandlar.m_curLineRead) >> into;

	if ((*curHandlar.m_curLineRead).fail()) {
		//*curHandlar.removeLine();
		//*curHandlar.m_curLineRead->clear();
	throw std::invalid_argument::exception("invalid type has entered");
		}
	
	
		

	//if file has ended, set the input stream the previous stack
}

