#include <iostream>
#include <string>
#include "TrelScript.h"

///////////////////////////////////////////////////////////
// Main function                                         //
///////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	std::string filename	= "testfile.trole";
	if(argc > 0)
	{
		if(argv[1] != NULL)
			filename	= argv[1];
	}

	TrelScript *ts	= new TrelScript(filename);
	ts->runScript();
	delete ts;

	std::cout << "Press enter to exit.";
	std::cin.get();
	return 0;
}