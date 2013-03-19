#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "Line.h"
#include "Var.h"
#include "main.h"

class Scope
{
public:
	Scope();
	Scope(unsigned int a_id);
	~Scope();

	Var *vars;
	unsigned int id;
	unsigned int varCount;
};

#endif // __SCOPE_H__