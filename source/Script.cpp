#include <fstream>
#include <string>
#include "Interpreter.h"
#include "Script.h"
#include "Line.h"

Script::Script()
{
	interpreter	= new Interpreter();
	m_filepath	= "{{use default}}";
}

Script::Script(std::string a_filename)
{
	interpreter	= new Interpreter();
	m_filepath	= a_filename;
}

Script::~Script()
{
	delete interpreter;
}

bool Script::executeScript()
{
	if(m_filepath != "{{use default}}")
	{
		// Open the file
		m_file.open(m_filepath.c_str());
		std::string line;

		// If it opened okay
		if(m_file.is_open())
		{
			while(m_file.good())
			{
				// While there are still lines to load, load the next line and send it to the interpreter to perform magic on
				++lineNumber;
				line.clear();
				getline(m_file, line);
				Line l1;
				l1.setLine(line + '\0');

				if(line != "") // Don't waste time
				{
					// If the interpreter returns zero, exit the program (means a call to "divide by zero")
					if(interpreter->interpretLine(l1) == 0)
						break;
				}
			}
		}
		else
			return false;
	}
	else
	{
		std::cout << "No script file specified.\n";
	}

	return true;
}