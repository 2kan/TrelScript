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
	setFunctions();
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
		bool skipLine	= false;
		for(int lineNum=0; lineNum<m_numberOfLines; ++lineNum)
		{
			if(lines[lineNum].line != "") // If it's an empty line, just ignore it
			{
				// Check if the script calls a function
				if(lines[lineNum].words[0] == "eat")
				{
					for(int i=0; i<m_numberOfFunctions; ++i) // Get the function it called
					{
						if(lines[lineNum].words[1] == functions[i].name)
						{
							Line inlineCommand;
							inlineCommand.setLine("ham barf");

							// Create new scope for function
							interpreter->interpretLine(inlineCommand);
							// Execute each line of the function, then break
							for(int funcLineNum=functions[i].lineStart; funcLineNum<functions[i].lineEnd-1; ++funcLineNum)
							{
								interpreter->interpretLine(lines[funcLineNum]);
							}
							// End the scope
							inlineCommand.setLine("ham eat");
							interpreter->interpretLine(inlineCommand);
							break;
						}
					}
				}
				else
				{
					if(lines[lineNum].words[0] == "spud")
						skipLine	= true;

					if(!skipLine)
					{
						// If the interpreter returns zero, exit the program (means a call to "divide by zero")
						if(interpreter->interpretLine(lines[lineNum]) == 0)
							break;
					}
					
					if(lines[lineNum].words[0] == "burn")
						skipLine	= false;
				}
			}
		}
	}
	else
	{
		std::cout << "No script file specified.\n";
	}

	return true;
}