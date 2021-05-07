#include "FunctionCalculator.h"

#include "Sin.h"
#include "Ln.h"
#include "Poly.h"
#include "Mul.h"
#include "Add.h"
#include "Comp.h"
#include "Log.h"

#include <istream>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <fstream>

FunctionCalculator::FunctionCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_functions(createFunctions()), m_istr(InputHandler(&istr, this)), m_ostr(ostr)
{
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
        if (m_istr.isCin())
            printFunctionList();
        try {
            const auto action = readAction();
            runAction(action);
        }

       
        catch (std::out_of_range& e) {
            m_ostr << e.what() << std::endl;
        }


        catch (MaximumFunctionsException& e) {
            m_ostr << e.what() << std::endl;
            if (y_n_catcher("The operation might delete some functions, would you like to continue? y/n")) {
                m_ostr << "Please enter a function to delete: ";
                del();
            }
        }

        catch (std::invalid_argument::exception &e) {
            //first we check if it is a file
            if (!m_istr.isCin()) {
                std::string cur;
                m_istr.clear();
                m_ostr <<"error : \n" <<m_istr.getLineRead()<<"\n";
                if (!y_n_catcher("would you like to continue reading? y/n"))
                    m_istr.removeStream();
                m_istr.readNewLine();
                //std::cin >> cur;
            }
            //m_ostr << e.what();
        }
    } while (m_running);
}

void FunctionCalculator::eval()
{
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
    auto coeffs = std::vector<double>(n);
    for (auto& coeff : coeffs)
    {
        m_istr >> coeff;
    }
    (m_maxFunctions > m_functions.size()) ?
        m_functions.push_back(std::make_shared<Poly>(coeffs)) :
        throw MaximumFunctionsException();
}

void FunctionCalculator::log()
{
    auto base = 0;
    m_istr >> base;
    if (base <=1)throw std::invalid_argument::exception("base of log suppose to be higher then one");
    if (auto f = readFunctionIndex(); f)
    {
        (m_maxFunctions > m_functions.size()) ?
            m_functions.push_back(std::make_shared<Log>(base, m_functions[*f])) :
            throw MaximumFunctionsException();
    }
}

void FunctionCalculator::del()
{
    if (auto i = readFunctionIndex(); i)
    {
        m_functions.erase(m_functions.begin() + *i);
    }
}

void FunctionCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}

void FunctionCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}

void FunctionCalculator::resize()
{
    
    try {
        unsigned int newSize;
        //m_istr.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        m_istr >> newSize;
        if (newSize < 2 || newSize > 100)
            throw std::out_of_range("Invalid size: can be resized only to values between 2 and 100, please enter a number again: ");
        if (newSize > m_maxFunctions)  m_maxFunctions = newSize;
        else  
            if (newSize < m_functions.size()) {
                if (y_n_catcher("The operation might delete some functions, would you like to continue? y/n")) {
                    m_maxFunctions = newSize;
                    m_functions.resize(m_maxFunctions);
                }
            }
            else
                m_maxFunctions = newSize;
        }
    catch (std::out_of_range& e) {
        m_ostr << e.what() << std::endl;
        this->resize();
    }
    catch (std::ios_base::failure& e) {
        m_ostr << e.what();
      //  m_istr.clear();
        this->resize();
    }
}

//function for handling y/n requests from user
//it goes throgh a loop and waits until a valid answer is recieved
bool FunctionCalculator::y_n_catcher(const std::string& requestMsg) {
    auto ans = std::string();
    auto ansIsStupid = true;
    while (ansIsStupid) {
        try {
            m_ostr << requestMsg; 
            std::getline(std::cin, ans);
            if (ans != "y" && ans != "n") {
                throw std::invalid_argument("the requested answer is either y or n");
            }
        }
        catch (std::invalid_argument& e) {
            m_ostr << e.what();
            continue;
        }
        break;
    }
    return ans == "y";
}

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
        m_ostr << "Function #" << i << " doesn't exist\n";
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
				m_ostr << "Command not found\n";
                throw std::invalid_argument::exception();
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

void FunctionCalculator::read() {
    auto fileName=std::string();
    m_istr >> fileName;
    std::ifstream *newF  = new std::ifstream ;//file pointer
    newF->open(fileName);
    m_istr.addStream(newF);
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
            " -resize the size of the list",
            Action::Resize
        },
        {
            "read",
            " -read from file",
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
