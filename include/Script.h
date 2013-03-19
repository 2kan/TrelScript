#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <fstream>
#include "Interpreter.h"

class Script
{
public:
	Script();
	Script(std::string file);
	~Script();

	bool executeScript();

private:
	Interpreter *interpreter;
	bool openScript();

	std::ifstream m_file;
	std::string m_filepath;
	std::string m_line;
	int lineNumber;
};

#endif // __SCRIPT_H__