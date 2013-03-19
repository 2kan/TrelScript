#include "main.h"
#include "Line.h"
#include "Scope.h"

Scope::Scope()
{
	vars		= new Var[100];
	varCount	= 0;
}

Scope::Scope(unsigned int a_id)
{
	vars		= new Var[100];
	varCount	= 0;
	id	= a_id;
}

Scope::~Scope()
{
	delete[] vars;
}