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

#ifndef __TRELSCRIPT_H__
#define __TRELSCRIPT_H__

// Forward declaring
class Script;

class TrelScript
{
public:
	TrelScript();
	TrelScript(std::string a_filepath);
	~TrelScript();

	void runScript();
	void addFunc(std::string a_funcName, void (*a_func)());
private:
	void setInfo();

	Script *m_script;
	std::string m_filepath;
	std::string m_name;
	std::string m_version;
};

#endif // __TRELSCRIPT_H__
