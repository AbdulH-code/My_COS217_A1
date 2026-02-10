/*
 * Decomment program
 * COS 217 Assignment 1
 * Created by Abdulkadir Husein
*/

#include <stdio.h>

/* States associated with program DFA */
enum Statetype {START, PRINT, LITERAL_SINGLE, LITERAL_DOUBLE, CHECK_START, COMMENT, CHECK_END};
/* Exit Codes returned by main */
enum Exitcode {EXIT_SUCCESS, EXIT_FAILURE};
/* Number of lines written to std out */
//int lineCount = 1;
/* The line of the most recent comment start */
/*int commentLine;*/

/* updates the line count when argument is a newline character */
/*int updateLineCount(int c) {
    if (c == '\n') {lineCount++;}
    return 0;
}*/

/* Starting state of DFA, chooses next state and outputs the char from stdin unless it is a forward slash */
enum Statetype handleStart(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CHECK_START;
    }
    else if (c == '\'') {
        state = LITERAL_SINGLE;
        putchar(c);
    }
    else if (c == '"') {
        state = LITERAL_DOUBLE;
        putchar(c);
    }
    else {
        state = PRINT;
        putchar(c);
    }
    /*updateLineCount(c);*/
    return state;
}

/* Prints char from stdin unless it is a forward slash, updates state */
enum Statetype handlePrint(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CHECK_START;
    }
    else if (c == '\'') {
        state = LITERAL_SINGLE;
        putchar(c);
    }
    else if (c == '"') {
        state = LITERAL_DOUBLE;
        putchar(c);
    }
    else {
        state = PRINT;
        putchar(c);
    }
    /*updateLineCount(c);*/
    return state;
}

/* Prints all chars inputted to it and continues to loop back to itself until the closing single quote is found */
enum Statetype handleLiteral_Single(int c) {
    enum Statetype state;
    putchar(c);
    if (c == '\'') {
        state = PRINT;
    }
    else if (c == '\\') {
        state = LITERAL_SINGLE;
        putchar(getchar());
    }
    else {
        state = LITERAL_SINGLE;
    }
    /*updateLineCount(c);*/
    return state;
}

/* Prints all chars inputted to it and continues to loop back to itself until the closing double quote is found */
enum Statetype handleLiteral_Double(int c) {
    enum Statetype state;
    putchar(c);
    if (c == '"') {
        state = PRINT;
    }
    else if (c == '\\') {
        state = LITERAL_DOUBLE;
        putchar(getchar());
    }
    else {
        state = LITERAL_DOUBLE;
    }
    /*updateLineCount(c);*/
    return state;
}


/* Checks if a comment has started in stdin (prints space if so), checks if literal is started, and loops back if
 * another forward slash is found in stdin */
enum Statetype handleCheck_Start(int c) {
    enum Statetype state;
    if (c == '*') {
        printf(" ");
        //commentLine = lineCount;
        state = COMMENT;
    }
    else if (c == '\'') {
        state = LITERAL_SINGLE;
        putchar(c);
    }
    else if (c == '"') {
        state = LITERAL_DOUBLE;
        putchar(c);
    }
    else if (c == '/') {
        printf("/");
        state = CHECK_START;
    }
    else {
        printf("/");
        state = PRINT;
        putchar(c);
    }
    /*updateLineCount(c);*/
    return state;
}

/* Loops through characters in comment and only prints if it is newline, checks for end of comment '*' */
enum Statetype handleComment(int c) {
    enum Statetype state;
    if (c == '\n') {
        putchar(c);
        state = COMMENT;
    }
    else if (c == '*') {
        state = CHECK_END;
    }
    else {
        state = COMMENT;
    }
    /*updateLineCount(c);*/
    return state;
}

/* checks if comment is ended by forward slash, loops back if another asterisk is found, and prints newline if found */
enum Statetype handleCheck_End(int c) {
    enum Statetype state;
    if (c == '/') {
        state = START;
    }
    else if (c == '*') {
        state = CHECK_END;
    }
    else if (c == '\n') {
        putchar(c);
        state = COMMENT;
    }
    else {
        state = COMMENT;
    }
    /*updateLineCount(c);*/
    return state;
}

/* Determines exit code based on current state and prints error message if it was a reject state */
int handleEOF(enum Statetype state, int line) {
    enum Exitcode;
    if (state == COMMENT || state == CHECK_END) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", line);
        return EXIT_FAILURE;
    }
    else {return EXIT_SUCCESS;}
}

int main(void) {
    int c; /* current character in stdin */
    int commentLine = 0;
    int lineCount = 1;
    enum Statetype state = START;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {lineCount++;}
        switch (state) {
            case START:
                state = handleStart(c);
                break;
            case PRINT:
                state = handlePrint(c);
                break;
            case LITERAL_SINGLE:
                state = handleLiteral_Single(c);
                break;
            case LITERAL_DOUBLE:
                state = handleLiteral_Double(c);
                break;
            case CHECK_START:
                if (c == '*') {commentLine = lineCount;}
                state = handleCheck_Start(c);
                break;
            case COMMENT:
                state = handleComment(c);
                break;
            case CHECK_END:
                state = handleCheck_End(c);
                break;
        }
    }
    return handleEOF(state, commentLine);
}

