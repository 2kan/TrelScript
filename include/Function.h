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

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

class Function
{
public:
	Function();

	void setFuncPtr(void(*a_pFunc)());
	void setName(std::string a_name);
	std::string getName();

	void runFunc();


	int	lineStart;
	int	lineEnd;
	void(*m_pFunction)();

private:
	std::string m_name;
};



#endif // __FUNCTION_H__
