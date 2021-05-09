# Functions Calculator
**written by Ronen Heifetz && Leon Markovich**

# github 
https://github.com/ronehe/ExceptionsExercise

Functions Calculator is a calculator capable of performing basic operations on a given set of functions, such as generating new functions out of already generated once, and evaluation at a real point in the domain of a certain function.


**Following is the list of the calculator's available commands:**

**"eval(uate) num x "**- Evaluates function #num on x

**"poly(nomial)N c0 c1 ... cN-1"**- Creates a polynomial with N coefficients

**"mul(tiply)"** num1 num2 - Creates a function that is the multiplication of function #num1 and function #num2

**"add num1 num2 "**- Creates a function that is the sum of function #num1 and function #num2

**"comp(osite)"** num1 num2 - Creates a function that is the composition offunction #num1 and function #num2

**"log N num"** - Creates a function that computes log N of function #num

**"del(ete) num"**- Deletes function #num from function list

**"help"** - Prints this help screen
**"exit"**- Exits the program

**NOTE**: every number in this function is rounded to 2 points after the decimal dot, beside powers in polynomials

# Details and design
The functions are displayed on the terminal in the form of a list, onto which the user can add the wanted function, using commands that operate on a function or a pair of functions.

## Classes
**Function**: ADT base class from which all functions in the calculator inherit. it holds the equation for the function, and the calculation/print methods.

**Log**: The logarithm function. default constructor initializes to natural logarithm, additional constructor recieves a positive value and initalizes to logarithm in the given base.

**Sin**: The sin function

**Polynomial**: The polynomial function. has a constructor that gets vector of coefficients.

**ComplexFun**: ADT base class from which all user-built functions will inherit. 

**SumFunction**: for all functions that are generated using the addition operator

**MulFunction**: for all functions that are generated using the multiplication operator

**ComposeFunction**: for all functions that are generated using the composition operator

**List**: data structure of calculator.

## UML
![img](https://i.imgur.com/7svMebS.png)

# Data Structures
We built a class "Function_list" as data structure. it contains a vector for shared pointers of type Function (ADT).
It can add new functions to the vector, remove functions, and the entire program runs based on this class.

# Noteworthy algorithms
None
# Known Bugs
None
