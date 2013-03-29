#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <fstream>
class Interpreter;
class Function;
class Line;

class Script
{
public:
	Script();
	Script(std::string file);
	~Script();

	bool executeScript();

private:
	void	setConfig(std::string a_settingName, std::string a_settingValue);
	void	getLineCount();
	void	setFunctions();
	void	getLines();
	int		executeFunction(std::string a_funcName);
	
	
	// Start of trelscript as a lib implementation
	void	addLibFunction(std::string a_funcName, void (*a_func)());
	void	runLibFunction(std::string a_funcName);
	
	Function	*libFunctions;
	int			maxLibFuncs;
	

	Interpreter *interpreter;
	Function	*functions;
	Line		*lines;

	std::ifstream	m_file;
	std::string		m_filepath;
	std::string		m_line;
	int	m_lineNumber;
	int	m_numberOfLines;
	int m_numberOfFunctions;
	int m_recursionDepth;
};

#endif // __SCRIPT_H__