# Mol
Mol (Matrix Operation Language)

What follows is a short description of Drake Oswald's CS 4800 project, Mol. 

Mol is a Domain-Specific Language (DSL) that focuses upon the domain of Linear
Algebra, specifically matrices and matrix operations. The purpose of Mol, as
it exists in this iteration, is three-fold: to act as a study into language
design, to implement the first steps of a compiler for Mol, and to to aid the
implementor in becoming more familiar with C.

At the start of the project, Mol was intended to be a full compiler; however,
time constraints, complexities of developing in a less familiar languages, and
the sheer scale of full compiler for a complex language lead to the project
focusing upon language design and developing a parser that can determine the
if a program is syntactically valid. For a full description on the language
features see doc/molFeatures.txt. Furthermore, for a full account on the 
progression of the project see doc/molDevelepment.txt.


###Decription of File Structure and Files###

doc- contains all relevant files about the design, grammar, and development of 
     Mol as a language.

examples- contains examples of mol programs.

include- contains all of the C header files necessary for the Mol compiler.

src- contains all of the C files that make up the Mol compiler

Makefile- file that specifies settings for the make command.


###Known Error###

As of now there is one known error. Per the specifications of the language,
both a vector and a matrix should be able to set the value of a spot through
the following sytax:

Vector:
    vct v1 = v[1 2 3];
    v1[2] = 4;
    print(v1);
    #In this example the print statement should be [1 2 4].#

Matrix:
    mat m1 = [1 2; 1 2];
    m1[1;1] = 3;
    print(m1);
    #In this example the print statement should be [1 2; 1 3];

As of now the error for both of these cases have an error when they see the
equals sign in the assignment statement. In both cases the nonterminal at the
top of the stack is Term-Tail and the token that is next in the token stream is
the equals sign. As the grammar is structured right now, the first and follow
sets of Term-Tail do not have the equals sign as a terminal to be matched as a 
rule. Therefore, the grammar around assignmets of vectors and matricies needs
to be reanalysed.


###To Run Recognition Parser###

1. Navigate to the root directory of the project.

2. Run the make command:

    make

Note: upon a successful make, the bin and obj folders should be created.

3. Run the scan executable, specifing the mol file to be scanned:

    ./bin/scan examples/fibonacci.mol

Note: the fibonacci.mol part of the example is interchangable with any program
      name.

4. Once you are done you can utilize the make clean command:

    make clean