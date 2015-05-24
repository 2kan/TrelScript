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

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <memory>
#include <fstream>
#include <vector>

class Interpreter;
class Function;
struct Line;

class Script
{
public:
	Script();
	Script(std::string file);
	~Script();

	bool	executeScript();
	void	addLibFunction(std::string a_funcName, void(*a_func)());

private:
	void	setConfig(std::string a_settingName, std::string a_settingValue);
	void	setFunctions();
	bool	getLines();

	int		executeFunction(std::string a_funcName);
	// Start of trelscript as a lib implementation
	int		runLibFunction(std::string a_funcName);

	std::unique_ptr<Interpreter>	interpreter;
	std::vector<Function>			m_functions;
	std::vector<Function>			m_libFuncs;
	std::vector<Line>				m_lines;

	bool			m_open;
	std::string		m_filepath;
	std::string		m_line;

	int	m_lineNumber;
	int m_recursionDepth;

	bool m_skipToRoasted;
	bool m_inLoop;
	int m_loopLine;
};

#endif // __SCRIPT_H__
