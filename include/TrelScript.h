#ifndef __TRELSCRIPT_H__
#define __TRELSCRIPT_H__

class TrelScript
{
public:
	TrelScript();
	TrelScript(std::string a_filepath);
	~TrelScript();

	void runScript();
private:
	void setInfo();

	std::string m_filepath;
	std::string m_name;
	std::string m_version;
};

#endif // __TRELSCRIPT_H__