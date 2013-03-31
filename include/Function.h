#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

class Function
{
public:
	Function();
	void setFuncPtr(void (*a_pFunc)());
	
	std::string name;
	int	lineStart;
	int	lineEnd;
	void (*m_pFunction)();
	
private:
	// Trelscript as lib
};



#endif // __FUNCTION_H__