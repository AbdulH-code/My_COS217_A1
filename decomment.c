/*
 * Decomment program
 * COS 217 Assignment 1
 * Created by Abdulkadir Husein
*/

#include <stdio.h>

/* States associated with program DFA */
enum Statetype {START, PRINT, LITERAL, CHECK_START, COMMENT, CHECK_END};
enum Exitcode {EXIT_SUCCESS, EXIT_FAILURE};

enum Statetype handleStart(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CHECK_START;
    }
    else if (c == '"' || c == '\'') {
        state = LITERAL;
        putchar(c);
    }
    else {
        state = PRINT;
        putchar(c);
    }
    return state;
}

enum Statetype handlePrint(int c) {
    enum Statetype state;
    if (c == '/') {
        state = CHECK_START;
    }
    else if (c == '"' || c == '\'') {
        state = LITERAL;
        putchar(c);
    }
    else {
        state = PRINT;
        putchar(c);
    }
    return state;
}

enum Statetype handleLiteral(int c) {
    enum Statetype state;
    if (c == '\"' || c == '\'') {
        state = PRINT;
    }
    else {
        state = LITERAL;
    }
    putchar(c);
    return state;
}

enum Statetype handleCheck_Start(int c) {
    enum Statetype state;
    if (c == '*') {
        state = COMMENT;
    }
    else if (c == '"' || c == '\'') {
        printf("/");
        state = LITERAL;
        putchar(c);
    }
    else {
        printf("/");
        state = PRINT;
        putchar(c);
    }
    return state;
}

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
    return state;
}

enum Statetype handleCheck_End(int c) {
    enum Statetype state;
    if (c == '/') {
        state = START;
    }
    else {
        state = COMMENT;
        printf("*");
        putchar(c);
    }
    return state;
}

int handleEOF(enum Statetype state) {
    enum Exitcode;
    if (state == COMMENT || state == CHECK_END) {return EXIT_FAILURE;}
    else {return EXIT_SUCCESS;}
}

int main(void){
    int c;
    enum Statetype state = START;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case START:
                state = handleStart(c);
                break;
            case PRINT:
                state = handlePrint(c);
                break;
            case LITERAL:
                state = handleLiteral(c);
                break;
            case CHECK_START:
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

    return handleEOF(state);
}

