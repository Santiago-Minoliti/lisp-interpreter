LISP INTERPRETER:

This project is an interpreter for a LISP-like language whose grammar is the following:

program → stmt_block
stmt_block → statement | ( BLOCK statement_list )
statement_list → statement statement_list | statement
statement → variable_def | io_stmt | cond_stmt | loop_stmt
variable_def → ( SET variable_id num_expr )
io_stmt → ( PRINT num_expr ) | ( INPUT variable_id )
cond_stmt → ( IF bool_expr stmt_block stmt_block )
loop_stmt → ( WHILE bool_expr stmt_block )
num_expr → ( ADD num_expr num_expr ) | ( SUB num_expr num_expr ) | ( MUL num_expr num_expr ) | ( DIV num_expr num_expr ) | number | variable_id
bool_expr → (LT num_expr num_expr) | (GT num_expr num_expr) | (EQ num_expr num_expr) | (AND bool_expr bool_expr) | (OR bool_expr bool_expr) | (NOT bool_expr) | TRUE | FALSE
variable_id → alpha_list
alpha_list → alpha alpha_list | alpha
alpha → a | b | c | . . . | z | A | B | C | . . . | Z
number → - posnumber | posnumber
posnumber → 0 | sigdigit rest
sigdigit → 1 | . . . | 9
rest → digit rest | 
digit → 0 | sigdigit


This interpreter takes in input a file as only argument in line of code when opened via terminal.
The file is read and tokenized in the first part of the execution. It gets divided in the fundamental
and significant fragments that are put in a vector tokenStream.

The stream of token is used to build the structure of the Composite pattern up (Composite pattern is descripted
in the UML table: "lispInterpreterComposite1.dia").

The Composite objects are created with the aid of a manager of the class Factory: the factory uses the Factory Method
pattern to create nodes, stores the nodes in a vector, and deletes all nodes when it is destructed.
The Composite objects must have a interpret() method (following the Interpreter pattern). When the interpret() function
of the Program object is called by the main a recursive chain of interpret function is activated, doing automatically all
the tasks needed.

This lisp interpreter then stops deleting all nodes.

If something goes wrong during parsing the parser throws an exception and the main catches it making the program stop after
printing an error message.
