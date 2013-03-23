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

	std::cout << "Press enter to exit.";
	std::cin.get();
	return 0;
}