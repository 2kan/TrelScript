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
	int varCount;
	unsigned int id;
};

#endif // __SCOPE_H__