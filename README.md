## Project Structure :
- the project contains the following components :
    1. a poly.c and poly.h those are the project's core codebase, they respectively contain implementation and declaration of the three main algorithms, karatsuba, toom-cook, and the naive one, as well as some helper functions for simplifying the implementation of the algorithms. 
    2. The main.c file contains the function calls of the three algorithms. it supports both commande-line arguments and user input.
    3. poly_wrapper.py is a small implementation of a shared library wrapper. It allows executing the poly.c's functions from a python script.
    4. test.py runs the three algorithms on a given range of polynomial degrees and plots a graph of in regards to their execution time.

## Execution : 
- to execute the .c files directly, compile the main.c and poly.c files using a c compiler. Ex: gcc main.c poly.c poly.h -o main. Then we have three scenarios : 
    1. scenario 1: we can provide two command line arguments p and max_degree, p is the prime number of the field Z/pZ and max_degree will be the degree of the two polynomials the will be multiplicated.
    In this scenario, the program will randomly generate the coefficients from the range (0, max_degree).
    **Command line example with p = 17 and max_degree = 10: .\main 17 10**
    2. scenario 2: we can provide one argument which will be considered the prime number. In this case the use will be prompted to enter the two polynomials' degrees as well as their coefficients.
    **Command line example with p = 17 : .\main 17**
    3. scenario 3: we can simply run the program without providing any arguments; In this case the user will be prompted to to enter the polynomials' degrees and their coeficients. And the prime number will take a default value of 13.
    **Command line example: .\main**
- to execute the test.py, we simply run the python file. we can also provide the same arguments as before.
    **Command line example: python test.py 17 10**
    **Command line example: python test.py**
**Note:** the poly.so file can cause some execution problems when the python interpreter's version is not x32
