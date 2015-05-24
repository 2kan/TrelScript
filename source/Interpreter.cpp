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

Interpreter::Interpreter()
{
	maxVars		= 100;
	varCounter	= 0;
	lineNumber	= 0;
	debugMode	= false;
	runNextLine	= true;


	// System scope
	m_scope.push_back(Scope(1));
	// User scope
	m_scope.push_back(Scope(2));

}

Interpreter::~Interpreter()
{
}

int Interpreter::interpretLine(Line l)
{
	bool interpreted = false;
	++lineNumber;

	if (lineNumber == 1)
	{
		if (l.wordCount() == 2 && l.word(0) == "trole" && l.word(1) == "bugs")
		{
			debugMode = true;
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
			for (int i = 1; i < l.wordCount(); ++i)
			{
				std::cout << l.word(i) << " ";
			}
			std::cout << std::endl;
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
			for (unsigned int i = 0; i < m_scope.size(); ++i) //TODO: aren't we meant to check backwards?
			{
				// If variable already exists, update the value
				int index = m_scope[i].findVar(l.word(1));
				if (index != -1)
				{
					Var& var = m_scope[i].var(index);
					var.value	= setVar(l);
					showDebugInfo("Updated variable '" + var.name + "'to new value '" + var.value);
					varExists	= true;
				}
			}

			if (!varExists)
			{
				Scope& scope = m_scope[m_scope.size() - 1];

				std::string value = setVar(l);
				scope.addVar(l.word(1), value);

				showDebugInfo(
					"Created variable '" +	l.word(1) +
					"' with value '" +		value + "'"
					);
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
			//TODO: While loops?
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

bool Interpreter::conditionResult(std::string a_lhs, std::string a_rhs, std::string comparator)
{
	//TODO: The comparison operators make too much sense and must be potatified.

	int lhs = 0;
	int rhs = 0;

	if (a_lhs[0] == '@')
		lhs = parseInt(getVarValue(a_lhs));
	if (a_rhs[0] == '@')
		rhs = parseInt(getVarValue(a_rhs));

	// Let's not use really long ternary operators to do this because that's potato and Tom's a shithead.
	if (comparator == "lt")
		return (lhs < rhs);
	else if (comparator == "gt")
		return (lhs > rhs);
	else if (comparator == "same")
		return (lhs == rhs);
	else if (comparator == "notsame")
		return (lhs == rhs);
		// Haha compiler specific nonstandard extensions.
	else if (comparator == "ltsame")
		return (lhs <= rhs);
	else if (comparator == "gtsame")
		return (lhs >= rhs);
	else
		return false; // If all else fails... and who needs bad syntax handling anyway?
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

std::string Interpreter::getVarValue(std::string a_varName)
{
	if (a_varName == "@seeds")
	{
		return getInput();
	}
	else
	{
		for (unsigned int i = 0; i < m_scope.size(); ++i) //TODO: Shouldn't this be backwards?
		{
			Scope& scope = m_scope[i];
			int index = scope.findVar(a_varName.substr(1));
			if (index != -1)
				return scope.var(index).value;
		}
	}

	return "";
}

std::string Interpreter::setVar(Line a_l)
{
	if (a_l.wordCount() == 7 && a_l.word(3) == "num")
	{
		int lhs	= atoi((a_l.word(4)[0] == '@') ? getVarValue(a_l.word(4)).c_str() : a_l.word(4).c_str());
		int rhs	= atoi((a_l.word(6)[0] == '@') ? getVarValue(a_l.word(6)).c_str() : a_l.word(6).c_str());

		if (a_l.word(5) == "add")
			return std::to_string(lhs + rhs);
		else if (a_l.word(5) == "sub")
			return std::to_string(lhs - rhs);
		else if (a_l.word(5) == "mul")
			return std::to_string(lhs * rhs);
		else if (a_l.word(5) == "div")
			return std::to_string(lhs / rhs);
		else
			return "";
	}
	else
	{
		return a_l.word(3);
	}
}

std::string Interpreter::getInput()
{
	std::string in;
	std::cin >> in;
	std::cin.ignore();
	return in;
}

void Interpreter::showDebugInfo(std::string a_info)
{
	if (debugMode)
		std::cout << a_info << std::endl;
}

void Interpreter::createNewScope()
{
	m_scope.push_back(Scope(m_scope.size() + 1));
}

void Interpreter::destroyScope()
{
	if (m_scope.size() > 0)
		m_scope.pop_back();
}

int Interpreter::parseInt(std::string str)
{
	return atoi(str.c_str());
}
