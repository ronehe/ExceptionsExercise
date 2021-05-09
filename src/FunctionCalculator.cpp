#include "FunctionCalculator.h"


FunctionCalculator::FunctionCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_functions(createFunctions()), m_istr(InputHandler(new CinHandler(&istr, this))), m_ostr(ostr)
{
    unsigned int firstSize;
    m_ostr << "please enter the max size functions between [2,100]  : ";
    m_istr >> firstSize;
    while (firstSize < 2 || firstSize > 100) {
        std::cin.clear();
        m_ostr << "please try a valid size (bigger  1 lower than 101)";
        m_istr >> firstSize;
    }
    m_maxFunctions = firstSize;
    m_istr.startRunning();
}


void FunctionCalculator::printFunctionList() {
    m_ostr << '\n';
    printFunctions();
    m_ostr << "Enter command ('help' for the list of available commands): ";
}

void FunctionCalculator::run()
{

    m_ostr << std::setprecision(2) << std::fixed;
    do
    {
        try {
            const auto action = readAction();
            runAction(action);
        }


        catch (std::out_of_range& e) {
            m_ostr << e.what() << std::endl;
        }




        catch (std::invalid_argument::exception& e) {
            m_ostr << e.what();
            m_istr.handleInvalidArgument(m_ostr);
        }
    } while (m_running);
}

void FunctionCalculator::eval()
{
    if (!checkParam(EVAL_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("evaluate  requires 2 parmeters functions and the X");
    if (auto i = readFunctionIndex(); i)
    {
        auto x = 0.;
        m_istr >> x;
        auto sstr = std::ostringstream();

        sstr << std::setprecision(2) << std::fixed << x;
        m_ostr << m_functions[*i]->to_string(sstr.str())
            << " = "
            << (*m_functions[*i])(x)
            << '\n';
    }
}

void FunctionCalculator::poly()
{
    auto n = 0;
    m_istr >> n;
    const unsigned int POLY_ARGS=n+2;
    //sends the amount of line arguments which are supposed to be
    if (!checkParam(POLY_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception(("reqired "+std::to_string(n)+" coefficents").data());

    auto coeffs = std::vector<double>(n);
    for (auto& coeff : coeffs){
        m_istr >> coeff;
    }
    (m_maxFunctions > m_functions.size()) ?
        m_functions.push_back(std::make_shared<Poly>(coeffs)) :
        throw std::invalid_argument::exception("there is no more sapce in the calculator");
}

void FunctionCalculator::log()
{
    if (!checkParam(LOG_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("log requires 2 parmeters : base, exponent");
    auto base = 0.;
    m_istr >> base;
    if (base ==1 ||base <=0)throw std::logic_error::exception("base of log suppose to be bigger than zero and diffrent then one");
    if (auto f = readFunctionIndex(); f)
    {
        (m_maxFunctions > m_functions.size()) ?
            m_functions.push_back(std::make_shared<Log>(base, m_functions[*f])) :
            throw std::invalid_argument::exception("there is no more sapce in the calculator");
    }
}

void FunctionCalculator::del()
{
    if (!checkParam(DEL_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("del(ete) requires 1 parmeter : the functions number");
    if (auto i = readFunctionIndex(); i)
    {
        m_functions.erase(m_functions.begin() + *i);
    }
}

void FunctionCalculator::help()
{
    if (!checkParam(HELP_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("help requires no parmeters");
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}

void FunctionCalculator::exit()
{
    if (!checkParam(EXIT_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("exit requires no parmeters");
    m_ostr << "Goodbye!\n";
    m_running = false;
}

void FunctionCalculator::resize()
{
    if (!checkParam(RESIZE_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("resize requires 1 parmeter: new size");
	unsigned int newSize;
	m_istr >> newSize;
	if (newSize < MIN_LIST_SIZE || newSize > MAX_LIST_SIZE)
		m_istr.handleOutOfRange(newSize);

	if (newSize > m_maxFunctions)
        m_maxFunctions = newSize;
	else if (newSize < m_functions.size()) {
        if(m_istr.handleOverloadFunctionList()){
			m_maxFunctions = newSize;
			m_functions.resize(m_maxFunctions);
		}
	}
	else
		m_maxFunctions = newSize;
}

void FunctionCalculator::read() {
    if (!checkParam(READ_ARGS, m_istr.getLineRead()))
        throw std::logic_error::exception("read requires 1 parmeter");
    auto fileName=std::string();
    m_istr >> fileName;
    std::ifstream *newF  = new std::ifstream ;//file pointer
    newF->open(fileName);
    if (!*newF)
        throw std::invalid_argument::exception(("file : " + fileName + " doesn't exists,").data());
    auto file = new FileHandler(newF, this, fileName);
    m_istr.addStream(file);
}

//function for handling y/n requests from user
//it goes through a loop and waits until a valid answer is recieved
bool FunctionCalculator::getYesNo(const std::string& requestMsg) {
    auto ans = std::string();
    auto invalidInput= true;
    while (invalidInput) {
        m_ostr << requestMsg;
        std::getline(std::cin, ans);
        if (ans != "y" && ans != "n") {
            m_ostr << "Please enter y/n\n";
            continue;
        }
        invalidInput = false;
    }
    return ans == "y";
}

//function for getting a valid value of size of the list
//it iterates in a loop until a valid value is entered
unsigned int FunctionCalculator::getValidListLength() {
    unsigned int num = 0;
    auto invalidAns = true;
    do {
        std::cout << "Enter a number between " << MIN_LIST_SIZE << "and " << MAX_LIST_SIZE << " : ";
        std::cin.clear();
        std::cin.ignore();
        if (!(std::cin >> num)) continue;
    } while (num < MIN_LIST_SIZE || num > MAX_LIST_SIZE);
    std::cin.ignore();
    return num;
}

//for printing the function list - is used once std::cin is getting a new line from user
void FunctionCalculator::printFunctions() const
{
    m_ostr << "List of available gates:\n";
    for (decltype(m_functions.size()) i = 0; i < m_functions.size(); ++i)
    {
        if (m_functions[i] == nullptr) break;
        m_ostr << i << ".\t" << m_functions[i]->to_string("x") << '\n';
    }
    m_ostr << '\n';
}

std::optional<int> FunctionCalculator::readFunctionIndex() const
{
    auto i = 0;
    m_istr >> i;
    if (i >= m_functions.size())
    {
        throw std::invalid_argument::exception(("Function #" + std::to_string(i) + " doesn't exist").data());
        //m_ostr << "Function #" << i << " doesn't exist\n";
        return {};
    }
    return i;
}

FunctionCalculator::Action FunctionCalculator::readAction() const
{
    auto action = std::string();
    m_istr >> action;

    for (decltype(m_actions.size()) i = 0; i < m_actions.size(); ++i)
    {
        if (action == m_actions[i].command)
        {
            return m_actions[i].action;
        }
    }

    return Action::Invalid;
}

void FunctionCalculator::runAction(Action action)
{
    
        switch (action)
        {
			default:
				m_ostr << "Unknown enum entry used!\n";
				break;

			case Action::Invalid:

                throw std::invalid_argument::exception("command not found");
				break;

			case Action::Eval:   eval();             break;
			case Action::Poly:   poly();             break;
			case Action::Mul:    binaryFunc<Mul>();  break;
			case Action::Add:    binaryFunc<Add>();  break;
			case Action::Comp:   binaryFunc<Comp>(); break;
			case Action::Log:    log();              break;
			case Action::Del:    del();              break;
			case Action::Help:   help();             break;
			case Action::Exit:   exit();             break;
			case Action::Resize: resize();           break;
            case Action::Read:   read();             break;
        }
}


FunctionCalculator::ActionMap FunctionCalculator::createActions()
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num x - compute the result of function #num on x",
            Action::Eval
        },
        {
            "poly",
            "(nomial) N c_0 c_1 ... c_(N-1) - creates a polynomial with N coefficients",
            Action::Poly
        },
        {
            "mul",
            "(tiply) num1 num2 - Creates a function that is the multiplication of "
            "function #num1 and function #num2",
            Action::Mul
        },
        {
            "add",
            " num1 num2 - Creates a function that is the sum of function #num1 and "
            "function #num2",
            Action::Add
        },
        {
            "comp",
            "(osite) num1 num2 - creates a function that is the composition of "
            "function #num1 and function #num2",
            Action::Comp
        },
        {
            "log",
            " N num - create a function that is the log_N of function #num",
            Action::Log
        },
        {
            "del",
            "(ete) num - delete function #num from the function list",
            Action::Del
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        },
        {
            "resize",
            " num - resize the size of the list to max #num",
            Action::Resize
        },
        {
            "read",
            " fileName - read from file #fileName",
            Action::Read
        }
    };
}

FunctionCalculator::FunctionList FunctionCalculator::createFunctions()
{
    return FunctionList
    {
        std::make_shared<Sin>(),
        std::make_shared<Ln>()
    };
}
//creating a defalut check for amount of arguments 


/// <summary>
/// counts the amount of parameters in the line read from user and compares to the right amount
/// </summary>
/// <param name="numOfArguments"> num of arguments for the requested function +the name of the function{ num of arg + 1} </param>
/// <param name="lineOfData">the line for which the function requested</param>
bool FunctionCalculator::checkParam(const unsigned int & numOfArguments,const std::string& lineOfData) {
    std::stringstream cur(lineOfData);
    std::string temp;
    unsigned int counter=0;
    while (cur >> temp) {
        counter++;
    }
    return(counter == numOfArguments);

}