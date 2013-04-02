#include "Function.h"


Function::Function()
{
	m_pFunction	= NULL;
}
	
void Function::setFuncPtr(void (*a_pFunc)())
{
	m_pFunction	= a_pFunc;
}

void Function::setName(std::string a_name)
{
	m_name	= a_name;
}

std::string Function::getName()
{
	return m_name;
}

void Function::runFunc()
{
	m_pFunction();
}