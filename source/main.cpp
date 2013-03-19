#include <iostream>
#include <string>
#include "TrelScript.h"

///////////////////////////////////////////////////////////
// Main function                                         //
///////////////////////////////////////////////////////////
int main()
{
	TrelScript *ts	= new TrelScript();
	ts->runScript();

	system("pause");
	return 0;
}