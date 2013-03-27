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
	
	void setFuncPtr(void* a_pFunc)
	{
		m_pFunction	= a_pFunc;
	}
	
	void* getFuncPtr()
	{
		return m_pFunction;
	}
	
	std::string name;
	int	lineStart;
	int	lineEnd;
	
private:
	// Trelscript as lib
	void *m_pFunction;
};



#endif // __FUNCTION_H__