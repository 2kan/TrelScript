#include <fstream>
#include <iostream>
#include <string>
#include "Interpreter.h"
#include "Line.h"
#include "Scope.h"

using namespace std;

Interpreter::Interpreter()
{
	curScope	= 0;
	maxVars		= 100;
	varCounter	= 0;
	lineNumber	= 0;
	debugMode	= false;
	runNextLine	= true;


	// System scope
	scope[0]	= new Scope(1);
	// User scope
	scope[1]	= new Scope(2);

	curScope	= 1;

	
}

Interpreter::~Interpreter()
{
	delete[] *scope;
}

int Interpreter::interpretLine(Line &l)
{
	bool interpreted	= false;
	++lineNumber;

	if(lineNumber == 1)
	{
		if(l.numWords == 2 && l.words[0] == "trole" && l.words[1] == "bugs")
		{
			debugMode	= true;
			return 1;
		}
	}

	// Only interpret the line if it isn't a comment
	if(l.line[0] != '#' && runNextLine)
	{
		parseVarNames(l);
		
		if(l.words[0] == "divide" && l.words[1] == "by" && l.words[2] == "zero")
		{
			return 0;
		}


		if(l.words[0] == "trel")
		{
			for(int i=1; i<l.numWords; ++i)
			{
				cout << l.words[i] << " ";
			}
			cout << endl;
		}
		else if(l.words[0] == "ham")
		{
			if(l.words[1] == "barf")
			{
				createNewScope();
				showDebugInfo("Created slice of ham");
			}
			else if(l.words[1] == "eat")
			{
				destroyScope();
				showDebugInfo("Destroyed ham");
			}
		}
		else if(l.words[0] == "potato")
		{
			// Check if the variable already exists
			bool varExists	= false;
			for(int i=0; i<=curScope; ++i)
			{
				for(int k=0; k<=scope[i]->varCount; ++k)
				{
					// If variable already exists, update the value
					if(l.words[1] == scope[i]->vars[k].name)
					{
						scope[i]->vars[k].value	= setVar(l);
						showDebugInfo("Updated variable '" + scope[i]->vars[k].name + "'to new value '" + scope[i]->vars[k].value);
						varExists	= true;
					}
				}
			}
			
			if(!varExists)
			{
				int vcount	= scope[curScope]->varCount;
				scope[curScope]->vars[vcount].name	= l.words[1];
				scope[curScope]->vars[vcount].value	= setVar(l);
				showDebugInfo("Created variable '" + scope[curScope]->vars[vcount].name + "' with value '" + scope[curScope]->vars[vcount].value + "'");
				++scope[curScope]->varCount;
			}
		}
		else if((l.words[0] == "same" || l.words[0] == "notsame") && l.numWords >= 3)
		{
			if(l.words[0] == "same" && l.words[1] != l.words[2])
				runNextLine	= false;
			else if(l.words[0] == "notsame" && l.words[1] == l.words[2])
				runNextLine	= false;
		}

		interpreted	= true;
	}

	if(!interpreted && !runNextLine && l.line[0] != '#')
	{
		runNextLine	= true;
	}

	return 1;
}

void Interpreter::parseVarNames(Line &l)
{
	for(int i=0; i<l.numWords; ++i)
	{
		if(l.words[i][0] == '@')
		{
			l.words[i]	= getVarValue(l.words[i]);
		}
	}
}

string Interpreter::getVarValue(string varName)
{
	string at	= "@";

	if(varName == at + "seeds")
		return getInput();
	else
	{
		for(int i=0; i<=curScope; ++i)
		{
			for(int k=0; k<=scope[i]->varCount; ++k)
			{
				if(at + scope[i]->vars[k].name == varName)
					return scope[i]->vars[k].value;
			}
		}
	}

	return "";
}

string Interpreter::setVar(Line a_l)
{
	if(a_l.numWords == 7 && a_l.words[3] == "num")
	{
		char buffer[16];
		int lhs	= atoi(a_l.words[4].c_str());
		int rhs	= atoi(a_l.words[6].c_str());
		
		if(a_l.words[5] == "add")
			itoa((lhs + rhs), buffer, 10);
		else if(a_l.words[5] == "sub")
			itoa((lhs - rhs), buffer, 10);
		else if(a_l.words[5] == "mul")
			itoa((lhs * rhs), buffer, 10);
		else if(a_l.words[5] == "div")
			itoa((lhs / rhs), buffer, 10);

		return string(buffer);
	}
	else
	{
		return a_l.words[3];
	}
}

string Interpreter::getInput()
{
	string in;
	cin >> in;
	cin.ignore();
	return in;
}

void Interpreter::showDebugInfo(string a_info)
{
	if(debugMode)
		cout << a_info << endl;
}

void Interpreter::getScopedVars(Scope *returnable)
{
	int count	= 0;

	for(int i=0; i<curScope; ++i)
	{
		for(int k=0; k<scope[i]->varCount; ++i)
		{
			returnable->vars[count]	= scope[i]->vars[k];
			++count;
		}
	}
}

void Interpreter::createNewScope()
{
	++curScope;
	scope[curScope]	= new Scope(curScope + 1);
}

void Interpreter::destroyScope()
{
	if(curScope > 0)
	{
		//delete scope[curScope];
		--curScope;
	}
}