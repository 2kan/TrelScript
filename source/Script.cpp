#include <fstream>
#include <string>
#include "Interpreter.h"
#include "Function.h"
#include "Script.h"
#include "Line.h"

Script::Script()
{
	interpreter		= new Interpreter();
	m_filepath		= "{{use default}}";
	m_numberOfLines	= 0;
	m_numberOfFunctions	= 0;
	lines			= new Line[1];
	functions		= new Function[1];
}

Script::Script(std::string a_filename)
{
	interpreter		= new Interpreter();
	m_filepath		= a_filename;
	m_numberOfLines	= 0;
	m_numberOfFunctions	= 0;
	getLineCount();
	lines			= new Line[m_numberOfLines];
	functions		= new Function[m_numberOfFunctions];
	getLines();
}

Script::~Script()
{
	delete[] lines;
	delete[] functions;
	delete interpreter;
}

void Script::getLineCount()
{
	std::string	line;
	m_file.open(m_filepath.c_str());
	while (std::getline(m_file, line))
	{
		++m_numberOfLines;
		if(line.substr(0,4) == "spud")
			++m_numberOfFunctions;
	}
	m_file.close();
}

void Script::setFunctions()
{
	std::string	line;
	m_file.open(m_filepath.c_str());
	for(int i=0; i<m_numberOfFunctions; ++i)
	{
		int lineCount	= 0;
		while (std::getline(m_file, line))
		{
			++lineCount;
			if(line.substr(0,4) == "spud")
			{
				functions[i].name		= line.substr(5);
				functions[i].lineStart	= lineCount;
			}
			else if(line == "burn spud")
				functions[i].lineEnd	= lineCount;
		}
	}
	m_file.close();
}

void Script::getLines()
{
	// Open the file
	m_file.open(m_filepath.c_str());
	std::string line;
	int lineCount	= 0;

	while(m_file.good())
	{
		line.clear();
		getline(m_file, line);
		lines[lineCount].setLine(line + '\0');

		++lineCount;
	}
	m_file.close();
}

bool Script::executeScript()
{
	if(m_filepath != "{{use default}}")
	{
		for(int i=0; i<m_numberOfLines; ++i)
		{
			if(lines[i].line != "") // Don't waste time
			{
				// If the interpreter returns zero, exit the program (means a call to "divide by zero")
				if(interpreter->interpretLine(lines[i]) == 0)
					break;
			}
		}
	}
	else
	{
		std::cout << "No script file specified.\n";
	}

	return true;
}