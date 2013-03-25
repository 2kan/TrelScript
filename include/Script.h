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
	bool	openScript();
	void	getLineCount();
	void	setFunctions();
	void	getLines();

	Interpreter *interpreter;
	Function	*functions;
	Line		*lines;

	std::ifstream	m_file;
	std::string		m_filepath;
	std::string		m_line;
	int	m_lineNumber;
	int	m_numberOfLines;
	int m_numberOfFunctions;
};

#endif // __SCRIPT_H__