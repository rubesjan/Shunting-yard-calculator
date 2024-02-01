# Shell calculator with unlimited precision including calculation with decimal numbers.

With Factorial and Round functions. e.g. Round(20.5) or Factorial(100).

Offers power '^', modulus '%', integer division '/', multiplication '*', addition '+' and substraction '-'.

Mathematical expression must be in infix notation, operations excluding functions can be nested with parenthesis.

Results can be stored in variables. Variables can be exported to user readable file, they can be also imported back. Importing variables overwrites current variables values. Exporting overwrites the file. Variables names can contain only alphabetic characters. Variables current values can be printed by simply writing the variable's name. Calculator can be exited by writing "exit".

Calculator parses the expression using Shunting-yard algorithm into postfix notation. Then creates abstract syntax tree from the expression and evaluates it. Nodes in the AST are polymorphic. Each node represents operator or a number.

Numbers are also polymorphic. Numbers are stored based on their density of digits - bytes. They are stored in a list of bytes - in 256 number system. Dense numbers are stored in a vector of bytes (class CLong). Numbers with lots of null bytes are stored in a map with number of the byte and the value (class CShort), null bytes are not stored. All numbers are stored using complementary code.

to run the application use command:
make run

for usage example see:<br>
examples/var.txt

to see documentation use commands:<br>
make doc;
firefox ./doc/index.html

to delete temporary files use command:<br>
make clean
