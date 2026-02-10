/*
 * Decomment program
 * COS 217 Assignment 1
 * Created by Abdulkadir Husein
*/

#include <stdio.h>

/* States associated with program DFA */
enum Statetype {START, PRINT, LITERAL_SINGLE, LITERAL_DOUBLE, CHECK_START, COMMENT, CHECK_END, ESCAPED_DOUBLE,
        ESCAPED_SINGLE};
enum Exitcode {EXIT_SUCCESS, EXIT_FAILURE};
int lineCount = 1;
int commentLine;

int updateLineCount(int c) {
    if (c == '\n') {lineCount++;}
    return 0;
}

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
    updateLineCount(c);
    return state;
}

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
    updateLineCount(c);
    return state;
}

enum Statetype handleLiteral_Single(int c) {
    enum Statetype state;
    if (c == '\'') {
        state = PRINT;
    }
    else if (c == '\\') {
        state = ESCAPED_SINGLE;
    }
    else {
        state = LITERAL_SINGLE;
    }
    putchar(c);
    updateLineCount(c);
    return state;
}

enum Statetype handleEscaped_Single(int c) {
    enum Statetype state;
    putchar(c);
    state = LITERAL_SINGLE;
    return state;
}

enum Statetype handleLiteral_Double(int c) {
    enum Statetype state;
    if (c == '"') {
        state = PRINT;
    }
    else if (c == '\\') {
        state = ESCAPED_DOUBLE;
        putchar(c);
    }
    else {
        state = LITERAL_DOUBLE;
    }
    putchar(c);
    updateLineCount(c);
    return state;
}

enum Statetype handleEscaped_Double(int c) {
    enum Statetype state;
    putchar(c);
    state = LITERAL_DOUBLE;
    return state;
}

enum Statetype handleCheck_Start(int c) {
    enum Statetype state;
    if (c == '*') {
        printf(" ");
        commentLine = lineCount;
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
    updateLineCount(c);
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
    updateLineCount(c);
    return state;
}

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
    updateLineCount(c);
    return state;
}

int handleEOF(enum Statetype state) {
    enum Exitcode;
    if (state == COMMENT || state == CHECK_END) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentLine);
        return EXIT_FAILURE;
    }
    else {return EXIT_SUCCESS;}
}

int main(void) {
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
            case LITERAL_SINGLE:
                state = handleLiteral_Single(c);
                break;
            case LITERAL_DOUBLE:
                state = handleLiteral_Double(c);
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
            case ESCAPED_SINGLE:
                state = handleEscaped_Single(c);
                break;
            case ESCAPED_DOUBLE:
                state = handleEscaped_Double(c);
        }
    }
    return handleEOF(state);
}

