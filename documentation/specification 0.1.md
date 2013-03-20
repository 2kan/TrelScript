TrelScript specification 0.1
20 March 2013

Whitespace
--
* Use tab-spaces how you please as they are invisible to the interpreter
* Only use single spaces between keywords and don't start lines with spaces as it will cause the line to be ignored


Comments
--
Preface a line with a single pound sign (#) and the entire line will be ignored. There is currently no way to comment multiple lines without having the pound sign at the beginning of each line


Terminating a program
--
To terminate a program at any stage in the script, type "divide by zero" and the scipt will end.


Scope
--
Scopes can be created and destroyed at will and there is initially two scopes (level 0 for system variables, level 1+ for script variables). The system scope cannot be ended or destroyed.

To create a new scope, type a new line saying "ham barf". This adds a "plate" to the stack (where 'ham' is the plate and 'barfing' is outputting a new plate).

To pop or destroy a scope, type a new line saying "ham eat".

Any variables created belong to the scope they're in and scopes cannot "see" any variables which are in higher-leveled scopes.


Variables
--
To declare and define a variable, type "potato <name> is <value>". This will create a new string variable.

To get the value of created variables, simply type the at-symbol (@) followed by the variable name.


I/O
--
Currently there is only one output function and no input functions. To display something to the console, type "trel" followed by the text to display.


Debug mode
--
To start in debug mode, the first line in the script must be "trole bugs". Debug mode will show output for any variables created and any stacks created or destroyed.