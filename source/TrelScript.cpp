#include <iostream>
#include <string>
#include "TrelScript.h"
#include "Script.h"

TrelScript::TrelScript()
{
	m_filepath	= "{{use default}}";
	setInfo();
}

TrelScript::TrelScript(std::string a_filepath)
{
	m_filepath	= a_filepath;
	setInfo();
}

TrelScript::~TrelScript()
{
	std::cout << "Execution complete.\n";
}

void TrelScript::setInfo()
{
	m_name		= "Trel Script";
	m_version	= "0.3.1";
}

void TrelScript::runScript()
{
	std::cout << "~~ " + m_name + " v" + m_version + " ~~" << std::endl;

	Script *thisScript	= new Script(m_filepath);
	thisScript->executeScript();
}