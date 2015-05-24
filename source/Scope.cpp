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

#include "Line.h"
#include "Scope.h"

Scope::Scope()
{

}

Scope::Scope(unsigned int a_id) :
	m_id(a_id)
{

}

Scope::~Scope()
{

}


const Var& Scope::var(int a_index) const
{
	return m_vars[a_index];
}

Var& Scope::var(int a_index)
{
	return m_vars[a_index];
}

unsigned int Scope::varCount() const
{
	return m_vars.size();
}

unsigned int Scope::id() const
{
	return m_id;
}


void Scope::addVar(std::string a_name, std::string a_value)
{
	Var newVar;
	newVar.name		= a_name;
	newVar.value	= a_value;

	m_vars.push_back(newVar);

}

int Scope::findVar(std::string a_name)
{
	int i = 0;
	for (Var& var : m_vars)
	{
		if (var.name.compare(a_name) == 0)
			return i;

		++i;
	}

	return -1;
}
