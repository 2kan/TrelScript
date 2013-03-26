TrelScript specification 0.2
==

26 March 2013


Whitespace
--
Use tab-spaces how you please as they are invisible to the interpreter. Only use single spaces between keywords and don't start lines with spaces as it will cause the line to be ignored


Comments
--
Preface a line with a single pound sign (#) and the entire line will be ignored. There is currently no way to comment multiple lines without having the pound sign at the beginning of each line


Terminating a program
--
To terminate a program at any stage in the script, type "divide by zero" and the scipt will end.


Scope
--
Scopes can be created and destroyed at will and there is initially two scopes (level 0 for system variables, level 1+ for script variables). The system scope cannot be ended or destroyed.

To create a new scope, type a new line saying `ham barf`. This adds a "plate" to the stack (where 'ham' is the plate and 'barfing' is outputting a new plate).

To pop or destroy a scope, type a new line and enter `ham eat`.

Any variables created belong to the scope they're in and scopes cannot "see" any variables which are in higher-leveled scopes.

Scopes are created when a function is called and consequently are destroyed when the function has ended.


Variables
--
To declare and define a variable, type:

    potato <name> is <value>

To get the value of created variables, simply type the at-symbol (@) followed by the variable name.

The following example will output the value of a variable named `derp`:

    trel @derp


Special variables
--
Currently there is only one special (system) variable which is used to get input from the user. This variable is `seeds` and is used in the following way

    potato invar is @seeds

This will prompt the user for input and will store the data the user entered in a variable named `invar`


Variable comparison
--
If-statements may be performed on two variables and is done so with the following syntax:

    same @<var1> @<var2>

If `var` has the same value as `var2`, the next line will be executed. If not, the next line will be skipped.

The same statement may be performed, except the next line will only be executed if the two variables aren't equal. Use the following syntax:

    notsame @<var1> @<var2>


Functions
--
Functions can be defined anywhere in the script and can be called at any point (before, after, or inside of a function) in the script. Entering a function creates a new scope which is later destroyed when the function has ended.

To create a function, use the following syntax:

    spud <function name>
        # body of function
    burn spud

To call a function:

    eat <function name>


Math
--
Currently only basic math functionality is implemented. Use the following syntax to perform math functions on a number:

    potato <variable> is num <num1> <function> <num2>

This will set `variable` equal to the result of `num1` and `num2` after having a math function performed. The following math functions are supported: `add` `sub` `mul` `div`.


I/O
--
Currently there is only one output function and one input functions. Refer to the *special variables* section. To display something to the console, type `trel` followed by the text to display.


Debug mode
--
To start in debug mode, the first line in the script must be `trole bugs`. Debug mode will show output for any variables created and any stacks created or destroyed.