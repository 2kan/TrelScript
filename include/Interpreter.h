#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "Scope.h"
#include "Line.h"

#include "Function.h"

class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	
	int interpretLine(Line);
	bool conditionResult(std::string, std::string, std::string);

private:
	void	parseVarNames(Line&);
	std::string	getVarValue(std::string);
	std::string	setVar(Line);
	std::string getInput();
	void	showDebugInfo(std::string);
	void	getScopedVars(Scope*);
	void	createNewScope();
	void	destroyScope();
	int		parseInt(std::string);
	

	int		maxVars;
	int		varCounter;
	bool	debugMode;
	Scope	*scope[50];
	int		lineNumber;
	int		curScope;
	bool	runNextLine;
};

#endif // __INTERPRETER_H__