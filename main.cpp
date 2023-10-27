#include <cmath>
#include <iostream>
#include <vector>
#include "Sparse_Matrix.hpp"

int main() {
    int rows_n, cols_n; 
    rows_n = 5;
    cols_n = 5;

    SparseMatrix *ptr;
    ptr = new SparseMatrixCSR(rows_n, cols_n);
    
    // tests
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    const double read_element = (*ptr)(0,1); // must dereference the ptr before calling the operators
    std::cout << "constant element " << read_element << std::endl;
    (*ptr) (1, 1) = 9;
    std::cout << "non-constant element written to " << (*ptr) (1, 1) << std::endl;
    ptr->print();

    // matrix-vector product tests 
    std::vector<double> v1{1,0,0,0,0}; // base
    std::vector<double> v2{1,1,1,1,1}; 
    (*ptr) * v2;
    delete ptr;
    return 0;
}