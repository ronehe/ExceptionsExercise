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

## Classes

# Data Structures
we desided to change the code as little as posible while adding the requetsed exceptions, so instead of recursivly 
readding from a file (you can call the read fucntion from a file as well), we decided to create an object of InputHandler 
which has a stack data structure - capble of collaborating between cin streams, and any other *istream* inherited classes
(like fstream for example).

# Noteworthy algorithms
using the read function from a file .
polymorphic functions used  whether its a cin handler or filehandler for a cleaner code .

# Known Bugs
None
