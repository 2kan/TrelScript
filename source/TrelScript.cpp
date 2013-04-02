#include <iostream>
#include <string>
#include "TrelScript.h"
#include "Script.h"

TrelScript::TrelScript()
{
	m_filepath	= "";
	m_script	= new Script(m_filepath);
	setInfo();
}

TrelScript::TrelScript(std::string a_filepath)
{
	m_filepath	= a_filepath;
	m_script	= new Script(m_filepath);
	setInfo();
}

TrelScript::~TrelScript()
{
	//delete m_script;
	std::cout << "Execution complete.\n";
}

void TrelScript::setInfo()
{
	m_name		= "Trel Script";
	m_version	= "0.4";
}

void TrelScript::runScript()
{
	std::cout << "~~ " + m_name + " v" + m_version + " ~~" << std::endl;
	m_script->executeScript();
}

void TrelScript::addFunc(std::string a_funcName, void (*a_func)())
{
	m_script->addLibFunction(a_funcName, a_func);
}