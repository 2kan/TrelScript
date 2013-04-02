#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

class Function
{
public:
	Function();

	void setFuncPtr(void (*a_pFunc)());
	void setName(std::string a_name);
	std::string getName();

	void runFunc();

	
	int	lineStart;
	int	lineEnd;
	void (*m_pFunction)();
	
private:
	std::string m_name;
};



#endif // __FUNCTION_H__