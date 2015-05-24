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

class Scope
{
public:
	Scope();
	Scope(unsigned int a_id);
	~Scope();

	Var *vars;
	int varCount;
	unsigned int id;
};

#endif // __SCOPE_H__
