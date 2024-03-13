LISP INTERPRETER:

This project is an interpreter for a LISP-like language whose grammar and features can be found on
https://2022.aulaweb.unige.it in the course 86755 > Progetto finale >
Descrizione del progetto (slide .pdf - Aggiornate 19/5/2023).

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

If something goes wrong during parsing the parser throws an exception and the main catch it making the program stop after
printing an error message.
