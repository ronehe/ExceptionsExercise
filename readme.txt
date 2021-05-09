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

**"read fileName"**- reads from a file

**"resize size "**- sets the max capacity of functions in the calculator 

**"help"** - Prints this help screen
**"exit"**- Exits the program

**NOTE**: every number in this function is rounded to 2 points after the decimal dot, beside powers in polynomials

# Details and design
The functions are displayed on the terminal in the form of a list, 
onto which the user can add the wanted function, 
using commands that operate on a function or a pair of functions.

the calculator excepets any kind of stream, *the read functions can be read from a file again *

The main idea behind out implementation is to not touch the given code if we don't have to,
so we created classes that handle the entirey of input management with specific handling functions
in specific cases for files and cin seperately.



## Classes

InputHandler:
	The wrapper of all the input management classes. It handles the entire process of getting input regardless
	of origin, and essentially links between the calculator and the input sources.

	It has a stack as a private member containing pointers to custom classes created in order to distinguish between 
	files and cin. The access to each one of them is accessed using polymorphism by a common base stream class.

	It has a templated >> operator for getting input regardless of type, and customed functions that 
	assist in this matter.

	It has a stringstream member that contains the entire input line, from which >> operator extracts information.

	The dyanmic allocation is done because the >> operator is being used in const functions, and the actions described
	above are changing parts of the fields.
	
BaseStreamHandler:
	A base class used for implementing polymorphism on the contents of the stream stack of InputHandler.
	It has functions that are common for all sources of input, and abstract functions used to build custom functions
	for each specific source of input, such as handling errors. In the case of cin, the handling is mostly done
	by iterating through a loop until recieving a valid answer, and in files the handling is done by throwing exceptions
	that are catched further in code, since the handling of those exceptions must be done in one place.

CinHandler:
	Inherits from BaseStreamHandler. It is responsible of handling errors once one has been caught.

FileHandler:
	Inherits from BaseStreamHandler. It is mainly throwing exceptions because if those sepcific cases are originated
	from a file, there is a need to do fix them in a common fashion, and it is done using the try-catch.
	

# Data Structures
we decided to change the code as little as possible while adding the requested exceptions, so instead of recursively 
reading from a file (you can call the read function from a file as well), we decided to create an object of InputHandler 
which has a stack data structure - capable of collaborating between cin streams, and any other *istream* inherited classes
(like fstream for example).

# Noteworthy algorithms
using the read function from a file .
polymorphic functions used  whether its a cin handler or filehandler for a cleaner code .

# Known Bugs
None
