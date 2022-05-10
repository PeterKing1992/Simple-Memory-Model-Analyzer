//SimpleMemModAnalyzer.c gets the memory allocation information of your C program
//@Author Zhao Ji Wang
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Helper function that gets the size of a specific pointer type

    Take a char* type as a parameter that belongs to one of {"int", "char", "float"}

    Return the size of the appropriate pointer type
*/
int getPointerSize(char* type){
    if(strcmp(type, "int") == 0){
        return sizeof(int*); 
    }else if(strcmp(type, "char") == 0){
        return sizeof(char*); 
    }else if(strcmp(type, "float") == 0){
        return sizeof(float*); 
    }
    return -1; 
}

/*
    Helper function that gets the size of a specific variable type

    Takes a char* type as parameter that belongs to one of {"int", "char", "float"}

    Return the size of the appropriate variable type
*/

int getSize(char* type){
    if(strcmp(type, "int") == 0){
        return sizeof(int); 
    }else if(strcmp(type, "char") == 0){
        return sizeof(char); 
    }else if(strcmp(type, "float") == 0){
        return sizeof(float); 
    }else if(strcmp(type, "void") == 0){
        return 1; 
    }
    return -1; 
}

/*
    Helper function that adds asteriks * to the input string

    Take char* str as parameter

    Return the same content of str followed by a "*"

*/

char* addStar(char* str){
    char* newStr = malloc(100*sizeof(char)); 
    strncpy(newStr, str, 99); 
    newStr[strlen(str)] = '*'; 
    newStr[strlen(str) + 1] = '\0';  
    return newStr; 
}

/*
    Helper function that adds asteriks * to the left of input string

    Take char* str as parameter

    Return the same content of str followed by a "*"

*/

char* addStarLeft(char* str){
    char* newStr = malloc(100*sizeof(char)); 
    newStr[0] = '*'; 
    for(int i = 0; i < strlen(str); i ++){
        newStr[i + 1] = str[i]; 
    }
    
    newStr[strlen(str) + 1] = '\0'; 
    return newStr; 
}


/*
    A helper function that adds "[]" to the end of its input string

    Take str of type char* as parameter

    Return str with a "[]" append to it at the end
*/
char* addArrayBrackets(char* str){
    char* newStr = malloc(100*sizeof(char)); 
    strncpy(newStr, str, 99); 
    newStr[strlen(str)] = '['; 
    newStr[strlen(str) + 1] = ']';  
    newStr[strlen(str) + 2] = '\0';  
    return newStr; 
}

/*
    A helper function that removes any character that belongs to {' ', ';', '\n', '*', 13th ascii character} in its input string

    Take str of type char* as parameter input

    Return the same content as str but with any character that belongs to {' ', ';', '*', 13th ascii character} removed
*/

char* trim(char* str)
{
    if(str == NULL){
        return NULL; 
    }
    char *newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != ';' && str[i] != ' ' && ((int)str[i]) != 13 && str[i] != '\n' && str[i] != ',' && str[i] != '*'){
            // newStr[i] = str[i]; 
            newStr[charCount] = str[i]; 
            charCount ++; 
        }
    }
    newStr[charCount] = '\0';
    return newStr;  
}


/*
    A helper function that removes all whitespaces in its input

    Take str of type char* as parameter

    Return the same content as str except with all whitespaces removed
*/
char* collapseWhiteSpaces(char* str){
    if(str == NULL){
        return NULL; 
    }
    char *newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != ' '){
            newStr[charCount] = str[i]; 
            charCount ++; 
        }
    }
    newStr[charCount] = '\0';
    return newStr;  
}

/*
    A helper function that removes all the leading whitespaces in its input string

    Take str of type char* as parameter

    Return a new string that is str with leading whitespaces removed
*/
char* removeLeadingWhiteSpaces(char* str){
    if(str == NULL){
        return NULL; 
    }
    char *newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    int copyingFlag = 0; 
    int offset = 0; 
    for(int i = 0; i < strlen(str); i++){
        if(copyingFlag == 1){
            charCount ++; 
            newStr[i - offset] = str[i]; 
        }else if(str[i] != ' '){
            copyingFlag = 1; 
            offset = i; 
            charCount ++; 
            newStr[i - offset] = str[i]; 
        }
    }
    newStr[charCount] = '\0';
    return newStr;  

}

/*
    A helper function that returns a substring formed by anything that is before character c in its input string str

    Takes str of type char* and c of type char as parameters

    Return substring of str from index 0 to index of c in str
*/
char* getStrBefore(char* str, char c){
    char *newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    for(int i = 0; i < strlen(str); i ++){
        if(str[i] != c){
            newStr[i] = str[i]; 
            charCount ++;  
        }else{
            break; 
        }
    }
    newStr[charCount] = '\0'; 
    return newStr; 
}

/*
    A helper function that gets substring in str that starts at index of first appearance of c and ends at index of the last character of str

    Take str of type char* and c of type char as parameters

    Return a substring in str that starts at index of c and ends at the index of the last character of str
*/
char* getStrAfter(char* str, char c){
    char *newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    int copyingFlag = 0; 
    int offset = 0; 
    for(int i = 0; i < strlen(str); i ++){
        if(str[i] == c && copyingFlag == 0){
            copyingFlag = 1; 
            offset = i + 1; 
        }else if(copyingFlag == 1){
            newStr[i - offset] = str[i]; 
            charCount ++; 
        }
    }
    newStr[charCount] = '\0'; 
    return newStr; 
}

/*
    A helper function that determines whether searchStr exist before splitChar in originalStr

    Take originalStr, searchedStr, and splitChar All of type char* as parameters

    Return 1 if searchedStr is exist before splitChar in originalStr
    Return -1 otherwise
*/
int containsBefore(char* originalStr, char* searchedStr, char* splitChar){
    char str[100]; 
    strncpy(str, originalStr, 99); 
    char* strBefore = strtok(str, splitChar); 
    if(strstr(strBefore, searchedStr)){
        return 1; 
    }
    return -1;  
}

/*
    A helper function that determines whether searchStr exist before splitChar in originalStr

    Take originalStr, searchedStr, and splitChar All of type char as parameters

    Return 1 if searchedStr is exist before splitChar in originalStr
    Return -1 otherwise
*/
int containsCharBefore(char* originalStr, char searchedStr, char* splitChar){
    char str[100]; 
    strncpy(str, originalStr, 99); 
    char* strAfter = getStrAfter(str, searchedStr); 
    if(strstr(strAfter, splitChar)){
        return 1; 
    }
    return -1;  
}

/*
    A helper function that determines if input string contains empty square brackets

    Take str of type char* as input

    Return 1 if str contains a pair of '[' and ']' with nothing or only whitespaces in between
    Return -1 otherwise
*/
int containsEmptySquareBrackets(char* str){
    int emptyBrackets = 0; 
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '['){
            emptyBrackets = 1; 
        }else if(emptyBrackets == 1 && str[i] == ']'){
            return 1; 
        }else if(emptyBrackets == 1 && str[i] != ' '){
            emptyBrackets = 0; 
        }
    }
    return emptyBrackets; 
}

/*
    A helper function that determines if its input is an empty string that contains nothing other than whitespaces

    Take str of type char* as parameter

    Return 1 if str is empty or only contains whitespaces
    Return -1 otherwise
*/
int isEmpty(char* str){
    if(strlen(trim(str)) <= 0){
        return 1; 
    }
    return -1; 
}

/*
    A helper function that determines if the input string is a function declaration

    Take str of type char* as parameter

    Return 1 if str is a function declaration
    Return -1 otherwise
*/
int isFunction(char* str){
    char newStr[100]; 
    strncpy(newStr, str, 99); 
    strtok(newStr, " ");
    // char* firstWord = strtok(newStr, " ");
    char* secondWord = strtok(NULL, " "); 
    char* thirdWord = strtok(NULL, " "); 
    char* fourthWord = strtok(NULL, " "); 
    
    if(secondWord != NULL){
        if(strstr(secondWord, "=")){
            return -1; 
        }
        if(strstr(secondWord, "(")){
            return 1; 
        }
    } 
    if(thirdWord != NULL){
        if(strstr(thirdWord, "=")){
            return -1; 
        }
        if(strstr(thirdWord, "(")){
            return 1; 
        }
    }
    if(fourthWord != NULL){
        if(strstr(fourthWord, "=")){
            return -1; 
        }
        if(strstr(fourthWord, "(")){
            return 1; 
        }
    }
    return -1; 
}

/*
    A helper function that determines whether its input string starts with a function or variable declaration keyword

    Take str of type char* as parameter

    Return 1 if str starts with one of {int, char, float, int*, char*, float*, void}
    Return -1 otherwise
*/
int startWithKeyword(char* str){
    char newStr[100]; 
    strncpy(newStr, str, 99); 
    char* firstWord = trim(strtok(newStr, " ")); 
    int size = getSize(firstWord); 
    if(size <= 0){
        return -1; //Does not start with a keyword
    }
    return 1; 
}

/*
    A helper function that gets the size of an array with a predefined size

    Take str of type char* as parameter, expected to be an array declaration of predefined size

    Return the size of array declared in str
*/

char* getArraySize(char* str){
    char* size = malloc(100 * sizeof(char)); 
    int copyingFlag = 0; 
    int charCount = 0; 
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '['){
            copyingFlag = 1; 
        }else if(str[i] == ']'){
            break; 
        }else if(copyingFlag == 1 && str[i] != ' '){
            size[charCount] = str[i]; 
            charCount ++; 
        }
    }
    size[charCount] = '\0'; 
    return size; 
}

/*
    A helper function that gets the size of an array with predefined content

    Take str of type char* as parameter, expected to be an array declaration that specifies the array content but not size

    Return size of the array declared in str
*/

int getPreDefinedArraySize(char* str){
    char size[100]; 
    int copyingFlag = 0; 
    int charCount = 0; 
    int sizeInt = 0; 

    char bracketStart = '{'; 
    char bracketEnd = '}'; 

    if(strstr(str, "\"")){
        bracketStart = '\"'; 
        bracketEnd = '\"'; 
    }

    for(int i = 0; i < 100; i++){
        if(str[i] == bracketStart && copyingFlag == 0){
            copyingFlag = 1; 
        }else if(str[i] == bracketEnd || str[i] == '\0'){
            break; 
        }else if(copyingFlag == 1){ 
            size[charCount] = str[i]; 
            charCount ++; 
        }
    }
    size[charCount] = '\0'; 

    if(strstr(str, "\"")){
        int len = 0; 
        for(int i = 0; i < 100; i ++){
            if(size[i] == '\0'){
                break; 
            }
            len ++;
        }
        return len; 
    }else{
        char* firstElement = strtok(size, ","); 
        if(firstElement != NULL){
            if(isEmpty(firstElement) != 1){
                sizeInt ++; 
            }
        }
        char* nextElement = strtok(NULL, ","); 
        while(nextElement != NULL){
            sizeInt ++; 
            nextElement = strtok(NULL, ","); 
        }
    }
    return sizeInt; 
}

/*
    A helper function that determines whether its input string is a for loop declaration

    Take input of type char*

    Return 1 if input is a for loop declaration
    Return 0 otherwise
*/

int isForLoop(char* input){
    char* code = removeLeadingWhiteSpaces(input); 
    int containsFor = 0; 
    for(int i = 0; i < strlen(code) ; i++){
        if(code[i] == 'f' && containsFor == 0){
            containsFor = 1; 
        }else if(code[i] == 'o' && containsFor == 1){
            containsFor = 2; 
        }else if(code[i] == 'r' && containsFor == 2){
            containsFor = 3; 
        }else if((code[i] == '(' || code[i] == ' ') && containsFor == 3){
            return 1; 
        }else{
            return 0; 
        }
    }
    return 0; 
}

/*
    A helper function that classify its input string into one of the 12 classes: 
    
    Take input of type char* as parameter

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
*/
int classify(char* input){
    if(isEmpty(input) == 1){
        return -1; 
    }
    if(startWithKeyword(input) != 1){
        if(isForLoop(input) == 1){ // is a for loop
            return 9; 
        }else if(strstr(input, "alloc")){ // start allocating space without a type declaration
            if(strstr(input, "=")){
                if(containsCharBefore(input, '=', "alloc") == 1){
                // printf("%s\n", input); 
                    if(containsBefore(input, "//", "alloc") != 1){
                        return 10; 
                    }
                }
            }
        }
        return -1; 
    }
    if(isFunction(input)==1){
        return 0; //Current line is a function header
    }
    if(containsBefore(input, "*", "=") == 1){
        if(strstr(input, "alloc")){
            return 1;  //Current line is a malloc statement
        }else{
            if(containsBefore(input, ",", "=") == 1){
                return 2; // Multiple pointers declared in one line
            }else{
                if(strstr(input, "char")){
                    if(strstr(input, "=")){
                        if(strstr(input, "\"")){
                            return 3; // Some String literal
                        }else{
                            return 4; 
                        }
                    }else{
                        return 4; // Single Regular Pointer
                    }
                }else{
                    return 4; // Single Regular Pointer
                }
            }
        }
    }else{
        if(containsBefore(input, "[", "=") == 1){
            if(containsEmptySquareBrackets(input) == 1){
                return 5; //Array without explicitly defining the length
            }else{
                return 6; //Array with initialized Length
            }
        }else{
            if(containsBefore(input, ",", "=") == 1){
                return 7; //Multiple primitive datatypes variables defined on the same line
            }else{
                return 8; //Single variable being defined
            }
        }
    }
    return -1; 

}

/*
    A helper function that gets the parameters its input string function declaration takes

    Take parameter function of type char*, expected to be a function declaration

    Return the parameters function takes
*/
char* getFunctionParameters(char* function){
    char* newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    int copyingFlag = 0; 
    for(int i = 0; i < strlen(function); i ++){
        if(function[i] == '('){
            copyingFlag = 1; 
        }else if(function[i] == ')'){
            break; 
        }else if(copyingFlag == 1){
            newStr[charCount] = function[i]; 
            charCount ++; 
        }
    }
    newStr[charCount] = '\0'; 
    return newStr; 
}

/*
    A helper function that prints out memory allocation and usage information incurred by its input string code, and specifies the name, scope, type, size of the memory used by code

    Take scope and code of both type char* as input
        scope is the scope of code(which function the line belongs to)
        code is the line in the program

    Return nothing
*/

void printVars(char* scope, char* code){
    char newStr[100]; 
    strncpy(newStr, code, 99); 

    int class = classify(code); 

    char* type; 
    char* varName; 
    int size = -1; 
    if(class == 8){ // Single variable defined
        char* beforeEquals = getStrBefore(newStr, '='); 
        strncpy(newStr, beforeEquals, 99); 
        type = trim(strtok(newStr, " "));
        size = getSize(type); 
        varName = trim(strtok(NULL, " ")); 
    }else if(class == 7){ // Multiple variables in one line
        strtok(newStr, "="); 
        type = trim(strtok(newStr, " ")); 
        size = getSize(type); 

        char* varNames = collapseWhiteSpaces(getStrAfter(removeLeadingWhiteSpaces(code), ' ')); 
        strtok(varNames, "="); 
        varName = trim(strtok(varNames, ",")); 
        printf("   %s   %s   %s   %d\n", varName, scope, type, size); 
        varName = trim(strtok(NULL, ",")); 
        while(varName != NULL){
            printf("   %s   %s   %s   %d\n", varName, scope, type, size); 
            varName = trim(strtok(NULL, ",")); 
        }
        size = -1; 
    }else if(class == 6){ // Array with Length defined
        strtok(newStr, "="); 
        char* singleType = trim(strtok(newStr, " ")); 
        char* beforebrackets = getStrBefore(code, '['); 
        varName = trim(getStrAfter(removeLeadingWhiteSpaces(beforebrackets), ' ')); 

        char* stringSize = getArraySize(code); 
        printf("   %s   %s   %s[%s]   %s", varName, scope, singleType, stringSize, stringSize); 
        printf("*sizeof(%s)\n", singleType); 
        size = -1; 
    }else if(class == 5){ // Pre defined array
        strtok(newStr, "="); 
        char* afterEquals = strtok(NULL, "="); 
        char* singleType = trim(strtok(newStr, " ")); 
        char* beforebrackets = getStrBefore(code, '['); 
        varName = trim(getStrAfter(removeLeadingWhiteSpaces(beforebrackets), ' ')); 
        if(afterEquals == NULL){
            size = getPointerSize(singleType); 
            type = addStar(singleType); 
        }else{
            size = getPreDefinedArraySize(code); 
            type = addArrayBrackets(singleType); 
            if(strstr(type, "char")){
                size ++; 
            }
            printf("   %s   %s   %s   %d", varName, scope, type, size); 
            printf("*sizeof(%s)\n", singleType); 
            size = -1; 
        }
    }else if(class == 4 || class == 3 || class == 1){ // Regular String Pointers or malloc or String literals
        char* beforeEquals = getStrBefore(removeLeadingWhiteSpaces(newStr), '='); 
        type = trim(strtok(beforeEquals, "*")); 
        varName = trim(strtok(NULL, "*")); 

        size = getPointerSize(type); 
        type = addStar(type); 
    }else if(class == 2){
        strtok(newStr, "="); 
        type = trim(strtok(newStr, " ")); 
        size = getPointerSize(type); 
        type = addStar(type); 

        char* varNames = collapseWhiteSpaces(getStrAfter(removeLeadingWhiteSpaces(code), ' ')); 
        strtok(varNames, "="); 
        varName = trim(strtok(varNames, ",")); 
        printf("   %s   %s   %s   %d\n", varName, scope, type, size);  
        varName = trim(strtok(NULL, ",")); 
        while(varName != NULL){
            printf("   %s   %s   %s   %d\n", varName, scope, type, size); 
            varName = trim(strtok(NULL, ",")); 
        }
        size = -1; 
    }else if(class == 9){
        char* startingInt = getStrAfter(newStr, '('); 
        startingInt = getStrBefore(startingInt, ';'); 
        size = -1; 
        printVars(scope, startingInt); 
    }

    if(size > 0){
        if(strcmp(varName, "argv") == 0){
            type = addStar(type); 
        }
        printf("   %s   %s   %s   %d\n", varName, scope, type, size); 
    }
}

/*
    A helper function that counts the number of variables declared in its input string

    Take code of type char* as parameter

    Return number of variables declared by code
*/
int countVars(char* code){
    char newStr[100]; 
    strncpy(newStr, code, 99); 
    int varCount = 0; 

    int class = classify(code); 

    char* varName; 
    if(class == 8){ // Single variable defined
        varCount ++; 
    }else if(class == 7){ // Multiple variables in one line
        strtok(newStr, "="); 
        strtok(newStr, " "); 

        char* varNames = collapseWhiteSpaces(getStrAfter(removeLeadingWhiteSpaces(code), ' ')); 
        strtok(varNames, "="); 
        varName = trim(strtok(varNames, ",")); 
        varCount ++; 
        varName = trim(strtok(NULL, ",")); 
        while(varName != NULL){
            varCount ++; 
            varName = trim(strtok(NULL, ",")); 
        }
    }else if(class == 6){ // Array with Length defined
        varCount ++; 
    }else if(class == 5){ // Pre defined array
        varCount ++; 
    }else if(class == 4 || class == 3 || class == 1){ // Regular String Pointers or String literals
        varCount ++; 
    }else if(class == 2){
        strtok(newStr, "="); 
        strtok(newStr, " "); 

        char* varNames = collapseWhiteSpaces(getStrAfter(removeLeadingWhiteSpaces(code), ' ')); 
        strtok(varNames, "="); 
        varName = trim(strtok(varNames, ",")); 
        varCount ++; 
        varName = trim(strtok(NULL, ",")); 
        while(varName != NULL){
            varCount ++;  
            varName = trim(strtok(NULL, ",")); 
        }
    }else if(class == 9){
        char* startingInt = getStrAfter(newStr, '('); 
        startingInt = getStrBefore(startingInt, ';'); 
        varCount += countVars(startingInt); 
    }
    return varCount; 
}

/*
    A helper function that prints out memory allocation and usage information of its input string, which is a function declaration

    Take code as input string, expected to be a function declaration

    Return nothing
*/

char* functionHandler(char* code){
    char* newStr; 
    newStr = getStrAfter(removeLeadingWhiteSpaces(code), ' '); 

    char* functionName = trim(getStrBefore(newStr, '(')); 

    char* parameters = getFunctionParameters(newStr); 
    char* firstParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 
    char* nextParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 

    if(firstParameter != NULL){
        printVars(functionName, firstParameter); 
    }
    while(isEmpty(nextParameter) != 1){
        printVars(functionName, nextParameter); 
        nextParameter = getStrBefore(parameters, ',');  
        parameters = getStrAfter(parameters, ','); 
    }

    return functionName; 

}

/*
    A helper function that stores the parameters of its input stirng code(expected to be a function declaration) in vars(which is an array of pointers to char, so array of strings) at the appropriate indices

    Take code of type char* and vars of type char** and index of type int as parameters
    code is a string that is expected to be a function declaration
    vars is an array to store the parameters of code
    index is the index at which the next parameter can be stored in vars

    Look at code determine what the parameters are and store the parameters each in a separate slot in vars

    Return the new index(which is right after the last inserted parameter in vars)
*/

int storeFunctionParam(char* code, char* vars[], int index){
    char* newStr; 
    newStr = getStrAfter(removeLeadingWhiteSpaces(code), ' '); 

    // char* functionName = trim(getStrBefore(newStr, '(')); 

    char* parameters = getFunctionParameters(newStr); 
    char* firstParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 
    char* nextParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 

    if(firstParameter != NULL){
        char* str = malloc(100*sizeof(char)); 
        strncpy(str, firstParameter, 99); 
        vars[index] = str; 
        index ++; 
    }
    while(isEmpty(nextParameter) != 1){
        char* str = malloc(100*sizeof(char)); 
        strncpy(str, nextParameter, 99); 
        vars[index] = str; 
        index ++; 
        // printf("%s\n", nextParameter); 
        nextParameter = getStrBefore(parameters, ',');  
        parameters = getStrAfter(parameters, ','); 
    }
    return index; 

}

/*
    A helper function that counts the number of parameters in its input(a function declaration)

    Take input code of type char* as parameter, which is expected to be a function declaration

    Return the number of parameters in code
*/
int functionVarCounter(char* code){
    char* newStr; 
    newStr = getStrAfter(removeLeadingWhiteSpaces(code), ' '); 
    int varCount = 0; 

    char* parameters = getFunctionParameters(newStr); 
    char* firstParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 
    char* nextParameter = getStrBefore(parameters, ','); 
    parameters = getStrAfter(parameters, ','); 

    if(firstParameter != NULL){
        varCount += countVars(firstParameter); 
    }
    while(isEmpty(nextParameter) != 1){
        varCount += countVars(nextParameter); 
        // printf("%s\n", nextParameter); 
        nextParameter = getStrBefore(parameters, ',');  
        parameters = getStrAfter(parameters, ','); 
    }

    return varCount; 

}

/*
    A helper function that gets the name of its input string function declaration

    Take code of type char* as its input, expected to be a function declaration

    Return the name of the function declared in code
*/
char* getFunctionName(char* code){
    char* newStr; 
    newStr = getStrAfter(removeLeadingWhiteSpaces(code), ' '); 

    char* functionName = trim(getStrBefore(newStr, '(')); 
    return functionName; 
}

/*
    A helper function that gets the name of its input string pointer declaration

    Take input code of type char*, expected to be a pointer declaration

    Return name of the pointer declared in code
*/
char* getPointerName(char* code){
    char* newStr; 
    newStr = getStrAfter(removeLeadingWhiteSpaces(code), ' '); 

    char* pointerName = trim(getStrBefore(newStr, '=')); 
    return pointerName; 
}

/*
    A helper function that gets the type of its input string pointer declaration

    Take input code of type char*, expected to be a pointer declaration

    Return type of the pointer declared in code
*/

char* getPointerType(char* code){
    char* newStr; 
    newStr = trim(getStrBefore(removeLeadingWhiteSpaces(code), ' ')); 
    return newStr; 
}

/*
    A helper function that take prints out the memory allocation and usage information of its input string code(a line of string literal declaration)

    Take scope and code both of type char* as parameters
        scope is the scope where code is found in the program(which function code is in)
        code is the string literal declaration

    Return nothing
*/

void printRO(char* scope, char* code){
    char* newStr; 
    newStr = getStrAfter(code, '"'); 
    newStr = getStrBefore(newStr, '"'); 
    char* type = "char*"; 
    char* varName = getPointerName(code); 
    int size = 0; 
    for(int i = 0; i < 200; i++){
        if(newStr[i] == '\0'){
            break; 
        }
        size ++; 
    }
    printf("   %s   %s   %s   %d", varName, scope, type, size+1); 
    printf("*sizeof(char)\n"); 
}

/*
    A function that returns the substring found after "alloc" in its input string

    Take code of type char* as input

    Return anything after "alloc" in input
*/

char* getStrAfterAlloc(char* code){
    int allocMatcher = 0; 
    char* newStr = malloc(100*sizeof(char)); 
    int charCount = 0; 
    for(int i = 0; i < strlen(code); i ++){
        if(code[i] == 'a'){
            allocMatcher ++; 
        }else if(code[i] == 'l' && allocMatcher == 1){
            allocMatcher ++; 
        }else if(code[i] == 'l' && allocMatcher == 2){
            allocMatcher ++; 
        }else if(code[i] == 'o' && allocMatcher == 3){
            allocMatcher ++; 
        }else if(code[i] == 'c' && allocMatcher == 4){
            allocMatcher ++; 
        }else if(allocMatcher > 4 && code[i] != ' '){
            newStr[charCount] = code[i]; 
            charCount ++; 
        }
    }
    newStr[charCount] = '\0'; 
    return newStr; 
}

/*
    A helper function that returns the size malloced by the input string code(which calls malloc)

    Take code as the parameter, expected to be a malloc line of code

    Return the size allocated by malloc in code
*/

char* evalMallocSize(char* code){
    char* secondHalf = getStrAfterAlloc(code);  
    char* returnString = malloc(100*sizeof(char)); 
    int charCount = 0; 
    int bracketCount = 0; 
    int copyingFlag = 0; 
    for(int i = 0; i < strlen(secondHalf); i ++){
        if(secondHalf[i] == '(' && copyingFlag == 0){
            copyingFlag = 1; 
        }else if(copyingFlag == 1){
            if(secondHalf[i] == '('){
                bracketCount ++; 
            }else if(secondHalf[i] == ')'){
                if(bracketCount == 0){
                    break; 
                }else{
                    bracketCount--; 
                }
            }
            returnString[charCount] = secondHalf[i]; 
            charCount ++; 
        }
    }
    returnString[charCount] = '\0'; 
    return returnString; 
}

/*
    A helper function that prints out the memory allocation and usage information of memory used by input string code(which is a malloc declaration with its pointer and type declared on the same line)

    Take scope of type char* as parameter(which is the scope where code is found in the program)
    Take code of type char* as parameter(which is expected to be a malloc allocation line of code)

    Return nothing
*/

void printHeap(char* scope, char* code){
    char* varName = getPointerName(code); 
    char* type = getPointerType(code); 
    // type = addStar(type); 
    varName = addStarLeft(varName); 
    char* size = evalMallocSize(code); 
    printf("   %s   %s   %s   %s\n", varName, scope, type, size); 
}

/*
    A helper function that analyzes the program specified by its input string fpath and prints out memory info of all the global vars in the program

    Take fpath of type char* as input, which is expected to be the path to where the c program is located

    Return nothing
*/

void analyzeGlobalVars(char *fpath){
    FILE *sourcecode = fopen(fpath, "r"); 

    char inputString[200]; 

    printf("### static data ###\n"); 

    printVars("global", fpath); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        //Attributes of global variables
        if(classify(inputString) == 0){
            break; 
        }
        printVars("global", inputString); 
    }
    fclose(sourcecode); 
}

/*
    A helper function that prints out all the memory allocation and usage information of all the stack variables in the program specified by the input string path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void analyzeStackVars(char *fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    int stackFlag = 0; 
    char* scope; 

    printf("### stack ###\n"); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        //Attributes of global variables
        if(classify(inputString) == 0){
            scope = functionHandler(inputString); 
            stackFlag = 1; 
        }else if(stackFlag == 1){
            printVars(scope, inputString); 
        }
    }
    fclose(sourcecode); 
}

/*
    A helper function that prints out all the memory allocation and usage information of all the ROData variables in the program specified by the input string path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void analyzeROData(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    if(sourcecode == NULL){
        fprintf(stderr, "File specified is not found. \n");
		exit(1);  
    }
    char inputString[200]; 
    char* scope = "global"; 

    printf("### ROData ###       scope  type  size\n"); 
    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        if(classify(inputString) == 3){
            printRO(scope, inputString); 
        }else if(classify(inputString) == 0){
            scope = getFunctionName(inputString); 
        }
    }
    fclose(sourcecode); 
}

/*
    A helper function and gets and returns the type of a variable initialized in its input varName

    Take varName of tyep char* as parameter, which is a line of code which initializes a variable without giving its type
    Take vars of type char** as parameter, which is an array of variables that are declared earlier in the program along with their names and types
    Take size of type int as parameter, which is the size of parameter vars

    return the type of variable initialized in varName
*/

char* getVarnameType(char** vars, int size, char* varName){
    // Go through every entry in vars and find one that matches the name of var initialized in varName and return the type accordingly
    for(int i = size-1; i >=0; i--){
        char* str = vars[i]; 
        char* beforeEquals = strtok(removeLeadingWhiteSpaces(str), "="); 
        char* type = malloc(100*sizeof(char)); 
        strncpy(type, getStrBefore(beforeEquals, ' '), 99); 
        char* varNames = getStrAfter(beforeEquals, ' '); 

        char* firstVar = trim(strtok(varNames, ",")); 
        char* nextVar = trim(strtok(NULL, ",")); 
        if(strcmp(firstVar, varName) == 0){
            return type; 
        }
        while(isEmpty(nextVar) != 1){
            if(strcmp(nextVar, varName) == 0){
                return type; 
            }
            nextVar = trim(strtok(NULL, ",")); 
        }
    }
    return NULL; 
}

/*
    A helper function that prints out all the memory allocation and usage information of all the heap data allocation in the program specified by the input string path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/
void analyzeHeap(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    char* scope = "global"; 

    char* vars[200]; 
    int index = 0; 

    printf("### heap ###\n"); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        // printf("%s", inputString); 
        //Attributes of global variables
        int class = classify(inputString); 
        if(class == 0){
            index = 0; 
            scope = getFunctionName(inputString); 
            index = storeFunctionParam(inputString, vars, index); 
        }else if(class == 1){
            printHeap(scope, inputString); 
        }else if(class == 10){
            char* varName = trim(getStrBefore(inputString, '=')); 
            char* type = getVarnameType(vars, index, varName); 
            varName = addStarLeft(varName); 
            if(type != NULL){
                if(type[strlen(type) - 1] == '*'){
                    type = trim(strtok(type, "*")); 
                }
            }
            char* size = evalMallocSize(inputString); 
            printf("   %s   %s   %s   %s\n", varName, scope, type, size); 
        }else if(class == 4 || class == 2){
            char* temp = malloc(100*sizeof(char)); 
            char* beforeEquals = getStrBefore(inputString, '='); 
            strncpy(temp, beforeEquals, 99); 
            vars[index] = temp; 
            index ++; 
        }
    }
    fclose(sourcecode); 
}
/*
    A helper function that prints out the total number of lines in the program specified by its input path and the number of functions in it

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/
void printTotalLinesAndFunctions(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    int totalLines = 0; 
    int totalFunctions = 0; 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        if(classify(inputString) == 0){
            totalFunctions ++; 
        }
        totalLines ++; 
    }
    fclose(sourcecode); 
    printf("  - Total number of lines in the file: %d\n", totalLines); 
    printf("  - Total number of functions: %d\n", totalFunctions); 
}

/*
    A helper function that prints out all the function names in program specified by its input path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void printFunctionNames(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    char* functionName = ""; 
    int isFirst = 1; 

    printf("   "); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        if(classify(inputString) == 0){
            functionName = getFunctionName(inputString); 
            if(isFirst == 1){
                isFirst = 0; 
                printf(" %s", functionName); 
            }else{
                printf(", %s", functionName); 
            }
        }
    }
    printf("\n"); 
    fclose(sourcecode); 
}

/*
    A helper function that prints out how many variables are declared in each function in the program specified by the input string path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void printFunctionVarCount(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    char* functionName = ""; 
    int varCount = 0; 

    printf("  - Total number of variables per function:\n"); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        if(classify(inputString) == 0){
            if(strlen(functionName) != 0){
                printf("    %s: %d\n", functionName, varCount);  
            }
            varCount = 0; 
            functionName = getFunctionName(inputString); 
            varCount += functionVarCounter(inputString); 
        }else{
            varCount += countVars(inputString); 
        }
    }
    if(strlen(functionName) != 0){
        printf("    %s: %d\n", functionName, varCount);
    }  
    fclose(sourcecode); 
}

/*
    A function that counts the number of '{' - the number of '}' in its input string

    Take code of type char* as parameter

    Return the number of '{' - the number of '}'
*/

int countBrackets(char* code){
    int bracketCount = 0; 
    for(int i = 0; i < strlen(code); i ++){
        if(code[i] == '{'){
            bracketCount ++; 
        }else if(code[i] == '}'){
            bracketCount --; 
        }
    }
    return bracketCount; 
}

/*
    A helper function that prints out number of lines per function in the program specified by the input string path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void printFunctionLines(char* fpath){
    FILE *sourcecode = fopen(fpath, "r"); 
    char inputString[200]; 
    char* functionName = ""; 
    int startCounting = -1; 
    int numLines = 0; 
    int bracketCount = 0; 

    printf("  - Total number of lines per functions:\n"); 

    while(!feof(sourcecode)){
        fgets(inputString, 200, sourcecode); //inputString now has the line scanned
        if(classify(inputString) == 0){
            functionName = getFunctionName(inputString); 
            startCounting = 0; 
        }else if(startCounting == 0){
            startCounting = 1; 
        }else if(startCounting == 1){
            if(strcmp(trim(inputString), "}") == 0 && bracketCount == 0){
                startCounting = -1; 
                printf("    %s: %d\n", functionName, numLines); 
                functionName = ""; 
                numLines = 0; 
            }else{
                numLines ++; 
                bracketCount = bracketCount + countBrackets(inputString); 
            }
        }
    }

    fclose(sourcecode); 
}

/*
    A helper function that calls necessary helper functions to print out the specific stats of the program specifed by the input path

    Take fpath of type char* as parameter, which is expected to be the c program to analyze

    Return nothing
*/

void analyzeStats(char* fpath){
    printf("**** STATS ****\n"); 
    printTotalLinesAndFunctions(fpath); 
    printFunctionNames(fpath); 
    printFunctionLines(fpath); 
    printFunctionVarCount(fpath); 
}

/*
    The main program that calls a variety of other helper functions to print out the necessary information about the memory model of the C program specified by the command line argument

    Take input argc of type int, which is the number of command line arguments
    Take input of argv, which is a vector of commandline arguments

*/

int main(int argc, char** argv){
    //Parse commandline
    // char *testStr = "       int * function1 (int i, int j, char        character)"; 
    printf(">>> Memory Model Layout <<<\n"); 
    printf("\n"); 

    printf("***  exec // text ***\n"); 
    if(argv[1] == NULL){
        fprintf(stderr, "File path is empty! \n");
		exit(1);  
    }
    printf("   %s\n", argv[1]); 
    printf("\n"); 

    analyzeROData(argv[1]); 
    printf("\n"); 

    analyzeGlobalVars(argv[1]); 
    printf("\n"); 

    analyzeHeap(argv[1]); 
    printf("\n"); 

    printf("####################\n"); 
    printf("### unused space ###\n"); 
    printf("####################\n"); 
    printf("\n"); 

    analyzeStackVars(argv[1]); 
    printf("\n"); 

    analyzeStats(argv[1]); 

    printf("//////////////////////////////\n"); 
}