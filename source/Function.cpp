#include "Function.h"


Function::Function()
{
	m_pFunction	= NULL;
}
	
void Function::setFuncPtr(void (*a_pFunc)())
{
	m_pFunction	= a_pFunc;
}