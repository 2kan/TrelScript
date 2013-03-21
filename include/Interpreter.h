#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "Scope.h"
#include "Line.h"

class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	
	int interpretLine(Line&);

	int maxVars;
	int varCounter;
	bool debugMode;
	Scope *scope[50];
	int lineNumber;
	int curScope;

private:
	void parseVarNames(Line&);
	std::string getVarValue(std::string);
	std::string setVar(Line);
	void showDebugInfo(std::string);
	void getScopedVars(Scope*);
	void createNewScope();
	void destroyScope();
};

#endif // __INTERPRETER_H__