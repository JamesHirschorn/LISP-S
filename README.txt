Tree Summing
------------

Implementation of: 
http://www.cs.duke.edu/courses/cps100/fall03/assign/extra/treesum.html.

Copyright (C) 2014 James Hirschorn <James.Hirschorn@gmail.com> 
=============================================================================

The program TreeSumming determines whether a pair (I, T), where I is an 
integer and T is a binary tree, has the property that T has a branch whose
elements add up to I. 

The program receives the input as a LISP S-expression.

Examples.
---------

Included are three sample inputs. Input.txt is from the web page above, and
Input-with-errors.1.txt and Input-with-errors.2.txt demonstrate some handling
of invalid inputs.

TreeSumming < Input.txt
TreeSumming < Input-with-errors.1.txt
TreeSumming < Input-with-errors.2.txt

Windows:
echo 14 (5 (4 () () ) (7 () (1 (1 ()()) (3 (4 ()()) ())))) | TreeSumming.exe

Unix:
echo '14 (5 (4 () () ) (7 () (1 (1 ()()) (3 (4 ()()) ()))))' | ./TreeSumming