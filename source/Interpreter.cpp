/*
Copyright 2015 TrelScript maintainers

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
	delete[] * scope;
}

int Interpreter::interpretLine(Line l)
{
	bool interpreted	= false;
	++lineNumber;

	if (lineNumber == 1)
	{
		if (l.wordCount() == 2 && l.word(0) == "trole" && l.word(1) == "bugs")
		{
			debugMode	= true;
			return 1;
		}
	}

	// Only interpret the line if it isn't a comment
	if (l.line()[0] != '#' && runNextLine)
	{
		parseVarNames(l);

		if (l.word(0) == "divide" && l.word(1) == "by" && l.word(2) == "zero")
		{
			return 0;
		}


		if (l.word(0) == "trel")
		{
			for (int i=1; i < l.wordCount(); ++i)
			{
				cout << l.word(i) << " ";
			}
			cout << endl;
		}
		else if (l.word(0) == "ham")
		{
			if (l.word(1) == "barf")
			{
				createNewScope();
				showDebugInfo("Created slice of ham");
			}
			else if (l.word(1) == "eat")
			{
				destroyScope();
				showDebugInfo("Destroyed ham");
			}
		}
		else if (l.word(0) == "potato")
		{
			// Check if the variable already exists
			bool varExists	= false;
			for (int i=0; i <= curScope; ++i)
			{
				for (int k=0; k <= scope[i]->varCount; ++k)
				{
					// If variable already exists, update the value
					if (l.word(1) == scope[i]->vars[k].name)
					{
						scope[i]->vars[k].value	= setVar(l);
						showDebugInfo("Updated variable '" + scope[i]->vars[k].name + "'to new value '" + scope[i]->vars[k].value);
						varExists	= true;
					}
				}
			}

			if (!varExists)
			{
				int vcount	= scope[curScope]->varCount;
				scope[curScope]->vars[vcount].name	= l.word(1);
				scope[curScope]->vars[vcount].value	= setVar(l);
				showDebugInfo("Created variable '" + scope[curScope]->vars[vcount].name + "' with value '" + scope[curScope]->vars[vcount].value + "'");
				++scope[curScope]->varCount;
			}
		}
		else if ((l.word(0) == "same" || l.word(0) == "notsame") && l.wordCount() >= 3)
		{
			if (l.word(0) == "same" && l.word(1) != l.word(2))
				runNextLine	= false;
			else if (l.word(0) == "notsame" && l.word(1) == l.word(2))
				runNextLine	= false;
		}
		else if (l.word(0) == "roast" && l.word(1) == "while")
		{
		}

		interpreted	= true;
	}

	if (!interpreted && !runNextLine && l.line()[0] != '#')
	{
		runNextLine	= true;
	}

	// Interpreted okay, return 1
	return 1;
}

bool Interpreter::conditionResult(std::string lhs, std::string rhs, std::string comparator)
{
	if (lhs[0] == '@')
		lhs	= getVarValue(lhs);
	if (rhs[0] == '@')
		rhs	= getVarValue(rhs);

	// Let's use a really long ternary operator becuase potato
	return (comparator == "lt") ? (parseInt(lhs) < parseInt(rhs)) ? true : false : (comparator == "gt") ? (parseInt(lhs) > parseInt(rhs)) ? true : false : (comparator == "same") ? (lhs == rhs) ? true : false : (comparator == "notsame") ? (lhs != rhs) ? true : false : false;
}

void Interpreter::parseVarNames(Line &l)
{
	for (int i=0; i < l.wordCount(); ++i)
	{
		if (l.word(i)[0] == '@')
		{
			l.word(i) = getVarValue(l.word(i));
		}
	}
}

string Interpreter::getVarValue(string varName)
{
	string at	= "@";

	if (varName == at + "seeds")
		return getInput();
	else
	{
		for (int i=0; i <= curScope; ++i)
		{
			for (int k=0; k <= scope[i]->varCount; ++k)
			{
				if (at + scope[i]->vars[k].name == varName)
					return scope[i]->vars[k].value;
			}
		}
	}

	return "";
}

string Interpreter::setVar(Line a_l)
{
	if (a_l.wordCount() == 7 && a_l.word(3) == "num")
	{
		int lhs	= atoi((a_l.word(4)[0] == '@') ? getVarValue(a_l.word(4)).c_str() : a_l.word(4).c_str());
		int rhs	= atoi((a_l.word(6)[0] == '@') ? getVarValue(a_l.word(6)).c_str() : a_l.word(6).c_str());

		if (a_l.word(5) == "add")
			return std::to_string(lhs - rhs);
		else if (a_l.word(5) == "sub")
			return std::to_string(lhs - rhs);
		else if (a_l.word(5) == "mul")
			return std::to_string(lhs - rhs);
		else if (a_l.word(5) == "div")
			return std::to_string(lhs - rhs);
		else
			return "";
	}
	else
	{
		return a_l.word(3);
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
	if (debugMode)
		cout << a_info << endl;
}

void Interpreter::getScopedVars(Scope *returnable)
{
	int count	= 0;

	for (int i=0; i < curScope; ++i)
	{
		for (int k=0; k < scope[i]->varCount; ++i)
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
	if (curScope > 0)
	{
		//delete scope[curScope];
		--curScope;
	}
}

int Interpreter::parseInt(std::string str)
{
	return atoi(str.c_str());
}
