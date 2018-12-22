/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:
    string content;

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &) = 0;
    virtual void parse(TokenScanner &, string &) = 0;

};


class REM : public Statement
{
public :
    REM() = default;
    virtual ~REM() = default;
    virtual void execute(EvalState &);
    virtual void parse(TokenScanner &, string &);


};

class IF : public Statement
{
public :
    IF() = default;
    virtual ~IF();
    virtual void execute(EvalState &) ;
    virtual void parse(TokenScanner &, string &);

private :
    Expression *lhs;
    Expression *rhs;
    int number;
    std::string cmp;
};

class LET : public Statement
{
public :
    LET() = default;
    virtual ~LET();
    virtual void execute(EvalState & );
    virtual void parse(TokenScanner &, string &);

private :
    Expression *exp;
    std::string name;
};

class GOTO : public Statement
{
public :
    GOTO() = default;
    virtual ~GOTO() = default;
    virtual void execute(EvalState &);
    virtual void parse(TokenScanner &, string &);

private :
    int number;
};

class PRINT : public Statement
{
public :
    PRINT() = default;
    virtual ~PRINT();
    virtual void execute(EvalState &);
    virtual void parse(TokenScanner &, string &);

private :
    Expression *exp;
};

class INPUT : public Statement {
public :
    INPUT() = default;
    virtual ~INPUT() = default;
    virtual void execute(EvalState &);
    virtual void parse(TokenScanner &, string &);

private :
    std::string name;
};

class END : public Statement{
public :
    END() = default;
    virtual ~END() = default;
    virtual void execute(EvalState &);
    virtual void parse(TokenScanner &, string &);
};

Statement * getstate(TokenScanner &, string &);
/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

#endif
