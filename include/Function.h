#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

class Function
{
public:
	Function()
	{
		m_pFunction	= NULL;
	}
	
	void setFuncPtr(void (*a_pFunc)())
	{
		m_pFunction	= a_pFunc;
	}
	
	std::string name;
	int	lineStart;
	int	lineEnd;
	void (*m_pFunction)();
	
private:
	// Trelscript as lib
};



#endif // __FUNCTION_H__