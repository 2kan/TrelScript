#include <iostream>
#include <string>
#include "TrelScript.h"

///////////////////////////////////////////////////////////
// Main function                                         //
///////////////////////////////////////////////////////////
int main()
{
	TrelScript *ts	= new TrelScript("testfile.trole");
	ts->runScript();
	delete ts;

	system("pause");
	return 0;
}