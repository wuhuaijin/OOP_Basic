/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include <map>
#include "program.h"
#include "statement.h"
#include "parser.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
   for (auto i = mmp.begin(); i != mmp.end(); i++) delete (*i).second;
   mmp.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line, TokenScanner & scanner) {
   Statement *sta = nullptr;
   sta = getstate(scanner, line);
   if (sta != nullptr) sta->parse(scanner, line);
   mmp[lineNumber] = sta;
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
   mmp.erase(lineNumber);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
   if (mmp.find(lineNumber) == mmp.end()) return "";
    //Returns an iterator to the element following the last element of the container.
    //This element acts as a placeholder; attempting to access it results in undefined behavior.
   return mmp[lineNumber]->content;    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
   return mmp.begin()->first;
   return 0;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    auto i = mmp.find(lineNumber);
    ++i;
    if (i == mmp.end()) return -1;
    return i -> first;

    // Replace this stub with your own code
}
void Program::list(){
   for (auto i : mmp)
      cout << (i.second)->content << endl;
}

void Program::run(EvalState & state) {
   state.setValue("RUN", getFirstLineNumber());
   state.setValue("GOTO", 1);
   state.setValue("END", 0);
   while (!state.getValue("END") && state.getValue("RUN") != -1){
       if (mmp.find(state.getValue("RUN")) == mmp.end())
           error("LINE NUMBER ERROR");
      mmp[state.getValue("RUN")]->execute(state);
      if (!(state.getValue("GOTO")))
         state.setValue("GOTO", 1);
      else
         state.setValue("RUN", getNextLineNumber(state.getValue("RUN")));
   }

}
/*
 * Method: getValue
 * Usage: int value = state.getValue(var);
 * ---------------------------------------
 * Returns the value associated with the specified variable.
 */
