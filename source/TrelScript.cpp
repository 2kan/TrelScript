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
	m_version	= "0.4.2";
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