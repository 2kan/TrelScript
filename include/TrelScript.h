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