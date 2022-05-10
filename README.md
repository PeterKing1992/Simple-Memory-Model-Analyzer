# Simple-Memory-Model-Analyzer
A C program that does a static analysis of your C program code, and generates a memory model graph representation of your program. 

How I solved the problem: 
At first, the assignment seemed very hard to me. I tried to implement the code by reading each word from the file and interpret the code and memory allocation of the code depending on what each word is and the order of the words. It was extremely tedious to do and extremely inefficient. 

I then reread the assignment instructions and found out that we can assume all variables are declared and initialized in the same line. This inspired me to change my code into reading the c file line by line and interpret each line accordingly by parsing each of the words in the line. This still did not work well for me, because there are so many possibilities for the variables to be declared and for the lines to change, and parsing the lines will involve a lot of if and else statements. 

Therefore, I changed my strategy once again. I reread the assignment instructions and found that we are supposed to assume that our program is analyzing functional code. I also got inspired by the decision tree concept in machine learning. Combined with these ideas, I sketched a decision tree that 
when fed an input(a line of code) can split it at each of its node based on what keywords are contained within the line, and at the leaf nodes, it categorizes the code in one of 12 categories. Then, I make functions that parse and interprets the line of code assuming that it has a certain structure based on which category it belongs to. This greatly speeds up the process of writing my code that prints memory information targeting each test case and made the code a lot more modular and understandable. 

So I followed this strategy to develop a class and a specific handler for each of the categories the line of code belongs following the decision tree I sketched. However, as I progress farther into the assignment, I noticed that certain assignment requirements were actually different from what I thought they were, so on top of my original design, I added new classes and special handlers to handle these edge cases. 

This assignment was overall not too easy, but I think it trained my analytical and problem solving skills quite a bit. 

An overview of the functions: 

There are many functions in the code, all of which I have documented using comments in my code(most of which are helper functions that do small things). Here I will just talk about each function’s purpose and functionality briefly, for more detailed documentations of these functions, please check the comments in my code. 

int getPointerSize(char* type)
Helper function that gets the size of a specific pointer type

int getSize(char* type)
Helper function that gets the size of a specific variable type

char* addStar(char* str)
Helper function that adds asteriks * to the end of its input string

char* addStarLeft(char* str)
Helper function that adds asteriks * to the left of input string

char* addArrayBrackets(char* str)
A helper function that adds "[]" to the end of its input string

char* trim(char* str)
 A helper function that removes any character that belongs to {' ', ';', '\n', '*', 13th ascii character} in its input string

char* collapseWhiteSpaces(char* str)
A helper function that removes all whitespaces in its input

removeLeadingWhiteSpaces(char* str)
A helper function that removes all the leading whitespaces in its input string

char* getStrBefore(char* str, char c)
A helper function that returns a substring formed by anything that is before character c in its input string str

char* getStrAfter(char* str, char c)
A helper function that gets substring in str that starts at index of first appearance of c and ends at index of the last character of str

int containsBefore(char* originalStr, char* searchedStr, char* splitChar)
A helper function that determines whether searchStr exist before splitChar in originalStr

int containsEmptySquareBrackets(char* str)
A helper function that determines if input string contains empty square brackets

int isEmpty(char* str)
 A helper function that determines if its input is an empty string that contains nothing other than whitespaces

int isFunction(char* str)
A helper function that determines if the input string is a function declaration

int startWithKeyword(char* str)
A helper function that determines whether its input string starts with a function or variable declaration keyword

char* getArraySize(char* str)
A helper function that gets the size of an array with a predefined size

int getPreDefinedArraySize(char* str)
A helper function that gets the size of an array with predefined content

int isForLoop(char* input)
A helper function that determines whether its input string is a for loop declaration

int classify(char* input)
A helper function that classify its input string into one of the 12 classes.     
Return 0: if input is a function declaration
    Return 1: if input is malloc declaration with its pointer and malloc function on the same line
    Return 2: if input is a pointer variable declaration with multiple variables declared on the same line
    Return 3: if input is a string literal declaration
    Return 4: if input is a single pointer variable declaration
    Return 5: if input is an array declaration with predefined content but not predefined size
    Return 6: if input is an array declaration with predefined size
    Return 7: if input is a declaration of multiple variables on the same line
    Return 8: if input is a declaration of a single variable
    Return 9: if input is a for loop declaration
    Return 10: if input is a malloc declaration without declaring the type of its pointer
Return -1: if input does not belong to any of the aforementioned classes

char* getFunctionParameters(char* function)
A helper function that gets the parameters its input string function declaration takes

void printVars(char* scope, char* code)
A helper function that prints out memory allocation and usage information incurred by its input string code, and specifies the name, scope, type, size of the memory used by code

int countVars(char* code)
A helper function that counts the number of variables declared in its input string

char* functionHandler(char* code)
A helper function that prints out memory allocation and usage information of its input string, which is a function declaration

int storeFunctionParam(char* code, char* vars[], int index)
A helper function that stores the parameters of its input stirng code(expected to be a function declaration) in vars(which is an array of pointers to char, so array of strings) at the appropriate indices

int functionVarCounter(char* code)
A helper function that counts the number of parameters in its input(a function declaration)

char* getFunctionName(char* code)
A helper function that gets the name of its input string function declaration

char* getPointerName(char* code)
A helper function that gets the name of its input string pointer declaration

char* getPointerType(char* code)
A helper function that gets the type of its input string pointer declaration

void printRO(char* scope, char* code)
A helper function that take prints out the memory allocation and usage information of its input string code(a line of string literal declaration)

char* getStrAfterAlloc(char* code)
A function that returns the substring found after "alloc" in its input string

char* evalMallocSize(char* code)
A helper function that returns the size malloced by the input string code(which calls malloc)

void printHeap(char* scope, char* code)
A helper function that prints out the memory allocation and usage information of memory used by input string code(which is a malloc declaration with its pointer and type declared on the same line)

void analyzeGlobalVars(char *fpath)
A helper function that analyzes the program specified by its input string fpath and prints out memory info of all the global vars in the program

void analyzeStackVars(char *fpath)
A helper function that prints out all the memory allocation and usage information of all the stack variables in the program specified by the input string path

void analyzeROData(char* fpath)
A helper function that prints out all the memory allocation and usage information of all the ROData variables in the program specified by the input string path

char* getVarnameType(char** vars, int size, char* varName)
A helper function and gets and returns the type of a variable initialized in its input varName

void analyzeHeap(char* fpath)
A helper function that prints out all the memory allocation and usage information of all the heap data allocation in the program specified by the input string path

void printTotalLinesAndFunctions(char* fpath)
A helper function that prints out the total number of lines in the program specified by its input path and the number of functions in it

void printFunctionNames(char* fpath)
A helper function that prints out all the function names in program specified by its input path

void printFunctionVarCount(char* fpath)
A helper function that prints out how many variables are declared in each function in the program specified by the input string path

int countBrackets(char* code)
A function that counts the number of '{' - the number of '}' in its input string

void printFunctionLines(char* fpath)
A helper function that prints out number of lines per function in the program specified by the input string path

void analyzeStats(char* fpath)
A helper function that calls necessary helper functions to print out the specific stats of the program specifed by the input path

int main(int argc, char** argv)
The main program that calls a variety of other helper functions to print out the necessary information about the memory model of the C program specified by the command line argument

Test Cases that I considered and their corresponding outputs: 
Case 1: 
	Type varname = …
	Or
	Type varname; 
Output: 
	Varname scope size type

Case 2: 
	Type function_name(type1 param1, type2 param2 …)
Output: 
	param1 function_name type1 sizeof(type1)
	param 2 function_name type2 sizeof(type2)

Case 3: 
for(int varname = 0 ; …)
Output: 
	Varname scope int sizeof(int)

Case 4: 
	Type var1, var2, var3; 
	Or
	Type var1, var2, var3 = …
Output
	Var1 scope type sizeof(type)
	Var2 scope type sizeof(type)
	Var3 scope type sizeof(type)

Case 5: 
	Type varname[num] = …; 
	Or
	Type varname[num]; 
Output: 
	Varname scope type[num] num*sizeof(type)

Case 6: 
	Type varname[] = {e1, e2, e2, …, eN}; 
Output: 
	Varname scope type[] N*sizeof(type)

Case 7: 
	Type* varname = malloc(N); 
Output: 
On the stack: varname scope type* sizeof(type)
On the heap: *varname scope type N

Case 8: 
	Type* varname; 
	Varname = malloc(N); 
Output: 
On the stack: varname scope type* sizeof(type)
On the heap: *varname scope type N

Case 9: 
Type * var1, *var2, *var3; 
Or
Type *var1, *var2, *var3 = …; 
Output: 
Var1 scope type* sizeof(type*)
Var2 scope type* sizeof(type*)
Var3 scope type* sizeof(type*)

Case 10: 
	Char* varname = “12345”; 
Output: 
On the stack: Varname scope char* sizeof(char*) 
On ROData: varname scope char* 5

Case 11: 
	Type* varname; 
	Or
	Type* varname = …; 
Output: 
	Varname scope type* sizeof(type*)

Note: one command argument is required to run the program, if no CLA is given or the path given in CLA is invalid, the program will raise an error and terminate
