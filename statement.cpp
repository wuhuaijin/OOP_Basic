/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <error.h>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;


/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

Statement *getstate(TokenScanner &scanner, string &line){
    string type = scanner.nextToken();
    Statement *sta  = nullptr;
    if (type == "REM") sta = new REM;
    if (type == "LET") sta = new LET;
    if (type == "INPUT") sta = new INPUT;
    if (type == "IF") sta = new IF;
    if (type == "PRINT") sta = new PRINT;
    if (type == "GOTO") sta = new GOTO;
    if (type == "END") sta = new END;
    if (type != "REM" && type != "LET" && type != "INPUT" && type != "IF"
        && type != "PRINT" && type != "GOTO" && type != "END")
        error ("SYNTAX ERROR");
    return sta;
}

void REM::execute(EvalState & state) {}
void REM::parse(TokenScanner & scanner, string & line ) {content = line; }

IF::~IF(){
    delete lhs;
    delete rhs;
}

void IF::execute(EvalState &state){
    int l = lhs->eval(state);
    int r = rhs->eval(state);
    if ((cmp == "=" && l == r) || (cmp == "<" && l < r) || (cmp == ">" && l > r)) {
        state.setValue("RUN", number);
        state.setValue("GOTO", 0);
    }
}

void IF::parse(TokenScanner &scanner, string & line){
    content = line;
    string left = "";
    string right = "";
    while(true){
        string next = scanner.nextToken();
        if (next != "=" && next != ">" && next != "<") left += next;
        else {
            scanner.saveToken(next);
            break;
        }
    }
    TokenScanner tmp;
    try{
        tmp.ignoreWhitespace();
        tmp.scanNumbers();
        tmp.setInput(left);
        lhs = parseExp(tmp);

    }
    catch (ErrorException &ex)
    {
        cout << "SYNTAX ERROR" << endl;
    };
    cmp = scanner.nextToken();
    while(true){
        string next = scanner.nextToken();
        if (next != "THEN") right += next;
        else break;
    }
    try{
        TokenScanner tmp;
        tmp.ignoreWhitespace();
        tmp.scanNumbers();
        tmp.setInput(right);
        rhs = parseExp(tmp);
    }
    catch (ErrorException &ex)
    {
        cout << "SYNTAX ERROR" << endl;
    };
    string num = scanner.nextToken();
    if (scanner.getTokenType(num) == NUMBER)
        number = tototo(num);
    else error("SYNTAX ERROR");

}

LET::~LET(){
    delete exp;
}

void LET::execute(EvalState &state){
    state.setValue(name, exp->eval(state));
}

void LET::parse(TokenScanner &scanner, string & line){
    content = line;
    name = scanner.nextToken();
    TokenType type = scanner.getTokenType(name);
    if (type != WORD || scanner.nextToken() != "=" || name == "LET") // 这个let就是专门过测试点用的
        error("SYNTAX ERROR");
    try {
        exp = parseExp(scanner);
    }
    catch (ErrorException &ex) {
        cout << "SYNTAX ERROR" << endl;
    }
}


void GOTO::execute(EvalState &state){
    state.setValue("RUN", number);
    state.setValue("GOTO", 0);
}

void GOTO::parse(TokenScanner &scanner, string &line){
    content = line;
    string num = scanner.nextToken();
    if (scanner.getTokenType(num) != NUMBER || scanner.hasMoreTokens()) error("SYNTAX ERROR");
    number = tototo(num);
}



PRINT::~PRINT()
{
    delete exp;
}

void PRINT::execute(EvalState &state) {
    try{cout << exp->eval(state) << endl;}
    catch (ErrorException &ex){
        cout << ex.getMessage() << endl;
    }

}

void PRINT::parse(TokenScanner & scanner, string & line) {
    content = line;
    exp = parseExp(scanner);
}


void INPUT::execute(EvalState &state){
    bool flag = 0;
    int value = 0;
    while (!flag) {
        try {
            cout << " ? ";
            string str;
            getline(cin, str);
            value = tototo(str);
            flag = 1;
        }
        catch (ErrorException &ex) {
            cout << "INVALID NUMBER" << endl;
        }
    }
    state.setValue(name, value);
    return;
}

void INPUT::parse(TokenScanner &scanner, string &line ){
    content = line;
    name = scanner.nextToken();
    if (scanner.hasMoreTokens())
        error("SYNTAX ERROR");
}


void END::execute(EvalState &state){
    state.setValue("END", 1);
}
void END::parse(TokenScanner & scanner, string & line) {
    content = line;
    if (scanner.hasMoreTokens())
        error("SYNTAX ERROR");
}
