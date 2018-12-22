/*
 * File: Basic.cpp
 * ---------------
 * Name: wuhuaijin[TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            processLine(getLine(), program, state);
        }
        catch (ErrorException & ex) {
            cout << ex.getMessage()<<endl;
            break;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
/*
* Class: TokenScanner
* -------------------
* This class divides a string into individual tokens.  The typical
* use of the <code>TokenScanner</code> class is illustrated by the
* following pattern, which reads the tokens in the string variable
* <code>input</code>:
*
*<pre>
        *    TokenScanner scanner(input);
*    while (scanner.hasMoreTokens()) {
*       string token = scanner.nextToken();
*       ... process the token ...
*    }
*</pre>
*
* The <code>TokenScanner</code> class exports several additional methods
* that give clients more control over its behavior.  Those methods are
        * described individually in the documentation.
*/

void processLine(string line, Program & program, EvalState & state) {
    TokenScanner scanner;
    //Program tmpprogram;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    //string tmp = scanner.nextToken();

    while (scanner.hasMoreTokens()){
        string tmp = scanner.nextToken();
        if (scanner.getTokenType(tmp) == NUMBER){
            if (scanner.hasMoreTokens())
                program.addSourceLine(tototo(tmp), line, scanner);
            else program.removeSourceLine(tototo(tmp));
            return;
        }
        int case_ = -1;
        if (tmp == "QUIT") case_ = 1;
        if (tmp == "RUN") case_ = 2;
        if (tmp == "LIST") case_ = 3;
        if (tmp == "CLEAR") case_ = 4;
        if (tmp == "HELP") case_ = 5;
        if ((tmp == "LET")|| (tmp == "PRINT")|| (tmp == "INPUT")) case_ = 6;
        switch(case_) {
            case -1:
                error("SYNTAX ERROR"); return;
            case 1:
                exit(0);
                break;
            case 2:
                program.run(state);
                break;
            case 3:
                program.list(); 
                break;
            case 4:
                program.clear(); state.clear();/// """""
                break;
            case 5:
                cout << "what's wrong?" << endl;
            case 6: {
                Statement *sta = nullptr;
                if (tmp == "LET") sta = new LET;
                if (tmp == "PRINT") sta = new PRINT;
                if (tmp == "INPUT") sta = new INPUT;
                sta->parse(scanner, line);
                sta->execute(state);
                delete sta;
                break;
            }
            default:break;
        }
    }
}
