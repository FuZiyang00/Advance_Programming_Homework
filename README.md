# Advanced Programming Homework 1

## Group Members: Fu Ziyang (s306770@ds.units.it), Tanja Derin (s278887@ds.units.it), Gabriel Masella (s269856@ds.units.it) 

## Individual contributions 
We started together with the definitons of the classes and their member functions on the header file, which implementations we splitted accordingly:
1) Ziyang Fu: getter functions override on the SparseMatrixCSR derived class, matrix printer, write() operator; 
2) Tanja Derin: override of the (*)operator, transformation function of the SparseMatrixCSR derived class, read() operator;
3) Gabriel Masella: the implementation of the whole SparseMatrixC00 derived class;

## Code explanations
The initializer list takes the number of rows and columns and then randomly generates a sparse matrix directly saved using the arrays of CSR and COO format. 
So the matrix per se has not been allocated memory.
