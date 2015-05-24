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

#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "Line.h"
#include "Var.h"
#include <string>
#include <vector>

class Scope
{
public:
	Scope();
	Scope(unsigned int a_id);
	~Scope();

	const Var& var(int a_index) const;
	Var& var(int a_index);
	unsigned int varCount() const;
	unsigned int id() const;

	void addVar(std::string a_name, std::string a_value);
	int findVar(std::string a_name);

private:
	std::vector<Var> m_vars;
	unsigned int m_id;
};

#endif // __SCOPE_H__
